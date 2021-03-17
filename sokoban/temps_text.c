 
#include "Entete.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
 
 
int timer(int temps_1){
        int temps_2;
        temps_2 = SDL_GetTicks();
        return (temps_2 - temps_1) ;
        
}

void score(int coup,int temps,SDL_Surface * ecran){
    
    TTF_Font * police = NULL;
    SDL_Rect position;
    position.x = ((64*SIZE)/3);
    position.y = ((64*SIZE)/3);
    
    int score = 50000 - (coup*50 + (temps%1000));
    char * score_affi = malloc(sizeof(char)*100);
    
    for(int i=0;i<99;i++){
        score_affi[i] = ' ';
    }
    
    if(score<0){
        score = 0;
    }
    
    sprintf(score_affi,"Score = %d ",score);
    
    TTF_Init();
    
    if(TTF_Init() == -1)
    {
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
    }
    
    police = TTF_OpenFont("ttf-font/TESLA.ttf", 60);
    
    SDL_Color couleur = {250,250,250};
    
    SDL_Surface* texte = NULL;
    
    texte = TTF_RenderText_Blended(police,score_affi,couleur);
    
    SDL_BlitSurface(texte, NULL, ecran, &position);
    
    SDL_FreeSurface(texte);
    
    free(score_affi);
    
    TTF_CloseFont(police);
    SDL_Flip(ecran);
    SDL_Delay(3000);
    
    TTF_Quit();
}

