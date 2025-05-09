//
// Created by pknadimp on 5/9/25.
//

#include "Map.h"

namespace shooter {
    static void draw_floor(float x, float z) {
        Vector3 position = {x, 0.0f, z};
        DrawCube(position, TILE_SIZE, 0.0f, TILE_SIZE, BLUE);
    }

    static void draw_left_wall(float x, float z) {
        Vector3 position = {x, CEILING_HEIGHT / 2.0f, z - TILE_SIZE / 2.0f};
        DrawCube(position, TILE_SIZE, CEILING_HEIGHT, 0.0f, GREEN);
    }

    static void draw_right_wall(float x, float z) {
        Vector3 position = {x, CEILING_HEIGHT / 2.0f, z + TILE_SIZE / 2.0f};
        DrawCube(position, TILE_SIZE, CEILING_HEIGHT, 0.0f, GREEN);
    }

    static void draw_front_wall(float x, float z) {
        Vector3 position = {x + TILE_SIZE / 2, CEILING_HEIGHT / 2.0f, z};
        DrawCube(position, 0.0f, CEILING_HEIGHT, TILE_SIZE, PURPLE);
    }

    static void draw_back_wall(float x, float z) {
        Vector3 position = {x - TILE_SIZE / 2, CEILING_HEIGHT / 2.0f, z};
        DrawCube(position, 0.0f, CEILING_HEIGHT, TILE_SIZE, PURPLE);
    }

    static void draw_walls(std::string_view tile, float x, float z) {
        for (auto &wall: tile) {
            if (wall == LEFT_WALL) {
                draw_left_wall(x, z);
            }
            if (wall == RIGHT_WALL) {
                draw_right_wall(x, z);
            }
            if (wall == FRONT_WALL) {
                draw_front_wall(x, z);
            }
            if (wall == BACK_WALL) {
                draw_back_wall(x, z);
            }
        }
    }

    void draw_map(const Map &map) {
        float center_x = ROWS / 2.0f;
        float center_z = COLS / 2.0f;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                float x = (static_cast<float>(i) - center_x) * TILE_SIZE / 2;
                float z = (static_cast<float>(j) - center_z) * TILE_SIZE / 2;

                std::string_view tile = map[i][j];

                draw_floor(x, z);
                draw_walls(tile, x, z);
            }
        }
    }
}
