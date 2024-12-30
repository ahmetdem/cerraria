#include "worldgen.h"
#include "noise.h"

inline int rand_range(std::mt19937 &rng, int min, int max) {
  return std::uniform_int_distribution<>(min, max)(rng);
}

void place_ore_vein(Chunk *chunk, const OreVein &vein) {
  if (vein.y >= 0 && vein.y < CHUNK_SIZE && vein.x >= 0 &&
      vein.x < CHUNK_SIZE) {
    chunk->tiles[vein.y][vein.x] = vein.type;
  }

  for (int i = 1; i < vein.size; i++) {
    int positions[][2] = {{vein.x + i, vein.y},
                          {vein.x - i, vein.y},
                          {vein.x, vein.y + i},
                          {vein.x, vein.y - i}};

    for (auto &pos : positions) {
      if (pos[1] >= 0 && pos[1] < CHUNK_SIZE && pos[0] >= 0 &&
          pos[0] < CHUNK_SIZE) {
        chunk->tiles[pos[1]][pos[0]] = vein.type;
      }
    }
  }
}

void generate_chunk(Chunk *chunk, int chunk_x, int chunk_y,
                    const WorldGenParams *params) {

  std::mt19937 rng(params->seed + (chunk_x * 51413) + (chunk_y * 15427));

  // Basic terrain generation
  for (int x = 0; x < CHUNK_SIZE; x++) {
    float world_x = (float)(x + chunk_x * CHUNK_SIZE);
    float noise_val = get_normalized_noise(world_x * params->noise_scale);
    int surface_height =
        params->surface_start + (int)(noise_val * params->height_variation);

    for (int y = 0; y < CHUNK_SIZE; y++) {
      int world_y = y + chunk_y * CHUNK_SIZE;

      if (world_y < surface_height) {
        chunk->tiles[y][x] = TILE_EMPTY;
      } else if (world_y < surface_height + params->dirt_depth) {
        chunk->tiles[y][x] = TILE_DIRT;
      } else {
        chunk->tiles[y][x] = TILE_STONE;
      }
    }
  }

  // Generate ore veins only below minimum depth
  if (chunk_y * CHUNK_SIZE >=
      (params->min_ore_depth + params->dirt_depth + params->surface_start)) {
    int num_veins = rand_range(rng, 1, params->max_veins);

    for (int i = 0; i < num_veins; i++) {
      OreVein vein = {.x = rand_range(rng, 0, CHUNK_SIZE - 1),
                      .y = rand_range(rng, 0, CHUNK_SIZE - 1),
                      .size = rand_range(rng, 2, 4),
                      .type = TILE_DIAMOND};
      place_ore_vein(chunk, vein);
    }
  }

  chunk->isDirty = true;
}
