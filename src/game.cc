#include "game.h"
#include "block.h"
#include "raylib.h"

Vector2 GridToWorldPos(const Vector2Int &gridPos) {
  Vector2 worldPos;

  worldPos.x = (gridPos.x - ROW_TILE_COUNT / 2 - 1) * TILE_SIZE + 50;
  worldPos.y = (gridPos.y - COL_TILE_COUNT / 2) * TILE_SIZE;

  return worldPos;
}

void RandomizeGrid(Grid &grid) {
  for (auto &row : grid)
    for (auto &tile : row)
      tile = TILE_DIRT;
}

void InitGameState(Game &game) {
  RandomizeGrid(game.grid);
  game.cam.zoom = 1.0f;
}

void DrawGrid(Grid &grid) {
  int offsetX = GAME_WIDTH / 2;
  int offsetY = GAME_HEIGHT / 2;

  for (int x = 0; x <= ROW_TILE_COUNT; ++x) {
    int lineX = x * TILE_SIZE - offsetX;
    DrawLine(lineX, -offsetY, lineX, COL_TILE_COUNT * TILE_SIZE - offsetY,
             GRAY);
  }

  for (int y = 0; y <= COL_TILE_COUNT; ++y) {
    int lineY = y * TILE_SIZE - offsetY;
    DrawLine(-offsetX, lineY, ROW_TILE_COUNT * TILE_SIZE - offsetX, lineY,
             GRAY);
  }
}

void DrawGameWorld(const Grid& grid) {
  for (int y = 0; y < COL_TILE_COUNT; ++y) {
    for (int x = 0; x < ROW_TILE_COUNT; ++x) {
      TileType tileType = grid[y][x];

      Block block;
      block.type = tileType; 

      Vector2Int gridPos = {x, y};

      DrawBlock(block, gridPos);
    }
  }
}
