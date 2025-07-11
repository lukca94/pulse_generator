#include "Free_Fonts.h"
#include <Arduino.h>

#include <TFT_eSPI.h>

#include "Common.h"
#include "Menus.h"
#include "Buttons.h"
#include "Control.h"
#include "Presets.h"

// screen size 135x240
TFT_eSPI tft = TFT_eSPI();


void setup()
{
	pinMode(UP_BUTTON, INPUT);
	pinMode(DOWN_BUTTON, INPUT);
	pinMode(SELECT_BUTTON, INPUT);
	pinMode(RETURN_BUTTON, INPUT);

	pinMode(INPUT_PIN,INPUT);
	pinMode(OUTPUT_PIN, OUTPUT);

	Serial.begin(9600);

	tft.begin();
	tft.setRotation(1);
	tft.setFreeFont(FF6);
	tft.setTextColor(TFT_ORANGE, TFT_BLACK);

	loadPresets();

	homeMenu();
}

void loop()
{
	upButtonPress();
	downButtonPress();
	selectButtonPress();
	returnButtonPress();

	drawPointer();
	drawUnderline();
}