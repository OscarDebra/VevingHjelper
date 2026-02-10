#include "../include/config.h"
#include <raylib.h>

namespace config {
    Color background_color = {210, 210, 210, 255};
    int screen_width = 1920; // redundant, but don't know how to remove it, screen is maximized in main.cpp, so it will be overridden anyway
    int screen_height = 1080;
}
