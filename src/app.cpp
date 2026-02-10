#include "app.h"
#include <raylib.h>
#include "../external/raygui/raygui.h"
#include "config.h"
#include <iostream>


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

    float container_width = 300;
    float container_height = 400;

    float margin_top = (screen_height - container_height) / 2;
    float middle_x = screen_width / 2;

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
        app_screen = screen::main;
    }
}

void App::DrawMainScreen() {
    GuiSetStyle(DEFAULT, TEXT_SIZE, 18);

    DrawLeftColumn();
    DrawGrid();
}

void App::DrawLeftColumn() {
    int screen_height = GetScreenHeight();

    float edge_padding = 20;
    float text_width = 100;
    float element_spacing = 75;
    float element_width = 100;
    float element_height = 50;

    float element_x_pos = edge_padding + text_width;

    static int temp_rows = 1;
    static int temp_columns = 1;


    // Rows
    GuiLabel({edge_padding, edge_padding, text_width, element_height}, "Rows:");
    if (GuiValueBox({element_x_pos, edge_padding, element_width, element_height}, "", &temp_rows, 1, 100, is_editing_rows))
        is_editing_rows = !is_editing_rows;

    if (!is_editing_rows) {
        user_data.rows = temp_rows;
    }


    // Columns
    GuiLabel({edge_padding, edge_padding + element_spacing, text_width, element_height}, "Columns:");
    if (GuiValueBox({element_x_pos, edge_padding + element_spacing, element_width, element_height}, "", &temp_columns, 1, 100, is_editing_columns))
        is_editing_columns = !is_editing_columns;
    
    if (!is_editing_columns) {
        user_data.columns = temp_columns;
    }


    // Back button
    if (GuiButton({edge_padding, screen_height - element_height - edge_padding, element_width, element_height}, "Back")) {
        app_screen = screen::form;
    }
}

void App::DrawGrid() {
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    int edge_padding = 100;

    int available_width = screen_width - edge_padding * 2 - 200; // 200 is the width of the left column
    int available_height = screen_height - edge_padding * 2;

    float canvas_ratio = (float)user_data.width / (float)user_data.height;


    float canvas_width, canvas_height;
    
    if (available_width / canvas_ratio <= available_height) {
        // Width is the limiting factor
        canvas_width = available_width;
        canvas_height = available_width / canvas_ratio;
    } else {
        // Height is the limiting factor
        canvas_height = available_height;
        canvas_width = available_height * canvas_ratio;
    }

    // Center the canvas in the available space
    float canvas_x = 200 + edge_padding + (available_width - canvas_width) / 2;
    float canvas_y = edge_padding + (available_height - canvas_height) / 2;

    // Draw
    DrawRectangle(canvas_x, canvas_y, canvas_width, canvas_height, GRAY);
}