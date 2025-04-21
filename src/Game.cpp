//
// Created by pknadimp on 4/14/25.
//

#include "Game.h"

#include <external/glad.h>
#include <external/miniaudio.h>

#include "raymath.h"

void shooter::Game::init() {
    InitWindow(m_width, m_height, "SHOOTER");

    DisableCursor();

    SetTargetFPS(144);

    m_registry.add_component<Transform>(m_player, Transform{});

    m_registry.add_component<Transform>(m_debug, Transform{.position = {10.0f, 0.0f, 0.0f}});
    m_registry.add_component<DebugController>(m_debug, DebugController{5.0f, 0.4f});
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
    m_renderer.render_player(m_registry.get_component<Transform>(m_player).position, camera);
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
    auto &position = m_registry.get_component<Transform>(m_player);
    if (IsKeyPressed('L') || IsKeyDown('L')) {
        position.position.z -= speed * m_delta_time;
    }
    if (IsKeyPressed('J') || IsKeyDown('J')) {
        position.position.z += speed * m_delta_time;
    }
    if (IsKeyPressed('K') || IsKeyDown('K')) {
        position.position.x -= speed * m_delta_time;
    }
    if (IsKeyPressed('I') || IsKeyDown('I')) {
        position.position.x += speed * m_delta_time;
    }

    if (IsKeyPressed('T')) {
        toggle_debug();
    }
}

void shooter::Game::update() {
    if (debug) {
        Transform& transform = m_registry.get_component<Transform>(m_debug);
        DebugController& controller = m_registry.get_component<DebugController>(m_debug);

        if (IsKeyDown(KEY_W)) transform.position.x -= controller.speed * m_delta_time;
        if (IsKeyDown(KEY_A)) transform.position.z += controller.speed * m_delta_time;
        if (IsKeyDown(KEY_S)) transform.position.x += controller.speed * m_delta_time;
        if (IsKeyDown(KEY_D)) transform.position.z -= controller.speed * m_delta_time;
        if (IsKeyDown(KEY_SPACE)) transform.position.y += controller.speed * m_delta_time;
        if (IsKeyDown(KEY_LEFT_CONTROL)) transform.position.y -= controller.speed * m_delta_time;

        // Handle Rotations - DEBUG CAMERA
        const Vector2 mouse_delta = GetMouseDelta();
        float pitch = mouse_delta.x * controller.sensitivity;
        if (pitch > 89.0f) {
            pitch = 89.0f;
        } else if (pitch < -89.0f) {
            pitch = -89.0f;
        }
        transform.rotation.pitch += pitch;
        transform.rotation.yaw += mouse_delta.y * controller.sensitivity;
        
        // update the target
        m_debug_camera.position = transform.position;
        m_debug_camera.target = Vector3Add(transform.position, {-1.0f, 0.0f, 0.0f});
        m_debug_camera.up = (Vector3){0.0f, 1.0f, 0.0f};
        m_debug_camera.fovy = 45.0f;
        m_debug_camera.projection = CAMERA_PERSPECTIVE;
        // UpdateCamera(&m_debug_camera, CAMERA_FREE);
    }
}
