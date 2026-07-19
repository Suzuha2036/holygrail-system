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


    Serial.println("Firebase Initialized");

};



// =====================================================
// Firebase Background Loop
// =====================================================

void firebaseLoop()
{

    // Required by FirebaseClient

    app.loop();



    if(app.ready())
    {

        firebaseReady = true;

        firebaseConnected = true;

    }
    else
    {

        firebaseReady = false;

        firebaseConnected = false;

    }

}



// =====================================================
// Firebase Synchronization
// =====================================================

void firebaseSync()
{
    if (!wifiConnected || !firebaseReady)
        return;

    if (millis() - lastFirebaseUpload < FIREBASE_UPLOAD_INTERVAL)
        return;

    lastFirebaseUpload = millis();


    uploadCurrentSensors();

    uploadDeviceStatus();

    downloadCommands();
    downloadAutomationSettings();

    applyRemoteCommands();
}

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

    Serial.println("Applying Commands");


    // ==========================
    // Fan 1
    // ==========================

    if(cmdFan1)
        fan1On();
    else
        fan1Off();



    // ==========================
    // Fan 2
    // ==========================

    if(cmdFan2)
        fan2On();
    else
        fan2Off();



    // ==========================
    // Solenoid 1
    // Sprinkler
    // ==========================

    if(cmdSolenoid1)
    {
        pumpOn();
        delay(2000);
        solenoid1On();
    }
    else
    {
        solenoid1Off();
        pumpOff();
    }



    // ==========================
    // Solenoid 2
    // Sanitation Valve
    // ==========================

    if(cmdSolenoid2)
    {
        pumpOn();
        delay(2000);
        solenoid2On();
    }
    else
    {
        solenoid2Off();
    }



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

// =====================================================
// Firebase Status
// =====================================================

bool isFirebaseConnected()
{
    return firebaseConnected;
}