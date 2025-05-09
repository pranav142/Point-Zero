//
// Created by pknadimp on 5/8/25.
//

#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include "raymath.h"

namespace shooter {
    struct Player {
        Transform transform = Transform(Vector3(0.0f, 0.0f, 0.0f), QuaternionIdentity(), Vector3(1.0f, 1.0f, 1.0f));
        float speed = 5.0f;
        float sensitivity = 0.2f;
    };

    void move_player_forward(Player& player, float delta_time);

    void move_player_backward(Player& player, float delta_time);

    void move_player_left(Player& player, float delta_time);

    void move_player_right(Player& player, float delta_time);

    void update_player(Player& player, float delta_time);
}


#endif //PLAYER_H
