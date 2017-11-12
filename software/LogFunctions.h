/*
 * LogFunctions.h
 *
 *  Created on: 11 de nov de 2017
 *      Author: André
 */

#ifndef LOG_FUNCTIONS_H_
#define LOG_FUNCTIONS_H_

#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include "Peripherals.h"
#include "HardwareAbstractionLayer.h"
#include "includes.h"

extern long TimeCounter;
extern long LogAvarageTemperature, LogMaximumTemperature, LogMinimumTemperature;
extern int LogTotalTime, LogHeatingTime, LogCoolingTime, LogInterruptionTime, LogInterruptionNumber;
//extern int CollectedData[LOG_DATA_SIZE];
extern unsigned long LogCoolingTimeStart;
extern float LogMaximumTemperatureBuffer, LogMinimumTemperatureBuffer;

#define DELAY_PERIOD_LOG				3000
#define DELAY_PERIOD_DEBOUNCER    		200

#define LOG_TEMPERATURE_AVERAGE			0
#define LOG_TEMPERATURE_MAXIMUM			1
#define LOG_TEMPERATURE_MINIMUM			2
#define LOG_TIME_TOTAL_ACTUAL			3
#define LOG_TIME_HEATING				4
#define LOG_TIME_COOLING				5
#define LOG_INTERRUPTION_TOTAL_TIME		6	
#define LOG_INTERRUPTION_NUMBER			7
#define LOG_COLLECTED_DATA				8

/*
 * Function: LogOverview(void)
 * This show the data colleted (log) in a menu 
 */
void LogOverview(void);

/*
 * Function: LogRefresh(void)
 * This refresh the data colleted 
 */
void LogRefresh(void);

#endif /* LOG_FUNCTIONS_H_ */
