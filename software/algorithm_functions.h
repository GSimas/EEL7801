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

#define VIEW_TIME					0
#define VIEW_TEMPERATURE			1

#define DEFAULT_TEMPERATURE			50
#define DEFAULT_TIME				5
#define RANGE_TEMPERATURE			1.0
#define SAFETY_TEMPERATURE			110
#define SAFETY_TIME					30
#define LOG_DATA_SIZE				(SAFETY_TIME * 6)
#define COLD_HOLDER					40

#define VALUE_CHANGED				1
#define VALUE_NOT_CHANGED			0
#define NOT_CONFIRMED				1
#define CONFIRMED					0
#define DISPLAY_MODE_NORMAL			1
#define DISPLAY_MODE_CHANGE 		0

#define LOG_TEMPERATURE_AVERAGE		0
#define LOG_TEMPERATURE_MAXIMUM		1
#define LOG_TEMPERATURE_MINIMUM		2
#define LOG_TIME_TOTAL_ACTUAL		3
#define LOG_TIME_HEATING			4
#define LOG_TIME_COOLING			5
#define LOG_INTERRUPTION_TOTAL_TIME	6	
#define LOG_INTERRUPTION_NUMBER		7
#define LOG_COLLECTED_DATA			8		

#define DELAY_PERIOD_WELCOME		2500
#define DELAY_PERIOD_SELECTION		3000
#define DELAY_PERIOD_DEBOUNCER		200
#define DELAY_PERIOD_BLINK			350
#define DELAY_PERIOD_CONTROL		1500
#define DELAY_PERIOD_LOG			3000

#define PERIOD						200
#define PERIODS_IN_SEC				(1000.0 / PERIOD)			// 1 second

#define RESET_PRESSED_TIME			(PERIODS_IN_SEC * 5.0)

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
 * Function: ControlProcessDynamicChange(void)
 * This function adds the possibility of choosing the parameters 
 * again in the middle of the process.
 */
void ControlProcessDynamicChange(void);

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

/*
 * Function: LogOverview(void)
 * This show the data colleted (log) in a menu 
 */
void LogOverview(void);

/*
 * Function: LogRefresh(void)
 * This refresh the data colleted 
 */
void LogRefresh(void);

#endif /* ALGORITHM_FUNCTIONS_H_ */