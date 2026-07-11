#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(115200);
    delay(1000);

    Serial.println();
    Serial.println("=== DHT11 Test ===");

    dht.begin();
}

void loop() {

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Failed to read from DHT11!");
    } else {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C");

        Serial.print("    Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }

    delay(2000);   // DHT11 updates about once per second; 2 seconds is safe
}