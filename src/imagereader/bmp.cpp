#include "imagereader/bmp.hpp"
#include "imagereader.hpp"

#include <cstddef>
#include <print>
#include <string>

bool k::BMPReader::load(const std::string file) {
        std::println("TODO: BMP load");

        return true;
}

k::image_data::Resopnce k::BMPReader::getData() {
        std::println("TODO: BMP getData");

        image_data::Resopnce responce = {};
        responce.type = image_data::DATA;
        responce.as.data = std::byte(1);

        return responce;
}
