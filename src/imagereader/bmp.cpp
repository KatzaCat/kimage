#include "imagereader/bmp.hpp"
#include "tools/int_type.hpp"
#include "imagereader.hpp"

#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdint>
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
        this->populatePixelData();

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

        std::println("Pixel Array Offset : {:8} -> 0x{:08X}", this->pixel_data_offset, this->pixel_data_offset);
        std::println("Image Width        : {:8} -> 0x{:08X}", this->image_width, this->image_width);
        std::println("Image Height       : {:8} -> 0x{:08X}", this->image_height, this->image_height);
        std::println("Bits Per Pixel     : {:8} -> 0x{:08X}", this->bits_per_pixel, this->bits_per_pixel);
        std::println("Compression Level  : {:8} -> 0x{:08X}", this->compression_level, this->compression_level);

        std::println("Color Table Size   : {:8} -> 0x{:08X}", this->color_table.size(), this->color_table.size());
        std::println("Color Table        : [");
        for (size_t index = 0; index < this->color_table.size(); index++)
        {std::println("\t{:08X}, ", this->color_table.at(index));}
        std::println("]");

        std::println("Pixel Data Size    : {:8} -> 0x{:08X}", this->pixel_data.size(), this->pixel_data.size());
        std::print  ("Pixel Data         : [\n\t");
        for (size_t index = 0; index < this->pixel_data.size(); index++) {
                std::print("{:08X} ", this->pixel_data.at(index));

                if (((index + 1) % this->image_width) == 0)
                {std::print("\n\t");}
        }
        std::println("]");
}

int32_t k::BMPReader::getWidth()
{return this->image_width;}

int32_t k::BMPReader::getHeight()
{return this->image_height;}

void k::BMPReader::populateBMPData() {
        this->pixel_data_offset = this->getFourBytesLittleEndian(10);

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

void k::BMPReader::populatePixelData() {
        switch (this->bits_per_pixel) {
                case 1:  this->process1Bit();  break;
                case 2:  this->process2Bit();  break;
                case 4:  this->process4Bit();  break;
                case 8:  this->process8Bit();  break;
                case 16: this->process16Bit(); break;
                case 24: this->process24Bit(); break;
                case 32: this->process32Bit(); break;
        }
}

void k::BMPReader::process1Bit() {
        size_t pixel_data_index = this->pixel_data_offset;

        int32_t bytes_per_row = (this->image_width + 1) / 8;
        int32_t padding = (4 - (bytes_per_row % 4)) % 4;

        size_t pixels_read = 0;
        for (size_t image_row = 0; image_row < this->image_height; image_row++) {
                pixels_read = 0;

                for (size_t byte_count = 0; byte_count < bytes_per_row; byte_count++) {
                        std::bitset<8> bitset = k::tools::toBitset(this->getByte(pixel_data_index++));

                        for (uint8_t index = 0; (index < bitset.size() && (pixels_read < this->image_width)); index++)
                        {this->pixel_data.push_back(bitset[index]); pixels_read++;}
                }

                pixel_data_index += padding;
        }
}

void k::BMPReader::process2Bit() {
        size_t pixel_data_index = this->pixel_data_offset;

        int32_t bytes_per_row = (this->image_width + 1) / 4;
        int32_t padding = (4 - (bytes_per_row % 4)) % 4;

        size_t pixels_read = 0;
        for (size_t image_row = 0; image_row < this->image_height; image_row++) {
                pixels_read = 0;

                for (size_t byte_count = 0; byte_count < bytes_per_row; byte_count++) {
                        std::byte byte = this->getByte(pixel_data_index++);

                        uint8_t color_index_1 = (static_cast<uint8_t>(byte) >> 6) & 0b00000011;
                        uint8_t color_index_2 = (static_cast<uint8_t>(byte) >> 4) & 0b00000011;
                        uint8_t color_index_3 = (static_cast<uint8_t>(byte) >> 2) & 0b00000011;
                        uint8_t color_index_4 =  static_cast<uint8_t>(byte)       & 0b00000011;

                        if (pixels_read < this->image_width)
                        {this->pixel_data.push_back(this->color_table.at(color_index_1)); pixels_read++;}
                        if (pixels_read < this->image_width)
                        {this->pixel_data.push_back(this->color_table.at(color_index_2)); pixels_read++;}
                        if (pixels_read < this->image_width)
                        {this->pixel_data.push_back(this->color_table.at(color_index_3)); pixels_read++;}
                        if (pixels_read < this->image_width)
                        {this->pixel_data.push_back(this->color_table.at(color_index_4)); pixels_read++;}
                }

                pixel_data_index += padding;
        }
}

void k::BMPReader::process4Bit() {
        size_t pixel_data_index = this->pixel_data_offset;

        int32_t bytes_per_row = (this->image_width + 1) / 2;
        int32_t padding = (4 - (bytes_per_row % 4)) % 4;

        size_t pixels_read = 0;
        for (size_t image_row = 0; image_row < this->image_height; image_row++) {
                pixels_read = 0;

                for (size_t byte_count = 0; byte_count < bytes_per_row; byte_count++) {
                        std::byte byte = this->getByte(pixel_data_index++);

                        uint8_t color_index_1 = (static_cast<uint8_t>(byte) >> 4) & 0b00001111;
                        uint8_t color_index_2 =  static_cast<uint8_t>(byte)       & 0b00001111;

                        if (pixels_read < this->image_width)
                        {this->pixel_data.push_back(this->color_table.at(color_index_1)); pixels_read++;}
                        if (pixels_read < this->image_width)
                        {this->pixel_data.push_back(this->color_table.at(color_index_2)); pixels_read++;}
                }

                pixel_data_index += padding;
        }
}

void k::BMPReader::process8Bit() {
        size_t pixel_data_index = this->pixel_data_offset;

        int32_t bytes_per_row = (this->image_width + 1) / 1;
        int32_t padding = (4 - (bytes_per_row % 4)) % 4;

        size_t pixels_read = 0;
        for (size_t image_row = 0; image_row < this->image_height; image_row++) {
                pixels_read = 0;

                for (size_t byte_count = 0; byte_count < bytes_per_row; byte_count++) {
                        std::byte byte = this->getByte(pixel_data_index++);

                        if (pixels_read < this->image_width)
                        {this->pixel_data.push_back(this->color_table.at(static_cast<uint8_t>(byte))); pixels_read++;}
                }

                pixel_data_index += padding;
        }
}

void k::BMPReader::process16Bit() {}

void k::BMPReader::process24Bit() {}

void k::BMPReader::process32Bit() {}
