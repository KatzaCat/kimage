#include "imagereader/bmp.hpp"
#include "imagereader.hpp"

#include <cstddef>
#include <fstream>
#include <ios>
#include <print>
#include <string>
#include <vector>

bool k::BMPReader::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        this->populateDataFromFile(binary_file);
        this->populateBMPData();

        binary_file.close();

        return true;
}

k::image_data::Response k::BMPReader::getData() {
        this->response.type = image_data::DATA;
        this->response.information = this->data;

        return this->response;
}

void k::BMPReader::printData() {
        for (size_t index = 0; index < this->data.size(); index++) {
                std::print("{:02X} ", static_cast<unsigned char>(this->data.at(index)));

                if (((index + 1) % 20) == 0)
                {std::print("\n");}
        }
        std::print("\n");

        std::println("Pixel Array Offset : {:8} -> 0x{:08X}", this->pixel_array_offset, this->pixel_array_offset);
        std::println("Image Width        : {:8} -> 0x{:08X}", this->image_width, this->image_width);
        std::println("Image Height       : {:8} -> 0x{:08X}", this->image_height, this->image_height);
        std::println("Bits Per Pixel     : {:8} -> 0x{:08X}", this->bits_per_pixel, this->bits_per_pixel);
}

int32_t k::BMPReader::getWidth()
{return this->image_width;}

int32_t k::BMPReader::getHeight()
{return this->image_height;}

void k::BMPReader::populateBMPData() {
        this->pixel_array_offset = this->getFourBytesLittleEndian(10);

        this->image_width = this->getFourBytesLittleEndian(18);
        this->image_height = this->getFourBytesLittleEndian(22);

        this->bits_per_pixel = this->getTwoBytesLittleEndian(28);
}
