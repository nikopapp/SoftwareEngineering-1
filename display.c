#include "display.h"

Display *newDisplay()
{
  Display *d =(Display *) malloc(sizeof(Display));
  int r = SDL_Init(SDL_INIT_EVERYTHING);
  if (r < 0){
    fail((char*)"Unable to initialize SDL");
  }

  /*Initialize SDL_mixer*/
  r= Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
  if(r < 0 ) {
    fprintf(OUTPUTERR,  "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
    Mix_GetError() );
    return(0);
  }

  readFont(fontdata,(char*)FONTNAME);
  d->win = SDL_CreateWindow("Project Elves", SDL_WINDOWPOS_UNDEFINED,
              SDL_WINDOWPOS_UNDEFINED, WWIDTH, WHEIGHT, SDL_WINDOW_SHOWN);
  if (d->win == NULL){
    fail((char*)"Unable to initialize SDL Window");
  }
  d->renderer = SDL_CreateRenderer(d->win, -1, 0);
  SDL_SetRenderDrawColor(d->renderer, 0, 0, 0, 0);
  SDL_RenderClear(d->renderer);

  /*MIXER-START*/
  d->zap = Mix_LoadWAV("files/click.wav");
  Mix_VolumeChunk(d->zap, 15);
  if (d->zap==NULL){
    fail((char*)"cannot load music file");
  }
  Mix_VolumeMusic(40);
  d->music = Mix_LoadMUS("files/elevator.mp3");
  if (d->music==NULL){
    fail((char*)"cannot load music file");
  }
  //If there is no music playing
  if( Mix_PlayingMusic() == 0 ) {
  //Play the music
  Mix_PlayMusic( d->music, -1.0 ); }
  /*MIXER-END*/
  return d;
}

//Credit to Ian Holyer for the drawFrame and fail function
void fail(char *s) {
    fprintf(OUTPUTERR, "%s: %s\n", s, SDL_GetError());
    SDL_Quit();
    exit(1);
}

// Update the window on screen, after delaying for the (rest of) the given time.
void drawFrame(Display *d, int milliseconds) {
    int t = milliseconds - SDL_GetTicks() % milliseconds;
    SDL_RenderPresent(d->renderer);
    SDL_Delay(t);
    SDL_RenderClear(d->renderer);

}

void loadPhoto(Display *d, char *s, int i)
{
  d->temp = IMG_Load(s);
  if (d->temp == NULL){
    fail((char*)"Cannot load photo");
  }
  d->images[i] = SDL_CreateTextureFromSurface(d->renderer, d->temp);
  SDL_SetTextureAlphaMod(d->images[i] , 255);
  SDL_SetTextureBlendMode(d->images[i], SDL_BLENDMODE_BLEND);

  SDL_RenderCopy(d->renderer, d->background, NULL, NULL);
}
void splashPhoto(Display *d, int i)
{

  SDL_RenderCopy(d->renderer, d->images[i], NULL, NULL);
}

/*My own delay function*/
void myDelay(int ms)
{
  SDL_Delay(ms);
}

//void drawText()
void drawBackground(Display *d,char c)
{
  SDL_RenderCopy(d->renderer, d->images[(int)c],NULL, NULL);
}

void drawEntities(Display *d, cell grid[H][W])
{
  SDL_Rect tile,dest;
  tile.w = tile.h = dest.w = dest.h = TILESIZE;
  tile.x = 0;
  tile.y = 0;
  int HCnt, WCnt;


  for(HCnt=0; HCnt<H; HCnt++){
    for(WCnt=0; WCnt<W; WCnt++){
      if (grid[HCnt][WCnt].background != NULL
      && (grid[HCnt][WCnt].background->type == OFFLIGHT
      || grid[HCnt][WCnt].background->type == ONLIGHT) ) {
        tile.h = dest.h = BULBHEIGHT;
      } /* custom rect for lightbulbs */
      else {
        tile.h = dest.h = TILESIZE;
      }

      dest.x = WCnt * TILESIZE;
      dest.y = HCnt * TILESIZE;

      if (grid[HCnt][WCnt].background != NULL) {
        SDL_RenderCopy(d->renderer,
          d->images[(int)grid[HCnt][WCnt].background->type],
            &tile, &dest);
      }
      if (grid[HCnt][WCnt].foreground != NULL) {
        SDL_RenderCopy(d->renderer,
          d->images[(int)grid[HCnt][WCnt].foreground->type],
            &tile, &dest);
      }
    }
  }
}

int drawString(Display *d, fntrow fontdata[FNTCHARS][FNTHEIGHT], char *str, int ox, int oy, int m,int height)
{
  int i = 0, j=0 ,wrdcnt=0;
  int x=ox;
  unsigned char chr;
  struct colour g = { 0, 213, 72, 255};
  struct colour r = { 250, 0, 0, 255};
  struct colour y = {  255,255,50, 255};
  struct colour w = { 255,255,255,255};

  if (m == normal) {
    setColour(d, g.red, g.green, g.blue, g.alpha);
  }
  else if (m == warning) {
    setColour(d, r.red, r.green, r.blue, r.alpha);
  }
  else if (m == yellow) {
    setColour(d, y.red, y.green, y.blue, y.alpha);
  }
  else if (m == white) {
    setColour(d, w.red, w.green, w.blue, w.alpha);
  }
  do {
    chr = str[i];

    if (isprint(chr) && chr != '\n') {
      x += (FNTWIDTH);
      if(height==0){
        drawChar(d, fontdata, chr, x, oy+j*FNTHEIGHT);
      }
      else{
        drawDoubleHeightChar(d, fontdata, chr, x, oy+j*FNTHEIGHT);
      }
    }
    if(str[i] == ' '){
      wrdcnt++;
    }

    if( (wrdcnt > 6) || (chr == '\n') ){
      j++;
      wrdcnt=0;
      x=ox;
    }
    i++;
  }
  while(str[i]);

  return (j + 1) * FNTHEIGHT; //returns the number of newlines inserted
}

//Credit to Neill Campbell for the .fnt file interpretation function
void drawChar(Display *d, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{

  unsigned x, y;
  for(y = 0; y < FNTHEIGHT; y++){
    for(x = 0; x < FNTWIDTH; x++){
      if(fontdata[chr-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
        SDL_RenderDrawPoint(d->renderer, x + ox, y+oy);
      }
    }
  }
}
void drawDoubleHeightChar(Display *d, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy)
{

  unsigned x, y;
  for(y = 0; y < FNTHEIGHT; y++){
    for(x = 0; x < FNTWIDTH; x++){
      if(fontdata[chr-FNT1STCHAR][y] >> (FNTWIDTH - 1 - x) & 1){
        SDL_SetRenderDrawBlendMode(d->renderer, SDL_BLENDMODE_BLEND);

        SDL_RenderDrawPoint(d->renderer, x + ox, 2*y+oy);
        SDL_RenderDrawPoint(d->renderer, x + ox, 2*y+oy+1);
      }
    }
  }
}

void readFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname)
{

    FILE *fp = fopen(fname, "rb");
    size_t itms;
    if(!fp){
       fprintf(OUTPUTERR, "Can't open Font file %s\n", fname);
       exit(1);
   }
   itms = fread(fontdata, sizeof(fntrow), FNTCHARS*FNTHEIGHT, fp);
   if(itms != FNTCHARS*FNTHEIGHT){
       fprintf(OUTPUTERR, "Can't read all Font file %s (%d) \n", fname, (int)itms);
       exit(1);
   }
   fclose(fp);

}

void setColour(Display *d, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{

   SDL_SetRenderDrawColor(d->renderer, r, g, b, a);

}

void closeDisplay(Display *d)
{
  //Stop the music
  Mix_HaltMusic();
  Mix_FreeMusic(d->music);
  Mix_CloseAudio();
  free(d);
  SDL_DestroyWindow(d->win);
  SDL_DestroyRenderer(d->renderer);
  SDL_Quit();
  d=NULL;
}
