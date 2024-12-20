// debug_system.cc
#include "debug.h"
#include <imgui.h>
#include <raylib.h>

void DebugUI::Initialize() {
  // Any additional initialization
}

void DebugUI::Shutdown() {
  // Any additional initialization
}

void DebugUI::Update(Game &game) {
  if (IsKeyPressed(KEY_F3)) {
    state.general.showDebugWindow = !state.general.showDebugWindow;
  }
}

void DebugUI::Render(Game &game) {
  if (!state.general.showDebugWindow)
    return;

  // Main debug window
  if (ImGui::Begin("Debug Controls", &state.general.showDebugWindow)) {
    if (ImGui::BeginTabBar("DebugTabs")) {
      if (ImGui::BeginTabItem("General")) {
        RenderGeneralDebugWindow(game);
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem("World")) {
        RenderWorldDebugWindow(game);
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem("Chunks")) {
        RenderChunkDebugWindow(game);
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem("Performance")) {
        RenderPerformanceWindow(game);
        ImGui::EndTabItem();
      }
      if (ImGui::BeginTabItem("Camera")) {
        RenderCameraDebugWindow(game.cam);
        ImGui::EndTabItem();
      }
      ImGui::EndTabBar();
    }
  }
  ImGui::End();

  // Demo window if enabled
  if (state.general.showImGuiDemo) {
    ImGui::ShowDemoWindow(&state.general.showImGuiDemo);
  }
}

void DebugUI::RenderGeneralDebugWindow(Game &game) {
  ImGui::Checkbox("Show ImGui Demo", &state.general.showImGuiDemo);

  ImGui::Separator();

  if (ImGui::TreeNode("Visualization Options")) {
    ImGui::Checkbox("Show Grid", &state.rendering.showGrid);
    if (state.rendering.showGrid) {
      ImGui::SliderFloat("Grid Opacity", &state.rendering.gridOpacity, 0.0f,
                         1.0f);

      // Convert Color to float[4] for ImGui
      float gridColor[4] = {state.rendering.gridColor.r / 255.0f,
                            state.rendering.gridColor.g / 255.0f,
                            state.rendering.gridColor.b / 255.0f,
                            state.rendering.gridColor.a / 255.0f};

      if (ImGui::ColorEdit4("Grid Color", gridColor)) {
        // Convert float[4] back to Color
        state.rendering.gridColor = {
            static_cast<unsigned char>(gridColor[0] * 255),
            static_cast<unsigned char>(gridColor[1] * 255),
            static_cast<unsigned char>(gridColor[2] * 255),
            static_cast<unsigned char>(gridColor[3] * 255)};
      }
    }

    ImGui::Checkbox("Show Chunk Borders", &state.rendering.showChunkBorders);
    if (state.rendering.showChunkBorders) {
      // Convert Color to float[4] for ImGui
      float chunkBorderColor[4] = {state.rendering.chunkBorderColor.r / 255.0f,
                                   state.rendering.chunkBorderColor.g / 255.0f,
                                   state.rendering.chunkBorderColor.b / 255.0f,
                                   state.rendering.chunkBorderColor.a / 255.0f};

      if (ImGui::ColorEdit4("Chunk Border Color", chunkBorderColor)) {
        // Convert float[4] back to Color
        state.rendering.chunkBorderColor = {
            static_cast<unsigned char>(chunkBorderColor[0] * 255),
            static_cast<unsigned char>(chunkBorderColor[1] * 255),
            static_cast<unsigned char>(chunkBorderColor[2] * 255),
            static_cast<unsigned char>(chunkBorderColor[3] * 255)};
      }
    }

    ImGui::TreePop();
  }
}

void DebugUI::RenderWorldDebugWindow(Game &game) {
  ImGui::Checkbox("Show Mouse World Coordinates",
                  &state.world.showMouseWorldCoords);

  if (state.world.showMouseWorldCoords) {
    Vector2 mouseWorld = GetScreenToWorld2D(GetMousePosition(), game.cam);
    ImGui::Text("Mouse World Pos: %.2f, %.2f", mouseWorld.x, mouseWorld.y);

    Vector2 calcWorldPos = GridToWorldPos(game.gridPos, game.gridInfo);
    ImGui::Text("Calculated World Pos: %.2f, %.2f", calcWorldPos.x,
                calcWorldPos.y);

    Vector2Int gridPos = WorldToGridPos(mouseWorld);
    ImGui::Text("Grid Pos: %d, %d", gridPos.x, gridPos.y);

    Vector2Int chunkPos = WorldToChunkPos(game.mouseWorldPos);
    ImGui::Text("Chunk Pos: %d, %d", chunkPos.x, chunkPos.y);
  }
}

void DebugUI::RenderChunkDebugWindow(Game &game) {
  ImGui::Checkbox("Show Chunk Stats", &state.chunks.showChunkStats);

  if (state.chunks.showChunkStats) {
    ImGui::Text("Loaded Chunks: %d", metrics.visibleChunksCount);
    ImGui::Text("Dirty Chunks: %d", metrics.dirtyChunksCount);
  }
}

void DebugUI::RenderPerformanceWindow(Game &game) {
  ImGui::Checkbox("Enable Profiling", &state.performance.enableProfiling);

  if (state.performance.enableProfiling) {
    state.performance.fpsGraph[state.performance.fpsGraphOffset] = metrics.fps;

    state.performance.fpsGraphOffset = (state.performance.fpsGraphOffset + 1) %
                                       IM_ARRAYSIZE(state.performance.fpsGraph);

    ImGui::PlotLines("FPS", state.performance.fpsGraph,
                     IM_ARRAYSIZE(state.performance.fpsGraph),
                     state.performance.fpsGraphOffset, "FPS History", 0.0f,
                     500.0f, ImVec2(0, 80));

    ImGui::Text("FPS: %d", metrics.fps);
  }
}

void DebugUI::RenderCameraDebugWindow(Camera2D &cam) {
  ImGui::Checkbox("Show Camera Info", &state.camera.showCameraInfo);
  ImGui::Checkbox("Lock Cam", &state.camera.lockCamera);

  if (state.camera.showCameraInfo) {
    ImGui::Text("Camera Position: %.2f, %.2f", cam.target.x, cam.target.y);
    ImGui::Text("Camera Zoom: %.2f", cam.zoom);
  }
}

void DebugUI::DrawGrid() {
  if (!state.rendering.showGrid)
    return;

  int offsetX = GAME_WIDTH / 2;
  int offsetY = GAME_HEIGHT / 2;

  // Adjust color opacity
  state.rendering.gridColor.a =
      (unsigned char)(255 * state.rendering.gridOpacity);

  for (int x = 0; x <= ROW_TILE_COUNT; ++x) {
    int lineX = x * TILE_SIZE - offsetX;
    DrawLine(lineX, -offsetY, lineX, COL_TILE_COUNT * TILE_SIZE - offsetY,
             state.rendering.gridColor);
  }

  for (int y = 0; y <= COL_TILE_COUNT; ++y) {
    int lineY = y * TILE_SIZE - offsetY;
    DrawLine(-offsetX, lineY, ROW_TILE_COUNT * TILE_SIZE - offsetX, lineY,
             state.rendering.gridColor);
  }
}

void DebugUI::DrawChunkGrid() {
  if (!state.rendering.showChunkBorders)
    return;

  int offsetX = GAME_WIDTH / 2;
  int offsetY = GAME_HEIGHT / 2;

  // Adjust color opacity
  state.rendering.chunkBorderColor.a = (unsigned char)(255 * 1.0f);

  for (int x = 0; x <= NUM_CHUNKS_X; ++x) {
    int lineX = x * (CHUNK_SIZE * TILE_SIZE) - offsetX;
    DrawLineEx(
        Vector2{(float)lineX, (float)-offsetY},
        Vector2{(float)lineX, (float)(COL_TILE_COUNT * TILE_SIZE - offsetY)},
        8.0f, state.rendering.chunkBorderColor);
  }

  for (int y = 0; y <= NUM_CHUNKS_Y; ++y) {
    int lineY = y * (CHUNK_SIZE * TILE_SIZE) - offsetY;
    DrawLineEx(
        Vector2{(float)-offsetX, (float)lineY},
        Vector2{(float)(ROW_TILE_COUNT * TILE_SIZE - offsetX), (float)lineY},
        8.0f, state.rendering.chunkBorderColor);
  }
}
