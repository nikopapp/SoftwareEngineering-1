#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define H 12
#define W 12

typedef enum direction { LEFT, RIGHT, UP, DOWN } direction;
typedef enum layer { background, foreground } layer;
typedef enum ispassable { passable, impassable } ispassable;

typedef struct entity {
  int ispassable; /* walls cannot be walked through - floors can */
  char type; /* for display when printing grid to terminal */
  struct entity *pointsto; /* this allows for connections between entities - such as from a switch to a lightbulb */
  int ison; /* 1 is on, 0 is off - for switches, lightbulbs */
} entity;

/* this and other entity-related stuff could probably be moved
to an entity.c file */

typedef struct cell {
  /* i have simplified the cells of the grid to just contain 2 possible
  entities - one at the front and one at the back.
  this should make it much simpler to add a new object*/
  entity *foreground; /*this is the foreground object - eg, the player, walls */
  entity *background; /*this is the background object - eg, the floor, a switch, a lightbulb, a wire */
} cell;

void directionsTrans(direction dir, int *x, int *y);

/* changes the type of an entity (a char).  this type is used to check in
the action loop what actions to take*/
void changeEntity(entity *e, char newtype);

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
void printGrid(cell grid[H][W], layer layer);

/* frees the memory used by malloc in the newEntity() function*/
void freeEntityMem(cell grid[H][W]);

void testGrid();

int main(void)
{
  srand(time(NULL));
  testGrid();
  return 0;
}

void initGrid(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<H; WCnt++){
      grid[HCnt][WCnt].foreground = NULL;
      grid[HCnt][WCnt].background = NULL;
      /* initialise the grid cells to contain no entities */
    }
  }
}

void freeEntityMem(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<H; WCnt++){
      free(grid[HCnt][WCnt].foreground);
      free(grid[HCnt][WCnt].background);
    }
  }
  initGrid(grid);
}

entity *newEntity(int ispassable, char type)
{
  entity *e = malloc(sizeof(entity));

  e->type = type;
  e->ispassable = ispassable;
  return e;
}

cell *getNeighbour(int x, int y, direction dir,  cell grid[H][W])
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
      (*y)++;
      break;
    case DOWN:
      (*y)--;
      break;
  }
}

void changeEntity(entity *e, char newtype)
{
  e->type = newtype;
}

void updateEntities(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<H; WCnt++){

      /* logic for lighbulbs and switches */
      if (grid[HCnt][WCnt].background != NULL /*is there an object */
      &&  grid[HCnt][WCnt].background->pointsto != NULL /*is switch connected */
      && (grid[HCnt][WCnt].background->type == '-'
      ||  grid[HCnt][WCnt].background->type == '+' )) { /*is the object a switch */
        if (grid[HCnt][WCnt].background->ison == 1) {
          changeEntity(grid[HCnt][WCnt].background->pointsto,'1');
          grid[HCnt][WCnt].background->pointsto->ison = 1;
        }
        if (grid[HCnt][WCnt].background->ison == 0) {
          changeEntity(grid[HCnt][WCnt].background->pointsto,'0');
          grid[HCnt][WCnt].background->pointsto->ison = 0;
        }
      }

    }
  }
}

void testGrid() {
  int i, rc, rp;

  cell grid[H][W];
  cell *tmp;

  initGrid(grid);
  fillGrid(grid);

  /* foreground layer test */
  grid[6][6].foreground = newEntity(passable,'r');

  /* lightbulbs */
  grid[1][2].background = newEntity(passable,'0');
  grid[1][3].background = newEntity(passable,'0');
  grid[1][4].background = newEntity(passable,'0');
  grid[1][5].background = newEntity(passable,'0');
  grid[1][6].background = newEntity(passable,'0');
  grid[1][7].background = newEntity(passable,'0');
  grid[1][8].background = newEntity(passable,'0');
  grid[1][9].background = newEntity(passable,'0');

    /* switches */
  grid[4][2].background = newEntity(passable,'-'); /* off switches - '+' is on*/
  grid[4][3].background = newEntity(passable,'-');
  grid[4][4].background = newEntity(passable,'-');
  grid[4][5].background = newEntity(passable,'-');
  grid[4][6].background = newEntity(passable,'-');
  grid[4][7].background = newEntity(passable,'-');
  grid[4][8].background = newEntity(passable,'-');
  grid[4][9].background = newEntity(passable,'-');

  printGrid(grid, background);

  /* test for the update entities function */
  for(i = 0; i < 10; i++) {
    rp = rand()%2;
    rc = (rand()%8) + 2;

    grid[4][rc].background->ison = rp;
    grid[4][rc].background->pointsto = grid[1][rc].background;
    if (grid[4][rc].background->ison == 1) {
      changeEntity(grid[4][rc].background,'+');
    }
    if (grid[4][rc].background->ison == 0) {
      changeEntity(grid[4][rc].background,'-');
    }

    printf("\nNEXTEST:\n\nswitch %d has changed\n", rc-1);
    grid[4][rc].background->pointsto = grid[1][rc].background;
    updateEntities(grid);

    printf("\nbulb %d has changed\n", rc-1);
    printGrid(grid, background);
  }

  /*foreground test */
  printGrid(grid, foreground);

  /*getNeighbour test */
  tmp = getNeighbour(5,6,RIGHT,grid);
  printf("\n\nCHAR:%c\n\n",tmp->foreground->type);

  freeEntityMem(grid);
}

void printGrid(cell grid[H][W], layer layer)
{
  int HCnt, WCnt;
  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      if (layer == background
      && grid[HCnt][WCnt].background != NULL) {
        printf("%c ", grid[HCnt][WCnt].background->type);
      }
      if (layer == foreground
      && grid[HCnt][WCnt].foreground != NULL) {
        printf("%c ", grid[HCnt][WCnt].foreground->type);
      }
      else if (layer == foreground
      && grid[HCnt][WCnt].foreground == NULL) {
        printf("%c ",' ');
      }
    }
    printf("\n");
  }
}

void fillGrid(cell grid[H][W])
{
  int HCnt, WCnt;
  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      grid[HCnt][WCnt].background = newEntity(0,'.');
    }
  }
}
