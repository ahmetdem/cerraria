#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"

void HandleCamMove(Camera2D &);
void HandleCamZoom(Camera2D &);
void HandleCamLimit(Camera2D &);

void DrawCamDebug(Camera2D &);

#endif // CAMERA_H
