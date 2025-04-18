//
// Created by pknadimp on 4/14/25.
//

#ifndef GAME_H
#define GAME_H
#include "Renderer.h"
#include "ECS/Registry.h"

namespace shooter {
    struct Position {
        Vector3 position;
    };

    class Game {
    public:
        Game(int width, int height) : m_width(width), m_height(height) {
            m_player = m_registry.create();

            m_registry.add_component<Position>(m_player, {0, 0, 0});
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
        bool debug = false;
    };
}


#endif //GAME_H
