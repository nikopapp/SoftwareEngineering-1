#include "display.h"




Display *newDisplay()
{
  Display *d = malloc(sizeof(Display));
  int r = SDL_Init(SDL_INIT_EVERYTHING);
  if (r < 0){
    fail("Unable to initialize SDL");
  }
   /*Initialize SDL_mixer*/
    r= Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
    if(r < 0 ) {
      printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
      Mix_GetError() );
      return(0);
    }
    d->win = SDL_CreateWindow("Project Elves", SDL_WINDOWPOS_UNDEFINED,
                SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
    if (d->win == NULL){
      fail("Unable to initialize SDL Window");
    }
    d->renderer = SDL_CreateRenderer(d->win, -1, 0);
    SDL_SetRenderDrawColor(d->renderer, 0, 0, 0, 0);
    SDL_RenderClear(d->renderer);

    /*MIXER-START*/
    d->zap = Mix_LoadWAV("files/click.wav");
    Mix_VolumeChunk(d->zap, 15);
    if (d->zap==NULL){
      fail("music not good");
    }
    d->music = Mix_LoadMUS("files/PdPrince-SStrobe.mp3");
    if (d->music==NULL){
      fail("music not good");
    }
     //If there is no music playing
     if( Mix_PlayingMusic() == 0 ) {
     //Play the music
     Mix_PlayMusic( d->music, -1.0 ); }
     /*MIXER-END*/
      return d;
}

void fail(char *s) {
    fprintf(stderr, "%s: %s\n", s, SDL_GetError());
    SDL_Quit();
    exit(1);
}

// Update the window on screen, after delaying for the (rest of) the given time.
//IAN HOLYER stuff
void drawFrame(Display *d, int milliseconds) {
    int t = milliseconds - SDL_GetTicks() % milliseconds;
    SDL_Delay(t);
    SDL_RenderPresent(d->renderer);
    SDL_RenderClear(d->renderer);

}

void loadPhoto(Display *d, char *s, int i)
{
  d->temp = IMG_Load(s);
  if (d->temp == NULL){
    fail("bad photo");
  }
  d->images[i] = SDL_CreateTextureFromSurface(d->renderer, d->temp);
  //SDL_SetTextureAlphaMod(d->images[i] , 255);
  //SDL_SetTextureBlendMode(d->images[i], SDL_BLENDMODE_BLEND);
    /* we got the texture now -> free surface */
  //SDL_RenderCopy(d->renderer, d->background, NULL, NULL);
}

void splashPhoto(Display *d)
{
SDL_RenderCopy(d->renderer, d->background, NULL, NULL);
}

/*My own delay function*/
void myDelay(int ms)
{
  SDL_Delay(ms);
}
void drawEntity(Display *d, entity *e)
{
  SDL_Rect tile,dest;
  tile.w=tile.h=dest.w=dest.h=64;
  tile.x = 0;
  tile.y = 0;
  dest.x = e->x*64;
  dest.y = e->y*64;
  SDL_RenderCopy(d->renderer, d->images[1], &tile, &dest);
}
void closeDisplay(Display *d)
{
  //Stop the music
  /*Mix_HaltMusic();
  Mix_FreeMusic(d->music);
  Mix_CloseAudio();
  free(d);*/
  SDL_DestroyWindow(d->win);
  SDL_DestroyRenderer(d->renderer);
  SDL_Quit();
}
