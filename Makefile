all: main

main: main.c vaderSentiment.c utility.h
	gcc -o main main.c vaderSentiment.c utility.h -lm


clean:
	rm -f main