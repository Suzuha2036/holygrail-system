#ifndef LCD_MANAGER_H
#define LCD_MANAGER_H

#include <Arduino.h>

// Initialize LCD
void initLCD();

// Update LCD pages
void updateLCD();

// Force a startup screen
void showStartupScreen();

#endif