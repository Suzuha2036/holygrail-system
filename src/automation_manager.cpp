#include "automation_manager.h"

#include "globals.h"
#include "relay_manager.h"
#include "buzzer_manager.h"

// ==========================================
// Internal Variables
// ==========================================

// Used only inside this file
unsigned long lockoutStartMillis = 0;

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
}

// ==========================================
// Main Automation
// ==========================================

void runAutomation()
{
    // ==========================================
    // Manual Override
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

        return;
    }

    // ==========================================
    // Fan Control
    // ==========================================

    if (temperature >= maxTemperature)
    {
        fan1On();
        fan2On();
    }
    else
    {
        fan1Off();
        fan2Off();
    }

    // ==========================================
    // Cooling Lockout
    // ==========================================

    if (coolingLockout)
    {
        if (millis() - lockoutStartMillis >= 300000) // 5 minutes
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

        warningBeep();

        pumpOn();

        delay(2000);

        solenoid1On();
    }

    // ==========================================
    // Cooling Running
    // ==========================================

    if (coolingActive)
    {
        if (millis() - coolingStartedAt >= (unsigned long)wateringDuration * 1000)
        {
            solenoid1Off();

            pumpOff();

            coolingActive = false;

            coolingLockout = true;

            lockoutStartMillis = millis();

            coolingLockoutUntil = lockoutStartMillis + 300000;

            currentProcess = "LOCKOUT";

            Serial.println("Cooling Finished");
        }
    }

    // ==========================================
    // Low Water Protection
    // ==========================================

    if (waterLevel <= minimumWaterLevel)
    {
        pumpOff();
        solenoid1Off();
    }
}