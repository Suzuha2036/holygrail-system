#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <Arduino.h>

// =====================================================
// Initialization
// =====================================================

void initFirebase();

void firebaseLoop();

void firebaseSync();

// =====================================================
// Upload Functions
// =====================================================

// Upload current sensor readings
void uploadCurrentSensors();

// Upload ESP32 device information
void uploadDeviceStatus();

// Upload relay states
void uploadActuatorStatus();

// =====================================================
// Download Functions
// =====================================================

// Read commands from Firebase
void downloadCommands();

void applyRemoteCommands();

// Read automation settings
void downloadAutomation();

void downloadAutomationSettings();

// Read threshold values
void downloadThresholds();

// Clear all manual commands
void clearManualCommands();

// =====================================================
// Logging Functions
// =====================================================

// Save history snapshot
void pushHistory();

// Create notification
void pushNotification(
    String title,
    String message,
    String type,
    String severity
);

// Log system event
void logEvent(
    String action,
    String reason
);

// =====================================================
// Utilities
// =====================================================

// Current timestamp
String getCurrentTimestamp();

// Firebase status
bool isFirebaseConnected();

#endif