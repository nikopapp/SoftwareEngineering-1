#include "binaryGame.h"



int binaryGame(void)
{
   int goal,res;
   int swich;
   int lights[8] = {0,1,2,3,4,5,6,7};
   int byte[8] = {0,0,0,0,0,0,0,0};
   int player[8] = {0,0,0,0,0,0,0,1};
   srand((unsigned) time(&t));
   goal =rand()%255;

   printf("try summing %d\n", goal );
   printf("result: %d\n", result(byte) );
   /*Light switch ON/OFF*/
   while(scanf("%d", &swich)==1){
     switch ( byte[swich]) {
       case 0:
          byte[swich]=1;
          break;
       case 1:
          byte[swich]=0;
          break;
     }
     BinPrintArray(lights);
     BinPrintArray(byte);
     BinPrintArray(player);

     res=BinResult(byte);
     printf("result %d\n",res );
     if(res==goal){
       break;
     }
   }
   printf("you win\n");
   return(1);
}
int BinResult(int byte[BYTE_L])
{
   int i;
   float result=0.0;
   for(i=0;i<8;i++){
     /*Exception for first bit 0=0*/
     if(i==0 && byte[0]==0){
       result=0;
     }
     else{
      result += pow( byte[i]*2, i);
     }
   }
   return((int)result);
}
BinPrintArray(int array[8])
{
  int i;
  for(i=0;i<8;i++){
    printf("%3d",array[i]);
  }
  printf("\n");
}
