#include <memory>

#include <imagereader/bmp.hpp>
#include <kimage.hpp>

int main() {
        k::Image bmp_file(std::make_unique<k::BMPReader>());

        bmp_file.load("images/BMP_Test.bmp");
        bmp_file.printData();

        return 0;
}
