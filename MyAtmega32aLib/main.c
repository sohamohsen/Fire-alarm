																	     /****LIBRARIES****/

#define F_CPU 16000000UL
#include <util/delay.h>
#include "HAL/LCD_interface.h"
#include "MCAL/ExINT_interface.h"
#include "MCAL/DIO_interface.h"
#include "MCAL/ADC_interface.h"
#include "MCAL/DIO_interface.h"
#include "BITMATH.h"
#include "HAL/password.h"
#include "HAL/keypad.h"
																	     /****MAIN****/

int main ()
{
	extern Uint8 f;
	
	LCD_init();    // LCD initialization
	ADC_INIT();    // Calling ADC initialization function
	
	                              //extnarnal hardware initialization*/
	
	DIO_SetPinDir(PORTA,PIN3,OUTPUT_PIN); //buzzer
	DDRC = 0xFF;                         //PORTc as Output for motor
	
	                                                    /****LED initialization****/
	DIO_SetPinDir(DIO_PORTD,PIN3,OUTPUT_PIN);
	DIO_SetPinDir(DIO_PORTC,PIN7,OUTPUT_PIN);
	DIO_SetPinDir(DIO_PORTC,PIN2,OUTPUT_PIN);
	DIO_SetPinDir(DIO_PORTA,PIN3,OUTPUT_PIN);


	/**  variable decleration**/
	float volt;
	float  _temperature ;
	int temperature;
	
	while(1){
		
															/** convert volt to temperature **/
															
		volt=((ADC_Read(ADC1))*10);
		_temperature =(volt)/(1020/10);
		temperature=(Uint8)_temperature;           //casting
		
		/** temperature conditions **/
		if ( temperature < 30 ){
		normal( temperature);

		}
		else if ('70 <= temperature >= 85'&& temperature<95)
		{
			Hot( temperature);
		}

		else if (temperature >=95 && f==0){
			Fire_WITHBUZ ( temperature);
			
		}
		else if (temperature >=95 && f==1){
			pass_succ ( temperature);
			
		}
		
		/*    show fire mode after pass
		else if (temperature >=95 && flag1==1){
			Fire_NOBUZ ( temperature);
			
		}
		*/	
		
	}

}
	