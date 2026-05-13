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

        if (!binary_file.is_open()) {
                this->response.type = image_data::ERROR;
                this->response.information = BMP_FILE_NOT_FOUND_ERROR;
                return false;
        }

        this->populateDataFromFile(binary_file);
        this->populateBMPData();
        this->populateColorTable();
        this->populatePixelData();

        binary_file.close();

        this->response.type = image_data::DATA;
        this->response.information = this->data;

        return true;
}

k::image_data::Response k::BMPReader::getResponse()
{return this->response;}

std::vector<unsigned char> k::BMPReader::getRawData() {
        std::vector<unsigned char> raw_data;

        for (size_t index = 0; index < this->pixel_data.size(); index++) {
                unsigned char red   = static_cast<unsigned char>((this->pixel_data.at(index) >> 24) & 0b11111111);
                unsigned char green = static_cast<unsigned char>((this->pixel_data.at(index) >> 16) & 0b11111111);
                unsigned char blue  = static_cast<unsigned char>((this->pixel_data.at(index) >> 8)  & 0b11111111);
                unsigned char alfa  = static_cast<unsigned char>( this->pixel_data.at(index)        & 0b11111111);

                raw_data.push_back(red);
                raw_data.push_back(green);
                raw_data.push_back(blue);
                raw_data.push_back(alfa);
        }

        return raw_data;
}

int32_t k::BMPReader::getWidth()
{return this->image_width;}

int32_t k::BMPReader::getHeight()
{return this->image_height;}

void k::BMPReader::printData() {
        for (size_t index = 0; index < this->data.size(); index++) {
                std::print("{:02X} ", static_cast<unsigned char>(this->data.at(index)));

                if (((index + 1) % 16) == 0)
                {std::print("\n");}
        }
        std::print("\n");

        std::println("Bits per Pixel     : {:8} -> 0x{:08X}", this->bits_per_pixel, this->bits_per_pixel);
        std::println("Pixel Data Offset  : {:8} -> 0x{:08X}", this->pixel_data_offset, this->pixel_data_offset);

        std::println("Image Width        : {:8} -> 0x{:08X}", this->image_width, this->image_width);
        std::println("Image Height       : {:8} -> 0x{:08X}", this->image_height, this->image_height);

        if (this->color_table.size() > 0) {
                std::println("Color Table        : [");
                for (size_t index = 0; index < this->color_table.size(); index++)
                {std::println("\t0x{:08X}, ", this->color_table.at(index));}
                std::println("]");
        }

        std::print  ("Pixel Data         : [\n\t");
        for (size_t index = 0; index < this->pixel_data.size(); index++) {
                std::print("{:08X} ", this->pixel_data.at(index));

                if (((index + 1) % this->image_width) == 0)
                {std::print("\n\t");}
        }
        std::println("]");
}

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
                        tools::toInt16(blue, std::byte(0xFF))
                );
        }
}

void k::BMPReader::populatePixelData() {
        this->bytes_per_row = (this->image_width * this->bits_per_pixel + 7) / 8;

        this->pixel_data_padding = (4 - (this->bytes_per_row % 4)) % 4;

        this->pixel_data_index = this->pixel_data_offset;

        switch (this->bits_per_pixel) {
                case 1:  this->processPixelBytes([this]() {this->bytes_per_pixel = 1; this->process1Bit();});  break;
                case 2:  this->processPixelBytes([this]() {this->bytes_per_pixel = 1; this->process2Bit();});  break;
                case 4:  this->processPixelBytes([this]() {this->bytes_per_pixel = 1; this->process4Bit();});  break;
                case 8:  this->processPixelBytes([this]() {this->bytes_per_pixel = 1; this->process8Bit();});  break;
                case 16: this->processPixelBytes([this]() {this->bytes_per_pixel = 2; this->process16Bit();}); break;
                case 24: this->processPixelBytes([this]() {this->bytes_per_pixel = 3; this->process24Bit();}); break;
                case 32: this->processPixelBytes([this]() {this->bytes_per_pixel = 4; this->process32Bit();}); break;
        }
}

void k::BMPReader::processPixelBytes(std::function<void()> function) {
        for (size_t row_index = 0; row_index < this->image_height; row_index++) {
                this->pixels_read = 0;

                for (size_t byte_index = 0; byte_index < bytes_per_row; byte_index += this->bytes_per_pixel)
                {function();}

                pixel_data_index += this->pixel_data_padding;
        }
}

void k::BMPReader::process1Bit() {
        std::bitset<8> bitset = k::tools::toBitset(this->getByte(this->pixel_data_index++));

        for (uint8_t index = 0; (index < bitset.size() && (pixels_read < this->image_width)); index++)
        {this->pixel_data.push_back(this->color_table.at(bitset[index])); pixels_read++;}
}

void k::BMPReader::process2Bit() {
        std::byte byte = this->getByte(this->pixel_data_index++);

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

void k::BMPReader::process4Bit() {
        std::byte byte = this->getByte(this->pixel_data_index++);

        uint8_t color_index_1 = (static_cast<uint8_t>(byte) >> 4) & 0b00001111;
        uint8_t color_index_2 =  static_cast<uint8_t>(byte)       & 0b00001111;

        if (this->pixels_read < this->image_width)
        {this->pixel_data.push_back(this->color_table.at(color_index_1)); this->pixels_read++;}
        if (this->pixels_read < this->image_width)
        {this->pixel_data.push_back(this->color_table.at(color_index_2)); this->pixels_read++;}
}

void k::BMPReader::process8Bit() {
        std::byte byte = this->getByte(this->pixel_data_index++);

        if (this->pixels_read < this->image_width)
        {this->pixel_data.push_back(this->color_table.at(static_cast<uint8_t>(byte))); this->pixels_read++;}
}

void k::BMPReader::process16Bit() {
        std::byte byte1 = this->getByte(this->pixel_data_index++);
        std::byte byte2 = this->getByte(this->pixel_data_index++);

        uint16_t color_data = k::tools::toInt16(byte1, byte2);

        std::byte red   = std::byte(((static_cast<uint8_t>(color_data >> 11) & 0b00011111) * 255) / 31);
        std::byte green = std::byte(((static_cast<uint8_t>(color_data >> 5)  & 0b00011111) * 255) / 31);
        std::byte blue  = std::byte(((static_cast<uint8_t>(color_data)       & 0b00011111) * 255) / 31);
        std::byte alfa  = std::byte(0xFF);

        uint16_t frount_bytes = k::tools::toInt16(red, green);
        uint16_t back_bytes = k::tools::toInt16(blue, alfa);

        if (this->pixels_read < this->image_width)
        {this->pixel_data.push_back(k::tools::toInt32(frount_bytes, back_bytes)); this->pixels_read++;}
}

void k::BMPReader::process24Bit() {
        std::byte blue  = this->getByte(this->pixel_data_index++);
        std::byte green = this->getByte(this->pixel_data_index++);
        std::byte red   = this->getByte(this->pixel_data_index++);

        uint16_t frount_bytes = k::tools::toInt16(red, green);
        uint16_t back_bytes = k::tools::toInt16(blue, std::byte(0xFF));

        if (this->pixels_read < this->image_width)
        {this->pixel_data.push_back(k::tools::toInt32(frount_bytes, back_bytes)); this->pixels_read++;}
}

void k::BMPReader::process32Bit() {
        std::byte blue  = this->getByte(this->pixel_data_index++);
        std::byte green = this->getByte(this->pixel_data_index++);
        std::byte red   = this->getByte(this->pixel_data_index++);
        std::byte alfa  = this->getByte(this->pixel_data_index++);

        uint16_t frount_bytes = k::tools::toInt16(red, green);
        uint16_t back_bytes = k::tools::toInt16(blue, alfa);

        this->pixel_data.push_back(k::tools::toInt32(frount_bytes, back_bytes));
}
