#include "imagereader.hpp"
#include <cstddef>

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
