//
// Created by aejt on 11/16/17.
//

#include "BinaryFileLoader.h"


#include <fstream>
#include <iterator>
#include <future>


namespace Enchine {

    std::vector<std::byte> BinaryFileLoader::load_binary(const std::string &identifier) {

        // Open file at end
        std::ifstream file(identifier, std::ios::binary | std::ios::ate | std::ios::in);
        auto file_size = static_cast<size_t>(file.tellg());
        file.seekg(0, std::ios::beg);

        std::vector<std::byte> file_content(file_size);
        file.read(reinterpret_cast<char *>(file_content.data()), file_size);

        return file_content;
    }

}