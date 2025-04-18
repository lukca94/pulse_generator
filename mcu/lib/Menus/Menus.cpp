#include "../../include/Free_Fonts.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <stdio.h>

#include "Control.h"
#include "Menus.h"
#include "Presets.h"
#include "../../include/Common.h"

void homeMenu() // Menu 1
{
	currentMenu = HOME_MENU;
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
	currentMenu = MANUAL_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	pointerState = false;
	// pointerTime = 0;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Enter f (Hz):", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	drawNumberLine(manualDigits, 1, 4);
	tft.drawString("Run", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}
void presetMenu()
{
	currentMenu = PRESETS_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;
	topShownLine = 0;

	pointerState = false;
	// pointerTime = 0;

	tft.fillScreen(TFT_BLACK);
	drawScrollableMenu();
}

void presetRemovingMenu()
{
	currentMenu = PRESETS_REMOVING_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;
	topShownLine = 0;

	pointerState = false;
	// pointerTime = 0;

	tft.fillScreen(TFT_BLACK);
	drawScrollableRemoveMenu();
}

void periodsMenu()
{
	currentMenu = PERIODS_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	pointerState = false;
	// pointerTime = 0;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Periods:", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	drawNumberLine(periodDigits, 1, 3);
	tft.drawString("Continue", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}

void dutyMenu()
{
	currentMenu = DUTY_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	pointerState = false;
	// pointerTime = 0;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Duty (%):", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	drawNumberLine(dutyDigits, 1, 3);
	tft.drawString("Continue", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}
