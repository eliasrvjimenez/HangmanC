#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>

#define ALPHA_SIZE 26
#define BUF_SIZE 64
#define WORDS 212 // Change to include custom words

typedef struct {
    char word[BUF_SIZE];
    int word_size;
    char guessed_word[BUF_SIZE];
    char guessed_letters[ALPHA_SIZE+1]; // +1 for null terminator
} hangman_struct;

/*
 * Opens src/words.txt and grabs a "random" word to be 
 * used in the game.
 * */
int load_word (); 


/*
 * checks if the given character was used.
 * */
int check_if_used (char c);

/*
 * Checks if character is in the word
*/
int check_in (char c, char arr[]);


/*
 * Updates the Hangman String if the given character is correct.
 * takes a single char c that represents the guess given.
 *  */
void update_hangman (char c);