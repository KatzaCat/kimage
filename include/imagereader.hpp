#pragma once

#include <string>
#include <unordered_map>
#include <vector>

namespace k {
        namespace image_data {
                enum Type {
                        ERROR,
                        DATA
                };

                struct Resopnce {
                        Type type;
                        union _as {
                                std::byte data;
                                int error;
                        } as;
                };
        }

        class ImageReader {
        public:
                std::unordered_map<std::string, std::vector<std::byte>> data = {};

        public:
                virtual ~ImageReader() = default;

                virtual bool load(const std::string file_name) = 0;

                virtual image_data::Resopnce getData() = 0;
        };
}
