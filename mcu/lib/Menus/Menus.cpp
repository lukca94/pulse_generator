#include "../../include/Free_Fonts.h"
#include <Arduino.h>
#include <TFT_eSPI.h>
#include <stdio.h>

#include "Control.h"
#include "Menus.h"
#include "Presets.h"
#include "../../include/Common.h"

void homeMenu() // Menu 1
{
	currentMenu = HOME_MENU;	// Menu identifier
	currentRow = 1;				// Initial cursor position
	firstRow = 1;				// Top cursor movement restriction
	numberOfRows = 3;			// Bottom cursor movement restriction

	pointerState = false;		// Reset pointer animation

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

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Enter f (Hz)", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	drawNumberLine(manualDigits, 1, 4);
	tft.drawString("Run", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}
void presetMenu() // Menu 3
{
	currentMenu = PRESETS_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;
	topShownLine = 0;

	pointerState = false;
	

	tft.fillScreen(TFT_BLACK);
	drawScrollableMenu();
}

void presetRemovingMenu() // Menu 4
{
	currentMenu = PRESETS_REMOVING_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;
	topShownLine = 0;

	pointerState = false;

	tft.fillScreen(TFT_BLACK);
	drawScrollableRemoveMenu();
}

void durationMenu() // Menu 5
{
	currentMenu = DURATION_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	pointerState = false;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Duration (s)", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	drawNumberLine(durationDigits, 1, 3);
	tft.drawString("Continue", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}

void dutyMenu() // Menu 6
{
	currentMenu = DUTY_MENU;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	pointerState = false;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Duty (%)", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	drawNumberLine(dutyDigits, 1, 2);
	tft.drawString("Continue", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}

void waitingMenu() // Menu 7
{
	currentMenu = WAITING_MENU;
	currentRow = 0;
	firstRow = 0;
	numberOfRows = 0;

	pointerState = false;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Waiting for", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	tft.drawString("a PPS signal", TEXT_BEGINNING, SECOND_LINE, GFXFF);
	tft.drawString("...", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}
void generatingMenu() // Menu 8
{
	currentMenu = GENERATING_MENU;
	currentRow = 0;
	firstRow = 0;
	numberOfRows = 0;

	pointerState = false;

	tft.fillScreen(TFT_BLACK);
	tft.drawString("Signal is", TEXT_BEGINNING, FIRST_LINE, GFXFF);
	tft.drawString("generated", TEXT_BEGINNING, SECOND_LINE, GFXFF);
	tft.drawString("...", TEXT_BEGINNING, THIRD_LINE, GFXFF);
}
