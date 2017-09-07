/*
 * control_system.c
 *
 *  Created on: 21 de ago de 2017
 *      Author: André
 */

#include "abstraction_layer.h"
#include "peripherals.h"
#include "algorithme_functions.h"

// Setup routine
void setup() {
	SensorSetup();
	DisplaySetup();
	ButtonSetup();
	ActuatorSetup();
}

// Loop routine
void loop() {

	ResetSystemVariables();

	MenuStart();									// Initializates the system (run only one time).

	MenuTemperatureSelect();						// Starts the temperature selection.

	MenuTimeSelect();								// Starts the time selection.	

	MenuConfirm();									// Confirm before start.

	ControlSystemRun();								// Run control loop.
}

