#ifndef RESOLVER_DJIKSTRA_H
#define RESOLVER_DJIKSTRA_H

//BIBLIOTHEQUE
#include "rdfs_generator.h" //pour les structures

//MACRO
#define CELL_TYPE_1 1
#define CELL_TYPE_2 2
#define CELL_TYPE_3 3

//ENUMERATION

//STRUCTURE

//PROTOTYPE
bool djikstra_main(const struct Grid* grid, struct Position start_position, struct Position arrival_position);

#endif