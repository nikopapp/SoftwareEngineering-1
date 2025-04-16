#include "input.h"

int input(Display *d)
{
  int input_value=0;
  int *input_pointer;
  input_pointer=&input_value;
  while(!d->finished){
      if(E_SDL_Event_Handling(input_pointer)!=0){
        return(input_value);
        printf("SHOUDLN'T HAPPEN :%d\n",input_value );
      }
  }
  return(input_value);
}

int E_SDL_Event_Handling(int *p)
{
   SDL_Event event;
   while(SDL_PollEvent(&event))
   {
      switch (event.type){
        case SDL_MOUSEBUTTONDOWN:
          break;
        case SDL_KEYDOWN:
          switch( event.key.keysym.sym ){
            case SDLK_LEFT:
              *p=1;
              fprintf(OUTPUT, "input output%d\n",*p);
              return(LEFT);
              break;
            case SDLK_RIGHT:
              *p=2;
              fprintf(OUTPUT, "input output%d\n",*p);
              return(RIGHT);
              break;
            case SDLK_UP:
              *p=3;
              fprintf(OUTPUT, "input output%d\n",*p);
              return(UP);
              break;
            case SDLK_DOWN:
              *p=4;
              fprintf(OUTPUT, "input output%d\n",*p);
              return(DOWN);
              break;
            case SDLK_SPACE:
              *p=9;
              fprintf(OUTPUT, "input output%d\n",*p);
              return(9);
              break;
            case SDLK_ESCAPE:
              *p=10;
              return 10;
              break;
          }
        break;
        case SDL_QUIT:
          *p=10;
          return 10;
          break;
      }
      return(0);
   }
   return(0);
}
