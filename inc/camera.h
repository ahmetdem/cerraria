#ifndef CAMERA_H
#define CAMERA_H

#include "game.h"
#include "raylib.h"

void HandleCamMove(Camera2D &);
void HandleCamZoom(Camera2D &);
void HandleCamLimit(Camera2D &);

void DrawCamDebug(Game &);
void UpdateMousePos(Game &);

#endif // CAMERA_H
