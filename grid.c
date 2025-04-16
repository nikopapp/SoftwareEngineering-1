#include "grid.h"

void testGrid();

int gridmain()
{
  // testGrid();
  return 0;
}

void initGrid(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      grid[HCnt][WCnt].foreground = NULL;
      grid[HCnt][WCnt].background = NULL;
      /* initialise the grid cells to contain no entities */
    }
  }
}


cell *getNeighbour(int x, int y, direction dir, cell grid[H][W])
{
  int px, py;
  cell *c;

  px = x;
  py = y;

  directionsTrans(dir,&px,&py);
  c = &grid[py][px];

  return c;
}


void directionsTrans(direction dir, int *x, int *y)
{
  switch(dir){
    case LEFT:
      (*x)--;
      break;
    case RIGHT:
      (*x)++;
      break;
    case UP:
      (*y)--;
      break;
    case DOWN:
      (*y)++;
      break;
  }
}
