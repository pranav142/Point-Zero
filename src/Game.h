//
// Created by pknadimp on 4/14/25.
//

#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include "raymath.h"
#include "Renderer.h"
#include "ECS/Registry.h"

namespace shooter {
    struct Rotation {
        float pitch = 0.0f;
        float yaw = 0.0f;
        float roll = 0.0f;
    };
    struct Transform {
        Vector3 position = { 0.0f, 0.0f, 0.0f };
        Rotation rotation = { 0.0f, 0.0f, 0.0f };
    };

    struct DebugController {
        float speed = 0.0f;
        float sensitivity = 0.0f;
    };

    class Game {
    public:
        Game(int width, int height) : m_width(width), m_height(height) {
            m_player = m_registry.create();
            m_debug = m_registry.create();
        };

        void init();

        void run();

        void handle_input();

        void update();

        void render();

        void toggle_debug();

    private:
        int m_width = 0, m_height = 0;

        Renderer m_renderer = Renderer();
        Camera m_debug_camera = Camera();
        ECS::Registry m_registry = ECS::Registry();

        ECS::Entity m_player;
        ECS::Entity m_debug;

        bool debug = false;
        float m_delta_time = 0.0f;
    };
}


#endif //GAME_H
