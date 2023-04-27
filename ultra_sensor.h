/*
 * ultra_sensor.h
 *
 *  Created on: Apr 27, 2023
 *      Author: Eng.Hany Ashraf
 */

#ifndef ULTRA_SENSOR_H_
#define ULTRA_SENSOR_H_

#define PORT_ID_Ultrasonic_Trigger  PORTB_ID

#define PIN_ID_Ultra_Trig  PIN5_ID
#define PIN_ID_Ultra_Echo  PIN6_ID


void Ultrasonic_edgeProcessing(void);

void Ultrasonic_init(void);

void Ultrasonic_Trigger(void);

uint16 Ultrasonic_readDistance(void);



#endif /* ULTRA_SENSOR_H_ */
