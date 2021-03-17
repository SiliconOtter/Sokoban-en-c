 
#include "Entete.h"
#include <stdio.h>
#include <stdlib.h>


char ** text_vers_tab2( char * nomfichier){ 
    FILE * fd = fopen(nomfichier,"r");
    char c;  
    int y,i;
    char ** tab = malloc(sizeof(* tab)*SIZE);
    for(int i=0;i<SIZE;i++){
        tab[i] = malloc(sizeof(char)*SIZE);
    }
    
    // On initialise le tableau
    for(int i=0;i<SIZE;i++){
        for(int y=0;y<SIZE;y++){
            tab[i][y] = ' ';
        }
    }
    
    if(fd == NULL ){
        perror("Impossible d'ouvrir le fichier de niveau");
        exit(EXIT_FAILURE) ;
    }
    i=1;
    y=1;
    while((c = fgetc(fd)) != EOF){
        if(c == '\n'){
            c = ' ';
            i++;
            y = 1;
        }
        tab[i][y] = c;
        if(c == '@'){ // Sert uniquement à satisfaire les consignes.
            tab[i][y] = 'P';
        }
        else if(c == '$'){
            tab[i][y] = 'C';
        }
        else if(c == '.'){
            tab[i][y] = 'I';
        }
        y++;
    }

    fclose(fd);
    return(tab);

}



/*Prend en paramétre le plateaux courant, le plateaux d'origines; les coordonnées de destinations et ceux du joueurs.
 Et détermine en conséquences les mouvements effectué, ou non .*/
void deplacement(char ** plateaux_1,char ** plateaux,int dest_x, int dest_y , int pos_x , int pos_y){
    if((plateaux[dest_x][dest_y] == ' ') || (plateaux[dest_x][dest_y] == 'I')){
        plateaux[dest_x][dest_y] = 'P';
        plateaux[pos_x][pos_y] = ' ';
    }
    if((plateaux[dest_x][dest_y] == 'C') && (plateaux[dest_x+(dest_x-pos_x)][dest_y+(dest_y-pos_y)] != '#')&& (plateaux[dest_x+(dest_x-pos_x)][dest_y+(dest_y-pos_y)] != 'C')){
        plateaux[dest_x][dest_y] = 'P';
        plateaux[pos_x][pos_y] = ' ';
        plateaux[dest_x+(dest_x-pos_x)][dest_y+(dest_y-pos_y)] = 'C';
    }
    
    for(int i=0;i<SIZE;i++){
        for(int y=0;y<SIZE;y++){
            if((plateaux_1[i][y] == 'I') & (plateaux[i][y] == ' ')){
                plateaux[i][y] = 'I';
            }   
        }
    }
}

/* vérifie si les conditions de victoires sont réalisées */
int is_victory(char ** plateaux,char ** plateaux_1){
    int victory = 1;
    for(int i=0;i<SIZE;i++){
            for(int y=0;y<SIZE;y++){
                if((plateaux[i][y] == 'I')||((plateaux[i][y] == 'P')&&(plateaux_1[i][y] == 'I'))){
                    victory = 0;
                }   
            }
        }
    return victory;
}

/*ceci n'est pas un main*/
void sokoban(){
    
    int num_niveaux = 1,num_niveaux_deci,quit = 1,temps = 0;
    
    char nom_niveau[3]; // 999 Niveaux, ça passe.
        
    SDL_Surface * ecran = initialisation_sdl();
    
    num_niveaux_deci = menu(ecran);
    
    if(num_niveaux_deci != 0){
        while(quit && (num_niveaux <= 5)){
            temps = timer(temps);
            sprintf(nom_niveau,"Levels/%d%d",num_niveaux_deci,num_niveaux);
                
            char ** plateaux = text_vers_tab2(nom_niveau);
                
            quit = boucleEv(plateaux,ecran,num_niveaux);
            num_niveaux ++;
            temps = timer(temps);
            score(10,temps,ecran);
            temps = 0;
            free(plateaux);
        }
        
    }

    fin_sdl();
}

int main(){
    sokoban();
    return 0;
}
