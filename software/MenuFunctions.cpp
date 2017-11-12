/*
 * MenuFunctions.cpp
 *
 *  Created on: 11 de nov de 2017
 *      Author: André
 */

#include "MenuFunctions.h"

void MenuStart(void) {

	/* Initialization */
	int AuxiliaryCounter;
	for (AuxiliaryCounter = 0; AuxiliaryCounter < LOG_DATA_SIZE; AuxiliaryCounter++) {
		CollectedData[AuxiliaryCounter] = 0;
	}

	ResetSystemVariables();

	/* Menu: Initialization */
	while (!ButtonVerification(BUTTON_NEXT));				// Wait the button for start.

	LEDDebugBlink(5);										// Blink LED Debug 5 times per second
	DisplayPrint("Bem vindo!", NO_CONTENT, "P.A.L.O.M.A");
	ActuatorActivation(TURN_ON, ACTUATOR_INDUCTOR);
	delay(DELAY_PERIOD_WELCOME);
}

void MenuTemperatureSelect(void) {
	int DisplayFlag = VALUE_NOT_CHANGED, BlinkTurn = 0;

	LEDDebugBlink(0);										// Turn on LED Debug

	/* Menu: Temperature text */
	DisplayPrint("Escolha a", NO_CONTENT, "temperatura!");
	delay(DELAY_PERIOD_SELECTION);	
	DisplayPrint("Temperatura(C):", TemperatureSelect, NO_MENU);

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

	LEDDebugBlink(0);

	/* Menu: Time text */
	DisplayPrint("Escolha o", NO_CONTENT, "tempo!");
	delay(DELAY_PERIOD_SELECTION);	
	DisplayPrint("Tempo(min):", TimeSelect, NO_MENU);

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

	TimeSelect = TimeSelect * 60;							// Convertion to seconds.
	while (ButtonVerification(BUTTON_NEXT));				// Wait the button next.
}

void MenuConfirm(void) {
	/* Menu: Parameters confirmation */
	DisplayPrint("Confirmando...", NO_CONTENT, "Voltar | Iniciar");

	while (1) {	
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