#include <Arduino.h>

#include "Menus.h"
#include "../../include/Common.h"

#define BUTTON_DELAY 300

u_int16_t currentMenu;
u_int16_t currentRow;
u_int16_t firstRow;
u_int16_t numberOfRows;

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

unsigned long upButtonTime = 0;
void upButtonPress()
{
	uint8_t state = digitalRead(UP_BUTTON);

	if (state == 1)
	{
		if ((millis() - upButtonTime) >= BUTTON_DELAY)
		{
			upButtonTime = millis();
			if (enteringNumber == true)
				numberChange(UP);
			else
				lineChange(UP);
		}
	}
}

unsigned long downButtonTime = 0;
void downButtonPress()
{
	uint8_t state = digitalRead(DOWN_BUTTON);
	if (state == 1)
	{
		if ((millis() - downButtonTime) >= BUTTON_DELAY)
		{
			downButtonTime = millis();
			if (enteringNumber == true)
				numberChange(DOWN);
			else
				lineChange(DOWN);
		}
	}
}

unsigned long selectButtonTime = 0;
void selectButtonPress()
{
	uint8_t state = digitalRead(SELECT_BUTTON);
	if (state == 1)
	{
		if ((millis() - selectButtonTime) >= BUTTON_DELAY)
		{
			selectButtonTime = millis();
			selectNavigation();
		}
	}
}

unsigned long returnButtonTime = 0;
void returnButtonPress()
{
	int state = digitalRead(RETURN_BUTTON);
	if (state == 1)
	{
		if ((millis() - returnButtonTime) >= BUTTON_DELAY)
		{
			returnButtonTime = millis();
			returnNavigation();
		}
	}
}
