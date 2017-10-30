//
// Created by aejt on 10/23/17.
//


#include "../Resources/ResourceCache.h"
#include "../Materials/Texture2D.h"

namespace Enchine {


    struct UniformValueSampler
    {
        unsigned int unit;
        Resource<Texture2D> texture;

    };

}