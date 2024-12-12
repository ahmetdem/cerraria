#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <array>
#include <cstdint>

#define GAME_WIDTH 175000 / 2
#define GAME_HEIGHT 90000 / 2

#define TILE_SIZE 100

extern int row_tile_count, col_tile_count;

using std::array;
using Grid = array<array<int8_t, 100>, 200>; 

struct Game {
  float dt = 0.0f;
  Camera2D cam = {};
  Grid grid {};
};

void InitGameState(Game&);
void RandomizeGrid(Grid&);

void DrawTheGrid(Grid &grid);

#endif // GAME_H
