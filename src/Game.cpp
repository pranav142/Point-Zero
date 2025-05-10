#include "Game.h"

#include "HUD.h"
#include "Utils/Input.h"
#include "Map.h"

void shooter::Game::init() {
    InitWindow(m_width, m_height, "SHOOTER");

    m_debug_camera.set_position(Vector3(5.0f, 5.0f, 0.0f));
    DisableCursor();

    SetTargetFPS(144);
}

void shooter::Game::run() {
    while (!WindowShouldClose()) {
        m_delta_time = GetFrameTime();
        handle_input();
        update();
        render();
    }

    CloseWindow();
}

void shooter::Game::render() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    Camera camera = get_player_raylib_cam(m_player);
    if (m_mode == GameMode::DEBUG) {
        camera = m_debug_camera.get_raylib_cam();
    }

    BeginMode3D(camera);

    draw_player(m_player);
    draw_map(m_map);

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
    if (IsKeyPressed('T')) {
        toggle_debug();
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
        update_player(m_player, m_delta_time);
    }
}
