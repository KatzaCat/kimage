#include <imageprocessor/bmp.hpp>
#include <kimage.hpp>
#include <memory>

int main() {
        // inject dependency
        k::Image image(std::make_unique<k::BMPProcessor>());

        // test to see if works
        image.load("BMP_test.bmp");

        return 0;
}
