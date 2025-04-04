#include <Arduino.h>

#include "Menus.h"
#include "Control.h"
#include "../../include/Common.h"
#include "Presets.h"

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
			// runPresets();
			break;
		}
		break;

	case MANUAL_MENU:
		switch (currentRow)
		{
		case 2:
			numberEntry(SELECT);
			break;
		case 3:
			// runManual();
			break;
		}
		break;
	case PRESETS_MENU:
		if (currentRow == addPosition)
			addPreset(); // inconsistent when header shown
		else if (currentRow == removePosition)
			presetRemovingMenu();
		else
		{
			numberEntry(SELECT);
		}
		break;
	case PRESETS_REMOVING_MENU:
		removePreset(topShownLine + currentRow - 1);
		presetMenu();
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
			numberEntry(RETURN);
			break;
		}
		homeMenu();
		break;
	case PRESETS_MENU:
		if (enteringNumber == true)
		{
			numberEntry(RETURN);
			break;
		}
		homeMenu();
		break;
	case PRESETS_REMOVING_MENU:

		presetMenu();
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
