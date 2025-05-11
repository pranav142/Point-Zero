//
// Created by pknadimp on 5/9/25.
//

#include "Map.h"

#include <iostream>
#include <ostream>

namespace shooter {
    void draw_floor(Vector3 center) {
        DrawCube(center, TILE_SIZE, WALL_THICKNESS, TILE_SIZE, BLUE);
    }

    void draw_left_wall(Vector3 center) {
        DrawCube(center, TILE_SIZE, WALL_HEIGHT, WALL_THICKNESS, GREEN);
    }

    void draw_right_wall(Vector3 center) {
        DrawCube(center, TILE_SIZE, WALL_HEIGHT, WALL_THICKNESS, GREEN);
    }

    void draw_back_wall(Vector3 center) {
        DrawCube(center, WALL_THICKNESS, WALL_HEIGHT, TILE_SIZE, PURPLE);
    }

    void draw_front_wall(Vector3 center) {
        DrawCube(center, WALL_THICKNESS, WALL_HEIGHT, TILE_SIZE, PURPLE);
    }

    void draw_wall(Wall wall) {
        switch (wall.orientation) {
            case WALL_ORIENTATION::FLOOR:
                draw_floor(wall.center);
                break;
            case WALL_ORIENTATION::BACK_WALL:
                draw_back_wall(wall.center);
                break;
            case WALL_ORIENTATION::LEFT_WALL:
                draw_left_wall(wall.center);
                break;
            case WALL_ORIENTATION::RIGHT_WALL:
                draw_right_wall(wall.center);
                break;
            case WALL_ORIENTATION::FRONT_WALL:
                draw_front_wall(wall.center);
                break;
            default:
                std::cout << "Wall orientation not supported" << std::endl;
        }
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
                map.push_back(floor);

                for (auto &tile: tiles[i][j]) {
                    if (tile == LEFT_WALL) {
                        Vector3 center = {x, WALL_HEIGHT / 2.0f, z - TILE_SIZE / 2.0f};
                        map.push_back({
                            center,
                            WALL_ORIENTATION::LEFT_WALL,
                        });
                    }

                    if (tile == RIGHT_WALL) {
                        Vector3 center = {x, WALL_HEIGHT / 2.0f, z + TILE_SIZE / 2.0f};
                        map.push_back({
                            center,
                            WALL_ORIENTATION::RIGHT_WALL,
                        });
                    }

                    if (tile == FRONT_WALL) {
                        Vector3 center = {x + TILE_SIZE / 2, WALL_HEIGHT / 2.0f, z};
                        map.push_back({
                            center,
                            WALL_ORIENTATION::FRONT_WALL,
                        });
                    }

                    if (tile == BACK_WALL) {
                        Vector3 center = {x - TILE_SIZE / 2, WALL_HEIGHT / 2.0f, z};
                        map.push_back({
                            center,
                            WALL_ORIENTATION::BACK_WALL,
                        });
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
}
