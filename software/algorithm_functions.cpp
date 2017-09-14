/*
 * algorithm_functions.c
 *
 *  Created on: 26 de ago de 2017
 *      Author: André
 */

#include "algorithm_functions.h"

int TimeCounter = 0, TemperatureSelect = DEFAULT_TEMPERATURE, TimeSelect = DEFAULT_TIME;
int ContentView;

/* Reset System (If necessary to use) 

void(* resetFunc) (void) = 0;				// Declare reset function at address 0.
*/

void ResetSystemVariables(void) {
	TimeCounter = 0;
	TemperatureSelect = DEFAULT_TEMPERATURE;
	TimeSelect = DEFAULT_TIME;
}

/* Switch Interrupt */

void SwitchInterrupt(void) {
	while(ButtonVerification(SWITCH)) {		// Switch open.
		ActuatorActivation(TURN_OFF);		// Actuator off for security.
		DisplayTurnMode(TURN_OFF);			
	}
	DisplayTurnMode(TURN_ON);
	if (SensorRoutine() < TemperatureSelect){
		ActuatorActivation(TURN_ON);
	}
}

/* Menu Functions */

void MenuStart(void) {

	ResetSystemVariables();

	/* Menu: Initialization */
	while (!ButtonVerification(BUTTON_NEXT));		// Wait the button for start.

	DisplayPrint("Bem vindo!", NO_CONTENT, NO_MENU);
	delay(1500);
}

void MenuTemperatureSelect(void) {
	int BlinkTurn = 0;

	/* Menu: Temperature text */
	DisplayPrint("Escolha a", NO_CONTENT, "temperatura!");
	delay(3000);	

	/* Menu: Temperature Select */
	while (!ButtonVerification(BUTTON_NEXT)) {
		if (ButtonVerification(BUTTON_PLUS)) {
			if (TemperatureSelect < SAFETY_TEMPERATURE) {
				TemperatureSelect = TemperatureSelect + 5;
			}
			delay(200);
		}
		if (ButtonVerification(BUTTON_MINUS)) {
			if (TemperatureSelect > NULL) {
				TemperatureSelect = TemperatureSelect - 5;
			}
			delay(200);
		}

		DisplayPrint("Temperatura(C):", TemperatureSelect, NO_MENU);		
		delay(100);
	}
	for (BlinkTurn = 0; BlinkTurn < 3; BlinkTurn++) {
		DisplayTurnMode(TURN_OFF);
		delay(300);
		DisplayTurnMode(TURN_ON);
		delay(300);
	}
	while (ButtonVerification(BUTTON_NEXT));				// Wait the button next.
}

void MenuTimeSelect(void) {
	int BlinkTurn = 0;

	/* Menu: Time text */
	DisplayPrint("Escolha o", NO_CONTENT, "tempo!");
	delay(3000);	

	/* Menu: Time Select */
	while (!ButtonVerification(BUTTON_NEXT)) {
		if (ButtonVerification(BUTTON_PLUS)) {
			if (TimeSelect < SAFETY_TIME) {
				TimeSelect++;
			}
			delay(200);
		}
		if (ButtonVerification(BUTTON_MINUS)) {
			if (TimeSelect > 1) {
				TimeSelect--;
			}
			delay(200);
		}
		DisplayPrint("Tempo(min):", TimeSelect, NO_MENU);		
		delay(100);
	}
	for (BlinkTurn = 0; BlinkTurn < 3; BlinkTurn++) {
		DisplayTurnMode(TURN_OFF);
		delay(300);
		DisplayTurnMode(TURN_ON);
		delay(300);
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
			break;
		}
		if (ButtonVerification(BUTTON_MINUS)) {
			while (ButtonVerification(BUTTON_MINUS));
			ResetSystemVariables();
			MenuTemperatureSelect();						// Starts the temperature selection.
			MenuTimeSelect();								// Starts the time selection.
			MenuConfirm();									// Confirm before start.
			break;
		}
		delay(200);
	}
}

void ControlStart(void) {
	float SensorTemperature;

	ActuatorActivation(TURN_ON);							// Start the process.

	while (SensorRoutine() < TemperatureSelect) {
		SensorTemperature = SensorRoutine();
		DisplayPrint("Esquentando...", SensorTemperature, NO_MENU);	
		delay(300);
		SwitchInterrupt();
	}

	DisplayPrint("Temperatura", NO_CONTENT, "certa!" );	
	delay(1500);
}

void ControlDisplayView(void) { 
	float PrintTime, SensorTemperature;

	if (ButtonVerification(BUTTON_NEXT)) {
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

	if (ContentView == VIEW_TEMPERATURE) {
		SensorTemperature = SensorRoutine();
		DisplayPrint("Temperatura(C):", SensorTemperature, NO_MENU);
	}
	if (ContentView == VIEW_TIME) {
		PrintTime = (TimeSelect - TimeCounter) / (60 * PERIODS_IN_SEC);
		DisplayPrint("Tempo Restante:", PrintTime, NO_MENU);	
	}
}

void ControlProcess(void) {
	if (SensorRoutine() >= (TemperatureSelect + RANGE_TEMPERATURE)) {
		ActuatorActivation(TURN_OFF);
	}
	if (SensorRoutine() < TemperatureSelect)  {
		ActuatorActivation(TURN_ON);
	}
}

void ControlSystemRun(void) {

	int ContentView = VIEW_TIME;
	ControlStart();

	while (TimeCounter <= TimeSelect) {
		ControlDisplayView();
		ControlProcess();
		SwitchInterrupt();

		TimeCounter++;
		delay(PERIOD);
	}

	ActuatorActivation(TURN_OFF);

	DisplayPrint("Finalizado com", NO_CONTENT, "sucesso!");
	delay(5000);

	DisplayPrint("Deseja iniciar", NO_CONTENT, "novamente?");
}