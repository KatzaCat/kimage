#include "imageprocessor/png.hpp"

#include <fstream>

bool k::PNGProcessor::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        binary_file.close();

        return true;
}

std::vector<unsigned char> k::PNGProcessor::getData() {
        return {};
}

int32_t k::PNGProcessor::getWidth()
{return 0;}

int32_t k::PNGProcessor::getHeight()
{return 0;}

std::string k::PNGProcessor::getName() 
{return "PNG Processor";}
