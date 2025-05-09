//
// Created by pknadimp on 4/14/25.
//

#ifndef GAME_H
#define GAME_H

#include "Core/Camera.h"
#include "Renderer.h"
#include "Player.h"

namespace shooter {
    enum class GameMode {
        PLAY,
        DEBUG,
    };

    class Game {
    public:
        Game(int width, int height) : m_width(width), m_height(height) {
            // m_player = m_registry.create();
            // m_debug = m_registry.create();
        };

        void init();

        void run();

        void handle_input();

        void update_debug_camera();

        void update();

        void render();

        void toggle_debug();

    private:
        int m_width = 0, m_height = 0;

        Renderer m_renderer = Renderer();
        core::Camera m_debug_camera = core::Camera();
        // ECS::Registry m_registry = ECS::Registry();
        shooter::Player m_player;
        // ECS::Entity m_player;

        GameMode m_mode = GameMode::PLAY;
        float m_delta_time = 0.0f;
    };
}


#endif //GAME_H
