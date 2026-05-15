#include <imageprocessor/bmp.hpp>
#include <kimage.hpp>

int main() {
        // inject dependency
        k::Image image;

        // test to see if works
        image.load("BMP_test.bmp");

        return 0;
}
