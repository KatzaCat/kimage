#include "imageprocessor/png.hpp"

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <print>

bool k::PNGProcessor::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        this->data.populateFromFile(binary_file);
        if (!this->loadChunks())
        {return false;}

        binary_file.close();

        return true;
}

std::vector<unsigned char> k::PNGProcessor::getData() {
        return {};
}

int32_t k::PNGProcessor::getWidth()
{return this->width;}

int32_t k::PNGProcessor::getHeight()
{return this->height;}

bool k::PNGProcessor::loadChunks() {
        png::Chunk chunk = {};

        for (size_t index = 8; index < this->data.getByteArraySize(); index += 12 + chunk.length) {
                chunk = {};

                chunk.length = this->data.getFourBytesBigEndian(index);
                chunk.type = this->data.getFourBytesBigEndian(index + 4);

                for (size_t data_index = 0; data_index < chunk.length; data_index++)
                {chunk.data.push_back(this->data.getByte((index + 8) + data_index));}

                chunk.crc = this->data.getFourBytesBigEndian((index + 8) + chunk.length);

                this->chunks.push_back(chunk);
        }

        return true;
}
