all: main

main: main.c vaderSentiment.c utility.h
	gcc -o main main.c vaderSentiment.c utility.h


clean:
	rm -f main