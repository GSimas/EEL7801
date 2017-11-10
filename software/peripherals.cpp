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
	int SensorReadUp, SensorReadDown;
	float TemperatureC;

	SensorReadUp = analogRead(SENSOR_PIN_UP);			// Read the sensor analogic value.
	//SensorReadDown = analogRead(SENSOR_PIN_DOWN);			
	//TemperatureC = ((SensorReadUp*0.25) + (SensorReadDown*0.75) / SENSOR_CONVERTION;	// Convert the raw temperature to celcius.
	TemperatureC = SensorReadUp / SENSOR_CONVERTION;

	return TemperatureC;
}

/* Display Functions */

// Setup the display comunication pins.
LiquidCrystal DisplayLCD (DISPLAY_RST, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);

void DisplaySetup(void) {
	DisplayLCD.begin(DISPLAY_LINE_LENGTH, DISPLAY_NUMBER_LINES);				// The display size, 2 lines and 16 columns.
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

void DisplayPrint(const char Header[], float Content, const char Menu[]) {	
	int TextTab; 

	DisplayLCD.clear();

	TextTab  = (DISPLAY_LINE_LENGTH - strlen(Header)) / 2;						// Calculates necessary tab to center the text.

	DisplayLCD.setCursor(TextTab, 0);											// Selects the First display line and gives a tab to the content.
	DisplayLCD.print(Header);													// Prints the header.
	
	if (Content >= 0) {
		DisplayLCD.setCursor(TextTab, 1);										// Second line.
		DisplayLCD.print(Content);												// Print the content information.
	}

	if (strlen(Menu)) {
		TextTab  = (DISPLAY_LINE_LENGTH - strlen(Menu)) / 2;					// Menu tab.

		DisplayLCD.setCursor(TextTab, 1);										// Second line.
		DisplayLCD.print(Menu);													// Print the content information.
	}
}

/* Button Functions */

void ButtonSetup(void) {
	pinMode(BUTTON_PLUS, INPUT);
	pinMode(BUTTON_MINUS, INPUT);
	pinMode(BUTTON_NEXT, INPUT);
	pinMode(SWITCH, INPUT);
}

int ButtonVerification(int PushedButton) {
	int ButtonState, ButtonVerification;

	ButtonState = digitalRead(PushedButton);

	if (ButtonState == LOW){ 
		ButtonVerification = PUSHED;		
	}
	else { 
		ButtonVerification = NOT_PUSHED;
	}

	return ButtonVerification;
}

/* Actuator Functions */

void ActuatorSetup(void) {
	pinMode(ACTUATOR_RELAY, OUTPUT);
	pinMode(ACTUATOR_INDUCTOR, OUTPUT);
}

void ActuatorActivation(int TurnMode, int ActuatorSelection) {
	if(ActuatorSelection == ACTUATOR_RELAY){
		if (TurnMode) {
			digitalWrite(ACTUATOR_RELAY, HIGH);	
		}
		else {
			digitalWrite(ACTUATOR_RELAY, LOW);		
		}
	}
	else{
		if (TurnMode) {
			digitalWrite(ACTUATOR_INDUCTOR, HIGH);	
		}
		else {
			digitalWrite(ACTUATOR_INDUCTOR, LOW);		
		}
	}
}

void LEDDebugSetup(void) {
	pinMode(DEBUG_LED, OUTPUT);
}

void LEDDebugBlink(int BlinkFrequency) {
	float BlinkPeriod;

	if (BlinkFrequency < 5) {
		digitalWrite(DEBUG_LED, HIGH);
	}
	else {
		BlinkPeriod = 1000 / BlinkFrequency;
		digitalWrite(DEBUG_LED, HIGH);	
		delay(BlinkPeriod);
		digitalWrite(DEBUG_LED, LOW);
		delay(BlinkPeriod);
	} 
}



