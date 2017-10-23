//
// Created by aejt on 10/22/17.
//

#pragma once

#include <vector>
#include "../Meshes/Mesh.h" // TODO: Remove
#include "../Materials/ShaderProgram.h" // TODO: Remove
#include "../Materials/Material.h" // TODO: Remove
#include "../Materials/Texture2D.h" // TODO: Remove

#include "RenderCommand.h"

namespace Enchine {

    class Renderer {
    private:
        std::vector<Mesh> temp_meshes; // TODO: Remove
        std::vector<ShaderProgram> temp_shaders; // TODO: Remove
        std::vector<Texture2D> temp_textures; // TODO: Remove
        std::vector<Material> temp_materials; // TODO: Remove

        std::vector<RenderCommand> m_render_commands; //TODO: Need more than one buffer? Create separate class?


    public:
        Renderer();

        virtual ~Renderer();

        void run();

    };

}

