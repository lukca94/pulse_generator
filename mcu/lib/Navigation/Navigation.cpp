#include <Arduino.h>

#include "Menus.h"
#include "Control.h"
#include "../../include/Common.h"
#include "Presets.h"
#include "Run.h"

uint16_t currentMenu;
uint16_t currentRow;
uint16_t firstRow;
uint16_t numberOfRows;

void selectNavigation()
{
	switch (currentMenu)
	{
	case HOME_MENU:
		switch (currentRow)
		{
		case 1:
			manualMenu();
			break;
		case 2:
			presetMenu();
			break;
		case 3:
			durationMenu();
			manual = false;
			break;
		}
		break;

	case MANUAL_MENU:
		switch (currentRow)
		{
		case 2:
			numberEntry(SELECT, 4);
			break;
		case 3:
			durationMenu();
			manual = true;
			break;
		}
		break;

	case PRESETS_MENU:
		if (currentRow == addPosition)
			addPreset();
		else if (currentRow == removePosition)
			presetRemovingMenu();
		else if (numberOfPresets != 0)
			numberEntry(SELECT, 4);
		break;

	case PRESETS_REMOVING_MENU:
		removePreset(topShownLine + currentRow - 2);
		presetMenu();
		break;

	case DURATION_MENU:
		switch (currentRow)
		{
		case 2:
			numberEntry(SELECT, 3);
			break;
		case 3:
			dutyMenu();
			break;
		}
		break;

	case DUTY_MENU:
		switch (currentRow)
		{
		case 2:
			numberEntry(SELECT, 2);
			break;
		case 3:
			run();
			break;
		}
		break;
	}
}
void returnNavigation()
{
	switch (currentMenu)
	{
	case MANUAL_MENU:
		if (enteringNumber == true)
		{
			numberEntry(RETURN, 4);
			break;
		}
		homeMenu();
		break;

	case PRESETS_MENU:
		if (enteringNumber == true)
		{
			numberEntry(RETURN, 4);
			break;
		}
		homeMenu();
		savePresets();
		break;

	case PRESETS_REMOVING_MENU:
		presetMenu();
		break;
	case DURATION_MENU:
		if (enteringNumber == true)
		{
			numberEntry(RETURN, 3);
			break;
		}
		if (manual == true)
		{
			manualMenu();
		}
		else
		{
			homeMenu();
		}

		break;

	case DUTY_MENU:
		if (enteringNumber == true)
		{
			numberEntry(RETURN, 2);
			break;
		}
		durationMenu();
		break;
	}
}
void upNavigation()
{
	if (enteringNumber == true)
		numberChange(UP);
	else
		lineChange(UP);
}
void downNavigation()
{
	if (enteringNumber == true)
		numberChange(DOWN);
	else
		lineChange(DOWN);
}
