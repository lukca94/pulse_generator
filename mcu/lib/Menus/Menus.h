#include "../../include/Free_Fonts.h"

#ifndef MENUS_H
#define MENUS_H

#define UP 0
#define DOWN 1

#define TEXT_BEGINNING 30
#define POINTER_BEGINNING 10
#define FIRST_LINE 18
#define SECOND_LINE 57
#define THIRD_LINE 96

void homeMenu();
void manualMenu();
void presetMenu();

void drawPointer();

void lineChange(int direction);
void numberEntry();

#endif // MENUS_H
