/*
*
* MAIN SKETCH - Main entry point for the firmware
*
* DIY-Thermocam Firmware
*
* GNU General Public License v3.0
*
* Copyright by Max Ritter
*
* http://www.diy-thermocam.net
* https://github.com/maxritter/DIY-Thermocam
*
*/

/* Current firmware version */
#define Version "Firmware 2.39 from 22.02.2017"
#define fwVersion 239

/* External Libraries */

#include "Libraries/SPI/SPI.h"
#include "Libraries/I2C/i2c_t3.h"
#include "Libraries/EEPROM/EEPROM.h"
#include "Libraries/ADC/ADC.h"
#include "Libraries/Metro/Metro.h"
#include "Libraries/Time/Time.h"
#include "Libraries/Bounce/Bounce.h"
#include "Libraries/SdFat/SdFat.h"

/* General Includes */

#include "General/GlobalDefines.h"
#include "General/GlobalVariables.h"
#include "General/GlobalMethods.h"
#include "General/ColorSchemes.h"

/* Modules */

#include "Hardware/Hardware.h"
#include "GUI/GUI.h"
#include "Thermal/Thermal.h"

/* Main Entry point */

void setup()
{
	CORE_PIN14_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);
	//Init the hardware components
	initHardware();

	//Check for firmware upgrade done
	//checkFWUpgrade();

	//Enter USB connection if no display attached
	if (checkNoDisplay()) {
		serialInit();
		Serial.print("no display");
	}

	/*display_fillScr(200, 200, 200);
	display_setFont(bigFont);
	display_setBackColor(200, 200, 200);
	display_setColor(VGA_FUCHSIA);
	display_print("does it wkjlork", CENTER, 10);*/
	//Check for hardware issues
	checkDiagnostic();
	Serial.print("checking");
	//Do the first start setup if required
	/*if (checkFirstStart())
		firstStart();*/

	//Read all settings from EEPROM
	readEEPROM();
	Serial.print("checking eeprom");
	//Show the live mode helper if required
	/*if (checkLiveModeHelper())
		liveModeHelper();*/

	//Go to the live Mode
	/*for (int x = 0; x < 2000; x++) {
		createThermalImg();
		showImage();
	}*/
	liveMode();
}

/* Loop not used */

void loop()
{
}
