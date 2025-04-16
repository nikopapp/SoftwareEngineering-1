#include "game.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1
#define LENGTH 30
#define LIST_SIZE 7
#define ALPHABET 26
#define VOWEL 1
#define CONSONANT 2
#define ROW 3
#define HINTLENGTH 200
#define INTROSTRING "Can you unscramble the word?\nUse the arrow buttons on the floor to try!\n\nIf you get stuck, try the 'hint' or 'reset' buttons"
#define SCRNSTARTY 66
#define SCRNSTARTX 224
#define LOW_TO_CAP 32

int enc_shuffle(char word[LENGTH], int size);
char enc_vowel();
char enc_constant();
void enc_changeRow(char word[LENGTH], int size, int shift);
void enc_change(char word[LENGTH], int size, int game);
void encrytionGridInit(char *shuffle_word);
void enc_newLetter(cell grid[H][W], int x, int y, char c);
void enc_shiftLetter(cell grid[H][W], int y, int x);
void enc_updateLetter(cell grid[H][W], int y, int x);
void enc_letterDown(entity *e);
void enc_letterUp(entity *e);
void enc_updateWord(cell grid[H][W], int y, int x, char shuffle[LENGTH]);
int isvowel(char c);
int enc_getWord(char str[LENGTH]);
int encLineCount(void);
void enc_getHint(char str[40], int line);

void makeBoundariesquizGame(cell grid[H][W]);
void encGameDraw(Display *d, cell grid[H][W], int printHint, char hintWord[HINTLENGTH], int resetsent, char letter);
