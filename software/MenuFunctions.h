/*
 * MenuFunctions.h
 *
 *  Created on: 11 de nov de 2017
 *      Author: André
 */

#ifndef MENU_FUNCTIONS_H_
#define MENU_FUNCTIONS_H_

#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include "Peripherals.h"
#include "HardwareAbstractionLayer.h"
#include "includes.h"

#define DELAY_PERIOD_WELCOME		2500
#define DELAY_PERIOD_SELECTION		3000
#define DELAY_PERIOD_DEBOUNCER		200
#define DELAY_PERIOD_BLINK			350

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

#endif /* MENU_FUNCTIONS_H_ */
