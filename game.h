#include <assert.h>
#ifndef GAMEH
  #define GAMEH

  #include "input.h"
  #include <time.h>
  void intro(Display *d);
  int binaryGame(void);
  int quizGame(Display *sw);
  int gridmain(Display *sw);
  int input(Display *sw);
  int bgame(Display *sw);
  void mediaLoad(Display *d);
  void makeBoundariesLobby(cell grid[H][W]);
  void lobbyDraw(Display *d, cell grid[H][W]);
  void GameOver(Display *d, int *in);

#define NUMLINES 42
#define SCREENSIZE 14

typedef struct  scenario {
  char line[100];
  int print_line;
} Scenario;
#endif
