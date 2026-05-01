#pragma once

#include <string>

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
                virtual ~ImageReader() = default;

                virtual bool load(const std::string file) = 0;

                virtual image_data::Resopnce getData() = 0;
        };
}
