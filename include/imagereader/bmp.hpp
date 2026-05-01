#pragma once

#include "../imagereader.hpp"
#include <cstddef>

namespace k {
        class BMPReader : public ImageReader {
        public:
                virtual ~BMPReader() override = default;

                virtual bool load(const std::string file_name) override;

                virtual image_data::Resopnce getData() override;

        private:
                size_t number_of_colors = 0;

        private:
                bool proccessDataBffer(std::vector<std::byte> data_buffer);


                const size_t SIGNATURE_POSITION       = 2;
                const size_t FILESIZE_POSITION        = 4;
                const size_t DATAOFFSET_POSITION      = 4;
                const size_t SIZE_POSITION            = 4;
                const size_t WIDTH_POSITION           = 4;
                const size_t HEIGHT_POSITION          = 4;
                const size_t PLANES_POSITION          = 2;
                const size_t BITSPERPIXEL_POSITION    = 2;
                const size_t COMPRESSION_POSITION     = 4;
                const size_t IMAGESIZE_POSITION       = 4;
                const size_t XPIXELSPERM_POSITION     = 4;
                const size_t YPIXELSPERM_POSITION     = 4;
                const size_t COLORSUSED_POSITION      = 4;
                const size_t IMPORTANTCOLORS_POSITION = 4;
                const size_t RED_POSITION             = 1;
                const size_t GREEN_POSITION           = 1;
                const size_t BLUE_POSITION            = 1;
        };
}
