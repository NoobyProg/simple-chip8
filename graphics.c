#include <stdio.h>
#include "include/raylib.h"
#include "include/graphics.h"

void initScreen(){
    int W = 1280, H = 720;

    InitWindow(W, H, "chip-8 emulator");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(DARKBROWN);
        DrawText("Your Chip-8 Interpreter has a working screen", W/2 - 250, H/2, 20, WHITE);
        EndDrawing();
    }
    
    CloseWindow();
}