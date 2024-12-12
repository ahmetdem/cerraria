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

void DrawCamDebug(Camera2D &cam) {
  Vector2 topLeft = (Vector2){10, 10};
  Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), cam);

  DrawTextEx(GetFontDefault(),
             TextFormat("World Position: [%.2f, %.2f]", mouseWorldPos.x,
                        mouseWorldPos.y),
             topLeft, 20, 2, BLACK);

  DrawCircleV(GetMousePosition(), 4, DARKGRAY);
  DrawTextEx(GetFontDefault(),
             TextFormat("Screen Position: [%i, %i]", GetMouseX(), GetMouseY()),
             (Vector2){topLeft.x, topLeft.y + 30}, 20, 2, BLACK);
}
