//
// Created by aejt on 11/16/17.
//

#include "TextureFactory.h"

#include <memory>

#ifndef STB_IMAGE_IMPLEMENTATION // TODO: Remove
#include <stb_image.h> // TODO: Remove
#endif

Enchine::Resource<Enchine::Texture2D> Enchine::TextureFactory::load(const std::string& path) {
    int width, height, nr_channels;
    GLenum format;

    std::vector<std::byte> image_data = m_binary_loader->load_file(path);

    // Wrap in a unique_ptr
    auto data = std::unique_ptr<unsigned char>(stbi_load_from_memory(reinterpret_cast<unsigned char*>(image_data.data()), image_data.size(), &width, &height, &nr_channels, 0));

    // Was the texture RBG or RGBA?
    format = (nr_channels == 3) ? GL_RGB : GL_RGBA;

    return m_cache->load(path, Texture2D(reinterpret_cast<std::byte*>(data.get()), width, height, GL_RGBA, format, GL_UNSIGNED_BYTE));

    // unique_ptr will clear the memory stbi allocated!
}

void Enchine::TextureFactory::load_async(const std::string& path) {

}
