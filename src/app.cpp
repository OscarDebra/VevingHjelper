#include "app.h"
#include <raylib.h>
#include "../external/raygui/raygui.h"
#include "config.h"


void App::Init() {
    // initialize app state
}

void App::Draw() {
    ClearBackground(config::background_color);

    if (app_screen == screen::form) {
        DrawFormScreen();
    }
    else if (app_screen == screen::main) {
        DrawMainScreen();
    }
}

void App::DrawFormScreen() {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    float margin_top = (screen_height - 400) / 2;
    float middle_x = screen_width / 2;
    float container_width = 300;
    float element_width = 200;
    float element_height = 50;
    float element_x_pos = middle_x + container_width/2 - element_width;
    float text_x_pos = middle_x - container_width/2;
    float element_spacing = 100;
    float text_width = 100;

    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);

    DrawText("Enter canvas ratio", text_x_pos, margin_top, 30, DARKGRAY);

    GuiLabel({text_x_pos, margin_top + element_spacing, text_width, element_height}, "Width:");
    GuiLabel({text_x_pos, margin_top + element_spacing * 2, text_width, element_height}, "Height:");

    if (GuiValueBox({element_x_pos, margin_top + element_spacing, element_width, element_height}, "", &user_data.width, 1, 100, is_editing_width))
        is_editing_width = !is_editing_width;
    
    if (GuiValueBox({element_x_pos, margin_top + element_spacing * 2, element_width, element_height}, "", &user_data.height, 1, 100, is_editing_height))
        is_editing_height = !is_editing_height;

    if (GuiButton({element_x_pos, margin_top + element_spacing * 3, element_width, element_height}, "Confirm")) {
        TraceLog(LOG_INFO, "Width: %d", user_data.width);
        TraceLog(LOG_INFO, "Height: %d", user_data.height);
        app_screen = screen::main;
    }
}

void App::DrawMainScreen() {
    DrawText("Data received!", 20, 80, 24, DARKGREEN);

    DrawText(TextFormat("Width: %d", user_data.width), 20, 130, 20, DARKGRAY);
    DrawText(TextFormat("Height: %d", user_data.height), 20, 160, 20, DARKGRAY);
    
    if (GuiButton({20, 220, 200, 30}, "Back")) {
        app_screen = screen::form;
    }
}

void App::Shutdown() {
    // cleanup if needed
}