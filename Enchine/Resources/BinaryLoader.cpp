//
// Created by aejt on 11/16/17.
//

#include "BinaryLoader.h"


#include <fstream>
#include <iterator>
#include <future>


namespace Enchine {

    std::vector<std::byte> BinaryLoader::load_file(const std::string& path) {

        // Open file at end
        std::ifstream file(path, std::ios::binary | std::ios::ate | std::ios::in);
        auto file_size = static_cast<size_t>(file.tellg());
        file.seekg(0, std::ios::beg);

        std::vector<std::byte> file_content(file_size);
        file.read(reinterpret_cast<char *>(file_content.data()), file_size);

        return file_content;
    }

    void BinaryLoader::load_file_async(const std::string& path, std::function<void(std::vector<std::byte>&&)> callback) {
        std::async(std::launch::async, [&]() { callback(load_file(path)); });
    }

}