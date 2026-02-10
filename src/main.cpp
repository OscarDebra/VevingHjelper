#include <raylib.h>
#include "../include/config.h"
#include "../include/app.h"
#include <iostream>

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(config::screen_width, config::screen_height, "VevingHjelper");
    MaximizeWindow();

    SetTargetFPS(60);

    App app;

    while (!WindowShouldClose()) {

        BeginDrawing();
        app.Draw();
        EndDrawing();
    }

    CloseWindow();
}