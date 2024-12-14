#include "camera.h"
#include "game.h"
#include "raymath.h"

void HandleCamMove(Camera2D &cam) {
  if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
    Vector2 delta = GetMouseDelta();
    delta = Vector2Scale(delta, -1.0f / cam.zoom);
    cam.target = Vector2Add(cam.target, delta);
  }
}

void HandleCamZoom(Camera2D &cam) {
  float wheel = GetMouseWheelMove();
  if (wheel != 0) {
    Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);

    cam.offset = GetMousePosition();
    cam.target = mouseWorldPos;

    float scaleFactor = 1.0f + (0.25f * fabsf(wheel));

    if (wheel < 0)
      scaleFactor = 1.0f / scaleFactor;

    cam.zoom = Clamp(cam.zoom * scaleFactor, 0.125f, 64.0f);
  }
}

void HandleCamLimit(Camera2D &cam) {
  float minX = -1 * ((float)GAME_WIDTH / 2.0f);
  float minY = -1 * ((float)GAME_HEIGHT / 2.0f);

  float maxX = 1 * ((float)GAME_WIDTH / 2.0f);
  float maxY = 1 * ((float)GAME_HEIGHT / 2.0f);

  cam.target.x = Clamp(cam.target.x, minX, maxX);
  cam.target.y = Clamp(cam.target.y, minY, maxY);
}

void DrawCamDebug(Game &game) {
  Vector2 topLeft = (Vector2){10, 10};

  DrawTextEx(
      GetFontDefault(),
      TextFormat("Grid Position: [%i, %i]", game.gridPos.x, game.gridPos.y),
      Vector2Add(topLeft, (Vector2){10, 0}), 20, 2, DARKGREEN);

  DrawTextEx(GetFontDefault(),
             TextFormat("World Position: [%.2f, %.2f]", game.mouseWorldPos.x,
                        game.mouseWorldPos.y),
             Vector2Add(topLeft, (Vector2){10, 30}), 20, 2, BLACK);

  Vector2 calcPos = GridToWorldPos(game.gridPos, game.gridInfo);
  DrawTextEx(GetFontDefault(),
             TextFormat("Calculated World Position: [%.2f, %.2f]", calcPos.x,
                        calcPos.y),
             Vector2Add(topLeft, (Vector2){10, 60}), 20, 2, BLACK);

  // Draw the mouse position marker
  DrawCircleV(GetMousePosition(), 4, DARKGRAY);
}

void UpdateMousePos(Game &game) {
  game.mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), game.cam);

  game.gridPos.x =
      static_cast<int>(std::floor(
          (game.mouseWorldPos.x + (float)TILE_SIZE / 2) / TILE_SIZE)) +
      ROW_TILE_COUNT / 2;

  game.gridPos.y =
      static_cast<int>(std::floor(game.mouseWorldPos.y / TILE_SIZE)) +
      COL_TILE_COUNT / 2;

  if (game.mouseWorldPos.x < (float)-GAME_WIDTH / 2 ||
      game.mouseWorldPos.x > (float)GAME_WIDTH / 2 ||
      game.mouseWorldPos.y < (float)-GAME_HEIGHT / 2 ||
      game.mouseWorldPos.y > (float)GAME_HEIGHT / 2) {
    game.gridPos.x = -1;
    game.gridPos.y = -1;
  }
}
