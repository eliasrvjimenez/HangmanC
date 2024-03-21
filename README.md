# Very Simple C Hangman #
***Created By Elias Vera-Jimenez***

## To compile ##
Use CMAKE (minimum version 3.28.3) to compile in `build/`.

```zsh
../HangmanC/build > cmake ..
    ... <creating cmake files>
../HangmanC/build > cmake --build .
```
Then just run:


```zsh
../HangmanC/build/> ./hangman
```

To use custom words or add words to words.txt, go into hangman.h and increment/decrement by the number of lines in the words.txt -1 to properly generate the word randomly.

