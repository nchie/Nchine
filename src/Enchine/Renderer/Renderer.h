//
// Created by aejt on 10/22/17.
//

#pragma once

#include <vector>
#include "../Meshes/Mesh.h" // TODO: Remove
#include "../Materials/ShaderProgram.h" // TODO: Remove
#include "../Materials/Material.h" // TODO: Remove
#include "../Materials/Texture2D.h" // TODO: Remove
#include "../Resources/ResourceLibrary.h"
#include "GLContext.h"

#include "RenderCommand.h"

namespace Enchine {

    class Renderer {
    private:
        std::vector<Material> temp_materials; // TODO: Remove

        GLContext glcontext;
        ResourceLibrary resource_lib;

    private:

        std::vector<RenderCommand> m_render_commands; //TODO: Need more than one buffer? Create separate class?

        void render_command(const RenderCommand* command /*TODO: Camera */);

    public:
        Renderer();
        ~Renderer() = default;

        void run();

    };

}

