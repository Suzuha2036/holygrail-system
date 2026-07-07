#include <Arduino.h>

const int RELAY = 2;   // IN1 connected to GPIO2

void setup() {
    pinMode(RELAY, OUTPUT);

    // Most 5V relay modules are active LOW
    digitalWrite(RELAY, HIGH);   // Relay OFF initially
}

void loop() {
    digitalWrite(RELAY, LOW);    // Relay ON
    delay(2000);

    digitalWrite(RELAY, HIGH);   // Relay OFF
    delay(9000);
}