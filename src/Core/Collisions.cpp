//
// Created by pknadimp on 5/12/25.
//

#include "Collisions.h"

#include "raymath.h"
#include "Utils/BoundingBox.h"

namespace core {
    BBOXCollision check_collision_boxes(const BoundingBox &box1, const BoundingBox &box2) {
        if (!CheckCollisionBoxes(box1, box2)) {
            return BBOXCollision{
                .collided = false,
            };
        }

        BBOXCollision collision{};
        collision.collided = true;

        Vector3 box1_center = utils::get_bounding_box_center(box1);
        Vector3 box2_center = utils::get_bounding_box_center(box2);

        Vector3 box1_dims = utils::get_bounding_box_dimensions(box1);
        Vector3 box2_dims = utils::get_bounding_box_dimensions(box2);

        Vector3 delta = Vector3Subtract(box1_center, box2_center);

        float overlap_x = box1_dims.x - box2_dims.x - abs(delta.x);
        float overlap_y = box1_dims.y - box2_dims.y - abs(delta.y);
        float overlap_z = box1_dims.z - box2_dims.z - abs(delta.z);

        if (overlap_x < overlap_y && overlap_x < overlap_z) {
            collision.minimum_translation_vector = { (delta.x > 0 ? overlap_x : -overlap_x), 0, 0 };
        } else if (overlap_y < overlap_z) {
            collision.minimum_translation_vector = { 0, (delta.y > 0 ? overlap_y : -overlap_y), 0 };
        } else {
            collision.minimum_translation_vector = { 0, 0, (delta.z > 0 ? overlap_z : -overlap_z) };
        }

        return collision;
    }
} // core
