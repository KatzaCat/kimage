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

        private:
                size_t byte_index = 0;

        protected:
                void populateDataFromFile(std::ifstream &file);

                std::byte getNextByte();

                uint16_t getNextTwoBytesLSB();
                uint32_t getNextFourBytesLSB();

                uint16_t getNextTwoBytesMSB();
                uint32_t getNextFourBytesMSB();
        };
}
