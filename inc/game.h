#ifndef GAME_H
#define GAME_H

#include "block.h"
#include "raylib.h"
#include "util.h"
#include <array>

#define GAME_WIDTH (175000 / 2)
#define GAME_HEIGHT (90000 / 2)

#define TILE_SIZE 100

#define ROW_TILE_COUNT (GAME_WIDTH / TILE_SIZE)
#define COL_TILE_COUNT (GAME_HEIGHT / TILE_SIZE)

using std::array;
using Grid = array<array<TileType, ROW_TILE_COUNT>, COL_TILE_COUNT>;

struct Game {
  Vector2 mouseWorldPos;
  Vector2Int gridPos = {-1, -1};
  float dt = 0.0f;
  Camera2D cam = {};
  Grid grid{};
};

void InitGameState(Game &);

void RandomizeGrid(Grid &);
void DrawGrid(Grid &);
void DrawGameWorld(const Grid &);

Vector2 GridToWorldPos(const Vector2Int&);


#endif // GAME_H

