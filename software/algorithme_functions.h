/*
 * algorithme_functions.h
 *
 *  Created on: 26 de ago de 2017
 *      Author: André
 */

#ifndef ALGORITHME_FUNCTIONS_H_
#define ALGORITHME_FUNCTIONS_H_

#include <Arduino.h>
#include <string.h>
#include "abstraction_layer.h"
#include "peripherals.h"

#define VIEW_TIME			0
#define VIEW_TEMPERATURE	1

#define SAFETY_TEMPERATURE	110
#define SAFETY_TIME			45

#define PERIOD				300
#define PERIODS_IN_SEC		(1000.0 / PERIOD)			// 1 second

/* Menu Functions */
void MenuStart(void);
void MenuTemperatureSelect(void);
void MenuTimeSelect(void);
void MenuConfirm(void);
void ControlSystemRun(void);

#endif /* ALGORITHME_FUNCTIONS_H_ */