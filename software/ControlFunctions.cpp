/*
 * ControlFunctions.cpp
 *
 *  Created on: 11 de nov de 2017
 *      Author: André
 */

#include "ControlFunctions.h"

int AuxiliaryCounterData = 0;
int ContentViewFlag = VIEW_TEMPERATURE;
unsigned long StartRestoreTime = 0, EndRestoreTime = 0, RestoreTime = 0;

/*
 * Function: ResetFunc(void)
 * Reset the microcontroller. 
 */
void(* resetFunc) (void) = 0;                // Declare reset function at address 0.

void ControlStart(void) {
	float SensorTemperature;
	unsigned long LogHeatingTimeStart = 0, LogHeatingTimeEnd = 0;
	int DataCollectCounterStart = 0, DataCollectModStart = 0, DisplayCounter = 0, DisplayMod = 0, DelayCounter = 0;

	ActuatorActivation(TURN_ON, ACTUATOR_RELAY);			// Start the process.

	LogMaximumTemperatureBuffer = SensorRoutine();
	LogHeatingTimeStart = millis();

	while (SensorRoutine() < TEMPERATURE_START_LIMIT) {
		SensorTemperature = SensorRoutine();

		if (LogMaximumTemperatureBuffer < SensorTemperature) {
			LogMaximumTemperatureBuffer = SensorTemperature;
		}

		DisplayMod = DisplayCounter++ % (PERIODS_IN_SEC * 2);
		if (DisplayMod == 0) {
			DisplayPrint("Esquentando...", SensorTemperature, NO_MENU);
		}
		//SwitchInterrupt();
		
		/*
		DataCollectModStart = DataCollectCounterStart++ % DATA_COLLECT_RATE;
		if (DataCollectModStart == 0) {
			CollectedData[AuxiliaryCounterData++] = SensorRoutine(); 		
		}
		*/
		LEDDebugBlink(TURN_ON);								// Blink LED Debug
		delay(PERIOD);
		LEDDebugBlink(TURN_OFF);							// Blink LED Debug
	}

	ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);
	delay(DELAY_PERIOD_SECURITY_TIME);

	if (TemperatureSelect >= SLOW_PASTEURIZATION) {
		if (TemperatureSelect >= FAST_PASTEURIZATION) {
			DisplayPrint("Pasteurizacao", NO_CONTENT, "rapida");
			while (DelayCounter++ < DELAY_HEATING_FAST) {
				ActuatorActivation(TURN_ON, ACTUATOR_RELAY);
				//SwitchInterrupt();
				delay(DELAY_PERIOD_HEATING);
			}
		}
		else {
			DisplayPrint("Pasteurizacao", NO_CONTENT, "lenta");
			while (DelayCounter++ < DELAY_HEATING_SLOW) {
				ActuatorActivation(TURN_ON, ACTUATOR_RELAY);
				//SwitchInterrupt();
				delay(DELAY_PERIOD_HEATING);
			}
		}
	}

	LogMinimumTemperatureBuffer = SensorRoutine();
	LogHeatingTimeEnd = millis();
	LogHeatingTime = (LogHeatingTimeEnd - LogHeatingTimeStart) / 1000;

	LEDDebugBlink(TURN_ON);									// Blink LED Debug

	DisplayPrint("Temperatura", NO_CONTENT, "certa!" );	
	delay(DELAY_PERIOD_CONTROL);
}

void ControlDisplayView(void) { 
	int PrintTimeRaw, PrintTimeSeconds, PrintTimeMinutes;
	float SensorTemperature;
	char PrintTimeString[5];

	if (ContentViewFlag == VIEW_TEMPERATURE) {					// Temperatura view mode.
		SensorTemperature = SensorRoutine();
		DisplayPrint("Temperatura(C):", SensorTemperature, NO_MENU);
	}
	if (ContentViewFlag == VIEW_TIME) {							// Time view mode.
		PrintTimeRaw = TimeSelect - TimeCounter;			// Countdown.
		PrintTimeMinutes = PrintTimeRaw / 60.0;
		PrintTimeSeconds = PrintTimeRaw % 60;
		if (PrintTimeSeconds < 10){
			sprintf(PrintTimeString, "%d:0%d", PrintTimeMinutes, PrintTimeSeconds);
		}
		else {
			sprintf(PrintTimeString, "%d:%d", PrintTimeMinutes, PrintTimeSeconds);
		}
		DisplayPrint("Tempo Restante:", NO_CONTENT, PrintTimeString);	
	}
}

void ControlProcessDynamicChange(void) {
	ResetSystemVariables();
	MenuTemperatureSelect();
	MenuTimeSelect();
	EndRestoreTime = millis();
	RestoreTime = RestoreTime + (EndRestoreTime - StartRestoreTime);
	LEDDebugBlink(TURN_ON);								// Blink LED Debug
}

void ControlProcess(void) {
	float CurrentTemperature;

	CurrentTemperature = SensorRoutine();

	if (LogMaximumTemperatureBuffer < CurrentTemperature) {
		LogMaximumTemperatureBuffer = CurrentTemperature;
	}
	if (LogMinimumTemperatureBuffer > CurrentTemperature) {
		LogMinimumTemperatureBuffer = CurrentTemperature;
	}

	if (CurrentTemperature >= (TemperatureSelect)) {
		ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);
	}
	if (CurrentTemperature < TemperatureSelect - CONTROL_RANGE_TEMPERATURE)  {
		ActuatorActivation(TURN_ON, ACTUATOR_RELAY);
	}
}

void ControlSystemRun(void) {

	int ResetCounter = 0, DataCollectCounter = 0;
	int DisplayCounter = 0, DisplayMod = 0, DataCollectMod = 0;
	unsigned long StartControlTime = 0, EndTurnTime = 0;

	LogMaximumTemperatureBuffer = SensorRoutine();
	ControlStart();

	StartControlTime = millis();

	while (TimeCounter <= TimeSelect) {						// Loop routine for control the actuator.
		
		/* Reset with continuos button minus pressed */
		if (ButtonVerification(BUTTON_MINUS)){				
			ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);
			
			LogInterruptionNumber++;
			LogInterruptTimeStart = millis();	

			while(ButtonVerification(BUTTON_MINUS)) {
				ResetCounter++;
				delay(PERIOD);
			}
			if (ResetCounter >= RESET_PRESSED_TIME) {
				resetFunc();	
			}
			ResetCounter = 0;

			LogInterruptTimeEnd = millis();		
			LogInterruptionTime = LogInterruptionTime + ((LogInterruptTimeEnd - LogInterruptTimeStart) / 1000);
		}

		/* Dynamic temperature change with button plus */
		if (ButtonVerification(BUTTON_PLUS)){
			StartRestoreTime = millis();
			ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);
			while(ButtonVerification(BUTTON_PLUS));
			
			LogInterruptionNumber++;
			LogInterruptTimeStart = millis();	

			ControlProcessDynamicChange();

			LogInterruptTimeEnd = millis();		
			LogInterruptionTime = LogInterruptionTime + ((LogInterruptTimeEnd - LogInterruptTimeStart) / 1000);
		}

		/* Show a different content with the button next */
		if (ButtonVerification(BUTTON_NEXT)) {					// Switch the view mode of the Display.
			if (ContentViewFlag == VIEW_TEMPERATURE) {
				ContentViewFlag = VIEW_TIME;
			}
			else {
				ContentViewFlag = VIEW_TEMPERATURE;
			}
		}

		/* Avoid flickering on display and blink debug LED */
		DisplayMod = DisplayCounter++ % PERIODS_IN_SEC;
		if (DisplayMod == 0) {
			ControlDisplayView();
		}

		ControlProcess();
		//SwitchInterrupt();

		delay(PERIOD);

		EndTurnTime = millis();
		TimeCounter = ((EndTurnTime - StartControlTime) - RestoreTime) / 1000;	// Convertion to seconds, normaly RestoreTime = 0.
	
		/* Collect the temperature during the process
		DataCollectMod = DataCollectCounter++ % DATA_COLLECT_RATE;
		if (DataCollectMod) {
			CollectedData[AuxiliaryCounterData++] = SensorRoutine(); 		
		}
		*/
	}

	ActuatorActivation(TURN_OFF, ACTUATOR_RELAY);
	ActuatorActivation(TURN_OFF, ACTUATOR_INDUCTOR);

	LogCoolingTimeStart = millis();

	DisplayPrint("Finalizado com", NO_CONTENT, "sucesso!");
	while (!ButtonVerification(BUTTON_NEXT));
}