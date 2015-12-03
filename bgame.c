/* This is the binary game's integration with the grid.  */
#include "bgame.h"

int bgame (Display *sw)
{
  cell grid[H][W];
  entity *player, *byte[BYTE_L],  *door1, *door2;
  int in, i, j;
  int goal,res;

  initGrid(grid);
  /* place player */
  player = grid[4][1].foreground = newEntity(passable,'R',1,4);
  /* 8 lightbytes and 8 switches */
  for (i = BYTE_L, j = (W / 2) - (BYTE_L / 2); i > 0; i--, j++) {
    byte[i-1] = newBulb(grid, j, 1);
  }
  // Dividing wall
  for (i = 1; i < W - 1; i++) {
    newWall(grid, i, 3);
  }
  // Creates the boundary walls
  createBoundingWalls(grid);
  delEntity(grid[4][W-1].background);
  delEntity(grid[4][0].background);
  door1 = grid[4][W-1].background = newEntity(impassable,'&',W-1,4);
  door2 = grid[4][0].background = newEntity(impassable,'&',0,4);
  /* layer of floortiles */
  fillGrid(grid);

  drawEntities(sw, grid);
  drawFrame(sw, 20);

  goal = rand()%255;
  printf("try summing %d\n", goal );
  printf("result: %d\n", binResult(byte) );

  /* MAIN LOOP */
	while(!sw->finished){
    res=binResult(byte);
    printf("result %d\n",res);
    if(res==goal){
      changeEntity(door1,'%');
      changePassable(door1,passable);
      changeEntity(door2,'%');
      changePassable(door2,passable);
      printf("you win\n");
    }
    in=input(sw);

    if (grid[player->y][player->x].background == door1) {
      freeEntityMem(grid);  /* free memory */
      bgame(sw);
    }
    if (grid[player->y][player->x].background == door2) {
      freeEntityMem(grid);  /* free memory */
      bgame(sw);
    }
    if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
      move(&grid[player->y][player->x],player->x,player->y,in,grid);
      printGrid(grid);
      updatePlayerfacing(player, in);
    }
    if (in == 9) { /*checks for spacebar */
      if( grid[player->y][player->x].background != NULL
      &&  grid[player->y][player->x].background->type == '-') {
        changeEntity(grid[player->y][player->x].background,'+');
        updateEntities(grid);
        printGrid(grid);
        Mix_PlayChannel( -1, sw->zap, 0 );
      }
	  else if( grid[player->y][player->x].background != NULL
      &&  grid[player->y][player->x].background->type == '+') {
        changeEntity(grid[player->y][player->x].background,'-');
        updateEntities(grid);
        printGrid(grid);
        Mix_PlayChannel( -1, sw->zap, 0 );
      }
    }
    drawEntities(sw, grid);
    drawFrame(sw, 20);
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
  grid[y+3][x].background = newEntity(passable,'-',x,y+3);
  grid[y+3][x].background->pointsto = grid[y][x].background;

  return grid[y][x].background;
}
