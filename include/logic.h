#pragma once

#include "Arduino.h"
#include "sound.h"
#include "vacuum.h"
#include "servo.h"
#include "resetButton.h"

class Logic {
public:
  Logic();
  Sound sound;
  Vacuum vacuum;
  MyServo servo;
  ResetButton resetButton;
  
  void setup();
  void handle();
  void status();
  
private:
  bool handledResetPressed = false;
};

