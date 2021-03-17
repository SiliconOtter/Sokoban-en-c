all: sokoban

sokoban : affichage.o gestion.o temps_text.o
	gcc -o sokoban affichage.o temps_text.o gestion.o  `sdl-config --libs --cflags` -l SDL_ttf

affichage.o: affichage.c Entete.h
	gcc -c affichage.c

gestion.o: gestion.c Entete.h
	gcc -c gestion.c
	
temps_text.o: temps_text.c Entete.h
	gcc -c temps_text.c
	
clean:
	rm -rf *.o
