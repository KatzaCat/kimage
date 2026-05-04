#pragma once

#include "../imagereader.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace k {
        namespace bm {
                struct FileHeader {
                        std::byte signature[2] = {};
                        uint32_t file_size = 0;
                        uint16_t reserved1 = 0;
                        uint16_t reserved2 = 0;
                        uint32_t pixel_array_offset = 0;
                };

                enum struct Compression : int {
                        BI_RGB            = 0,
                        BI_RLE8           = 1,
                        BI_RLE4           = 2,
                        BI_BITFIELDS      = 3,
                        BI_JPEG           = 4,
                        BI_PNG            = 5,
                        BI_ALPHABITFIELDS = 6,
                        BI_CMYK           = 11,
                        BI_CMYKRLE8       = 12,
                        BI_CMYKRLE4       = 13
                };

                struct InformationHeader {
                        uint32_t header_size = 0;
                        int32_t image_width = 0;
                        int32_t image_height = 0;
                        uint16_t plains = 0;
                        uint16_t bits_per_pixel = 0;
                        Compression compression = Compression::BI_RGB;
                        uint32_t image_size = 0;
                        int32_t horizontal_resolution = 0;
                        int32_t vertical_resolution = 0;
                        uint32_t color_table_colors = 0;
                        uint32_t important_colors = 0;
                };

                struct Color {
                        char red;
                        char green;
                        char blue;
                        char alfa;
                };
        }

        class BMPReader : public ImageReader {
        public:
                virtual ~BMPReader() override = default;

                virtual bool load(const std::string file_name) override;

                virtual image_data::Response getData() override;

                virtual void printData() override;
        private:
                bm::FileHeader file_header = {};
                bm::InformationHeader information_header = {};

                std::vector<bm::Color> color_table = {};
                std::vector<bm::Color> pixel_array = {};
        private:
                void populateFileHeader();
                void populateInformationHeader();
                void populateColorTable();
                void populatePixelArray();

                void loadPixelArrayOneBit(std::vector<std::byte> pixels_in_bytes);
                void loadPixelArrayTwoBit(std::vector<std::byte> pixels_in_bytes);
                void loadPixelArrayFourBit(std::vector<std::byte> pixels_in_bytes);
                void loadPixelArrayEightBit(std::vector<std::byte> pixels_in_bytes);
                void loadPixelArraySixteenBit(std::vector<std::byte> pixels_in_bytes);
                void loadPixelArrayTwentyFourBit(std::vector<std::byte> pixels_in_bytes);
                void loadPixelArrayThirtyFourBit(std::vector<std::byte> pixels_in_bytes);
        };
}
