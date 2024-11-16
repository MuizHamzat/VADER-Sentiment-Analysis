#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "utility.h"

char posAmplifiers[13][MAX_STRING_LENGTH] = { 
    "absolutely", "completely", "extremely", "really", "so", "totally", "very", "particularly", "exceptionally", "incredibly", "remarkably", "uber", "friggin"
};

char negAmplifiers[9][MAX_STRING_LENGTH] = {
    "barely", "hardly", "scarcely", "somewhat", "mildly", "slightly", "partially", "fairly", "pretty much"
};

char negations[13][MAX_STRING_LENGTH] = {
    "not", "isn't", "doesn't", "wasn't", "shouldn't", "won't", "cannot", "can't", "nor", "neither", "without", "lack", "missing"
};

int countLines(FILE *file){
    int count = 0;
    char c;
    while((c = (char)fgetc(file)) != EOF){//fgetc() returns each character in the file (in sequence) every time it's called. So if there is a text file that just says "Hello World!", it will return 'H' in the first loop, then 'e', then 'l'. Once it reaches the end of the file, it will return 'EOF'.

        if (c == '\n'){count++;}
    }
    //!!!Rewind the file since the pointer to the file is now at the end of the file. If you try to use fscanf() without rewinding, it will start at the end of the file
    rewind(file);
    return count;
}

WordData* createLexiconDictionary(FILE *file){
    //Count the number of lines in the file
    int count = countLines(file);


    WordData *lexiconDictionary = malloc(sizeof(WordData) * (unsigned int)count);
    if (lexiconDictionary == NULL){
        printf("Memory allocation failed. Exiting...");
        exit(1);
    }

    //Add data from file to dictionary
    char line[100];
    int i=0;
    while (i < count && fgets(line, sizeof(line), file) != NULL){ //fgets() will read a line and store it in the line[] buffer. sizeof(line) is the maximum amount of characters fgets() will read to prevent buffer overflow. If it successfully reads the line, it returns a pointer to line[]. Otheriwse, NULL

        char *charInLine = line;

        //Extract the word's string by reading the line until we encounter a tab chararacter ('\t')
        int currentWordIndex = 0;
        while(*charInLine){
            if(*charInLine == '\t'){
                charInLine++; //Move past the space
                break;
            }
            lexiconDictionary[i].word[currentWordIndex] = *charInLine;
            currentWordIndex++;
            charInLine++;
        }
        lexiconDictionary[i].word[currentWordIndex] = '\0'; //Don't forget the null character

        //Read values 1 & 2 in the line
        if(sscanf(charInLine, "%f %f", &lexiconDictionary[i].value1, &lexiconDictionary[i].value2) != 2){
            printf("Problem reading sentiment values\n");
            break;
        }

 //sscan() will return the number of successful inputs it's able to read in the line (in this case, starting from wherever charInLine is pointing to). If it reads less than 2 items (the 2 float values), then there was an issue reading the file, so it will exit the loop

        //Find where the array of distribution starts in the line
        char *arrChar = strchr(charInLine, '['); //Searches for '[' in the line (starting from charInLine), and returns a pointer to '['
        if (arrChar == NULL){
            printf("Problem finding array\n");
            break;
        }

        //Parse the array of distribution
        int j=0;
        char *token = strtok(arrChar, "[, ]"); //Split the string into tokens (chars), with '[', ',' ' ', and ']' as delimiters
        while (token != NULL && j < ARRAY_SIZE){ //While there are more tokens to return & there are still indexes in the array:
            lexiconDictionary[i].intArray[j] = atoi(token); //Convert from string to int
            token = strtok(NULL, "[, ]"); //When you call strtok() the first time, you pass in the string to tokenize. For every call after that, you pass in NULL to continue tokenizing the same string
            j++;
        }
        i++;
    }

    return lexiconDictionary;
}


float calculateSentimentScore(char *sentence, WordData *lexiconDictionary, int n){
    
    //Copy the string and tokenize the copy
    char *tokSentence = malloc(strlen(sentence)+1); //We add plus 1 for the null character
    strcpy(tokSentence, sentence);
    char *word = strtok(tokSentence, " ,");

    //Go through each word in the sentence and determine it's value

    float totalScore = 0;
    int wordsInDictionary = 0;
    int numOfExclamations=0;
    float amplifier = 0;
    bool allCaps = false;
    bool negation = false;
    bool negationAllCaps = false;

    //Main loop. This loop will run for each word in the sentence
    while(word != NULL){
        //PUNCTUATION~~~~~
        //Check if it has exclamation marks in the string (or ends in a period)
        //We can iterate through the string and replace all the exclamation marks with other characters in the string, effectively removing the exclamation marks and leaving just the word
        int i=0,j=0;
        while (word[i] != '\0'){
            if (word[i] == '!'){numOfExclamations++;}
            else if (word[i] != '.' && word[i] != '?'){ //Get rid of periods
                word[j] = word[i]; //Copy the character i is on to j. word[j] will never be '!' since we skip copying any instances of '!'
                j++;
            }
            i++;
        }
        //Replace word[j] with '\0', which will end the string at j and get rid of any '!'s at the end
        word[j] = '\0';
        
        //ALL CAPS~~~~~
        //Allocate memory for an uppercase version of the word
        char *upperWord = malloc(strlen(word) + 1);
            if (upperWord == NULL){
                printf("Memory allocation failed. Exiting...");
                exit(1);
            }
        
        //Check if word is in all caps
        for (i=0; word[i] != '\0'; i++){upperWord[i] = (char)toupper(word[i]);}
        upperWord[strlen(word)] = '\0';
        //If word and upperWord are the same, then the word must be in ALLCAPS
        if (strcmp(word, upperWord) == 0){allCaps = true;}
        
        for (i=0; word[i] != '\0';i++){word[i] = (char)tolower(word[i]);} //If word is in ALLCAPS (or titled), make it lowercase so it can properly be identified in the lexicon


        //SCORE CALCULATION~~~~~
        //Find word in dictionary
        for (i=0; i < n; i++){
            if (strcmp(word, lexiconDictionary[i].word) == 0) {
                wordsInDictionary++;
                totalScore += lexiconDictionary[i].value1 * (allCaps ? 1.5f:1.0f) * (negation ? -0.5f * (negationAllCaps ? 1.5f:1.0f):1.0f) + (lexiconDictionary[i].value1 * amplifier);
                totalScore += (totalScore/fabsf(totalScore)) * 0.292f*(float)numOfExclamations;
                //If the word was in dictionary, then any amplifiers would've been applied to that word, so we "turn off" the amplifiers. If there is a negation, it will be applied to the rest of the sentence
                amplifier = 0;
                numOfExclamations=0;
            }
        }

        //INTENSIFIERS
        //Check if word is a positive amplifier
        for (i=0; i < 13; i++){
            if (strcmp(word, posAmplifiers[i]) == 0) {
                amplifier += (float)0.293 * (allCaps ? 1.5f:1.0f);
            }
        }
        //Check if word is a negative amplifier
        for (i=0; i < 9; i++){
            if (strcmp(word, negAmplifiers[i]) == 0) {
                amplifier -= (float)0.293 * (allCaps ? 1.5f:1.0f);
            }
        }
        //Check if word is a negator
        for (i=0; i < 13; i++){
            if (strcmp(word, negations[i]) == 0) {
                negation = true;
                if (allCaps){
                    negationAllCaps = true;
                }
            }
        }
        allCaps = false; // We reset allCaps outside of the dictionary check because a word might be all caps, but not in the dictionary (ex: VADER). So we want to reset allCaps every word, regardless of wether it's in the dictionary or not. We also want to consider if any of the intensifier words should be boosted by allCaps
        
        //Move on to the next word
        word = strtok(NULL, " ,");
        free(upperWord);
    }

    //Calculate compound score
    float compound = totalScore/sqrtf(totalScore*totalScore+15.0f);

    free(tokSentence);
    return compound;
}
