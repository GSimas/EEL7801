/*
 * hardware_abstraction.h
 *
 *  Created on: 21 de ago de 2017
 *      Author: André
 */

#ifndef HARDWARE_ABSTRACTION_H_
#define HARDWARE_ABSTRACTION_LAYER_H_

/* Pins abstraction */

// Use 2 temperature sensors to get more accuracy values.
#define SENSOR_PIN_1		0
#define SENSOR_PIN_2		1

// Interface display pins.
#define DISPLAY_RST			12
#define DISPLAY_EN			11
#define DISPLAY_D4			5
#define DISPLAY_D5			4
#define DISPLAY_D6			3
#define DISPLAY_D7			2

// Buttons for user interation.
#define BUTTON_PLUS			7
#define BUTTON_MINUS		6
#define BUTTON_NEXT			9

// Switch for safety purposes (turn off the system when the equipment is open). 
#define SWITCH				10

// Actuator control pin
#define ACTUATOR			8

#endif /* HARDWARE_ABSTRACTION_LAYER_H_ */