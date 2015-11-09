#include "input.h"

int input(void)
{
  int input_value;
  int *input_pointer;
  SDL_Simplewin sw;
  input_pointer=&input_value;
  Nikos_SDL_Init(&sw);
  while(!sw.finished){
      Nikos_SDL_Events(&sw,input_pointer);
  }
  SDL_Quit();
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

   /* Set screen to black
   Neill_SDL_SetDrawColour(sw, 0, 0, 0);
   SDL_RenderClear(sw->renderer);
   SDL_RenderPresent(sw->renderer);*/

}
/* Gobble all events & ignore most */
int Nikos_SDL_Events(SDL_Simplewin *sw, int *p)
{
   SDL_Event event;
   while(SDL_PollEvent(&event))
   {
      switch (event.type){
         case SDL_MOUSEBUTTONDOWN:
         case SDL_KEYDOWN:
            switch( event.key.keysym.sym ){
               case SDLK_LEFT:
                  *p=1;
                  printf("%d\n",*p);
                  sw->finished=1;
                  return(1);
                  break;
               case SDLK_RIGHT:
                  *p=2;
                  printf("%d\n",*p);
                  sw->finished=1;
                  return(2);
                  break;
               case SDLK_UP:
                  *p=3;
                  printf("%d\n",*p);
                  sw->finished=1;
                  return(3);
                  break;
               case SDLK_DOWN:
      //   printf("Interaction\n");
                  *p=4;
                  printf("%d\n",*p);
                  sw->finished=1;
                  return(4);
                  break;
               case SDLK_ESCAPE:
                  sw->finished =1;
                  break;
         }
         break;
         case SDL_QUIT:
            sw->finished = 1;
      }
      return(0);
   }
   return(0);
}
