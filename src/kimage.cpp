#include "kimage.hpp"
#include "imagereader.hpp"
#include <memory>

k::Image::Image(std::unique_ptr<ImageReader> reader)
{if (!this->setReder(std::move(reader))) {return;}}

k::Image::Image(std::unique_ptr<ImageReader> reader, const std::string file) {
        if (!this->setReder(std::move(reader))) {return;}
        this->load(file);
}

bool k::Image::load(const std::string file) {
        bool error_value = this->reader->load(file);
        if (!error_value) {return false;}

        return true;
}

k::image_data::Response k::Image::getResponse()
{return this->reader->getResponse();}

std::vector<unsigned char> k::Image::getRawData()
{return this->reader->getRawData();}

int32_t k::Image::getWidth()
{return this->reader->getWidth();}

int32_t k::Image::getHeight()
{return this->reader->getHeight();}

void k::Image::printData()
{this->reader->printData();}

bool k::Image::setReder(std::unique_ptr<ImageReader> reader) {
        this->reader = std::move(reader);
        if (this->reader == nullptr) {return false;}
        return true;
}
