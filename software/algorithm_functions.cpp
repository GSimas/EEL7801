/*
 * algorithm_functions.c
 *
 *  Created on: 26 de ago de 2017
 *      Author: André
 */

#include "algorithm_functions.h"

int TimeCounter = 0, TemperatureSelect = DEFAULT_TEMPERATURE, TimeSelect = DEFAULT_TIME;
int ContentView;

/* Reset Microcontroller */ 

void(* resetFunc) (void) = 0;								// Declare reset function at address 0.

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
	while(ButtonVerification(SWITCH)) {						// Switch open.
		ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);		// Actuator Relay off for security.
		DisplayTurnMode(TURN_OFF);							// Indicate that the switch is not open.
	}
	DisplayTurnMode(TURN_ON);
	if (SensorRoutine() < TemperatureSelect){
		ActuatorActivation(TURN_ON, ACTUATOR_RELAY);
	}
}

/* Menu Functions */

void MenuStart(void) {

	ResetSystemVariables();

	/* Menu: Initialization */
	while (!ButtonVerification(BUTTON_NEXT));				// Wait the button for start.

	DisplayPrint("Bem vindo!", NO_CONTENT, "P.A.L.O.M.A");
	ActuatorActivation(TURN_ON, ACTUATOR_INDUCTOR);
	delay(DELAY_PERIOD_WELCOME);
}

void MenuTemperatureSelect(void) {
	int DisplayFlag = VALUE_NOT_CHANGED, BlinkTurn = 0;

	/* Menu: Temperature text */
	DisplayPrint("Escolha a", NO_CONTENT, "temperatura!");
	delay(DELAY_PERIOD_SELECTION);	

	/* Menu: Temperature Select */
	while (!ButtonVerification(BUTTON_NEXT)) {				// Loop to refresh the Display and verify the button state.
		if (ButtonVerification(BUTTON_PLUS)) {
			DisplayFlag = VALUE_CHANGED;
			if (TemperatureSelect < SAFETY_TEMPERATURE) {
				TemperatureSelect = TemperatureSelect + 5;
			}
			delay(DELAY_PERIOD_DEBOUNCER);
		}
		if (ButtonVerification(BUTTON_MINUS)) {
			DisplayFlag = VALUE_CHANGED;
			if (TemperatureSelect > 0) {
				TemperatureSelect = TemperatureSelect - 5;
			}
			delay(DELAY_PERIOD_DEBOUNCER);
		}

		if (DisplayFlag) {									// If value changed print in the display.
			DisplayPrint("Temperatura(C):", TemperatureSelect, NO_MENU);
			DisplayFlag = VALUE_NOT_CHANGED;
		}		

		delay(DELAY_PERIOD_DEBOUNCER);
	}
	for (BlinkTurn = 0; BlinkTurn < 3; BlinkTurn++) {		// Loop to indicate the chosen value.
		DisplayTurnMode(TURN_OFF);
		delay(DELAY_PERIOD_BLINK);
		DisplayTurnMode(TURN_ON);
		delay(DELAY_PERIOD_BLINK);
	}
	while (ButtonVerification(BUTTON_NEXT));				// Wait the button next.
}

void MenuTimeSelect(void) {									// Similar to the MenuTemperatureSelect().
	int DisplayFlag = VALUE_NOT_CHANGED, BlinkTurn = 0;

	/* Menu: Time text */
	DisplayPrint("Escolha o", NO_CONTENT, "tempo!");
	delay(DELAY_PERIOD_SELECTION);	

	/* Menu: Time Select */
	while (!ButtonVerification(BUTTON_NEXT)) {
		if (ButtonVerification(BUTTON_PLUS)) {
			DisplayFlag = VALUE_CHANGED;
			if (TimeSelect < SAFETY_TIME) {
				TimeSelect++;
			}
			delay(DELAY_PERIOD_DEBOUNCER);
		}
		if (ButtonVerification(BUTTON_MINUS)) {
			DisplayFlag = VALUE_CHANGED;
			if (TimeSelect > 1) {
				TimeSelect--;
			}
			delay(DELAY_PERIOD_DEBOUNCER);
		}
		if (DisplayFlag) {									// If value changed print in the display.
			DisplayPrint("Tempo(min):", TimeSelect, NO_MENU);
			DisplayFlag = VALUE_NOT_CHANGED;		
		}

		delay(DELAY_PERIOD_DEBOUNCER);
	}
	for (BlinkTurn = 0; BlinkTurn < 3; BlinkTurn++) {
		DisplayTurnMode(TURN_OFF);
		delay(DELAY_PERIOD_BLINK);
		DisplayTurnMode(TURN_ON);
		delay(DELAY_PERIOD_BLINK);
	}

	TimeSelect = TimeSelect * 60 * PERIODS_IN_SEC;			// Convert the selected time to cycles per second.
	while (ButtonVerification(BUTTON_NEXT));				// Wait the button next.
}

void MenuConfirm(void) {
	/* Menu: Parameters confirmation */
	while (1) {
		DisplayPrint("Confirmando...", NO_CONTENT, "Voltar | Iniciar");	
		if (ButtonVerification(BUTTON_PLUS)) {
			while (ButtonVerification(BUTTON_PLUS));
			ConfirmFlag = CONFIRMED;
			break;
		}
		if (ButtonVerification(BUTTON_MINUS)) {
			while (ButtonVerification(BUTTON_MINUS));
			ResetSystemVariables();
			break;
		}
		delay(DELAY_PERIOD_DEBOUNCER);
	}
}

/* Control Functions */

void ControlStart(void) {
	float SensorTemperature;

	ActuatorActivation(TURN_ON, ACTUATOR_RELAY);			// Start the process.

	while (SensorRoutine() < TemperatureSelect) {
		SensorTemperature = SensorRoutine();
		DisplayPrint("Esquentando...", SensorTemperature, NO_MENU);
		LEDDebugBlink(7);									// Blink Debug 7 times per second
		//SwitchInterrupt();
	}

	DisplayPrint("Temperatura", NO_CONTENT, "certa!" );	
	delay(DELAY_PERIOD_CONTROL);
}

void ControlDisplayView(void) { 
	float PrintTime, SensorTemperature;

	if (ButtonVerification(BUTTON_NEXT)) {					// Switch the view mode of the Display.
		switch (ContentView) {
			case VIEW_TIME:
				ContentView = VIEW_TEMPERATURE;
				break;
			case VIEW_TEMPERATURE:
				ContentView = VIEW_TIME;
				break;
			default: break;
		}
	}

	if (ContentView == VIEW_TEMPERATURE) {					// Temperatura view mode.
		SensorTemperature = SensorRoutine();
		DisplayPrint("Temperatura(C):", SensorTemperature, NO_MENU);
	}
	if (ContentView == VIEW_TIME) {							// Time view mode.
		PrintTime = (TimeSelect - TimeCounter) / (60 * PERIODS_IN_SEC);
		DisplayPrint("Tempo Restante:", PrintTime, NO_MENU);	
	}
}

void ControlProcess(void) {
	LEDDebugBlink(5);										// Blink Debug 5 times per second

	if (SensorRoutine() >= (TemperatureSelect + RANGE_TEMPERATURE)) {
		ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);
	}
	if (SensorRoutine() < TemperatureSelect)  {
		ActuatorActivation(TURN_ON, ACTUATOR_RELAY);
	}
}

void ControlSystemRun(void) {

	int ContentView = VIEW_TIME;
	int ResetCounter = 0;

	ControlStart();

	while (TimeCounter <= TimeSelect) {						// Loop routine for control the actuator.
		if (ButtonVerification(BUTTON_NEXT)){				// Reset with continuos pressed button start.
			ResetCounter++;
			if (ResetCounter >= RESET_PRESSED_TIME) {
				resetFunc();
			}
		}

		ControlDisplayView();							
		ControlProcess();
		//SwitchInterrupt();

		TimeCounter++;
		delay(PERIOD);
	}

	ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);
	ActuatorActivation(TURN_OFF, ACTUATOR_INDUCTOR);

	DisplayPrint("Finalizado com", NO_CONTENT, "sucesso!");
	delay(DELAY_PERIOD_END);

	DisplayPrint("Deseja iniciar", NO_CONTENT, "novamente?");
}