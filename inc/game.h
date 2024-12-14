#ifndef GAME_H
#define GAME_H

#include "block.h"
#include "raylib.h"
#include "util.h"
#include <array>

#define GAME_WIDTH (180000 / 2)
#define GAME_HEIGHT (90000 / 2)

#define TILE_SIZE 100

#define ROW_TILE_COUNT (GAME_WIDTH / TILE_SIZE)
#define COL_TILE_COUNT (GAME_HEIGHT / TILE_SIZE)

using std::array;
using Grid = array<array<TileType, ROW_TILE_COUNT>, COL_TILE_COUNT>;

struct GridInfo {
  int centerX, centerY;
  int xOffset, yOffset;

  Vector2 precomputedWorldPositions[ROW_TILE_COUNT][COL_TILE_COUNT];
};

struct Game {
  Vector2 mouseWorldPos;
  Vector2Int gridPos = {-1, -1};
  float dt = 0.0f;
  Camera2D cam = {};
  Grid grid{};
  GridInfo gridInfo;
};

void InitGameState(Game &);
void InitGridInfo(GridInfo &);
void InitWorldPositions(Vector2 precomputedWorldPositions[][COL_TILE_COUNT]);

void RandomizeGrid(Grid &);
void DrawGrid(Grid &);
void DrawGameWorld(const Grid &, const GridInfo &, const Camera2D &);

Vector2 GridToWorldPos(const Vector2Int &, const GridInfo &);
bool IsInsideVisibleCam(const Camera2D &, const Vector2 &);

#endif // GAME_H
