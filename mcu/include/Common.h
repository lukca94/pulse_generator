#include <TFT_eSPI.h>

#define UP_BUTTON 36
#define DOWN_BUTTON 37
#define SELECT_BUTTON 38
#define RETURN_BUTTON 39

#define NUMBER_OF_PRESETS 20

#define HOME_MENU 1
#define MANUAL_MENU 2
#define PRESETS_MENU 3
#define PRESETS_REMOVING_MENU 4
#define PERIODS_MENU 5
#define DUTY_MENU 6

#define TEXT_BEGINNING 30
#define POINTER_BEGINNING 10
#define FIRST_LINE 18
#define SECOND_LINE 57
#define THIRD_LINE 96

extern TFT_eSPI tft;

extern uint16_t currentMenu;
extern uint16_t currentRow;
extern uint16_t firstRow;
extern uint16_t numberOfRows;

extern uint16_t topShownLine;

// extern u_int8_t selectedNumberPosition;
extern bool enteringNumber;
extern bool pointerState;
// extern bool freezePointer;

extern uint8_t manualDigits[4];
extern int16_t presetsArray[NUMBER_OF_PRESETS][4];
extern uint8_t dutyDigits[3];
extern uint8_t periodDigits[3];

extern uint16_t numberOfPresets;

extern uint8_t addPosition;
extern uint8_t removePosition;
