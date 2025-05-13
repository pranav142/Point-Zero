//
// Created by pknadimp on 5/12/25.
//

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "raylib.h"

#include <bitset>

namespace core {
    struct BBOXCollision {
        bool collided;
        Vector3 minimum_translation_vector;
    };

    //
    // This returns the minimum translation vector needed for box2 to move
    //
    BBOXCollision check_collision_boxes(const BoundingBox &box1, const BoundingBox &box2);
} // core

#endif //COLLISIONS_H
