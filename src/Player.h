//
// Created by pknadimp on 5/8/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "Map.h"

#include "raylib.h"
#include "raymath.h"
#include "Core/Collisions.h"

namespace shooter {
    // Player is a capsule
    //   Radius: Sphere at bottom and top
    //   Body Height: Distance between spheres
    //   Player Height: Total height of player
    constexpr float PLAYER_RADIUS = 0.5f;
    constexpr float BODY_HEIGHT = 1.0f;
    constexpr float PLAYER_HEIGHT = BODY_HEIGHT + PLAYER_RADIUS * 2;

    constexpr Vector3 PLAYER_BOUNDING_BOX_SIZE = {2 * PLAYER_RADIUS, PLAYER_HEIGHT, 2 * PLAYER_RADIUS};

    constexpr float PLAYER_SPEED = 5.0f;

    enum class PlayerState {
        DEAD,
        ALIVE
    };

    struct Player {
        Transform transform = Transform(Vector3(0.0f, 0.0f, 0.0f),
                                        QuaternionFromEuler(0.0f, 0.0f, 0.0f),
                                        Vector3(1.0f, 1.0f, 1.0f));
        Vector3 velocity = {0.0f, 0.0f, 0.0f};

        float sensitivity = 0.2f;

        Vector3 camera_offset = Vector3(0.0f, PLAYER_HEIGHT + 0.05f, 0.0f);

        PlayerState state = PlayerState::ALIVE;

        void set_player_position(Vector3 position);

        void set_player_center(Vector3 center);

        [[nodiscard]] Vector3 camera_position() const;

        [[nodiscard]] Vector3 center() const;
    };

    void yaw_player(Player &player, float dx);

    void pitch_player(Player &player, float dy);

    void update_player(Player &player);

    void move_player(Player& player, float delta_time);

    void resolve_player_collision(Player& player, core::BBOXCollision collision);

    void draw_player(const Player &player);

    // @TODO: Remove This when we have more robust collision models
    void draw_collision_mesh(const Player& player);

    void draw_player_bounding_box(const Player& player);

    void draw_player_ray(const Player& player);

    Camera3D get_player_raylib_cam(const Player &player);

    Ray player_shoot(const Player &player);

    void kill_player(Player &player);

    void revive_player(Player &player);

    BoundingBox get_player_bounding_box(const Player& player);

    RayCollision get_ray_collision_player(const Ray &ray, const Player &player);

    WallCollision check_player_collides_with_map(Map& map, const Player& player);
}


#endif //PLAYER_H
