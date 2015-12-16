#include <stdio.h>
#include "game.h"

int main(void)
{
   Display *d = newDisplay();
   cell grid[H][W];
   entity *player, *door1, *door2;
   int in, count=0, in_prev=0;
   
   mediaLoad(d);
   initGrid(grid);
   /* place player */
   player = grid[10][2].foreground = newEntity(passable,'R',2,10);
   // Creates the boundary walls
   //createBoundingWalls(grid);
   door1 = grid[4][W-6].background = newEntity(passable,'.',W-6,4);
   door2 = grid[7][W-11].background = newEntity(passable,'.',W-11,7);
   /* layer of floortiles -
   must be the last entity placement*/
   fillGrid(grid);
   drawEntities(d, grid);
   drawFrame(d, 20);

   while(!d->finished){
      if (grid[player->y][player->x].background == door1) {
        bgame(d);

      }
      if (grid[player->y][player->x].background == door2 /*||
          grid[player->y][player->x+1].background == door2||
          grid[player->y][player->x+2].background == door2*/) {
        encryption(d);
      //delEntity(grid[8][W-1].background);
      }
      drawBackground(d,0);
      drawEntities(d, grid);
      drawFrame(d, 20);
      in=input(d);
      move(&grid[player->y][player->x],player->x,player->y,(direction)in,grid);
      printGrid(grid);
      count = next_movment(count, &in_prev, in);
      updatePlayerfacing(player,(direction)in, count);
   }

   freeEntityMem(grid);  /* free memory */
   closeDisplay(d);
   printf("\n\n");
   return(0);
}

void mediaLoad(Display *d)
{
  loadPhoto(d, "files/board.png" , 0); /* use numbers for backgrounds.  these are unused ascii chars */
  loadPhoto(d, "files/room0.png" , 1);
  loadPhoto(d, "images/screen.png" , 2);
  
  loadPhoto(d, "images/floor.bmp", '.');
  loadPhoto(d, "images/offlight.png", '0');
  loadPhoto(d, "images/onlight.png", '1');
  loadPhoto(d, "images/offswitch.bmp", '-');
  loadPhoto(d, "images/onswitch.bmp", '+');
  
  loadPhoto(d, "images/dooropen.bmp", '%');
  loadPhoto(d, "images/doorclosed.bmp", '*');
  
  loadPhoto(d, "images/blue_un.bmp", '&');
  loadPhoto(d, "images/red_un.bmp", 'E');
  loadPhoto(d, "images/wall.bmp", '#');

  loadPhoto(d, "images/Red_Elf_Front.bmp", 'D');
  loadPhoto(d, "images/Red_Elf_Front2.bmp", '/');
  loadPhoto(d, "images/Red_Elf_Front3.bmp", '?');

  loadPhoto(d, "images/Red_Elf_Back.bmp", 'U');
  loadPhoto(d, "images/Red_Elf_Back2.bmp", ';');
  loadPhoto(d, "images/Red_Elf_Back3.bmp", ':');

  loadPhoto(d, "images/Red_Elf_Left.bmp", 'L');
  loadPhoto(d, "images/Red_Elf_Left2.bmp", '{');
  loadPhoto(d, "images/Red_Elf_Left3.bmp", '(');

  loadPhoto(d, "images/Red_Elf_Right.bmp", 'R');
  loadPhoto(d, "images/Red_Elf_Right2.bmp", '}');
  loadPhoto(d, "images/Red_Elf_Right3.bmp", ')');

  loadPhoto(d, "images/chars/a.bmp", 'a');
 loadPhoto(d, "images/chars/b.bmp", 'b');
 loadPhoto(d, "images/chars/c.bmp", 'c');
 loadPhoto(d, "images/chars/d.bmp", 'd');
 loadPhoto(d, "images/chars/e.bmp", 'e');
 loadPhoto(d, "images/chars/f.bmp", 'f');
 loadPhoto(d, "images/chars/g.bmp", 'g');
 loadPhoto(d, "images/chars/h.bmp", 'h');
 loadPhoto(d, "images/chars/i.bmp", 'i');
 loadPhoto(d, "images/chars/j.bmp", 'j');
 loadPhoto(d, "images/chars/k.bmp", 'k');
 loadPhoto(d, "images/chars/l.bmp", 'l');
 loadPhoto(d, "images/chars/m.bmp", 'm');
 loadPhoto(d, "images/chars/n.bmp", 'n');
 loadPhoto(d, "images/chars/o.bmp", 'o');
 loadPhoto(d, "images/chars/p.bmp", 'p');
 loadPhoto(d, "images/chars/q.bmp", 'q');
 loadPhoto(d, "images/chars/r.bmp", 'r');
 loadPhoto(d, "images/chars/s.bmp", 's');
 loadPhoto(d, "images/chars/t.bmp", 't');
 loadPhoto(d, "images/chars/v.bmp", 'v');
 loadPhoto(d, "images/chars/u.bmp", 'u');
 loadPhoto(d, "images/chars/w.bmp", 'w');
 loadPhoto(d, "images/chars/x.bmp", 'x');
 loadPhoto(d, "images/chars/y.bmp", 'y');
 loadPhoto(d, "images/chars/z.bmp", 'z');
 loadPhoto(d, "images/RArrow.bmp", '>');
 loadPhoto(d, "images/LArrow.bmp", '<');
 loadPhoto(d, "images/DArrow.bmp", '$');
 loadPhoto(d, "images/UArrow.bmp", '^');

}
