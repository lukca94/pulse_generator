#include <Arduino.h>

#include "Menus.h"
#include "Control.h"
#include "../../include/Common.h"

uint16_t currentMenu;
uint16_t currentRow;
uint16_t firstRow;
uint16_t numberOfRows;


void selectNavigation()
{
	switch (currentMenu)
	{
	case 1:
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

	case 2:
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
	}
}
void returnNavigation()
{
	switch (currentMenu)
	{
	case 2:
		if (enteringNumber == true)
		{
			numberEntry(RETURN);
			break;
		}

		homeMenu();
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
