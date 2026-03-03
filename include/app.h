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

    std::vector<Color> column_colors;
    std::vector<Color> row_colors;
    std::vector<std::array<char,8>> column_color_inputs; // 6 chars + null terminator
    std::vector<std::array<char,8>> row_color_inputs;

    int active_column_input = -1;
    int active_row_input = -1;

public:
    void Draw();

private:
    void DrawFormScreen();
    void DrawMainScreen();
    void DrawLeftColumn();
    void DrawGrid();

    Color ParseColor(const char* hex);
    Color MixColors(Color a, Color b);
};

