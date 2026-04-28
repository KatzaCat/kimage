#include <imagereader/bmp.hpp>
#include <kimage.hpp>

int main() {
        // create dependency
        k::reader::BMP BMPReader = {};

        // inject dependency
        k::Image image(&BMPReader);

        // test to see if works
        image.load("test.bmp");
        (void)image.getData();

        return 0;
}
