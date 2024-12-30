#pragma once

#include "block.h"

#define CHUNK_SIZE 16

struct Chunk {
  TileType tiles[CHUNK_SIZE][CHUNK_SIZE];
  bool isDirty;
};

struct OreVein {
  int x, y;      // Starting position
  int size;      // How many blocks in this vein
  TileType type; // What kind of ore
};

struct WorldGenParams {
  uint32_t seed = 12345;
  int surface_start = 110;     // Where surface starts (in tiles from top)
  float noise_scale = 0.04f;   // How stretched the noise is
  float height_variation = 6.5; // How much height varies
  int dirt_depth = 6;         // How deep is the dirt layer
  int min_ore_depth = 12;      // Minimum depth for ores to appear
  int max_veins = 5;           // Maximum number of ore veins per chunk
};

void place_ore_vein(Chunk *chunk, const OreVein &vein);
void generate_chunk(Chunk *chunk, int chunk_x, int chunk_y,
                    const WorldGenParams *params);
