#include "firebase_manager.h"
#define ENABLE_USER_AUTH
#include <Arduino.h>
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>
#include <time.h>

#include "config.h"
#include "globals.h"
#include "relay_manager.h"
#include "firebase_paths.h"

using namespace firebase_ns;


// =====================================================
// Firebase Objects
// =====================================================

WiFiClientSecure sslClient;


// Async Firebase Client
AsyncClientClass aClient(
    sslClient
);


FirebaseApp app;

UserAccount user(
    FIREBASE_API_KEY
);

RealtimeDatabase Database;
AsyncResult databaseResult;


// =====================================================
// Firebase Status
// =====================================================

unsigned long lastFirebaseUpload = 0;

const unsigned long FIREBASE_UPLOAD_INTERVAL = 5000;

bool firebaseReady = false;



// =====================================================
// Remote Commands
// =====================================================

bool cmdFan1 = false;
bool cmdFan2 = false;
bool cmdSolenoid1 = false;
bool cmdSolenoid2 = false;

void downloadCommands();
void applyRemoteCommands();


// =====================================================
// Initialize Firebase
// =====================================================

void initFirebase()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("Initializing Firebase...");
    Serial.println("==============================");


    sslClient.setInsecure();


    configTime(
        GMT_OFFSET_SEC,
        DAYLIGHT_OFFSET_SEC,
        NTP_SERVER
    );


    Serial.println("Synchronizing time...");


    signup(
        aClient,
        app,
        getAuth(user)
    );


    app.getApp<RealtimeDatabase>(Database);


    Database.url(FIREBASE_DATABASE_URL);


    firebaseConnected = false;
    firebaseReady = false;


    Serial.println("Firebase Authentication Started");

}

void firebaseLoop()
{

    // Firebase background processing
    app.loop();


    static bool startupLogged = false;
    static bool thresholdsInitialized = false;


    if(app.ready())
    {

        if(!firebaseConnected)
        {
            Serial.println("[Firebase] Connected");
        }


        firebaseConnected = true;
        firebaseReady = true;



        // ================================
        // Startup Event
        // ================================

        if(!startupLogged)
        {

            logEvent(
                "STARTUP",
                "SYSTEM",
                "INFO",
                "System Boot",
                "ESP32"
            );


            pushNotification(
                "System Started",
                "Holy Grail Piggery System is online.",
                "SYSTEM",
                "INFO",
                "ESP32"
            );


            startupLogged = true;
        }



        // ================================
        // Initialize Defaults
        // ================================

        if(!thresholdsInitialized)
        {

            initializeThresholds();

            thresholdsInitialized = true;
        }



        // ================================
        // Sync Firebase
        // ================================

        firebaseSync();

    }

    else
    {

        firebaseConnected = false;
        firebaseReady = false;


        static unsigned long lastFirebaseWait = 0;


        if(millis() - lastFirebaseWait > 5000)
        {
            Serial.println("[Firebase] Waiting for connection...");
            lastFirebaseWait = millis();
        }

    }

}

void firebaseSync()
{

    if(!firebaseConnected)
    {
        return;
    }


    if(!wifiConnected)
    {
        return;
    }



    if(millis() - lastFirebaseUpload < FIREBASE_UPLOAD_INTERVAL)
    {
        return;
    }


    lastFirebaseUpload = millis();



    Serial.println("[Firebase] Syncing...");



    uploadCurrentSensors();


    uploadDeviceStatus();


    uploadActuatorStatus();



    downloadCommands();


    downloadAutomationSettings();


    downloadThresholds();



    if(manualOverride)
    {

        applyRemoteCommands();

    }

}

void initializeThresholds()
{
    float temp;
    int value;

    // ==========================
    // Maximum Temperature
    // ==========================

    temp = Database.get<float>(
        aClient,
        FB_THRESHOLD_MAXTEMP
    );

    if(temp >= 20 && temp <= 45)
    {
        maxTemperature = temp;
    }
    else
    {
        Database.set<float>(
            aClient,
            FB_THRESHOLD_MAXTEMP,
            maxTemperature
        );
    }

    // ==========================
    // Minimum Humidity
    // ==========================

    temp = Database.get<float>(
        aClient,
        FB_THRESHOLD_MINHUM
    );

    if(temp >= 10 && temp <= 100)
    {
        minHumidity = temp;
    }
    else
    {
        Database.set<float>(
            aClient,
            FB_THRESHOLD_MINHUM,
            minHumidity
        );
    }

    // ==========================
    // Minimum Water Level
    // ==========================

    value = Database.get<int>(
        aClient,
        FB_THRESHOLD_MINWATER
    );

    if(value >= 0 && value <= 100)
    {
        minimumWaterLevel = value;
    }
    else
    {
        Database.set<int>(
            aClient,
            FB_THRESHOLD_MINWATER,
            minimumWaterLevel
        );
    }

    // ==========================
    // Fan Delay
    // ==========================

    value = Database.get<int>(
        aClient,
        FB_THRESHOLD_FANDELAY
    );

    if(value >= 0)
    {
        fanDelay = value;
    }
    else
    {
        Database.set<int>(
            aClient,
            FB_THRESHOLD_FANDELAY,
            fanDelay
        );
    }

    // ==========================
    // Watering Duration
    // ==========================

    value = Database.get<int>(
        aClient,
        FB_THRESHOLD_WATERING
    );

    if(value >= 1)
    {
        wateringDuration = value;
    }
    else
    {
        Database.set<int>(
            aClient,
            FB_THRESHOLD_WATERING,
            wateringDuration
        );
    }

    // ==========================
    // Cooling Lockout
    // ==========================

    value = Database.get<int>(
        aClient,
        FB_THRESHOLD_LOCKOUT
    );

    if(value >= 10)
    {
        coolingLockoutDuration = value;
    }
    else
    {
        Database.set<int>(
            aClient,
            FB_THRESHOLD_LOCKOUT,
            coolingLockoutDuration
        );
    }

    Serial.println("[Firebase] Thresholds initialized.");
}


// =====================================================
// Upload Functions
// =====================================================


void uploadCurrentSensors()
{
    bool success = true;

    success &= Database.set<number_t>(
        aClient,
        FB_CURRENT_TEMPERATURE,
        number_t(temperature, 1)
    );

    success &= Database.set<number_t>(
        aClient,
        FB_CURRENT_HUMIDITY,
        number_t(humidity, 1)
    );

    success &= Database.set<int>(
        aClient,
        FB_CURRENT_WATERLEVEL,
        waterLevel
    );

    // Sensor Status
    sensorStatus = "NORMAL";

    if (temperature >= maxTemperature)
        sensorStatus = "HIGH_TEMPERATURE";

    if (waterLevel <= minimumWaterLevel)
        sensorStatus = "LOW_WATER";

    success &= Database.set<String>(
        aClient,
        FB_CURRENT_STATUS,
        sensorStatus
    );

    success &= Database.set<String>(
        aClient,
        FB_CURRENT_UPDATED,
        getCurrentTimestamp()
    );

    if (success)
    {
        Serial.println("[Firebase] Sensors uploaded.");
    }
    else
    {
        Serial.print("[Firebase] Upload failed: ");
        Serial.println(aClient.lastError().message());
    }
}

void uploadDeviceStatus()
{
    
    bool success = true;

    // Update local status first
    deviceStatus = wifiConnected ? "ONLINE" : "OFFLINE";

    // Device Information
    success &= Database.set<String>(
        aClient,
        FB_DEVICE_NAME,
        DEVICE_NAME
    );

    success &= Database.set<String>(
        aClient,
        FB_DEVICE_FIRMWARE,
        FIRMWARE_VERSION
    );

    
    // Device Status
    success &= Database.set<String>(
        aClient,
        FB_DEVICE_STATUS,
        deviceStatus
    );

    success &= Database.set<String>(
        aClient,
        FB_DEVICE_LASTSEEN,
        getCurrentTimestamp()
    );

    // Network Information
    success &= Database.set<bool>(
        aClient,
        FB_DEVICE_CONNECTED,
        wifiConnected
    );

    success &= Database.set<String>(
        aClient,
        FB_DEVICE_SSID,
        WIFI_SSID
    );

    success &= Database.set<String>(
        aClient,
        FB_DEVICE_IP,
        WiFi.localIP().toString()
    );

    success &= Database.set<int>(
        aClient,
        FB_DEVICE_RSSI,
        WiFi.RSSI()
    );

    if (success)
    {
        Serial.println("[Firebase] Device status uploaded.");
    }
    else
    {
        Serial.print("[Firebase] Device upload failed: ");
        Serial.println(aClient.lastError().message());
    }
}

void uploadActuatorStatus()
{
    bool success = true;

    // =====================================
    // Fan 1
    // =====================================

    success &= Database.set<bool>(
        aClient,
        FB_ACTUATOR_FAN1_STATE,
        fan1State
    );

    success &= Database.set<String>(
        aClient,
        FB_ACTUATOR_FAN1_REASON,
        fan1Reason
    );

    // =====================================
    // Fan 2
    // =====================================

    success &= Database.set<bool>(
        aClient,
        FB_ACTUATOR_FAN2_STATE,
        fan2State
    );

    success &= Database.set<String>(
        aClient,
        FB_ACTUATOR_FAN2_REASON,
        fan2Reason
    );

    // =====================================
    // Pump
    // =====================================

    success &= Database.set<bool>(
        aClient,
        FB_ACTUATOR_PUMP_STATE,
        pumpState
    );

    success &= Database.set<String>(
        aClient,
        FB_ACTUATOR_PUMP_REASON,
        pumpReason
    );

    // =====================================
    // Solenoid 1
    // =====================================

    success &= Database.set<bool>(
        aClient,
        FB_ACTUATOR_SOL1_STATE,
        solenoid1State
    );

    success &= Database.set<String>(
        aClient,
        FB_ACTUATOR_SOL1_REASON,
        solenoid1Reason
    );

    // =====================================
    // Solenoid 2
    // =====================================

    success &= Database.set<bool>(
        aClient,
        FB_ACTUATOR_SOL2_STATE,
        solenoid2State
    );

    success &= Database.set<String>(
        aClient,
        FB_ACTUATOR_SOL2_REASON,
        solenoid2Reason
    );

    if(success)
    {
        Serial.println("[Firebase] Actuator status uploaded.");
    }
    else
    {
        Serial.print("[Firebase] Actuator upload failed: ");
        Serial.println(aClient.lastError().message());
    }
}


// =====================================================
// Download Functions
// =====================================================

void downloadCommands()
{
    cmdFan1 = Database.get<bool>(
        aClient,
        FB_COMMAND_FAN1
    );


    cmdFan2 = Database.get<bool>(
        aClient,
        FB_COMMAND_FAN2
    );


    cmdSolenoid1 = Database.get<bool>(
        aClient,
        FB_COMMAND_SOLENOID1
    );


    cmdSolenoid2 = Database.get<bool>(
        aClient,
        FB_COMMAND_SOLENOID2
    );


    Serial.println("Commands downloaded.");
}

void downloadAutomationSettings()
{

    bool enabled = Database.get<bool>(
        aClient,
        FB_AUTOMATION_ENABLED
    );


    String mode = Database.get<String>(
    aClient,
    FB_AUTOMATION_MODE
    );

    mode.toUpperCase();


    automationEnabled = enabled;
    automationMode = mode;



    if(mode == "MANUAL")
    {
        manualOverride = true;
    }
    else
    {
        manualOverride = false;
    }



    Serial.println("===== Automation Settings =====");

    Serial.print("Enabled: ");
    Serial.println(
        automationEnabled
    );


    Serial.print("Mode: ");
    Serial.println(
        automationMode
    );


    Serial.print("Manual Override: ");
    Serial.println(
        manualOverride
    );


    Serial.println("==============================");

}

void applyRemoteCommands()
{
    // =====================================
    // Fan 1
    // =====================================

    if(cmdFan1)
    {
        fan1On();
        fan1Reason = "MANUAL - App Command";
    }
    else
    {
        fan1Off();
        fan1Reason = "Idle";
    }

    // =====================================
    // Fan 2
    // =====================================

    if(cmdFan2)
    {
        fan2On();
        fan2Reason = "MANUAL - App Command";
    }
    else
    {
        fan2Off();
        fan2Reason = "Idle";
    }

    // =====================================
    // Sprinkler
    // Pump always follows Solenoid 1
    // =====================================

    if(cmdSolenoid1)
    {
        pumpOn();
        solenoid1On();

        pumpReason = "MANUAL - Sprinkler";
        solenoid1Reason = "MANUAL - Sprinkler";
    }
    else
    {
        solenoid1Off();
        pumpOff();

        solenoid1Reason = "Idle";
        pumpReason = "Idle";
    }

    // =====================================
    // Sanitation Valve
    // =====================================

    if(cmdSolenoid2)
    {
        solenoid2On();
        solenoid2Reason = "MANUAL - Sanitation";
    }
    else
    {
        solenoid2Off();
        solenoid2Reason = "Idle";
    }

    Serial.println("Applying Commands");

    Serial.println("Relay States:");

    Serial.print("Fan1: ");
    Serial.println(fan1State);

    Serial.print("Fan2: ");
    Serial.println(fan2State);

    Serial.print("Pump: ");
    Serial.println(pumpState);

    Serial.print("Solenoid1: ");
    Serial.println(solenoid1State);

    Serial.print("Solenoid2: ");
    Serial.println(solenoid2State);
}

void clearManualCommands()
{
    bool success = true;

    success &= Database.set<bool>(
        aClient,
        FB_COMMAND_FAN1,
        false
    );

    success &= Database.set<bool>(
        aClient,
        FB_COMMAND_FAN2,
        false
    );

    success &= Database.set<bool>(
        aClient,
        FB_COMMAND_SOLENOID1,
        false
    );

    success &= Database.set<bool>(
        aClient,
        FB_COMMAND_SOLENOID2,
        false
    );

    // Clear local command variables
    cmdFan1 = false;
    cmdFan2 = false;
    cmdSolenoid1 = false;
    cmdSolenoid2 = false;

    if(success)
    {
        Serial.println("[Firebase] Manual commands cleared.");
    }
    else
    {
        Serial.print("[Firebase] Failed to clear commands: ");
        Serial.println(aClient.lastError().message());
    }
}

void downloadThresholds()
{
    // =====================================
    // Float Values
    // =====================================

    float temp;

    temp = Database.get<float>(
        aClient,
        FB_THRESHOLD_MAXTEMP
    );

    if(temp >= 20 && temp <= 45)
        maxTemperature = temp;

    temp = Database.get<float>(
        aClient,
        FB_THRESHOLD_MINHUM
    );

    if(temp >= 10 && temp <= 100)
        minHumidity = temp;

    // =====================================
    // Integer Values
    // =====================================

    int value;

    // Minimum Water Level
    value = Database.get<int>(
        aClient,
        FB_THRESHOLD_MINWATER
    );

    if(value >= 0 && value <= 100)
        minimumWaterLevel = value;

    // Fan Delay
    value = Database.get<int>(
        aClient,
        FB_THRESHOLD_FANDELAY
    );

    if(value >= 0)
        fanDelay = value;

    // Watering Duration
    value = Database.get<int>(
        aClient,
        FB_THRESHOLD_WATERING
    );

    if(value >= 1)
        wateringDuration = value;

    // Cooling Lockout Duration
    value = Database.get<int>(
        aClient,
        FB_THRESHOLD_LOCKOUT
    );

    if(value >= 10)
        coolingLockoutDuration = value;

    // =====================================
    // Debug
    // =====================================

    Serial.println("[Firebase] Thresholds Updated");

    Serial.println("===== Thresholds =====");

    Serial.print("Max Temperature: ");
    Serial.println(maxTemperature);

    Serial.print("Min Humidity: ");
    Serial.println(minHumidity);

    Serial.print("Minimum Water Level: ");
    Serial.println(minimumWaterLevel);

    Serial.print("Fan Delay: ");
    Serial.println(fanDelay);

    Serial.print("Watering Duration: ");
    Serial.println(wateringDuration);

    Serial.print("Cooling Lockout: ");
    Serial.print(coolingLockoutDuration);
    Serial.println(" sec");

    Serial.println("======================");
}


// =====================================================
// Log Event, Notification, History
// =====================================================

void logEvent(
    String action,
    String category,
    String severity,
    String reason,
    String triggeredBy
)
{

    String eventID = String(millis());


    String basePath =
        String(FB_EVENTS) + "/" + eventID;


    bool success = true;


    success &= Database.set<String>(
        aClient,
        basePath + "/action",
        action
    );


    success &= Database.set<String>(
        aClient,
        basePath + "/category",
        category
    );


    success &= Database.set<String>(
        aClient,
        basePath + "/severity",
        severity
    );


    success &= Database.set<String>(
        aClient,
        basePath + "/reason",
        reason
    );


    success &= Database.set<String>(
        aClient,
        basePath + "/device",
        DEVICE_ID
    );


    success &= Database.set<String>(
        aClient,
        basePath + "/triggeredBy",
        triggeredBy
    );


    success &= Database.set<String>(
        aClient,
        basePath + "/timestamp",
        getCurrentTimestamp()
    );


    if(success)
    {
        Serial.println("[Firebase] Event logged.");

        Serial.print("Event: ");
        Serial.println(action);
    }
    else
    {
        Serial.print("[Firebase] Event failed: ");
        Serial.println(
            aClient.lastError().message()
        );
    }

}

void pushNotification(
    String title,
    String message,
    String type,
    String severity,
    String source
)
{
    String notificationID = String(millis());


    String path =
        String(FB_NOTIFICATIONS) + "/" + notificationID;


    bool success = true;


    success &= Database.set<String>(
        aClient,
        path + "/title",
        title
    );


    success &= Database.set<String>(
        aClient,
        path + "/message",
        message
    );


    success &= Database.set<String>(
        aClient,
        path + "/type",
        type
    );


    success &= Database.set<String>(
        aClient,
        path + "/severity",
        severity
    );


    success &= Database.set<String>(
        aClient,
        path + "/source",
        source
    );


    success &= Database.set<bool>(
        aClient,
        path + "/read",
        false
    );


    success &= Database.set<String>(
        aClient,
        path + "/timestamp",
        getCurrentTimestamp()
    );


    if(success)
    {
        Serial.println("[Firebase] Notification created.");

        Serial.print("Notification: ");
        Serial.println(title);
    }
    else
    {
        Serial.print("[Firebase] Notification failed: ");
        Serial.println(
            aClient.lastError().message()
        );
    }
}


// =====================================================
// Utility Functions
// =====================================================

String getCurrentTimestamp()
{
    struct tm timeinfo;

    if (!getLocalTime(&timeinfo))
    {
        return "";
    }

    char buffer[30];

    strftime(
        buffer,
        sizeof(buffer),
        "%Y-%m-%dT%H:%M:%S",
        &timeinfo
    );

    return String(buffer);
}

bool isFirebaseConnected()
{
    return firebaseConnected;
}