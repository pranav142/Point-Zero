//
// Created by pknadimp on 5/8/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"
#include "Core/Camera.h"

namespace shooter {
    // Player is a capsule
    //   Radius: Sphere at bottom and top
    //   Body Height: Distance between spheres
    //   Player Height: Total height of player
    constexpr float PLAYER_RADIUS = 0.5f;
    constexpr float BODY_HEIGHT = 1.0f;
    constexpr float PLAYER_HEIGHT = BODY_HEIGHT + PLAYER_RADIUS * 2;

    struct Player {
        Transform transform = Transform(Vector3(0.0f, 0.0f, 0.0f),
                                        // @WTF! Why do we have to set the ROLL instead of pitch?
                                        QuaternionFromEuler(0.0f, 0.0f, 1.0f),
                                        Vector3(1.0f, 1.0f, 1.0f));
        float speed = 5.0f;
        float sensitivity = 0.2f;

        Vector3 camera_offset = Vector3(0.0f, PLAYER_HEIGHT + 0.05f, 0.0f);
    };

    void move_player_forward(Player &player, float delta_time);

    void move_player_backward(Player &player, float delta_time);

    void move_player_left(Player &player, float delta_time);

    void move_player_right(Player &player, float delta_time);

    void yaw_player(Player &player, float dx);

    void pitch_player(Player &player, float dy);

    void update_player(Player &player, float delta_time);

    void draw_player(const Player &player);

    Camera3D get_player_raylib_cam(const Player &player);
}


#endif //PLAYER_H
