/* This is the binary game's integration with the grid.  */
#include "bgame.h"

int bgame (Display *d)
{
  cell grid[H][W];
  entity *player, *byte[BYTE_L],  *door1, *hbutton;
  int in, i, j;
  int goal, res = 0, printHint = 0;

  initGrid(grid);
  
  /* place player */
  player = grid[8][1].foreground = newEntity(passable,P_R1,1,8);
  /* 8 lightbytes and 8 switches */
  j = ((W / 2) - (BYTE_L / 2)) + 2; //set starting point dynamically for bulbs
  for (i = BYTE_L; i > 0; i--, j++) {
    byte[i-1] = newBulb(grid, j, 0);
  }
  makeBoundariesBinary(grid);
  door1 = grid[7][3].background = newEntity(impassable,DOORCLOSED,7,3);
  // door2 = grid[7][3].background = newEntity(impassable,DOORCLOSED,0,8);
  hbutton = grid[7][16].background = newEntity(impassable, BHINTBUTTON,7,16);
  fillGrid(grid); /* layer of floortiles */

  goal = rand()%255;
  
  fprintf(OUTPUT, "try summing %d\n", goal );
  fprintf(OUTPUT, "result: %d\n", binResult(byte) );
  bgameDraw(d, grid, goal, res, printHint);

  /* MAIN LOOP */
	while(!d->finished){


    in=input(d);

    if (grid[player->y][player->x].background == door1) {
      freeEntityMem(grid);  /* free memory */
      return 0;
    }

    if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
      move(&grid[player->y][player->x],player->x,player->y,(direction)in,grid);
      printGrid(grid);

    }
    if (in == 9) { /*checks for spacebar */
      if( grid[player->y-1][player->x].background != NULL
      &&  grid[player->y-1][player->x].background->type == OFFSWITCH) {
        changeEntity(grid[player->y-1][player->x].background, ONSWITCH);
        updateEntities(grid);
        printGrid(grid);
        Mix_PlayChannel( -1, d->zap, 0 );
      }
      else if( grid[player->y-1][player->x].background != NULL
      &&  grid[player->y-1][player->x].background->type == ONSWITCH) {
        changeEntity(grid[player->y-1][player->x].background, OFFSWITCH);
        updateEntities(grid);
        printGrid(grid);
        Mix_PlayChannel( -1, d->zap, 0 );
      }
      else if(grid[player->y-1][player->x].background == hbutton) {
        printHint = !printHint;
        if (hbutton->type == BHINTBUTTON) {
          changeEntity(hbutton, HBUTTON_PR);
        }
        else {
          changeEntity(hbutton, BHINTBUTTON);
        }
        Mix_PlayChannel( -1, d->zap, 0 );
      }
      res=binResult(byte);
    }
    if(res==goal){
      changeEntity(door1,DOOROPEN);
      changePassable(door1,passable);
      // changeEntity(door2,DOOROPEN);
      // changePassable(door2,passable);
      fprintf(OUTPUT, "you win\n");
    }
    bgameDraw(d, grid, goal, res, printHint);

  }
  freeEntityMem(grid);
  return 0;
}

int binResult(entity *byte[BYTE_L])
{
  int i;
  float result=0.0;
  for( i = 0; i < BYTE_L; i++){
    /*Exception for first bit 0=0*/
    if(i==0 && byte[0]->type== OFFLIGHT){
      result=0;
    }
    else if (byte[i]->type == ONLIGHT) {
      result += pow( 2, i);
    }
  }
  return((int)result);
}

entity *newBulb(cell grid[H][W], int x, int y)
{
  grid[y][x].background = newEntity(impassable, OFFLIGHT,x,y);

  grid[y+7][x].background = newEntity(impassable,OFFSWITCH,x,y+7);
  grid[y+7][x].background->pointsto = grid[y][x].background;

  return grid[y][x].background;
}

void makeBoundariesBinary(cell grid[H][W])
{
  // Dividing wall(invisible)
  newLimit(grid,0, 7);
  newLimit(grid,1, 7);
  newLimit(grid,2, 7);
  newLimit(grid,4, 7);
  newLimit(grid,5, 7);
  newLimit(grid,6, 7);
  newLimit(grid,W-1, 7);
  newLimit(grid,W-2, 7);
  newLimit(grid,W-3, 7);


  newLimit(grid,0, 8);
  newLimit(grid,0, 9);
  newLimit(grid,W-1, 8);
  newLimit(grid,W-1, 9);

}
void bgameDraw(Display *d, cell grid[H][W], int goal, int res ,
  int printHint)
{
  char str[STRLEN], instruction[STRLEN], binaryNumber[STRLEN];
  int line = 0;

  drawBackground(d,BG_BIN);
  drawEntities(d, grid);
  
  sprintf(instruction,"TARGET:  %3d", goal);
  sprintf(str, "CURRENT: %3d%c",res,'\0');
  assert(str!=NULL);
  
  line += drawString(d, fontdata, BINTROSTRING, BSCRNSTARTX, 
    BSCRNSTARTY + line, normal);
  line += drawString(d, fontdata, instruction, BSCRNSTARTX,
    BSCRNSTARTY + line, normal);
  
  if (res <= goal) {
    line += drawString(d, fontdata, str, BSCRNSTARTX, BSCRNSTARTY + line, normal);
  }
  else {
    line += drawString(d, fontdata, str, BSCRNSTARTX, BSCRNSTARTY + line, warning); 
    if (countOnBits(res) > countOnBits(goal) ) {
      line += drawString(d, fontdata, "(Too many switches!)", BSCRNSTARTX,
        BSCRNSTARTY + line, warning); 
    }
    else {
      line += drawString(d, fontdata, "(Wrong switch!)", BSCRNSTARTX,
        BSCRNSTARTY + line, warning);    
    }
  }
  if (res == goal) {
      calcBinaryNumber(goal, binaryNumber);
      line += drawString(d, fontdata, binaryNumber, BSCRNSTARTX,
        BSCRNSTARTY + line, normal);  
  }
  drawString(d, fontdata, "EXIT", 175, 420, yellow);
  // drawString(d, fontdata, "EXIT", 875, 420);
  
  if(printHint==1){
    drawString(d, fontdata, "128", 310 + 128, 420, yellow);
    drawString(d, fontdata, "64", 390 + 128, 420, yellow);
    drawString(d, fontdata, "32", 450 + 128, 420, yellow);
    drawString(d, fontdata, "16", 510 + 128, 420, yellow);
    drawString(d, fontdata, "8", 585 + 128, 420, yellow);
    drawString(d, fontdata, "4", 645 + 128, 420, yellow);
    drawString(d, fontdata, "2", 708 + 128, 420, yellow);
    drawString(d, fontdata, "1", 774 + 128, 420, yellow);
  }
  drawFrame(d, REFRESH_RATE);
}

int countOnBits(Uint8 byte)
{
  int cnt = 0;
  
  while (byte > 0) {
    if (byte & 1) {
      cnt++;
    }
    byte = byte >> 1;
  }
  return cnt;
}

void calcBinaryNumber(Uint8 byte, char *binaryNumber)
{ 
  sprintf(binaryNumber,"%s:  %d%d%d%d%d%d%d%d", VICTORYSTRING,
    (byte >> 7) & 1, 
    (byte >> 6) & 1, 
    (byte >> 5) & 1, 
    (byte >> 4) & 1, 
    (byte >> 3) & 1, 
    (byte >> 2) & 1, 
    (byte >> 1) & 1, 
    (byte) & 1);
}