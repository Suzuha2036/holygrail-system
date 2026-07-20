#include "automation_manager.h"

#include "globals.h"
#include "relay_manager.h"
#include "buzzer_manager.h"

// ==========================================
// Internal Variables
// ==========================================

// Used only inside this file
unsigned long lockoutStartMillis = 0;
static bool lastManualOverride = false;

// ==========================================
// Initialize Automation
// ==========================================

void initAutomation()
{
    coolingActive = false;
    coolingLockout = false;
    

    coolingStartedAt = 0;
    coolingLockoutUntil = 0;

    currentProcess = "IDLE";

    fan1Reason = "Idle";
    fan2Reason = "Idle";
    pumpReason = "Idle";
    solenoid1Reason = "Idle";
    solenoid2Reason = "Idle";
}

// ==========================================
// Main Automation
// ==========================================

void runAutomation()
{

    // ==========================================
    // Detect MANUAL -> AUTO transition
    // ==========================================

    if (lastManualOverride && !manualOverride)
    {
        Serial.println("Switching to AUTO Mode");

        logEvent(
            "AUTO_ENABLED",
            "SYSTEM",
            "INFO",
            "Automatic mode enabled",
            "USER"
        );


        allRelaysOff();

        fan1Reason = "Idle";
        fan2Reason = "Idle";
        pumpReason = "Idle";
        solenoid1Reason = "Idle";
        solenoid2Reason = "Idle";

        clearManualCommands();

        currentProcess = "IDLE";
    }

    lastManualOverride = manualOverride;
    if(!lastManualOverride && manualOverride)
    {
        logEvent(
            "MANUAL_ENABLED",
            "MANUAL",
            "INFO",
            "Manual override enabled",
            "USER"
        );
    }


    lastManualOverride = manualOverride;

    
    // ==========================================
    // Manual Override / Remote Control
    // ==========================================

    if (manualOverride)
    {
        currentProcess = "MANUAL";
        return;
    }

    // ==========================================
    // Maintenance Mode
    // ==========================================

    if (maintenanceMode)
    {
        currentProcess = "MAINTENANCE";

        allRelaysOff();
        fan1Reason = "Maintenance Mode";
        fan2Reason = "Maintenance Mode";
        pumpReason = "Maintenance Mode";
        solenoid1Reason = "Maintenance Mode";
        solenoid2Reason = "Maintenance Mode";

        return;
    }

    // ==========================================
    // Fan Control
    // ==========================================

    if (temperature >= maxTemperature)
    {
        fan1On();
        fan2On();

        fan1Reason = "AUTO - High Temperature";
        fan2Reason = "AUTO - High Temperature";
    }
    else
    {
        fan1Off();
        fan2Off();

        fan1Reason = "Idle";
        fan2Reason = "Idle";
    }

    // ==========================================
    // Cooling Lockout
    // ==========================================

    if (coolingLockout)
    {
        if (millis() - lockoutStartMillis >= (unsigned long)coolingLockoutDuration * 1000)
        {
            coolingLockout = false;
            currentProcess = "IDLE";

            Serial.println("Cooling Lockout Finished");
        }

        return;
    }

    // ==========================================
    // Start Cooling
    // ==========================================

    if (!coolingActive &&
        temperature >= maxTemperature &&
        waterLevel > minimumWaterLevel)
    {
        coolingActive = true;

        coolingStartedAt = millis();

        currentProcess = "COOLING";

        Serial.println("Cooling Started");
        logEvent(
            "COOLING_START",
            "COOLING",
            "INFO",
            "Temperature exceeded threshold",
            "AUTO"
        );
        pushNotification(
            "Cooling Started",
            "Automatic cooling cycle started",
            "SYSTEM",
            "INFO",
            "ESP32"
        );

        warningBeep();

        pumpOn();
        pumpReason = "Cooling Cycle";

        delay(2000);

        solenoid1On();
        solenoid1Reason = "Cooling Cycle";
    }

    // ==========================================
    // Cooling Running
    // ==========================================

    if (coolingActive)
    {
        if (millis() - coolingStartedAt >= (unsigned long)wateringDuration * 1000)
        {
            solenoid1Off();
            solenoid1Reason = "Idle";

            pumpOff();
            pumpReason = "Idle";

            coolingActive = false;

            coolingLockout = true;

            lockoutStartMillis = millis();

            coolingLockoutUntil =
                lockoutStartMillis +
                ((unsigned long)coolingLockoutDuration * 1000);

            currentProcess = "LOCKOUT";

            Serial.println("Cooling Finished");
            logEvent(
                "COOLING_END",
                "COOLING",
                "INFO",
                "Cooling cycle completed",
                "AUTO"
            );
            pushNotification(
                "Cooling Finished",
                "Cooling cycle completed successfully",
                "SYSTEM",
                "INFO",
                "ESP32"
            );
        }
    }

    // ==========================================
    // Low Water Protection
    // ==========================================

    if (waterLevel <= minimumWaterLevel)
    {
        pumpOff();
        pumpReason = "Low Water Protection";

        solenoid1Off();
        solenoid1Reason = "Low Water Protection";


        if(!lowWaterEventSent)
        {
            logEvent(
                "LOW_WATER",
                "SAFETY",
                "WARNING",
                "Water level below minimum protection threshold",
                "AUTO"
            );
            pushNotification(
                "Low Water Warning",
                "Water level below minimum protection threshold",
                "SAFETY",
                "WARNING",
                "ESP32"
            );

            lowWaterEventSent = true;
        }
    }
    else
    {
        lowWaterEventSent = false;
    }
}