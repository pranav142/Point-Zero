//
// Created by pknadimp on 4/14/25.
//

#include "Game.h"

#include <iterator>

void shooter::Game::init() {
    InitWindow(m_width, m_height, "SHOOTER");

    DisableCursor();

    SetTargetFPS(144);

    m_camera = {0};
    m_camera.position = (Vector3){10.0f, 10.0f, 10.0f};
    m_camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    m_camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    m_camera.fovy = 45.0f;
    m_camera.projection = CAMERA_PERSPECTIVE;
}

void shooter::Game::run() {
    while (!WindowShouldClose()) {
        UpdateCamera(&m_camera, CAMERA_FREE);

        handle_input();

        render();
    }

    CloseWindow();
}

void shooter::Game::render() {
    m_renderer.begin_frame();
    m_renderer.render_player(m_player_position, m_camera);
    m_renderer.end_frame();
}

void shooter::Game::handle_input() {
    if (IsKeyPressed('Z')) m_camera.target = (Vector3){0.0f, 0.0f, 0.0f};
}
