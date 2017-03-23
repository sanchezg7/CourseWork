#ifndef __irDist_h
#define __irDist_h
#include <Wire.h>
#include <utility/Adafruit_MCP23017.h>
#include <Arduino.h>

int computeDistance_SIR(int value);
int longComputeDist(int LValueF);
int trueDist(int sensor, int loops);
bool isAWall(int shrtF);

#endif