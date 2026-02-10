#pragma once

class App {
private:
    struct UserData {
        int width = 1;
        int height = 1;
    };

    UserData user_data;

    bool is_editing_width = false;
    bool is_editing_height = false;

    enum class screen {
        form,
        main
    };

    screen app_screen = screen::form;

public:
    void Init();
    void Draw();
    void Shutdown();

private:
    void DrawFormScreen();
    void DrawMainScreen();
};

