#include <LiquidCrystal.h>

// Pins Abstraction.
#define SENSOR_PIN			0
#define DISPLAY_RS			12
#define DISPLAY_EN			11
#define DISPLAY_D4			5
#define DISPLAY_D5			4
#define DISPLAY_D6			3
#define DISPLAY_D7			2

// Constants Abstraction.
#define SENSOR_CONVERTION 	(0.01 / (1.1 / 1024))		// (10 millivolts per celcius) / (analogic reference) / (ADC convertion range).