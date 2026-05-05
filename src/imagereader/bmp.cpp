#include "imagereader/bmp.hpp"
#include "imagereader.hpp"

#include <cstddef>
#include <fstream>
#include <ios>
#include <memory>
#include <print>
#include <string>
#include <vector>

bool k::BMPReader::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        this->populateDataFromFile(binary_file);

        binary_file.close();

        return true;
}

k::image_data::Response k::BMPReader::getData() {
        std::println("TODO: BMP getData");

        image_data::Response response;
        response.type = image_data::DATA;

        std::unique_ptr<std::byte> data_pointer(this->data.data());
        response.information = std::move(data_pointer);

        return response;
}

void k::BMPReader::printData() {}
