#include "eeprom.h"

#include <Arduino.h>
#include <EEPROM.h>

extern int f_sec, f_dec, w_sec, w_dec;
int address;

void initEEPROM() {
  address = 0;
  EEPROM.put(address, 2);
  
  address += sizeof(int);
  EEPROM.put(address, 50);

  address += sizeof(int);
  EEPROM.put(address, 3);

  address += sizeof(int);
  EEPROM.put(address, 0);
}

void read_EEPROM() {
  address = 0;
  f_sec = EEPROM.read(address);

  address += sizeof(int);
  f_dec = EEPROM.read(address);

  address += sizeof(int);
  w_sec = EEPROM.read(address);

  address += sizeof(int);
  w_dec = EEPROM.read(address);
}

void write_EEPROM(int fs, int fd, int ws, int wd, int addr) {
  address = addr;
  EEPROM.put(address, fs);
  
  address += sizeof(int);
  EEPROM.put(address, fd);

  address += sizeof(int);
  EEPROM.put(address, ws);

  address += sizeof(int);
  EEPROM.put(address, wd);

}

void writeInt_EEPROM(int number, int address) { 
  EEPROM.write(address, number >> 8);
  EEPROM.write(address + 1, number & 0xFF);
}

int readInt_EEPROM(int address) {
  byte byte1 = EEPROM.read(address);
  byte byte2 = EEPROM.read(address + 1);

  return (byte1 << 8) + byte2;
}
