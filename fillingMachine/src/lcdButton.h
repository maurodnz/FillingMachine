#ifndef LCDBUTTON_H
#define LCDBUTTON_H

#include <Arduino.h>

#define KEY_UP      0
#define KEY_DOWN    1
#define KEY_SELECT  2

#define TH_UP     770
#define TH_DOWN   540
#define TH_SELECT 100

#define TH_RANGE 50

int readKeys() {
  int n = analogRead(A0);

  if ((n >= TH_UP - TH_RANGE) && (n <= TH_UP + TH_RANGE)) {
    return KEY_UP;
  } else if ((n >= TH_DOWN - TH_RANGE) && (n <= TH_DOWN + TH_RANGE)) {
    return KEY_DOWN;
  } else if ((n >= TH_SELECT - TH_RANGE) && (n <= TH_SELECT + TH_RANGE)) {
    return KEY_SELECT;
  } else {
    return -1;
  }
}

#endif
