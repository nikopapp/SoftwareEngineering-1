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
  int i=0,j, cnt[20], totErrors=0;
  char format[40]="------------------------------------\n";

  printf("\n\nTESTING\n%s",format );
  printf("\ndisplay.c\n%s",format );
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_newDisplay();
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_closeDisplay();
  printf("\ngrid.c\n%s",format );
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_initGrid();
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_getNeighbour();
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_directionsTrans();
  printf("\ninput.c\n%s",format );
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_input();
  printf("\nentity.c\n%s",format );
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_fillGrid();
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_updateEntities();
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_updatePlayerfacing();
  printf("\nbgame.c\n%s",format );
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_newBulb();
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_makeBoundariesBinary();
  printf("\nquizGame.c\n%s",format );
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_enc_getHint();
  printf("%2d. ",i+1 );
  cnt[i++]=TEST_enc_updateWord();
  for(j=0;j<i;j++){
    totErrors+=cnt[j];
  }

    printf("%s%d of %d %s %s\n\n",format,i-totErrors, i,"tests", "PASSED" );
  if(totErrors==0){
    return SUCCESS;
  }
  else{
    return ERROR;
  }
}
// Testing display.c
int TEST_newDisplay()
{
  Display *d;
  d=newDisplay();
  if(d==NULL){
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
int TEST_closeDisplay()
{
  Display *d;
  d=newDisplay();
  closeDisplay(d);
  if(d!=NULL){
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS);
    return SUCCESS;
  }
}
// Testing grid.c
int TEST_fillGrid()
{
  cell grid[H][W];
  initGrid(grid);
  fillGrid(grid);
  if(grid[rand()%H][rand()%W].background->ispassable!=passable){
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
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
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
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
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
    return SUCCESS;
  }
}

int TEST_initGrid()
{
  cell grid[H][W];
  initGrid(grid);
  if(grid[5][5].foreground!=NULL||grid[5][5].background!=NULL){
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
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
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
    return SUCCESS;
  }
}

int TEST_directionsTrans()
{
  int x,y;
  cell grid[H][W];
  initGrid(grid);
  fillGrid(grid);
  x=grid[5][1].background->x;
  y=grid[5][0].background->y;
  directionsTrans(LEFT, &x, &y);
  if(x!=grid[5][0].background->x){
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
    return SUCCESS;
  }
}


int TEST_newBulb(){
  cell grid[H][W];
  int x=0, y=0;
  entity *bulb=newBulb(grid, x, y);
  initGrid(grid);
  fillGrid(grid);
  if(bulb->ispassable!=1 || bulb->x!=x || bulb->y !=y){
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
    return SUCCESS;
  }
}

int TEST_makeBoundariesBinary()
{
  cell grid[H][W];
  // initGrid(grid);
  makeBoundariesBinary(grid);
  if(grid[0][7].background->ispassable!=0){
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
    return SUCCESS;
  }
}
int TEST_updateEntities()
{
  cell grid[H][W];
  initGrid(grid);
  newBulb(grid,1,1);
  assert(grid[8][1].background->type==OFFSWITCH);
  updateEntities(grid);
  if(grid[8][1].background->type==ONSWITCH){
    printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
  else{
    printf("%25s %s\n",__func__, PASS );
    return SUCCESS;
  }


}

// Testing quizGame.c

int TEST_enc_updateWord()
{
   /*test if the word "elves" will be updated
     from the grid to a string variable*/
  cell grid[H][W];
  /* need to give an init word cause enc_updateWord
     uses strlen */
  char word[LENGTH]={"tests"};
  int i;
  word[5] = '\0';//to mark the end of string

  for (i=0; i<5; i++){
     grid[0][i].background = (entity *)malloc(sizeof(entity));
 }
 // pass the word on the grid
  grid[0][0].background->type = 'e';
  grid[0][1].background->type = 'l';
  grid[0][2].background->type = 'v';
  grid[0][3].background->type = 'e';
  grid[0][4].background->type = 's';
  enc_updateWord(grid, 0, 0, word);
  if(strcmp(word, "elves") == 0){
    printf("%25s %s\n",__func__, PASS );
    return SUCCESS;
  }
  else{
     printf("%25s %s\n",__func__, FAIL );
    return ERROR;
  }
}

int TEST_enc_getHint()
{
   char hint[HINTLENGTH];
   int found_letter = ERROR, i, errors=0;
   // set all hint chars to NULL
   for (i=0; i<HINTLENGTH; i++){
      hint[i] = '\0';
   }
   enc_getHint(hint, 0);
   // search if hint is still empty
   for (i=0; i<HINTLENGTH; i++){
      if( hint[i] != '\0'){
         found_letter = SUCCESS;
         break;
      }
   }
   /* now I will also check some random lines
      to see if I get the right hints*/
   if(strcmp(hint, "Handles memory between Hard Disk and CPU") != 0){
      errors++;
   }
   enc_getHint(hint, 8);
   if(strcmp(hint, "Think of it as a computer in your hand.") != 0){
      errors++;
   }
   enc_getHint(hint, 19);
   if(strcmp(hint, "Legolas, Erwin, Tauriel.. You know them!") != 0){
      errors++;
   }
   if ((errors == 0) && (found_letter == SUCCESS)){
     printf("%25s %s\n",__func__, PASS );
     return SUCCESS;
   }
   else{
      printf("%25s %s\n",__func__, FAIL );
     return ERROR;
   }
}


//  game binary game, grid.c
