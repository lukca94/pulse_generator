#include <Arduino.h>

#include "Navigation.h"
#include "../../include/Common.h"

#define BUTTON_DELAY 300

unsigned long upButtonTime = 0;
void upButtonPress()
{
	uint8_t state = digitalRead(UP_BUTTON);

	if (state == 1)
	{
		if ((millis() - upButtonTime) >= BUTTON_DELAY)
		{
			upButtonTime = millis();
			upNavigation();
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
			downNavigation();
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
	uint8_t state = digitalRead(RETURN_BUTTON);
	if (state == 1)
	{
		if ((millis() - returnButtonTime) >= BUTTON_DELAY)
		{
			returnButtonTime = millis();
			returnNavigation();
		}
	}
}
