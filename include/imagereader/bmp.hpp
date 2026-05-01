#pragma once

#include "../imagereader.hpp"

namespace k {
        class BMPReader : public ImageReader {
        public:
                virtual ~BMPReader() override = default;

                virtual bool load(const std::string file) override;

                virtual image_data::Resopnce getData() override;
        };
}
