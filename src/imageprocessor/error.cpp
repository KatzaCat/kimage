#include "imageprocessor/error.hpp"

#include <vector>

bool k::ErrorProcessor::load(const std::string file_name) {return false;}

std::vector<unsigned char> k::ErrorProcessor::getData() {
        std::vector<unsigned char> unsupported_image = {};

        unsupported_image.push_back(static_cast<unsigned char>(0xFF));
        unsupported_image.push_back(static_cast<unsigned char>(0x00));
        unsupported_image.push_back(static_cast<unsigned char>(0xFF));
        unsupported_image.push_back(static_cast<unsigned char>(0xFF));

        unsupported_image.push_back(static_cast<unsigned char>(0x00));
        unsupported_image.push_back(static_cast<unsigned char>(0x00));
        unsupported_image.push_back(static_cast<unsigned char>(0x00));
        unsupported_image.push_back(static_cast<unsigned char>(0xFF));

        unsupported_image.push_back(static_cast<unsigned char>(0x00));
        unsupported_image.push_back(static_cast<unsigned char>(0x00));
        unsupported_image.push_back(static_cast<unsigned char>(0x00));
        unsupported_image.push_back(static_cast<unsigned char>(0xFF));

        unsupported_image.push_back(static_cast<unsigned char>(0xFF));
        unsupported_image.push_back(static_cast<unsigned char>(0x00));
        unsupported_image.push_back(static_cast<unsigned char>(0xFF));
        unsupported_image.push_back(static_cast<unsigned char>(0xFF));

        return unsupported_image;
}

int32_t k::ErrorProcessor::getWidth() {return 2;}

int32_t k::ErrorProcessor::getHeight() {return 2;}
