#include "Arduino.h"
#include "logic.h"

#define PIN_BUTTON A4
#define BOUNCE_TIME_MS 10

unsigned long pressedTime = 0;
ResetButton::ResetButton(Logic &logic)
: _logic(logic)
{
}

void ResetButton::setup() {
    pinMode(PIN_BUTTON, INPUT);
}

void ResetButton::handle() {
    int btnState = digitalRead(PIN_BUTTON);

    if (!btnState) {
        pressedTime = 0;
        pressed = false;
    }
    else {
        if (pressedTime == 0) {
            pressedTime = millis();
        }
        else if (millis() - pressedTime > BOUNCE_TIME_MS) {
            pressed = true;
        }
    }
}