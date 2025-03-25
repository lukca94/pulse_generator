#include "../../include/Free_Fonts.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <stdio.h>

#include "Control.h"
#include "Menus.h"
#include "../../include/Common.h"

void homeMenu() // Menu 1
{
	currentMenu = 1; // DEFINE THESE AS WORDS
	currentRow = 1;
	firstRow = 1;
	numberOfRows = 3;

	pointerState = false;
	// pointerTime = 0;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Manual", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	tft.drawString("Presets", TEXT_BEGINNING, SECOND_LINE, GFXFF);
	tft.drawString("Run presets", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}
void manualMenu() // Menu 2
{
	currentMenu = 2;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	pointerState = false;
	// pointerTime = 0;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Enter f (Hz):", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	for (size_t i = 0; i < 5; i++) // TOHLE MOŽNÁ PŘEDĚLAT NA SEPARÁTNÍ FUNKCI
	{
		if (i == 2)
			tft.drawString(",", TEXT_BEGINNING + i * 30, SECOND_LINE, GFXFF);
		else
		{
			char number[2];
			itoa(enteredDigits[i], number, 10);
			tft.drawString(number, TEXT_BEGINNING + i * 30, SECOND_LINE, GFXFF);
		}
	}
	tft.drawString("Run", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}
void presetMenu() // Menu 3 NOTDONE
{
	currentMenu = 3;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	pointerState = false;
	// pointerTime = 0;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Presets", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	tft.drawString("0 0 , 0 0", TEXT_BEGINNING, SECOND_LINE, GFXFF);
	tft.drawString("0 0 , 0 0", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}
