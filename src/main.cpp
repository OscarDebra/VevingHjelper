#include <raylib.h>
#include "../include/config.h"
#include "../include/app.h"
#include <iostream>

int main() {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    
    InitWindow(config::screen_width, config::screen_height, "VevingHjelper");
    MaximizeWindow(); // Maximizes the window
    SetTargetFPS(60);

    App app;
    app.Init();

    while (!WindowShouldClose()) {

        BeginDrawing();
        app.Draw();
        EndDrawing();
    }

    app.Shutdown();
    CloseWindow();
}