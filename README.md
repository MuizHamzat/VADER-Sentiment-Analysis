# VADER-Sentiment-Analysis

This was an assignment from my MECHTRON2MP3 course.

The purpose of this assignment was to create a program that can take a given string (so for example, an Instagram comment on a post), and return it's sentiment value, which is a score rangin from -1 to 1, with -1 being a very negative sentence, 0 being a neutral sentence, and 1 being a very positive sentence.

There is the ```vader_lexicon.txt``` file, which contains all the words that make up the lexicon and their sentiment scores (and where ```vaderSentiment.c``` reads from). There are test cases in ```main.c```, and all the implementation is in ```vaderSentiment.c```.

To compile and run the code in ```main.c```, type the following in the terminal:\
```gcc main.c utiliy.h vaderSentiment.c -lm```\
then run the executable.

You can also use the Makefile and simply type ```make```