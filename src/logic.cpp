#include "Arduino.h"
#include "logic.h"

Logic::Logic()
  : sound(*this),
    vacuum(*this),
    servo(*this)
{
}

void Logic::setup() {
  sound.setup();
  vacuum.setup();
  servo.setup();

  // Move servo to start position on reset
  servo.startPosition();
}

void Logic::handle() {
  sound.handle();
  vacuum.handle();
  servo.handle();
}

void Logic::status() {
  char cMsg[254];
  sprintf(cMsg, 
    "status="
      "vacuum:%s,"
      "servo:%d"

      "\r\n"
    ,
      vacuum.status(),
      servo.getPosition()
  );

  Serial.print(cMsg);
}