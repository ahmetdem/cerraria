#include "game.h"
#include "raylib.h"
#include <iostream>

int row_tile_count = (int)GAME_WIDTH / TILE_SIZE;
int col_tile_count = (int)GAME_HEIGHT / TILE_SIZE;

void RandomizeGrid(Grid &grid) {
  for (auto &row : grid)
    for (auto &tile : row)
      tile = 1;
}

void InitGameState(Game &game) {
  RandomizeGrid(game.grid);
  game.cam.zoom = 1.0f;
}


void DrawTheGrid(Grid &grid) {
    int offsetX = GAME_WIDTH / 2;
    int offsetY = GAME_HEIGHT / 2;

    for (int x = 0; x <= row_tile_count; ++x) {
        int lineX = x * TILE_SIZE - offsetX;
        DrawLine(lineX, -offsetY, lineX, col_tile_count * TILE_SIZE - offsetY, GRAY);
    }

    for (int y = 0; y <= col_tile_count; ++y) {
        int lineY = y * TILE_SIZE - offsetY;
        DrawLine(-offsetX, lineY, row_tile_count * TILE_SIZE - offsetX, lineY, GRAY);
    }
}
