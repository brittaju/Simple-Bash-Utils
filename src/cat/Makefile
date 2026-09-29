CC = gcc 
CFLAGS = -Wall -Werror -Wextra -std=c11 -D_DEFAULT_SOURCE

all : s21_cat

s21_cat : s21_cat.c s21_cat.h
	$(CC) $(CFLAGS) s21_cat.c -o s21_cat

clean :
	rm -f s21_cat

rebuild :
	clean all