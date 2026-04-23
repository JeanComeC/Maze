#ifndef RESOLVER_BREADTHFIRSTSEARCH_H
#define RESOLVER_BREADTHFIRSTSEARCH_H

//BIBLIOTHEQUE
#include "rdfs_generator.h" //pour les structures
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

//MACRO

//ENUMERATION


//STRUCTURE
struct Cell_bfs{
    struct Cell_bfs* parent;
};

//PROTOTYPE
bool breadthfirstsearch_main(struct Grid grid, struct Position start_position, struct Position arrival_position);

#endif