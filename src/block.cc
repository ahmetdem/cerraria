#include "block.h"
#include "game.h"
#include "util.h"

std::array<Texture2D, MAX_TEXTURES> textures;

bool LoadTextures() {
  textures[TILE_DIAMOND] = LoadTexture("assets/diamond.png");
  textures[TILE_DIRT] = LoadTexture("assets/dirt.png");
  textures[TILE_STONE] = LoadTexture("assets/stone.png");

  // Validate that all textures loaded successfully
  for (int i = 0; i < TILE_COUNT; ++i) {
    if (textures[i].id == 0) {
      TraceLog(LOG_ERROR, "Failed to load texture for tile type %d", i);
      return false;
    }
  }

  return true;
}

Texture2D GetTextureByType(TileType type) {
  if (type < 0 || type >= TILE_COUNT) {
    TraceLog(LOG_WARNING, "Invalid TileType: %d", type);
    return Texture2D{}; // Return empty texture
  }
  return textures[type];
}

void UnloadAllTextures() {
  for (Texture2D &texture : textures) {
    if (texture.id != 0) {
      UnloadTexture(texture);
    }
  }
}

void DrawBlock(const Block &block, const Vector2Int &gridPos,
               const GridInfo &gridInfo) {
  Texture2D texture = GetTextureByType(block.type);
  if (texture.id == 0) {
    return;
  }

  Vector2 worldPos = GridToWorldPos(gridPos, gridInfo);

  Rectangle sourceRect = {0, 0, (float)texture.width, (float)texture.height};
  Rectangle destRect = {(float)worldPos.x, (float)worldPos.y, (float)TILE_SIZE,
                        (float)TILE_SIZE};
  Vector2 origin = {0.0f, 0.0f};

  DrawTexturePro(texture, sourceRect, destRect, origin, 0.0f, WHITE);
}
