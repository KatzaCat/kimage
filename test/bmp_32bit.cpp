#include <imageprocessor/bmp.hpp>
#include <kimage.hpp>

int main() {
        k::Image bmp_file;

        bmp_file.load("images/BMP32bit.bmp");

        return 0;
}
