#ifndef UTIL_H
#define UTIL_H

#include "raylib.h"
#include <random>

inline Color GetRandomColor() {
  return (Color){static_cast<unsigned char>(std::rand() % 256),
                 static_cast<unsigned char>(std::rand() % 256),
                 static_cast<unsigned char>(std::rand() % 256),
                 255}; // Random R, G, B, Alpha = 255
}

#endif // UTIL_H
