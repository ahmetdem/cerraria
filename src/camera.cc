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
    float scaleFactor = 1.0f + (0.25f * fabsf(wheel));
    if (wheel < 0)
      scaleFactor = 1.0f / scaleFactor;

    float newZoom = cam.zoom * scaleFactor;

    if (newZoom >= 0.125f && newZoom <= 64.0f) {
      Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);

      cam.offset = {static_cast<float>(GetScreenWidth() / 2),
                    static_cast<float>(GetScreenHeight() / 2)};
      cam.target = mouseWorldPos;

      cam.zoom = newZoom;
    }
  }
}

void HandleCamLimit(Camera2D &cam) {
  float halfWorldWidth = (float)GAME_WIDTH / 2.0f;
  float halfWorldHeight = (float)GAME_HEIGHT / 2.0f;

  cam.target.x = Clamp(cam.target.x, -halfWorldWidth, halfWorldWidth);
  cam.target.y = Clamp(cam.target.y, -halfWorldHeight, halfWorldHeight);
}

void UpdateMousePos(Game &game) {
  game.mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), game.cam);
  game.gridPos = WorldToGridPos(game.mouseWorldPos);

  if (game.mouseWorldPos.x < (float)-GAME_WIDTH / 2 ||
      game.mouseWorldPos.x > (float)GAME_WIDTH / 2 ||
      game.mouseWorldPos.y < (float)-GAME_HEIGHT / 2 ||
      game.mouseWorldPos.y > (float)GAME_HEIGHT / 2) {
    game.gridPos.x = -1;
    game.gridPos.y = -1;
  }
}
