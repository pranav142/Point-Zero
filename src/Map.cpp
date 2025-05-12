//
// Created by pknadimp on 5/9/25.
//

#include "Map.h"

#include <iostream>
#include <Utils/BoundingBox.h>

namespace shooter {
    void draw_wall(const Wall &wall) {
        Vector3 dimensions = get_wall_dimensions(wall);
        Color color = get_wall_color(wall);
        DrawCube(wall.center, dimensions.x, dimensions.y, dimensions.z, color);
    }

    void draw_wall_bounding_box(const Wall &wall) {
        Vector3 dimensions = get_wall_dimensions(wall);
        DrawCubeWires(wall.center, dimensions.x, dimensions.y, dimensions.z, RED);
    }

    static void add_bounding_box(Wall &wall) {
        Vector3 dimensions = get_wall_dimensions(wall);
        wall.bounding_box = utils::create_bounding_box(wall.center, dimensions);
    }

    Vector3 get_wall_dimensions(const Wall &wall) {
        if (wall.orientation == WallOrientation::FRONT_WALL || wall.orientation == WallOrientation::BACK_WALL) {
            return {WALL_THICKNESS, WALL_HEIGHT, TILE_SIZE};
        }

        if (wall.orientation == WallOrientation::LEFT_WALL || wall.orientation == WallOrientation::RIGHT_WALL) {
            return {TILE_SIZE, WALL_HEIGHT, WALL_THICKNESS};
        }

        if (wall.orientation == WallOrientation::FLOOR) {
            return {TILE_SIZE, WALL_THICKNESS, TILE_SIZE};
        }

        return {0, 0, 0};
    }

    Color get_wall_color(const Wall &wall) {
         if (wall.orientation == WallOrientation::FRONT_WALL || wall.orientation == WallOrientation::BACK_WALL) {
             return GREEN;
        }

        if (wall.orientation == WallOrientation::LEFT_WALL || wall.orientation == WallOrientation::RIGHT_WALL) {
            return PURPLE;
        }

        if (wall.orientation == WallOrientation::FLOOR) {
            return BLUE;
        }

        return BLACK;
    }

    Map load_map(std::string tiles[ROWS][COLS]) {
        Map map;
        float center_x = ROWS / 2.0f;
        float center_z = COLS / 2.0f;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                float x = (static_cast<float>(i) - center_x) * TILE_SIZE;
                float z = (static_cast<float>(j) - center_z) * TILE_SIZE;

                Wall floor = {
                    {x, 0.0f, z},
                    WallOrientation::FLOOR,
                };
                add_bounding_box(floor);
                map.push_back(floor);

                for (auto &tile: tiles[i][j]) {
                    if (tile == LEFT_WALL) {
                        Vector3 center = {x, WALL_HEIGHT / 2.0f, z - TILE_SIZE / 2.0f};
                        Wall wall = {
                            center,
                            WallOrientation::LEFT_WALL,
                        };
                        add_bounding_box(wall);
                        map.push_back(wall);
                    }

                    if (tile == RIGHT_WALL) {
                        Vector3 center = {x, WALL_HEIGHT / 2.0f, z + TILE_SIZE / 2.0f};
                        Wall wall = {
                            center,
                            WallOrientation::RIGHT_WALL,
                        };
                        add_bounding_box(wall);
                        map.push_back(wall);
                    }

                    if (tile == FRONT_WALL) {
                        Vector3 center = {x + TILE_SIZE / 2, WALL_HEIGHT / 2.0f, z};
                        Wall wall = {
                            center,
                            WallOrientation::FRONT_WALL,
                        };
                        add_bounding_box(wall);
                        map.push_back(wall);
                    }

                    if (tile == BACK_WALL) {
                        Vector3 center = {x - TILE_SIZE / 2, WALL_HEIGHT / 2.0f, z};
                        Wall wall = {
                            center,
                            WallOrientation::BACK_WALL,
                        };
                        add_bounding_box(wall);
                        map.push_back(wall);
                    }
                }
            }
        }

        return map;
    }

    void draw_map(const Map &map) {
        for (auto &wall: map) {
            draw_wall(wall);
        }
    }

    void draw_map_collision_mesh(const Map &map) {
        for (auto &wall: map) {
            draw_wall_bounding_box(wall);
        }
    }

    void print_wall(const Wall &wall) {
        std::string orientation = wall_orientation_to_string(wall.orientation);
        std::cout << "Wall; Orientation: " << orientation;
    }

    std::string wall_orientation_to_string(WallOrientation orientation) {
        switch (orientation) {
            case WallOrientation::FLOOR:
                return "FLOOR";
            case WallOrientation::LEFT_WALL:
                return "LEFT_WALL";
            case WallOrientation::RIGHT_WALL:
                return "RIGHT_WALL";
            case WallOrientation::FRONT_WALL:
                return "FRONT_WALL";
            case WallOrientation::BACK_WALL:
                return "BACK_WALL";
            default:
                return "UNKNOWN";
        }
    }

    WallCollisions check_collision_map(Map &map, const BoundingBox &bounding_box) {
        WallCollisions wall_collisions;
        for (auto &wall: map) {
            core::BBOXCollision collision = core::check_collision_boxes(wall.bounding_box, bounding_box);
            if (collision.collided) {
                WallCollision wall_collision{};
                wall_collision.wall = &wall;
                wall_collision.collision = collision;
                wall_collisions.push_back(wall_collision);
            }
        }
        return wall_collisions;
    }
}
