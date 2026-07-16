#ifndef BUZZER_MANAGER_H
#define BUZZER_MANAGER_H

#include <Arduino.h>

// Initialize buzzer
void initBuzzer();

// Simple beep
void beep(int duration = 150);

// Different sound patterns
void startupBeep();
void successBeep();
void warningBeep();
void errorBeep();

#endif