//
// Created by pknadimp on 4/14/25.
//

#ifndef GAME_H
#define GAME_H

#include "Core/Camera.h"
#include "Player.h"
#include "Map.h"

namespace shooter {
    enum class GameMode {
        PLAY,
        DEBUG,
    };

    class Game {
    public:
        Game(int width, int height) : m_width(width), m_height(height) {
        };

        void init();

        void run();

        void spawn_enemy();

        void handle_input();

        void update_debug_camera();

        void update();

        void render() const;

        void toggle_debug();

    private:
        int m_width = 0, m_height = 0;

        core::Camera m_debug_camera = core::Camera();

        Player m_player;
        Player m_enemy_player;

        GameMode m_mode = GameMode::PLAY;

        Map m_map = load_map(default_map);

        float m_delta_time = 0.0f;
    };
}


#endif //GAME_H
