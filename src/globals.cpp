#include "globals.h"

// ===========================
// Sensor Values
// ===========================
float temperature = 0.0;
float humidity = 0.0;
int waterLevel = 0;

// ===========================
// Actuator States
// ===========================
bool fan1State = false;
bool fan2State = false;
bool pumpState = false;
bool solenoid1State = false;
bool solenoid2State = false;

// ===========================
// System States
// ===========================
bool manualOverride = false;
bool maintenanceMode = false;

// ===========================
// Connectivity
// ===========================
bool wifiConnected = false;
bool firebaseConnected = false;