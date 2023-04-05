CC = gcc
FLAGS = -Wall -Werror -Wextra

all: sborka go

sborka: pong.c 
	$(CC) $(FLAGS)  pong.c -o main

clang: 
	clang-format -i pong.c

git: 
	git add . 
	git commit -m"make commit"
	git push origin main

go:
	./main