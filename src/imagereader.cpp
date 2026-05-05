#include "imagereader.hpp"
#include <cstddef>
#include <cstdint>

bool k::ImageReader::populateDataFromFile(std::ifstream &file) {
        file.seekg(0, std::ios::end);
        std::streamsize file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        if (file_size <= 0) {return false;}
        this->data.resize(file_size);

        for (size_t index = 0; index < this->data.size(); index++) {
                char current_byte;
                file.get(current_byte);

                this->data[index] = std::byte(current_byte);
        }

        return true;
}

std::byte k::ImageReader::getByte(size_t offset) {
        if (offset > this->data.size() || offset > this->data.size())
        {return std::byte(0);}
        return this->data.at(offset);
}

uint16_t k::ImageReader::getTwoBytesBigEndian(size_t offset) {
        return  static_cast<uint16_t>(this->getByte(offset)) << 8 |
                static_cast<uint16_t>(this->getByte(offset + 1));
}

uint32_t k::ImageReader::getFourBytesBigEndian(size_t offset) {
        return  static_cast<uint32_t>(this->getTwoBytesBigEndian(offset)) << 16 |
                static_cast<uint32_t>(this->getTwoBytesBigEndian(offset + 2));
}

uint16_t k::ImageReader::getTwoBytesLittleEndian(size_t offset) {
        std::byte first_byte = this->getByte(offset);
        std::byte second_byte = this->getByte(offset + 1);

        return  static_cast<uint16_t>(second_byte) << 8 |
                static_cast<uint16_t>(first_byte);
}

uint32_t k::ImageReader::getFourBytesLittleEndian(size_t offset) {
        uint16_t front_bytes = this->getTwoBytesLittleEndian(offset);
        uint16_t back_bytes = this->getTwoBytesLittleEndian(offset + 2);

        return  static_cast<uint32_t>(back_bytes) << 16 |
                static_cast<uint32_t>(front_bytes);
}
