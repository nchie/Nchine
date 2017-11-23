//
// Created by aejt on 11/16/17.
//

#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <functional>

namespace Enchine {

    class BinaryLoader {

    private:

    public:
        std::vector<std::byte> load_file(const std::string& path);

        void load_file_async(const std::string& path, std::function<void(std::vector<std::byte>&&)> callback);

    };

}