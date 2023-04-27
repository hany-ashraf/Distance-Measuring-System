/*
 * Application.c
 *
 *  Created on: Apr 27, 2023
 *      Author: Eng.Hany Ashraf
 */
/*--------------------------------------------------------------*/

#include"lcd.h"
#include"ultra_sensor.h"
#include"std_types.h"


int main(void)
{
	uint16 Data;
	/*initialize LCD */
	LCD_init();
	/*initialize Ultrasonic Sensor*/
	Ultrasonic_init();

	while(1)
	{
		LCD_moveCursor(0,0);

		LCD_displayString("Distance = ");

		Data = Ultrasonic_readDistance();

		if((Data >= 2) && (Data <= 400))
		{
			LCD_intgerToString(Data);

			LCD_displayString(" cm");
  		}
		else
		{
			LCD_displayStringRowColumn(1,3," Nothing ");
		}
	}
}
