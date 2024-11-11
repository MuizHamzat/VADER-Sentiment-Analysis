#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

WordData* createLexiconDictionary(FILE *file){
    //Count the number of lines in the file
    int count = 0;
    char c;
    while((c = fgetc(file)) != EOF){//fgetc() returns each character in the file (in sequence) every time it's called. So if there is a text file that just says "Hello World!", it will return 'H' in the first loop, then 'e', then 'l'. Once it reaches the end of the file, it will return 'EOF'.

        if (c == '\n'){count++;}
    } 

    WordData *lexiconDictionary = malloc(sizeof(WordData) * count);

    //Add data from file to dictionary
    int i,j;
    while (i < count){
        WordData line = lexiconDictionary[i];
        if (fscanf(file, "%s %f %f", line.word, &line.value1, &line.value2) != 3){break;} //fscan() will return the number of successful inputs it's able to read (in this case, 3). If it reads less than 3 items, then there was an issue reading the file, so it will exit the loop

        //Read the values from the distribution array
        for (j=0; j < ARRAY_SIZE; j++){
            if (fscanf(file, "%d", &line.intArray[j]) != 1){
                printf("Error reading array. Exiting...\n");
                exit(1);
            }
        }

        i++;
    }

    return lexiconDictionary;

}
