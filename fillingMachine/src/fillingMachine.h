#ifndef FILLINGMACHINE_H
#define FILLINGMACHINE_H

#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Pins definition
#define CLEAR_BTN     6
#define AUTO_BTN      4
#define MANUAL_BTN    7
#define PUMP          5
#define AUTO_LED      12
#define PUMP_LED      11
#define BUZZER        10

// LCD Print functions
void printCounter(int c);
void printDigit(int d);
void printIcon();

void printFillTime();
void printWaitTime();
void printScreen();

void resetCounter();

void createBottleIcon();
void bootToneBeep();
void fillCompleteBeep();

// State functions
void setState(int s);

void mainStatus();
void setFillSec();
void setFillDec();
void setWaitSec();
void setWaitDec();

#endif
