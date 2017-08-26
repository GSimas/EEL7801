/*
 * algorithme_functions.c
 *
 *  Created on: 26 de ago de 2017
 *      Author: André
 */

#include "algorithme_functions.h"

int TimeCounter = 0, TemperatureSelect = 25, TimeSelect = 5;
int ContentView;

/* Menu Functions */

void MenuStart(void) {
	/* Menu: Initialization */
	DisplayPrint("Bem vindo!", NO_CONTENT, NO_MENU);
	delay(1500);
}

void MenuTemperatureSelect(void) {
	/* Menu: Temperatura text */
	DisplayPrint("Escolha a", NO_CONTENT, "temperatura!");
	delay(3000);	

	/* Menu: Temperature Select */
	while (!ButtonVerification(BUTTON_NEXT)) {
		if (ButtonVerification(BUTTON_MORE)) {
			if (TemperatureSelect < SAFETY_TEMPERATURE) {
				TemperatureSelect = TemperatureSelect + 5;
			}
			delay(200);
		}
		if (ButtonVerification(BUTTON_LESS)) {
			if (TemperatureSelect > NULL) {
				TemperatureSelect = TemperatureSelect - 5;
			}
			delay(200);
		}
		else {
			DisplayPrint("Temperatura(C):", TemperatureSelect, NO_MENU);		
		}
		delay(100);
	}
}

void MenuTimeSelect(void) {
	/* Menu: Time text */
	DisplayPrint("Escolha o", NO_CONTENT, "tempo!");
	delay(3000);	

	/* Menu: Time Select */
	while (!ButtonVerification(BUTTON_NEXT)) {
		if (ButtonVerification(BUTTON_MORE)) {
			if (TimeSelect < SAFETY_TIME) {
				TimeSelect++;
			}
			delay(200);
		}
		if (ButtonVerification(BUTTON_LESS)) {
			if (TimeSelect > 1) {
				TimeSelect--;
			}
			delay(200);
		}
		else {
			DisplayPrint("Tempo(min):", TimeSelect, NO_MENU);		
		}
		delay(100);
	}

	TimeSelect = TimeSelect * 60 * PERIODS_IN_SEC;			// Convert the selected time to cycles per second.
}

void MenuConfirm(void) {
	/* Menu: Parameters confirmation */

	int PrintTime;

	DisplayPrint("Temperatura(C):", TemperatureSelect, NO_MENU);
	delay(2000);

	PrintTime = TimeSelect / (60 * PERIODS_IN_SEC);
	DisplayPrint("Tempo(min):", PrintTime, NO_MENU);
	delay(2000);

	while (!ButtonVerification(BUTTON_NEXT)) {
		DisplayPrint("Deseja", NO_CONTENT, "iniciar?");	
		delay(200);
	}
}

void ControlStart() {
	float SensorTemperature;

	ActuatorActivation(TURN_ON);							// Start the process.

	while (SensorRoutine() < TemperatureSelect) {
		SensorTemperature = SensorRoutine();
		DisplayPrint("Esquentando...", SensorTemperature, NO_MENU);	
		delay(300);
	}

	DisplayPrint("Temperatura", NO_CONTENT, "certa!" );	
	delay(1500);
}

void ControlDisplayView() { 
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

void ControlProcess() {
	if (SensorRoutine() >= TemperatureSelect) {
		ActuatorActivation(TURN_OFF);
	}
	if (SensorRoutine() < TemperatureSelect)  {
		ActuatorActivation(TURN_ON);
	}
}

void ControlSystemRun() {

	int ContentView = VIEW_TIME;

	ControlStart();

	while (TimeCounter <= TimeSelect) {
		ControlDisplayView();
		ControlProcess();

		TimeCounter++;
		delay(PERIOD);
	}

	ActuatorActivation(TURN_OFF);

	DisplayPrint("Finalizado com", NO_CONTENT, "sucesso!");
	delay(5000);

	DisplayPrint("Deseja iniciar", NO_CONTENT, "novamente?");
}