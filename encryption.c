#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define LENGTH 30
#define LIST_SIZE 7
#define ALPHABET 26

void shufle(char word[LENGTH], int size);
int isvowel(char c);
char vowel();
char constant();
void changeRow(char word[LENGTH], int size);
void change(char word[LENGTH], int size, int game);





int main(void)
{


  char *list[] = {"frondo", "gandalf","elrond", "legolas", "gimli", "aragorn","saouron"};
  char rand_word[LENGTH], shuffle_word[LENGTH];
  int i, word_size;

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
  shufle(shuffle_word, word_size);
  printf("%s\n", shuffle_word);



  /*if (strcmp(given_word,list_word1) == 0){
    condition = FALSE;
  }*/
  return 0;
}

void shufle(char word[LENGTH], int size)
{
  int game ;

  game = rand()%3;
  switch (game){
    case 0:
      printf("we are going to change a vowel\n\n");
      change(word, size, game);
      break;
    case 1 :
      printf("we are going to change a constant\n\n" );
      change(word, size, game);
      break;
    case 2 :
      printf("we are going to switch the whole row\n\n" );
      changeRow(word, size);
      break;
  }
}

void change(char word[LENGTH], int size, int game)
{
  int condition=TRUE, letter, i;
  char c;

  do {
    if (game == 0){
      letter = rand()%size; /* pick random letter*/
      if(isvowel(word[letter])){ /* see if the letter is a vowel*/
        if((c=vowel()) != word[letter]){ /* see if the vowel is different of the on I had */
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
      letter = rand()%size; /* same here */
      if(isvowel(word[letter]) == 0){
        if((c=constant()) != word[letter]){
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
void changeRow(char word[LENGTH], int size)
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
int isvowel(char c)
{
  if ((c=='a') || (c=='A') ||(c=='e') || (c=='E') || (c=='u') || (c=='U') || (c=='o') || (c=='O')
      || (c=='i') || (c=='I')){
	return 1;
  }
  else{
    return 0;
  }
}
char vowel()
{
  char letter[] = {'a','e','i','o','u'};
  return letter[rand()%5];
}
char constant()
{
  char letter[] = {'b','c','d','f','g','h','j','k','l','m','n','p','q',
                    'r','s','t','v','w','x','y','z'};
  return letter[rand()%21];
}
