#include "resolver_breadthfirstsearch.h"

/*
Breadth First Search (BFS) :
Le BFS fonctionne quand tous les poids des arêtes sont égaux (ici, passer d'une cellule à une autre coûte toujours "1").
Dans ce cas BFS trouve le plus court chemin naturellement grâce à l'exploration par couches.

BFS explore toutes les cellules de la couche 1, puis 2, etc ... et après, il "remonte" jusqu'au parent pour afficher le chemin
le plus court.
*/

bool breadthfirstsearch_main(struct Grid grid, struct Position start_position, struct Position arrival_position){
    if(!grid.cells)return false;
    //
    return true;
}

