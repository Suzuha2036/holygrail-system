#include "globals.h"

//
// ===========================
// Sensor Data
// ===========================
//

float temperature = 0.0;
float humidity = 0.0;
int waterLevel = 0;

//
// ===========================
// Relay States
// ===========================
//

bool fan1State = false;
bool fan2State = false;
bool pumpState = false;
bool solenoid1State = false;
bool solenoid2State = false;

//
// ===========================
// System Status
// ===========================
//

bool wifiConnected = false;
bool firebaseConnected = false;

bool manualOverride = false;
bool maintenanceMode = false;

//
// ===========================
// Device Status
// ===========================
//

String deviceStatus = "OFFLINE";
String firmwareVersion = "1.0.0";

long uptime = 0;

//
// ===========================
// Sensor Status
// ===========================
//

String sensorStatus = "NORMAL";

//
// ===========================
// Thresholds
// (Same defaults as Firebase)
// ===========================
//

float maxTemperature = 32.0;
float minHumidity = 60.0;
int minimumWaterLevel = 20;

int wateringDuration = 30;
int fanDelay = 10;