#include <imageprocessor/bmp.hpp>
#include <kimage.hpp>

int main() {
        k::Image bmp_file;

        bmp_file.load("images/BMP24bit.bmp");

        return 0;
}
