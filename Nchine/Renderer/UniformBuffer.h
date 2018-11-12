//
// Created by aejt on 11/1/17.
//

#pragma once

#include <glad/glad.h>

namespace Nchine
{
    template <class T>
    class UniformBuffer : public T
    {

    private:
        unsigned int m_id = 0;

    public:
        UniformBuffer()
        {
            glGenBuffers(1, &m_id);
            glBindBuffer(GL_UNIFORM_BUFFER, m_id);
            glBufferData(GL_UNIFORM_BUFFER, sizeof(T), nullptr, GL_STREAM_DRAW);
            glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_id);
        }

        ~UniformBuffer()
        {
            // If id is a valid buffer id, delete it (if it isn't, it has been moved)
            if(m_id != 0) {
                glDeleteBuffers(1, &m_id);
                m_id = 0;
            }
        }

        UniformBuffer(UniformBuffer &&other) noexcept {
            //TODO: Check for self-assignment

            this->m_id = other.m_id;;

            // Invalidate old texture's id
            other.m_id = 0;
        }

        UniformBuffer& operator=(UniformBuffer &&other) noexcept {
            //TODO: Check for self-assignment

            this->m_id = other.m_id;;

            // Invalidate old texture's id
            other.m_id = 0;

            return *this;
        }

        void update()
        {
            glBindBuffer(GL_UNIFORM_BUFFER, m_id);
            glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(T), this);
        }

        unsigned int get_id() { return m_id; }


    };
}


