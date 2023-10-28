#include <avr/io.h>
#include "Std_Macros.h"

void EEPROM_Write(unsigned short address,unsigned char data)
{
	//set up EEPROM address
	EEARL=(char)address;
	EEARH=(char)(address>>8);  //address is 10 bit
	//set up data register
	EEDR=data;
	//enable write operation
	SET_BIT(EECR,EEMWE);
	SET_BIT(EECR,EEWE);
	//wait until write operation is complete
	while(READ_BIT(EECR,EEWE)==1);
}

unsigned char EEPROM_Read(unsigned short address)
{
	//set up EEPROM address
	EEARL=(char)address;
	EEARH=(char)(address>>8);  //address is 10 bit
	//enable read operation
	SET_BIT(EECR,EERE);
	return EEDR;
}