#include "raylib.h"

int main() {
    // Initialize window
    InitWindow(800, 600, "Hello, Raylib!");
    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Hello!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }

    CloseWindow(); // Close window and clean up resources
    return 0;
}
