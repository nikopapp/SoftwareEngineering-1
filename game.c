#include <stdio.h>
#include "game.h"

int main(void)
{
   Display *d = newDisplay();
   cell grid[H][W];
   entity *player, *door1, *door2;
   int in;
   mediaLoad(d);
   initGrid(grid);
   /* place player */
   player = grid[6][6].foreground = newEntity(passable,'R',6,6);
   // Creates the boundary walls
   createBoundingWalls(grid);
   delEntity(grid[4][W-1].background);
   delEntity(grid[4][0].background);
   door1 = grid[4][W-1].background = newEntity(passable,'%',W-1,4);
   door2 = grid[4][0].background = newEntity(passable,'%',0,4);
   /* layer of floortiles -
   must be the last entity placement*/
   fillGrid(grid);

   drawEntities(d, grid);
   drawFrame(d, 20);

   while(!d->finished){
      if (grid[player->y][player->x].background == door1) {
        bgame(d);
      }
      if (grid[player->y][player->x].background == door2) {
        bgame(d);
      }
      in=input(d);
      if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
        move(&grid[player->y][player->x],player->x,player->y,in,grid);
        printGrid(grid);
        updatePlayerfacing(player, in);
      }
      drawEntities(d, grid);
      drawFrame(d, 20);
    }

   freeEntityMem(grid);  /* free memory */
   closeDisplay(d);
   printf("\n\n");
   return(0);
}
void mediaLoad(Display *d)
{
  loadPhoto(d, "files/room0.bmp" , 'b');
   loadPhoto(d, "images/floor.bmp", '.');
  loadPhoto(d, "images/offlight.bmp", '0');
  loadPhoto(d, "images/onlight.bmp", '1');
  loadPhoto(d, "images/offswitch.bmp", '-');
  loadPhoto(d, "images/onswitch.bmp", '+');
  loadPhoto(d, "images/dooropen.bmp", '%');
  loadPhoto(d, "images/doorclosed.bmp", '&');
  loadPhoto(d, "images/wall.bmp", '#');
  loadPhoto(d, "images/Red_Elf_Front.bmp", 'D');
  loadPhoto(d, "images/Red_Elf_Back.bmp", 'U');
  loadPhoto(d, "images/Red_Elf_Left.bmp", 'L');
  loadPhoto(d, "images/Red_Elf_Right.bmp", 'R');

}
