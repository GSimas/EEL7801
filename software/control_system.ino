/*
 * control_system.c
 *
 *  Created on: 21 de ago de 2017
 *      Author: André
 */

#include "hardware_abstraction.h"
#include "peripherals.h"
#include "algorithm_functions.h"

int ConfirmFlag = NOT_CONFIRMED;

void setup() {
	SensorSetup();
	DisplaySetup();
	ButtonSetup();
	ActuatorSetup();
	LEDDebugSetup();
}

void loop() {

	MenuStart();						// Initializate the system (Introduction).

	while (ConfirmFlag) {				// Verify confirm flag.
		MenuTemperatureSelect();		// Start the temperature selection.

		MenuTimeSelect();				// Start the time selection.	

		MenuConfirm();					// Confirm before start for actualy initializate or select the variables again.
	}
	ControlSystemRun();					// Verificate and control the temperature in a loop.
}

