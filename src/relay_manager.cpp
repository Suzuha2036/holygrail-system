#include "relay_manager.h"
#include "pins.h"
#include "globals.h"

// ======================================================
// Change these if your relay board is ACTIVE HIGH
// ======================================================
#define RELAY_ON LOW
#define RELAY_OFF HIGH

// ======================================================
// Initialize
// ======================================================
void initRelays()
{
    pinMode(FAN1_PIN, OUTPUT);
    pinMode(FAN2_PIN, OUTPUT);
    pinMode(PUMP_PIN, OUTPUT);
    pinMode(SOLENOID1_PIN, OUTPUT);
    pinMode(SOLENOID2_PIN, OUTPUT);

    allRelaysOff();

    Serial.println("Relays Initialized");
}

// ======================================================
// FAN 1
// ======================================================
void fan1On()
{
    digitalWrite(FAN1_PIN, RELAY_ON);
    fan1State = true;
}

void fan1Off()
{
    digitalWrite(FAN1_PIN, RELAY_OFF);
    fan1State = false;
}

// ======================================================
// FAN 2
// ======================================================
void fan2On()
{
    digitalWrite(FAN2_PIN, RELAY_ON);
    fan2State = true;
}

void fan2Off()
{
    digitalWrite(FAN2_PIN, RELAY_OFF);
    fan2State = false;
}

// ======================================================
// PUMP
// ======================================================
void pumpOn()
{
    digitalWrite(PUMP_PIN, RELAY_ON);
    pumpState = true;
}

void pumpOff()
{
    digitalWrite(PUMP_PIN, RELAY_OFF);
    pumpState = false;
}

// ======================================================
// SOLENOID 1
// ======================================================
void solenoid1On()
{
    digitalWrite(SOLENOID1_PIN, RELAY_ON);
    solenoid1State = true;
}

void solenoid1Off()
{
    digitalWrite(SOLENOID1_PIN, RELAY_OFF);
    solenoid1State = false;
}

// ======================================================
// SOLENOID 2
// ======================================================
void solenoid2On()
{
    digitalWrite(SOLENOID2_PIN, RELAY_ON);
    solenoid2State = true;
}

void solenoid2Off()
{
    digitalWrite(SOLENOID2_PIN, RELAY_OFF);
    solenoid2State = false;
}

// ======================================================
// GROUP FUNCTIONS
// ======================================================
void allRelaysOff()
{
    fan1Off();
    fan2Off();
    pumpOff();
    solenoid1Off();
    solenoid2Off();
}

void allRelaysOn()
{
    fan1On();
    fan2On();
    pumpOn();
    solenoid1On();
    solenoid2On();
}