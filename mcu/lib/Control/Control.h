#ifndef CONTROL_H
#define CONTROL_H

#include <stdint.h> 



void drawPointer();
void drawUnderline();

void lineChange(uint8_t direction);

void numberEntry(uint8_t direction);

void numberChange(uint8_t direction);

void drawScrollableMenu();
void drawScrollableRemoveMenu();

#endif // CONTROL_H
