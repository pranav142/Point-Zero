//
// Created by pknadimp on 4/14/25.
//

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
    m_registry.add_component<Transform>(m_debug, default_transform);

    m_registry.add_component<components::DebugController>(m_debug, components::DebugController{5.0f, 0.2f});
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
    Camera camera = m_debug_camera;
    m_renderer.begin_frame();
    m_renderer.render_player(m_registry.get_component<Transform>(m_player).translation, camera);
    m_renderer.end_frame();
}

void shooter::Game::toggle_debug() {
    debug = !debug;
}

void shooter::Game::handle_input() {
    if (IsKeyPressed('Z')) {
        m_debug_camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    }

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
        auto &transform = m_registry.get_component<Transform>(m_debug);
        const auto &[speed, sensitivity] = m_registry.get_component<components::DebugController>(m_debug);

        const auto [dx, dy] = GetMouseDelta();

        const float d_pitch = utils::pitch_delta_rad(-dy, sensitivity);
        const float d_yaw = utils::yaw_delta_rad(-dx, sensitivity);

        utils::rotate_yaw(transform, d_yaw);
        utils::rotate_pitch(transform, d_pitch);

        const float displacement = speed * m_delta_time;
        if (IsKeyDown(KEY_W))
            utils::move_forward(transform, displacement);
        if (IsKeyDown(KEY_A))
            utils::move_right(transform, -displacement);
        if (IsKeyDown(KEY_S))
            utils::move_forward(transform, -displacement);
        if (IsKeyDown(KEY_D))
            utils::move_right(transform, displacement);
        if (IsKeyDown(KEY_SPACE))
            utils::move_up(transform, displacement);
        if (IsKeyDown(KEY_LEFT_SHIFT))
            utils::move_up(transform, -displacement);

        m_debug_camera.position = transform.translation;
        m_debug_camera.target = Vector3Add(transform.translation, utils::get_forward_vector(transform));
        m_debug_camera.up = utils::get_up_vector(transform);
        m_debug_camera.fovy = 45.0f;
        m_debug_camera.projection = CAMERA_PERSPECTIVE;
    }
}
