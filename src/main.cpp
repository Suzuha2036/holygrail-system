#include <Arduino.h>

#include "sensor_manager.h"

void setup()
{
    Serial.begin(115200);

    initSensors();
}

void loop()
{
    readSensors();

    Serial.print("Temperature : ");
    Serial.print(getTemperature());

    Serial.print(" °C");

    Serial.print("   Humidity : ");

    Serial.print(getHumidity());

    Serial.print(" %");

    Serial.print("   Water : ");

    Serial.print(getWaterLevel());

    Serial.print("   Status : ");

    Serial.println(isDHTConnected() ? "OK" : "ERROR");

    delay(2000);
}