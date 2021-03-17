 
#ifndef Prototype
#define Prototype
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>

#define SIZE 15

#define VRAI 1
#define FAUX 0

/*gestion.c*/
char ** text_vers_tab2( char * nomfichier1);
void deplacement(char ** plateaux_1,char ** plateaux,int dest_x, int dest_y , int pos_x , int pos_y);
int is_victory(char ** plateaux,char ** plateaux_1);
void sokoban();

/*Affichage.c*/
void affichage_plateaux(char ** tab,char ** ref,SDL_Surface * ecran,int does_what);
SDL_Surface * initialisation_sdl();
void fin_sdl();
int boucleEv(char ** plateaux,SDL_Surface * ecran,int num_niveaux);
int menu(SDL_Surface * ecran);

/*temps_text.c*/
int timer(int temps_1);
void score(int coup, int temps,SDL_Surface * ecran);

#endif 
