//
// Created by pknadimp on 5/11/25.
//

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "raylib.h"

namespace utils {
    inline BoundingBox create_bounding_box(Vector3 center, Vector3 size) {
        Vector3 minimum = {center.x - size.x/2, center.y - size.y/2, center.z - size.z/2};
        Vector3 maximum = {center.x + size.x/2, center.y + size.y/2, center.z + size.z/2};
        return {minimum, maximum};
    }
}

#endif //BOUNDINGBOX_H
