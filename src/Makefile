CC = gcc
FLAGS = -Wall -Werror -Wextra

all: clang sborka 

sborka: pong.c 
	$(CC) $(FLAGS)  pong.c -o main

clang: 
	clang-format -i pong.c