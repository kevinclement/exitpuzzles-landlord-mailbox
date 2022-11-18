#include "Arduino.h"
#include "logic.h"

#define START_DELAY_MS   1000
#define DROP_DELAY_MS    3000
#define SETTLE_DELAY_MS  2000

const char *stateStrings[] = { "WAITING", "STARTING", "DROPPING", "SETTLING", "ALERTING", "DONE" };

unsigned long vacuumTime = 0;
unsigned long dropTime = 0;
unsigned long settleTime = 0;

Logic::Logic()
  : sound(*this),
    vacuum(*this),
    servo(*this),
    resetButton(*this)
{
}

void Logic::setup() {
  sound.setup();
  vacuum.setup();
  servo.setup();
  resetButton.setup();

  // Move servo to start position on reset
  servo.startPosition();
}

void Logic::handle() {
  sound.handle();
  vacuum.handle();
  servo.handle();
  resetButton.handle();

  if (!handledResetPressed && resetButton.pressed) {
    Serial.println("Reset button pressed.");
    handledResetPressed = true;
    servo.startPosition();
  }

  if (handledResetPressed && !resetButton.pressed) {
    handledResetPressed = false;
  }

  if (state == STARTING && millis() - vacuumTime > START_DELAY_MS) {
    Serial.println("Vacuum ran for min time.  Triggering drop...");
    state = DROPPING;
    dropTime = millis();
    servo.endPosition();
  }

  if (state == DROPPING && millis() - dropTime > DROP_DELAY_MS) {
    Serial.println("Dropped.  Turning off vacuum and settling...");
    state = SETTLING;
    settleTime = millis();
    vacuum.off();
  }

  if (state == SETTLING && millis() - settleTime > SETTLE_DELAY_MS) {
    Serial.println("Settled.  Playing Audio...");
    state = ALERTING;
    sound.playMail();
  }

  if (state == ALERTING && !sound.isPlaying()) {
    Serial.println("Audio finished.  All DONE.");
    state = DONE;
  }

}

void Logic::trigger() {
		Serial.println("Triggering device...");
    state = STARTING;

    vacuum.on();
    vacuumTime = millis();
}

void Logic::status() {
  char cMsg[254];
  sprintf(cMsg, 
    "status="
      "vacuum:%s,"
      "servo:%d,"
      "state:%s,"
      "resetButton:%s"

      "\r\n"
    ,
      vacuum.status(),
      servo.getPosition(),
      stateStrings[state],
      resetButton.pressed ? "on" : "off"
  );

  Serial.print(cMsg);
}