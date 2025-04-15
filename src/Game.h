//
// Created by pknadimp on 4/14/25.
//

#ifndef GAME_H
#define GAME_H
#include "Renderer.h"


namespace shooter {
    class Game {
    public:
        Game(int width, int height) : m_width(width), m_height(height) {
        };

        void init();

        void run();

        void render();

        void handle_input();
    private:
        int m_width = 0, m_height = 0;
        Renderer m_renderer = Renderer();
        Camera m_camera = Camera();
        Vector3 m_player_position = Vector3(0, 0, 0);
    };
}


#endif //GAME_H
