#include "game.h"
#include <assert.h>

 
#define BYTE_L 8
#define BHINTLENGTH 200
#define BSCRNSTARTY 60
#define BSCRNSTARTX 76
#define BINTROSTRING "Try and reach the\ntarget! Each switch\nhas a different\nvalue, with the high\nnumbers on the left.\n"
#define STRLEN 64 /*str size for string to hold binary number */
#define VICTORYSTRING "OUTPUT"

// Calculates the base10 value of the 8-digit binary number
int binResult(entity *byte[BYTE_L]);

/* creates a new bulb-switch pair */
entity *newBulb(cell grid[H][W], int x, int y);

void bgameDraw(Display *d, cell grid[H][W], int goal, int res , int printHint);

void init(cell grid[H][W], entity *player);

void makeBoundariesBinary(cell grid[H][W]);

//counts how many bits are set to 1 in a byte
int countOnBits(Uint8 byte);

//create a string of 8 1s or 0s
void calcBinaryNumber(Uint8 byte, char *num);
