#include <Arduino.h>
#include "Audio.h"
#include "SPIFFS.h"
#include <ESP32Servo.h>
Servo myservo;

// Digital I/O used
#define PIN_SERVO 	32
#define PIN_RELAY 	14
#define I2S_DOUT  	A1    // BROWN  => 25 A1
#define I2S_BCLK   	A10   // ORANGE => 27 A10
#define I2S_LRC    	A0    // BLUE   => 26 A0

Audio audio;

int pos 			= 0;
bool servoEnabled 	= true;
bool forward 		= true;
bool relayOn 		= false;

void setup() {
	Serial.begin(115200);
	Serial.setTimeout(10);
	Serial.println("\n\nFeather v2 by kevinc...");
	
	pinMode(PIN_RELAY, OUTPUT);

	if(!SPIFFS.begin(true)){
        Serial.println("An Error has occurred while mounting SPIFFS");
        return;
    }

	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

	myservo.attach(PIN_SERVO);

    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setBalance(-16); // mutes the left channel
    audio.setVolume(21);   // max loudness

    audio.connecttoFS(SPIFFS, "001-worms-incoming.mp3");
}

void loop() {
	audio.loop();

	if (Serial.available() > 0) {
		String str = Serial.readStringUntil('\n');	
		
		if (str == "0") {
			pos = 0;
			Serial.println("Setting to 0");
		} else if (str == "8") {
			pos = 180;
			Serial.println("Setting to 180");
		} else if (str == "2") {
			relayOn = !relayOn;
			Serial.printf("turning relay %s\n", relayOn ? "ON" : "OFF");
		} else if (str == "3") {
			Serial.printf("playing mail...\n");
			audio.connecttoFS(SPIFFS, "002-jetsons.mp3");
		} else if (str == "s") {
			pos = 15;
			Serial.println("Setting to 15 (launch)");
		} else if (str == "e") {
			pos = 115;
			Serial.println("Setting to 115 (end)");
		} else if (str == "v") {
			Serial.println("Toggling vacuum...");
			relayOn = !relayOn;
		} else if (str == "i") {
			pos += 5;
		}

		if (pos > 180) {
			Serial.println("Limiting to 180.");
			pos = 180;
		}
	}
	
	// write current pos
	myservo.write(pos);

	// write relay state
	digitalWrite(PIN_RELAY, relayOn ? HIGH : LOW);
	
	delay(15);
}