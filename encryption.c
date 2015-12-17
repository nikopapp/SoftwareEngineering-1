#include "encryption.h"

int encryption(Display *d)
{
  char rand_word[LENGTH], shuffle_word[LENGTH], original_word[LENGTH];
  char hintWord[HINTLENGTH];
  int i, word_size, j, yinit = 9, xinit, cnt=0, in, printHint=0, resetsent = 0;
  int hintNum=0, in_prev=0, count=0;
  cell grid[H][W];
  entity *player, *door1, *door2;
  initGrid(grid);
  hintNum=enc_getWord(rand_word);
  enc_getHint(hintWord, hintNum-1);
  word_size = strlen(rand_word);
  rand_word[word_size]='\0';

  // here we make sure the word always apears in the middle
  xinit = (W/2) - (word_size/2);
  strcpy(shuffle_word, rand_word);
  enc_shufle(shuffle_word, word_size);
  strcpy(original_word, shuffle_word);
  player = grid[8][3].foreground = newEntity(passable,'R',3,8);
  door1 = grid[7][W-4].background = newEntity(impassable,'*',W-4,7);
  door2 = grid[7][3].background = newEntity(impassable,'*',3,7);

  /* place the word in the grid */
  for (j=0; j<word_size; j++){
    enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
  }
  makeBoundariesEncryption(grid);
  grid[yinit][xinit-1].background = newEntity(passable,'<',xinit-1,yinit);
  grid[yinit][xinit + word_size].background = newEntity(passable,'>',xinit + word_size, yinit);
  grid[7][1].background = newEntity(impassable,'E',7,1);
  grid[7][16].background = newEntity(impassable,'&',7,16);
  fillGrid(grid);   /* layer of floortiles */

  encGameDraw(d, grid, printHint, hintWord, resetsent);

  /* MAIN LOOP */
  while(!d->finished){
    printf("line = %d\n", hintNum);

    in=input(d);
    resetsent = 0;
    if( (in > 0) && (in < 5) ){ /*checks for arrowkeys */
      move(&grid[player->y][player->x],player->x,player->y,(direction)in,grid);
      printGrid(grid);
      count = next_movment(count, &in_prev, in);
      updatePlayerfacing(player,(direction)in, count);
    }
    if (in == 9) { /*checks for spacebar */
      if(grid[player->y][player->x].background->type == '$') {// "$" is now the down arrow symbol
          // enc_shiftLetter(grid, player->y, player->x);#
        enc_updateLetter(grid, player->y, player->x);  
        }
      else if(grid[player->y][player->x].background->type == '^') {
        // enc_shiftLetter(grid, player->y, player->x);
        enc_updateLetter(grid, player->y, player->x);
      }
      else if(grid[player->y][player->x].background->type == '>') {
        enc_changeRow(shuffle_word, word_size, -1);
        for (j=0; j<word_size; j++){
          enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
        }
      }
      else if(grid[player->y][player->x].background->type == '<') {
        enc_changeRow(shuffle_word, word_size, 1);
        for (j=0; j<word_size; j++){
          enc_newLetter(grid, xinit+j, yinit, shuffle_word[j]);
        }
      }
      else if(grid[player->y-1][player->x].background->type == 'E') {// "E" is now the reset letter
        for (i=0; i<word_size; i++){
          enc_newLetter(grid, xinit+i, yinit, original_word[i]);
        }
        resetsent = 1;
      }
      else if(grid[player->y-1][player->x].background->type == '&') {// "&" is now the hint symbol
        printHint=1;
      }
    }
    enc_updateWord(grid, yinit, xinit, shuffle_word);
    if(strcmp(shuffle_word, rand_word)==0){
      changeEntity(door1,'%');
      changePassable(door1,passable);
      changeEntity(door2,'%');
      changePassable(door2,passable);
    }
    printGrid(grid);
    encGameDraw(d, grid, printHint, hintWord, resetsent);
    enc_print_ascii(grid[yinit][player->x].background->type);
    if (grid[player->y][player->x].background == door1|| grid[player->y][player->x].background == door2) {
      freeEntityMem(grid);  /* free memory */
      return 0;
    }
    cnt++;
  }
  freeEntityMem(grid);  /* free memory */
  return 0;
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
  drawBackground(d,3);
  printf("hint word%s\n", hintWord);
  drawEntities(d, grid);
  if(resetsent==1){
    drawString(d, fontdata, "RESET", SCRNSTARTX, SCRNSTARTY);
    line+= FNTHEIGHT;
  }
  if(printHint==1){
    drawString(d, fontdata, hintWord, SCRNSTARTX, SCRNSTARTY + line);
  }
  drawString(d, fontdata, "EXIT", 175, 420);
  drawString(d, fontdata, "EXIT", 875, 420);
  drawFrame(d, REFRESH_RATE);
}



void enc_print_ascii(char letter){
   if ((letter < 'a') || (letter > 'z')){
      printf("ascii code: %c\n",' ' );
   }
   else{
   printf("ascii code: %d\n", letter);
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
  str[strcspn(str, "\n")]='\0';
  return cnt;
}

void enc_getHint(char str[HINTLENGTH], int line){
  FILE *file=fopen("encHints.txt", "r");
  int cnt=0; //find a random line
  for(cnt=0; cnt<=line; cnt++){
    fgets(str, HINTLENGTH, file);
  }
  str[strcspn(str, "\n")]='\0';
}



int encLineCount(void){
  FILE *file=fopen("encWords.txt", "r");
  char str[LENGTH];
  int cnt=0;
  while(fgets(str, LENGTH, file)!=NULL){
    printf("fgst\n");
    cnt++;
  }
  return cnt;
}

// this is a new function that vowels change only to vowels and likewise with consonants
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

   if (grid[y][x].background->type == '$') {// cause 'v' may be part of the word
    enc_letterDown(grid[y][x].background->pointsto);
   }
   if (grid[y][x].background->type == '^'){
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
  grid[y-1][x].background = newEntity(passable,'^',x,y-1);
  grid[y-1][x].background->pointsto = grid[y][x].background;
  grid[y+1][x].background = newEntity(passable,'$',x,y-1);
  grid[y+1][x].background->pointsto = grid[y][x].background;
}

int enc_shufle(char word[LENGTH], int size){
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
      if(enc_isenc_vowel(word[letter])){ /* see if the letter is a enc_vowel*/
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
      if(enc_isenc_vowel(word[letter]) == 0){
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

int enc_isenc_vowel(char c){
  c=tolower(c);
  if ((c=='a') || (c=='e') || (c=='u') || (c=='o') || (c=='i')){
	return 1;
  }
  else{
    return 0;
  }
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
