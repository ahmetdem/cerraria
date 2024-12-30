// debug_system.h
#pragma once

#include "game.h"

// Forward declarations
struct Game;
struct Camera2D;

// Debug categories enum
enum class DebugCategory {
  GENERAL,
  RENDERING,
  WORLD,
  CHUNKS,
  PERFORMANCE,
  CAMERA
};

// Debug state container
struct DebugState {
  // General visualization toggles
  struct {
    bool showDebugWindow = true;
    bool showImGuiDemo = false;
  } general;

  // Rendering options
  struct {
    bool showGrid = true;
    bool showChunkBorders = true;
    float gridOpacity = 1.0f;
    Color gridColor = {0, 0, 0, 255};
    Color chunkBorderColor = {255, 255, 0, 255};
  } rendering;

  // World debug info
  struct {
    bool showMouseWorldCoords = true;
  } world;

  // Chunk system debug
  struct {
    bool showChunkStats = true;
    bool showLoadedChunks = true; // UNUSED FOR NOW
  } chunks;

  // Performance monitoring
  struct {
    bool enableProfiling = true;
    float fpsGraph[100] = {0};
    int fpsGraphOffset = 0;
  } performance;

  // Camera debug
  struct {
    bool lockCamera = false;
    bool showCameraInfo = true;
  } camera;
};

// Debug UI Manager class
class DebugUI {
public:
  static DebugUI &Instance() {
    static DebugUI instance;
    return instance;
  }

  void Initialize();
  void Shutdown();
  void Update(Game &game);
  void Render(Game &game);

  // Getters for debug states
  const DebugState &GetState() const { return state; }
  bool IsDebugEnabled() const { return state.general.showDebugWindow; }

  // Performance metrics
  struct PerformanceMetrics {
    int fps;
    int dirtyChunksCount = 0;
    int visibleChunksCount = 0;
  } metrics;

  // Helper methods
  void DrawGrid();
  void DrawChunkGrid();

private:
  DebugUI() = default;
  ~DebugUI() = default;

  // Different debug windows
  void RenderGeneralDebugWindow(Game &game);
  void RenderWorldDebugWindow(Game &game);
  void RenderChunkDebugWindow(Game &game);
  void RenderPerformanceWindow(Game &game);
  void RenderCameraDebugWindow(Camera2D &cam);

  // Helper Methods
  void ChangeWorldSeed(uint32_t &);

  DebugState state;
};

// Macro for easier access
#define DEBUG_UI DebugUI::Instance()
