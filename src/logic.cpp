#include "Arduino.h"
#include "logic.h"

#define START_DELAY_MS   3000
#define DROP_DELAY_MS    1100
#define SETTLE_DELAY_MS  500

const char *stateStrings[] = { "WAITING", "STARTING", "DROPPING", "SETTLING", "DONE" };

unsigned long vacuumTime = 0;
unsigned long dropTime = 0;
unsigned long settleTime = 0;

Logic::Logic()
  : vacuum(*this),
    servo(*this),
    resetButton(*this)
{
}

void Logic::setup() {
  vacuum.setup();
  servo.setup();
  resetButton.setup();

  // Move servo to start position on reset
  servo.startPosition();
}

void Logic::handle() {
  vacuum.handle();
  servo.handle();
  resetButton.handle();

  if (!handledResetPressed && resetButton.pressed) {
    Serial.println("Reset button pressed.");
    reset();
  }

  if (handledResetPressed && !resetButton.pressed) {
    handledResetPressed = false;
  }

  if (state == STARTING && millis() - vacuumTime > START_DELAY_MS) {
    Serial.println("Vacuum ran for min time.  Triggering drop...");
    state = DROPPING;
    dropTime = millis();
    status();
    servo.endPosition();
  }

  if (state == DROPPING && millis() - dropTime > DROP_DELAY_MS) {
    Serial.println("Dropped.  Turning off vacuum and settling...");
    state = SETTLING;
    settleTime = millis();
    vacuum.off();
    status();
  }

  if (state == SETTLING && millis() - settleTime > SETTLE_DELAY_MS) {
    Serial.println("Settled.  All DONE.");
    state = DONE;
    status();
  }
}

void Logic::trigger() {
		Serial.println("Triggering device...");
    state = STARTING;
    vacuum.on();
    vacuumTime = millis();
    status();
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

void Logic::reset() {
  ESP.restart();
}