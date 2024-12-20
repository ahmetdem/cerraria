#include "camera.h"
#include "debug.h"
#include "game.h"
#include "raylib.h"
#include "rlImGui.h"
#include "rlgl.h"
#include <ctime>

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

void UpdateGame(Game &);
void RenderGame(Game &);

int main(void) {
  InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "CERRARIA");
  rlImGuiSetup(false);

  DEBUG_UI.Initialize();

  LoadTextures();
  srand(time(0));

  Game Game;
  InitGameState(Game);

  while (!WindowShouldClose()) {
    Game.dt = GetFrameTime();

    UpdateGame(Game);
    RenderGame(Game);
  }

  DEBUG_UI.Shutdown();

  rlImGuiShutdown();
  UnloadAllTextures();
  CloseWindow();
  return 0;
}

void UpdateGame(Game &game) {
  DEBUG_UI.Update(game);

  if (!DEBUG_UI.GetState().camera.lockCamera) {
    HandleCamMove(game.cam);
    HandleCamZoom(game.cam);
    HandleCamLimit(game.cam);
  }
}

void RenderGame(Game &game) {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  BeginMode2D(game.cam); // Begin 2d Mode

  DrawGameWorld(game.chunks, game.gridInfo, game.cam);

  DEBUG_UI.DrawGrid();
  DEBUG_UI.DrawChunkGrid();

  EndMode2D(); // End 2d Mode
  
  DEBUG_UI.metrics.fps = GetFPS();
  UpdateMousePos(game);

  rlImGuiBegin();
  DEBUG_UI.Render(game);
  rlImGuiEnd();

  EndDrawing();
}
