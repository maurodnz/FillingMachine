#include "fillingMachine.h"
#include "lcdButton.h"

extern int counter;

extern int f_sec, f_dec, w_sec, w_dec;
extern unsigned long t1, dt, intervalMillis;
extern int pumpState;
extern int fillTime, waitTime;
extern int state;
extern bool first, debug;

//extern LiquidCrystal lcd;
extern LiquidCrystal_I2C lcd;

byte bottle_1[8] = {
  B00011,
  B00011,
  B00010,
  B00100,
  B01000,
  B10000,
  B10000,
  B10000
};
byte bottle_2[8] = {
  B11000,
  B11000,
  B01000,
  B00100,
  B00010,
  B00001,
  B00001,
  B00001
};
byte bottle_3[8] = {
  B10000,
  B10000,
  B10000,
  B11111,
  B11111,
  B11111,
  B01111,
  B00111
};
byte bottle_4[8] = {
  B00001,
  B00001,
  B00001,
  B11111,
  B11111,
  B11111,
  B11110,
  B11100
};

void createBottleIcon() {
  lcd.createChar(1, bottle_1);
  lcd.createChar(2, bottle_2);
  lcd.createChar(3, bottle_3);
  lcd.createChar(4, bottle_4);
}

void printIcon() {
  lcd.setCursor(0, 0);
  lcd.write(1);
  lcd.setCursor(1, 0);
  lcd.write(2);
  lcd.setCursor(0, 1);
  lcd.write(3);
  lcd.setCursor(1, 1);
  lcd.write(4);
}

void setState(int s) {
  state = s;
  first = true;

  lcd.clear();

  delay(300);
}

void printCounter(int c) {
  lcd.setCursor(3,0);
  lcd.print("Qty");

  char str[4];
  sprintf(str, "%02d", c);

  lcd.setCursor(3,1);
  lcd.print(str);
}

void printDigit(int d) {
  char str[2];
  sprintf(str, "%02d", d);

  lcd.print(str);
}

void printScreen() {
  printIcon();
  printCounter(counter);

  char f[11], w[11];
  sprintf(f, "FT:%02d.%02ds", f_sec, f_dec);
  sprintf(w, "WT:%02d.%02ds", w_sec, w_dec);

  lcd.setCursor(7, 0);
  lcd.print(f);
  lcd.setCursor(7, 1);
  lcd.print(w);
}

void mainStatus() {
  //printScreen();

  dt = millis() - t1;

  fillTime = f_sec * 1000 + f_dec * 10;
  waitTime = w_sec * 1000 + w_dec * 10;

  // Manual Mode
  if(digitalRead(MANUAL_BTN) == HIGH) {
    if(debug)
      Serial.println("Manual filling...");

    digitalWrite(PUMP, HIGH);
    digitalWrite(PUMP_LED, HIGH);
    delay(fillTime);
    digitalWrite(PUMP, LOW);
    digitalWrite(PUMP_LED, LOW);

    if(debug)
      Serial.println("Manual filling complete.");

    fillCompleteBeep();
  }

  // Reset counter
  if(digitalRead(CLEAR_BTN) == HIGH) {
    resetCounter();
    delay(100);

    if(debug) {
      Serial.println("Reset counter.");
      Serial.print("New counter value: ");
      Serial.println(counter);
    }
  }

  // Auto Mode
  if(digitalRead(AUTO_BTN) == HIGH) {
    if(debug)
      Serial.println("Auto filling...");
    
    digitalWrite(AUTO_LED, HIGH);

    if (dt >= intervalMillis) {
      t1 = millis();
      pumpState = !pumpState;
      digitalWrite(PUMP, pumpState);
      digitalWrite(PUMP_LED, pumpState);

      if(pumpState) {
        intervalMillis = fillTime;                                                                                                                                                    
        printCounter(++counter);

        if(debug) {
          Serial.println("Filling. Pump running...");
          Serial.print("pumpState: "); Serial.println(pumpState);
        }
      } else {
        intervalMillis = waitTime;

        if(debug) {
          Serial.println("Fill Completed. Waiting for next bottle...");
          Serial.print("pumpState: "); Serial.println(pumpState);
        }
      }
    }
  } else {
    //Serial.println("Auto filling off.");
    digitalWrite(PUMP, LOW);
    digitalWrite(AUTO_LED, LOW);

    fillCompleteBeep();
  }

  if(readKeys() == KEY_SELECT) {
    setState(10);
  }
}

void setFillSec() {
  if(first) {
    printScreen();
    first = false;
  }

  lcd.setCursor(9,0);
  lcd.print(">");

  lcd.setCursor(10,0);

  /*
  if(digitalRead(UP) == HIGH)
    if(f_sec < 59) {
      f_sec++;
      printDigit(f_sec);
      delay(300);
     } else {
      f_sec = 0;
      printDigit(f_sec);
      delay(300);
     }

  if(digitalRead(DOWN) == HIGH)
    if(f_sec > 0) {
      f_sec--;
      printDigit(f_sec);
      delay(300);
    } else {
      f_sec = 59;
      printDigit(f_sec);
      delay(300);
     }

  if(digitalRead(SELECT) == HIGH)
    setState(20);*/

    int key = readKeys();

    switch(key) {
      case KEY_UP:
        if(f_sec < 59) {
          f_sec++;
          printDigit(f_sec);
          delay(300);
        } else {
          f_sec = 0;
          printDigit(f_sec);
          delay(300);
        }
        break;
      case KEY_DOWN:
        if(f_sec > 0) {
          f_sec--;
          printDigit(f_sec);
          delay(300);
        } else {
          f_sec = 59;
          printDigit(f_sec);
          delay(300);
        }
        break;
      case KEY_SELECT:
        setState(20);
        break;
    }
}

void setFillDec() {
  if(first) {
    printScreen();
    first = false;
  }

  lcd.setCursor(12,0);
  lcd.print(">");

  lcd.setCursor(13,0);

  /*
  if(digitalRead(UP) == HIGH)
    if(f_dec < 90) {
      f_dec+=10;
      printDigit(f_dec);
      delay(300);
     } else {
      f_dec = 0;
      printDigit(f_dec);
      delay(300);
     }

  if(digitalRead(DOWN) == HIGH)
    if(f_dec > 0) {
      f_dec-=10;
      printDigit(f_dec);
      delay(300);
    } else {
      f_dec = 90;
      printDigit(f_dec);
      delay(300);
     }

  if(digitalRead(SELECT) == HIGH) {
    setState(30);
  }*/

  int key = readKeys();

  switch(key) {
    case KEY_UP:
      if(f_dec < 90) {
        f_dec+=10;
        printDigit(f_dec);
        delay(300);
      } else {
        f_dec = 0;
        printDigit(f_dec);
        delay(300);
      }
      break;
    case KEY_DOWN:
      if(f_dec > 0) {
        f_dec-=10;
        printDigit(f_dec);
        delay(300);
      } else {
        f_dec = 90;
        printDigit(f_dec);
        delay(300);
      }
      break;
    case KEY_SELECT:
      setState(30);
      break;
  }
}

void setWaitSec() {
  if(first) {
    printScreen();
    first = false;
  }

  lcd.setCursor(9,1);
  lcd.print(">");

  lcd.setCursor(10,1);

  /*if(digitalRead(UP) == HIGH)
    if(w_sec < 59) {
      w_sec++;
      printDigit(w_sec);
      delay(300);
     } else {
      w_sec = 0;
      printDigit(w_sec);
      delay(300);
     }

  if(digitalRead(DOWN) == HIGH)
    if(w_sec > 0) {
      w_sec--;
      printDigit(w_sec);
      delay(300);
    } else {
      w_sec = 59;
      printDigit(w_sec);
      delay(300);
     }

  if(digitalRead(SELECT) == HIGH) {
    setState(40);
  }*/

  int key = readKeys();

  switch(key) {
    case KEY_UP:
      if(w_sec < 59) {
        w_sec++;
        printDigit(w_sec);
        delay(300);
      } else {
        w_sec = 0;
        printDigit(w_sec);
        delay(300);
      }
      break;
    case KEY_DOWN:
      if(w_sec > 0) {
        w_sec--;
        printDigit(w_sec);
        delay(300);
      } else {
        w_sec = 59;
        printDigit(w_sec);
        delay(300);
      }
      break;
    case KEY_SELECT:
      setState(40);
      break;
  }
}

void setWaitDec() {
  if(first) {
    printScreen();
    first = false;
  }

  lcd.setCursor(12,1);
  lcd.print(">");

  lcd.setCursor(13,1);

  /*if(digitalRead(UP) == HIGH)
    if(w_dec < 90) {
      w_dec+=10;
      printDigit(w_dec);
      delay(300);
     } else {
      w_dec = 0;
      printDigit(w_dec);
      delay(300);
     }

  if(digitalRead(DOWN) == HIGH)
    if(w_dec > 0) {
      w_dec-=10;
      printDigit(w_dec);
      delay(300);
    } else {
      w_dec = 90;
      printDigit(w_dec);
      delay(300);
     }

  if(digitalRead(SELECT) == HIGH) {
    setState(0);
  }*/

  int key = readKeys();

  switch(key) {
    case KEY_UP:
      if(w_dec < 90) {
        w_dec+=10;
        printDigit(w_dec);
        delay(300);
      } else {
        w_dec = 0;
        printDigit(w_dec);
        delay(300);
      }
      break;
    case KEY_DOWN:
      if(w_dec > 0) {
        w_dec-=10;
        printDigit(w_dec);
        delay(300);
      } else {
        w_dec = 90;
        printDigit(w_dec);
        delay(300);
      }
      break;
    case KEY_SELECT:
      setState(0);
      break;
  }
}

void fillCompleteBeep() {
  
}

void bootToneBeep() {
  int frequency[] = {880, 880, 784, 740, 587, 740, 880, 784};
  int duration[] = {500, 375, 125, 375, 125, 375, 125, 1000};

  for (int i = 0; i < 8; i++) {
    tone(BUZZER, frequency[i], duration[i]);

    // To distinguish the notes, set a minimum time between them.
    // The note's duration + 30% seems to work well.
    int pauseBetweenNotes = duration[i] * 1.30;
    delay(pauseBetweenNotes);

    noTone(BUZZER);
  }
}

void resetCounter() {
  counter = 0;
}