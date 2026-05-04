#pragma once

#include <cstddef>
#include <fstream>
#include <memory>
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
                        std::variant<std::unique_ptr<std::byte>, int> information;
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
        private:
                size_t data_index = 0;
        protected:
                bool populateDataFromFile(std::ifstream &file);

                std::byte getCurrentByte();

                uint16_t getCurrentTwoBytesBigEndian();
                uint32_t getCurrentFourBytesBigEndian();

                uint16_t getCurrentTwoBytesLittleEndian();
                uint32_t getCurrentFourBytesLittleEndian();
        };
}
