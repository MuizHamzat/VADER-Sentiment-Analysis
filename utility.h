#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>

#define ARRAY_SIZE 10
#define MAX_STRING_LENGTH 50

typedef struct {
    char word[MAX_STRING_LENGTH];
    float value1; //Mean sentiment value
    float value2; //Standard deviation
    int intArray[ARRAY_SIZE]; //Array of sentiment ratings
} WordData;

WordData* createLexiconDictionary(FILE *file);

#endif