#pragma once

#include <string>

#include "imagereader.hpp"

namespace k {
        class Image {
        public:
                Image();
                Image(const std::string file, ImageReader *reader);

                bool load(const std::string file, ImageReader *reader);

                image::DataResopnce getData();
        private:
                ImageReader *reader = nullptr;
        };
}
