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
        if (wall.orientation == WALL_ORIENTATION::FRONT_WALL || wall.orientation == WALL_ORIENTATION::BACK_WALL) {
            return {WALL_THICKNESS, WALL_HEIGHT, TILE_SIZE};
        }

        if (wall.orientation == WALL_ORIENTATION::LEFT_WALL || wall.orientation == WALL_ORIENTATION::RIGHT_WALL) {
            return {TILE_SIZE, WALL_HEIGHT, WALL_THICKNESS};
        }

        if (wall.orientation == WALL_ORIENTATION::FLOOR) {
            return {TILE_SIZE, WALL_THICKNESS, TILE_SIZE};
        }

        return {0, 0, 0};
    }

    Color get_wall_color(const Wall &wall) {
         if (wall.orientation == WALL_ORIENTATION::FRONT_WALL || wall.orientation == WALL_ORIENTATION::BACK_WALL) {
             return GREEN;
        }

        if (wall.orientation == WALL_ORIENTATION::LEFT_WALL || wall.orientation == WALL_ORIENTATION::RIGHT_WALL) {
            return PURPLE;
        }

        if (wall.orientation == WALL_ORIENTATION::FLOOR) {
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
                float x = (static_cast<float>(i) - center_x) * TILE_SIZE / 2;
                float z = (static_cast<float>(j) - center_z) * TILE_SIZE / 2;

                Wall floor = {
                    {x, 0.0f, z},
                    WALL_ORIENTATION::FLOOR,
                };
                add_bounding_box(floor);
                map.push_back(floor);

                for (auto &tile: tiles[i][j]) {
                    if (tile == LEFT_WALL) {
                        Vector3 center = {x, WALL_HEIGHT / 2.0f, z - TILE_SIZE / 2.0f};
                        Wall wall = {
                            center,
                            WALL_ORIENTATION::LEFT_WALL,
                        };
                        add_bounding_box(wall);
                        map.push_back(wall);
                    }

                    if (tile == RIGHT_WALL) {
                        Vector3 center = {x, WALL_HEIGHT / 2.0f, z + TILE_SIZE / 2.0f};
                        Wall wall = {
                            center,
                            WALL_ORIENTATION::RIGHT_WALL,
                        };
                        add_bounding_box(wall);
                        map.push_back(wall);
                    }

                    if (tile == FRONT_WALL) {
                        Vector3 center = {x + TILE_SIZE / 2, WALL_HEIGHT / 2.0f, z};
                        Wall wall = {
                            center,
                            WALL_ORIENTATION::FRONT_WALL,
                        };
                        add_bounding_box(wall);
                        map.push_back(wall);
                    }

                    if (tile == BACK_WALL) {
                        Vector3 center = {x - TILE_SIZE / 2, WALL_HEIGHT / 2.0f, z};
                        Wall wall = {
                            center,
                            WALL_ORIENTATION::BACK_WALL,
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
}
