#include "imagereader.hpp"
#include "tools/to_int.hpp"
#include <cstddef>
#include <print>

void k::ImageReader::populateDataFromFile(std::ifstream &file) {
        file.seekg(0, std::ios::end);
        std::streamsize file_size = file.tellg();
        file.seekg(0, std::ios::beg);

        this->data.resize(file_size);

        for (size_t index = 0; index < file_size; index++) {
                char current_byte;
                file.get(current_byte);

                this->data[index] = std::byte(current_byte);
        }
}

std::byte k::ImageReader::getNextByte() {
        std::byte return_value = {};

        return_value = this->data.at(this->byte_index);

        this->byte_index += 1;

        return return_value;
}

uint16_t k::ImageReader::getNextTwoBytesLSB() {
        uint16_t return_value = 0;

        if ((this->byte_index + 1) >= this->data.size()) {
                std::print("byte index out of bounds, cant access {}", this->byte_index + 1);
                exit(-1);
                return return_value;
        }

        return_value = tool::toUint16LSB(
                this->data.at(this->byte_index),
                this->data.at(this->byte_index + 1));

        this->byte_index += 2;

        return return_value;
}

uint32_t k::ImageReader::getNextFourBytesLSB() {
        uint32_t return_value = 0;

        if ((this->byte_index + 3) >= this->data.size()) {
                std::print("byte index out of bounds, cant access {}", this->byte_index + 3);
                exit(-1);
                return return_value;
        }

        return_value = tool::toUint32LSB(
                this->data.at(this->byte_index),
                this->data.at(this->byte_index + 1),
                this->data.at(this->byte_index + 2),
                this->data.at(this->byte_index + 3));

        this->byte_index += 4;

        return return_value;
}

uint16_t k::ImageReader::getNextTwoBytesMSB() {
        uint16_t return_value = 0;

        if ((this->byte_index + 1) >= this->data.size()) {
                std::print("byte index out of bounds, cant access {}", this->byte_index + 1);
                exit(-1);
                return return_value;
        }

        return_value = tool::toUint16MSB(
                this->data.at(this->byte_index),
                this->data.at(this->byte_index + 1));

        this->byte_index += 2;

        return return_value;
}

uint32_t k::ImageReader::getNextFourBytesMSB() {
        uint32_t return_value = 0;

        if ((this->byte_index + 3) >= this->data.size()) {
                std::print("byte index out of bounds, cant access {}", this->byte_index + 3);
                exit(-1);
                return return_value;
        }

        return_value = tool::toUint32MSB(
                this->data.at(this->byte_index),
                this->data.at(this->byte_index + 1),
                this->data.at(this->byte_index + 2),
                this->data.at(this->byte_index + 3));

        this->byte_index += 4;

        return return_value;
}
