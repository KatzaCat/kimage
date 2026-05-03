#include "imagereader.hpp"
#include <cstddef>

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
