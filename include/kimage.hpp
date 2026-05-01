#pragma once

#include <memory>
#include <string>

#include "imagereader.hpp"

namespace k {
        class Image {
        public:
                Image() = default;

                Image(std::unique_ptr<ImageReader> reader);
                Image(std::unique_ptr<ImageReader> reader, const std::string file);

                bool load(std::string file);

                bool setReder(std::unique_ptr<ImageReader> reader);

                image_data::Resopnce getData();
        private:
                std::unique_ptr<ImageReader> reader = {};
        };
}
