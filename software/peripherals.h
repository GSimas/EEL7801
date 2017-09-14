/*
 * peripherals.h
 *
 *  Created on: 25 de ago de 2017
 *      Author: André
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <Arduino.h>
#include <string.h>
#include <LiquidCrystal.h>
#include "hardware_abstraction.h"

// Constants Abstraction
#define DISPLAY_LINE_LENGTH		16
#define DISPLAY_NUMBER_LINES	2

#define SENSOR_CONVERTION 		(0.01 / (1.1 / 1024))		// (10 mV per celcius) / (analogic reference) / (ADC range).

#define TURN_ON				1
#define TURN_OFF			0
#define NO_CONTENT			-1							// Negative number (Display condition for no content).
#define NO_MENU				""							// Empty string (Display condition for no menu).							
#define PUSHED 				1
#define NOT_PUSHED			0

/*
 * Function: SensorSetup(void)
 * For use the temperature sensors, this setup the voltage
 * reference in 1.1V for the ADC convertion. 
 */
void SensorSetup(void);

/*
 * Function: SensorRoutine(void)
 * Process the temperature raw data from ADC to celcius.
 */
float SensorRoutine(void);

/*
 * Function: DisplaySetup(void)
 * Begin the display with 2 lines and 16 columns.
 */
void DisplaySetup(void);

/*
 * Function: DisplayTurnMode(int TurnMode)
 * Select if the display is turn on or turn off without 
 * losing the data to be printed.
 * Parameter: (TurnMode) On or Off.
 */
void DisplayTurnMode(int TurnMode);

/*
 * Function: DisplayPrint(char Header[], float Content, char Menu[])
 * Print data on the screen.
 * Parameters: (Header and Menu) Used to pass text data. 
 * 			   (Content) Pass numeric values.
 */
void DisplayPrint(char Header[], float Content, char Menu[]);

/*
 * Function: ButtonSetup(void)
 * Set button pins as digital inputs.
 */
void ButtonSetup(void);

/*
 * Function: ButtonVerification(int PushedButton)
 * Read the button or switch state .
 * Parameter: (PushedButton) Button or switch to verify.
 * Return: (ButtonVerification) Pushed or non-pushed.
 */
int ButtonVerification(int PushedButton);

/*
 * Function: ActuatorSetup(void)
 * Set the Actuator pin as digital output.
 */
void ActuatorSetup(void);

/*
 * Function: ActuatorActivation(int TurnMode)
 * This send a sign HIGH or LOW to the actuator pin for turn on or off.
 * Parameter: (TurnMode) On or off.
 */
void ActuatorActivation(int TurnMode);

#endif /* PERIPHERALS_H_ */