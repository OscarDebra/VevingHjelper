#pragma once
#include <raylib.h>
#include <vector>
#include <array>

class App {
private:
    struct UserData {
        int width = 1;
        int height = 1;

        int columns = 5;
        int rows = 5;
    };

    UserData user_data;

    bool is_editing_width = false;
    bool is_editing_height = false;
    bool is_editing_rows = false;
    bool is_editing_columns = false;

    enum class screen {
        form,
        main
    };

    screen app_screen = screen::form;

    std::vector<float> v_dividers = {0.5f, 0.7f};
    std::vector<float> h_dividers = {0.2f, 0.5f};
    int draggedV = -1;
    int draggedH = -1;

    std::vector<Color> column_colors_a;
    std::vector<Color> row_colors_a;
    std::vector<std::array<char,8>> column_color_inputs_a; // 6 chars + null terminator
    std::vector<std::array<char,8>> row_color_inputs_a;
    int active_column_input_a = -1;
    int active_row_input_a = -1;

    std::vector<Color> column_colors_b;  // bottom swatch colors
    std::vector<Color> row_colors_b;     // right swatch colors
    std::vector<std::array<char, 8>> column_color_inputs_b;
    std::vector<std::array<char, 8>> row_color_inputs_b;
    int active_column_input_b = -1;
    int active_row_input_b = -1;

    bool equalize_columns = false;
    bool equalize_rows = false;

public:
    void Draw();

private:
    void DrawFormScreen();
    void DrawMainScreen();
    void DrawLeftColumn();
    void DrawGrid();

    Color ParseColor(const char* hex);
    Color MixColors(Color weft_a, Color weft_b, Color warp_a, Color warp_b, int row, int col);

    void HandleCopyPaste(char* buf, int max_len);
};

