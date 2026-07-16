#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <Arduino.h>

// ===========================================
// Initialization
// ===========================================

void initWiFi();

// ===========================================
// Connection Management
// ===========================================

void connectWiFi();
void disconnectWiFi();
void checkWiFi();

// ===========================================
// Status
// ===========================================

bool isWiFiConnected();

String getIPAddress();

int getRSSI();

#endif