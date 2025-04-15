//
// Created by pknadimp on 4/14/25.
//

#include "Renderer.h"

#include "raylib.h"

void shooter::Renderer::begin_frame() {
    BeginDrawing();

    ClearBackground(RAYWHITE);
}

void shooter::Renderer::render_player(const Vector3 &position, const Camera3D &camera) {
    constexpr float CUBE_SIZE = 2.0f;
    BeginMode3D(camera);
    DrawCube(position, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, RED);
    DrawCubeWires(position, CUBE_SIZE, CUBE_SIZE, CUBE_SIZE, MAROON);
    EndMode3D();
}

void shooter::Renderer::end_frame() {
    EndDrawing();
}
