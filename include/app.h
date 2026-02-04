#pragma once

class App {
private:
    struct UserData {
        char name[64];
        char email[64];

        UserData() {
            name[0] = '\0';
            email[0] = '\0';
        }
    };

    UserData userData;
    bool nameEdit = false;
    bool emailEdit = false;

    enum class AppScreen {
        Form,
        Main
    };

    AppScreen screen = AppScreen::Form;

public:
    void init();
    void update();
    void draw();
    void shutdown();
    void drawFormScreen();
    void drawMainScreen();
};

