#ifndef FIREBASE_MANAGER_H
#define FIREBASE_MANAGER_H

#include <Arduino.h>

// =====================================================
// Initialization
// =====================================================

void initFirebase();

void firebaseLoop();

void firebaseSync();

void initializeThresholds();

// =====================================================
// Upload Functions
// =====================================================

// Upload current sensor readings
void uploadCurrentSensors();

// Upload ESP32 device information
void uploadDeviceStatus();

// Upload actuator states
void uploadActuatorStatus();

// =====================================================
// Download Functions
// =====================================================

// Download manual commands
void downloadCommands();

// Download automation settings
void downloadAutomationSettings();

// Download thresholds
void downloadThresholds();

// =====================================================
// Manual Command Functions
// =====================================================

// Apply manual relay commands
void applyRemoteCommands();

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