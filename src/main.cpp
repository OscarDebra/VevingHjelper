#include <raylib.h>
#include "../include/config.h"
#include "../include/app.h"

int main() {
    InitWindow(config::screen_width, config::screen_height, "VevingHjelper");
    SetTargetFPS(60);

    App app;

    while (!WindowShouldClose()) {

        BeginDrawing();
        app.draw();
        EndDrawing();
    }

    CloseWindow();
}