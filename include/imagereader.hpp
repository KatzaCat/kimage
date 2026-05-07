#pragma once

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include <variant>
#include <vector>

namespace k {
        namespace image_data {
                enum Type {
                        ERROR,
                        DATA
                };

                struct Response {
                        Type type;
                        std::variant<std::vector<std::byte>, int> information;
                };
        }

        class ImageReader {
        public:
                std::vector<std::byte> data;
        public:
                virtual ~ImageReader() = default;

                virtual bool load(const std::string file_name) = 0;

                virtual image_data::Response getData() = 0;

                virtual void printData() = 0;

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
