#include <stdlib.h>
#include <stdio.h>

#define H 3
#define W 3
#define ENTITIES 5

typedef enum direction { LEFT, RIGHT, UP, DOWN } direction;

typedef struct entity {
  int ispassable;
  char type;
} entity;

typedef struct cell {
  entity *elist[ENTITIES];
  int listmax;
} cell;

void directionsTrans(direction dir, int * x, int * y);
cell getNeighbour(int x, int y, direction dir,  cell grid[H][W]);
void initGrid(cell grid[H][W]);
entity *newEntity(int ispassable, char type);
void fillGrid(cell grid[H][W]);
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

cell getNeighbour(int x, int y, direction dir,  cell grid[H][W])
{
  int *px, *py;

  *px = x;
  *py = y;

  directionsTrans(dir, px, py);
  return grid[*py][*px];
}

void directionsTrans(direction dir, int * x, int * y){
  switch(dir){
    case LEFT: x--;
    case RIGHT: x++;
    case UP: y++;
    case DOWN: y--;
  }
}
