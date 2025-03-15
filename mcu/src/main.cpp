#include "Free_Fonts.h"
#include "Arduino.h"
#include "SPI.h"
#include "TFT_eSPI.h"

#define UP_BUTTON 36
#define DOWN_BUTTON 37
#define SELECT_BUTTON 38
#define RETURN_BUTTON 39

#define textBegining 30
#define pointerBegining 10
#define firstLine 18
#define secondLine 57
#define thirdLine 96

// screen size 135x240
TFT_eSPI tft = TFT_eSPI();
// tft.setFreeFont(FF2);  // Free mono 12pt

// tft.setFreeFont(FF6);	// bold
// tft.drawString("Hia", 100, 70, GFXFF);

uint16_t currentMenu;
u_int16_t currentRow;
uint16_t firstRow;
u_int16_t numberOfRows;

void homeMenu() // Menu 1
{
	currentMenu = 1;
	currentRow = 1;
	firstRow = 1;
	numberOfRows = 3;

	tft.setFreeFont(FF6);
	tft.fillScreen(TFT_BLACK);
	tft.drawString("Manual", textBegining, firstLine, GFXFF);
	tft.drawString("Presets", textBegining, secondLine, GFXFF);
	tft.drawString("Run presets", textBegining, thirdLine, GFXFF);
}
void manualMenu() // Menu 2
{
	currentMenu = 2;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	tft.setFreeFont(FF6);
	tft.fillScreen(TFT_BLACK);
	tft.drawString("Enter f (Hz):", textBegining, firstLine, GFXFF);
	tft.drawString("0 0 , 0 0", textBegining, secondLine, GFXFF);
	tft.drawString("Run", textBegining, thirdLine, GFXFF);
}
void presetMenu() // Menu 3 NOTDONE
{
	currentMenu = 2;
	currentRow = 2;
	firstRow = 2;
	numberOfRows = 3;

	tft.setFreeFont(FF6);
	tft.fillScreen(TFT_BLACK);
	tft.drawString("Enter a value f (Hz)", textBegining, firstLine, GFXFF);
	tft.drawString("0 0 , 0 0", textBegining, secondLine, GFXFF);
	tft.drawString("Run", textBegining, thirdLine, GFXFF);
}

void runPresets() {}

void enterNumber() {}

void runManual() {}

void select()
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
			runPresets();
			break;
		}
		break;

	case 2:
		switch (currentRow)
		{
		case 2:
			enterNumber();
			break;
		case 3:
			runManual();
			break;
		}
		break;
	}
}

unsigned long buttonDelay = 500;

unsigned long upButtonTime = 0;
void upButtonPress()
{
	uint8_t state = digitalRead(UP_BUTTON);

	if (state == 1)
	{
		if ((millis() - upButtonTime) >= buttonDelay)
		{
			upButtonTime = millis();
			currentRow--;
		}
	}
}
unsigned long downButtonTime = 0;
void downButtonPress()
{
	uint8_t state = digitalRead(DOWN_BUTTON);
	if (state == 1)
	{
		if ((millis() - downButtonTime) >= buttonDelay)
		{
			downButtonTime = millis();
			currentRow++;
		}
	}
}
unsigned long selectButtonTime = 0;
void selectButtonPress()
{
	uint8_t state = digitalRead(SELECT_BUTTON);
	if (state == 1)
	{
		if ((millis() - selectButtonTime) >= buttonDelay)
		{
			selectButtonTime = millis();
			select();
		}
	}
}
unsigned long returnButtonTime = 0;
void returnButtonPress()
{
	int state = digitalRead(RETURN_BUTTON);
	if (state == 1)
	{
		if ((millis() - returnButtonTime) >= buttonDelay)
		{
			returnButtonTime = millis();
			Serial.println("upis");
		}
	}
}

int lineCordinates[] = {firstLine, secondLine, thirdLine};

unsigned long pointerDelay = 1000;
unsigned long pointerTime = 0;
bool pointerState = false;
void drawPointer()
{
	if ((millis() - pointerTime) >= pointerDelay)
	{
		// Serial.println("ping");
		pointerTime = millis();
		if (pointerState == true)
		{
			tft.drawString("  ", pointerBegining, lineCordinates[currentRow - 1], GFXFF);
			pointerState = false;
		}
		else
		{
			tft.drawString(">", pointerBegining, lineCordinates[currentRow - 1], GFXFF);
			pointerState = true;
		}
	}
}

void setup()
{
	pinMode(UP_BUTTON, INPUT);
	pinMode(DOWN_BUTTON, INPUT);
	pinMode(SELECT_BUTTON, INPUT);
	pinMode(RETURN_BUTTON, INPUT);

	Serial.begin(9600);

	tft.begin();
	tft.setRotation(1);
	tft.setTextColor(TFT_ORANGE, TFT_BLACK);

	homeMenu();
}
void loop()
{
	upButtonPress();
	downButtonPress();
	selectButtonPress();
	returnButtonPress();

	drawPointer();
	// int width = tft.textWidth("Run presets");
	// Serial.println(width);

	// int height = tft.fontHeight();
	// Serial.println(height);
}