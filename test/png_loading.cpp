#include "kimage.hpp"
#include <print>

int main() {
        k::Image png_image;
        png_image.load("images/PNGImage.png");

        std::println("width  : {}", png_image.getWidth());
        std::println("height : {}", png_image.getHeight());

        return 0;
}
