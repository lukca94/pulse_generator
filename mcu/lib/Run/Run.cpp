#include <Arduino.h>
#include "../../include/Common.h"
#include "Menus.h"

#define PULSE_SET_DELAY 5000

bool manual = false;
bool outputState = false;
unsigned long startTime = 0;
double periodTime;
unsigned long onTime;
unsigned long offTime;
uint8_t cycles = 0;
double frequency = 0;

void run()
{
	uint8_t cycles;
	double frequency;
	double duty = (double)(dutyDigits[0] * 10 + dutyDigits[1]) / 100;
	uint16_t numberOfPeriods = periodDigits[0] * 100 + periodDigits[1] * 10 + periodDigits[2];

	waitingMenu();

	while (true)
	{
		if (digitalRead(INPUT_PIN))
			break;
	}

	generatingMenu();

	if (manual == true)
		cycles = 1;
	else
		cycles = numberOfPresets;

	for (size_t i = 0; i < cycles; i++)
	{
		if (manual == true)
			frequency = manualDigits[0] * 10 + manualDigits[1] + manualDigits[2] * 0.1 + manualDigits[3] * 0.01;
		else
			frequency = presetsArray[i][0] * 10 + presetsArray[i][1] + presetsArray[i][2] * 0.1 + presetsArray[i][3] * 0.01;

		periodTime = 1.0 / frequency * 1000;
		onTime = periodTime * duty;
		offTime = periodTime * (1 - duty);

		outputState = true;
		digitalWrite(OUTPUT_PIN, outputState);

		startTime = millis();
		for (size_t i = 0; i < (numberOfPeriods * 2); i++)
		{
			if (outputState == true)
			{
				while (true)
				{
					if ((millis() - startTime) >= onTime)
					{
						outputState = false;
						digitalWrite(OUTPUT_PIN, outputState);
						startTime = millis();
						break;
					}
				}
			}
			else
			{
				while (true)
				{
					if ((millis() - startTime) >= offTime)
					{
						outputState = true;
						digitalWrite(OUTPUT_PIN, outputState);
						startTime = millis();
						break;
					}
				}
			}
		}
		outputState = false;
		digitalWrite(OUTPUT_PIN, outputState);
		if (i != cycles - 1)
		{
			startTime = millis();
			while (true)
			{
				if ((millis() - startTime) >= PULSE_SET_DELAY)
					break;
			}
		}
	}
	homeMenu();
}
