//
// Created by pknadimp on 4/14/25.
//

#include "Game.h"

void shooter::Game::init() {
    InitWindow(m_width, m_height, "SHOOTER");

    DisableCursor();

    SetTargetFPS(144);

    m_debug_camera = {0};
    m_debug_camera.position = (Vector3){10.0f, 0.0f, 0.0f};
    m_debug_camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    m_debug_camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    m_debug_camera.fovy = 45.0f;
    m_debug_camera.projection = CAMERA_PERSPECTIVE;
}

void shooter::Game::run() {
    while (!WindowShouldClose()) {
        handle_input();

        update();

        render();
    }

    CloseWindow();
}

void shooter::Game::render() {
    Camera3D camera = (debug) ? m_debug_camera : m_debug_camera;
    m_renderer.begin_frame();
    m_renderer.render_player(m_registry.get_component<Position>(m_player).position, camera);
    m_renderer.end_frame();
}

void shooter::Game::toggle_debug() {
    debug = !debug;
}

void shooter::Game::handle_input() {
    if (IsKeyPressed('Z')) {
        m_debug_camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    }
    if (IsKeyPressed('L') || IsKeyDown('L')) {
        auto &position = m_registry.get_component<Position>(m_player);
        position.position.z -= 0.2f;
    }

    if (IsKeyPressed('T')) {
        toggle_debug();
    }
}

void shooter::Game::update() {
    if (debug) {
        UpdateCamera(&m_debug_camera, CAMERA_FREE);
    }
}
