#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

int main(){
    //Open VADER lexicon file
    FILE *lexicon = fopen("vader_lexicon.txt", "r");
    if (lexicon == NULL){
        printf("Error opening file. Exiting...");
        return 1;
    }

    int *lexiconSize;

    WordData *lexiconDictionary = createLexiconDictionary(lexicon, lexiconSize);

    for (int i=0; i < ARRAY_SIZE; i++){
        //For some reason, removing this for loop causes a slightly longer runtime, then prints nothing to the terminal. Will fix after implementations
    }

    float score = calculateSentimentScore("VADER is very SMART, handsome, and FUNNY", lexiconDictionary, lexiconSize);

    printf("%f\n", score);

    fclose(lexicon);

    free(lexiconDictionary);
}