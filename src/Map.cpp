//
// Created by pknadimp on 5/9/25.
//

#include "Map.h"

#include <iostream>
#include <Utils/BoundingBox.h>

namespace shooter {
    Wall create_wall(Vector3 center, WallOrientation orientation) {
        Wall wall;
        wall.center = center;
        wall.orientation = orientation;
        wall.bounding_box = calculate_bounding_box(wall);
        wall.model = LoadModelFromMesh(generate_wall_mesh(wall));
        return wall;
    }

    void draw_wall(const Wall &wall) {
        Color color = get_wall_color(wall);
        DrawModel(wall.model, wall.center, 1.0f, color);
    }

    void draw_wall_bounding_box(const Wall &wall) {
        Vector3 dimensions = get_wall_dimensions(wall);
        DrawCubeWires(wall.center, dimensions.x, dimensions.y, dimensions.z, RED);
    }

    static BoundingBox calculate_bounding_box(const Wall &wall) {
        Vector3 dimensions = get_wall_dimensions(wall);
        return utils::create_bounding_box(wall.center, dimensions);
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

    Mesh generate_wall_mesh(const Wall &wall) {
        Vector3 dims = get_wall_dimensions(wall);
        return GenMeshCube(dims.x, dims.y, dims.z);
    }

    Map load_map(std::string tiles[ROWS][COLS]) {
        Map map;
        float center_x = ROWS / 2.0f;
        float center_z = COLS / 2.0f;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                float x = (static_cast<float>(i) - center_x) * TILE_SIZE;
                float z = (static_cast<float>(j) - center_z) * TILE_SIZE;

                Wall floor = create_wall({x, 0.0f, z}, WallOrientation::FLOOR);
                map.push_back(floor);

                for (auto &tile: tiles[i][j]) {
                    if (tile == LEFT_WALL) {
                        Vector3 center = {x, WALL_HEIGHT / 2.0f, z - TILE_SIZE / 2.0f};
                        Wall wall = create_wall(center, WallOrientation::LEFT_WALL);
                        map.push_back(wall);
                    }

                    if (tile == RIGHT_WALL) {
                        Vector3 center = {x, WALL_HEIGHT / 2.0f, z + TILE_SIZE / 2.0f};
                        Wall wall = create_wall(center, WallOrientation::RIGHT_WALL);
                        map.push_back(wall);
                    }

                    if (tile == FRONT_WALL) {
                        Vector3 center = {x + TILE_SIZE / 2, WALL_HEIGHT / 2.0f, z};
                        Wall wall = create_wall(center, WallOrientation::FRONT_WALL);
                        map.push_back(wall);
                    }

                    if (tile == BACK_WALL) {
                        Vector3 center = {x - TILE_SIZE / 2, WALL_HEIGHT / 2.0f, z};
                        Wall wall = create_wall(center, WallOrientation::BACK_WALL);
                        map.push_back(wall);
                    }
                }
            }
        }

        return map;
    }

    void unload_map(Map &map) {
        for (auto &wall : map) {
            UnloadModel(wall.model);
        }
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

    WallCollision check_collision_map(Map &map, const BoundingBox &bounding_box) {
        for (auto &wall: map) {
            core::BBOXCollision collision = core::check_collision_boxes(wall.bounding_box, bounding_box);
            if (collision.collided) {
                WallCollision wall_collision{};
                wall_collision.wall = &wall;
                wall_collision.collision = collision;
                return wall_collision;
            }
        }
        return WallCollision{};
    }
}
