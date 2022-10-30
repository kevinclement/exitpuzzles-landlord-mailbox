#include "Arduino.h"
#include "logic.h"

Logic::Logic()
  : sound(*this),
    vacuum(*this)
{
}

void Logic::setup() {
  sound.setup();
  vacuum.setup();
}

void Logic::handle() {
  sound.handle();
  vacuum.handle();
}

void Logic::status() {
  char cMsg[254];
  sprintf(cMsg, 
    "status="
      "foo:%s,"

      "\r\n"
    ,
      "on"
  );

  Serial.print(cMsg);
}