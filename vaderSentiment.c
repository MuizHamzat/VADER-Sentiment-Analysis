#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utility.h"

WordData* createLexiconDictionary(FILE *file){
    //Count the number of lines in the file
    int count = 0;
    char c;
    while((c = fgetc(file)) != EOF){//fgetc() returns each character in the file (in sequence) every time it's called. So if there is a text file that just says "Hello World!", it will return 'H' in the first loop, then 'e', then 'l'. Once it reaches the end of the file, it will return 'EOF'.

        if (c == '\n'){count++;}
    }

    //!!!Rewind the file since the pointer to the file is now at the end of the file. If you try to use fscanf() without rewinding, it will start at the end of the file
    rewind(file);

    WordData *lexiconDictionary = malloc(sizeof(WordData) * count);

    //Add data from file to dictionary
    char line[100];
    int i=0,j=0;
    while (i < count && fgets(line, sizeof(line), file) != NULL){ //fgets() will read a line and store it in the line[] buffer. sizeof(line) is the maximum amount of characters fgets() will read to prevent buffer overflow. If it successfully reads the line, it returns a pointer to line[]. Otheriwse, NULL

        //Read the 1st 3 values in the line
        if(sscanf(line, "%s %f %f", lexiconDictionary[i].word, &lexiconDictionary[i].value1, &lexiconDictionary[i].value2) != 3){
            printf("Problem reading word or sentiment values\n");
            break;
        }
        
        // if(fscanf(file, "%s %f %f", lexiconDictionary[i].word, &lexiconDictionary[i].value1, &lexiconDictionary[i].value2) != 3){
        //     printf("Problem reading file\n");
        //     break;
        // }

 //fscan() will return the number of successful inputs it's able to read (in this case, 3). If it reads less than 3 items, then there was an issue reading the file, so it will exit the loop

        //Find where the array of distribution starts in the line
        char *arrChar = strchr(line, '['); //Searches for '[' in the line, and returns a pointer to '['
        if (arrChar == NULL){
            printf("Problem finding array\n");
            break;
        }

        //Parse the array of distribution
        char *token = strtok(arrChar, "[, ]"); //Split the string into tokens (chars), with '[', ',' ' ', and ']' as delimiters
        while (token != NULL && j < ARRAY_SIZE){ //While there are more tokens to return & there are still indexes in the array:
            lexiconDictionary[i].intArray[j] = atoi(token); //Convert from string to int
            token = strtok(NULL, "[, ]"); //When you call strtok() the first time, you pass in the string to tokenize. For every call after that, you pass in NULL to continue tokenizing the same string
            j++;
        }
       

        printf("%s %f %f\n", lexiconDictionary[i].word, lexiconDictionary[i].value1, lexiconDictionary[i].value2);
        i++;
    }

    return lexiconDictionary;

}
