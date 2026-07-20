#ifndef FIREBASE_PATHS_H
#define FIREBASE_PATHS_H

#include "config.h"

// =====================================================
// Root // it's on config.h
// =====================================================


// =====================================================
// Sensors
// =====================================================

#define FB_CURRENT_TEMPERATURE   FIREBASE_ROOT "/sensors/current/temperature"
#define FB_CURRENT_HUMIDITY      FIREBASE_ROOT "/sensors/current/humidity"
#define FB_CURRENT_WATERLEVEL    FIREBASE_ROOT "/sensors/current/waterLevel"
#define FB_CURRENT_STATUS        FIREBASE_ROOT "/sensors/current/status"
#define FB_CURRENT_UPDATED       FIREBASE_ROOT "/sensors/current/updatedAt"

#define FB_SENSOR_DHT11          FIREBASE_ROOT "/sensors/health/dht11"
#define FB_SENSOR_WATER          FIREBASE_ROOT "/sensors/health/waterSensor"

// =====================================================
// Commands
// =====================================================

#define FB_COMMAND_FAN1          FIREBASE_ROOT "/commands/fan1"
#define FB_COMMAND_FAN2          FIREBASE_ROOT "/commands/fan2"
#define FB_COMMAND_SOLENOID1     FIREBASE_ROOT "/commands/solenoid1"
#define FB_COMMAND_SOLENOID2     FIREBASE_ROOT "/commands/solenoid2"
#define FB_COMMAND_UPDATED       FIREBASE_ROOT "/commands/updatedAt"


// =====================================================
// Actuators
// =====================================================

#define FB_ACTUATOR_FAN1_STATE   FIREBASE_ROOT "/actuators/fan1/state"
#define FB_ACTUATOR_FAN1_REASON  FIREBASE_ROOT "/actuators/fan1/reason"

#define FB_ACTUATOR_FAN2_STATE   FIREBASE_ROOT "/actuators/fan2/state"
#define FB_ACTUATOR_FAN2_REASON  FIREBASE_ROOT "/actuators/fan2/reason"

#define FB_ACTUATOR_PUMP_STATE   FIREBASE_ROOT "/actuators/pump/state"
#define FB_ACTUATOR_PUMP_REASON  FIREBASE_ROOT "/actuators/pump/reason"

#define FB_ACTUATOR_SOL1_STATE   FIREBASE_ROOT "/actuators/solenoid1/state"
#define FB_ACTUATOR_SOL1_REASON  FIREBASE_ROOT "/actuators/solenoid1/reason"

#define FB_ACTUATOR_SOL2_STATE   FIREBASE_ROOT "/actuators/solenoid2/state"
#define FB_ACTUATOR_SOL2_REASON  FIREBASE_ROOT "/actuators/solenoid2/reason"

// =====================================================
// Device
// =====================================================

#define FB_DEVICE_NAME           FIREBASE_ROOT "/devices/" DEVICE_ID "/name"
#define FB_DEVICE_STATUS         FIREBASE_ROOT "/devices/" DEVICE_ID "/status"
#define FB_DEVICE_FIRMWARE       FIREBASE_ROOT "/devices/" DEVICE_ID "/firmware"
#define FB_DEVICE_LASTSEEN       FIREBASE_ROOT "/devices/" DEVICE_ID "/lastSeen"

#define FB_DEVICE_CONNECTED      FIREBASE_ROOT "/devices/" DEVICE_ID "/network/connected"
#define FB_DEVICE_SSID           FIREBASE_ROOT "/devices/" DEVICE_ID "/network/ssid"
#define FB_DEVICE_IP             FIREBASE_ROOT "/devices/" DEVICE_ID "/network/ipAddress"
#define FB_DEVICE_RSSI           FIREBASE_ROOT "/devices/" DEVICE_ID "/network/wifiRSSI"

// =====================================================
// Automation
// =====================================================

#define FB_AUTOMATION_ENABLED    FIREBASE_ROOT "/automation/enabled"
#define FB_AUTOMATION_MODE       FIREBASE_ROOT "/automation/mode"

// =====================================================
// Thresholds
// =====================================================

#define FB_THRESHOLD_MAXTEMP     FIREBASE_ROOT "/thresholds/maxTemperature"
#define FB_THRESHOLD_MINHUM      FIREBASE_ROOT "/thresholds/minHumidity"
#define FB_THRESHOLD_MINWATER    FIREBASE_ROOT "/thresholds/minimumWaterLevel"
#define FB_THRESHOLD_FANDELAY    FIREBASE_ROOT "/thresholds/fanDelay"
#define FB_THRESHOLD_WATERING    FIREBASE_ROOT "/thresholds/wateringDuration"
#define FB_THRESHOLD_LOCKOUT     FIREBASE_ROOT "/thresholds/coolingLockoutDuration"

// =====================================================
// System
// =====================================================

#define FB_SYSTEM_UPTIME         FIREBASE_ROOT "/system/uptime"
#define FB_SYSTEM_VERSION        FIREBASE_ROOT "/system/version"
#define FB_SYSTEM_RESTART        FIREBASE_ROOT "/system/lastRestart"
#define FB_SYSTEM_MANUAL         FIREBASE_ROOT "/system/manualOverride"
#define FB_SYSTEM_MAINTENANCE    FIREBASE_ROOT "/system/maintenanceMode"


// =====================================================
// Events
// =====================================================

#define FB_EVENTS FIREBASE_ROOT "/events"


// =====================================================
// Notifications
// =====================================================

#define FB_NOTIFICATIONS FIREBASE_ROOT "/notifications"


// =====================================================
// History
// =====================================================

#define FB_HISTORY FIREBASE_ROOT "/history"


#endif