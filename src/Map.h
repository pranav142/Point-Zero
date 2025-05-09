//
// Created by pknadimp on 5/9/25.
//

#ifndef MAP_H
#define MAP_H

#include <string>

#include "Core/Camera.h"

namespace shooter {
    constexpr float TILE_SIZE = 10.0f;
    constexpr float CEILING_HEIGHT = 5.0f;

    constexpr int ROWS = 5;
    constexpr int COLS = 5;

    using Map = std::string[ROWS][COLS];

    constexpr char EMPTY_TILE = '.';
    constexpr char LEFT_WALL = '[';
    constexpr char RIGHT_WALL = ']';
    constexpr char BACK_WALL = '-';
    constexpr char FRONT_WALL = '_';

    static Map default_map = {
        {"[-", "-", "-", "-", "-]"},
        {"[", ".", ".", "[-", "-]"},
        {"[", ".", ".", ".", "]"},
        {"[", ".", ".", ".", "]"},
        {"[_", "_", "_", "_", "_]"},
    };

    static void draw_floor(float x, float z);
    static void draw_left_wall(float x, float z);
    static void draw_right_wall(float x, float z);
    static void draw_front_wall(float x, float z);
    static void draw_back_wall(float x, float z);
    static void draw_walls(std::string_view tile, float x, float z);

    void draw_map(const Map &map);
} // shooter

#endif //MAP_H
