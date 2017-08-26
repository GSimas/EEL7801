/*
 * control_system.c
 *
 *  Created on: 21 de ago de 2017
 *      Author: André
 */

#include "abstraction_layer.h"
#include "peripherals.h"

// Setup routine
void setup() {
	SensorSetup();
	DisplaySetup();
	ButtonSetup();
	ActuatorSetup();
	//Serial.begin(9600);
}

// Loop routine
void loop() {
	float SensorTemperature;
	SensorTemperature = SensorRoutine();

	DisplayPrint("Temperatura:", SensorTemperature);

	if (ButtonVerification(BUTTON_MORE)) {
		ActuatorActivation(TURN_ON);
	}
	if (ButtonVerification(BUTTON_LESS)) {
		ActuatorActivation(TURN_OFF);
	}

	//Serial.println(Temperature);
	delay(1000);
}