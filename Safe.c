#define F_CPU 8000000UL
#include <util/delay.h>
#include "LCD.h"
#include "Keypad.h"
// define passward location
#define  EEPROM_STATUS_LOCATION 0x20
#define  EEPROM_PASSWORD_LOCATION1 0x21
#define  EEPROM_PASSWORD_LOCATION2 0x22
#define  EEPROM_PASSWORD_LOCATION3 0x23
#define  EEPROM_PASSWORD_LOCATION4 0x24
#define MAX_TRIES 2

char arr[4];

int main(void)
{
	char value=NOTPRESSED;
	char flag=0,i;
	char tries=MAX_TRIES;
	Keypad_Init();
	LCD_Init();
    while(1)
    {
		//set pass for 1st time
        if(EEPROM_Read(EEPROM_STATUS_LOCATION)==NOTPRESSED)
		{
			LCD_Sendstring("Set Pass:");
			for (i=0;i<=3;i++)
			{
				do 
				{
					value=Keypad_CheckPress(); //pass=1111
				} while (value==NOTPRESSED);
				LCD_Sendchar(value);
				_delay_ms(200);
				LCD_Movecurser(1,10+i);
				LCD_Sendchar('*'); //to make pass unseen
				_delay_ms(200);
				EEPROM_Write(EEPROM_PASSWORD_LOCATION1+i,value);
			}
			EEPROM_Write(EEPROM_STATUS_LOCATION,0x00);
		}
		// start to check pass
		while(flag==0)
		{
			arr[0]=arr[1]=arr[2]=arr[3]=NOTPRESSED;
			LCD_CLRScreen();
			LCD_Sendstring("check pass:");
			for (i=0;i<=3;i++)
			{
				do
				{
					arr[i]=Keypad_CheckPress();
				}while (arr[i]==NOTPRESSED);
				LCD_Sendchar(arr[i]);
				_delay_ms(500);
				LCD_Movecurser(1,12+i);
				LCD_Sendchar('*');
				_delay_ms(500);
			}
			if (EEPROM_Read(EEPROM_PASSWORD_LOCATION1)==arr[0] && EEPROM_Read(EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_Read(EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_Read(EEPROM_PASSWORD_LOCATION4)==arr[3])
			{
				LCD_CLRScreen();
				LCD_Sendstring("right pass");
				LCD_Movecurser(2,1);
				LCD_Sendstring("safe opened successfully");
				flag=1;
			}
			else
			{
				tries=tries-1;
				if (tries>0)
				{
					LCD_CLRScreen();
					LCD_Sendstring("wrong password");
					_delay_ms(1000);
					LCD_CLRScreen();
					LCD_Sendstring("tries left:");
					LCD_Sendchar(tries+48);
					_delay_ms(1000);
				}
				else
				{
					LCD_CLRScreen();
					LCD_Sendstring("wrong password");
					LCD_Movecurser(2,1);
					LCD_Sendstring("safe closed");
					flag=1;
				}
			}
		}						
			}		
}
		
		