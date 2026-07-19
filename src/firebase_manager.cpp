#include "firebase_manager.h"
#define ENABLE_USER_AUTH
#include <Arduino.h>
#include <FirebaseClient.h>
#include <WiFiClientSecure.h>
#include <time.h>

#include "config.h"
#include "globals.h"


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



// =====================================================
// Firebase Status
// =====================================================

unsigned long lastFirebaseUpload = 0;

const unsigned long FIREBASE_UPLOAD_INTERVAL = 5000;


bool firebaseReady = false;



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
    if (!wifiConnected)
        return;

    if (!firebaseReady)
        return;

    if (millis() - lastFirebaseUpload < FIREBASE_UPLOAD_INTERVAL)
        return;

    lastFirebaseUpload = millis();

    uploadCurrentSensors();

    uploadDeviceStatus();
}

void uploadCurrentSensors()
{
    bool success = true;

    success &= Database.set<number_t>(
        aClient,
        FB_SENSORS_CURRENT "/temperature",
        number_t(temperature, 1)
    );

    success &= Database.set<number_t>(
        aClient,
        FB_SENSORS_CURRENT "/humidity",
        number_t(humidity, 1)
    );

    success &= Database.set<int>(
        aClient,
        FB_SENSORS_CURRENT "/waterLevel",
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
        FB_SENSORS_CURRENT "/status",
        sensorStatus
    );

    success &= Database.set<String>(
        aClient,
        "/HolyGrailPiggery/sensors/current/updatedAt",
        getCurrentTimestamp()
    );

    if(success)
    {
        Serial.println("[Firebase] Sensors uploaded.");
    }
    else
    {
        Serial.print("Upload failed: ");
        Serial.println(aClient.lastError().message());
    }
}

void uploadDeviceStatus()
{
    bool success = true;

    // Device Information
    success &= Database.set<String>(
        aClient,
        FB_DEVICE "/name",
        DEVICE_NAME
    );

    success &= Database.set<String>(
        aClient,
        FB_DEVICE "/firmware",
        FIRMWARE_VERSION
    );

    // Device Status
    success &= Database.set<String>(
        aClient,
        FB_DEVICE "/status",
        wifiConnected ? "ONLINE" : "OFFLINE"
    );

    success &= Database.set<String>(
        aClient,
        FB_DEVICE "/lastSeen",
        getCurrentTimestamp()
    );

    // Network Information
    success &= Database.set<bool>(
        aClient,
        FB_DEVICE "/network/connected",
        wifiConnected
    );

    success &= Database.set<String>(
        aClient,
        FB_DEVICE "/network/ssid",
        WIFI_SSID
    );

    success &= Database.set<String>(
        aClient,
        FB_DEVICE "/network/ipAddress",
        WiFi.localIP().toString()
    );

    success &= Database.set<int>(
        aClient,
        FB_DEVICE "/network/wifiRSSI",
        WiFi.RSSI()
    );

    if(success)
    {
        Serial.println("[Firebase] Device status uploaded.");
    }
    else
    {
        Serial.print("[Firebase] Device upload failed: ");
        Serial.println(aClient.lastError().message());
    }
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