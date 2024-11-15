all: main

main: main.c vaderSentiment.c utility.h
	gcc -o main main.c vaderSentiment.c utility.h -lm -Wall -Wextra -Wconversion -Wsign-conversion


clean:
	rm -f main