//
// Created by pknadimp on 4/25/25.
//

#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"

namespace utils {
    inline float pitch_delta_rad(const float mouse_dy, const float sensitivity) {
        return DEG2RAD * mouse_dy * sensitivity;
    }

    inline float yaw_delta_rad(const float mouse_dx, const float sensitivity) {
        return DEG2RAD * mouse_dx * sensitivity;
    }
}

#endif //INPUT_H
