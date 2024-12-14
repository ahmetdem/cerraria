#include "game.h"
#include "block.h"
#include "raylib.h"

void InitGridInfo(GridInfo &gridInfo) {
    gridInfo.centerX = ROW_TILE_COUNT / 2;
    gridInfo.centerY = COL_TILE_COUNT / 2;

    // Precompute offsets for odd/even grid sizes
    gridInfo.xOffset = (ROW_TILE_COUNT % 2 == 0) ? 0 : TILE_SIZE / 2 - TILE_SIZE;
    gridInfo.yOffset = (COL_TILE_COUNT % 2 == 0) ? 0 : TILE_SIZE / 2 - TILE_SIZE;
}

Vector2 GridToWorldPos(const Vector2Int &gridPos, const GridInfo &gridInfo) {
    Vector2 worldPos;

    worldPos.x = (gridPos.x - gridInfo.centerX) * TILE_SIZE + gridInfo.xOffset;
    worldPos.y = (gridPos.y - gridInfo.centerY) * TILE_SIZE + gridInfo.yOffset;

    return worldPos;
}

void RandomizeGrid(Grid &grid) {
  for (auto &row : grid)
    for (auto &tile : row)
      tile = TILE_DIRT;
}

void InitGameState(Game &game) {
  RandomizeGrid(game.grid);
  InitGridInfo(game.gridInfo);
  game.cam.zoom = 1.0f;
}

void DrawGrid(Grid &grid) {
  int offsetX = GAME_WIDTH / 2;
  int offsetY = GAME_HEIGHT / 2;

  for (int x = 0; x <= ROW_TILE_COUNT; ++x) {
    int lineX = x * TILE_SIZE - offsetX;
    DrawLine(lineX, -offsetY, lineX, COL_TILE_COUNT * TILE_SIZE - offsetY,
             BLACK);
  }

  for (int y = 0; y <= COL_TILE_COUNT; ++y) {
    int lineY = y * TILE_SIZE - offsetY;
    DrawLine(-offsetX, lineY, ROW_TILE_COUNT * TILE_SIZE - offsetX, lineY,
             BLACK);
  }
}

void DrawGameWorld(const Grid &grid, const GridInfo& gridInfo) {
  for (int y = 0; y < COL_TILE_COUNT; ++y) {
    for (int x = 0; x < ROW_TILE_COUNT; ++x) {
      TileType tileType = grid[y][x];

      Block block;
      block.type = tileType;

      Vector2Int gridPos = {x, y};

      DrawBlock(block, gridPos, gridInfo);
    }
  }
}
