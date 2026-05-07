#include "imagereader.hpp"
#include "tools/int_type.hpp"
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
        if (offset >= this->data.size() || offset < 0)
        {return std::byte(0);}
        return this->data.at(offset);
}

uint16_t k::ImageReader::getTwoBytesBigEndian(size_t offset)
{return tools::toInt16(this->getByte(offset), this->getByte(offset + 1));}

uint32_t k::ImageReader::getFourBytesBigEndian(size_t offset) {
        return  tools::toInt32(
                this->getFourBytesBigEndian(offset),
                this->getFourBytesBigEndian(offset + 2)
        );
}

uint16_t k::ImageReader::getTwoBytesLittleEndian(size_t offset) {
        std::byte first_byte = this->getByte(offset);
        std::byte second_byte = this->getByte(offset + 1);

        return tools::toInt16(second_byte, first_byte);
}

uint32_t k::ImageReader::getFourBytesLittleEndian(size_t offset) {
        uint16_t front_bytes = this->getTwoBytesLittleEndian(offset);
        uint16_t back_bytes = this->getTwoBytesLittleEndian(offset + 2);

        return  tools::toInt32(back_bytes, front_bytes);
}
