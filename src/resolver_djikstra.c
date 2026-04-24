#include "resolver_djikstra.h"

/*
Djikstra : 
Dijkstra fonctionne quand les poids sont variables (passer par certaines cellules coûte plus cher que d'autres).
Il utilise une file de priorité (priority queue) au lieu d'une simple file FIFO.

Si traverser chaque cellule coute toujours "1", Djikstra retourne la meme chose que BFS, Dijkstra est interressant si il y a,
des cellules boueuses qui coute "3" par exemple, car il retournera le chemin le moins coûteux.
*/

bool djikstra_main(const struct Grid* grid, struct Position start_position, struct Position arrival_position){
    if(!grid || !grid->cells)return false;
    //
    printf("Sorry, this algorithm has not yet been coded !\n");
    //
    return true;
}