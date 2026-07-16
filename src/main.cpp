#include <Arduino.h>


// =======================================
// Managers
// =======================================

#include "globals.h"
#include "config.h"

#include "sensor_manager.h"
#include "lcd_manager.h"
#include "relay_manager.h"
#include "buzzer_manager.h"
#include "automation_manager.h"

#include "wifi_manager.h"
#include "firebase_manager.h"


// =======================================
// Timers
// =======================================

unsigned long lastSensorUpdate = 0;
unsigned long lastLCDUpdate = 0;
unsigned long lastSerialUpdate = 0;


// =======================================
// Setup
// =======================================

void setup()
{

    Serial.begin(115200);

    delay(1000);


    Serial.println();
    Serial.println("==============================");
    Serial.println(" Holy Grail Piggery System ");
    Serial.println(" ESP32 Firmware v1.0.0 ");
    Serial.println("==============================");



    // -------------------------------
    // Hardware Initialization
    // -------------------------------

    initSensors();

    initLCD();

    initRelays();

    initBuzzer();



    // -------------------------------
    // System Logic
    // -------------------------------

    initAutomation();



    // -------------------------------
    // Communication
    // -------------------------------

    initWiFi();

    initFirebase();



    // -------------------------------
    // Startup Notification
    // -------------------------------

    startupBeep();


    Serial.println();
    Serial.println("SYSTEM READY");
}



// =======================================
// Main Loop
// =======================================

void loop()
{


    // ==================================
    // WiFi Monitoring
    // ==================================

    checkWiFi();



    // ==================================
    // Firebase Processing
    // ==================================

    firebaseLoop();

    firebaseSync();




    // ==================================
    // Sensor Reading
    // ==================================

    if(millis() - lastSensorUpdate >= SENSOR_INTERVAL)
    {

        lastSensorUpdate = millis();


        readSensors();

    }




    // ==================================
    // Automation Logic
    // ==================================

    runAutomation();




    // ==================================
    // LCD Update
    // ==================================

    if(millis() - lastLCDUpdate >= LCD_INTERVAL)
    {

        lastLCDUpdate = millis();


        updateLCD();

    }




    // ==================================
    // Serial Monitor
    // ==================================

    if(millis() - lastSerialUpdate >= 3000)
    {

        lastSerialUpdate = millis();


        Serial.println();
        Serial.println("==============================");
        Serial.println("SYSTEM STATUS");
        Serial.println("==============================");


        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" C");


        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");


        Serial.print("Water Level: ");
        Serial.println(waterLevel);



        Serial.println();


        Serial.print("WiFi: ");
        Serial.println(
            wifiConnected ? "CONNECTED" : "OFFLINE"
        );


        Serial.print("Firebase: ");
        Serial.println(
            firebaseConnected ? "CONNECTED" : "OFFLINE"
        );



        Serial.println();


        Serial.print("Fan 1: ");
        Serial.println(
            fan1State ? "ON" : "OFF"
        );


        Serial.print("Fan 2: ");
        Serial.println(
            fan2State ? "ON" : "OFF"
        );


        Serial.print("Pump: ");
        Serial.println(
            pumpState ? "ON" : "OFF"
        );


        Serial.print("Solenoid 1: ");
        Serial.println(
            solenoid1State ? "ON" : "OFF"
        );


        Serial.print("Solenoid 2: ");
        Serial.println(
            solenoid2State ? "ON" : "OFF"
        );


        Serial.println("==============================");

    }



    delay(10);

}