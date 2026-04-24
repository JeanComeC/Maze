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
struct Cell_BFS{
    struct Cell_BFS* parent;
    bool chemin;
};

struct Grid_BFS{
    struct Cell_BFS** cells;
    const int height;
    const int width;
};

//PROTOTYPE
bool breadthfirstsearch_main(const struct Grid* grid, struct Position start_position, struct Position arrival_position);

// === === ===

struct Grid_BFS create_grid_BFS(const int height, const int width);
void free_grid_BFS(struct Grid_BFS* grid_BFS);

// ===
struct Position* create_queue(const int height, const int width);
void free_queue(struct Position* queue);
bool en_queue(struct Position* queue, int* rear, int* size, const int size_queue_max, struct Position new_position);
bool de_queue(int* front, int* size);

// ===
//bool stalk_neighbour(struct Position initial, const struct Grid* grid, struct Position* queue);
bool update_parent(struct Grid_BFS* grid_BFS, struct Position parent, enum Direction direction_parent, struct Position* enfant);


#endif