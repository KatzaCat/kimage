#include "imageprocessor/bmp.hpp"
#include <cstddef>
#include <kimage.hpp>
#include <memory>
#include <print>
#include <vector>
//#include <print>

int main() {
        k::Image image(std::make_unique<k::BMPProcessor>(), "images/BMP32bit.bmp");

        std::vector<unsigned char> image_data_vector = image.getData();

        unsigned char *raw_data = image_data_vector.data();
        size_t raw_data_size = image_data_vector.size();

        for (size_t index = 0; index < raw_data_size; index++) {
                std::print("{:02X}", raw_data[index]);

                if (((index + 1) % 4) == 0) {std::print(" ");}
                if (((index + 1) % (image.getWidth() * 4)) == 0) {std::print("\n");}
        }

        return 0;
}
