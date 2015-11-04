#include <stdlib.h>
#include <stdio.h>

#define H 3
#define W 3
#define ENTITIES 5 /* max num of entities per cell */

typedef enum direction { LEFT, RIGHT, UP, DOWN } direction;

typedef struct entity {
  int ispassable; /* walls cannot be walked through - floors can */
  char type; /* for display when printing grid to terminal */
  char* name; /* name of entity - maybe unneeded */
} entity;

typedef struct cell {
  entity *elist[ENTITIES]; /* a list of all the entities in a cell */
  int listmax; /* the current amount of entities in a cell */
} cell;

void directionsTrans(direction dir, int * x, int * y);

/* returns a pointer to the neighbouring cell in direction dir */
cell *getNeighbour(int x, int y, direction dir,  cell grid[H][W]);

/* sets listmax to zero in all cells - i.e. makes them empty */
void initGrid(cell grid[H][W]);

/* call this to create a new entity.  uses malloc and needs a free() still */
entity *newEntity(int ispassable, char type);

/* placeholder function to fill grid with floor entities */
void fillGrid(cell grid[H][W]);

/* placeholder function to print grid to terminal.
only prints one layer of the grid */
void printGrid(cell grid[H][W], int layer);

int main(void)
{
  cell grid[H][W];

  initGrid(grid);
  fillGrid(grid);

  grid[1][1].elist[grid[1][1].listmax] = newEntity(0,'r');
  grid[1][1].listmax++;

  printGrid(grid,0);
  printf("\n");
  printGrid(grid,1);

  return 0;
}

void initGrid(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<H; WCnt++){
      grid[HCnt][WCnt].listmax = 0;
    }
  }
}

entity *newEntity(int ispassable, char type)
{
  entity *e = malloc(sizeof(entity));

  e->type = type;
  e->ispassable = ispassable;
  return e;
}

void printGrid(cell grid[H][W], int layer)
{
  int HCnt, WCnt;
  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      if (grid[HCnt][WCnt].listmax > layer) {
        printf("%c", grid[HCnt][WCnt].elist[layer]->type);
      }
    }
    printf("\n");
  }
}

void fillGrid(cell grid[H][W]){
  int HCnt, WCnt;
  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      grid[HCnt][WCnt].elist[grid[HCnt][WCnt].listmax] = newEntity(0,'.');
      grid[HCnt][WCnt].listmax++;
    }
  }
}

cell *getNeighbour(int x, int y, direction dir,  cell grid[H][W])
{
  int px, py;
  cell *c;

  px = x;
  py = y;
  directionsTrans(dir, &px, &py);
  c = &grid[py][px];

  return c;
}

void directionsTrans(direction dir, int *x, int *y){
  switch(dir){
    case LEFT: x--;
    case RIGHT: x++;
    case UP: y++;
    case DOWN: y--;
  }
}
