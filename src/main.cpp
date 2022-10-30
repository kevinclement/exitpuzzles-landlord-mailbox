#include <Arduino.h>
#include "logic.h"

#include <ESP32Servo.h>
Servo myservo;

Logic logic;
void(* resetFunc) (void) = 0;

// Digital I/O used
#define PIN_SERVO 	32

int pos 			= 0;
bool servoEnabled 	= true;
bool forward 		= true;

void readAnySerialMessage() {
	if (!Serial.available()) {
    	return;
  	}

	// read and handle message from serial
	String msg = Serial.readStringUntil('\n');
	Serial.print("got '");
	Serial.print(msg);
	Serial.println("' command");

	if (msg == "reset" || msg == "reboot" || msg == "r") {
    	resetFunc();
  	} else if (msg == "0") {
		pos = 0;
		Serial.println("Setting to 0");
	} else if (msg == "8") {
		pos = 180;
		Serial.println("Setting to 180");
	} else if (msg == "3") {
		Serial.printf("playing mail...\n");
		logic.sound.playMail();
	} else if (msg == "4") {
		Serial.printf("playing worms...\n");
		logic.sound.playWorms();
	} else if (msg == "5") {
		Serial.printf("playing jetsons...\n");
		logic.sound.playJetsons();
	} else if (msg == "s") {
		pos = 15;
		Serial.println("Setting to 15 (launch)");
	} else if (msg == "e") {
		pos = 115;
		Serial.println("Setting to 115 (end)");
	} else if (msg == "v") {
		Serial.println("Toggling vacuum...");
		logic.vacuum.toggle();
	} else if (msg == "i") {
		pos += 5;
  	} else {
    	Serial.print("unknown command: ");
    	Serial.println(msg);
  	}

	if (pos > 180) {
		Serial.println("Limiting to 180.");
		pos = 180;
	}
}

void setup() {
	Serial.begin(115200);
	Serial.setTimeout(10);
	Serial.println("READY");
	Serial.println("Mailbox by kevinc...\n");

	logic.setup();
  	logic.status();

	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	myservo.attach(PIN_SERVO);
}

void loop() {
	readAnySerialMessage();
  	logic.handle();
	
	// write current pos
	myservo.write(pos);
	
	delay(15);
}