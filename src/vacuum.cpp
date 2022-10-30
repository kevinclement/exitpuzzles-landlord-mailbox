#include "Arduino.h"
#include "logic.h"

#define PIN_RELAY 14

Vacuum::Vacuum(Logic &logic)
: _logic(logic)
{
}

void Vacuum::setup() {
    pinMode(PIN_RELAY, OUTPUT);    
}

void Vacuum::handle() {
	digitalWrite(PIN_RELAY, relayOn ? HIGH : LOW);
}

void Vacuum::toggle() {
    relayOn = !relayOn;
}

void Vacuum::on() {
    relayOn = true;
}

void Vacuum::off() {
    relayOn = false;
}

