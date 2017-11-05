//
// Created by aejt on 10/22/17.
//

#pragma once

#include <vector>
#include <optional>

#include "GLContext.h"

#include "../Camera/Camera.h"

#include "../Meshes/Mesh.h" // TODO: Remove

#include "../Materials/ShaderProgram.h" // TODO: Remove
#include "../Materials/Material.h" // TODO: Remove
#include "../Materials/Texture2D.h" // TODO: Remove

#include "../Resources/ResourceLibrary.h"

#include "RenderTarget.h"
#include "RenderCommand.h"
#include "UniformBuffer.h"
#include "UBData.h"

namespace Enchine {

    class Renderer {
    private: // TODO: Variables which aren't to be used later on
        std::vector<Material>       temp_materials; // TODO: Remove
        std::vector<RenderCommand>  temp_render_commands;

    private:

        unsigned int                m_width = 800; // Don't have a default value
        unsigned int                m_height = 600; // Don't have a default value


        GLContext                   glcontext;
        ResourceLibrary             resource_lib;

        RenderTarget                m_gbuffer;
        std::vector<RenderTarget>   m_render_targets;
        RenderTarget                m_default_target;
        RenderTarget               *m_active_target;

        UniformBuffer<UBData>       m_uniform_buffer;

        Camera                      m_camera;


    private:

        std::vector<RenderCommand> m_render_commands; //TODO: Need more than one buffer? Create separate class?

        void render_command(const RenderCommand* command /*TODO: Camera */);

    public:
        Renderer();
        ~Renderer() = default;

        void set_target(RenderTarget& render_target, GLenum target = GL_TEXTURE_2D);
        RenderTarget& get_active_render_target();
        void blit_color(const RenderTarget& dst, const RenderTarget& src);

        Camera& get_camera() { return m_camera; }


        void run();

    };

}

