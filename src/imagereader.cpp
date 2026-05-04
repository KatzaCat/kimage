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

std::byte k::ImageReader::getCurrentByte() {
        std::byte current_byte = std::byte(0);

        if (this->data_index > this->data.size())
        {return std::byte(0);}

        current_byte = this->data.at(this->data_index);
        this->data_index += 1;

        return current_byte;
}

uint16_t k::ImageReader::getCurrentTwoBytesBigEndian() {
        return  static_cast<uint16_t>(this->getCurrentByte()) << 8 |
                static_cast<uint16_t>(this->getCurrentByte());
}

uint32_t k::ImageReader::getCurrentFourBytesBigEndian() {
        return  static_cast<uint32_t>(this->getCurrentTwoBytesBigEndian()) << 16 |
                static_cast<uint32_t>(this->getCurrentTwoBytesBigEndian());
}

uint16_t k::ImageReader::getCurrentTwoBytesLittleEndian() {
        std::byte first_byte = this->getCurrentByte();
        std::byte second_byte = this->getCurrentByte();

        return  static_cast<uint16_t>(second_byte) << 8 |
                static_cast<uint16_t>(first_byte);
}

uint32_t k::ImageReader::getCurrentFourBytesLittleEndian() {
        uint16_t front_bytes = this->getCurrentTwoBytesLittleEndian();
        uint16_t back_bytes = this->getCurrentTwoBytesLittleEndian();

        return  static_cast<uint32_t>(back_bytes) << 16 |
                static_cast<uint32_t>(front_bytes);
}
