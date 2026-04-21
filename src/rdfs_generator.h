#ifndef RDFS_GENERATOR_H
#define RDFS_GENERATOR_H

//BIBLIOTHEQUE
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

//MACRO

//ENUMERATION
enum Direction{
    NORTH, //=> 0
    SOUTH, //=> 1
    WEST, //=> 2
    EAST, //=> 3
};

//STRUCTURE
struct Cell{
    struct Cell* adjacent_cells[4];//tableau de 4 pointeurs vers des Cell
    bool visited;
};

struct Grid{
    struct Cell** cells;
    const int height;
    const int width;
};

//PROTOTYPE
struct Grid create_grid(const int height, const int width);
void free_grid(struct Grid* grid);

// ===
int nb_random0(int min, int max, int* tab_prohibited, int size_tab_prohibited);
int nb_random1(int* tab_authorized, int size_tab_authorized);
void create_tab_authorized(int* tab_authorized, int* size_tab_authorized, struct Grid* grid, int height_cell, int width_cell);
bool check_next_cell(struct Grid* grid, int height_cell, int width_cell, enum Direction direction_next_cell);

// ===
bool visitor(struct Cell* cell);
int f_height_next_cell(int height_current_cell, enum Direction direction);
int f_width_next_cell(int width_current_cell, enum Direction direction);

bool linker_cells(struct Cell* cell_1, struct Cell* cell_2, enum Direction dir_cell_1);
int reverser_direction(enum Direction direction);

// ===
void affichage();

#endif