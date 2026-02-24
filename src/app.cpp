#include "app.h"
#include <raylib.h>
#include "../external/raygui/raygui.h"
#include "config.h"
#include <iostream>
#include <algorithm>
#include <raymath.h>

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

    std::vector<Color> colors = { RED, GREEN, BLUE, YELLOW, PURPLE, ORANGE, PINK, LIME, SKYBLUE, BROWN };

    const float SNAP = 6.0f;

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
    } 
    else {
        // Height is the limiting factor
        canvas_height = available_height;
        canvas_width = available_height * canvas_ratio;
    }

    float canvas_x = 200 + edge_padding + (available_width - canvas_width) / 2;
    float canvas_y = edge_padding + (available_height - canvas_height) / 2;

    Vector2 mouse = GetMousePosition();

    // Hover detection
    int hoveredV = -1, hoveredH = -1;
    if (draggedV == -1 && draggedH == -1) {
        for (int i = 0; i < (int)v_dividers.size(); i++) {
            float screen_x = canvas_x + v_dividers[i] * canvas_width;
            if (fabsf(mouse.x - screen_x) < SNAP &&
                mouse.y >= canvas_y && mouse.y <= canvas_y + canvas_height) {
                hoveredV = i; break;
            }
        }
        for (int i = 0; i < (int)h_dividers.size(); i++) {
            float screen_y = canvas_y + h_dividers[i] * canvas_height;
            if (fabsf(mouse.y - screen_y) < SNAP &&
                mouse.x >= canvas_x && mouse.x <= canvas_x + canvas_width) {
                hoveredH = i; break;
            }
        }
    }

    // Drag start/end
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        if (hoveredV != -1) draggedV = hoveredV;
        else if (hoveredH != -1) draggedH = hoveredH;
    }
    if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
        draggedV = draggedH = -1;
    }

    // Update divider positions
    if (draggedV != -1) {
        float norm = (mouse.x - canvas_x) / (float)canvas_width;
        // Clamp between neighbors so lines can't cross
        float lo = (draggedV > 0) ? v_dividers[draggedV - 1] + 0.02f : 0.02f;
        float hi = (draggedV < (int)v_dividers.size() - 1) ? v_dividers[draggedV + 1] - 0.02f : 0.98f;
        v_dividers[draggedV] = Clamp(norm, lo, hi);
    }
    if (draggedH != -1) {
        float norm = (mouse.y - canvas_y) / (float)canvas_height;
        float lo = (draggedH > 0) ? h_dividers[draggedH - 1] + 0.02f : 0.02f;
        float hi = (draggedH < (int)h_dividers.size() - 1) ? h_dividers[draggedH + 1] - 0.02f : 0.98f;
        h_dividers[draggedH] = Clamp(norm, lo, hi);
    }

    // Cursor
    if (hoveredV != -1 || draggedV != -1) SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
    else if (hoveredH != -1 || draggedH != -1) SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

    std::vector<float> col_edges = { (float)canvas_x };
    for (float d : v_dividers) col_edges.push_back(canvas_x + d * canvas_width);
    col_edges.push_back((float)(canvas_x + canvas_width));

    std::vector<float> row_edges = { (float)canvas_y };
    for (float d : h_dividers) row_edges.push_back(canvas_y + d * canvas_height);
    row_edges.push_back((float)(canvas_y + canvas_height));

    // Draw cells
    int color_index = 0;
    for (int row = 0; row < (int)row_edges.size() - 1; row++) {
        for (int col = 0; col < (int)col_edges.size() - 1; col++) {
            int x = (int)col_edges[col];
            int y = (int)row_edges[row];
            int w = (int)(col_edges[col + 1] - col_edges[col]);
            int h = (int)(row_edges[row + 1] - row_edges[row]);

            DrawRectangle(x, y, w, h, colors[color_index % colors.size()]);
            color_index++;
        }
    }

    // Draw divider lines
    for (int i = 0; i < (int)v_dividers.size(); i++) {
        float x = canvas_x + v_dividers[i] * canvas_width;
        Color c = (draggedV == i) ? WHITE : (hoveredV == i) ? GRAY : BLACK;
        DrawLineEx({x, (float)canvas_y}, {x, (float)(canvas_y + canvas_height)}, 2.0f, c);
    }
    for (int i = 0; i < (int)h_dividers.size(); i++) {
        float y = canvas_y + h_dividers[i] * canvas_height;
        Color c = (draggedH == i) ? WHITE : (hoveredH == i) ? GRAY : BLACK;
        DrawLineEx({(float)canvas_x, y}, {(float)(canvas_x + canvas_width), y}, 2.0f, c);
    }

    // Border
    DrawRectangleLines(canvas_x, canvas_y, canvas_width, canvas_height, BLACK);
    
}