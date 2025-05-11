//
// Created by pknadimp on 5/8/25.
//

#include "Player.h"


#include "Utils/Input.h"
#include "Utils/Movement.h"
#include "Utils/BoundingBox.h"

namespace shooter {
    void Player::set_player_position(Vector3 position) {
        transform.translation = position;
    }

    Vector3 Player::camera_position() const {
        return transform.translation + camera_offset;
    }

    Vector3 Player::center() const {
        return Vector3Add(transform.translation, {0.0f, PLAYER_HEIGHT / 2.0f, 0.0f});
    }

    void move_player_forward(Player &player, float delta_time) {
        float displacement = delta_time * player.speed;
        utils::move_forward_fps(player.transform, displacement);
    }

    void move_player_backward(Player &player, float delta_time) {
        float displacement = delta_time * player.speed;
        utils::move_forward_fps(player.transform, -displacement);
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

    void pitch_player(Player &player, float dy) {
        const float d_pitch = utils::pitch_delta_rad(dy, player.sensitivity);
        utils::rotate_pitch(player.transform, d_pitch);
    }

    void update_player(Player &player, float delta_time) {
        const auto [dx, dy] = GetMouseDelta();

        yaw_player(player, dx);
        pitch_player(player, -dy);

        if (IsKeyDown(KEY_W))
            move_player_forward(player, delta_time);
        if (IsKeyDown(KEY_A))
            move_player_left(player, delta_time);
        if (IsKeyDown(KEY_S))
            move_player_backward(player, delta_time);
        if (IsKeyDown(KEY_D))
            move_player_right(player, delta_time);
    }


    void draw_player(const Player &player) {
        Vector3 start_position = Vector3Add(player.transform.translation, Vector3(0.0f, PLAYER_RADIUS - 0.01f, 0.0f));
        Vector3 end_position = Vector3Add(start_position, Vector3(0.0f, BODY_HEIGHT, 0.0f));
        DrawCapsule(start_position, end_position, PLAYER_RADIUS, 50, 50, LIGHTGRAY);
    }

    void draw_player_bounding_box(const Player &player) {
        DrawCubeWires(player.center(), PLAYER_BOUNDING_BOX_SIZE.x, PLAYER_BOUNDING_BOX_SIZE.y, PLAYER_BOUNDING_BOX_SIZE.z, YELLOW);
    }

    Camera3D get_player_raylib_cam(const Player &player) {
        Vector3 translation = player.camera_position();
        Camera3D camera;
        camera.position = translation;
        camera.target = Vector3Add(translation, utils::get_forward_vector(player.transform));
        camera.up = utils::get_up_vector(player.transform);
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;
        return camera;
    }

    Ray player_shoot(const Player &player) {
        Ray ray;
        ray.position = player.camera_position();
        ray.direction = utils::get_forward_vector(player.transform);
        return ray;
    }

    void draw_collision_sphere(const Player &player) {
        DrawSphereWires(player.transform.translation, 3.0f, 5, 5, YELLOW);
    }

    void draw_player_ray(const Player &player) {
        Ray ray = player_shoot(player);
        Vector3 end_position = Vector3Add(ray.position, ray.direction * 5);
        DrawLine3D(ray.position, end_position, RED);
    }

    void kill_player(Player &player) {
        player.state = PlayerState::DEAD;
    }

    void revive_player(Player &player) {
        player.state = PlayerState::ALIVE;
    }

    BoundingBox get_player_bounding_box(const Player &player) {
        return utils::create_bounding_box(player.center(), PLAYER_BOUNDING_BOX_SIZE);
    }

    RayCollision get_ray_collision_player(Ray ray, const Player &player) {
        BoundingBox bounding_box = get_player_bounding_box(player);
        return GetRayCollisionBox(ray, bounding_box);
    }
}
