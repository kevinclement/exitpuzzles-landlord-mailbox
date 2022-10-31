#include "Arduino.h"
#include "logic.h"

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
  }

  if (handledResetPressed && !resetButton.pressed) {
    Serial.println("button up now..resetting...");
    handledResetPressed = false;
  }
}

void Logic::status() {
  char cMsg[254];
  sprintf(cMsg, 
    "status="
      "vacuum:%s,"
      "servo:%d,"
      "resetButton:%s"

      "\r\n"
    ,
      vacuum.status(),
      servo.getPosition(),
      resetButton.pressed ? "on" : "off"
  );

  Serial.print(cMsg);
}