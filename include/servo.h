#pragma once
#include "Arduino.h"

class Logic;

class MyServo {
  public:
    MyServo(Logic &logic);
    void setup();
    void handle();
    void setPosition(int pos);
    int getPosition();
    void startPosition();
    void endPosition();
    void increment();

  private:
    Logic &_logic;
    int pos = 0;
};