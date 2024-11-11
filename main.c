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

    WordData *lexiconDictionary = createLexiconDictionary(lexicon);

    printf("%s, %.1f, %.5f, [", lexiconDictionary[7520].word, lexiconDictionary[7520].value1, lexiconDictionary[7520].value2);

    for (int i=0; i < ARRAY_SIZE; i++){
        printf("%d ", lexiconDictionary[7520].intArray[i]);
    }
    printf("]\n");

    fclose(lexicon);

    for (int i=0; i < 7520; i++){
        free(lexiconDictionary);
    }
}