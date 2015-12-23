#include "game.h"

#define BYTE_L 8
#define HINTLENGTH 200
#define SCRNSTARTY 60
#define SCRNSTARTX 76
#define INTROSTRING "Try and reach the\ntarget! Each switch\nhas a different\nvalue, with the high\nnumbers on the left.\n"

// Calculates the base10 value of the 8-digit binary number
int binResult(entity *byte[BYTE_L]);

/* creates a new bulb-switch pair */
entity *newBulb(cell grid[H][W], int x, int y);

void bgameDraw(Display *d, cell grid[H][W], int goal, int res , int printHint);

void init(cell grid[H][W], entity *player);

void makeBoundariesBinary(cell grid[H][W]);
