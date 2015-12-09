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
   door1 = grid[5][W-8].background = newEntity(passable,'.',W-8,5);
   door2 = grid[8][W-9].background = newEntity(passable,'.',W-9,8);
   /* layer of floortiles -
   must be the last entity placement*/
   fillGrid(grid);
   drawEntities(d, grid);
   drawFrame(d, 20);

   while(!d->finished){
      if (grid[player->y][player->x].background == door1) {
        bgame(d);
      }
      if (grid[player->y][player->x].background == door2||
          grid[player->y][player->x+1].background == door2||
          grid[player->y][player->x+2].background == door2) {
        bgame(d);
      delEntity(grid[8][W-1].background);
      }
      loadPhoto(d, "files/board.bmp" , 'b');
      drawEntities(d, grid);
      drawFrame(d, 20);
      in=input(d);
      if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
        move(&grid[player->y][player->x],player->x,player->y,(direction)in,grid);
        printGrid(grid);
        updatePlayerfacing(player,(direction)in);
      }
    }

   freeEntityMem(grid);  /* free memory */
   closeDisplay(d);
   printf("\n\n");
   return(0);
}
void mediaLoad(Display *d)
{
  loadPhoto(d, "files/board.bmp" , 'b');
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
