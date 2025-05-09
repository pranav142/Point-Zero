#include "Game.h"

#include <iostream>
#include "Utils/Input.h"
#include "Utils/Movement.h"

#include "Components/DebugController.h"

#include "raymath.h"


void shooter::Game::init() {
    InitWindow(m_width, m_height, "SHOOTER");

    DisableCursor();

    SetTargetFPS(144);

    Transform default_transform {
        .translation = {0.0f, 0.0f, 0.0f },
        .rotation = Quaternion(0.0f, 0.0f, 0.0f, 1.0f),
        .scale = {1.0f, 1.0f, 1.0f},
    };
    m_registry.add_component<Transform>(m_player, default_transform);
    // m_registry.add_component<Transform>(m_debug, default_transform);

    // m_registry.add_component<components::DebugController>(m_debug, components::DebugController{5.0f, 0.2f});
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
    Camera camera = m_debug_camera.get_raylib_cam();
    m_renderer.begin_frame();
    m_renderer.render_player(m_registry.get_component<Transform>(m_player).translation, camera);
    m_renderer.end_frame();
}

void shooter::Game::toggle_debug() {
    debug = !debug;
}

void shooter::Game::handle_input() {
    constexpr float speed = 5.0f;
    // add these to move functions
    auto &position = m_registry.get_component<Transform>(m_player);
    if (IsKeyPressed('L') || IsKeyDown('L')) {
        position.translation.z -= speed * m_delta_time;
    }
    if (IsKeyPressed('J') || IsKeyDown('J')) {
        position.translation.z += speed * m_delta_time;
    }
    if (IsKeyPressed('K') || IsKeyDown('K')) {
        position.translation.x -= speed * m_delta_time;
    }
    if (IsKeyPressed('I') || IsKeyDown('I')) {
        position.translation.x += speed * m_delta_time;
    }

    if (IsKeyPressed('T')) {
        toggle_debug();
    }
}

void shooter::Game::update() {
    if (debug) {
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
            m_debug_camera.move_forward(m_delta_time);
    }
}
