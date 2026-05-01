#include <imagereader/bmp.hpp>
#include <kimage.hpp>
#include <memory>

int main() {
        // inject dependency
        k::Image image(std::make_unique<k::BMPReader>());

        // test to see if works
        image.load("BMP_test.bmp");
        (void)image.getData();

        return 0;
}
