#pragma once

#include "../imagereader.hpp"
#include <cstdint>
#include <vector>

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

                uint32_t pixel_data_offset = 0;

                int32_t image_width = 0;
                int32_t image_height = 0;

                uint16_t bits_per_pixel = 0;

                uint32_t compression_level = 0;

                std::vector<uint32_t> color_table = {};
                std::vector<uint32_t> pixel_data = {};
        private:
                void populateBMPData();
                void populateColorTable();
                void populatePixelData();

                void process1Bit();
                void process2Bit();
                void process4Bit();
                void process8Bit();
                void process16Bit();
                void process24Bit();
                void process32Bit();
        };
}
