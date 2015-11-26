struct SDL_Simplewin {
   SDL_bool finished;
   SDL_Window *win;
   SDL_Renderer *renderer;
   SDL_Surface *images[128];
};

void Nikos_SDL_Init(SDL_Simplewin *sw);