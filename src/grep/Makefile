CC = gcc 
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_DEFAULT_SOURCE

all : s21_grep

s21_grep : s21_grep.c s21_grep.h
	$(CC) $(CFLAGS) s21_grep.c -o s21_grep

clean :
	rm -f s21_grep

rebuild :
	clean all