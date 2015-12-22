#include <stdbool.h>
#include <math.h>
#include "entity.h"

#define MILLISECONDDELAY     20
#define BULBHEIGHT           364 //height of bulb images

struct display {
    SDL_bool finished;
    SDL_Window *win;
    SDL_Surface *temp;
    SDL_Texture *images[256];
    SDL_Texture *background;
    SDL_Renderer *renderer;
    SDL_Event event;
    Uint32 colour;
    //declare the music file
    Mix_Music *music;
    Mix_Chunk *zap;
};

/* Font stuff */
typedef unsigned short fntrow;
#define FNTWIDTH (sizeof(fntrow)*8)
#define FNTHEIGHT 18
#define FNTCHARS 96
#define FNT1STCHAR 32
#define FONTNAME "files/m7fixed.fnt"
fntrow fontdata[FNTCHARS][FNTHEIGHT];

void drawChar(Display *d, fntrow fontdata[FNTCHARS][FNTHEIGHT], unsigned char chr, int ox, int oy);
void drawString(Display *d, fntrow fontdata[FNTCHARS][FNTHEIGHT], char *str, int ox, int oy);
void Neill_SDL_ReadFont(fntrow fontdata[FNTCHARS][FNTHEIGHT], char *fname);

// Create a new display object.
Display *newDisplay();
void loadPhoto(Display *d, char *s, int i);
//Splashes photo without loading it again
void splashPhoto(Display *d, int i);
void drawBackground(Display *d, char c);
//draws entity
void drawEntities(Display *d, cell grid[H][W]);
//Set drawing colour
void setColour(Display *d, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
// Update the window on screen, after delaying for the (rest of) the given time.
void drawFrame(Display *d, int milliseconds);
// Return true if the quit button has been pressed.
bool quitEvent(Display *d);
//Gets whatever error message SDL gives and it prits it with the input *s
void fail(char *s);
/*My own delay function*/
void myDelay(int ms);
void closeDisplay(Display *d);

