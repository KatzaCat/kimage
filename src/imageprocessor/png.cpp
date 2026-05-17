#include "imageprocessor/png.hpp"

#include <fstream>

bool k::PngProcessor::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        this->data.populateFromFile(binary_file);

        binary_file.close();

        return true;
}

std::vector<unsigned char> k::PngProcessor::getData() {
        return {};
}

int32_t k::PngProcessor::getWidth()
{return 0;}

int32_t k::PngProcessor::getHeight()
{return 0;}
