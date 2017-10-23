//
// Created by aejt on 10/22/17.
//

#include "Mesh.h"

#include <glad/glad.h>


namespace Enchine {

    Mesh::Mesh(const std::vector<float> &vertice_data, const std::vector<int> &indices,
               std::bitset<ATTRIBUTE_COUNT> attributes) : m_attribute_data(attributes) {
        generate(vertice_data, indices);
    }

    int Mesh::get_stride() const {
        int stride = 3 * sizeof(float); // Vertices are always needed for a mesh!

        std::string test = m_attribute_data.to_string();

        stride += m_attribute_data[NORMALS_BIT] * 3 * sizeof(float); // Normals size per vertex
        stride += m_attribute_data[COLORS_BIT] * 3 * sizeof(float); // Color size per vertex
        stride += m_attribute_data[TEXCOORDS_BIT] * 2 * sizeof(float); // TexCoords size per vertex
        stride += m_attribute_data[SKIN_BIT] * 8 * sizeof(int); // Skin size per vertex TODO: Fix


        return stride;
    }

    void Mesh::draw() const {
        glBindVertexArray(m_vao);
        glDrawElements(GL_TRIANGLES, m_indice_count, GL_UNSIGNED_INT, 0);
    }

    Mesh::Mesh(const std::vector<glm::vec3> &vertices, const std::vector<int> &indices) {
        // Mesh with only vertices
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

    Mesh::Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uv,
               const std::vector<int> &indices) {
        // Mesh with vertices and texture coords
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

    Mesh::Mesh(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec2> &uv,
               const std::vector<glm::vec3> &normals, const std::vector<int> &indices) {
        // Mesh with vertices, texture coords and normals
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

    void Mesh::generate(const std::vector<float> &vertice_data, const std::vector<int> &indices) {
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertice_data.size() * sizeof(float), vertice_data.data(), GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
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

        // Save VAO
        m_vao = VAO;
        m_vertice_count = static_cast<unsigned int>(vertice_data.size() / stride);
        m_indice_count = static_cast<unsigned int>(indices.size());

        // Unbind TODO: Not necessary
        glBindVertexArray(0);
    }
}