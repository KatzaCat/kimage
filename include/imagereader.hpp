#pragma once

#include <string>

namespace k {
        namespace image {
                enum DataType {
                        ERROR,
                        DATA
                };

                struct DataResopnce {
                        DataType type;
                        union _as {
                                std::byte data;
                                int error;
                        } as;
                };
        }

        class ImageReader {
        public:
                virtual bool load(const std::string file) = 0;

                virtual image::DataResopnce getData();
        };
}
