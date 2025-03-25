#include "../../include/Free_Fonts.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <stdio.h>
#include <stdint.h> // Include standard header for uint8_t

#include "Menus.h"
#include "../../include/Common.h"

#define POINTER_DELAY 1000

int lineCordinates[] = {FIRST_LINE, SECOND_LINE, THIRD_LINE};

unsigned long pointerTime = 0;
bool pointerState = false;
bool freezePointer = false;
void drawPointer()
{
	if (freezePointer == true)
	{
		pointerState = false;
	}

	if ((millis() - pointerTime) >= POINTER_DELAY)
	{
		pointerTime = millis();
		if (pointerState == true)
		{
			tft.drawString("  ", POINTER_BEGINNING, lineCordinates[currentRow - 1], GFXFF);
			pointerState = false;
		}
		else
		{
			tft.drawString(">", POINTER_BEGINNING, lineCordinates[currentRow - 1], GFXFF);
			pointerState = true;
		}
	}
}

void lineChange(uint8_t direction)
{
	if (freezePointer == true)
	{
		return;
	}
	switch (direction)
	{
	case UP:
		if (firstRow < currentRow)
		{
			tft.drawString("  ", POINTER_BEGINNING, lineCordinates[currentRow - 1], GFXFF);
			currentRow--;
			pointerState = false;
			pointerTime = 0;
		}

		break;

	case DOWN:
		if (currentRow < numberOfRows)
		{
			tft.drawString("  ", POINTER_BEGINNING, lineCordinates[currentRow - 1], GFXFF);
			currentRow++;
			pointerState = false;
			pointerTime = 0;
		}

		break;
	}
}

uint8_t selectedNumberPosition = 0;
unsigned long underlineTime = 0;
bool underlineState = false;
bool enteringNumber = false;
void drawUnderline()
{
	if (enteringNumber == false)
	{
		return;
	}
	if ((millis() - underlineTime) >= POINTER_DELAY)
	{
		underlineTime = millis();
		if (underlineState == true)
		{
			tft.fillRect(TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, SECOND_LINE + tft.fontHeight() - 4, tft.textWidth("0"), 2, TFT_BLACK);
			underlineState = false;
		}
		else
		{
			tft.fillRect(TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, SECOND_LINE + tft.fontHeight() - 4, tft.textWidth("0"), 2, TFT_ORANGE);
			underlineState = true;
		}
	}
}

void numberEntry(uint8_t direction)
{
	tft.fillRect(TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, SECOND_LINE + tft.fontHeight() - 4, tft.textWidth("0") + 2, 2, TFT_BLACK);
	underlineState = false;

	switch (direction)
	{
	case SELECT:
		if (enteringNumber == false)
		{
			enteringNumber = true;
			freezePointer = true;
		}
		if (selectedNumberPosition == 5)
		{
			enteringNumber = false;
			freezePointer = false;
			pointerState = true;
			selectedNumberPosition = 0;
			break;
		}
		if (selectedNumberPosition == 2)
			selectedNumberPosition++;
		selectedNumberPosition++;
		break;

	case RETURN:
		if (selectedNumberPosition == 1)
		{
			enteringNumber = false;
			freezePointer = false;
			pointerState = true;
			selectedNumberPosition = 0;
			break;
		}
		if (selectedNumberPosition == 4)
			selectedNumberPosition--;
		selectedNumberPosition--;
		break;
	}
}

uint8_t enteredDigits[5] = {0, 0, 0, 0, 0}; 
void numberChange(uint8_t direction)
{
	switch (direction)
	{
	case UP:
		if (enteredDigits[(selectedNumberPosition - 1)] < 9)
		{
			enteredDigits[(selectedNumberPosition - 1)]++;
			char number[2];
			itoa(enteredDigits[(selectedNumberPosition - 1)], number, 10);
			tft.drawString(number, TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, SECOND_LINE, GFXFF);
		}

		break;

	case DOWN:
		if (enteredDigits[(selectedNumberPosition - 1)] > 0)
		{
			enteredDigits[(selectedNumberPosition - 1)]--;
			char number[2];
			itoa(enteredDigits[(selectedNumberPosition - 1)], number, 10);
			tft.drawString(number, TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, SECOND_LINE, GFXFF);
		}

		break;
	}
}
