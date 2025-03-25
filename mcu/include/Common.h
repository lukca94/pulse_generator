#include <TFT_eSPI.h>

#define UP_BUTTON 36
#define DOWN_BUTTON 37
#define SELECT_BUTTON 38
#define RETURN_BUTTON 39

extern TFT_eSPI tft;

extern uint16_t currentMenu;
extern uint16_t currentRow;
extern uint16_t firstRow;
extern uint16_t numberOfRows;

// extern u_int8_t selectedNumberPosition;
extern bool enteringNumber;
extern bool pointerState;
// extern bool freezePointer;

extern uint8_t enteredDigits[5];
