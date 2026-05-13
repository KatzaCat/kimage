#pragma once

#include "../imagereader.hpp"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

#define BMP_FILE_NOT_FOUND_ERROR 0x10001

namespace k {
        class BMPReader : public ImageReader {
        public:
                virtual ~BMPReader() override = default;

                virtual bool load(const std::string file_name) override;

                virtual image_data::Response getResponse() override;
                virtual std::vector<unsigned char> getRawData() override;

                virtual int32_t getWidth() override;
                virtual int32_t getHeight() override;

                virtual void printData() override;
        private:
                image_data::Response response = {};

                uint32_t pixel_data_offset = 0;

                int32_t image_width = 0;
                int32_t image_height = 0;

                uint16_t bits_per_pixel = 0;

                uint32_t compression_level = 0;

                std::vector<uint32_t> color_table = {};

                std::vector<uint32_t> pixel_data = {};

                size_t pixel_data_index = 0;

                int32_t bytes_per_row = 0;
                int32_t bytes_per_pixel = 0;

                int32_t pixel_data_padding = 0;

                size_t pixels_read = 0;
        private:
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
