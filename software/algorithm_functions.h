/*
 * algorithm_functions.h
 *
 *  Created on: 26 de ago de 2017
 *      Author: André
 */

#ifndef ALGORITHM_FUNCTIONS_H_
#define ALGORITHM_FUNCTIONS_H_

#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include "hardware_abstraction.h"
#include "peripherals.h"

extern int ConfirmFlag;

#define VIEW_TIME				0
#define VIEW_TEMPERATURE		1

#define DEFAULT_TEMPERATURE		50
#define DEFAULT_TIME			5
#define RANGE_TEMPERATURE		1.0
#define SAFETY_TEMPERATURE		110
#define SAFETY_TIME				30

#define VALUE_CHANGED			1
#define VALUE_NOT_CHANGED		0
#define NOT_CONFIRMED			1
#define CONFIRMED				0

#define DELAY_PERIOD_WELCOME	2500
#define DELAY_PERIOD_SELECTION	3000
#define DELAY_PERIOD_DEBOUNCER	200
#define DELAY_PERIOD_BLINK		350
#define DELAY_PERIOD_CONTROL	1500
#define DELAY_PERIOD_END		5000

#define PERIOD					200
#define PERIODS_IN_SEC			(1000.0 / PERIOD)			// 1 second

#define RESET_PRESSED_TIME		(PERIODS_IN_SEC * 5.0)

/*
 * Function: ResetSystemVariables(void)
 * Back variables to their default values. 
 */
void ResetSystemVariables(void);

/*
 * Function: SwitchInterrupt(void)
 * When the safety switch is pressed the system can 
 * be executed, otherwise it stops.
 */
void SwitchInterrupt(void);

/*
 * Function: MenuStart(void)
 * Initializate the system. 
 */
void MenuStart(void);

/*
 * Function: MenuTemperatureSelect(void)
 * It make the temperature selection using buttons and 
 * prints it into the display. 
 */
void MenuTemperatureSelect(void);

/*
 * Function: MenuTimeSelect(void)
 * It make the time selection using buttons and prints 
 * it into the display. 
 */
void MenuTimeSelect(void);

/*
 * Function: MenuConfirm(void)
 * Its a recursive function that confirm if the parameters 
 * are correct or remake the selection. 
 */
void MenuConfirm(void);

/*
 * Function: ControlStart(void)
 * Ensure that the temperature is right before start the
 * process and change if necessary.
 */
void ControlStart(void);

/*
 * Function: ControlDisplayView(void)
 * Print into the display relevant information for the user.
 */
void ControlDisplayView(void);

/*
 * Function: ControlProcess(void)
 * This keep the teperature at the user choice turning on or off
 * the actuator. 
 */
void ControlProcess(void);

/*
 * Function: ControlSystemRun(void)
 * Its a loop that refresh the information and do a periodic
 * control of the temperature. 
 */
void ControlSystemRun(void);

#endif /* ALGORITHM_FUNCTIONS_H_ */