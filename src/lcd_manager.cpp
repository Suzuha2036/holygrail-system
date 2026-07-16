#include "lcd_manager.h"
#include "globals.h"
#include "pins.h"

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ================================
// LCD Configuration
// ================================
LiquidCrystal_I2C lcd(0x27, 16, 2);

unsigned long lastPageChange = 0;
int currentPage = 0;

// ================================
// Initialize LCD
// ================================
void initLCD()
{
    Wire.begin(LCD_SDA, LCD_SCL);

    lcd.init();
    lcd.backlight();

    showStartupScreen();
}

// ================================
// Startup Screen
// ================================
void showStartupScreen()
{
    lcd.clear();

    lcd.setCursor(0,0);
    lcd.print(" Holy Grail");

    lcd.setCursor(0,1);
    lcd.print(" Piggery");

    delay(2000);

    lcd.clear();
}

// ================================
// Update LCD
// ================================
void updateLCD()
{
    if (millis() - lastPageChange < 3000)
        return;

    lastPageChange = millis();

    lcd.clear();

    switch(currentPage)
    {

    // ===========================
    // Page 1
    // ===========================
    case 0:

        lcd.setCursor(0,0);
        lcd.print("Temp:");
        lcd.print(temperature,1);
        lcd.print((char)223);
        lcd.print("C");

        lcd.setCursor(0,1);
        lcd.print("Hum :");
        lcd.print(humidity,0);
        lcd.print("%");

        break;

    // ===========================
    // Page 2
    // ===========================
    case 1:

        lcd.setCursor(0,0);
        lcd.print("Water:");
        lcd.print(waterLevel);

        lcd.setCursor(0,1);
        lcd.print(sensorStatus);

        break;

    // ===========================
    // Page 3
    // ===========================
    case 2:

        lcd.setCursor(0,0);
        lcd.print("WiFi:");

        if(wifiConnected)
            lcd.print("ONLINE");
        else
            lcd.print("OFFLINE");

        lcd.setCursor(0,1);
        lcd.print("ESP:");
        lcd.print(deviceStatus);

        break;

    // ===========================
    // Page 4
    // ===========================
    case 3:

        lcd.setCursor(0,0);
        lcd.print("Fan1:");

        lcd.print(fan1State ? "ON " : "OFF");

        lcd.setCursor(9,0);

        lcd.print("Fan2:");

        lcd.print(fan2State ? "ON" : "OFF");

        lcd.setCursor(0,1);

        lcd.print("Pump:");

        lcd.print(pumpState ? "ON " : "OFF");

        break;

    }

    currentPage++;

    if(currentPage > 3)
        currentPage = 0;
}