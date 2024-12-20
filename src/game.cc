#include "game.h"
#include "block.h"
#include "raylib.h"
#include "raymath.h"
#include "debug.h"

void InitGridInfo(GridInfo &gridInfo) {
  gridInfo.centerX = ROW_TILE_COUNT / 2;
  gridInfo.centerY = COL_TILE_COUNT / 2;

  // Precompute offsets for odd/even grid sizes
  gridInfo.xOffset = (ROW_TILE_COUNT % 2 == 0) ? 0 : TILE_SIZE / 2 - TILE_SIZE;
  gridInfo.yOffset = (COL_TILE_COUNT % 2 == 0) ? 0 : TILE_SIZE / 2 - TILE_SIZE;

  for (int y = 0; y < COL_TILE_COUNT; ++y) {
    for (int x = 0; x < ROW_TILE_COUNT; ++x) {
      gridInfo.precomputedWorldPositions[x][y] =
          GridToWorldPos({x, y}, gridInfo);
    }
  }
}

Vector2 GridToWorldPos(const Vector2Int &gridPos, const GridInfo &gridInfo) {
  Vector2 worldPos;

  worldPos.x = (gridPos.x - gridInfo.centerX) * TILE_SIZE + gridInfo.xOffset;
  worldPos.y = (gridPos.y - gridInfo.centerY) * TILE_SIZE + gridInfo.yOffset;

  return worldPos;
}

Vector2Int WorldToChunkPos(const Vector2 &worldPos) {
  Vector2Int pos, temp;
  temp = WorldToGridPos(worldPos);

  // Clamp values between 0 and max chunk size
  pos.x = Clamp(temp.x / CHUNK_SIZE, 0, NUM_CHUNKS_X - 1);
  pos.y = Clamp(temp.y / CHUNK_SIZE, 0, NUM_CHUNKS_Y - 1);

  return pos;
}

Vector2Int WorldToGridPos(const Vector2 &worldPos) {
  Vector2Int pos = {};

  pos.x = static_cast<int>(
              std::floor((worldPos.x + (float)TILE_SIZE / 2) / TILE_SIZE)) +
          ROW_TILE_COUNT / 2;

  pos.y =
      static_cast<int>(std::floor(worldPos.y / TILE_SIZE)) + COL_TILE_COUNT / 2;

  return pos;
}

void InitChunks(ChunkGrid &chunks) {
  for (int y = 0; y < NUM_CHUNKS_Y; ++y) {
    for (int x = 0; x < NUM_CHUNKS_X; ++x) {
      Chunk &chunk = chunks[y][x];
      chunk.isDirty = false;

      for (int tileY = 0; tileY < CHUNK_SIZE; ++tileY) {
        for (int tileX = 0; tileX < CHUNK_SIZE; ++tileX) {
          chunk.tiles[tileY][tileX] = TILE_DIRT;
        }
      }
    }
  }
}

void InitGameState(Game &game) {
  InitChunks(game.chunks);
  InitGridInfo(game.gridInfo);

  game.cam.zoom = 1.0f;
}

void DrawGameWorld(const ChunkGrid &chunks, const GridInfo &gridInfo,
                   const Camera2D &cam) {
  int chunkXMin, chunkXMax, chunkYMin, chunkYMax;
  GetVisibleChunks(cam, chunkXMin, chunkXMax, chunkYMin, chunkYMax);

  int dirtyChunksCount = 0;
  int visibleChunksCount = 0;

  for (int chunkY = chunkYMin; chunkY <= chunkYMax; ++chunkY) {
    for (int chunkX = chunkXMin; chunkX <= chunkXMax; ++chunkX) {
      const Chunk &chunk = chunks[chunkY][chunkX];
      ++visibleChunksCount;

      // Count dirty chunks
      if (chunk.isDirty) {
        ++dirtyChunksCount;
      }

      for (int y = 0; y < CHUNK_SIZE; ++y) {
        for (int x = 0; x < CHUNK_SIZE; ++x) {
          Vector2Int gridPos = {chunkX * CHUNK_SIZE + x,
                                chunkY * CHUNK_SIZE + y};
          TileType tile = chunk.tiles[y][x];

          Vector2 worldPos = GridToWorldPos(gridPos, gridInfo);
          if (IsInsideVisibleCam(cam, worldPos)) {
            DrawBlock(tile, gridPos, gridInfo, cam);
          }
        }
      }
    }
  }

  DEBUG_UI.metrics.dirtyChunksCount = dirtyChunksCount;
  DEBUG_UI.metrics.visibleChunksCount = visibleChunksCount;
}

bool IsInsideVisibleCam(const Camera2D &cam, const Vector2 &blockWorldPos) {
  float visibleWidth = GetScreenWidth() / cam.zoom;
  float visibleHeight = GetScreenHeight() / cam.zoom;

  Vector2 cameraPosition = cam.target;
  float margin = 1000.0f;

  float left = cameraPosition.x - visibleWidth / 2.0f - margin;
  float right = cameraPosition.x + visibleWidth / 2.0 + margin;
  float top = cameraPosition.y - visibleHeight / 2.0f - margin;
  float bottom = cameraPosition.y + visibleHeight / 2.0f + margin;

  return (blockWorldPos.x >= left && blockWorldPos.x <= right &&
          blockWorldPos.y >= top && blockWorldPos.y <= bottom);
}

void GetVisibleChunks(const Camera2D &cam, int &chunkXMin, int &chunkXMax,
                      int &chunkYMin, int &chunkYMax) {
  float visibleWidth = GetScreenWidth() / cam.zoom;
  float visibleHeight = GetScreenHeight() / cam.zoom;

  Vector2 cameraPosition = cam.target;
  float margin = 1000.0f;

  float left = cameraPosition.x - visibleWidth / 2.0f - margin;
  float right = cameraPosition.x + visibleWidth / 2.0f + margin;
  float top = cameraPosition.y - visibleHeight / 2.0f - margin;
  float bottom = cameraPosition.y + visibleHeight / 2.0f + margin;

  Vector2Int leftTopChunk = WorldToChunkPos({left, top});
  Vector2Int rightBottomChunk = WorldToChunkPos({right, bottom});

  chunkXMin = leftTopChunk.x;
  chunkXMax = rightBottomChunk.x;
  chunkYMin = leftTopChunk.y;
  chunkYMax = rightBottomChunk.y;
}
