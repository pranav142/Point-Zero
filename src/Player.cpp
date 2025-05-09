//
// Created by pknadimp on 5/8/25.
//

#include "Player.h"

#include "Utils/Input.h"
#include "Utils/Movement.h"

namespace shooter {
    void move_player_forward(Player &player, float delta_time) {
        float displacement = delta_time * player.speed;
        utils::move_forward(player.transform, displacement);
    }

    void move_player_backward(Player &player, float delta_time) {
        float displacement = delta_time * player.speed;
        utils::move_forward(player.transform, -displacement);
    }

    void move_player_left(Player &player, float delta_time) {
        float displacement = delta_time * player.speed;
        utils::move_right(player.transform, -displacement);
    }

    void move_player_right(Player &player, float delta_time) {
        float displacement = delta_time * player.speed;
        utils::move_right(player.transform, displacement);
    }

    void yaw_player(Player &player, float dx) {
        const float d_yaw = utils::yaw_delta_rad(-dx, player.sensitivity);
        utils::rotate_yaw(player.transform, d_yaw);
    }

    void update_player(Player &player, float delta_time) {
        const auto [dx, dy] = GetMouseDelta();

        yaw_player(player, dx);

        if (IsKeyDown(KEY_W))
            move_player_forward(player, delta_time);
        if (IsKeyDown(KEY_A))
            move_player_left(player, delta_time);
        if (IsKeyDown(KEY_S))
            move_player_backward(player, delta_time);
        if (IsKeyDown(KEY_D))
            move_player_right(player, delta_time);
    }
}
