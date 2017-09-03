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
	
	while (!ButtonVerification(BUTTON_NEXT));		// Wait the button start.
	MenuStart();									// Initializates the system.

	MenuTemperatureSelect();						// Starts the temperature selection.
	while (ButtonVerification(BUTTON_NEXT));		// Wait the button next.

	MenuTimeSelect();								// Starts the time selection.
	while (ButtonVerification(BUTTON_NEXT));		

	MenuConfirm();									// Confirm before start.
	while (ButtonVerification(BUTTON_NEXT));

	ControlSystemRun();								// Run control loop.
}

