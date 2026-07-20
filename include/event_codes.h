#ifndef EVENT_CODES_H
#define EVENT_CODES_H

// =====================================================
// System
// =====================================================

#define EVENT_STARTUP                 "STARTUP"
#define EVENT_SHUTDOWN                "SHUTDOWN"

// =====================================================
// WiFi
// =====================================================

#define EVENT_WIFI_CONNECTED          "WIFI_CONNECTED"
#define EVENT_WIFI_DISCONNECTED       "WIFI_DISCONNECTED"

// =====================================================
// Firebase
// =====================================================

#define EVENT_FIREBASE_CONNECTED      "FIREBASE_CONNECTED"
#define EVENT_FIREBASE_DISCONNECTED   "FIREBASE_DISCONNECTED"

// =====================================================
// Automation
// =====================================================

#define EVENT_COOLING_STARTED         "COOLING_STARTED"
#define EVENT_COOLING_FINISHED        "COOLING_FINISHED"

#define EVENT_LOW_WATER              "LOW_WATER_TRIGGERED"

#define EVENT_MANUAL_ENABLED         "MANUAL_MODE_ENABLED"
#define EVENT_MANUAL_DISABLED        "MANUAL_MODE_DISABLED"

#define EVENT_MAINTENANCE_ENABLED    "MAINTENANCE_ENABLED"
#define EVENT_MAINTENANCE_DISABLED   "MAINTENANCE_DISABLED"

// =====================================================
// Relays
// =====================================================

#define EVENT_FAN1_ON                "FAN1_ON"
#define EVENT_FAN1_OFF               "FAN1_OFF"

#define EVENT_FAN2_ON                "FAN2_ON"
#define EVENT_FAN2_OFF               "FAN2_OFF"

#define EVENT_PUMP_ON                "PUMP_ON"
#define EVENT_PUMP_OFF               "PUMP_OFF"

#define EVENT_SOLENOID1_ON           "SOLENOID1_ON"
#define EVENT_SOLENOID1_OFF          "SOLENOID1_OFF"

#define EVENT_SOLENOID2_ON           "SOLENOID2_ON"
#define EVENT_SOLENOID2_OFF          "SOLENOID2_OFF"

#endif