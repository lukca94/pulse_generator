#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h>

void drawPointer();
void drawUnderline();

void lineChange(uint8_t direction);
void numberEntry(uint8_t direction, uint8_t numberOfDigits);
void numberChange(uint8_t direction);

void drawNumberLine(int16_t *number, uint8_t lineIndex, uint8_t numberVectorLenght);

void drawScrollableMenu();
void drawScrollableRemoveMenu();

#endif // CONTROL_H
