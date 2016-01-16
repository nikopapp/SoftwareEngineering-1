#include "encryption.h"

int encryption(Display *d)
{
  char rand_word[LENGTH], shuffle_word[LENGTH], original_word[LENGTH];
  char hintWord[HINTLENGTH];
  int i, word_size, j, yinit = 9, xinit, cnt=0, in, printHint=0, resetsent = 0;
  int hintNum=0;
  cell grid[H][W];
  entity *player, *door1, *door2, *rbutton, *hbutton;

  initGrid(grid);
  hintNum=enc_getWord(rand_word);
  enc_getHint(hintWord, hintNum-1);
  word_size = strlen(rand_word);
  rand_word[word_size]='\0';

  // here we make sure the word always apears in the middle
  xinit = (W/2) - (word_size/2);
  strcpy(shuffle_word, rand_word);
  enc_shuffle(shuffle_word, word_size);
  strcpy(original_word, shuffle_word);
  player = grid[8][3].foreground = newEntity(passable,P_R1,3,8);
  door1 = grid[7][W-4].background = newEntity(impassable,DOORCLOSED,W-4,7);
  door2 = grid[7][3].background = newEntity(impassable,DOORCLOSED,3,7);

  /* place the word in the grid */
  for (j=0; j<word_size; j++){
    enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
  }
  makeBoundariesEncryption(grid);
  grid[yinit][xinit-1].background = newEntity(passable, LARROW ,xinit-1,yinit);
  grid[yinit][xinit + word_size].background = newEntity(passable, RARROW ,xinit + word_size, yinit);

  rbutton = grid[7][1].background = newEntity(impassable, RESETBUTTON,7,1);
  hbutton = grid[7][16].background = newEntity(impassable, HINTBUTTON,7,16);
  fillGrid(grid);   /* layer of floortiles */

  encGameDraw(d, grid, printHint, hintWord, resetsent);

  /* MAIN LOOP */
  while(in!=10){
    fprintf(OUTPUT, "line = %d\n", hintNum);

    in=input(d);

    if (grid[player->y][player->x].background == door1|| grid[player->y][player->x].background == door2) {
      freeEntityMem(grid);  /* free memory */
      return 0;
    }
    resetsent = 0;
    changeEntity(rbutton, RESETBUTTON);
    if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
      move(&grid[player->y][player->x],player->x,player->y,(direction)in,grid);
      printGrid(grid);
    }
    if (in == 9) { /*checks for spacebar */
      if(grid[player->y][player->x].background->type == DARROW) {// "$" is now the down arrow symbol
          // enc_shiftLetter(grid, player->y, player->x);
        enc_updateLetter(grid, player->y, player->x);
        Mix_PlayChannel( -1, d->zap, 0 );
        }
      else if(grid[player->y][player->x].background->type == UARROW) {
        // enc_shiftLetter(grid, player->y, player->x);
        enc_updateLetter(grid, player->y, player->x);
        Mix_PlayChannel( -1, d->zap, 0 );
      }
      else if(grid[player->y][player->x].background->type == RARROW) {
        enc_changeRow(shuffle_word, word_size, -1);
        for (j=0; j<word_size; j++){
          enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
        }
        Mix_PlayChannel( -1, d->zap, 0 );
      }
      else if(grid[player->y][player->x].background->type == LARROW) {
        enc_changeRow(shuffle_word, word_size, 1);
        for (j=0; j<word_size; j++){
          enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
        }
        Mix_PlayChannel( -1, d->zap, 0 );
      }
      else if(grid[player->y-1][player->x].background->type == RESETBUTTON) {
        for (i=0; i<word_size; i++){
          enc_newLetter(grid, xinit+i, yinit, original_word[i]);
        }
        resetsent = 1;
        changeEntity(rbutton, RBUTTON_PR);
        Mix_PlayChannel( -1, d->zap, 0 );
      }
      else if(grid[player->y-1][player->x].background == hbutton) {
        printHint = !printHint;
        if (hbutton->type == HINTBUTTON) {
          changeEntity(hbutton, HBUTTON_PR);
        }
        else {
          changeEntity(hbutton, HINTBUTTON);
        }
        Mix_PlayChannel( -1, d->zap, 0 );
      }
    }
    enc_updateWord(grid, yinit, xinit, shuffle_word);
    if(strcmp(shuffle_word, rand_word)==0){
      changeEntity(door1, DOOROPEN);
      changePassable(door1,passable);
      changeEntity(door2, DOOROPEN);
      changePassable(door2,passable);
    }
    printGrid(grid);
    encGameDraw(d, grid, printHint, hintWord, resetsent);
    enc_print_ascii(grid[yinit][player->x].background->type);

    cnt++;
  }
  freeEntityMem(grid);  /* free memory */
  return 1;
}



void makeBoundariesEncryption(cell grid[H][W])
{
  int i;
  for (i = 0; i < W; i++) {
    if (i != W-2 && i != W-4 && i != 3 && i != 1) { /* non-wall locations*/
      newLimit(grid, i, 7);
    }
  }
}

void encGameDraw(Display *d, cell grid[H][W], int printHint, char hintWord[HINTLENGTH], int resetsent) {
  int line = 0;
  drawBackground(d, BG_ENC);
  fprintf(OUTPUT, "hint word%s\n", hintWord); 
  drawEntities(d, grid);

  line += drawString(d, fontdata, INTROSTRING, SCRNSTARTX, SCRNSTARTY, normal,0);

  if(resetsent==1){
    line += drawString(d, fontdata, "RESET SIGNAL SENT", SCRNSTARTX,
      SCRNSTARTY + line, warning,0);
  }
  if(printHint==1){
    line += drawString(d, fontdata, "\nHINT:", SCRNSTARTX,
      SCRNSTARTY + line, normal,0);
    drawString(d, fontdata, hintWord, SCRNSTARTX,
      SCRNSTARTY + line, normal,0);
  }
  drawString(d, fontdata, (char*)"EXIT", 177, 410, yellow,1);
  drawString(d, fontdata, (char*)"EXIT", 879, 410, yellow,1);
  drawFrame(d, REFRESH_RATE);
}



void enc_print_ascii(char letter){
   if ((letter < 'a') || (letter > 'z')){
      fprintf(OUTPUT, "ascii code: %c\n",' ' );
   }
   else{
   fprintf(OUTPUT, "ascii code: %d\n", letter);
   }
}

void enc_updateWord(cell grid[H][W], int y, int x, char shuffle[LENGTH]){

   int i=0, size=strlen(shuffle);

   for( i=0; i<size; i++){
      shuffle[i] = grid[y][x++].background->type;
   }
}

int enc_getWord(char str[LENGTH]){
  FILE *file=fopen("encWords.txt", "r");
  int line=rand()%encLineCount(), cnt=0; //find a random line
  for(cnt=0; cnt<=line; cnt++){
    fgets(str, LENGTH, file);
  }
  str[strcspn(str, "\n")]='\0'; //removes the newline
  return cnt;
}

void enc_getHint(char str[HINTLENGTH], int line){
  FILE *file=fopen("encHints.txt", "r");
  int cnt=0; //find a random line
  for(cnt=0; cnt<=line; cnt++){
    fgets(str, HINTLENGTH, file);
  }
  str[strcspn(str, "\n")]='\0'; //removes the newline
}



int encLineCount(void){
  FILE *file=fopen("encWords.txt", "r");
  char str[LENGTH];
  int cnt=0;
  while(fgets(str, LENGTH, file)!=NULL){
    fprintf(OUTPUT, "loaded string\n");
    cnt++;
  }
  return cnt;
}

// this is function ensures vowels change only to vowels and likewise with consonants.
// currently unused.
void enc_shiftLetter(cell grid[H][W], int y, int x){
   entity *e;

   e = grid[y][x].background->pointsto;
   if (isvowel(e->type)){
      do {
         enc_updateLetter(grid, y, x);
         e = grid[y][x].background->pointsto;
      } while(isvowel(e->type) == FALSE);
   }
   else if ( ! (isvowel(e->type))) {
      do {
         enc_updateLetter(grid, y, x);
         e = grid[y][x].background->pointsto;
      } while(isvowel(e->type) == TRUE);
   }
}

void enc_updateLetter(cell grid[H][W], int y, int x){

   if (grid[y][x].background->type == DARROW) {
    enc_letterDown(grid[y][x].background->pointsto);
   }
   if (grid[y][x].background->type == UARROW){
    enc_letterUp(grid[y][x].background->pointsto);
   }
}

void enc_letterDown(entity *e){
   int letter = (int) e->type;

   if( letter == (int) 'a'){
      letter += 25;
      e->type = (char) letter;
   }
   else{
      letter--;
      e->type = (char) letter;
   }
}

void enc_letterUp(entity *e){
   int letter = (int) e->type;

   if( letter == (int) 'z'){
      letter -= 25;
      e->type = (char) letter;
   }
   else{
      letter++;
      e->type = (char) letter;
   }
}

void enc_newLetter(cell grid[H][W], int x, int y, char c){
  grid[y][x].background = newEntity(passable, c, x, y);
  grid[y-1][x].background = newEntity(passable,UARROW ,x,y-1);
  grid[y-1][x].background->pointsto = grid[y][x].background;
  grid[y+1][x].background = newEntity(passable,DARROW ,x,y-1);
  grid[y+1][x].background->pointsto = grid[y][x].background;
}

int enc_shuffle(char word[LENGTH], int size){
  int game ;

  game = rand()%3;
  switch (game){
    case 0:
      // printf("we are going to change a vowel\n\n");
      enc_change(word, size, game);
      break;
    case 1 :
      // printf("we are going to change a constant\n\n" );
      enc_change(word, size, game);
      break;
    case 2 :
      // printf("we are going to switch the whole row\n\n" );
      enc_changeRow(word, size, 0);
      break;
  }
  return game;
}

void enc_changeRow(char word[LENGTH], int size, int shift){
  int i;
  if(shift==0){
  shift = rand()%(ALPHABET-1)+1;
  // printf("shift = %d\n", shift);
 }
  for (i=0; i<size; i++){
    word[i] = word[i] - shift;
    if ((int)word[i] > (int) 'z'){
      word[i] = word[i] - ALPHABET;
    }
    else if ((int)word[i] < (int) 'a'){
      word[i] = word[i] + ALPHABET;
    }
  }
}

void enc_change(char word[LENGTH], int size, int game){
  int condition=TRUE, letter, i;
  char c;

  do {
    if (game == 0){
      letter = rand()%size; /* pick random letter*/
      if(isvowel(word[letter])){ /* see if the letter is a enc_vowel*/
        if((c=enc_vowel()) != word[letter]){ /* see if the enc_vowel is different of the on I had */
          for (i=0; i<size; i++){
            if (word[i] == word[letter]){ /* I want to check if there are more */
              word[i] = c;                /* than one same letters in my initial word */
              condition = FALSE;
            }
          }
        }
      }
    }
    else if (game == 1 ){
      letter = rand()%size; /* same here  */
      if(isvowel(word[letter]) == 0){
        if((c=enc_constant()) != word[letter]){
          for (i=0; i<size; i++){
            if (word[i] == word[letter]){
              word[i] = c;
              condition = FALSE;
            }
          }
        }
      }
    }
  } while (condition);
}

char enc_vowel(){
  char letter[] = {'a','e','i','o','u'};
  return letter[rand()%5];
}

char enc_constant(){
  char letter[] = {'b','c','d','f','g','h','j','k','l','m','n','p','q',
                    'r','s','t','v','w','x','y','z'};
  return letter[rand()%21];
}

int isvowel(char c){
   c=tolower(c);
   if ((c=='a') || (c=='e') || (c=='i') || (c=='o') || (c=='u')){
      return 1;
   }
   else{
      return 0;
   }
}
