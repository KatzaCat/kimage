#include "imagereader/bmp.hpp"
#include "imagereader.hpp"

#include <cstddef>
#include <print>
#include <string>

bool k::reader::BMP::load(const std::string file) {
        std::println("TODO: BMP load");

        return true;
}

k::image::DataResopnce k::reader::BMP::getData() {
        std::println("TODO: BMP getData");

        k::image::DataResopnce responce = {};
        responce.type = image::DATA;
        responce.as.data = std::byte(1);

        return responce;
}
