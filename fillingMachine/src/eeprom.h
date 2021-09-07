#ifndef EEPROM_H
#define EEPROM_H

void read_EEPROM();
void write_EEPROM(int value, int address);

void writeInt_EEPROM(int number, int address);
int readInt_EEPROM(int address);

#endif
