#include "imagereader/bmp.hpp"
#include "imagereader.hpp"

#include <fstream>
#include <ios>
#include <print>
#include <string>

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
        response.information = this->data;

        return response;
}

void k::BMPReader::printData() {
        std::println("TODO: BMP printData");
}
