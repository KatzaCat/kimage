#pragma once

#include "../imagereader.hpp"

namespace k {
        namespace reader {
                class BMP :public ImageReader {
                        bool load(const std::string file) override;

                        image::DataResopnce getData() override;
                };
        }
}
