#ifndef EEPROM_H_
#define EEPROM_H_
void EEPROM_Write(unsigned short address,unsigned char data);
unsigned char EEPROM_Read(unsigned short address);

#endif