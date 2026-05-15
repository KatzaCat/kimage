#pragma once

#include <vector>
#include <fstream>

namespace k {
        class ImageData {
        public:
                bool populateFromFile(std::ifstream &file);

                void pushPixel(uint32_t pixel);

                std::vector<unsigned char> format(int32_t width, int32_t height);

                std::byte getByte(size_t offset);

                uint16_t getTwoBytesBigEndian(size_t offset);
                uint32_t getFourBytesBigEndian(size_t offset);

                uint16_t getTwoBytesLittleEndian(size_t offset);
                uint32_t getFourBytesLittleEndian(size_t offset);
        private:
                std::vector<std::byte> bytes = {};
                std::vector<uint32_t> pixels = {};
        };
}
