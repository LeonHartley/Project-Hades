#pragma once

#include <string>
#include <fstream>
#include <experimental/filesystem>

namespace hades {

    class File {
    public:
        static std::string load(const std::string path) {
            std::ifstream ifs(path);
            std::string content((std::istreambuf_iterator<char>(ifs)),
                                 (std::istreambuf_iterator<char>()));

            return std::move(content);
        }
    };

}