#include <Arduino.h>

#include "sensor_manager.h"
#include "lcd_manager.h"
#include "relay_manager.h"
#include "buzzer_manager.h"

unsigned long lastRelayTest = 0;
int relayStep = 0;

void setup()
{
    Serial.begin(115200);

    Serial.println("==============================");
    Serial.println("Holy Grail Piggery");
    Serial.println("Integration Test");
    Serial.println("==============================");

    initSensors();
    initLCD();
    initRelays();
    initBuzzer();

    startupBeep();
}

void loop()
{
    // Read sensors
    readSensors();

    // Update LCD
    updateLCD();

    // Serial Monitor
    Serial.print("Temp: ");
    Serial.print(getTemperature());
    Serial.print(" °C   ");

    Serial.print("Hum: ");
    Serial.print(getHumidity());
    Serial.print(" %   ");

    Serial.print("Water: ");
    Serial.println(getWaterLevel());

    // Relay test every 5 seconds
    if (millis() - lastRelayTest >= 5000)
    {
        lastRelayTest = millis();

        allRelaysOff();

        switch(relayStep)
        {
            case 0:
                fan1On();
                Serial.println("Fan1 ON");
                beep();
                break;

            case 1:
                fan2On();
                Serial.println("Fan2 ON");
                beep();
                break;

            case 2:
                pumpOn();
                Serial.println("Pump ON");
                beep();
                break;

            case 3:
                solenoid1On();
                Serial.println("Solenoid1 ON");
                beep();
                break;

            case 4:
                solenoid2On();
                Serial.println("Solenoid2 ON");
                beep();
                break;
        }

        relayStep++;

        if(relayStep > 4)
            relayStep = 0;
    }

    delay(100);
}