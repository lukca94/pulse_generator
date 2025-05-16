#include "../../include/Free_Fonts.h"
#include <Arduino.h>
#include <SPI.h>
#include <TFT_eSPI.h>
#include <stdio.h>
#include <stdint.h>

#include "Menus.h"
#include "Presets.h"
#include "../../include/Common.h"

#define POINTER_DELAY 500
#define DIGIT_OFFSET 30
#define COMMA_OFFSET 60

int lineCordinates[] = {FIRST_LINE, SECOND_LINE, THIRD_LINE};

uint8_t selectedNumberPosition = 0;

unsigned long pointerTime = 0;
bool pointerState = false;
bool freezePointer = false;

uint16_t topShownLine;
uint16_t scrollableLines;
uint8_t addPosition;
uint8_t removePosition;

unsigned long underlineTime = 0;
bool underlineState = false;
bool enteringNumber = false;

uint8_t manualDigits[4] = {0, 0, 0, 0};
uint8_t dutyDigits[2] = {0, 0};
uint8_t periodDigits[3] = {0, 0, 0};

uint16_t getOffset()
{
	if (currentMenu == DUTY_MENU || currentMenu == PERIODS_MENU)
		return (selectedNumberPosition - 1) * DIGIT_OFFSET;
	else
		return (selectedNumberPosition > 2) ? (selectedNumberPosition * DIGIT_OFFSET) : ((selectedNumberPosition - 1) * DIGIT_OFFSET);
}

void drawPointer()
{
	if (freezePointer == true)
	{
		pointerState = false;
	}
	if (currentRow == 0)
	{
		pointerState = true;
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

void drawNumberLine(uint8_t numberVector[4], uint8_t lineIndex, uint8_t numberVectorLenght)
{
	if (numberVectorLenght == 4)
	{
		tft.drawString(",", TEXT_BEGINNING + COMMA_OFFSET, lineCordinates[lineIndex], GFXFF);
		for (size_t i = 0; i < numberVectorLenght; i++)
		{
			char number[2];
			itoa(numberVector[i], number, 10);
			uint16_t offset = (i >= 2) ? (i + 1) * DIGIT_OFFSET : i * DIGIT_OFFSET;
			tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[lineIndex], GFXFF);
		}
	}
	else if (numberVectorLenght == 3 || numberVectorLenght == 2)
	{
		for (size_t i = 0; i < numberVectorLenght; i++)
		{
			char number[2];
			itoa(numberVector[i], number, 10);
			uint16_t offset = i * DIGIT_OFFSET;
			tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[lineIndex], GFXFF);
		}
	}
}

void drawScrollableMenu()
{
	tft.fillScreen(TFT_BLACK);

	if (topShownLine == 0) // Show header
	{
		firstRow = 2;	// Block first line selection
		currentRow = 2; // Select first non-header line

		tft.drawString("Presets f (Hz)", TEXT_BEGINNING, FIRST_LINE, GFXFF);
		if (numberOfPresets == 0) // No presets
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
				uint8_t number[4];
				memcpy(number, presetsArray[i], sizeof(number));
				drawNumberLine(number, i - topShownLine + 1, 4);
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
		for (size_t i = topShownLine; i < (topShownLine + presetsToShow); i++)
		{
			uint8_t number[4];
			memcpy(number, presetsArray[i - 1], sizeof(number));
			drawNumberLine(number, i - topShownLine, 4);
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
			uint8_t number[4];
			memcpy(number, presetsArray[i], sizeof(number));
			drawNumberLine(number, i - topShownLine + 1, 4);
		}
		if (presetsToShow == 1) // Not sure what is this for
		{
			numberOfRows = 2;
		}
	}
	else // Don't show header
	{
		firstRow = 1; // Allow first line selection

		uint8_t presetsToShow = numberOfPresets - topShownLine + 1;
		if (presetsToShow > 3)
			presetsToShow = 3;
		for (size_t i = topShownLine; i < (topShownLine + presetsToShow); i++)
		{
			uint8_t number[4];
			memcpy(number, presetsArray[i - 1], sizeof(number));
			drawNumberLine(number, i - topShownLine, 4);
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
		else if (currentMenu == PRESETS_MENU || currentMenu == PRESETS_REMOVING_MENU)
		{
			if (topShownLine != 0) // Upper limit
			{
				topShownLine--;
				if (currentMenu == PRESETS_MENU)
					drawScrollableMenu();
				else if (currentMenu == PRESETS_REMOVING_MENU)
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
		else if (currentMenu == PRESETS_MENU)
		{
			if (topShownLine != numberOfPresets) // Bottom limit
			{
				topShownLine++;

				drawScrollableMenu();
			}
		}
		else if (currentMenu == PRESETS_REMOVING_MENU)
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

void drawUnderline()
{
	if (enteringNumber == false || currentRow == 0)
	{
		return;
	}
	if ((millis() - underlineTime) >= POINTER_DELAY)
	{
		underlineTime = millis();
		uint16_t offset = getOffset();
		if (underlineState == true)
		{
			tft.fillRect(TEXT_BEGINNING + offset, lineCordinates[currentRow - 1] + tft.fontHeight() - 4, tft.textWidth("0"), 2, TFT_BLACK);
			underlineState = false;
		}
		else
		{
			tft.fillRect(TEXT_BEGINNING + offset, lineCordinates[currentRow - 1] + tft.fontHeight() - 4, tft.textWidth("0"), 2, TFT_ORANGE);
			underlineState = true;
		}
	}
}

void numberEntry(uint8_t direction, uint8_t numberOfDigits)
{
	uint16_t offset = getOffset();

	tft.fillRect(TEXT_BEGINNING + offset, lineCordinates[currentRow - 1] + tft.fontHeight() - 4, tft.textWidth("0") + 2, 2, TFT_BLACK);

	underlineState = false;

	switch (direction)
	{
	case SELECT:
		if (enteringNumber == false)
		{
			enteringNumber = true;
			freezePointer = true;
		}
		if (selectedNumberPosition == numberOfDigits) // exit
		{
			enteringNumber = false;
			freezePointer = false;
			pointerState = true;
			selectedNumberPosition = 0;
			break;
		}
		selectedNumberPosition++;
		break;

	case RETURN:
		if (selectedNumberPosition == 1) // exit
		{
			enteringNumber = false;
			freezePointer = false;
			pointerState = true;
			selectedNumberPosition = 0;
			break;
		}
		selectedNumberPosition--;
		break;
	}
}

void numberChange(uint8_t direction)
{
	uint16_t offset = getOffset();

	switch (currentMenu)
	{
	case MANUAL_MENU:
		switch (direction)
		{
		case UP:
			if (manualDigits[selectedNumberPosition - 1] < 9)
			{
				manualDigits[selectedNumberPosition - 1]++;

				char number[2];
				itoa(manualDigits[selectedNumberPosition - 1], number, 10);
				tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[currentRow - 1], GFXFF);
			}
			break;

		case DOWN:
			if (manualDigits[selectedNumberPosition - 1] > 0)
			{
				manualDigits[selectedNumberPosition - 1]--;

				char number[2];
				itoa(manualDigits[selectedNumberPosition - 1], number, 10);
				tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[currentRow - 1], GFXFF);
			}
			break;
		}
		break;

	case PRESETS_MENU:
		switch (direction)
		{
		case UP:
			if (presetsArray[topShownLine + currentRow - 2][selectedNumberPosition - 1] < 9)
			{
				presetsArray[topShownLine + currentRow - 2][selectedNumberPosition - 1]++;

				char number[2];
				itoa(presetsArray[topShownLine + currentRow - 2][selectedNumberPosition - 1], number, 10);
				tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[currentRow - 1], GFXFF);
			}
			break;

		case DOWN:
			if (presetsArray[topShownLine + currentRow - 2][selectedNumberPosition - 1] > 0)
			{
				presetsArray[topShownLine + currentRow - 2][selectedNumberPosition - 1]--;

				char number[2];
				itoa(presetsArray[topShownLine + currentRow - 2][selectedNumberPosition - 1], number, 10);
				tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[currentRow - 1], GFXFF);
			}
			break;
		}
		break;

	case PERIODS_MENU:
		switch (direction)
		{
		case UP:
			if (periodDigits[selectedNumberPosition - 1] < 9)
			{
				periodDigits[selectedNumberPosition - 1]++;

				char number[2];
				itoa(periodDigits[selectedNumberPosition - 1], number, 10);
				tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[currentRow - 1], GFXFF);
			}
			break;

		case DOWN:
			if (periodDigits[selectedNumberPosition - 1] > 0)
			{
				periodDigits[selectedNumberPosition - 1]--;

				char number[2];
				itoa(periodDigits[selectedNumberPosition - 1], number, 10);
				tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[currentRow - 1], GFXFF);
			}
			break;
		}
		break;

	case DUTY_MENU:
		switch (direction)
		{
		case UP:
			if (dutyDigits[selectedNumberPosition - 1] < 9)
			{
				dutyDigits[selectedNumberPosition - 1]++;

				char number[2];
				itoa(dutyDigits[selectedNumberPosition - 1], number, 10);
				tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[currentRow - 1], GFXFF);
			}
			break;

		case DOWN:
			if (dutyDigits[selectedNumberPosition - 1] > 0)
			{
				dutyDigits[selectedNumberPosition - 1]--;

				char number[2];
				itoa(dutyDigits[selectedNumberPosition - 1], number, 10);
				tft.drawString(number, TEXT_BEGINNING + offset, lineCordinates[currentRow - 1], GFXFF);
			}
			break;
		}
		break;
	}
}
