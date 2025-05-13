//
// Created by pknadimp on 5/9/25.
//

#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

#include "Core/Camera.h"
#include "Core/Collisions.h"

namespace shooter {
    constexpr float TILE_SIZE = 10.0f;
    constexpr float WALL_HEIGHT = 5.0f;
    constexpr float WALL_THICKNESS = 0.1f;

    constexpr int ROWS = 5;
    constexpr int COLS = 5;

    enum class WallOrientation {
        FLOOR,
        LEFT_WALL,
        RIGHT_WALL,
        BACK_WALL,
        FRONT_WALL,
    };

    struct Wall {
        Vector3 center{};
        WallOrientation orientation;
        BoundingBox bounding_box{};

        // Mesh mesh{};
        Model model{};
    };

    using Map = std::vector<Wall>;

    constexpr char EMPTY_TILE = '.';
    constexpr char LEFT_WALL = '[';
    constexpr char RIGHT_WALL = ']';
    constexpr char BACK_WALL = '-';
    constexpr char FRONT_WALL = '_';

    static std::string default_map[ROWS][COLS] = {
        {"[-", "-", "-", "-", "-]"},
        {"[", ".", ".", "[-", "-]"},
        {"[", ".", ".", ".", "]"},
        {"[", ".", ".", ".", "]"},
        {"[_", "_", "_", "_", "_]"},
    };

    struct WallCollision {
        Wall* wall;
        core::BBOXCollision collision;
    };


    static Wall create_wall(Vector3 center, WallOrientation orientation);

    static void draw_wall(const Wall &wall);

    static void draw_wall_bounding_box(const Wall &wall);

    static BoundingBox calculate_bounding_box(const Wall &wall);

    static Vector3 get_wall_dimensions(const Wall &wall);

    static Color get_wall_color(const Wall &wall);

    static Mesh generate_wall_mesh(const Wall& wall);

    Map load_map(std::string tiles[ROWS][COLS]);

    void unload_map(Map& map);

    void draw_map(const Map &map);

    void draw_map_collision_mesh(const Map &map);

    void print_wall(const Wall &wall);

    std::string wall_orientation_to_string(WallOrientation orientation);

    WallCollision check_collision_map(Map &map, const BoundingBox &bounding_box);
} // shooter

#endif //MAP_H
