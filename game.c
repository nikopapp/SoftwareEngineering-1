#include <stdio.h>
#include "game.h"

/*hello --this is a test change-- */

int main(int argc, char **argv)
{
   int sw;
   if(argc==2){
      sw = atoi(argv[1]);
   }
   else{
   printf("1.Binary Game\n");
   printf("2.Encryption Game\n");
   printf("3.Test Grid\n");
   scanf("%d", &sw );
   }
switch (sw) {
  case 1:
     if(binaryGame()==1){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;
  case 2:
     if(encryption()==0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;
  case 3:
     if(grid()==0){printf("everything OK\n");}
     else{printf("ERROR \n");}
     break;

}


printf("\n\n");
return(0);
}
