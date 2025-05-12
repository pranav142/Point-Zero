//
// Created by pknadimp on 4/25/25.
//

#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "Directions.h"
#include "raylib.h"
#include "raymath.h"

namespace utils {
    constexpr float MAX_PITCH_RAD = DEG2RAD * 89.0f;

    inline void rotate_yaw(Transform &transform, const float yaw_rad) {
        const Quaternion q_yaw = QuaternionFromAxisAngle(UP, yaw_rad);
        transform.rotation = QuaternionMultiply(q_yaw, transform.rotation);
        transform.rotation = QuaternionNormalize(transform.rotation);
    }

    inline Vector3 get_forward_vector(const Transform &transform) {
        return Vector3RotateByQuaternion(FORWARD, transform.rotation);
    }

    inline Vector3 get_right_vector(const Transform &transform) {
        return Vector3RotateByQuaternion(RIGHT, transform.rotation);
    }

    inline Vector3 get_up_vector(const Transform &transform) {
        return Vector3RotateByQuaternion(UP, transform.rotation);
    }

    inline Vector3 get_forward_vector_fps(const Transform &transform) {
        Vector3 forward = get_forward_vector(transform);
        forward.y = 0;
        return Vector3Normalize(forward);
    }

    inline float get_current_pitch(const Transform &transform) {
        const Vector3 forward = get_forward_vector(transform);
        return asinf(Clamp(forward.y, -1.0f, 1.0f));
    }

    inline void rotate_pitch(Transform &transform, const float pitch_rad) {
        const float current_pitch = get_current_pitch(transform);
        const float desired_pitch = Clamp(current_pitch + pitch_rad, -MAX_PITCH_RAD, MAX_PITCH_RAD);
        const float allowed_pitch = desired_pitch - current_pitch;

        const Vector3 right = get_right_vector(transform);
        const Quaternion q_pitch = QuaternionFromAxisAngle(right, allowed_pitch);

        transform.rotation = QuaternionMultiply(q_pitch, transform.rotation);
        transform.rotation = QuaternionNormalize(transform.rotation);
    }

    inline void move_forward(Transform &transform, const float displacement) {
        const Vector3 forward = get_forward_vector(transform);
        transform.translation = Vector3Add(transform.translation, forward * displacement);
    }

    inline void move_right(Transform &transform, const float displacement) {
        const Vector3 right = get_right_vector(transform);
        transform.translation = Vector3Add(transform.translation, right * displacement);
    }

    inline void move_up(Transform &transform, const float displacement) {
        transform.translation = Vector3Add(transform.translation, UP * displacement);
    }

    inline void move_forward_fps(Transform &transform, const float displacement) {
        Vector3 forward = get_forward_vector_fps(transform);
        transform.translation = Vector3Add(transform.translation, forward * displacement);
    }
}

#endif
