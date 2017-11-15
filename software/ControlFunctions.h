/*
 * ControlFunctions.h
 *
 *  Created on: 11 de nov de 2017
 *      Author: André
 */

#ifndef CONTROL_FUNCTIONS_H_
#define CONTROL_FUNCTIONS_H_

#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include "Peripherals.h"
#include "HardwareAbstractionLayer.h"
#include "MenuFunctions.h"
#include "includes.h"

extern int TemperatureSelect;
extern int TimeSelect;
extern int LogHeatingTime, LogCoolingTime, LogInterruptionTime, LogInterruptionNumber;
//extern int CollectedData[LOG_DATA_SIZE];
extern unsigned long LogCoolingTimeStart, LogInterruptTimeStart, LogInterruptTimeEnd;
extern float LogMaximumTemperatureBuffer, LogMinimumTemperatureBuffer;
extern long TimeCounter;

#define DELAY_PERIOD_CONTROL			30000
#define DELAY_PERIOD_CONTROL_START		1000
#define DELAY_HEATING_SLOW				100
#define DELAY_HEATING_FAST				180
#define DELAY_PERIOD_HEATING			1000
#define DELAY_PERIOD_SECURITY_TIME		30000

#define SLOW_PASTEURIZATION				60
#define FAST_PASTEURIZATION				75		

#define TEMPERATURE_START_LIMIT			108
#define CONTROL_RANGE_TEMPERATURE		8	

#define VIEW_TIME						0
#define VIEW_TEMPERATURE				1

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

#endif /* CONTROL_FUNCTIONS_H_ */
