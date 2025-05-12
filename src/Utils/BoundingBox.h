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

    inline Vector3 get_bounding_box_center(const BoundingBox& box) {
        return Vector3Scale(Vector3Add(box.max, box.min), 0.5f);
    }

    inline Vector3 get_bounding_box_dimensions(const BoundingBox& box) {
        return Vector3Subtract(box.max, box.min);
    }
}

#endif //BOUNDINGBOX_H
