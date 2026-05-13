#include "kimage.hpp"
#include "imageprocessor.hpp"
#include <memory>

k::Image::Image(std::unique_ptr<ImageProcessor> processor)
{if (!this->setProcessor(std::move(processor))) {return;}}

k::Image::Image(std::unique_ptr<ImageProcessor> processor, const std::string file) {
        if (!this->setProcessor(std::move(processor))) {return;}
        this->load(file);
}

bool k::Image::load(const std::string file) {
        bool error_value = this->processor->load(file);
        if (!error_value) {return false;}

        return true;
}

std::vector<unsigned char> k::Image::getData()
{return this->processor->getData();}

int32_t k::Image::getWidth()
{return this->processor->getWidth();}

int32_t k::Image::getHeight()
{return this->processor->getHeight();}

bool k::Image::setProcessor(std::unique_ptr<ImageProcessor> processor) {
        this->processor = std::move(processor);
        if (this->processor == nullptr) {return false;}
        return true;
}
