#pragma once

#include "../imagereader.hpp"
#include <cstdint>

namespace k {
        class BMPReader : public ImageReader {
        public:
                virtual ~BMPReader() override = default;

                virtual bool load(const std::string file_name) override;

                virtual image_data::Response getData() override;

                virtual void printData() override;

                virtual int32_t getWidth() override;
                virtual int32_t getHeight() override;
        private:
                image_data::Response response = {};

                uint32_t pixel_array_offset = 0;

                int32_t image_width = 0;
                int32_t image_height = 0;

                uint16_t bits_per_pixel = 0;
        private:
                void populateBMPData();
        };
}
