# All Target
all: battleships.o battleships_game.o
	gcc -Wextra -Wall -Wvla -std=c99 battleships.o battleships_game.o -o ex2.exe

battleships.o: battleships.c battleships.h
	gcc -c battleships.c

battleships_game.o: battleships.c battleships.h
	gcc -c battleships_game.c

# clean
clean:
	rm -f *.o ex2.exe

# tar
tar:
	tar cvf ex2.tar battleships.c battleships.h battleships_game.c Makefile


