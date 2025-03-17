#include "../../include/Free_Fonts.h"

#ifndef MENUS_H
#define MENUS_H

#define UP 0
#define DOWN 1

#define SELECT 0
#define RETURN 1

#define TEXT_BEGINNING 30
#define POINTER_BEGINNING 10
#define FIRST_LINE 18
#define SECOND_LINE 57
#define THIRD_LINE 96

void homeMenu();
void manualMenu();
void presetMenu();

void drawPointer();

void lineChange(u_int8_t direction);

void numberEntry(u_int8_t direction);
void drawUnderline();
void numberChange(u_int8_t direction);

#endif // MENUS_H
