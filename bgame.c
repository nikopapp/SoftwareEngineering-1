/* This is the binary game's integration with the grid.  */
#include "bgame.h"

int bgame (Display *d)
{
  cell grid[H][W];
  entity *player, *byte[BYTE_L],  *door1, *door2;
  int in, i, j;
  int goal,res=0;
  char instruction[16];

  initGrid(grid);
  /* place player */
  player = grid[8][1].foreground = newEntity(passable,'R',1,8);
  /* 8 lightbytes and 8 switches */
  for (i = BYTE_L, j = (W / 2) - (BYTE_L / 2); i > 0; i--, j++) {
    byte[i-1] = newBulb(grid, j, 4);
  }
  // Dividing wall(invisible)
  for (i = 1; i < W - 1; i++) {
    newLimit(grid, i, H - 1);
  }
  newLimit(grid,0, 7);
  newLimit(grid,1, 7);
  newLimit(grid,2, 7);
  newLimit(grid,4, 7);  
  newLimit(grid,W-1, 7);
  newLimit(grid,W-2, 7);
  newLimit(grid,W-3, 7);
  newLimit(grid,W-5, 7);
  
  newLimit(grid,0, 8);
  newLimit(grid,0, 9);
  newLimit(grid,W-1, 8);
  newLimit(grid,W-1, 9);
 
  door1 = grid[7][W-4].background = newEntity(impassable,'&',W-1,8);
  door2 = grid[7][3].background = newEntity(impassable,'&',0,8);
  /* layer of floortiles */
  fillGrid(grid);
  
  bgameDraw(d, grid, instruction, res);
  
  goal = rand()%255;
  sprintf(instruction,"Try summing %d", goal);
  printf("try summing %d\n", goal );
  printf("result: %d\n", binResult(byte) );

  /* MAIN LOOP */
	while(!d->finished){

    in=input(d);
    if(res==goal){
      changeEntity(door1,'%');
      changePassable(door1,passable);
      changeEntity(door2,'%');
      changePassable(door2,passable);
      printf("you win\n");
    }

    if (grid[player->y][player->x].background == door1) {
        /* free memory */
      return 0;
    }
    if (grid[player->y][player->x].background == door2) {
        /* free memory */
      return 0;
    }
    if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
      move(&grid[player->y][player->x],player->x,player->y,in,grid);
      printGrid(grid);
      updatePlayerfacing(player, in);
    }
    if (in == 9) { /*checks for spacebar */
      if( grid[player->y-1][player->x].background != NULL
      &&  grid[player->y-1][player->x].background->type == '-') {
        changeEntity(grid[player->y-1][player->x].background,'+');
        updateEntities(grid);
        printGrid(grid);
        Mix_PlayChannel( -1, d->zap, 0 );
      }
	  else if( grid[player->y-1][player->x].background != NULL
      &&  grid[player->y-1][player->x].background->type == '+') {
        changeEntity(grid[player->y-1][player->x].background,'-');
        updateEntities(grid);
        printGrid(grid);
        Mix_PlayChannel( -1, d->zap, 0 );
      }
      res=binResult(byte);
    }
    bgameDraw(d, grid, instruction, res);

  }
  return 0;
}

int binResult(entity *byte[BYTE_L])
{
  int i;
  float result=0.0;
  for( i = 0; i < BYTE_L; i++){
    /*Exception for first bit 0=0*/
    if(i==0 && byte[0]->type=='0'){
      result=0;
    }
    else if (byte[i]->type == '1') {
      result += pow( 2, i);
    }
  }
  return((int)result);
}

entity *newBulb(cell grid[H][W], int x, int y)
{
  grid[y][x].background = newEntity(impassable,'0',x,y);
  grid[y+3][x].background = newEntity(impassable,'-',x,y+3);
  grid[y+3][x].background->pointsto = grid[y][x].background;

  return grid[y][x].background;
}


void bgameDraw(Display *d, cell grid[H][W], char* instruction, int res )
{
  char str[3];
  
  drawBackground(d,1);
  drawEntities(d, grid);
  
  sprintf(str, "%d%c",res,'\0');
  assert(str!=NULL);
  
  drawString(d, fontdata, instruction, 200, 100);
  drawString(d, fontdata, str, 950, 400);
  drawString(d, fontdata, "EXIT", 180, 380);
  drawString(d, fontdata, "EXIT", 180, 380);
  drawFrame(d, 20);
}