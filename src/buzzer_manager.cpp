#include "buzzer_manager.h"
#include "pins.h"

// =========================================
// Initialize
// =========================================
void initBuzzer()
{
    pinMode(BUZZER_PIN, OUTPUT);
    digitalWrite(BUZZER_PIN, LOW);

    Serial.println("Buzzer Initialized");
}

// =========================================
// Single Beep
// =========================================
void beep(int duration)
{
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(BUZZER_PIN, LOW);
}

// =========================================
// Startup Sound
// =========================================
void startupBeep()
{
    beep(150);
    delay(100);
    beep(150);
}

// =========================================
// Success Sound
// =========================================
void successBeep()
{
    beep(100);
    delay(50);
    beep(100);
}

// =========================================
// Warning Sound
// =========================================
void warningBeep()
{
    for(int i = 0; i < 3; i++)
    {
        beep(200);
        delay(150);
    }
}

// =========================================
// Error Sound
// =========================================
void errorBeep()
{
    for(int i = 0; i < 5; i++)
    {
        beep(100);
        delay(100);
    }
}