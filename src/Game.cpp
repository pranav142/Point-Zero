//
// Created by pknadimp on 4/14/25.
//

#include "Game.h"

#include <iostream>
#include <external/glad.h>
#include <external/miniaudio.h>

#include "raymath.h"

void shooter::Game::init() {
    InitWindow(m_width, m_height, "SHOOTER");

    DisableCursor();

    SetTargetFPS(144);

    m_registry.add_component<Transform>(m_player, Transform{});

    m_registry.add_component<Transform>(m_debug, Transform{.position = {10.0f, 0.0f, 0.0f}});
    m_registry.add_component<DebugController>(m_debug, DebugController{5.0f, 0.2f});
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
        Transform &transform = m_registry.get_component<Transform>(m_debug);
        DebugController &controller = m_registry.get_component<DebugController>(m_debug);

        // calculate the pitch and yaw
        const Vector2 mouse_delta = GetMouseDelta();
        float pitch = -mouse_delta.y * controller.sensitivity;
        if (pitch > 89.0f) {
            pitch = 89.0f;
        } else if (pitch < -89.0f) {
            pitch = -89.0f;
        }
        transform.rotation.pitch += pitch;
        transform.rotation.yaw += mouse_delta.x * controller.sensitivity;

        // calculate the new direction the camera looks at
        // TODO: This needs to be moved to a separate function
        float x = -cosf(DEG2RAD * transform.rotation.yaw) * cosf(DEG2RAD * transform.rotation.pitch);
        float z = -sinf(DEG2RAD * transform.rotation.yaw) * cosf(DEG2RAD * transform.rotation.pitch);
        float y = sinf(DEG2RAD * transform.rotation.pitch);
        Vector3 direction = Vector3Normalize({x, y, z});

        // update the direction the camera moves
        Vector3 right = Vector3Normalize(Vector3CrossProduct(Vector3(0.0f, 1.0f, 0.0f), direction));
        // TODO: These Need To Be Moved To Seperate Functions
        if (IsKeyDown(KEY_W)) transform.position = Vector3Add(transform.position, direction * controller.speed * m_delta_time);
        if (IsKeyDown(KEY_A)) transform.position = Vector3Add(transform.position, right * controller.speed * m_delta_time);
        if (IsKeyDown(KEY_S)) transform.position = Vector3Subtract(transform.position, direction * controller.speed * m_delta_time);
        if (IsKeyDown(KEY_D)) transform.position = Vector3Subtract(transform.position, right * controller.speed * m_delta_time);
        if (IsKeyDown(KEY_SPACE)) transform.position.y += controller.speed * m_delta_time;
        if (IsKeyDown(KEY_LEFT_SHIFT)) transform.position.y -= controller.speed * m_delta_time;

        // update the rest of the camera
        m_debug_camera.position = transform.position;
        m_debug_camera.target = Vector3Add(transform.position, direction);
        m_debug_camera.up = Vector3CrossProduct(direction, right);
        m_debug_camera.fovy = 45.0f;
        m_debug_camera.projection = CAMERA_PERSPECTIVE;
        // UpdateCamera(&m_debug_camera, CAMERA_FREE);
    }
}
