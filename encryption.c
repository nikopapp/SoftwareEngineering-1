/*next steps
1. implemnet the grid
2. implement key presses with SDL
3. test if everything works*/
#include "encryption.h"

#define gridSize 10

void enc_shufle(char word[LENGTH], int size);
int enc_isenc_vowel(char c);
char enc_vowel();
char enc_constant();
void enc_changeRow(char word[LENGTH], int size);
void enc_change(char word[LENGTH], int size, int game);
void enc_printGrid(char grid[gridSize][gridSize]); //hello

int encryption(void)
{

  char *list[] = {"frondo", "gandalf","elrond", "legolas", "gimli", "aragorn","saouron"};
  char rand_word[LENGTH], shuffle_word[LENGTH];
  int i, word_size;
  char grid[gridSize][gridSize];

  srand(time(NULL));

  if (sscanf(list[(rand()%LIST_SIZE)], "%s", rand_word) != 1){
    printf("couldn't get a word from the list\n");
    return 1;
  }
  word_size = strlen(rand_word);
  for (i=0; i<word_size; i++){
    shuffle_word[i] = rand_word[i];
  }
  shuffle_word[word_size] = '\0';

  printf("\nThe initial word is %s and ", shuffle_word);
  enc_shufle(shuffle_word, word_size);
  printf("%s\n", shuffle_word);
  enc_printGrid(grid);

  /*if (strcmp(given_word,list_word1) == 0){
    condition = FALSE;
  }*/
  return 0;
}

void enc_printGrid(char grid[gridSize][gridSize]){
  int cntW, cntH;
  for (cntH=0; cntH<gridSize; cntH++){
    for (cntW=0; cntW<gridSize; cntW++){
      if ((cntH == 0) || (cntH == (gridSize-1))){
          grid[cntH][cntW] = '_';
      }
      else if ((cntW==0) || (cntW == (gridSize-1))){
        grid[cntH][cntW] = '|';
      }
      else{
          grid[cntH][cntW]=' ';
      }
      printf("%c", grid[cntH][cntW]);
      if(grid[cntH][cntW]=='\0'){
        printf("0");
      }
    }
    printf("\n");
  }
}

void enc_shufle(char word[LENGTH], int size)
{
  int game ;

  game = rand()%3;
  switch (game){
    case 0:
      printf("we are going to enc_change a enc_vowel\n\n");
      enc_change(word, size, game);
      break;
    case 1 :
      printf("we are going to enc_change a enc_constant\n\n" );
      enc_change(word, size, game);
      break;
    case 2 :
      printf("we are going to switch the whole row\n\n" );
      enc_changeRow(word, size);
      break;
  }
}

void enc_change(char word[LENGTH], int size, int game)
{
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

void enc_changeRow(char word[LENGTH], int size)
{
  int shift, i;

  shift = rand()%ALPHABET;
  for (i=0; i<size; i++){
    word[i] = word[i] - shift;
    if ((int)word[i] < (int) 'a'){
      word[i] = word[i] + ALPHABET;
    }
  }
}

int enc_isenc_vowel(char c)
{
  c=tolower(c);
  if ((c=='a') || (c=='e') || (c=='u') || (c=='o') || (c=='i')){
	return 1;
  }
  else{
    return 0;
  }
}

char enc_vowel()
{
  char letter[] = {'a','e','i','o','u'};
  return letter[rand()%5];
}

char enc_constant()
{
  char letter[] = {'b','c','d','f','g','h','j','k','l','m','n','p','q',
                    'r','s','t','v','w','x','y','z'};
  return letter[rand()%21];
}
