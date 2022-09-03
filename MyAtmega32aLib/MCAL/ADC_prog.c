/*
 * ADC.c
 *
 * Created: 5/27/2022 2:58:30 PM
 */ 

#include "ADC_interface.h"


void ADC_INIT(){	
	
#if VOLTAGE_REFERENCE == AREF      //0v
CLEAR_BIT(ADMUX,REFS0);
CLEAR_BIT(ADMUX,REFS1);
#elif  VOLTAGE_REFERENCE == AVCC    //5v
 SET_BIT(ADMUX,REFS0);
 CLEAR_BIT(ADMUX,REFS1);
#elif  VOLTAGE_REFERENCE == Internal_2_56V
  SET_BIT(ADMUX,REFS0);
  SET_BIT(ADMUX,REFS1);
#endif  

  
 
  	/*Right ADJUST*/
  	CLEAR_BIT(ADMUX, ADLAR);
  	/*128 Pres caller*/
  SET_BIT(ADCSRA,ADPS0);
  SET_BIT(ADCSRA,ADPS1);
  SET_BIT(ADCSRA,ADPS2);
	/*Conversion Mode: AutoTrigger/FreeRunning*/
  	SET_BIT(ADCSRA, ADATE);
  	SFIOR = (AUTO_TRIGGER_MODE << 5)| (SFIOR & 0x0F);
  	/*ADC peripheral Enable*/
  	SET_BIT(ADCSRA,ADEN);
   
   
}


Uint16 ADC_Read(Uint8 ADC_CHANNEL)
{
	/*Channel select*/ 
	CLEAR_BIT(DDRA,ADC_CHANNEL);
	
	ADMUX = ADC_CHANNEL | (ADMUX & 0xE0);  
	/*Start of conversion*/					
	SET_BIT(ADCSRA, ADSC);							
	/*End of conversion Polling*/
	while(IS_LOW(ADCSRA, ADIF));
	/*Converted digital output*/
	return ADC_REG;
}