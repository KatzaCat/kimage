#pragma once

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

namespace k {
        class ImageProcessor {
        public:
                std::vector<std::byte> byte_data = {};
                std::vector<uint32_t> pixel_data = {};
        public:
                virtual ~ImageProcessor() = default;

                virtual bool load(const std::string file_name) = 0;

                std::vector<unsigned char> getData();

                virtual int32_t getWidth() = 0;
                virtual int32_t getHeight() = 0;
        protected:
                bool populateDataFromFile(std::ifstream &file);

                std::byte getByte(size_t offset);

                uint16_t getTwoBytesBigEndian(size_t offset);
                uint32_t getFourBytesBigEndian(size_t offset);

                uint16_t getTwoBytesLittleEndian(size_t offset);
                uint32_t getFourBytesLittleEndian(size_t offset);
        };
}
