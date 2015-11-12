#include "game.h"

int bgame (SDL_Simplewin *sw)
{
  cell grid[H][W];
  entity *player;
  int in;
  
  initGrid(grid);
  /* place player */
  
  player = grid[6][6].foreground = newEntity(passable,'@',6,6);
  
  /* 8 lightbulbs and 8 switches */
  newBulb(grid, 2, 1);
  newBulb(grid, 3, 1);
  newBulb(grid, 4, 1);
  newBulb(grid, 5, 1);
  newBulb(grid, 6, 1);
  newBulb(grid, 7, 1);
  newBulb(grid, 8, 1);
  newBulb(grid, 9, 1);
  
  /*layer of floortiles */
  fillGrid(grid);
  
  /* MAIN LOOP */
	while(!sw->finished){
		in=input(sw);
		if( (in > 0) && (in < 5) ){
		  move(&grid[player->y][player->x],player->x,player->y,in,grid);
		}
		if (in == 9) {
		  if( grid[player->y][player->x].background != NULL
		  &&  grid[player->y][player->x].background->type == '-') {
			changeEntity(grid[player->y][player->x].background,'+');
		  }
		  if( grid[player->y][player->x].background != NULL
		  &&  grid[player->y][player->x].background->type == '+') {
			changeEntity(grid[player->y][player->x].background,'-');
		  }
		}
    updateEntities(grid);
    printGrid(grid);
	}
  
  /* free memory */
	freeEntityMem(grid);
  
  return 0;
}