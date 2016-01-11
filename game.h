#ifndef GAMEH
#define GAMEH

#define OUTPUT stdout
#define OUTPUTERR stderr

#include "input.h"

int binaryGame(void);
int encryption(Display *sw);
int gridmain(Display *sw);
int input(Display *sw);
int bgame(Display *sw);
void mediaLoad(Display *d);
void makeBoundariesLobby(cell grid[H][W]);
void lobbyDraw(Display *d, cell grid[H][W]);

#endif