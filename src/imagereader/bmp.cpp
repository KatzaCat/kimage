#include "imagereader/bmp.hpp"
#include "tools/int_type.hpp"
#include "imagereader.hpp"

#include <cmath>
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
        this->populateColorTable();

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
        std::println("Compression Level  : {:8} -> 0x{:08X}", this->compression_level, this->compression_level);

        std::println("Color Table Size   : {:8} -> 0x{:08X}", this->color_table.size(), this->color_table.size());
        std::println("Color Table        : [");
        for (size_t index = 0; index < this->color_table.size(); index++)
        {std::println("\t{:08X}, ", this->color_table.at(index));}
        std::println("]");
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

        this->compression_level = this->getFourBytesLittleEndian(30);
}

void k::BMPReader::populateColorTable() {
        if (this->bits_per_pixel > 8) {
                this->color_table.resize(0);
                return;
        }

        size_t offset = 54;
        size_t bytes_per_entry = 4;

        this->color_table.resize(std::pow(2, this->bits_per_pixel));

        size_t compression_offset_adition = 0;
        if      (this->compression_level == 3) {compression_offset_adition = 12;}
        else if (this->compression_level == 6) {compression_offset_adition = 16;}
        size_t color_table_offset = offset + compression_offset_adition;

        for (size_t index = 0; index < this->color_table.size(); index++) {
                size_t current_offset = color_table_offset + (bytes_per_entry * index);

                std::byte red = this->getByte(current_offset + 2);
                std::byte green = this->getByte(current_offset + 1);
                std::byte blue = this->getByte(current_offset);

                this->color_table.at(index) = tools::toInt32(
                        tools::toInt16(red, green),
                        tools::toInt16(blue, std::byte(0))
                );
        }
}
