#include "binaryGame.h"

int result(int byte[8]);

int binaryGame(void)
{
   int goal,res,i;
   int swich;
   int byte[8] = {0,0,0,0,0,0,0,0};
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
     printf("0 1 2 3 4 5 6 7\n");
     for(i=0;i<8;i++){
     printf("%d ",byte[i]);
     }
     printf("\n\n");
     res=result(byte);
     printf("result %d\n",res );
     if(res==goal){
       break;
     }
   }
   printf("you win\n");
   return(1);
}
int result(int byte[8])
{
   int i;
   float result=0.0;
   for(i=0;i<8;i++){
     if(i==0 && byte[0]==0){
       result=0;
     }
     else{
      result += pow( byte[i]*2, i);
     }
   }
   return((int)result);
}
