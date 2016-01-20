#include "game.h"
#define MAXPLAYTIMES 1
int main(void)
{
  Display *d = newDisplay();
  cell grid[H][W];
  entity *player, *door1, *door2;
  int in,gamesPlayed[2];
  srand(time(NULL));
  gamesPlayed[0]=gamesPlayed[1]=0;

  mediaLoad(d);
  do{
    splashPhoto(d,INTRO_SCREEN);
    drawString(d, fontdata, (char*)"PRESS SPACE", 270, 520, white,1);
    drawFrame(d,REFRESH_RATE);
    in=input(d);
  }while(in==0||in==10);
  initGrid(grid);
   // place player
  player = grid[10][2].foreground = newEntity(passable,P_R1 ,2,10);
   // Creates the boundary walls
  makeBoundariesLobby(grid);

  door1 = grid[4][W-6].background = newEntity(passable,DOORINVIS, W-6,4);
  door2 = grid[7][W-11].background = newEntity(passable,DOORINVIS ,W-11,7);

  /* layer of floortiles -
  must be the last entity placement*/
  fillGrid(grid);


  while(in!=10){
    if(gamesPlayed[0]!=MAXPLAYTIMES||gamesPlayed[1]!=MAXPLAYTIMES){
      lobbyDraw(d, grid);
      in=input(d);
      if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
        move(&grid[player->y][player->x],player->x,player->y,(direction)in,grid);
        printGrid(grid);
      }
    }
    else{
      do{
        splashPhoto(d,GOVER_SCREEN);
        drawString(d, fontdata, (char*)"PRESS SPACE TO PLAY AGAIN", 350, 540, white,1);
        drawString(d, fontdata, (char*)"OR ESC TO QUIT", 350, 580, warning,0);
        drawFrame(d,REFRESH_RATE);
        in=input(d);
      }while(in==0);
        if(in!=10){
          gamesPlayed[0]=gamesPlayed[1]=0;
        }
        else{
          /*in==10 the same as d->finished=true;*/
          in=10;
          d->finished=(SDL_bool)true;
        }
    }
    if (grid[player->y][player->x].background == door1&&gamesPlayed[0]<MAXPLAYTIMES) {
      bgame(d);
      gamesPlayed[0]++;
      move(&grid[player->y][player->x],player->x,player->y,DOWN,grid);
      changeEntity(player, P_DOWN1);
    }
    if (grid[player->y][player->x].background == door2&&gamesPlayed[1]<MAXPLAYTIMES) {
      quizGame(d);
      gamesPlayed[1]++;
      move(&grid[player->y][player->x],player->x,player->y,DOWN,grid);
      changeEntity(player, P_DOWN1);
    }
  }
  freeEntityMem(grid);  /* free memory */
  closeDisplay(d);
  d->finished=(SDL_bool)true;
  fprintf(OUTPUT, "\n\n");
  return(0);
}

void makeBoundariesLobby(cell grid[H][W])
{
  int i,j;
  newLimit(grid, 7, H-5);
  newLimit(grid, 12, H-8);
  for (i = 0; i < W; i++) {
    for(j = 4; j < H-1; j++){
      if (i != W-6 && i != W-11) { /*ladder locations */
        newLimit(grid, i, j);
      }
    }
  }
}

void lobbyDraw(Display *d, cell grid[H][W])
{
  drawBackground(d,BG_LOBBY);
  drawEntities(d, grid);
  drawString(d, fontdata, (char*)"LEARN BINARY", 680, 240, yellow,1);
  drawString(d, fontdata, (char*)"COMPUTER QUIZ", 360, 400, yellow,1);

  drawFrame(d, REFRESH_RATE);
}

void mediaLoad(Display *d)
{
/* the enum for the entity type values is in base.h
 * wall tiles and some types of door have no image,
 * but are displayed in terminal for debugging. */

  loadPhoto(d, (char*)"files/board.png" , BG_LOBBY);  /* use numbers for backgrounds.  these are unused ascii chars */
  loadPhoto(d, (char*)"files/room2.png" , BG_BIN);
  loadPhoto(d, (char*)"files/room1.png" , BG_ENC);
  loadPhoto(d, (char*)"images/gameOver.png", GOVER_SCREEN);
  loadPhoto(d, (char*)"images/Intro.png", INTRO_SCREEN);

  loadPhoto(d, (char*)"images/offlight.png", OFFLIGHT);
  loadPhoto(d, (char*)"images/onlight.png", ONLIGHT);
  loadPhoto(d, (char*)"images/offswitch.bmp", OFFSWITCH);
  loadPhoto(d, (char*)"images/onswitch.bmp", ONSWITCH);

  loadPhoto(d, (char*)"images/dooropen.bmp", DOOROPEN);
  loadPhoto(d, (char*)"images/doorclosed.bmp", DOORCLOSED);

  loadPhoto(d, (char*)"images/blue_un.png", HINTBUTTON);
  loadPhoto(d, (char*)"images/red_un.png", RESETBUTTON);
  loadPhoto(d, (char*)"images/blue_pr.png", HBUTTON_PR);
  loadPhoto(d, (char*)"images/red_pr.png", RBUTTON_PR);

  loadPhoto(d, (char*)"images/Red_Elf_Front.bmp", P_DOWN1);
  loadPhoto(d, (char*)"images/Red_Elf_Front2.bmp", P_DOWN2);
  loadPhoto(d, (char*)"images/Red_Elf_Front3.bmp", P_DOWN3);

  loadPhoto(d, (char*)"images/Red_Elf_Back.bmp", P_UP1);
  loadPhoto(d, (char*)"images/Red_Elf_Back2.bmp", P_UP2);
  loadPhoto(d, (char*)"images/Red_Elf_Back3.bmp", P_UP3);

  loadPhoto(d, (char*)"images/Red_Elf_Left.bmp", P_L1);
  loadPhoto(d, (char*)"images/Red_Elf_Left2.bmp", P_L2);
  loadPhoto(d, (char*)"images/Red_Elf_Left3.bmp", P_L3);

  loadPhoto(d, (char*)"images/Red_Elf_Right.bmp", P_R1);
  loadPhoto(d, (char*)"images/Red_Elf_Right2.bmp", P_R2);
  loadPhoto(d, (char*)"images/Red_Elf_Right3.bmp", P_R3);

  loadPhoto(d, (char*)"images/RArrow.bmp", RARROW);
  loadPhoto(d, (char*)"images/LArrow.bmp", LARROW);
  loadPhoto(d, (char*)"images/DArrow.bmp", DARROW);
  loadPhoto(d, (char*)"images/UArrow.bmp", UARROW);

  loadPhoto(d, (char*)"images/chars/a.bmp", 'a');
  loadPhoto(d, (char*)"images/chars/b.bmp", 'b');
  loadPhoto(d, (char*)"images/chars/c.bmp", 'c');
  loadPhoto(d, (char*)"images/chars/d.bmp", 'd');
  loadPhoto(d, (char*)"images/chars/e.bmp", 'e');
  loadPhoto(d, (char*)"images/chars/f.bmp", 'f');
  loadPhoto(d, (char*)"images/chars/g.bmp", 'g');
  loadPhoto(d, (char*)"images/chars/h.bmp", 'h');
  loadPhoto(d, (char*)"images/chars/i.bmp", 'i');
  loadPhoto(d, (char*)"images/chars/j.bmp", 'j');
  loadPhoto(d, (char*)"images/chars/k.bmp", 'k');
  loadPhoto(d, (char*)"images/chars/l.bmp", 'l');
  loadPhoto(d, (char*)"images/chars/m.bmp", 'm');
  loadPhoto(d, (char*)"images/chars/n.bmp", 'n');
  loadPhoto(d, (char*)"images/chars/o.bmp", 'o');
  loadPhoto(d, (char*)"images/chars/p.bmp", 'p');
  loadPhoto(d, (char*)"images/chars/q.bmp", 'q');
  loadPhoto(d, (char*)"images/chars/r.bmp", 'r');
  loadPhoto(d, (char*)"images/chars/s.bmp", 's');
  loadPhoto(d, (char*)"images/chars/t.bmp", 't');
  loadPhoto(d, (char*)"images/chars/v.bmp", 'v');
  loadPhoto(d, (char*)"images/chars/u.bmp", 'u');
  loadPhoto(d, (char*)"images/chars/w.bmp", 'w');
  loadPhoto(d, (char*)"images/chars/x.bmp", 'x');
  loadPhoto(d, (char*)"images/chars/y.bmp", 'y');
  loadPhoto(d, (char*)"images/chars/z.bmp", 'z');
}
