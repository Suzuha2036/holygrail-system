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

bool automationEnabled = true;
String automationMode = "AUTO";

//
// ===========================
// Device Status
// ===========================
//

String deviceStatus = "OFFLINE";
String firmwareVersion = "1.0.0";

unsigned long uptime = 0;

//
// ===========================
// Sensor Status
// ===========================
//

String sensorStatus = "NORMAL";

//
// ===========================
// Thresholds
// (Default values)
// ===========================
//

float maxTemperature = 32.0;
float minHumidity = 60.0;

int minimumWaterLevel = 30;

int wateringDuration = 60;
int fanDelay = 10;

//
// ===========================
// Cooling System
// ===========================
//

bool coolingActive = false;
bool coolingLockout = false;

unsigned long coolingStartedAt = 0;
unsigned long coolingLockoutUntil = 0;

//
// ===========================
// Scheduler
// ===========================
//

bool scheduleRunning = false;

String currentSchedule = "";

//
// ===========================
// Current Process
// ===========================
//

String currentProcess = "IDLE";