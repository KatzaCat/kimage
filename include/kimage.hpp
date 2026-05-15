#pragma once

#include <memory>
#include <string>
#include <vector>

#include "imageprocessor.hpp"

namespace k {
        class Image {
        public:
                Image() = default;

                Image(const std::string file);

                bool load(std::string file);

                std::vector<unsigned char> getData();

                int32_t getWidth();
                int32_t getHeight();
        private:
                std::unique_ptr<ImageProcessor> processor  = {};
        private:
                bool setProcessor(std::unique_ptr<ImageProcessor> processor);
        };
}
