#ifndef CONFIG_H
#define CONFIG_H

// =====================================================
// Device Information
// =====================================================

#define DEVICE_ID              "esp32_01"
#define DEVICE_NAME            "Main ESP32"
#define FIRMWARE_VERSION       "1.0.0"

// =====================================================
// WiFi Configuration
// =====================================================

#define WIFI_SSID              "SM City - Candaba Chapter IV"
#define WIFI_PASSWORD          "montano08"  

// =====================================================
// NTP Configuration
// =====================================================

#define NTP_SERVER              "pool.ntp.org"

#define GMT_OFFSET_SEC          (8 * 3600)   // Philippines UTC+8

#define DAYLIGHT_OFFSET_SEC     0

// =====================================================
// Firebase Configuration
// =====================================================
/*
// Example:
// https://holygrailpiggery-default-rtdb.asia-southeast1.firebasedatabase.app/

#define FIREBASE_HOST "holygrailpiggery-default-rtdb.firebaseio.com"

// Web API Key
#define FIREBASE_API_KEY       "AIzaSyA1hathT-KaG63LnMQMv29IHPejmk0REjA"

// =====================================================
// Firebase Root
// =====================================================

#define FIREBASE_ROOT          "/HolyGrailPiggery" */

// =====================================================
// Firebase Configuration
// =====================================================

#define FIREBASE_HOST "holygrailpiggery-default-rtdb.firebaseio.com"

#define FIREBASE_DATABASE_URL "https://holygrailpiggery-default-rtdb.firebaseio.com"

#define FIREBASE_API_KEY "AIzaSyA1hathT-KaG63LnMQMv29IHPejmk0REjA"


// =====================================================
// Firebase Root
// =====================================================

#define FIREBASE_ROOT "/HolyGrailPiggery"

// =====================================================
// Default Thresholds
// =====================================================

#define DEFAULT_MAX_TEMP           32.0
#define DEFAULT_MIN_HUMIDITY       60.0

#define DEFAULT_MIN_WATER_LEVEL    30

// =====================================================
// Cooling Configuration
// =====================================================

#define DEFAULT_WATERING_DURATION  60      // seconds

#define DEFAULT_FAN_DELAY          10      // seconds

#define DEFAULT_LOCKOUT_TIME       300     // seconds (5 minutes)

// =====================================================
// LCD Configuration
// =====================================================

#define LCD_COLUMNS    16
#define LCD_ROWS       2

// =====================================================
// Timing
// =====================================================

#define SENSOR_INTERVAL       2000
#define LCD_INTERVAL          3000
#define FIREBASE_INTERVAL     1000
#define WIFI_CHECK_INTERVAL   5000



// =====================================================
// Firebase Database Paths
// =====================================================

#define FB_ROOT                 "/HolyGrailPiggery"

// Device
#define FB_DEVICE               FB_ROOT "/devices/" DEVICE_ID

// Sensors
#define FB_SENSORS_CURRENT      FB_ROOT "/sensors/current"
#define FB_SENSORS_HEALTH       FB_ROOT "/sensors/health"

// Automation
#define FB_AUTOMATION           FB_ROOT "/automation"

// Commands
#define FB_COMMANDS             FB_ROOT "/commands"

// Actuators
#define FB_ACTUATORS            FB_ROOT "/actuators"

// Thresholds
#define FB_THRESHOLDS           FB_ROOT "/thresholds"

// System
#define FB_SYSTEM               FB_ROOT "/system"

// Notifications
#define FB_NOTIFICATIONS        FB_ROOT "/notifications"

// Events
#define FB_EVENTS               FB_ROOT "/events"

// History
#define FB_HISTORY              FB_ROOT "/history"

// Users
#define FB_USERS                FB_ROOT "/users"

#endif