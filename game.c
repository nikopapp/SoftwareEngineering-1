#include <stdio.h>
#include "game.h"

int main(int argc, char **argv)
{
  entity *e = newEntity(passable,1,6,6);
   Display *d = newDisplay();
   loadPhoto(d, "images/floor.bmp", 1);
   drawEntity(d,e);
   e->x=10;
   e->y=10;
   drawEntity(d,e);
   drawFrame(d, 20);
   int select;
   if(argc==2){
      select = atoi(argv[1]);
   }
   else{
  //  printf("1.Binary Game\n");
  //  printf("2.Encryption Game\n");
  //  printf("3.Test Grid\n");
   printf("4.Test input\n");
   printf("5.Binary game/grid integration\n");
   scanf("%d", &select );
   }
switch (select) {
  // case 1:
  //    if(binaryGame()==1){printf("everything OK\n");}
  //    else{printf("ERROR \n");}
  //    break;
  // case 2:
  //    if(encryption()==0){printf("everything OK\n");}
  //    else{printf("ERROR \n");}
  //    break;
  // case 3:
  //    if(gridmain(swin)==0){printf("everything OK\n");}
  //    else{printf("ERROR \n");}
  //    break;
  case 4:
     if(input(d)!=0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;
  case 5:
     if(bgame(d)!=0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;

}

closeDisplay(d);
printf("\n\n");
return(0);
}
