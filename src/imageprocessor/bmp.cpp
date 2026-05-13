#include "imageprocessor/bmp.hpp"
#include "tools/int_type.hpp"

#include <bitset>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <ios>
#include <string>
#include <vector>

bool k::BMPProcessor::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        this->populateDataFromFile(binary_file);
        this->populateColorTable();
        this->populatePixelData();

        binary_file.close();

        return true;
}

int32_t k::BMPProcessor::getWidth()
{return this->getFourBytesLittleEndian(18);}

int32_t k::BMPProcessor::getHeight()
{return this->getFourBytesLittleEndian(22);}

int32_t k::BMPProcessor::getBitsPerPixel()
{return this->getTwoBytesLittleEndian(28);}

void k::BMPProcessor::populateColorTable() {
        if (this->getBitsPerPixel() > 8) {
                this->color_table.resize(0);
                return;
        }

        size_t offset = 54;
        size_t bytes_per_entry = 4;
        uint32_t compression_level = this->getFourBytesLittleEndian(30);

        this->color_table.resize(std::pow(2, this->getBitsPerPixel()));

        size_t compression_offset_adition = 0;
        if      (compression_level == 3) {compression_offset_adition = 12;}
        else if (compression_level == 6) {compression_offset_adition = 16;}
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

void k::BMPProcessor::populatePixelData() {
        this->bytes_per_row = (this->getWidth() * this->getBitsPerPixel() + 7) / 8;

        switch (this->getBitsPerPixel()) {
                case 1:  this->processPixelBytes([this]() {this->bytes_per_pixel = 1; this->process1Bit();});  break;
                case 2:  this->processPixelBytes([this]() {this->bytes_per_pixel = 1; this->process2Bit();});  break;
                case 4:  this->processPixelBytes([this]() {this->bytes_per_pixel = 1; this->process4Bit();});  break;
                case 8:  this->processPixelBytes([this]() {this->bytes_per_pixel = 1; this->process8Bit();});  break;
                case 16: this->processPixelBytes([this]() {this->bytes_per_pixel = 2; this->process16Bit();}); break;
                case 24: this->processPixelBytes([this]() {this->bytes_per_pixel = 3; this->process24Bit();}); break;
                case 32: this->processPixelBytes([this]() {this->bytes_per_pixel = 4; this->process32Bit();}); break;
        }
}

void k::BMPProcessor::processPixelBytes(std::function<void()> function) {
        int32_t pixel_data_padding = (4 - (this->bytes_per_row % 4)) % 4;

        this->pixel_data_index = this->getFourBytesLittleEndian(10);
        for (size_t row_index = 0; row_index < this->getHeight(); row_index++) {
                this->pixels_read = 0;

                for (size_t byte_index = 0; byte_index < bytes_per_row; byte_index += this->bytes_per_pixel)
                {function();}

                pixel_data_index += pixel_data_padding;
        }
}

void k::BMPProcessor::process1Bit() {
        std::bitset<8> bitset = k::tools::toBitset(this->getByte(this->pixel_data_index++));

        for (uint8_t index = 0; (index < bitset.size() && (pixels_read < this->getWidth())); index++)
        {this->pixel_data.push_back(this->color_table.at(bitset[index])); pixels_read++;}
}

void k::BMPProcessor::process2Bit() {
        std::byte byte = this->getByte(this->pixel_data_index++);

        uint8_t color_index_1 = (static_cast<uint8_t>(byte) >> 6) & 0b00000011;
        uint8_t color_index_2 = (static_cast<uint8_t>(byte) >> 4) & 0b00000011;
        uint8_t color_index_3 = (static_cast<uint8_t>(byte) >> 2) & 0b00000011;
        uint8_t color_index_4 =  static_cast<uint8_t>(byte)       & 0b00000011;

        if (pixels_read < this->getWidth())
        {this->pixel_data.push_back(this->color_table.at(color_index_1)); pixels_read++;}
        if (pixels_read < this->getWidth())
        {this->pixel_data.push_back(this->color_table.at(color_index_2)); pixels_read++;}
        if (pixels_read < this->getWidth())
        {this->pixel_data.push_back(this->color_table.at(color_index_3)); pixels_read++;}
        if (pixels_read < this->getWidth())
        {this->pixel_data.push_back(this->color_table.at(color_index_4)); pixels_read++;}
}

void k::BMPProcessor::process4Bit() {
        std::byte byte = this->getByte(this->pixel_data_index++);

        uint8_t color_index_1 = (static_cast<uint8_t>(byte) >> 4) & 0b00001111;
        uint8_t color_index_2 =  static_cast<uint8_t>(byte)       & 0b00001111;

        if (this->pixels_read < this->getWidth())
        {this->pixel_data.push_back(this->color_table.at(color_index_1)); this->pixels_read++;}
        if (this->pixels_read < this->getWidth())
        {this->pixel_data.push_back(this->color_table.at(color_index_2)); this->pixels_read++;}
}

void k::BMPProcessor::process8Bit() {
        std::byte byte = this->getByte(this->pixel_data_index++);

        if (this->pixels_read < this->getWidth())
        {this->pixel_data.push_back(this->color_table.at(static_cast<uint8_t>(byte))); this->pixels_read++;}
}

void k::BMPProcessor::process16Bit() {
        std::byte byte1 = this->getByte(this->pixel_data_index++);
        std::byte byte2 = this->getByte(this->pixel_data_index++);

        uint16_t color_data = k::tools::toInt16(byte1, byte2);

        std::byte red   = std::byte(((static_cast<uint8_t>(color_data >> 11) & 0b00011111) * 255) / 31);
        std::byte green = std::byte(((static_cast<uint8_t>(color_data >> 5)  & 0b00011111) * 255) / 31);
        std::byte blue  = std::byte(((static_cast<uint8_t>(color_data)       & 0b00011111) * 255) / 31);
        std::byte alfa  = std::byte(0xFF);

        uint16_t frount_bytes = k::tools::toInt16(red, green);
        uint16_t back_bytes = k::tools::toInt16(blue, alfa);

        if (this->pixels_read < this->getWidth())
        {this->pixel_data.push_back(k::tools::toInt32(frount_bytes, back_bytes)); this->pixels_read++;}
}

void k::BMPProcessor::process24Bit() {
        std::byte blue  = this->getByte(this->pixel_data_index++);
        std::byte green = this->getByte(this->pixel_data_index++);
        std::byte red   = this->getByte(this->pixel_data_index++);

        uint16_t frount_bytes = k::tools::toInt16(red, green);
        uint16_t back_bytes = k::tools::toInt16(blue, std::byte(0xFF));

        if (this->pixels_read < this->getWidth())
        {this->pixel_data.push_back(k::tools::toInt32(frount_bytes, back_bytes)); this->pixels_read++;}
}

void k::BMPProcessor::process32Bit() {
        std::byte blue  = this->getByte(this->pixel_data_index++);
        std::byte green = this->getByte(this->pixel_data_index++);
        std::byte red   = this->getByte(this->pixel_data_index++);
        std::byte alfa  = this->getByte(this->pixel_data_index++);

        uint16_t frount_bytes = k::tools::toInt16(red, green);
        uint16_t back_bytes = k::tools::toInt16(blue, alfa);

        this->pixel_data.push_back(k::tools::toInt32(frount_bytes, back_bytes));
}
