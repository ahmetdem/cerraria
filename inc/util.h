#ifndef UTIL_H
#define UTIL_H

#include "raylib.h"
#include <random>

struct Vector2Int {
  int x;
  int y;

  Vector2Int() : x(0), y(0) {}
  Vector2Int(int _x, int _y) : x(_x), y(_y) {}
};

inline Color GetRandomColor() {
  return (Color){static_cast<unsigned char>(std::rand() % 256),
                 static_cast<unsigned char>(std::rand() % 256),
                 static_cast<unsigned char>(std::rand() % 256),
                 255}; // Random R, G, B, Alpha = 255
}

#endif // UTIL_H
