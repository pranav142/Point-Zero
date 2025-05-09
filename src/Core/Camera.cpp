//
// Created by pknadimp on 5/8/25.
//

#include "Camera.h"

#include "Utils/Movement.h"
#include "Utils/Input.h"

namespace core {
    // @Refactor Separate Camera Controller behavior from the Camera Data
    void Camera::rotate_yaw(float dx) {
        const float d_yaw = utils::yaw_delta_rad(-dx, m_sensitivity);
        utils::rotate_yaw(m_transform, d_yaw);
    }

    void Camera::rotate_pitch(float dy) {
        const float d_pitch = utils::pitch_delta_rad(dy, m_sensitivity);
        utils::rotate_pitch(m_transform, d_pitch);
    }

    void Camera::move_forward(float delta_time) {
        float displacement = delta_time * m_speed;
        utils::move_forward(m_transform, displacement);
    }

    void Camera::move_backward(float delta_time) {
        float displacement = delta_time * m_speed;
        utils::move_forward(m_transform, -displacement);
    }

    void Camera::move_right(float delta_time) {
        float displacement = delta_time * m_speed;
        utils::move_right(m_transform, displacement);
    }

    void Camera::move_left(float delta_time) {
        float displacement = delta_time * m_speed;
        utils::move_right(m_transform, -displacement);
    }

    void Camera::move_up(float delta_time) {
        float displacement = delta_time * m_speed;
        utils::move_up(m_transform, displacement);
    }

    void Camera::move_down(float delta_time) {
        float displacement = delta_time * m_speed;
        utils::move_up(m_transform, -displacement);
    }

    void Camera::set_position(const Vector3 &position) {
        m_transform.translation = position;
    }

    void Camera::set_fov(float fov) {
        m_fov = fov;
    }

    void Camera::set_speed(float speed) {
        m_speed = speed;
    }

    void Camera::set_sensitivity(float sensitivity) {
        m_sensitivity = sensitivity;
    }

    Camera3D Camera::get_raylib_cam() const {
        Camera3D camera;
        camera.position = m_transform.translation;
        camera.target = Vector3Add(m_transform.translation, utils::get_forward_vector(m_transform));
        camera.up = utils::get_up_vector(m_transform);
        camera.fovy = m_fov;
        camera.projection = CAMERA_PERSPECTIVE;
        return camera;
    }
}
