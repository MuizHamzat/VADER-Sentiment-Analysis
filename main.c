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

    //print a line from the dictionary
    int line = 7216;
    printf("%s, %.1f, %.5f [", lexiconDictionary[line-1].word, lexiconDictionary[line-1].value1, lexiconDictionary[line-1].value2);

    for (int i=0; i < ARRAY_SIZE; i++){
        printf("%d ", lexiconDictionary[line-1].intArray[i]);
    }
    printf("]\n");

    float score = calculateSentimentScore("risky robber", lexiconDictionary, lexiconSize);

    printf("%f\n", score);

    fclose(lexicon);

   free(lexiconDictionary);
}