/*
 * ultra_sensor.c
 *
 *  Created on: Apr 27, 2023
 *      Author: Eng.Hany Ashraf
 */


#include"icu.h"
#include"ultra_sensor.h"
#include"std_types.h"
#include"gpio.h"
#include<util/delay.h>

/*******************************Ultrasonic Driver****************************/
/*Global Variable*/
static volatile uint8 flag = 0;
/**********************************ISR**************************************/
void Ultrasonic_edgeProcessing(void)
{
	flag++;

	if(flag == 1)
	{
		/*When the ICU detect a Rising Edge it will clear the ICR1 Register*/
		Icu_clearTimerValue();
		/*Setup the edge detection type to be with Falling*/
		Icu_setEdgeDetectionType(FALLING);
	}

	else if(flag == 2)
	{
		/*Setup the edge detection type to be with RISING*/
		Icu_setEdgeDetectionType(RISING);
		/*Reset the Flag*/
		flag = 0;
	}
}

/**********************************Ultrasonic_init******************************/
/*Initialization Function*/
void Ultrasonic_init(void)
{
	/*Structure for configuration */
	Icu_ConfigType config_type = {F_CPU_8, RISING};
	/*Make the pin of tigger as output pin*/
	GPIO_setupPinDirection(PORT_ID_Ultrasonic_Trigger, PIN5_ID, PIN_OUTPUT);
	/*initialize the Input Capture Unit*/
	Icu_init(&config_type);
	/*Call Back Function*/
	Icu_setCallBack(Ultrasonic_edgeProcessing);
}
/***************************************Ultrasonic_Trigger**************************/
/*Trigger Function Of Ultra_sensor to sense the distance*/
void Ultrasonic_Trigger(void)
{
	/*Makes the Tigger Pin of sensor a High */
	GPIO_writePin(PORT_ID_Ultrasonic_Trigger, PIN5_ID, LOGIC_HIGH);
	/*makes delay 10 mili_second*/
	_delay_ms(10);
	/*Makes the Tigger Pin of sensor a LOW*/
 	GPIO_writePin(PORT_ID_Ultrasonic_Trigger, PIN5_ID, LOGIC_LOW);

}

/*------------------------------------Ultrasonic_readDistance--------------------*/

/*A Function that calculate the distance and return it to Display Function */
uint16 Ultrasonic_readDistance(void)
{
	/*call a function to trigger pin Trig. at Ultrasonic sensor */
	Ultrasonic_Trigger();
	/*Auto variable to reserve the Distance */
	uint16 distance;

	if(flag == 2)
	{
		distance = ((Icu_getInputCaptureValue()-1)*(float32)(0.017));
	}
	/*When the ICU detect a Falling Edge it will clear the ICR1 Register*/
	Icu_clearTimerValue();

	/*return the distance to Display at LCD*/
	return distance;
}
