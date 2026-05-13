#include <memory>

#include <imageprocessor/bmp.hpp>
#include <kimage.hpp>

int main() {
        k::Image bmp_file(std::make_unique<k::BMPProcessor>());

        bmp_file.load("images/BMP1bit.bmp");

        return 0;
}
