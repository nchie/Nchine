//
// Created by aejt on 11/1/17.
//

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Nchine {

    Camera::Camera() {

    }

    Camera::Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up) {

    }

    void Camera::set_perspective(float fov, float aspect, float near, float far) {
        m_perspective = true;
        m_projection = glm::perspective(fov, aspect, near, far);
        m_fov    = fov;
        m_aspect = aspect;
        m_near   = near;
        m_far    = far;
    }

    void Camera::update_view() {
        m_forward.x = static_cast<float>(cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));
        m_forward.y = static_cast<float>(sin(glm::radians(m_pitch)));
        m_forward.z = static_cast<float>(sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch)));

        m_right = glm::normalize(glm::cross(m_forward, m_world_up));
        m_forward = glm::normalize(m_forward);
        m_up = glm::normalize(glm::cross(m_right, m_forward));

        m_view = glm::lookAt(m_position, m_position + m_forward, m_world_up);
    }

    void Camera::move_forward(float amount) {
        m_position += m_forward * amount;
    }

    void Camera::move_backward(float amount) {
        m_position -= m_forward * amount;
    }

    void Camera::move_left(float amount) {
        m_position -= m_right * amount;
    }

    void Camera::move_right(float amount) {
        m_position += m_right * amount;
    }

    void Camera::move_up(float amount) {
        m_position += m_up * amount;
    }




    const glm::mat4 &Camera::get_projection() const {
        return m_projection;
    }

    const glm::mat4 &Camera::get_view() const {
        return m_view;
    }

    const glm::vec3 &Camera::get_position() const {
        return m_position;
    }

    void Camera::set_projection(const glm::mat4 &projection) {
        m_projection = projection;
    }

    void Camera::set_view(const glm::mat4 &view) {
        m_view = view;
    }

    void Camera::set_position(const glm::vec3 &position) {
        m_position = position;
    }

}