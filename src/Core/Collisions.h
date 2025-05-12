//
// Created by pknadimp on 5/12/25.
//

#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "raylib.h"

#include <bitset>

namespace core {
   // enum class CollisionDirection : uint8_t {
   //     UP,
   //     DOWN,
   //     LEFT,
   //     RIGHT
   // };

    struct BBOXCollision {
        bool collided;
        Vector3 minimum_translation_vector;
    };

    BBOXCollision check_collision_boxes(const BoundingBox &box1, const BoundingBox &box2);
} // core

#endif //COLLISIONS_H
