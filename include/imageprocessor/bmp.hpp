#pragma once

#include "../imageprocessor.hpp"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

namespace k {
        class BMPProcessor : public ImageProcessor {
        public:
                virtual ~BMPProcessor() override = default;

                virtual bool load(const std::string file_name) override;

                virtual int32_t getWidth() override;
                virtual int32_t getHeight() override;
        private:
                size_t pixel_data_index = 0;

                std::vector<uint32_t> color_table = {};

                int32_t bytes_per_row = 0;
                int32_t bytes_per_pixel = 0;

                size_t pixels_read = 0;
        private:
                int32_t getBitsPerPixel();

                void populateBMPData();
                void populateColorTable();
                void populatePixelData();

                void processPixelBytes(std::function<void()> function);

                void process1Bit();
                void process2Bit();
                void process4Bit();
                void process8Bit();
                void process16Bit();
                void process24Bit();
                void process32Bit();
        };
}
