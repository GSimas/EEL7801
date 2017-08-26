/*
 * peripherals.h
 *
 *  Created on: 25 de ago de 2017
 *      Author: André
 */

#ifndef PERIPHERALS_H_
#define PERIPHERALS_H_

#include <Arduino.h>
#include <string.h>
#include <LiquidCrystal.h>
#include "abstraction_layer.h"

// Constants Abstraction
#define SENSOR_CONVERTION 	(0.01 / (1.1 / 1024))		// (10 millivolts per celcius) / (analogic reference) / (ADC convertion range).
#define TURN_ON		1
#define TURN_OFF	0

void SensorSetup(void);
float SensorRoutine(void);

void DisplaySetup(void);
void DisplayPrint(char Header[], float Content);

void ButtonSetup(void);
int ButtonVerification(int PushedButton);

void ActuatorSetup(void);
void ActuatorActivation(int TurnMode);

#endif /* PERIPHERALS_H_ */