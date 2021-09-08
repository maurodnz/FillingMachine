#include "fillingMachine.h"

LiquidCrystal_I2C lcd(0x27,16,2);

int f_sec = 1, f_dec = 0;
int w_sec = 3, w_dec = 0;

unsigned long t1, dt, intervalMillis;
int pumpState;
int fillTime, waitTime;
int state;
int counter;
bool first;
bool debug = true;

void setup() {
  // Pin Mode Configuration
  pinMode(CLEAR_BTN, INPUT);
  pinMode(AUTO_BTN, INPUT);
  pinMode(MANUAL_BTN, INPUT);

  pinMode(PUMP, OUTPUT);
  pinMode(PUMP_LED, OUTPUT);
  pinMode(AUTO_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);


  // Initial configuration
  counter = 0;
  state = 0;
  first = true;

  read_EEPROM();

  pumpState = LOW;
  intervalMillis = f_sec * 1000 + f_dec * 10;

  digitalWrite(PUMP, pumpState);

  initLCD();
  bootToneBeep();

  if(debug) {
    Serial.begin(9600);
    Serial.print("Fill time: ");
    Serial.println(intervalMillis);
    Serial.println("System ready");
    Serial.println("-----------------------");
  }
}

void loop() {
  switch(state) {
    case 0:
      mainStatus();
      break;
    case 10:
      setFillSec();
      break;
    case 20:
      setFillDec();
      break;
    case 30:
      setWaitSec();
      break;
    case 40:
      setWaitDec();
      break;
  }
}
