//
// Created by pknadimp on 5/9/25.
//

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

#include "Core/Camera.h"

namespace shooter {
    constexpr float TILE_SIZE = 10.0f;
    constexpr float WALL_HEIGHT = 5.0f;
    constexpr float WALL_THICKNESS = 0.1f;

    constexpr int ROWS = 5;
    constexpr int COLS = 5;

    enum class WALL_ORIENTATION {
        FLOOR,
        LEFT_WALL,
        RIGHT_WALL,
        BACK_WALL,
        FRONT_WALL,
    };

    // Position, Orientation,
    struct Wall {
        Vector3 center;
        WALL_ORIENTATION orientation;
    };

    using Map = std::vector<Wall>;

    constexpr char EMPTY_TILE = '.';
    constexpr char LEFT_WALL = '[';
    constexpr char RIGHT_WALL = ']';
    constexpr char BACK_WALL = '-';
    constexpr char FRONT_WALL = '_';

    // initialize the map with this
    static std::string default_map[ROWS][COLS] = {
        {"[-", "-", "-", "-", "-]"},
        {"[", ".", ".", "[-", "-]"},
        {"[", ".", ".", ".", "]"},
        {"[", ".", ".", ".", "]"},
        {"[_", "_", "_", "_", "_]"},
    };

    static void draw_floor(Vector3 center);

    static void draw_left_wall(Vector3 center);

    static void draw_right_wall(Vector3 center);

    static void draw_back_wall(Vector3 center);

    static void draw_front_wall(Vector3 center);

    static void draw_wall(Wall wall);
    
    Map load_map(std::string tiles[ROWS][COLS]);

    void draw_map(const Map &map);
} // shooter

#endif //MAP_H
