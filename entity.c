#include "entity.h"

entity *newEntity(int ispassable, char type, int x, int y)
{
  entity *e = (entity *)malloc(sizeof(entity));
  e-> x = x;
  e-> y = y;
  e->type = type;
  e->ispassable = ispassable;
  return e;
}

void changeEntity(entity *e, char newtype)
{
  e->type = newtype;
}

void changePassable(entity *e, int ispassable) {
  e->ispassable = ispassable;
}


void delEntity(entity *e)
{
  free(e);
}

void updateEntities(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){

      /* logic for lighbulbs and switches */
      if (grid[HCnt][WCnt].background != NULL /*is there an object */
      &&  grid[HCnt][WCnt].background->pointsto != NULL) { /*is switch connected */
        /*is the object an on switch */
        if (grid[HCnt][WCnt].background->type == ONSWITCH) {
          changeEntity(grid[HCnt][WCnt].background->pointsto, ONLIGHT);
        }
        /*is the object an off switch */
        if (grid[HCnt][WCnt].background->type == OFFSWITCH) {
          changeEntity(grid[HCnt][WCnt].background->pointsto, OFFLIGHT);
        }
      }
    }
  }
}

void move(cell *c, int x, int y, direction dir, cell grid[H][W]) {

  static int count = 0;
  unsigned int dir_prev = 0;
  
  if (isEdge(x,y,dir)) {
    return;
  }
  cell *cnew = getNeighbour(x,y,dir,grid);

  if (cnew->background->ispassable == impassable) {
    return;
  }
  int px, py;

  px = x;
  py = y;

  directionsTrans(dir,&px,&py);
  
  count = next_movement(count, &dir_prev, dir);
  updatePlayerfacing(c->foreground, dir, count);
  
  c->foreground->x = px;
  c->foreground->y = py;

  cnew->foreground = c->foreground;
  c->foreground = NULL;
}

int isEdge(int x, int y, direction dir) {

  printf("x: %d y: %d", x, y);
  if ( x == (W - 1)&& dir == RIGHT ) {
    printf("x>edge\n");
    return 1;
  }
  else if ( x == 0 && dir == LEFT) {
    printf("x<0\n");
    return 1;
  }
  else if ( y == (H - 1) && dir == DOWN) {
    printf("y>h-1\n");
    return 1;
  }
  else if ( y == 0 && dir == UP) {
    printf("y<0\n");
    return 1;
  }
  else{
    return 0;
  }
}

int next_movement(int count, unsigned int *dir_prev, direction dir)
{

  if( dir == *dir_prev){// same arrow key
    count++;
  }// we are going to use 'count' for moving animation inside the updatePlayerfacing function
  else if( dir != *dir_prev ){// different arrow key
    *dir_prev = dir;
    count = 0;
  }
  return count;
}

void updatePlayerfacing(entity *player, direction dir, int count)
{
  switch(dir){
    case LEFT:
       if (count % 3 == 0){  changeEntity(player,P_L1); }
       if (count % 3 == 1){  changeEntity(player,P_L2); }
       if (count % 3 == 2){  changeEntity(player,P_L3); }
       break;
    case RIGHT:
      if (count % 3 == 0){  changeEntity(player,P_R1); }
      if (count % 3 == 1){  changeEntity(player,P_R2); }
      if (count % 3 == 2){  changeEntity(player,P_R3); }
      break;
    case UP:
       if (count % 3 == 0){  changeEntity(player,P_UP1); }
       if (count % 3 == 1){  changeEntity(player,P_UP2); }
       if (count % 3 == 2){  changeEntity(player,P_UP3); }
       break;
    case DOWN:
       if (count % 3 == 0){  changeEntity(player,P_DOWN1); }
       if (count % 3 == 1){  changeEntity(player,P_DOWN1); }
       if (count % 3 == 2){  changeEntity(player,P_DOWN1); }
       break;
  }
}

void freeEntityMem(cell grid[H][W])
{
  int HCnt, WCnt;

  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      if (grid[HCnt][WCnt].foreground != NULL) {
        free(grid[HCnt][WCnt].foreground);
      }
      if (grid[HCnt][WCnt].background != NULL) {
        free(grid[HCnt][WCnt].background);
      }
    }
  }
  initGrid(grid);
}

void fillGrid(cell grid[H][W])
{
  int HCnt, WCnt;
  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      if (grid[HCnt][WCnt].background == NULL) {
        grid[HCnt][WCnt].background = newEntity(passable,FLOOR ,WCnt,HCnt);
      }
    }
  }
}

void printGrid(cell grid[H][W])
{
  int HCnt, WCnt;

  printf("\n");
  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      if (grid[HCnt][WCnt].foreground != NULL) {
        printf("%c ", grid[HCnt][WCnt].foreground->type);
      }
      else if (grid[HCnt][WCnt].background != NULL) {
        printf("%c ", grid[HCnt][WCnt].background->type);
      }
    }
    printf("\n");
  }
}

entity *newLimit(cell grid[H][W], int x, int y)
{
  grid[y][x].background = newEntity(impassable,WALL,x,y);
  return grid[y][x].background;
}
