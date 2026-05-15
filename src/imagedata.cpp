#include "imagedata.hpp"

#include "tools/int_type.hpp"

bool k::ImageData::populateFromFile(std::ifstream &file) {
        file.seekg(0, std::ios::end);
        std::streamsize file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (file_size <= 0) {return false;}
        this->bytes.resize(file_size);

        for (size_t index = 0; index < this->bytes.size(); index++) {
                char current_byte;
                file.get(current_byte);

                this->bytes[index] = std::byte(current_byte);
        }

        return true;
}

void k::ImageData::pushPixel(uint32_t pixel)
{this->pixels.push_back(pixel);}

std::vector<unsigned char> k::ImageData::format(int32_t width, int32_t height) {
        std::vector<unsigned char> raw_data;

        for (size_t y_index = height; y_index > 0; y_index--) {
                for (size_t x_index = 0; x_index < width; x_index++) {
                        uint32_t pixel = this->pixels.at(((y_index - 1) * width) + x_index);

                        unsigned char red   = static_cast<unsigned char>((pixel >> 24) & 0b11111111);
                        unsigned char green = static_cast<unsigned char>((pixel >> 16) & 0b11111111);
                        unsigned char blue  = static_cast<unsigned char>((pixel >> 8)  & 0b11111111);
                        unsigned char alfa  = static_cast<unsigned char>( pixel        & 0b11111111);

                        raw_data.push_back(red);
                        raw_data.push_back(green);
                        raw_data.push_back(blue);
                        raw_data.push_back(alfa);
                }
        }

        return raw_data;
}

std::byte k::ImageData::getByte(size_t offset) {
        if (offset >= this->bytes.size() || offset < 0)
        {return std::byte(0);}
        return this->bytes.at(offset);
}

uint16_t k::ImageData::getTwoBytesBigEndian(size_t offset)
{return tools::toInt16(this->getByte(offset), this->getByte(offset + 1));}

uint32_t k::ImageData::getFourBytesBigEndian(size_t offset) {
        return  tools::toInt32(
                this->getFourBytesBigEndian(offset),
                this->getFourBytesBigEndian(offset + 2)
        );
}

uint16_t k::ImageData::getTwoBytesLittleEndian(size_t offset) {
        std::byte first_byte = this->getByte(offset);
        std::byte second_byte = this->getByte(offset + 1);

        return tools::toInt16(second_byte, first_byte);
}

uint32_t k::ImageData::getFourBytesLittleEndian(size_t offset) {
        uint16_t front_bytes = this->getTwoBytesLittleEndian(offset);
        uint16_t back_bytes = this->getTwoBytesLittleEndian(offset + 2);

        return  tools::toInt32(back_bytes, front_bytes);
}
