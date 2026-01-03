#include "Arduino.h"
#include "logic.h"
#include <ESP32Servo.h>
Servo myservo;

// Digital I/O used
#define PIN_SERVO 	32

MyServo::MyServo(Logic &logic)
: _logic(logic)
{
}

void MyServo::setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	myservo.attach(PIN_SERVO);
}

void MyServo::handle() {
	myservo.write(pos);
}

void MyServo::setPosition(int newPos) { 
    pos = newPos;
}

void MyServo::startPosition() { 
    setPosition(25);
}

void MyServo::endPosition() { 
    setPosition(115);
}

int MyServo::getPosition() { 
    return pos;
}

void MyServo::increment() { 
    pos += 5;

    if (pos > 180) {
		Serial.println("Limiting to 180.");
		pos = 180;
	}
}
