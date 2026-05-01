#include "imagereader/bmp.hpp"
#include "imagereader.hpp"

#include <cstddef>
#include <fstream>
#include <ios>
#include <print>
#include <string>
#include <vector>

bool k::BMPReader::load(const std::string file_name) {
        std::ifstream file(file_name, std::ios::binary);
        if (!file.is_open()) {return false;}

        std::streamsize file_stream_size = file.tellg();
        file.seekg(0, std::ios::beg);

        std::vector<std::byte> data_buffer(file_stream_size);
        if (!file.read(reinterpret_cast<char *>(data_buffer.data()), file_stream_size)) {
                file.close();
                return false;
        }
        if (!this->proccessDataBffer(data_buffer)) {
                file.close();
                return false;
        }

        file.close();

        return true;
}

k::image_data::Resopnce k::BMPReader::getData() {
        std::println("TODO: BMP getData");

        image_data::Resopnce responce = {};
        responce.type = image_data::DATA;
        responce.as.data = std::byte(1);

        return responce;
}

bool k::BMPReader::proccessDataBffer(std::vector<std::byte> data_buffer) {
        // Header (14 bytes) :
        //      Signature       -> 2 bytes
        //      FileSize        -> 4 bytes
        //      Reserved        -> 4 bytes
        //      DataOffset      -> 4 bytes
        // InfoHeader (40) :
        //      Size            -> 4 bytes
        //      Width           -> 4 bytes
        //      Height          -> 4 bytes
        //      Planes          -> 2 bytes
        //      BitsPerPixel    -> 2 bytes
        //      Compression     -> 4 bytes
        //      ImageSize       -> 4 bytes
        //      XpixelsPerM     -> 4 bytes
        //      YpixelsPerM     -> 4 bytes
        //      ColorsUsed      -> 4 bytes
        //      ImportantColors -> 4 bytes
        // ColorTable (4 * number_of_colors bytes) :
        //      Red             -> 1 byte
        //      Green           -> 1 byte
        //      Blue            -> 1 byte
        //      Reserved        -> 1 byte
        // PixelData ()

        return true;
}
