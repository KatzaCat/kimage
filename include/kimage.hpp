#pragma once

#include <memory>
#include <string>
#include <vector>

#include "imagereader.hpp"

namespace k {
        class Image {
        public:
                Image() = default;

                Image(std::unique_ptr<ImageReader> reader);
                Image(std::unique_ptr<ImageReader> reader, const std::string file);

                bool load(std::string file);

                image_data::Response getResponse();
                std::vector<unsigned char> getRawData();

                int32_t getWidth();
                int32_t getHeight();

                void printData();
        private:
                std::unique_ptr<ImageReader> reader = {};
        private:
                bool setReder(std::unique_ptr<ImageReader> reader);
        };
}
