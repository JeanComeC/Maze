#include "rdfs_generator.h"

struct Grid create_grid(const int height, const int width){//fonction pour créer mon grand tableau avec toutes les cellules.
    struct Grid new_grid={.cells=NULL,.height=height,.width=width};//j'initialise maintenant car apès c'est impossible car c'est des const
    new_grid.cells=malloc(sizeof(struct Cell*)*height);
    if(!new_grid.cells){perror("Error memory (first layer).\n");exit(1);}
    for(int i=0;i<height;i++){
        new_grid.cells[i]=malloc(sizeof(struct Cell)*width);//pointeur vers une structure Cell directement et pas vers un pointeur !
        if(!new_grid.cells[i]){perror("Error memory (second layer).\n");exit(1);}
        //new_grid.cells[i][j] est une struct Cell pas un pointeur (!!)
        for(int j=0;j<width;j++){
            new_grid.cells[i][j].visited=false;
            for(int k=0;k<4;k++){
                new_grid.cells[i][j].adjacent_cells[k]=NULL;
            }
        }
    }
    return new_grid;
}

void free_grid(struct Grid* grid){
    if(grid==NULL || grid->cells==NULL)return;
    for(int i=0;i<grid->height;i++){
        free(grid->cells[i]);
        grid->cells[i]=NULL;
    }
    free(grid->cells);
    grid->cells=NULL;
    printf("\nNettoyage ...\n");
}

// ===

int nb_random0(int min, int max, int* tab_prohibited, int size_tab_prohibited){//fonction qui retourne un entier aléatoire avec tableau interdit, et appel récursif.
    int nbra=rand()%(max-min+1)+min;
    if(size_tab_prohibited==0)return nbra;//si le tableau est vide, on return direct
    if(size_tab_prohibited>=(max-min)+1)return -1;//et si le tableau est supérieur ou égale eux nombres de choix, c'est qu'il n'y a aucun choix possible.
    for(int i=0;i<size_tab_prohibited;i++){
        if(nbra==tab_prohibited[i]){
            return nb_random0(min,max,tab_prohibited,size_tab_prohibited);
        }
    }
    return nbra;
}

int nb_random1(int* tab_authorized, int size_tab_authorized){//fonction qui retourne aléatoirement un élément d'une liste d'entiers autorisés.
    if(size_tab_authorized<1 || tab_authorized==NULL)return -1;//gestion d'erreur
    int index_random=rand()%size_tab_authorized;
    return tab_authorized[index_random];
}

void create_tab_authorized(int* tab_authorized, int* size_tab_authorized, struct Grid* grid, struct Position cell){//fonction qui créer un tableau avec les directions valides
    *size_tab_authorized=0;//on l'initialise à 0 pour être sûr, et pour gérer le cas où toutes les cellules voisines seraient false.
    enum Direction i;
    for(i=0;i<4;i++){
        if(check_next_cell(grid,cell,i)){
            tab_authorized[*size_tab_authorized]=i;
            (*size_tab_authorized)++;//ajout de parenthèses car l'opérateur '++' est prioritaire sur '*' .
        }
    }
}

bool check_next_cell(struct Grid* grid, struct Position cell, enum Direction direction_next_cell){//fonction qui vérifie si la cellule peut être visitée ou pas.
    //Check border :
    bool checkpoint_1=false;
    switch(direction_next_cell){
        case NORTH:
            if(cell.h>0)checkpoint_1=true;
            break;
        
        case SOUTH:
            if(cell.h<grid->height-1)checkpoint_1=true;
            break;
        
        case WEST:
            if(cell.w>0)checkpoint_1=true;
            break;
        
        case EAST:
            if(cell.w<grid->width-1)checkpoint_1=true;
            break;
    }

    //Check visited :
    bool checkpoint_2=false;
    if(checkpoint_1){
        switch(direction_next_cell){
        case NORTH:
            if(grid->cells[cell.h-1][cell.w].visited==false)checkpoint_2=true;
            break;
        
        case SOUTH:
            if(grid->cells[cell.h+1][cell.w].visited==false)checkpoint_2=true;
            break;
        
        case WEST:
            if(grid->cells[cell.h][cell.w-1].visited==false)checkpoint_2=true;
            break;
        
        case EAST:
            if(grid->cells[cell.h][cell.w+1].visited==false)checkpoint_2=true;
            break;
        }
    }
    
    //Check final :
    if(checkpoint_1==true && checkpoint_2==true){
        return true;
    }
    return false;
}

// ===

bool visitor(struct Cell* cell){//fonction pour activer 'visited' dans une cellule PAS visitée
    if(cell==NULL)return false;
    if(cell->visited==true)return false;
    cell->visited=true;
    return true;
}

int f_height_next_cell(int height_current_cell, enum Direction direction){
    int height_next_cell=-1;
    switch(direction){
    case NORTH:
        height_next_cell=height_current_cell-1;
        break;
    
    case SOUTH:
        height_next_cell=height_current_cell+1;
        break;
    
    default:
        height_next_cell=height_current_cell;
        break;
    }
    return height_next_cell;
}
int f_width_next_cell(int width_current_cell, enum Direction direction){
    int width_next_cell=-1;
    switch(direction){
    case WEST:
        width_next_cell=width_current_cell-1;
        break;
    
    case EAST:
        width_next_cell=width_current_cell+1;
        break;
    
    default:
        width_next_cell=width_current_cell;
        break;
    }
    return width_next_cell;
}

bool linker_cells(struct Cell* cell_1, struct Cell* cell_2, enum Direction dir_cell_1){//fonction pour lier 2 cellules avec une direction.
    bool errcode=false;
    if(!cell_1 || !cell_2)return errcode;
    if(cell_1->adjacent_cells[dir_cell_1]!=NULL || cell_2->adjacent_cells[reverser_direction(dir_cell_1)]!=NULL){
        fprintf(stderr,"Error: Ré-écriture de liens interdite.(linker_cells)(!)\n");
        return errcode;
    }
    cell_1->adjacent_cells[dir_cell_1]=cell_2;
    cell_2->adjacent_cells[reverser_direction(dir_cell_1)]=cell_1;
    return errcode=true;
}

int reverser_direction(enum Direction direction){//fonction pour inverser une direction.
    int rev_dir=-1;
    switch(direction){
    case NORTH:
        rev_dir=1;
        break;
    
    case SOUTH:
        rev_dir=0;
        break;
    
    case WEST:
        rev_dir=3;
        break;
    
    case EAST:
        rev_dir=2;
        break;
    }
    return rev_dir;
}

// ===

struct Position* create_stack(const int height, const int width){//fonction pour malloc ma pile (stack)
    struct Position* stack = malloc(sizeof(struct Position)*height*width);
    if(!stack){perror("Error memory (stack).\n");exit(1);}
    return stack;
}

void free_stack(struct Position* stack){//fonction pour free la pile (stack)
    if(!stack)return;
    free(stack);
    stack=NULL;
}

bool push_stack(int* stack_top, struct Position* stack, struct Position new_position){
    if((*stack_top)<-1 || !stack)return false;
    (*stack_top)++;
    stack[*stack_top]=new_position;
    return true;
}

bool pop_stack(int* stack_top){
    if((*stack_top)<-1)return false;//-1 et pas 0, car sinon on peut pas sortir proprement de la boucle while !
    (*stack_top)--;
    return true;
}

// ===

