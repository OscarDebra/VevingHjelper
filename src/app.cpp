#include "app.h"
#include <raylib.h>
#include "../external/raygui/raygui.h"
#include "config.h"

void App::init() {
    // initialize app state
}

void App::update() {
    // input + logic
}

void App::draw() {
    ClearBackground(config::background_color);

    if (GuiButton({20, 20, 120, 30}, "OK")) {
        // handle click
    }
}

void App::shutdown() {
    // cleanup if needed
}