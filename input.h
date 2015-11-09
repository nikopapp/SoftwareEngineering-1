<<<<<<< HEAD
#include <SDL.h>
=======
#include <SDL2/SDL.h>
>>>>>>> ae85e4dfcb116ad742cbae4de47e8f8075c32210

#define WWIDTH    400
#define WHEIGHT   300

struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
};
typedef struct SDL_Simplewin SDL_Simplewin;

void Nikos_SDL_Init(SDL_Simplewin *sw);
int Nikos_SDL_Events(SDL_Simplewin *sw, int *p);
