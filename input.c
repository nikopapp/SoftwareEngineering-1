#include "input.h"
//input get a pointer for a simple window
//simple window is declared
int input(SDL_Simplewin *sw)
{
  int input_value=0;
  int *input_pointer;
  input_pointer=&input_value;
//  Nikos_SDL_Init(sw);
  while(!sw->finished){
      if(Nikos_SDL_Events(sw,input_pointer)!=0){
        return(input_value);
         printf("shit :%d\n",input_value );
      }
  }
  return(input_value);
}

void Nikos_SDL_Init(SDL_Simplewin *sw)
{

   if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      fprintf(stderr, "\nUnable to initialize SDL:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   sw->finished = 0;

   sw->win= SDL_CreateWindow("SDL Window",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          WWIDTH, WHEIGHT,
                          SDL_WINDOW_SHOWN);
   if(sw->win == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Window:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   sw->renderer = SDL_CreateRenderer(sw->win, -1, 0);
   if(sw->renderer == NULL){
      fprintf(stderr, "\nUnable to initialize SDL Renderer:  %s\n", SDL_GetError());
      SDL_Quit();
      exit(1);
   }

   /* Set screen to black*/
   SDL_SetRenderDrawColor(sw->renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
   SDL_RenderClear(sw->renderer);
   SDL_RenderPresent(sw->renderer);

}

/* Gobble all events & ignore most */
int Nikos_SDL_Events(SDL_Simplewin *sw, int *p)
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
                  printf("input output%d\n",*p);
                  return(1);
                  break;
               case SDLK_RIGHT:
                  *p=2;
                  printf("input output%d\n",*p);
                  return(2);
                  break;
               case SDLK_UP:
                  *p=3;
                  printf("input output%d\n",*p);
                  return(3);
                  break;
               case SDLK_DOWN:
                  *p=4;
                  printf("input output%d\n",*p);
                  //  printf("%d\n",*p);
                  return(4);
                  break;
               case SDLK_ESCAPE:
                  sw->finished = 1;
                  break;
         }
         break;
         case SDL_QUIT:
            sw->finished = 1;
            break;
      }
      return(0);
   }
   return(0);
}
