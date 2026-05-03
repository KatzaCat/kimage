#pragma once

#include "../imagereader.hpp"

namespace k {
        class BMPReader : public ImageReader {
        public:
                virtual ~BMPReader() override = default;

                virtual bool load(const std::string file_name) override;

                virtual image_data::Response getData() override;

                virtual void printData() override;
        };
}
