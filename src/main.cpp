#include <Arduino.h>
#include "logic.h"

Logic logic;

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
    	logic.reset();
	} else if (msg == "status" || msg == "s") {
  	  	logic.status();
  	} else if (msg == "0") {
		Serial.println("Setting to 0");
		logic.servo.setPosition(0);
	} else if (msg == "8") {
		Serial.println("Setting to 180");
		logic.servo.setPosition(180);
	} else if (msg == "l" || msg == "startPos") {
		Serial.println("Setting to start position...");
		logic.servo.startPosition();
	} else if (msg == "f" || msg == "endPosition") {
		Serial.println("Setting to end position...");
		logic.servo.endPosition();
	} else if (msg == "v" || msg == "vacuum") {
		Serial.println("Toggling vacuum...");
		logic.vacuum.toggle();
	} else if (msg == "t" || msg == "drop") {
		logic.trigger();
	} else if (msg == "i") {
		logic.servo.increment();
  	} else {
    	Serial.print("unknown command: ");
    	Serial.println(msg);
  	}
}

void setup() {
	Serial.begin(115200);
	Serial.setTimeout(10);
	Serial.println("READY");
	Serial.println("Mailbox by kevinc...\n");

	logic.setup();
  	logic.status();
}

void loop() {
	readAnySerialMessage();
  	logic.handle();
	delay(15);
}