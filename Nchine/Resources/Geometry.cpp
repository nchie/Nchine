//
// Created by aejt on 10/22/17.
//

#include "Geometry.h"

#include <glad/glad.h>


namespace Nchine {

    Geometry::Geometry(const std::vector<float> &vertice_data, const std::vector<unsigned int> &indices,
               std::bitset<ATTRIBUTE_COUNT> attributes) : m_attribute_data(attributes) {
        generate(vertice_data, indices);
    }

    Geometry::Geometry(const std::vector<glm::vec3> &vertices, const std::vector<unsigned int> &indices) {
        // Geometry with only vertices
        m_attribute_data = flags::none;

        // Append all vertex positions
        std::vector<float> vertice_data;
        for (int i = 0; i < vertices.size(); ++i) {
            // Append vertex positions
            vertice_data.push_back(vertices[i].x);
            vertice_data.push_back(vertices[i].y);
            vertice_data.push_back(vertices[i].z);
        }

        generate(vertice_data, indices);
    }

    Geometry::Geometry(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uv,
               const std::vector<unsigned int> &indices) {
        // Geometry with vertices and texture coords
        m_attribute_data = flags::texcoords;


        std::vector<float> vertice_data;

        for (int i = 0; i < vertices.size(); ++i) {
            // Append vertex positions
            vertice_data.push_back(vertices[i].x);
            vertice_data.push_back(vertices[i].y);
            vertice_data.push_back(vertices[i].z);


            // Append texture coords
            vertice_data.push_back(uv[i].x);
            vertice_data.push_back(uv[i].y);
        }

        generate(vertice_data, indices);
    }

    Geometry::Geometry(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uv,
               const std::vector<glm::vec3> &normals, const std::vector<unsigned int> &indices) {
        // Geometry with vertices, texture coords and normals
        m_attribute_data = flags::texcoords | flags::normals;

        // Append all vertex positions
        std::vector<float> vertice_data;
        for (int i = 0; i < vertices.size(); ++i) {
            // Append vertex positions
            vertice_data.push_back(vertices[i].x);
            vertice_data.push_back(vertices[i].y);
            vertice_data.push_back(vertices[i].z);


            // Append texture coords
            vertice_data.push_back(uv[i].x);
            vertice_data.push_back(uv[i].y);

            // Append normals
            vertice_data.push_back(normals[i].x);
            vertice_data.push_back(normals[i].y);
            vertice_data.push_back(normals[i].z);
        }


        generate(vertice_data, indices);

    }

    Geometry::~Geometry()
    {
        // If ids are still valid, delete them (if they haven't, they have been moved)

        if(m_vao != 0) {
            glDeleteVertexArrays(1, &m_vao);
            m_vao = 0;
        }
        if(m_vbo != 0) {
            glDeleteBuffers(1, &m_vbo);
            m_vbo = 0;
        }
        if(m_ebo != 0) {
            glDeleteBuffers(1, &m_ebo);
            m_ebo = 0;
        }
    }

    Geometry::Geometry(Geometry &&other) noexcept{
        this->m_vao   = other.m_vao;
        this->m_vbo   = other.m_vbo;
        this->m_ebo   = other.m_ebo;

        this->m_vertice_count   = other.m_vertice_count;
        this->m_indice_count    = other.m_indice_count;



        // Invalidate old mesh's ids
        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_ebo = 0;
    }

    Geometry &Geometry::operator=(Geometry &&other) noexcept{
        this->m_vao   = other.m_vao;
        this->m_vbo   = other.m_vbo;
        this->m_ebo   = other.m_ebo;

        this->m_vertice_count   = other.m_vertice_count;
        this->m_indice_count    = other.m_indice_count;

        // Invalidate old mesh's ids
        other.m_vao = 0;
        other.m_vbo = 0;
        other.m_ebo = 0;

        return *this;
    }


    void Geometry::generate(const std::vector<float> &vertice_data, const std::vector<unsigned int> &indices) {
        glGenVertexArrays(1, &m_vao);
        glGenBuffers(1, &m_vbo);
        glGenBuffers(1, &m_ebo);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(m_vao);

        glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertice_data.size() * sizeof(float), vertice_data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(float), indices.data(), GL_STATIC_DRAW);

        int stride = get_stride();
        int offset = 0;
        unsigned int attribute_index = 0;

        // Vertex data
        glVertexAttribPointer(attribute_index, 3, GL_FLOAT, GL_FALSE, stride, (void *) offset);
        glEnableVertexAttribArray(attribute_index);
        attribute_index++;
        offset += (3 * sizeof(float));

        // Color data
        if (m_attribute_data[COLORS_BIT]) {
            glVertexAttribPointer(attribute_index, 3, GL_FLOAT, GL_FALSE, stride, (void *) offset);
            glEnableVertexAttribArray(attribute_index);
            attribute_index++;
            offset += (3 * sizeof(float));
        }

        // TexCoord data
        if (m_attribute_data[TEXCOORDS_BIT]) {
            glVertexAttribPointer(attribute_index, 2, GL_FLOAT, GL_FALSE, stride, (void *) offset);
            glEnableVertexAttribArray(attribute_index);
            attribute_index++;
            offset += (2 * sizeof(float));
        }

        // Normal data
        if (m_attribute_data[NORMALS_BIT]) {
            glVertexAttribPointer(attribute_index, 3, GL_FLOAT, GL_FALSE, stride, (void *) offset);
            glEnableVertexAttribArray(attribute_index);
            attribute_index++;
            offset += (3 * sizeof(float));
        }

        m_vertice_count = static_cast<unsigned int>(vertice_data.size() / stride);
        m_indice_count = static_cast<unsigned int>(indices.size());

        // Unbind TODO: Not necessary
        glBindVertexArray(0);
    }

    int Geometry::get_stride() const {
        int stride = 3 * sizeof(float); // Vertices are always needed for a mesh!

        std::string test = m_attribute_data.to_string();

        stride += m_attribute_data[NORMALS_BIT] * 3 * sizeof(float); // Normals size per vertex
        stride += m_attribute_data[COLORS_BIT] * 3 * sizeof(float); // Color size per vertex
        stride += m_attribute_data[TEXCOORDS_BIT] * 2 * sizeof(float); // TexCoords size per vertex
        stride += m_attribute_data[SKIN_BIT] * 8 * sizeof(int); // Skin size per vertex TODO: Fix


        return stride;
    }

    void Geometry::draw() const {
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indice_count, GL_UNSIGNED_INT, 0);
    }
}