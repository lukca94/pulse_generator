#include "Free_Fonts.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>

#include "Menus.h"
#include "Common.h"
#include "Buttons.h"

// screen size 135x240
TFT_eSPI tft = TFT_eSPI();
// tft.setFreeFont(FF2);  // Free mono 12pt

// tft.setFreeFont(FF6);	// bold
// tft.drawString("Hia", 100, 70, GFXFF);

void setup()
{
	pinMode(UP_BUTTON, INPUT);
	pinMode(DOWN_BUTTON, INPUT);
	pinMode(SELECT_BUTTON, INPUT);
	pinMode(RETURN_BUTTON, INPUT);

	Serial.begin(9600);

	tft.begin();
	tft.setRotation(1);
	tft.setFreeFont(FF6);
	tft.setTextColor(TFT_ORANGE, TFT_BLACK);

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