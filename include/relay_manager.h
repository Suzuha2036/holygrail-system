#ifndef RELAY_MANAGER_H
#define RELAY_MANAGER_H

#include <Arduino.h>

// ===========================
// Initialization
// ===========================
void initRelays();

// ===========================
// Individual Controls
// ===========================
void fan1On();
void fan1Off();

void fan2On();
void fan2Off();

void pumpOn();
void pumpOff();

void solenoid1On();
void solenoid1Off();

void solenoid2On();
void solenoid2Off();

// ===========================
// Group Controls
// ===========================
void allRelaysOff();
void allRelaysOn();

#endif