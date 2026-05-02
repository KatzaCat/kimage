#pragma once

#include "../imagereader.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace k {
        namespace bmp {
                struct Header {
                        uint16_t signature = 0;
                        uint32_t file_size = 0;
                        uint32_t reserved = 0;
                        uint32_t raster_data_offset = 0;
                };

                struct InfoHeader {
                        uint32_t info_header_size = 0;
                        uint32_t bitmap_width = 0;
                        uint32_t bitmap_height = 0;
                        uint16_t plane_amount = 0;
                        uint16_t bits_per_pixel = 0;
                        uint32_t compression_type = 0;
                        uint32_t image_size = 0;
                        uint32_t horizontal_resolution = 0;
                        uint32_t vertical_resolution = 0;
                        uint32_t amount_colors_used = 0;
                        uint32_t amount_important_colors = 0;
                        std::vector<uint32_t> color_table = {};
                };
        }

        class BMPReader : public ImageReader {
        public:
                virtual ~BMPReader() override = default;

                virtual bool load(const std::string file_name) override;

                virtual image_data::Response getData() override;

                virtual void printData() override;

        private:
                bmp::Header header = {};

                bmp::InfoHeader info_header = {};
                size_t number_of_colors = 0;

                std::vector<std::byte> raster_data = {};

        private:
                void populateInformation();
                void populateHeader();

                void populateColorTable();
                void populateInfoHeader();

                void populateRasterData();
        };
}
