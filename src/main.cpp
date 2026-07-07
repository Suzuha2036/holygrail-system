#include <Arduino.h>

// Built-in LED is usually GPIO2 on most ESP32 DevKit boards
const int LED_PIN = 2;

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(LED_PIN, HIGH); // LED ON
    delay(500);

    digitalWrite(LED_PIN, LOW);  // LED OFF
    delay(2000);
}