//
// Created by pknadimp on 5/8/25.
//

#include "Player.h"

#include <iostream>
#include <ostream>


#include "Utils/Input.h"
#include "Utils/Movement.h"
#include "Utils/BoundingBox.h"

namespace shooter {
    void Player::set_player_position(Vector3 position) {
        transform.translation = position;
    }

    void Player::set_player_center(Vector3 center) {
        transform.translation = Vector3Subtract(center, {0.0f, PLAYER_HEIGHT / 2.0f, 0.0f});
    }

    Vector3 Player::camera_position() const {
        return camera_forward_fps() * 0.5f + camera_position_offset + transform.translation;
    }

    Vector3 Player::camera_forward() const {
        return Vector3RotateByQuaternion(utils::get_forward_vector(transform), camera_rotation_offset);
    }

    Vector3 Player::camera_up() const {
        return Vector3RotateByQuaternion(utils::get_up_vector(transform), camera_rotation_offset);
    }

    Vector3 Player::camera_right() const {
        return Vector3RotateByQuaternion(utils::get_right_vector(transform), camera_rotation_offset);
    }

    Vector3 Player::camera_forward_fps() const {
        return Vector3RotateByQuaternion(utils::get_forward_vector_fps(transform), camera_rotation_offset);
    }

    Vector3 Player::center() const {
        return Vector3Add(transform.translation, {0.0f, PLAYER_HEIGHT / 2.0f, 0.0f});
    }

    Player create_player() {
        Player player;
        player.model = LoadModel("models/Character_Soldier.gltf");
        return player;
    }

    void yaw_player(Player &player, float dx) {
        const float d_yaw = utils::yaw_delta_rad(-dx, player.sensitivity);
        utils::rotate_yaw(player.transform, d_yaw);
    }

    void pitch_player(Player &player, float dy) {
        const float d_pitch = utils::pitch_delta_rad(dy, player.sensitivity);
        utils::rotate_pitch(player.transform, d_pitch);
    }

    void update_player(Player &player) {
        const auto [dx, dy] = GetMouseDelta();

        yaw_player(player, dx);
        pitch_player(player, -dy);

        Vector3 input_direction = {0.0f, 0.0f, 0.0f};
        if (IsKeyDown(KEY_W))
            input_direction += player.camera_forward_fps();
        if (IsKeyDown(KEY_S))
            input_direction -= player.camera_forward_fps();
        if (IsKeyDown(KEY_A))
            input_direction -= player.camera_right();
        else if (IsKeyDown(KEY_D))
            input_direction += player.camera_right();

        if (input_direction != Vector3(0.0f, 0.0f, 0.0f)) {
            input_direction = Vector3Normalize(input_direction);
        }

        player.velocity = input_direction * PLAYER_SPEED;
    }

    void move_player(Player &player, float delta_time) {
        player.transform.translation += player.velocity * delta_time;
    }

    void resolve_player_collision(Player &player, core::BBOXCollision collision) {
        if (!collision.collided) {
            return;
        }

        player.set_player_center(player.center() - collision.minimum_translation_vector);
        if (collision.minimum_translation_vector.x != 0) {
            player.velocity.x = 0;
        }

        if (collision.minimum_translation_vector.y != 0) {
            player.velocity.y = 0;
        }

        if (collision.minimum_translation_vector.z != 0) {
            player.velocity.z = 0;
        }
    }

    void draw_player(const Player &player) {
        // float yaw = utils::get_yaw_from_quaternion(player.transform.rotation);
        Vector3 forward = player.camera_forward_fps();
        float yaw = atan2f(forward.x, forward.z) * RAD2DEG;
        DrawModelEx(player.model, player.transform.translation, utils::UP, yaw,{1.0f, 1.0f, 1.0f}, WHITE);
    }

    void draw_player_bounding_box(const Player &player) {
        DrawCubeWires(player.center(), PLAYER_BOUNDING_BOX_SIZE.x, PLAYER_BOUNDING_BOX_SIZE.y,
                      PLAYER_BOUNDING_BOX_SIZE.z, YELLOW);
    }

    Camera3D get_player_raylib_cam(const Player &player) {
        Vector3 translation = player.camera_position();
        Camera3D camera;
        camera.position = translation;
        camera.target = Vector3Add(translation, player.camera_forward());
        camera.up = player.camera_up();
        camera.fovy = 45.0f;
        camera.projection = CAMERA_PERSPECTIVE;
        return camera;
    }

    Ray player_shoot(const Player &player) {
        Ray ray;
        ray.position = player.camera_position();
        ray.direction = player.camera_forward();
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

    RayCollision get_ray_collision_player(const Ray &ray, const Player &player) {
        BoundingBox bounding_box = get_player_bounding_box(player);
        return GetRayCollisionBox(ray, bounding_box);
    }

    WallCollision check_player_collides_with_map(Map &map, const Player &player) {
        return check_collision_map(map, get_player_bounding_box(player));
    }

    core::BBOXCollision check_player_collides_player(const Player &player, const Player &other) {
        return core::check_collision_boxes(get_player_bounding_box(player), get_player_bounding_box(other));
    }

    void unload_player(const Player &player) {
        UnloadModel(player.model);
    }
}
