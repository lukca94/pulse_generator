#include <Arduino.h>
#include <TFT_eSPI.h>
#include <Preferences.h>

#include "../../include/Common.h"
#include "Control.h"

#define SAVE_DELAY 10000

Preferences pref;

int16_t presetsArray[NUMBER_OF_PRESETS][4] = {-1};
uint16_t numberOfPresets = 0;

uint32_t saveTime = 0;
int16_t presetsArrayPrevious[NUMBER_OF_PRESETS][4];

void addPreset()
{
	if (numberOfPresets == NUMBER_OF_PRESETS) // Maximum number of presets..
		return;

	int16_t newRow[4] = {0, 0, 0, 0};
	memcpy(presetsArray[numberOfPresets], newRow, sizeof(newRow));
	numberOfPresets++;
	drawScrollableMenu();
}

void removePreset(uint16_t index)
{
	if (numberOfPresets == 0) // Nothing to remove
		return;

	for (size_t i = index; i < (numberOfPresets - index); i++)
	{
		memcpy(presetsArray[i], presetsArray[i + 1], sizeof(presetsArray[i + 1]));
	}

	int16_t emptyRow[4] = {-1, -1, -1, -1};
	memcpy(presetsArray[numberOfPresets], emptyRow, sizeof(emptyRow));

	numberOfPresets--;
}

void loadPresets()
{
	pref.begin("presetsStorage", false);
	pref.getBytes("presets", presetsArray, sizeof(presetsArray));

	for (size_t i = 0; i < NUMBER_OF_PRESETS; i++)
	{
		if (presetsArray[i][1] != -1)
			numberOfPresets++;
	}
	memcpy(presetsArrayPrevious, presetsArray, sizeof(presetsArray));
}

void savePresets()
{
	if (presetsArray != presetsArrayPrevious)
	{
		pref.putBytes("presets", presetsArray, sizeof(presetsArray));
		memcpy(presetsArrayPrevious, presetsArray, sizeof(presetsArray));
	}
}
