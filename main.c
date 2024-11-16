#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

void TestCase(char *sentence, WordData *lexiconDictionary, int n);

int main(){
    //Open VADER lexicon file
    FILE *lexicon = fopen("vader_lexicon.txt", "r");
    if (lexicon == NULL){
        printf("Error opening file. Exiting...");
        return 1;
    }

    int lexiconSize = countLines(lexicon);

    WordData *lexiconDictionary = createLexiconDictionary(lexicon);

    //Test Cases
    TestCase("VADER is smart, handsome, and funny.", lexiconDictionary, lexiconSize);
    TestCase("VADER is smart, handsome, and funny!", lexiconDictionary, lexiconSize);
    TestCase("VADER is very smart, handsome, and funny.", lexiconDictionary, lexiconSize);
    TestCase("VADER is VERY SMART, handsome, and FUNNY.", lexiconDictionary, lexiconSize);
    TestCase("VADER is VERY SMART, handsome, and FUNNY!!!", lexiconDictionary, lexiconSize);
    TestCase("VADER is VERY SMART, uber handsome, and FRIGGIN FUNNY!!!.", lexiconDictionary, lexiconSize);
    TestCase("VADER is not smart, handsome, nor funny.", lexiconDictionary, lexiconSize);
    TestCase("At least it isn't a horrible book.", lexiconDictionary, lexiconSize);
    TestCase("The plot was good, but the characters are uncompelling and the dialog is not great.", lexiconDictionary, lexiconSize);
    TestCase("Make sure you :) or :D today!.", lexiconDictionary, lexiconSize);
    TestCase("Not bad at all", lexiconDictionary, lexiconSize);

    fclose(lexicon);

    free(lexiconDictionary);
}

void TestCase(char *sentence, WordData *lexiconDictionary, int n){
    float compound = calculateSentimentScore(sentence, lexiconDictionary, n);
    printf("Sentence: %s; Compound Score: %.4f\n", sentence, compound);
    return;
}