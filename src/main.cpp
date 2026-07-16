#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ===========================
// DHT11
// ===========================
#define DHT_PIN 4
#define DHTTYPE DHT11

// ===========================
// Relay Pins
// ===========================
#define FAN1_PIN 18
#define FAN2_PIN 19
#define PUMP_PIN 21
#define SOLENOID1_PIN 22
#define SOLENOID2_PIN 23

// ===========================
// Active Buzzer
// ===========================
#define BUZZER_PIN 25

// ===========================
// LCD I2C
// ===========================
#define LCD_SDA 26
#define LCD_SCL 27

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(DHT_PIN, DHTTYPE);

const int relayPins[] = {
    FAN1_PIN,
    FAN2_PIN,
    PUMP_PIN,
    SOLENOID1_PIN,
    SOLENOID2_PIN
};

const char* relayNames[] = {
    "Fan 1",
    "Fan 2",
    "Pump",
    "Valve 1",
    "Valve 2"
};

// =========================================
// Buzzer
// =========================================
void beep(int duration = 150)
{
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(BUZZER_PIN, LOW);
}

// =========================================
// Relay ON
// =========================================
void relayOn(int pin)
{
    digitalWrite(pin, LOW);      // Active LOW relay
}

// =========================================
// Relay OFF
// =========================================
void relayOff(int pin)
{
    digitalWrite(pin, HIGH);
}

void setup()
{
    Serial.begin(115200);

    Wire.begin(LCD_SDA, LCD_SCL);

    lcd.init();
    lcd.backlight();

    dht.begin();

    pinMode(BUZZER_PIN, OUTPUT);

    // Initialize relays
    for(int i = 0; i < 5; i++)
    {
        pinMode(relayPins[i], OUTPUT);
        relayOff(relayPins[i]);
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Holy Grail");

    lcd.setCursor(0,1);
    lcd.print("System Boot");

    beep(300);

    delay(2000);
}

void loop()
{
    float temp = dht.readTemperature();
    float hum = dht.readHumidity();

    // ----------------------------
    // Display DHT11
    // ----------------------------
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print("T:");
    lcd.print(temp,1);
    lcd.print((char)223);
    lcd.print("C");

    lcd.setCursor(0,1);
    lcd.print("H:");
    lcd.print(hum,0);
    lcd.print("%");

    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" C    ");

    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.println(" %");

    delay(3000);

    // ----------------------------
    // Test every relay
    // ----------------------------
    for(int i = 0; i < 5; i++)
    {
        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print(relayNames[i]);

        lcd.setCursor(0,1);
        lcd.print("TURNING ON");

        Serial.print(relayNames[i]);
        Serial.println(" ON");

        beep();

        relayOn(relayPins[i]);

        delay(2000);

        relayOff(relayPins[i]);

        lcd.clear();

        lcd.setCursor(0,0);
        lcd.print(relayNames[i]);

        lcd.setCursor(0,1);
        lcd.print("TURNING OFF");

        Serial.print(relayNames[i]);
        Serial.println(" OFF");

        beep();

        delay(1000);
    }
}