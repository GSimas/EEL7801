/*
 * LogFunctions.cpp
 *
 *  Created on: 11 de nov de 2017
 *      Author: André
 */

#include "LogFunctions.h"

int ActualDataSize = 0;

void LogRefresh(void) {
	float AuxiliaryTemperature;
	unsigned long LogCoolingTimeEnd = 0;
	int AuxiliaryCounter;

	for (AuxiliaryCounter = 0; AuxiliaryCounter < LOG_DATA_SIZE; AuxiliaryCounter++) {
		if (CollectedData[AuxiliaryCounter] > 0) {
			AuxiliaryTemperature =+ CollectedData[AuxiliaryCounter];
			ActualDataSize++;
		}
	}
	LogAvarageTemperature = AuxiliaryTemperature/ ActualDataSize;
	
	LogMaximumTemperature = LogMaximumTemperatureBuffer;
	LogMinimumTemperature = LogMinimumTemperatureBuffer;
	
	LogTotalTime = TimeCounter;

	if (SensorRoutine() <= COLD_HOLDER){
		LogCoolingTimeEnd = millis();		
		LogCoolingTime = (LogCoolingTimeEnd - LogCoolingTimeStart) / 1000;
	} 
}

void LogOverview(void) {
	int LogOverviewMode = 0, LogMaxLength, DisplayFlag, AuxiliaryCounter;
	char PrintData[13];
	int TimeBaseVector[LOG_DATA_SIZE];

	for (AuxiliaryCounter = 0; AuxiliaryCounter < LOG_DATA_SIZE; AuxiliaryCounter++) {
		TimeBaseVector[AuxiliaryCounter] = 10 * AuxiliaryCounter;
	}

	LogMaxLength = LOG_DATA_SIZE + 8;

	DisplayPrint("Resultados:", NO_CONTENT, NO_MENU);
	delay(DELAY_PERIOD_LOG);

	/* Show the content at the first time */
	LogRefresh();
	DisplayPrint("Temp. media(C):", LogAvarageTemperature, NO_MENU);

	while (!ButtonVerification(BUTTON_NEXT)) {
		LogRefresh();

		if (ButtonVerification(BUTTON_PLUS)) {
			DisplayFlag = VALUE_CHANGED;
			if (LogOverviewMode < LogMaxLength) {
				LogOverviewMode++;
			}
			delay(DELAY_PERIOD_DEBOUNCER);
		}
		if (ButtonVerification(BUTTON_MINUS)) {
			DisplayFlag = VALUE_CHANGED;
			if (LogOverviewMode > 0) {
				LogOverviewMode--;
			}
			delay(DELAY_PERIOD_DEBOUNCER);
		}
		
		if (DisplayFlag) {									// If value changed print in the display.
			switch (LogOverviewMode) {
				case LOG_TEMPERATURE_AVERAGE:
					DisplayPrint("Temp. media(C):", LogAvarageTemperature, NO_MENU);
					break;
				case LOG_TEMPERATURE_MAXIMUM:
					DisplayPrint("Temp. max.(C):", LogMaximumTemperature, NO_MENU);
					break;
				case LOG_TEMPERATURE_MINIMUM:
					DisplayPrint("Temp. min.(C):", LogMinimumTemperature, NO_MENU);
					break;
				case LOG_TIME_TOTAL_ACTUAL:
					DisplayPrint("Tempo tot.(s):", LogTotalTime, NO_MENU);
					break;
				case LOG_TIME_HEATING:
					DisplayPrint("Tempo aqc.(s):", LogHeatingTime, NO_MENU);
					break;
				case LOG_TIME_COOLING:
					DisplayPrint("Tempo rsf.(s):", LogCoolingTime, NO_MENU);
					break;
				case LOG_INTERRUPTION_TOTAL_TIME:
					DisplayPrint("Tempo int.(s):", LogInterruptionTime, NO_MENU);
					break;
				case LOG_INTERRUPTION_NUMBER:
					DisplayPrint("interrup. numb.:", LogInterruptionNumber, NO_MENU);
					break;
				default: break;
			}

			if ((LogOverviewMode >= LOG_COLLECTED_DATA) && (LogOverviewMode <= (ActualDataSize + 8))) {
				if (CollectedData[LogOverviewMode-8] > 0) {
					sprintf(PrintData, "%d | %d", (int)CollectedData[LogOverviewMode-8], TimeBaseVector[LogOverviewMode-8]);
					DisplayPrint("Temp.x Tempo(s):", NO_CONTENT, PrintData);
				}
			}
			
			DisplayFlag = VALUE_NOT_CHANGED;		
		}
		delay(DELAY_PERIOD_DEBOUNCER);
	}

	DisplayPrint("Deseja iniciar", NO_CONTENT, "novamente?");
	while(!ButtonVerification(BUTTON_NEXT));
}