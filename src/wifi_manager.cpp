#include "wifi_manager.h"

#include <WiFi.h>

#include "config.h"
#include "globals.h"

// ===========================================
// Internal Variables
// ===========================================

unsigned long lastReconnectAttempt = 0;

const unsigned long RECONNECT_INTERVAL = 5000;

// ===========================================
// Initialize
// ===========================================

void initWiFi()
{
    WiFi.mode(WIFI_STA);

    connectWiFi();
}

// ===========================================
// Connect
// ===========================================

void connectWiFi()
{
    Serial.println();
    Serial.println("==============================");
    Serial.println("Connecting to WiFi...");
    Serial.println(WIFI_SSID);
    Serial.println("==============================");

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    unsigned long start = millis();

    while (WiFi.status() != WL_CONNECTED &&
           millis() - start < 15000)
    {
        Serial.print(".");
        delay(500);
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        wifiConnected = true;
        deviceStatus = "ONLINE";

        Serial.println();
        Serial.println("WiFi Connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        Serial.print("RSSI: ");
        Serial.println(WiFi.RSSI());
    }
    else
    {
        wifiConnected = false;
        deviceStatus = "OFFLINE";

        Serial.println();
        Serial.println("WiFi Connection Failed");
    }
}

// ===========================================
// Disconnect
// ===========================================

void disconnectWiFi()
{
    WiFi.disconnect(true);

    wifiConnected = false;

    deviceStatus = "OFFLINE";

    Serial.println("WiFi Disconnected");
}

// ===========================================
// Auto Reconnect
// ===========================================

void checkWiFi()
{
    if (WiFi.status() == WL_CONNECTED)
    {
        wifiConnected = true;
        deviceStatus = "ONLINE";
        return;
    }

    wifiConnected = false;
    deviceStatus = "OFFLINE";

    if (millis() - lastReconnectAttempt >= RECONNECT_INTERVAL)
    {
        lastReconnectAttempt = millis();

        Serial.println("Attempting WiFi Reconnect...");

        WiFi.disconnect();

        WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    }
}

// ===========================================
// Helper Functions
// ===========================================

bool isWiFiConnected()
{
    return WiFi.status() == WL_CONNECTED;
}

String getIPAddress()
{
    if (!isWiFiConnected())
        return "0.0.0.0";

    return WiFi.localIP().toString();
}

int getRSSI()
{
    if (!isWiFiConnected())
        return 0;

    return WiFi.RSSI();
}