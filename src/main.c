#include "rdfs_generator.h"
#include "resolver_breadthfirstsearch.h"
#include "resolver_djikstra.h"
#include "resolver_a.h"
#include <stdio.h>
#include <stdlib.h>

int choix_utilisateur(int min_choice, int max_choice);

int main(int argc, char** argv){//HEIGHT WIDTH
    //INITIALISATION :
    if(argc!=3){perror("Vous avez oublié de mettre les (bonnes) dimensions.");exit(1);}
    srand(time(NULL));
    const int height=atoi(argv[argc-2]);
    const int width=atoi(argv[argc-1]);
    //Conditions pour vérifier que les dimensions ne soient pas absurdes (0 0, ou 1 0, 0 x, etc ...)
    if(height<1 || height>SIZE_HEIGHT_MAX || width<1 || width>SIZE_WIDTH_MAX){fprintf(stderr,"Dimensions' size is not valid.\n");exit(1);}

    //GENERATION :
    struct Grid grid_main=create_grid(height, width);
    struct Position* stack_main=create_stack(height,width);
    int stack_top=-1;

    //Je commence arbitrairement dans la cellule (0;0).
    struct Position initial_position = {.h=HEIGHT_INITIAL_POSITION,.w=WIDTH_INITIAL_POSITION};
    if(!push_stack(&stack_top,stack_main,initial_position)){
        fprintf(stderr,"Error push_stack().\n");
        free_stack(stack_main);
        free_grid(&grid_main);
        exit(1);
    }
    
    if(!visitor(&(grid_main.cells[stack_main[stack_top].h][stack_main[stack_top].w]))){
        fprintf(stderr,"Erreur lors de la visitation initiale.\n");
        free_stack(stack_main);
        free_grid(&grid_main);
        exit(1);
    }

    while(stack_top>-1){
        //on créé le tableau des directions autorisées :
        int* tab_authorized=malloc(sizeof(int)*4);
        int size_tab_authorized;
        create_tab_authorized(tab_authorized,&size_tab_authorized,&grid_main,stack_main[stack_top]);

        //BACKTRACKING :
        if(size_tab_authorized>0){//Si il y a une cellule possible, on continue normalement ...
            enum Direction dir_next_cell=nb_random1(tab_authorized,size_tab_authorized);
            free(tab_authorized);
            if(dir_next_cell==-1){//Seconde vérification du BackTracking
                fprintf(stderr,"Error BackTracking.\n");
                free_stack(stack_main);
                free_grid(&grid_main);
                exit(1);
            }

            //Liaison :
            if(!linker_cells(&(grid_main.cells[stack_main[stack_top].h][stack_main[stack_top].w]),&(grid_main.cells[f_height_next_cell(stack_main[stack_top].h,dir_next_cell)][f_width_next_cell(stack_main[stack_top].w,dir_next_cell)]),dir_next_cell)){
                fprintf(stderr,"Error in linker_cells()\n");
                free_stack(stack_main);
                free_grid(&grid_main);
                exit(1);
            }

            //PUSH :
            struct Position next_position = {.h=f_height_next_cell(stack_main[stack_top].h,dir_next_cell),.w=f_width_next_cell(stack_main[stack_top].w,dir_next_cell)};//je créé une nouvelle position avec les nouvelles coordonnées
            if(!push_stack(&stack_top,stack_main,next_position)){
                fprintf(stderr,"Error push_stack().\n");
                free_stack(stack_main);
                free_grid(&grid_main);
                exit(1);
            }

            //on visite la nouvelle cellule :
            if(!visitor(&(grid_main.cells[stack_main[stack_top].h][stack_main[stack_top].w]))){
                fprintf(stderr,"Erreur lors de la visitation.\n");
                free_stack(stack_main);
                free_grid(&grid_main);
                exit(1);
            }

        }else{
            free(tab_authorized);

            //POP :
            if(!pop_stack(&stack_top)){
                fprintf(stderr,"Error pop_stack().\n");
                free_stack(stack_main);
                free_grid(&grid_main);
                exit(1);
            }
        }
    }
    free_stack(stack_main);

    //AFFICHAGE :
    affichage_00(width);
    for(int m=0;m<height;m++){
        printf("|");
        for(int n=0;n<width;n++){
            affichage_EAST(grid_main.cells[m][n]);
        }
        printf("\n");
        printf("+");
        for(int n=0;n<width;n++){
            affichage_SOUTH(grid_main.cells[m][n]);
        }
        printf("\n");
    }

    //AFFICHAGE TOTALE:
    // for(int m=0;m<height;m++){
    //     affichage_00(width);
    //     affichage_11(width);
    // }
    // affichage_00(width);

    //RESOLUTION :
    printf("1- BreadthFirstSearch\n2- Djikstra\n3- A*\n");
    int reponse=choix_utilisateur(1,3);

    //Je choisis arbitrairement que l'entrée est en bas à gauche, et l'arrivée en haut à droite :
    struct Position start_position = {.h=height-1,.w=0};
    struct Position arrival_position = {.h=0,.w=width-1};

    switch(reponse){
    case 1:
        if(!breadthfirstsearch_main(&grid_main,start_position,arrival_position)){
            fprintf(stderr,"Error BreadthFirstSearch.\n");
            free_grid(&grid_main);
            exit(1);
        }
        break;
    
    case 2:
        if(!djikstra_main(&grid_main,start_position,arrival_position)){
            fprintf(stderr,"Error Djikstra.\n");
            free_grid(&grid_main);
            exit(1);
        }
        break;

    case 3:
        if(!a_main(&grid_main,start_position,arrival_position)){
            fprintf(stderr,"Error A*.\n");
            free_grid(&grid_main);
            exit(1);
        }
        break;
    }

    //NETTOYAGE :
    free_grid(&grid_main);

    return 0;
}


int choix_utilisateur(int min_choice, int max_choice){
    int rep;
    scanf(" %d",&rep);
    if(rep>max_choice || rep<min_choice){
        printf("Votre choix doit être compris entre %d et %d inclus.\n",min_choice,max_choice);
        return choix_utilisateur(min_choice,max_choice);
    }
    return rep;
}

