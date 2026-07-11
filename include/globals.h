#ifndef GLOBALS_H
#define GLOBALS_H

// ===========================
// Sensor Values
// ===========================
extern float temperature;
extern float humidity;
extern int waterLevel;

// ===========================
// Actuator States
// ===========================
extern bool fan1State;
extern bool fan2State;
extern bool pumpState;
extern bool solenoid1State;
extern bool solenoid2State;

// ===========================
// System States
// ===========================
extern bool manualOverride;
extern bool maintenanceMode;

// ===========================
// Connectivity
// ===========================
extern bool wifiConnected;
extern bool firebaseConnected;

#endif