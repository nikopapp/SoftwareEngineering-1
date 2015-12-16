#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <CUnit/Basic.h>
/*uses sdl libraries from srcfolder*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>

#define WHEIGHT             704
#define WWIDTH             1152
#define TILESIZE             64

#define H WHEIGHT / TILESIZE
#define W WWIDTH / TILESIZE

/* FORWARD DEDCLARATIONS */
struct display;
typedef struct display Display;

struct entity;
typedef struct entity entity;

struct cell;
typedef struct cell cell;
