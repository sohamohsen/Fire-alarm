#include <util/delay.h>
#include "../MCAL/DIO_interface.h"
#include "../HAL/_7SEG.h"

	
	void pass(){
		KeyPad_init();
		LCD_init();
		LCD_GoTo(0,0);
	Uint8 key,arr[3],i=0;
	while(1){
		key=KeyPad_GetKey();
		while(key==0){
			
			key=KeyPad_GetKey();
			_delay_ms(2000);
		}
		
		arr[i]=key;
		i++;
		LCD_WriteCHAR('*');
		

		if(arr[0]=='1'&&arr[1]=='2'&&arr[2]=='3'){
			LCD_GoTo(1,0);
			LCD_WriteSTRING("successful pass");
			_delay_ms(3000);
			break;
		}
		
		
		
	}
	
}
