//
// Created by aejt on 11/1/17.
//

#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Enchine {

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
        m_far = far;
    }

    void Camera::update_view() {

        m_view = glm::lookAt(m_position, m_position + m_forward, m_up);
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


    void Camera::adjust_yaw_pitch(float yaw, float pitch)
    {
        m_forward.x += cos(glm::radians(yaw)) * cos(glm::radians(pitch))*0.001;
        m_forward.y += sin(glm::radians(pitch));
        m_forward.z += sin(glm::radians(yaw)) * cos(glm::radians(pitch))*0.0001;
        m_forward = glm::normalize(m_forward);
    }

    void Camera::adjust_yaw(float amount) {

    }

    void Camera::adjust_pitch(float amount) {

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