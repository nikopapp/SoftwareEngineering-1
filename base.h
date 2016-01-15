#include <ctype.h>
// #include <CUnit/Basic.h>

/*uses sdl libraries from srcfolder*/
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#define WHEIGHT             704
#define WWIDTH             1152
#define TILESIZE             64
#define REFRESH_RATE         20

#define H WHEIGHT / TILESIZE
#define W WWIDTH / TILESIZE

#define OUTPUT stdout
#define OUTPUTERR stderr 

/* used to give the entity types more descriptive names */
typedef enum etype {
  BG_LOBBY    = 0,  /* bgs */
  BG_BIN      = 1,
  BG_ENC      = 3,
  FLOOR       = '.',
  OFFLIGHT    = '0',
  ONLIGHT     = '1',
  OFFSWITCH   = '-',
  ONSWITCH    = '+',
  DOOROPEN    = '%',
  DOORCLOSED  = '*',
  DOORINVIS   = 'X',
  RESETBUTTON = 'E',
  HINTBUTTON  = '&',
  RBUTTON_PR  = '@',
  HBUTTON_PR  = 'H',
  WALL        = '#',
  RARROW      = '>',
  LARROW      = '<',
  DARROW      = '$',
  UARROW      = '^',
  P_UP1       = 'D', /* player directional sprites and animation */
  P_UP2       = '/',
  P_UP3       = '?',
  P_DOWN1     = 'U',
  P_DOWN2     = ';',
  P_DOWN3     = ':',
  P_L1        = 'L',
  P_L2        = '{',
  P_L3        = '(',
  P_R1        = 'R',
  P_R2        = '}',
  P_R3        = ')'
} etype;

/* FORWARD DEDCLARATIONS */
struct display;
typedef struct display Display;

struct entity;
typedef struct entity entity;

struct cell;
typedef struct cell cell;
