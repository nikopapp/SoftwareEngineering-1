#include "game.h"

#define BYTE_L 8

int binResult(entity *byte[BYTE_L]);

/* creates a new bulb-switch pair */
entity *newBulb(cell grid[H][W], int x, int y);

entity *newWall(cell grid[H][W], int x, int y);
