#pragma once

#include <string>

#include "imagereader.hpp"

namespace k {
        class Image {
        public:
                Image();
                Image(ImageReader *reader);
                Image(const std::string file, ImageReader *reader);

                bool load(const std::string file);

                bool setReder(ImageReader *reader);

                image::DataResopnce getData();
        private:
                ImageReader *reader = nullptr;
        };
}
