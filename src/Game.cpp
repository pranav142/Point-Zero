#include "Game.h"

#include <iostream>
#include <ostream>
#include <signal.h>

#include "HUD.h"
#include "Utils/Input.h"
#include "Map.h"

void shooter::Game::init() {
    InitWindow(m_width, m_height, "SHOOTER");

    m_debug_camera.set_position(Vector3(5.0f, 5.0f, 0.0f));
    m_enemy_player.set_player_position(Vector3(5.0f, 0.0f, 5.0f));
    m_player.set_player_position(Vector3(0.0f, 0.0f, 0.0f));
    DisableCursor();

    SetTargetFPS(144);
}

void shooter::Game::run() {
    while (!WindowShouldClose()) {
        m_delta_time = GetFrameTime();
        // std::cout << 1 / m_delta_time << std::endl;

        handle_input();
        update();
        render();
    }

    CloseWindow();
}

void shooter::Game::spawn_enemy() {
    revive_player(m_enemy_player);
}

void shooter::Game::resolve_player_collisions() {
    WallCollision wall_collision = check_player_collides_with_map(m_map, m_player);
    int count = 0;
    constexpr int MAX_ITERS = 5;
    while (wall_collision.collision.collided && count <= MAX_ITERS) {
        resolve_player_collision(m_player, wall_collision.collision);
        wall_collision = check_player_collides_with_map(m_map, m_player);
        count++;
    };
}

void shooter::Game::render() const {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    Camera camera = get_player_raylib_cam(m_player);
    if (m_mode == GameMode::DEBUG) {
        camera = m_debug_camera.get_raylib_cam();
    }

    BeginMode3D(camera);

    draw_player(m_player);
    draw_player_ray(m_player);

    if (m_enemy_player.state == PlayerState::ALIVE) {
        draw_player(m_enemy_player);
        draw_player_bounding_box(m_enemy_player);
    }

    draw_map(m_map);
    draw_map_collision_mesh(m_map);

    EndMode3D();

    draw_HUD(m_width, m_height);

    EndDrawing();
}

void shooter::Game::toggle_debug() {
    if (m_mode == GameMode::DEBUG) {
        m_mode = GameMode::PLAY;
    } else if (m_mode == GameMode::PLAY) {
        m_mode = GameMode::DEBUG;
    }
}

void shooter::Game::handle_input() {
    if (IsKeyPressed(KEY_T)) {
        toggle_debug();
    }

    if (IsKeyPressed(KEY_R)) {
        spawn_enemy();
    }
}

void shooter::Game::update_debug_camera() {
    const auto [dx, dy] = GetMouseDelta();

    m_debug_camera.rotate_pitch(-dy);
    m_debug_camera.rotate_yaw(dx);

    if (IsKeyDown(KEY_W))
        m_debug_camera.move_forward(m_delta_time);
    if (IsKeyDown(KEY_A))
        m_debug_camera.move_left(m_delta_time);
    if (IsKeyDown(KEY_S))
        m_debug_camera.move_backward(m_delta_time);
    if (IsKeyDown(KEY_D))
        m_debug_camera.move_right(m_delta_time);
    if (IsKeyDown(KEY_SPACE))
        m_debug_camera.move_up(m_delta_time);
    if (IsKeyDown(KEY_LEFT_SHIFT))
        m_debug_camera.move_down(m_delta_time);
}


void shooter::Game::update() {
    if (m_mode == GameMode::DEBUG) {
        update_debug_camera();
    }

    if (m_mode == GameMode::PLAY) {
        update_player(m_player);
        move_player(m_player, m_delta_time);
    }

    resolve_player_collisions();

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && m_enemy_player.state == PlayerState::ALIVE) {
        Ray ray = player_shoot(m_player);
        RayCollision collision = get_ray_collision_player(ray, m_enemy_player);
        if (collision.hit) {
            kill_player(m_enemy_player);
        }
    }
}
