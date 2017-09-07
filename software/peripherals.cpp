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
	int SensorRead_1, SensorRead_2;
	float TemperatureC;

	SensorRead_1 = analogRead(SENSOR_PIN_1);			// Reads the sensor analogic value.
	SensorRead_2 = analogRead(SENSOR_PIN_2);			// Reads the sensor analogic value.
	TemperatureC = (SensorRead_1 + SensorRead_2) / (SENSOR_CONVERTION * 2);		// Converts the raw temperature to celcius.
	
	return TemperatureC;
}

/* Display Functions */

// Setup the display comunication pins.
LiquidCrystal DisplayLCD (DISPLAY_RS, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

void DisplaySetup(void) {
	DisplayLCD.begin(16, 2);							// The display size, 2 lines and 16 columns.
}

void DisplayTurnMode(int TurnMode) {
	switch(TurnMode) {
		case TURN_ON:
			DisplayLCD.display();
			break;
		case TURN_OFF:
			DisplayLCD.noDisplay();
			break;
	}
}

void DisplayPrint(char Header[], float Content, char Menu[]) {	
	int TextTab; 

	DisplayLCD.clear();

	TextTab  = (16 - strlen(Header)) / 2;				// Calculates necessary tab to center the text.

	DisplayLCD.setCursor(TextTab, 0);					// Selects the First display line and gives a tab to the content.
	DisplayLCD.print(Header);							// Prints the header.
	
	if (Content >= NULL) {
		DisplayLCD.setCursor(TextTab, 1);				// Second line.
		DisplayLCD.print(Content);						// Print the content information.
	}

	if (strlen(Menu)) {
		TextTab  = (16 - strlen(Menu)) / 2;				// Menu tab.

		DisplayLCD.setCursor(TextTab, 1);				// Second line.
		DisplayLCD.print(Menu);							// Print the content information.
	}
}

/* Button Functions */

void ButtonSetup(void) {
	pinMode(BUTTON_MORE, INPUT);
	pinMode(BUTTON_LESS, INPUT);
	pinMode(BUTTON_NEXT, INPUT);
	pinMode(SWITCH, INPUT);
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