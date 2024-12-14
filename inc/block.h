#ifndef BLOCK_H
#define BLOCK_H

#include "raylib.h"
#include "util.h"

#define MAX_TEXTURES 256

enum TileType { TILE_DIAMOND, TILE_DIRT, TILE_STONE, TILE_EMPTY, TILE_COUNT };

struct Vector2Int;
struct GridInfo;

struct Block {
  TileType type;

  Block(TileType t = TILE_EMPTY, int power = 0) : type(t) {};
};

bool LoadTextures();
Texture2D GetTextureByType(TileType type);
void UnloadAllTextures();

void DrawBlock(const Block &, const Vector2Int &, const GridInfo &gridInfo);

#endif // BLOCK_H
