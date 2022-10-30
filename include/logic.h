#pragma once

#include "Arduino.h"
#include "sound.h"
#include "vacuum.h"

class Logic {
public:
  Logic();
  Sound sound;
  Vacuum vacuum;
  
  void setup();
  void handle();
  void status();
  
private:
};

