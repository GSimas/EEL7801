/*
 * Includes.h
 *
 *  Created on: 26 de ago de 2017
 *      Author: André
 */

#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include "Peripherals.h"
#include "HardwareAbstractionLayer.h"

#define NOT_CONFIRMED				1
#define CONFIRMED					0
#define VIEW_TEMPERATURE			1
#define VIEW_TIME					0
#define VALUE_CHANGED				1
#define VALUE_NOT_CHANGED			0	

#define DEFAULT_TEMPERATURE			50
#define DEFAULT_TIME				5
#define RANGE_TEMPERATURE			1.0
#define SAFETY_TEMPERATURE			110
#define SAFETY_TIME					30

//#define LOG_DATA_SIZE				((10 * 4) + 15)	// ((SAFETY_TIME * SecondsConvertion) + CoolingTime)
#define COLD_HOLDER					40	

#define PERIOD						500
#define PERIODS_IN_SEC				(1000 / PERIOD)				// 1 second. WARNING! Use only integer numbers to avoid truncation

#define RESET_PRESSED_TIME			(PERIODS_IN_SEC * 5)
#define DATA_COLLECT_RATE			(PERIODS_IN_SEC * 15)

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
 * Function: Initsystem(void)
 * Init the system calling the setup function of the peripherals.
 */
void InitSystem(void);

#endif /* INCLUDES_H_ */
