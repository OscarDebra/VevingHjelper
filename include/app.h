#pragma once

class App {
private:
    struct UserData {
        int width = 1;
        int height = 1;

        int columns = 1;
        int rows = 1;
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

public:
    void Draw();

private:
    void DrawFormScreen();
    void DrawMainScreen();
    void DrawLeftColumn();
};

