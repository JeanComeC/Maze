#include "resolver_breadthfirstsearch.h"

/*
Breadth First Search (BFS) :
Le BFS fonctionne quand tous les poids des arêtes sont égaux (ici, passer d'une cellule à une autre coûte toujours "1").
Dans ce cas BFS trouve le plus court chemin naturellement grâce à l'exploration par couches.

BFS explore toutes les cellules de la couche 1, puis 2, etc ... et après, il "remonte" de parent en parent jusqu'au début
pour afficher le chemin le plus court.
*/

bool breadthfirstsearch_main(const struct Grid* grid, struct Position start_position, struct Position arrival_position){
    if(!grid || !grid->cells)return false;

    //Génération :
    struct Grid_BFS grid_BFS=create_grid_BFS(grid->height,grid->width);
    struct Position* queue=create_queue(grid->height,grid->width);
    int front=0;
    int rear=0;
    int size_queue=0;
    const int size_queue_max=(grid->height)*(grid->width);

    if(!en_queue(queue,&rear,&size_queue,size_queue_max,start_position)){
        fprintf(stderr,"Error en_queue().\n");
        free_queue(queue);
        free_grid_BFS(&grid_BFS);
        return false;//je return false au lieu de exit(1), car il faut que je retourne dans mon main pour free le grid_main !
    }

    //BOUCLE PRINCIPALE :
    while(size_queue>0){
        //on vérifie que la cellule parent ne soit pas l'arrivée
        if(queue[front].h==arrival_position.h && queue[front].w==arrival_position.w)break;

        //On ajoute les voisins dans la file :
        for(enum Direction i;i<4;i++){
            if(grid->cells[queue[front].h][queue[front].w].adjacent_cells[i]!=NULL){
                struct Position enfant = {};
                if(!update_parent(&grid_BFS,queue[front],i,&enfant)){
                    fprintf(stderr,"Error update_parent().\n");
                    free_queue(queue);
                    free_grid_BFS(&grid_BFS);
                    return false;
                }
                if(!en_queue(queue,&rear,&size_queue,size_queue_max,enfant)){
                    fprintf(stderr,"Error en_queue().\n");
                    free_queue(queue);
                    free_grid_BFS(&grid_BFS);
                    return false;
                }
            }
        }

        //Ensuite j'enlève le parent :
        if(!de_queue(&front,&size_queue)){
            fprintf(stderr,"Error de_queue().\n");
            free_queue(queue);
            free_grid_BFS(&grid_BFS);
            return false;
        }
    }

    //INVERSION :
    

    //AFFICHAGE :
    //dkdkdk

    //NETTOYAGE :
    free_grid_BFS(&grid_BFS);

    return true;
}


// === === ===


struct Grid_BFS create_grid_BFS(const int height, const int width){//je re-créé un tableau mais avec mes nouvelles structures.
    struct Grid_BFS grid_BFS = {.cells=NULL,.height=height,.width=width};
    grid_BFS.cells=malloc(sizeof(struct Cell_BFS*)*height);
    if(!grid_BFS.cells){perror("Error memory BFS (first layer).\n");exit(1);}
    for(int i=0;i<height;i++){
        grid_BFS.cells[i]=malloc(sizeof(struct Cell_BFS)*width);
        if(!grid_BFS.cells[i]){perror("Error memory BFS (second layer).\n");exit(1);}
        for(int j=0;j<width;j++){
            grid_BFS.cells[i][j].chemin=false;
            grid_BFS.cells[i][j].parent=NULL;
        }
    }
    return grid_BFS;
}

void free_grid_BFS(struct Grid_BFS* grid_BFS){
    if(grid_BFS==NULL || grid_BFS->cells==NULL)return;
    for(int i=0;i<grid_BFS->height;i++){
        free(grid_BFS->cells[i]);
        grid_BFS->cells[i]=NULL;
    }
    free(grid_BFS->cells);
    grid_BFS->cells=NULL;
}

// ===

struct Position* create_queue(const int height, const int width){
    //je n'utilise pas de file circulaire avec un modulo, je fais directement pour simplifier une file de taille height*width
    struct Position* queue = malloc(sizeof(struct Position)*height*width);//height*width car c la taille maximum dans le pire cas.
    if(!queue){perror("Error memory (queue).\n");exit(1);}
    return queue;
}

void free_queue(struct Position* queue){
    if(!queue)return;
    free(queue);
    queue=NULL;
}

bool en_queue(struct Position* queue, int* rear, int* size, const int size_queue_max, struct Position new_position){
    if(!queue || (*rear)<-1 || (*size)<0 || (*size)>=size_queue_max)return false;
    (*rear)++;
    queue[*rear]=new_position;
    (*size)++;
    return true;
}

bool de_queue(int* front, int* size){
    if((*front)<-1 || (*size)<0)return false;
    (*front)++;
    (*size)--;
    return true;
}

// ===

bool update_parent(struct Grid_BFS* grid_BFS, struct Position parent, enum Direction direction_parent, struct Position* enfant){//fonction pour remplir l'élément parent dans un enfant depuis la direction du parent
    if(!grid_BFS || !grid_BFS->cells)return false;
    switch (direction_parent){
    case NORTH:
        enfant->h=parent.h-1;
        enfant->w=parent.w;
        grid_BFS->cells[enfant->h][enfant->w].parent=&(grid_BFS->cells[parent.h][parent.w]);
        break;
    
    case SOUTH:
        enfant->h=parent.h+1;
        enfant->w=parent.w;
        grid_BFS->cells[enfant->h][enfant->w].parent=&(grid_BFS->cells[parent.h][parent.w]);

    case WEST:
        enfant->h=parent.h;
        enfant->w=parent.w-1;
        grid_BFS->cells[enfant->h][enfant->w].parent=&(grid_BFS->cells[parent.h][parent.w]);
        break;

    case EAST:
        enfant->h=parent.h;
        enfant->w=parent.w+1;
        grid_BFS->cells[enfant->h][enfant->w].parent=&(grid_BFS->cells[parent.h][parent.w]);
        break;
    }
    return true;
}


