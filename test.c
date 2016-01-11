#include "test.h"
#define PASS "\x1B[32mPASSED\x1B[0m"
#define FAIL "\x1B[31mFAILED\x1B[0m"


int main(void)
{
  test();
  return SUCCESS;
}
int test(void)
{
  int i=0, cnt[20], totErrors=0,totTests=8;
  char format[35]="---------------------------------\n";
  printf("\n\nTESTING\n%s",format );
  printf("%d. ",i+1 );
  cnt[i++]=TEST_newDisplay();
  printf("%d. ",i+1 );
  cnt[i++]=TEST_closeDisplay();
  printf("%d. ",i+1 );
  cnt[i++]=TEST_initGrid();
  printf("%d. ",i+1 );
  cnt[i++]=TEST_updatePlayerfacing();
  printf("%d. ",i+1 );
  cnt[i++]=TEST_fillGrid();
  printf("%d. ",i+1 );
  cnt[i++]=TEST_input();
  printf("%d. ",i+1 );
  cnt[i++]=TEST_getNeighbour();
  printf("%d. ",i+1 );
  cnt[i++]=TEST_directionsTrans();
  for(i=0;i<totTests;i++){
    totErrors+=cnt[i];
  }

    printf("%s%d of %d %s %s\n\n",format,totTests-totErrors, totTests,"tests", "PASSED" );
  if(totErrors==0){
    return SUCCESS;
  }
  else{
    return ERROR;
  }
}
int TEST_fillGrid()
{
  cell grid[H][W];
  initGrid(grid);
  fillGrid(grid);
  if(grid[rand()%H][rand()%W].background->ispassable!=passable){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
int TEST_updatePlayerfacing()
{
  entity *e=NULL;
  e=newEntity(10,10,10,10);
  direction direct=LEFT;
  updatePlayerfacing(e,direct,DOWN);
  if(e->x!=10){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
int TEST_newDisplay()
{
  Display *d;
  d=newDisplay();
  if(d==NULL){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
int TEST_input()
{
  int value=0;
  Display *d;
  d=newDisplay();
  value = input(d);
  if(value!=0){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
int TEST_closeDisplay()
{
  Display *d;
  d=newDisplay();
  closeDisplay(d);
  if(d!=NULL){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS);
    return SUCCESS;
  }
}

int TEST_initGrid()
{
  cell grid[H][W];
  initGrid(grid);
  if(grid[5][5].foreground!=NULL||grid[5][5].background!=NULL){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
int TEST_getNeighbour()
{
  int x=5, y=5;
  direction dir=LEFT;
  cell grid[H][W], *testCell;
  initGrid(grid);
  fillGrid(grid);
  testCell=getNeighbour(x, y, dir, grid);
  if(testCell->background!=grid[y][x-1].background){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}

int TEST_directionsTrans()
{
  int x,y;
  cell grid[H][W];
  initGrid(grid);
  x=grid[5][1].background->x;
  y=grid[5][0].background->y;
  directionsTrans(LEFT, &x, &y);
  if(x!=grid[5][0].background->x){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
/*

int TEST_newBulb(){
  entity bulb;
  cell grid[H][W];
  int x=0, y=0;
  initGrid(grid);
  fillGrid(grid);
  bulb=newBulb(grid[y][x]);
  if(entity.ispassable!=1 || entity.offlight!='0' || enity.x!=x || entity.y !=y){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}

int TEST_makeBoundariesBinary()
{
  cell grid[H][W];
  initGrid(grid);
  makeBoundariesBinary(grid);
  if(grid[0][7].ispassable!=1){
    printf("%23s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%23s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
*/
// encryption, game binary game, grid.c
