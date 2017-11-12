/*
 * Includes.cpp
 *
 *  Created on: 26 de ago de 2017
 *      Author: André
 */

#include "Includes.h"


/* Flags and user selection variables */
int ConfirmFlag = NOT_CONFIRMED;
int TemperatureSelect = DEFAULT_TEMPERATURE, TimeSelect = DEFAULT_TIME;

/* Log Variables*/
float LogAvarageTemperature = 0, LogMaximumTemperature, LogMinimumTemperature;
int LogTotalTime, LogHeatingTime = 0, LogCoolingTime = 0, LogInterruptionTime = 0, LogInterruptionNumber = 0;
//int CollectedData[LOG_DATA_SIZE];
unsigned long LogCoolingTimeStart = 0, LogInterruptTimeStart = 0, LogInterruptTimeEnd = 0;
float LogMaximumTemperatureBuffer, LogMinimumTemperatureBuffer;

/* Principal Timer Loop */
long TimeCounter = 0;

/* Reset internal system variables */
void ResetSystemVariables(void) {
	TimeCounter = 0;
	TemperatureSelect = DEFAULT_TEMPERATURE;
	TimeSelect = DEFAULT_TIME;
	ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);
	ConfirmFlag = NOT_CONFIRMED;
}

/* Switch Interrupt */
void SwitchInterrupt(void) {

	LogInterruptionNumber++;
	LogInterruptTimeStart = millis();

	while(ButtonVerification(SWITCH)) {						// Switch open.
		ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);		// Actuator Relay off for security.
		DisplayTurnMode(TURN_OFF);							// Indicate that the switch is not open.
	}

	LogInterruptTimeEnd = millis();		
	LogInterruptionTime = LogInterruptionTime + ((LogInterruptTimeEnd - LogInterruptTimeStart) / 1000);

	DisplayTurnMode(TURN_ON);
	if (SensorRoutine() < TemperatureSelect){
		ActuatorActivation(TURN_ON, ACTUATOR_RELAY);
	}
}

/* Init System (Setup functions) */
void InitSystem(void) {
	SensorSetup();
	DisplaySetup();
	ButtonSetup();
	ActuatorSetup();
	LEDDebugSetup();
}
