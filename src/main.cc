#include "camera.h"
#include "game.h"
#include "raylib.h"
#include "rlgl.h"
#include <ctime>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

void UpdateGame(Game &);
void RenderGame(Game &);

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CERRARIA");
  SetTargetFPS(60);

  LoadTextures();

  srand(time(0));

  Game Game;
  InitGameState(Game);

  while (!WindowShouldClose()) {
    Game.dt = GetFrameTime();

    UpdateGame(Game);
    RenderGame(Game);
  }

  UnloadAllTextures();
  CloseWindow();
  return 0;
}

void UpdateGame(Game &game) {
  HandleCamMove(game.cam);
  HandleCamZoom(game.cam);
  HandleCamLimit(game.cam);
}

void RenderGame(Game &game) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  BeginMode2D(game.cam); // Begin 2d Mode

  DrawGameWorld(game.grid, game.gridInfo);
  DrawGrid(game.grid);

  DrawCircle(GetScreenWidth() / 2, GetScreenHeight() / 2, 50, MAROON);

  EndMode2D(); // End 2d Mode

  DrawFPS(SCREEN_WIDTH - 100, 20);
  UpdateMousePos(game);
  DrawCamDebug(game);

  EndDrawing();
}
