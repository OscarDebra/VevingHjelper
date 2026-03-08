#include "app.h"
#include <raylib.h>
#include "../external/raygui/raygui.h"
#include "config.h"
#include <iostream>
#include <algorithm>
#include <raymath.h>
#include <cstring>

void App::Draw() {
    ClearBackground(config::background_color);

    if (app_screen == screen::form) {
        DrawFormScreen();
    } else if (app_screen == screen::main) {
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
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0x000000FF);
    DrawText("Enter canvas ratio", text_x_pos, margin_top, 30, BLACK);

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
    if (!is_editing_rows) user_data.rows = temp_rows;

    // Columns
    GuiLabel({edge_padding, edge_padding + element_spacing, text_width, element_height}, "Columns:");
    if (GuiValueBox({element_x_pos, edge_padding + element_spacing, element_width, element_height}, "", &temp_columns, 1, 100, is_editing_columns))
        is_editing_columns = !is_editing_columns;
    if (!is_editing_columns) user_data.columns = temp_columns;

    if (GuiButton({edge_padding, edge_padding + element_spacing * 2, element_width + text_width, element_height}, "Equalize Columns")) {
        equalize_columns = true;
    }
    if (GuiButton({edge_padding, edge_padding + element_spacing * 3, element_width + text_width, element_height}, "Equalize Rows")) {
        equalize_rows = true;
    }

    // Back button
    if (GuiButton({edge_padding, screen_height - element_height - edge_padding, element_width, element_height}, "Back")) {
        app_screen = screen::form;
    }

}

void App::DrawGrid() {
    const float SNAP = 6.0f;
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    int edge_padding = 100;
    int available_width = screen_width - edge_padding * 2 - 200;
    int available_height = screen_height - edge_padding * 2;

    float canvas_ratio = (float)user_data.width / (float)user_data.height;
    float canvas_width, canvas_height;

    if (available_width / canvas_ratio <= available_height) {
        canvas_width = available_width;
        canvas_height = available_width / canvas_ratio;
    } else {
        canvas_height = available_height;
        canvas_width = available_height * canvas_ratio;
    }

    float canvas_x = 225 + edge_padding + (available_width - canvas_width) / 2;
    float canvas_y = edge_padding + (available_height - canvas_height) / 2;

    Vector2 mouse = GetMousePosition();
    bool clicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
    bool released = IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
    bool clicked_any_input = false;


    // Sync dividers to row/column counts
    int target_v = user_data.columns - 1;
    int target_h = user_data.rows - 1;

    while ((int)v_dividers.size() < target_v) {
        float t = (float)(v_dividers.size() + 1) / (float)(v_dividers.size() + 2);
        v_dividers.push_back(t);
        std::sort(v_dividers.begin(), v_dividers.end());
    }
    while ((int)v_dividers.size() > target_v) v_dividers.pop_back();

    while ((int)h_dividers.size() < target_h) {
        float t = (float)(h_dividers.size() + 1) / (float)(h_dividers.size() + 2);
        h_dividers.push_back(t);
        std::sort(h_dividers.begin(), h_dividers.end());
    }
    while ((int)h_dividers.size() > target_h) h_dividers.pop_back();


    // Equalizer buttons logic
    if (equalize_columns) {
        for (int i = 0; i < (int)v_dividers.size(); i++)
            v_dividers[i] = (float)(i + 1) / (float)(v_dividers.size() + 1);
        equalize_columns = false;
    }
    if (equalize_rows) {
        for (int i = 0; i < (int)h_dividers.size(); i++)
            h_dividers[i] = (float)(i + 1) / (float)(h_dividers.size() + 1);
        equalize_rows = false;
    }


    // Hover detection
    int hoveredV = -1, hoveredH = -1;
    if (draggedV == -1 && draggedH == -1) {
        for (int i = 0; i < (int)v_dividers.size(); i++) {
            float screen_x = canvas_x + v_dividers[i] * canvas_width;
            if (fabsf(mouse.x - screen_x) < SNAP && mouse.y >= canvas_y && mouse.y <= canvas_y + canvas_height) {
                hoveredV = i;
                break;
            }
        }
        for (int i = 0; i < (int)h_dividers.size(); i++) {
            float screen_y = canvas_y + h_dividers[i] * canvas_height;
            if (fabsf(mouse.y - screen_y) < SNAP && mouse.x >= canvas_x && mouse.x <= canvas_x + canvas_width) {
                hoveredH = i;
                break;
            }
        }
    }

    bool started_drag = false;
    if (clicked) {
        if (hoveredV != -1) { draggedV = hoveredV; started_drag = true; }
        else if (hoveredH != -1) { draggedH = hoveredH; started_drag = true; }
    }
    if (released) draggedV = draggedH = -1;


    // Update dividers before building edges
    if (draggedV != -1) {
        float norm = (mouse.x - canvas_x) / canvas_width;
        float lo = (draggedV > 0) ? v_dividers[draggedV - 1] + 0.02f : 0.02f;
        float hi = (draggedV < (int)v_dividers.size() - 1) ? v_dividers[draggedV + 1] - 0.02f : 0.98f;
        v_dividers[draggedV] = Clamp(norm, lo, hi);
    }
    if (draggedH != -1) {
        float norm = (mouse.y - canvas_y) / canvas_height;
        float lo = (draggedH > 0) ? h_dividers[draggedH - 1] + 0.02f : 0.02f;
        float hi = (draggedH < (int)h_dividers.size() - 1) ? h_dividers[draggedH + 1] - 0.02f : 0.98f;
        h_dividers[draggedH] = Clamp(norm, lo, hi);
    }


    // Build edges after updating dividers
    std::vector<float> col_edges = { canvas_x };
    for (float d : v_dividers) col_edges.push_back(canvas_x + d * canvas_width);
    col_edges.push_back(canvas_x + canvas_width);

    std::vector<float> row_edges = { canvas_y };
    for (float d : h_dividers) row_edges.push_back(canvas_y + d * canvas_height);
    row_edges.push_back(canvas_y + canvas_height);

    int col_count = col_edges.size() - 1;
    int row_count = row_edges.size() - 1;


    // Ensure color arrays
    if ((int)column_colors_a.size() != col_count) {
        column_colors_a.assign(col_count, WHITE);
        column_color_inputs_a.resize(col_count);
        for (auto &buf : column_color_inputs_a) strcpy(buf.data(), "FFFFFF");
    }
    if ((int)row_colors_a.size() != row_count) {
        row_colors_a.assign(row_count, WHITE);
        row_color_inputs_a.resize(row_count);
        for (auto &buf : row_color_inputs_a) strcpy(buf.data(), "FFFFFF");
    }

    if ((int)column_colors_b.size() != col_count) {
        column_colors_b.assign(col_count, BLACK);
        column_color_inputs_b.resize(col_count);
        for (auto &buf : column_color_inputs_b) strcpy(buf.data(), "000000");
    }
    if ((int)row_colors_b.size() != row_count) {
        row_colors_b.assign(row_count, BLACK);
        row_color_inputs_b.resize(row_count);
        for (auto &buf : row_color_inputs_b) strcpy(buf.data(), "000000");
    }



    // Column hex inputs a
    for (int col = 0; col < col_count; col++) {
        float cell_center_x = col_edges[col] + (col_edges[col+1] - col_edges[col]) / 2.0f;
        Rectangle swatch = { cell_center_x - 10, canvas_y - 25, 20, 20 };
        Rectangle box = { cell_center_x - 43, canvas_y - 55, 85, 24 };
        Color preview = ParseColor(column_color_inputs_a[col].data());

        DrawRectangleRec(swatch, preview);
        DrawRectangleLinesEx(swatch, 1, BLACK);

        if (clicked) {
            if (CheckCollisionPointRec(mouse, box) && active_column_input_a == col) {
                clicked_any_input = true;
            } else if (CheckCollisionPointRec(mouse, swatch)) {
                active_column_input_a = (active_column_input_a == col) ? -1 : col;
                active_row_input_a = -1;
                active_column_input_b = -1;  // close B
                active_row_input_b = -1;     // close B
                clicked_any_input = true;
            }
        }

        if (active_column_input_a == col) {
            GuiTextBox(box, column_color_inputs_a[col].data(), 7, true);
            column_colors_a[col] = ParseColor(column_color_inputs_a[col].data());

            HandleCopyPaste(column_color_inputs_a[col].data(), 7);
        } else {
            column_colors_a[col] = preview;
        }
    }


    // Column hex inputs b
    for (int col = 0; col < col_count; col++) {
        float cell_center_x = col_edges[col] + (col_edges[col+1] - col_edges[col]) / 2.0f;
        Rectangle swatch = { cell_center_x - 10, canvas_y + canvas_height + 5, 20, 20 };
        Rectangle box = { cell_center_x - 43, canvas_y + canvas_height + 30, 85, 24 };
        Color preview = ParseColor(column_color_inputs_b[col].data());

        DrawRectangleRec(swatch, preview);
        DrawRectangleLinesEx(swatch, 1, BLACK);

        if (clicked) {
            if (CheckCollisionPointRec(mouse, box) && active_column_input_b == col) {
                clicked_any_input = true;
            } else if (CheckCollisionPointRec(mouse, swatch)) {
                active_column_input_b = (active_column_input_b == col) ? -1 : col;
                active_row_input_b = -1;
                active_column_input_a = -1;   // close A
                active_row_input_a = -1;      // close A
                clicked_any_input = true;
            }
        }

        if (active_column_input_b == col) {
            GuiTextBox(box, column_color_inputs_b[col].data(), 7, true);
            HandleCopyPaste(column_color_inputs_b[col].data(), 7);
            column_colors_b[col] = ParseColor(column_color_inputs_b[col].data());
        } else {
            column_colors_b[col] = preview;
        }
    }


    // Row hex inputs a
    for (int row = 0; row < row_count; row++) {
        float cell_center_y = row_edges[row] + (row_edges[row+1] - row_edges[row]) / 2.0f;
        Rectangle swatch = { canvas_x - 25, cell_center_y - 10, 20, 20 };
        Rectangle box = { canvas_x - 90, cell_center_y - 40, 85, 24 };
        Color preview = ParseColor(row_color_inputs_a[row].data());

        DrawRectangleRec(swatch, preview);
        DrawRectangleLinesEx(swatch, 1, BLACK);

        if (clicked) {
            if (CheckCollisionPointRec(mouse, box) && active_row_input_a == row) {
                clicked_any_input = true;
            } else if (CheckCollisionPointRec(mouse, swatch)) {
                active_row_input_a = (active_row_input_a == row) ? -1 : row;
                active_column_input_a = -1;
                active_column_input_b = -1;
                active_row_input_b = -1;
                clicked_any_input = true;
            }
        }

        if (active_row_input_a == row) {
            GuiTextBox(box, row_color_inputs_a[row].data(), 7, true);
            row_colors_a[row] = ParseColor(row_color_inputs_a[row].data());

            HandleCopyPaste(row_color_inputs_a[row].data(), 7);
        } else {
            row_colors_a[row] = preview;
        }
    }


    // Row hex inputs b
    for (int row = 0; row < row_count; row++) {
        float cell_center_y = row_edges[row] + (row_edges[row+1] - row_edges[row]) / 2.0f;
        Rectangle swatch = { canvas_x + canvas_width + 5, cell_center_y - 10, 20, 20 };
        Rectangle box = { canvas_x + canvas_width + 30, cell_center_y - 11, 85, 24 };
        Color preview = ParseColor(row_color_inputs_b[row].data());

        DrawRectangleRec(swatch, preview);
        DrawRectangleLinesEx(swatch, 1, BLACK);

        if (clicked) {
            if (CheckCollisionPointRec(mouse, box) && active_row_input_b == row) {
                clicked_any_input = true;
            } else if (CheckCollisionPointRec(mouse, swatch)) {
                active_row_input_b = (active_row_input_b == row) ? -1 : row;
                active_column_input_b = -1;
                active_column_input_a = -1;   // close A
                active_row_input_a = -1;      // close A
                clicked_any_input = true;
            }
        }

        if (active_row_input_b == row) {
            GuiTextBox(box, row_color_inputs_b[row].data(), 7, true);
            HandleCopyPaste(row_color_inputs_b[row].data(), 7);
            row_colors_b[row] = ParseColor(row_color_inputs_b[row].data());
        } else {
            row_colors_b[row] = preview;
        }
    }


    // Close inputs if clicked elsewhere
    if (clicked && !clicked_any_input && !started_drag) {
        active_column_input_a = -1;
        active_row_input_a = -1;
        active_column_input_b = -1;
        active_row_input_b = -1;
    }
        

    // Draw cells
    for (int row = 0; row < row_count; row++) {
        for (int col = 0; col < col_count; col++) {
            DrawRectangle(
                (int)col_edges[col],
                (int)row_edges[row],
                (int)(col_edges[col+1] - col_edges[col]),
                (int)(row_edges[row+1] - row_edges[row]),
                MixColors(row_colors_a[row], row_colors_b[row],
                        column_colors_a[col], column_colors_b[col], row, col)
            );
        }
    }



    // Draw dividers
    for (int i = 0; i < (int)v_dividers.size(); i++) {
        float x = canvas_x + v_dividers[i] * canvas_width;
        Color c = (draggedV == i) ? LIGHTGRAY : (hoveredV == i) ? GRAY : BLACK;
        DrawLineEx({x, canvas_y}, {x, canvas_y + canvas_height}, 2, c);
    }
    for (int i = 0; i < (int)h_dividers.size(); i++) {
        float y = canvas_y + h_dividers[i] * canvas_height;
        Color c = (draggedH == i) ? LIGHTGRAY : (hoveredH == i) ? GRAY : BLACK;
        DrawLineEx({canvas_x, y}, {canvas_x + canvas_width, y}, 2, c);
    }

    DrawRectangleLines(canvas_x, canvas_y, canvas_width, canvas_height, BLACK);

    // Cursor
    if (draggedV != -1 || hoveredV != -1) SetMouseCursor(MOUSE_CURSOR_RESIZE_EW);
    else if (draggedH != -1 || hoveredH != -1) SetMouseCursor(MOUSE_CURSOR_RESIZE_NS);
    else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
}



Color App::ParseColor(const char* hex) {
    int r=255,g=255,b=255;
    if (strlen(hex) >= 6) sscanf(hex, "%2x%2x%2x", &r,&g,&b);
    return {(unsigned char)r, (unsigned char)g, (unsigned char)b, 255};
}



Color App::MixColors(Color weft_a, Color weft_b, Color warp_a, Color warp_b, int row, int col) {
    // Checkerboard determines which layer is on top
    bool layer_a_on_top = (row + col) % 2 == 0;

    // Pick the warp and weft colors for this cell based on which layer faces up
    Color warp  = layer_a_on_top ? warp_a  : warp_b;
    Color weft  = layer_a_on_top ? weft_a  : weft_b;

    return {
        (unsigned char)(warp.r * 0.5f + weft.r * 0.5f),
        (unsigned char)(warp.g * 0.5f + weft.g * 0.5f),
        (unsigned char)(warp.b * 0.5f + weft.b * 0.5f),
        255
    };
}



void App::HandleCopyPaste(char* buf, int max_len) {
    bool modifier = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_LEFT_SUPER);

    if (modifier && IsKeyPressed(KEY_V)) {
        const char* clipboard = GetClipboardText();
        if (clipboard) {
            const char* src = (clipboard[0] == '#') ? clipboard + 1 : clipboard;
            strncpy(buf, src, max_len - 1);
            buf[max_len - 1] = '\0';
        }
    }

    if (modifier && IsKeyPressed(KEY_C)) {
        SetClipboardText(buf);
    }
}