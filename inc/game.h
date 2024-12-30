#ifndef GAME_H
#define GAME_H

#include "block.h"
#include "raylib.h"
#include "util.h"
#include "worldgen.h"
#include <array>

#define GAME_WIDTH (175000 / 2)
#define GAME_HEIGHT (90000 / 2)

#define TILE_SIZE 100

#define ROW_TILE_COUNT (GAME_WIDTH / TILE_SIZE)
#define COL_TILE_COUNT (GAME_HEIGHT / TILE_SIZE)

#define NUM_CHUNKS_X (ROW_TILE_COUNT / CHUNK_SIZE)
#define NUM_CHUNKS_Y (COL_TILE_COUNT / CHUNK_SIZE)

using std::array;

using ChunkGrid = array<array<Chunk, NUM_CHUNKS_X>, NUM_CHUNKS_Y>;

struct GridInfo {
  int centerX, centerY;
  int xOffset, yOffset;

  Vector2 precomputedWorldPositions[ROW_TILE_COUNT][COL_TILE_COUNT];
};

struct Game {
  Vector2 mouseWorldPos;
  Vector2Int gridPos = {-1, -1};
  float dt = 0.0f;
  Camera2D cam = {};
  ChunkGrid chunks;
  GridInfo gridInfo;
  WorldGenParams worldGenParams = {};
};

void InitGameState(Game &);
void InitGridInfo(GridInfo &);
void InitWorldPositions(Vector2 precomputedWorldPositions[][COL_TILE_COUNT]);

void ChangeWorldSeed(uint32_t &);
void GenerateWorld(ChunkGrid &, const WorldGenParams &);

void DrawGameWorld(const ChunkGrid &chunks, const GridInfo &gridInfo,
                   const Camera2D &cam);

Vector2 GridToWorldPos(const Vector2Int &, const GridInfo &);
Vector2Int WorldToChunkPos(const Vector2 &);
Vector2Int WorldToGridPos(const Vector2 &);

bool IsInsideVisibleCam(const Camera2D &, const Vector2 &);
void GetVisibleChunks(const Camera2D &cam, int &chunkXMin, int &chunkXMax,
                      int &chunkYMin, int &chunkYMax);

#endif // GAME_H
