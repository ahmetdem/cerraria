#include "noise.h"
#include <math.h>

#define PERM_SIZE 256
static uint8_t perm[PERM_SIZE * 2];

static float fade(float t) {
  return t * t * t * (t * (t * 6.0f - 15.0f) + 10.0f);
}

static float grad(int hash, float x) {
  int h = hash & 15;
  float grad = 1.0f + (h & 7);
  if (h & 8)
    grad = -grad;
  return grad * x;
}

void init_noise(uint32_t seed) {
  // Simple seed-based shuffle
  for (int i = 0; i < PERM_SIZE; i++) {
    perm[i] = i;
  }

  // Basic shuffle algorithm
  for (int i = PERM_SIZE - 1; i > 0; i--) {
    seed = seed * 1103515245 + 12345;
    int j = seed % (i + 1);
    uint8_t temp = perm[i];
    perm[i] = perm[j];
    perm[j] = temp;
  }

  // Duplicate for easier indexing
  for (int i = 0; i < PERM_SIZE; i++) {
    perm[PERM_SIZE + i] = perm[i];
  }
}

float get_noise(float x) {
  int X = ((int)floor(x)) & 255;
  x -= floor(x);
  float u = fade(x);

  int A = perm[X];
  int B = perm[X + 1];

  return lerp(grad(perm[A], x), grad(perm[B], x - 1), u);
}

float get_normalized_noise(float x) { return (get_noise(x) + 1.0f) * 0.5f; }
