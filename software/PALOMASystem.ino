/*
 * PALOMASystem.ino
 *
 *  Created on: 21 de ago de 2017
 *      Author: André
 */

#include "Includes.h"
#include "ControlFunctions.h"
#include "LogFunctions.h"
#include "MenuFunctions.h"

void setup() {
	InitSystem();
}

void loop() {
  /*
	MenuStart();						// Initializate the system (Introduction).

	while (ConfirmFlag) {				// Verify confirm flag.
		MenuTemperatureSelect();		// Start the temperature selection.

		MenuTimeSelect();				// Start the time selection.	

		MenuConfirm();					// Confirm before start for actualy initializate or select the variables again.
	}
  */
	ControlSystemRun();					// Verificate and control the temperature in a loop.

	//LogOverview();						// Collect all the data and show in the display.
}

