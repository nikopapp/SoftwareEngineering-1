#include "game.h"

int main(void)
{
  Display *d = newDisplay();
  cell grid[H][W];
  entity *player, *door1, *door2;
  int in, count=0, in_prev=0;
  srand(time(NULL));


  mediaLoad(d);
  initGrid(grid);
   /* place player */
  player = grid[10][2].foreground = newEntity(passable,P_R1 ,2,10);
   // Creates the boundary walls
  makeBoundariesLobby(grid);

  door1 = grid[4][W-6].background = newEntity(passable,DOORINVIS, W-6,4);
  door2 = grid[7][W-11].background = newEntity(passable,DOORINVIS ,W-11,7);

  /* layer of floortiles -
  must be the last entity placement*/
  fillGrid(grid);
  drawEntities(d, grid);
  drawFrame(d, REFRESH_RATE);

  while(!d->finished){
    if (grid[player->y][player->x].background == door1) {
      bgame(d);
      move(&grid[player->y][player->x],player->x,player->y,DOWN,grid);
      changeEntity(player, P_DOWN1);
    }
    if (grid[player->y][player->x].background == door2) {
      encryption(d);
      move(&grid[player->y][player->x],player->x,player->y,DOWN,grid);
      changeEntity(player, P_DOWN1);
    }
    drawBackground(d,BG_LOBBY);
    drawEntities(d, grid);
    drawFrame(d, REFRESH_RATE);
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
void makeBoundariesLobby(cell grid[H][W])
{
  int i,j;
  newLimit(grid, 7, H-5);
  newLimit(grid, 12, H-9);
  for (i = 0; i < W; i++) {
    for(j=5;j<H-1;j++){

      if (i != W-6 && i != W-11) { /*ladder locations */
        newLimit(grid, i, j);
      }
    }
  }
}
void mediaLoad(Display *d)
{
  loadPhoto(d, "files/board.png" , BG_LOBBY); /* use numbers for backgrounds.  these are unused ascii chars */
  loadPhoto(d, "files/room0.png" , BG_BIN);
  loadPhoto(d, "files/room1.png" , BG_ENC);

  loadPhoto(d, "images/floor.bmp", FLOOR);
  loadPhoto(d, "images/offlight.png", OFFLIGHT);
  loadPhoto(d, "images/onlight.png", ONLIGHT);
  loadPhoto(d, "images/offswitch.bmp", OFFSWITCH);
  loadPhoto(d, "images/onswitch.bmp", ONSWITCH);

  loadPhoto(d, "images/dooropen.bmp", DOOROPEN);
  loadPhoto(d, "images/doorclosed.bmp", DOORCLOSED);

  loadPhoto(d, "images/blue_un.bmp", HINTBUTTON);
  loadPhoto(d, "images/red_un.bmp", RESETBUTTON);

  loadPhoto(d, "images/Red_Elf_Front.bmp", P_DOWN1);
  loadPhoto(d, "images/Red_Elf_Front2.bmp", P_DOWN2);
  loadPhoto(d, "images/Red_Elf_Front3.bmp", p_DOWN3);

  loadPhoto(d, "images/Red_Elf_Back.bmp", P_UP1);
  loadPhoto(d, "images/Red_Elf_Back2.bmp", P_UP2);
  loadPhoto(d, "images/Red_Elf_Back3.bmp", P_UP3);

  loadPhoto(d, "images/Red_Elf_Left.bmp", P_L1);
  loadPhoto(d, "images/Red_Elf_Left2.bmp", P_L2);
  loadPhoto(d, "images/Red_Elf_Left3.bmp", P_L3);

  loadPhoto(d, "images/Red_Elf_Right.bmp", P_R1);
  loadPhoto(d, "images/Red_Elf_Right2.bmp", P_R2);
  loadPhoto(d, "images/Red_Elf_Right3.bmp", P_R3);

  loadPhoto(d, "images/RArrow.bmp", RARROW);
  loadPhoto(d, "images/LArrow.bmp", LARROW);
  loadPhoto(d, "images/DArrow.bmp", DARROW);
  loadPhoto(d, "images/UArrow.bmp", UPARROW);
  
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


}
