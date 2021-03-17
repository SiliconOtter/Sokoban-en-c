#include "Entete.h"
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>


void affichage_plateaux(char ** tab,char ** ref,SDL_Surface * ecran,int does_what)
{
    SDL_Rect position;
    position.x=0 ;
    position.y=0 ;

    /*On charge toutes les textures */
    SDL_Surface* Title_screen = SDL_LoadBMP("bmp_ressources/Title_screen.bmp");
    SDL_Surface* floor = SDL_LoadBMP("bmp_ressources/floor.bmp");
    SDL_Surface* wall = SDL_LoadBMP("bmp_ressources/Wall.bmp");
    SDL_Surface* crate = SDL_LoadBMP("bmp_ressources/crate_I_Guess.bmp");
    SDL_Surface* cross = SDL_LoadBMP("bmp_ressources/gimp_is_hard.bmp");
    SDL_Surface* player = SDL_LoadBMP("bmp_ressources/Evil_jaw_man_1.bmp");
    SDL_Surface* player1 = SDL_LoadBMP("bmp_ressources/Evil_jaw_man_2.bmp");
    SDL_Surface* crate1 = SDL_LoadBMP("bmp_ressources/crate_!.bmp");
    
    /* On vérifie que aucun probléme n'est apparu */
    if(!Title_screen || !floor || !wall || !crate || !cross || !player || !crate1 || !player1)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }
    
    /*Selon notre plateaux actuel et celui d'origine, l'on génére chaque cases avec la bonne texture*/
    for(int i=0;i<SIZE;i++)
    {
            position.x=0;

        for(int j=0;j<SIZE;j++)
        {
            SDL_BlitSurface(floor,NULL,ecran,&position) ;
            if(tab[i][j] == '#' ){
                SDL_BlitSurface(wall,NULL,ecran,&position) ;
            }
            if(tab[i][j] == 'C' ){
                SDL_BlitSurface(crate,NULL,ecran,&position) ;
            }
            if(tab[i][j] == 'I' ){
                SDL_BlitSurface(cross,NULL,ecran,&position) ;
            }
            if((tab[i][j] == 'C')&&((ref[i][j]) == 'I')){
                SDL_BlitSurface(crate1,NULL,ecran,&position) ;
            }
            if(tab[i][j] == 'P'){
                SDL_BlitSurface(player,NULL,ecran,&position) ;
            }
            if((tab[i][j] == 'P')&&((ref[i][j]) == 'I')){
                SDL_BlitSurface(player1,NULL,ecran,&position) ;
            }
            position.x+=64;
        }
        position.y+=64;
    }
    /*Utilisé pour l'affichage de l'image écran titre*/
    if(does_what == 1){
        position.x = ((64*SIZE)/2)-100;
        position.y = 128;
        SDL_BlitSurface(Title_screen,NULL,ecran,&position) ;
        SDL_Delay(500);
    }

    SDL_FreeSurface(Title_screen);
    SDL_FreeSurface(floor);
    SDL_FreeSurface(wall);
    SDL_FreeSurface(crate);
    SDL_FreeSurface(cross);
    SDL_FreeSurface(player);
    SDL_FreeSurface(player1);
    SDL_FreeSurface(crate1);

    SDL_Flip(ecran);

}

/*On prépare notre fenétre*/
SDL_Surface * initialisation_sdl(){
    
    if(SDL_Init(SDL_INIT_VIDEO)==-1)
    {
        fprintf(stderr,"Erreur SDL :%s\n", SDL_GetError()) ;
        exit(EXIT_FAILURE) ;
    }
    SDL_Surface * ecran = NULL ;

    if((ecran = SDL_SetVideoMode(64*SIZE,64*SIZE,32, SDL_HWSURFACE|SDL_RESIZABLE))==NULL)
    {    
        fprintf(stderr,"Erreur VideoMode %s\n",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }
    return(ecran);
    
}

/*Un prix à payer pour avoir un main d'une ligne*/
void fin_sdl(){
    SDL_Quit();
}

/*Attend et réagi à toutes les entrées claviers du joueur, et invoque les fonctions en conséquence*/
int boucleEv(char ** plateaux,SDL_Surface * ecran,int num_niveaux){
    int cont=1 , what_do = 0;
    int pos_x, pos_y;
    
    char ** plateaux_1 = malloc(sizeof(* plateaux_1)*SIZE);
    for(int i=0;i<SIZE;i++){
        plateaux_1[i] = malloc(sizeof(char)*SIZE);
    }
    for(int i=0;i<SIZE;i++){
        for(int y=0;y<SIZE;y++){
            plateaux_1[i][y] = plateaux[i][y];
        }
    }

    
    SDL_Event event ;
    
    if(num_niveaux == 1){
        what_do = 1;
    }
    while(cont){
        SDL_WaitEvent(&event);
        for(int i=0;i<SIZE;i++){
            for(int y=0;y<SIZE;y++){
                if(plateaux[i][y] == 'P'){
                    pos_x = i;
                    pos_y = y;
                }   
            }
        }
        switch(event.type){
            case 
                SDL_QUIT:
                cont = 0;
                free(plateaux_1);
                return 0;
            case 
                SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_UP:
                    deplacement(plateaux_1,plateaux,pos_x-1,pos_y,pos_x,pos_y);
                    what_do = 0;
                    break ;
                case SDLK_DOWN:
                    deplacement(plateaux_1,plateaux,pos_x+1,pos_y,pos_x,pos_y);
                    what_do = 0;
                    break ;
                case SDLK_LEFT : 
                    deplacement(plateaux_1,plateaux,pos_x,pos_y-1,pos_x,pos_y);
                    what_do = 0;
                    break ;
                case SDLK_RIGHT:
                    deplacement(plateaux_1,plateaux,pos_x,pos_y+1,pos_x,pos_y);
                    what_do = 0;
                    break ;
                case 'r':
                    for(int i=0;i<SIZE;i++){
                        for(int y=0;y<SIZE;y++){
                            plateaux[i][y] = plateaux_1[i][y];
                        }
                    }
                    what_do = 0;
                    break;
                case 'p':
                    cont=0 ;
                    free(plateaux_1);
                    return 1; // Même condition que pour une victoire mais sans l'honneur 
                    break ;
                case 'q':
                    cont=0 ;
                    free(plateaux_1);
                    return 0;
                    break ;
            }
        }
        affichage_plateaux(plateaux,plateaux_1,ecran,what_do);
        if(is_victory(plateaux,plateaux_1)){
            printf("victory");
            free(plateaux_1);
            return 1;
        }
    }
}

int menu(SDL_Surface * ecran){
    
    int cont = 1;
    SDL_Rect position;
    position.x = ((64*SIZE)/2)-250;
    position.y = 250;
    
    SDL_Surface* menu = SDL_LoadBMP("bmp_ressources/Menu.bmp");
    if(!menu)
    {
        printf("Erreur de chargement de l'image : %s",SDL_GetError());
        exit(EXIT_FAILURE) ;
    }
    SDL_BlitSurface(menu,NULL,ecran,&position) ;
    
    SDL_Event event ;
    
    while(cont){
    SDL_WaitEvent(&event);
        switch(event.type){
            case 
                SDL_QUIT:
                cont = 0;
            case 
                SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case 'f':
                    cont = 0;
                    return 1;
                    break ;
                case 'm':
                    cont = 0;
                    return 2;
                    break ;
                case 'd' : 
                    cont = 0;
                    return 3;
                    break ;
                case 'q':
                    cont = 0;
                    return 0;
                    break ;
            }
        }
    }
}




