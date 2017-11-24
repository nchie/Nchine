//
// Created by aejt on 11/16/17.
//

#pragma once

#include <cstddef>
#include <vector>
#include <string>
#include <functional>

#include "BinaryLoader.h"

namespace Enchine {

    class BinaryFileLoader : public BinaryLoader {

    private:

    public:
        std::vector<std::byte> load_binary(const std::string& identifier) override;

    };

}