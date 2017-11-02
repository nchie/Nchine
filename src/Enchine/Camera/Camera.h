//
// Created by aejt on 11/1/17.
//

#pragma once

#include <glm/glm.hpp>

namespace Enchine {

    class Camera {

    private:
        glm::mat4 m_projection;
        glm::mat4 m_view;

    private:

        glm::vec3 m_position = glm::vec3(0.0f, 0.0f,  0.0f);
        glm::vec3 m_forward  = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 m_up       = glm::vec3(0.0f, 1.0f,  0.0f);
        glm::vec3 m_right    = glm::vec3(1.0f, 0.0f, 0.0f);

        float m_fov;
        float m_aspect;
        float m_near;
        float m_far;
        bool  m_perspective;


    public:
        Camera();
        Camera(glm::vec3 position, glm::vec3 forward, glm::vec3 up);
        void set_perspective(float fov, float aspect, float near, float far);
        void update_view();
        void move_forward(float amount);
        void move_backward(float amount);
        void move_left(float amount);
        void move_right(float amount);
        void adjust_yaw_pitch(float yaw, float pitch);
        void adjust_yaw(float amount);
        void adjust_pitch(float amount);


    public:
        const glm::vec3& get_position() const;
        const glm::mat4& get_view() const;
        const glm::mat4& get_projection() const;

        void set_position(const glm::vec3 &m_position);
        void set_view(const glm::mat4 &m_view);
        void set_projection(const glm::mat4 &m_projection);


    };
}