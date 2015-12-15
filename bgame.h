#include "game.h"

#define BYTE_L 8

// Calculates the base10 value of the 8-digit binary number
int binResult(entity *byte[BYTE_L]);

/* creates a new bulb-switch pair */
entity *newBulb(cell grid[H][W], int x, int y);

void bgameDraw(Display *d, cell grid[H][W], char* instruction, int res );

void init(cell grid[H][W], entity *player);