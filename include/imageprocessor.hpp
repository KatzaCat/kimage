#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace k {
        class ImageProcessor {
        public:
                virtual ~ImageProcessor() = default;

                virtual bool load(const std::string file_name) = 0;

                virtual std::vector<unsigned char> getData() = 0;

                virtual int32_t getWidth() = 0;
                virtual int32_t getHeight() = 0;
        };
}
