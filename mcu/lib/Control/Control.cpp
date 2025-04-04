#include "../../include/Free_Fonts.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <stdio.h>
#include <stdint.h> // Include standard header for uint8_t

#include "Menus.h"
#include "Presets.h"
#include "../../include/Common.h"

#define POINTER_DELAY 1000
#define DIGIT_OFFSET 30
#define COMMA_OFFSET 60

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

void drawNumber(uint16_t arrayIndex, uint8_t lineIndex)
{
	tft.drawString(",", TEXT_BEGINNING + COMMA_OFFSET, lineIndex, GFXFF);
	for (size_t i = 0; i < 4; i++)
	{
		char number[2];
		itoa(presetsArray[arrayIndex][i], number, 10);
		uint16_t offset = (i >= 2) ? (i + 1) * DIGIT_OFFSET : i * DIGIT_OFFSET;
		tft.drawString(number, TEXT_BEGINNING + offset, lineIndex, GFXFF);
	}
}

uint16_t topShownLine;
uint16_t scrollableLines;
uint8_t addPosition;
uint8_t removePosition;
void drawScrollableMenu()
{
	tft.fillScreen(TFT_BLACK);

	if (topShownLine == 0) // Show header
	{
		firstRow = 2;	// Block first line selection
		currentRow = 2; // Select first non-header line

		tft.drawString("Presets", TEXT_BEGINNING, FIRST_LINE, GFXFF);
		if (numberOfPresets == 0)
		{

			tft.drawString("No presets", TEXT_BEGINNING, SECOND_LINE, GFXFF);
			tft.drawString("Add", TEXT_BEGINNING, THIRD_LINE, GFXFF);

			addPosition = 3;
			removePosition = 0;
		}
		else
		{
			uint8_t presetsToShow = numberOfPresets - topShownLine;
			if (presetsToShow > 2)
				presetsToShow = 2;
			for (size_t i = topShownLine; i < topShownLine + presetsToShow; i++)
			{
				drawNumber(i, lineCordinates[i - topShownLine + 1]);
			}
			addPosition = 0;
			removePosition = 0;
			if (presetsToShow == 1)
			{
				tft.drawString("Add", TEXT_BEGINNING, THIRD_LINE, GFXFF);

				addPosition = 3;
			}
		}
	}
	else // Don't show header
	{
		firstRow = 1; // Allow first line selection

		uint8_t presetsToShow = numberOfPresets - topShownLine + 1;

		if (presetsToShow > 3)
			presetsToShow = 3;
		for (size_t i = topShownLine; i < topShownLine + presetsToShow; i++)
		{
			drawNumber(i - 1, lineCordinates[i - topShownLine]); // Hopefully this is fine :)
		}

		addPosition = 0;
		removePosition = 0;
		if (presetsToShow == 1)
		{
			tft.drawString("Add", TEXT_BEGINNING, SECOND_LINE, GFXFF);
			tft.drawString("Remove", TEXT_BEGINNING, THIRD_LINE, GFXFF);

			addPosition = 2;
			removePosition = 3;
		}
		else if (presetsToShow == 2)
		{
			tft.drawString("Add", TEXT_BEGINNING, THIRD_LINE, GFXFF);

			addPosition = 3;
		}
	}
}
void drawScrollableRemoveMenu()
{
	tft.fillScreen(TFT_BLACK);

	if (topShownLine == 0) // Show header
	{
		firstRow = 2;	// Block first line selection
		currentRow = 2; // Select first non-header line

		tft.drawString("Choose", TEXT_BEGINNING, FIRST_LINE, GFXFF);

		uint8_t presetsToShow = numberOfPresets - topShownLine;
		if (presetsToShow > 2)
			presetsToShow = 2;
		for (size_t i = topShownLine; i < topShownLine + presetsToShow; i++)
		{
			drawNumber(i, lineCordinates[i - topShownLine + 1]);
		}
		if (presetsToShow == 1)
		{
			numberOfRows = 2;
		}
	}
	else // Don't show header
	{
		firstRow = 1; // Allow first line selection

		uint8_t presetsToShow = numberOfPresets - topShownLine + 1;
		Serial.println(presetsToShow);
		if (presetsToShow > 3)
			presetsToShow = 3;
		for (size_t i = topShownLine; i < topShownLine + presetsToShow; i++)
		{
			drawNumber(i, lineCordinates[i - topShownLine]);
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
		else if (currentMenu == 3 || currentMenu == 4)
		{
			if (topShownLine != 0) // Upper limit
			{
				topShownLine--;
				if (currentMenu == 3)
					drawScrollableMenu();
				else if (currentMenu == 4)
					drawScrollableRemoveMenu();
			}
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
		else if (currentMenu == 3)
		{
			if (topShownLine != numberOfPresets) // Bottom limit
			{
				topShownLine++;

				drawScrollableMenu();
			}
		}
		else if (currentMenu == 4)
		{
			if (topShownLine < numberOfPresets - 2) // Bottom limit
			{
				topShownLine++;

				drawScrollableRemoveMenu();
			}
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
			tft.fillRect(TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, lineCordinates[currentRow-1] + tft.fontHeight() - 4, tft.textWidth("0"), 2, TFT_BLACK);
			underlineState = false;
		}
		else
		{
			tft.fillRect(TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, lineCordinates[currentRow - 1] + tft.fontHeight() - 4, tft.textWidth("0"), 2, TFT_ORANGE);
			underlineState = true;
		}
	}
}

void numberEntry(uint8_t direction) //Hrozně fucked up indexy
{
	tft.fillRect(TEXT_BEGINNING + (selectedNumberPosition - 1) * 30,
				 lineCordinates[currentRow - 1] + tft.fontHeight() - 4, tft.textWidth("0") + 2, 2, TFT_BLACK);

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
			tft.drawString(number, TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, lineCordinates[currentRow - 1], GFXFF);
		}

		break;

	case DOWN:
		if (enteredDigits[(selectedNumberPosition - 1)] > 0)
		{
			enteredDigits[(selectedNumberPosition - 1)]--;
			
			char number[2];
			itoa(enteredDigits[(selectedNumberPosition - 1)], number, 10);
			tft.drawString(number, TEXT_BEGINNING + (selectedNumberPosition - 1) * 30, lineCordinates[currentRow - 1], GFXFF);
		}

		break;
	}
}
