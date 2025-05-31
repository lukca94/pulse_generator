#include <Arduino.h>

#include "../../include/Common.h"
#include "Menus.h"

#define PULSE_SET_DELAY 5000

bool manual = false;
bool outputState = false;
unsigned long startTime = 0;
unsigned long delayTime = 0;
unsigned long pulseTime = 0;
double periodTime;
unsigned long onTime;
unsigned long offTime;
uint8_t cycles = 0;
double frequency = 0;

void pulseGeneration(uint16_t duration, double frequency, double duty)
{
	periodTime = 1.0 / frequency * 1000;
	onTime = periodTime * duty;
	offTime = periodTime * (1 - duty);
	duration *= 1000;

	outputState = true;
	pulseTime = millis();
	digitalWrite(OUTPUT_PIN, outputState);
	startTime = millis();
	while ((millis() - startTime) < duration)
	{
		if (outputState == true)
		{
			while (true)
			{
				if ((millis() - pulseTime) >= onTime)
				{
					outputState = false;
					digitalWrite(OUTPUT_PIN, outputState);
					pulseTime = millis();
					break;
				}
			}
		}
		else
		{
			while (true)
			{
				if ((millis() - pulseTime) >= offTime)
				{
					outputState = true;
					digitalWrite(OUTPUT_PIN, outputState);
					pulseTime = millis();
					break;
				}
			}
		}
	}
	outputState = false; // ensure LOW at the end
	digitalWrite(OUTPUT_PIN, outputState); 
}

void run()
{
	uint8_t cycles;
	double frequency;
	double duty = (double)(dutyDigits[0] * 10 + dutyDigits[1]) / 100;
	uint16_t duration = durationDigits[0] * 100 + durationDigits[1] * 10 + durationDigits[2];

	waitingMenu();
	while (true) // wait for LOW
	{
		if (digitalRead(INPUT_PIN) == LOW)
			break;
	}
	while (true) // wait for HIGH
	{
		if (digitalRead(INPUT_PIN) == HIGH)
			break;
	}

	generatingMenu();
	if (manual == true)
	{
		frequency = manualDigits[0] * 10 + manualDigits[1] + manualDigits[2] * 0.1 + manualDigits[3] * 0.01;
		pulseGeneration(duration, frequency, duty);
	}
	else
	{
		for (size_t i = 0; i < numberOfPresets; i++)
		{
			frequency = presetsArray[i][0] * 10 + presetsArray[i][1] + presetsArray[i][2] * 0.1 + presetsArray[i][3] * 0.01;
			pulseGeneration(duration, frequency, duty);

			delayTime = millis();
			while (true)
			{
				if ((millis() - delayTime) >= PULSE_SET_DELAY)
					break;
			}
		}
	}

	startTime = millis();

	homeMenu();
}
