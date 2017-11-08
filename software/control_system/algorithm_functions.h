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
#include "hardware_abstraction.h"
#include "peripherals.h"

#define VIEW_TIME				0
#define VIEW_TEMPERATURE		1

#define DEFAULT_TEMPERATURE		25
#define DEFAULT_TIME			5
#define RANGE_TEMPERATURE		3.0
#define SAFETY_TEMPERATURE		110
#define SAFETY_TIME				45

#define PERIOD					300
#define PERIODS_IN_SEC			(1000.0 / PERIOD)			// 1 second

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