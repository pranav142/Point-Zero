//
// Created by pknadimp on 4/14/25.
//

#ifndef RENDERER_H
#define RENDERER_H
#include "raylib.h"


namespace shooter {
    class Renderer {
    public:
        void begin_frame();

        void render_player(const Vector3 &position, const Camera3D &camera);

        void end_frame();
    };
}

#endif //RENDERER_H
