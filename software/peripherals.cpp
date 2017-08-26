/*
 * peripherals.cpp
 *
 *  Created on: 25 de ago de 2017
 *      Author: André
 */

#include "peripherals.h"

/* Sensor Functions */

void SensorSetup(void) {
	analogReference(INTERNAL);							// Use 1.1V as analogic reference for the maximum precision of the sensor.
}

float SensorRoutine(void) {
	int SensorRead;
	float TemperatureC;

	SensorRead = analogRead(SENSOR_PIN);				// Reads the sensor analogic value.
	TemperatureC = SensorRead / SENSOR_CONVERTION;		// Converts the raw temperature to celcius.
	
	return TemperatureC;
}

/* Display Functions */

// Setup the display comunication pins.
LiquidCrystal DisplayLCD (DISPLAY_RS, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

void DisplaySetup(void) {
	DisplayLCD.begin(16, 2);							// The display size, 2 lines and 16 columns.
}

void DisplayPrint(char Header[], float Content) {	
	int TextTab; 

	TextTab  = (16 - strlen(Header)) / 2;				// Calculates necessary tab to center the text.

	DisplayLCD.setCursor(TextTab, 0);					// Selects the First display line and gives a tab to the content.
	DisplayLCD.print(Header);							// Prints the header.
	
	DisplayLCD.setCursor(TextTab, 1);					// Second line.
	DisplayLCD.print(Content);							// Print the content information.
}

/* Button Functions */

void ButtonSetup(void) {
	pinMode(BUTTON_MORE, INPUT);
	pinMode(BUTTON_LESS, INPUT);
}

int ButtonVerification(int PushedButton) {
	int ButtonState, ButtonVerification;

	ButtonState = digitalRead(PushedButton);

	if (ButtonState == HIGH){ 
		ButtonVerification = 1;		
	}
	else { 
		ButtonVerification = 0;
	}

	return ButtonVerification;
}

/* Actuator Functions */

void ActuatorSetup(void) {
	pinMode(ACTUATOR, OUTPUT);
}

void ActuatorActivation(int TurnMode) {
	if (TurnMode) {
		digitalWrite(ACTUATOR, HIGH);	
	}
	else {
		digitalWrite(ACTUATOR, LOW);		
	}
}