#pragma once

#include "Arduino.h"
#include "sound.h"
#include "vacuum.h"
#include "servo.h"

class Logic {
public:
  Logic();
  Sound sound;
  Vacuum vacuum;
  MyServo servo;
  
  void setup();
  void handle();
  void status();
  
private:
};

