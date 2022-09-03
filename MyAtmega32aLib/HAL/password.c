																	     /****LIBRARIES****/	
																		  
#include <util/delay.h>
#include "LCD_interface.h"
#include "../MCAL/ExINT_interface.h"
#include "../MCAL/DIO_interface.h"
#include "../MCAL/ADC_interface.h"
#include "../MCAL/DIO_interface.h"
#include "../BITMATH.h"
#include "../HAL/LCD_interface.h"
#include "keypad.h"


																	/****GLOBAL VAR****/											
extern Uint8 f=0 ; 
															     
																

															/****Normal mode function****/
void normal(Uint8 temp )
{
		f=0;
															/****turn on leds****/
															
	DIO_SetPinVal(DIO_PORTC,PIN7,HIGH_PIN);
	DIO_SetPinVal(DIO_PORTC,PIN2,HIGH_PIN);
	DIO_SetPinVal(DIO_PORTD,PIN3,HIGH_PIN);
															/****LCD****/
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteSTRING("Normal") ;
	LCD_GoTo(1,0);
	LCD_WriteSTRING("temperature= ") ;
	LCD_WriteNUM(temp) ;
	_delay_ms(9000);
}

															/****Hot mode function****/

void Hot (Uint8 temp)
{
	
	
	f=0;
																/****leds****/

	DIO_SetPinVal(DIO_PORTC,PIN7,LOW_PIN);              //turn off normal mode led
	DIO_SetPinVal(DIO_PORTC,PIN2,HIGH_PIN);             //turn on hot mode led
	DIO_SetPinVal(DIO_PORTD,PIN3,LOW_PIN);              //turn off fire mode led
	
																/****buzzer for 5 sec****/

	DIO_SetPinVal(DIO_PORTA,PIN3,HIGH_PIN);				
	_delay_ms(500);                                     
	DIO_SetPinVal(DIO_PORTA,PIN3,LOW_PIN);             
													
												            	/****LCD****/
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteSTRING("Hot") ;
	LCD_GoTo(1,0);
	LCD_WriteSTRING("temperature= ") ;
	LCD_WriteNUM(temp) ;
	_delay_ms(9000);
}

																/****fire mode alarm function****/
																
void Fire_WITHBUZ (Uint8 temp)
{
																	     /****leds****/
																		
		DIO_SetPinVal(DIO_PORTC,PIN7,LOW_PIN);              //turn off normal mode led
		DIO_SetPinVal(DIO_PORTC,PIN2,LOW_PIN);             //turn off hot mode led
		DIO_SetPinVal(DIO_PORTD,PIN3,HIGH_PIN);           //turn on fire mode led

												                    	/****LCD****/

		LCD_Clear();
		LCD_GoTo(0,0);
		LCD_WriteSTRING("MODE= Fire") ;
		LCD_GoTo(1,0);
		LCD_WriteSTRING("temperature= ") ;
		LCD_WriteNUM(temp) ;
		 
		PORTC = 0x02; //Rotates Motor in Clockwise
		SET_BIT(PORTA,3); //buzzer turn on
		_delay_ms(50000);
		
		LCD_Clear();
			password();	    // calling password function
		
}
															/****turn off buzzer and normal mode function****/

void pass_succ (Uint8 temp)
{
	
																/****turn on leds****/

		DIO_SetPinVal(DIO_PORTC,PIN7,HIGH_PIN);
		DIO_SetPinVal(DIO_PORTC,PIN2,HIGH_PIN);
		DIO_SetPinVal(DIO_PORTD,PIN3,HIGH_PIN);
		
		CLEAR_BIT(PORTA,3);                            // turn off buzzer
				
															  	/****LCD****/

	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteSTRING("NORMAL ") ;
	LCD_GoTo(1,0);
	LCD_WriteSTRING("temperature= ") ;
	LCD_WriteNUM(temp) ;
	_delay_ms(4000);
	PORTC = 0x03; 	                                         //Stops Motor
	_delay_ms(9000);

	
}

/*              show buzzer mode after pass
void Fire_NOBUZ (Uint8 temp)
{
	
	
	DIO_SetPinVal(DIO_PORTD,PIN3,HIGH_PIN);
	DIO_SetPinVal(DIO_PORTC,PIN7,LOW_PIN);

	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_WriteSTRING("Fire") ;
	LCD_GoTo(1,0);
	LCD_WriteSTRING("temperature= ") ;
	CLEAR_BIT(PORTA,3);
	LCD_WriteNUM(temp) ;
	
	//Rotates Motor in Clockwise
	PORTC = 0x02; //00000010
	_delay_ms(9000);

	

	
}
*/

                                                                    /****PASSWORD FUNTION****/

void password(){
	
	KeyPad_init();

	
	Uint8 key,p1=1, p2=2, p3=3 ,p4=4;
	
	
	while (1) {
		LCD_Clear();
		LCD_GoTo(0,0);
		LCD_WriteSTRING("ENTER PASSWARD:");
		LCD_GoTo(1,0);
		/****fist case****/
		key=0;
		while(key==0){
			
			key=KeyPad_GetKey();
			_delay_ms(3000);       //delay for keypad entering
		}
		LCD_WriteCHAR('*');        //to make pass secure
		p1 = key ;
		_delay_ms(1);             //to take another char
		
		/****second case****/
		
		key=0;
		while(key==0){
			
			key=KeyPad_GetKey();
			_delay_ms(3000);          //delay for keypad entering
		}
		LCD_WriteCHAR('*');           //to make pass secure
		p2= key ;
		_delay_ms(1);                 //to take another char
		
		/****second case****/
		
		key=0;
		while(key==0){
			
			key=KeyPad_GetKey();
			_delay_ms(3000);           //delay for keypad entering
		}
		LCD_WriteCHAR('*');            //to make pass secure
		p3= key ;
		_delay_ms(1);                   //to take another char
		
		/****four case****/

		key=0;
		while(key==0){
			
			key=KeyPad_GetKey();
			_delay_ms(3000);            //delay for keypad entering
		}
		LCD_WriteCHAR('*');             //to make pass secure
		p4 = key ;
		_delay_ms(1);                  //to take another char
		
		/****Check pass****/
		
		if(p1=='1' && p2=='2' &&  p3=='3' && p4=='4'){
			f =1;                            //to enable fire function with no buzz
			
			/****LCD****/
			
			LCD_Clear();
			LCD_GoTo(1,0);
			LCD_WriteSTRING("successful pass");
			_delay_ms(3000);
			
			CLEAR_BIT(PORTA,3);                   //stop buzz
			PORTC = 0x03;                         //Stops Motor
			
			break;                                //to go out from while 1
		}
		/****Wrong pass****/
		else{
			LCD_Clear();
			LCD_GoTo(1,0);
			LCD_WriteSTRING("     Wrong pass");
			_delay_ms(6000);
			LCD_Clear();
		}
	}
}
