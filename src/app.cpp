#include "app.h"
#include <raylib.h>
#include "../external/raygui/raygui.h"
#include "config.h"


void App::init() {
    // initialize app state
}

void App::update() {
}

void App::draw() {
    ClearBackground(config::background_color);

    if (screen == AppScreen::Form) {
        drawFormScreen();
    }
    else if (screen == AppScreen::Main) {
        drawMainScreen();
    }
}

void App::drawFormScreen() {
    DrawText("Enter your info", 20, 20, 20, DARKGRAY);

    GuiLabel({20, 70, 80, 24}, "Name:");
    if (GuiTextBox({110, 70, 200, 24}, userData.name, 64, nameEdit))
        nameEdit = !nameEdit;

    GuiLabel({20, 110, 80, 24}, "Email:");
    if (GuiTextBox({110, 110, 200, 24}, userData.email, 64, emailEdit))
        emailEdit = !emailEdit;

    if (GuiButton({110, 160, 200, 30}, "Confirm")) {
        // collecting data
        TraceLog(LOG_INFO, "Name: %s", userData.name);
        TraceLog(LOG_INFO, "Email: %s", userData.email);

        screen = AppScreen::Main;
    }
}

void App::drawMainScreen() {
    DrawText("Data received!", 20, 80, 24, DARKGREEN);

    DrawText(TextFormat("Name: %s", userData.name), 20, 130, 20, DARKGRAY);
    DrawText(TextFormat("Email: %s", userData.email), 20, 160, 20, DARKGRAY);
}

void App::shutdown() {
    // cleanup if needed
}