#ifndef EEPROM_H
#define EEPROM_H

void initEEPROM();
void read_EEPROM();
void write_EEPROM(int fs, int fd, int ws, int wd, int addr);

void writeInt_EEPROM(int number, int address);
int readInt_EEPROM(int address);

#endif
