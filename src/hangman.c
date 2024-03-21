#include "hangman.h"

hangman_struct *hangman;

char lower_alpha[] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};

int load_word () {
    FILE *fptr = fopen("words.txt", "r"); // change to include custom word list
    if (fptr == NULL) {
        perror("Error loading words file");
        exit(EXIT_FAILURE);
    }

    //
    
    //Generating random line number
    srand(time(NULL));
    int random_line = rand() % WORDS;

    char *line = NULL;
    size_t len = 0;
    int bytes_read;
    int current_line = 0;

    while((bytes_read = getline(&line, &len, fptr)) != -1) {
        if (current_line == random_line) {
            // debug printf("random line = %d, current_line=%d\n", random_line, current_line);
            if (bytes_read != -1) {
                line[strlen(line)-1]='\0';
                // debug printf("Random line: %s\n", line);
                fclose(fptr);
                strcpy(hangman->word, line);
                hangman->word_size = strlen(line);
                free(line);
                return 0;
            }
        }
        current_line++;
    }
    fclose(fptr);
    fprintf(stderr, "Failed to read from words.txt\n");
    return -1;
}
int check_if_used (char c) {
    int len = strlen(hangman->guessed_letters);
    for (int i = 0; i<len; i++) {
        if (c == hangman->guessed_letters[i]) {
            return -1;
        }
    }
    hangman->guessed_letters[len] = c;
    hangman->guessed_letters[len+1] = '\0';
    return 0;
}
int check_in(char c, char arr[]) {
    int len = strlen(arr);
    for (int i = 0; i<len; i++) {
        if (c == arr[i]) {
            return 0;
        }
    }
    return -1;
}

void update_hangman (char c) {
    for (int i = 0; i<hangman->word_size; i++) {
        if (c == hangman->word[i]) { 
            hangman->guessed_word[i] = c;
        }
    }
    return;
}

int main () {
    printf("Starting Hangman...\n");
    hangman = malloc(sizeof(hangman_struct));
    hangman->guessed_letters[0] = '\0';
    if (load_word() == -1) {
        fprintf(stderr, "load_file() failed:");
        exit(EXIT_FAILURE);
    }

    //printf("Hangman Struct's word: %s\n", hangman->word);
    //printf("word length: %d\n", hangman->word_size);
    int lives = 7;
    for (int i = 0; i <hangman->word_size; i++) {
        strcat(hangman->guessed_word, "*");
    }

    do {
        if (strcasecmp(hangman->word,hangman->guessed_word) == 0) {
            printf("\nYou Win! The word was : %s\n", hangman->word);
            free(hangman);
            return 0;
        }
        printf("\nGuess: %s\nWord length: %d\nLives: %d\nGuessed Letters: %s\n", 
                hangman->guessed_word, hangman->word_size, lives, hangman->guessed_letters);
        char guess;
        printf("Guess a letter (a-z): ");
        scanf("%s", &guess);
        if (check_in(guess, lower_alpha) == 0) {
            
            if (check_if_used(guess) == 0) {
               
                if (check_in(guess, hangman->word) == 0) {
                   
                    update_hangman(guess);
                } else {
                    printf("\n%c is not in the word!\n", guess);
                    lives--;
                }
            } else {
                printf("\n%c was already guessed!\n", guess);
            }
        } else {
            printf("\nNot a valid guess, must be (a-z)\n");
        }
    } while (lives > 0);

    printf("You ran out of lives! The word was: %s\n", hangman->word);
    free(hangman);
    return 0;
}