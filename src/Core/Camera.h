//
// Created by pknadimp on 5/8/25.
//

#ifndef CAMERA_H
#define CAMERA_H

#include "raylib.h"
#include "raymath.h"

namespace core {
    class Camera {
    public:
        explicit Camera(float fov = 45.0f, float sensitivity = 0.2f, float speed = 5.0f)
            : m_fov(fov), m_sensitivity(sensitivity), m_speed(speed) {
        };

        void rotate_yaw(float dx);

        void rotate_pitch(float dy);

        void move_forward(float delta_time);

        void move_backward(float delta_time);

        void move_right(float delta_time);

        void move_left(float delta_time);

        void move_up(float delta_time);

        void move_down(float delta_time);

        void set_position(const Vector3 &position);

        void set_fov(float fov);

        void set_speed(float speed);

        void set_sensitivity(float sensitivity);

        [[nodiscard]] Camera3D get_raylib_cam() const;

    private:
        Transform m_transform = Transform(Vector3(0.0f, 0.0f, 0.0f), QuaternionIdentity(), Vector3(1.0f, 1.0f, 1.0f));

        float m_fov = 0.0f;
        float m_sensitivity = 0.0f;
        float m_speed = 0.0f;
    };
}


#endif //CAMERA_H
