//
// Created by pknadimp on 5/9/25.
//

#include "HUD.h"

#include "raylib.h"

namespace shooter {
    void draw_crosshair(int screen_width, int screen_height) {
        constexpr float CROSSHAIR_LENGTH = 14.0f;
        constexpr float CROSSHAIR_THICKNESS = 2.0f;
        DrawRectangle(screen_width / 2 + CROSSHAIR_THICKNESS / 2.0f, screen_height / 2 + CROSSHAIR_LENGTH / 2.0f, 14.0f, 2.0f, BLACK);
        DrawRectangle(screen_width / 2 + CROSSHAIR_LENGTH / 2.0f, screen_height / 2.0 + CROSSHAIR_THICKNESS / 2.0f, 2.0f, 14.0f, BLACK);
    }

    void draw_HUD(int screen_width, int screen_height) {
        draw_crosshair(screen_width, screen_height);
    }
} // shooter