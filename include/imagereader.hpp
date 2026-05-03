#pragma once

#include <cstddef>
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

        protected:
                void populateDataFromFile(std::ifstream &file);
        };
}
