#include "control_system.h"

LiquidCrystal DisplayLCD;

// Setup routine
void setup() {
	SensorSetup();
	DisplaySetup();
	//Serial.begin(9600);
}

// Loop routine
void loop() {
	float SensorTemperature;
	SensorTemperature = SensorRoutine();

	DisplayRoutine("Temperatura:", char(SensorTemperature), 2, 0);

	//Serial.println(Temperature);
	delay(1000);
}

// Setup Functions
void SensorSetup() {
	analogReference(INTERNAL);							// Use 1.1V as analogic reference for the maximum precision of the sensor.
}

void DisplaySetup() {
	// Setup the display comunication pins.
	LiquidCrystal DisplayLCD (DISPLAY_RS, DISPLAY_EN, DISPLAY_D4, DISPLAY_D5, DISPLAY_D6, DISPLAY_D7);
	DisplayLCD.begin(16, 2);									// The display size, 2 lines and 16 columns.
}

// Routine Functions
float SensorRoutine() {
	int SensorRead;
	float TemperatureC;

	SensorRead = analogRead(SENSOR_PIN);				// Reads the sensor analogic value.
	TemperatureC = SensorRead / SENSOR_CONVERTION;		// Converts the raw temperature to celcius.
	
	return TemperatureC;
}

void DisplayRoutine(char Header[], char Content[], int LineOneTab, int LineTwoTab) {

	DisplayLCD.setCursor(LineOneTab, 0);						// Selects the First display line and gives a tab to the content.
	DisplayLCD.print(Header);									// Prints the header.
	
	DisplayLCD.setCursor(LineTwoTab, 1);						// Second line.
	DisplayLCD.print(Content);									// Print the content information.
}





