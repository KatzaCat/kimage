#include "kimage.hpp"
#include "imageprocessor.hpp"
#include "imageprocessor/bmp.hpp"
#include <cstddef>
#include <memory>

static std::unique_ptr<k::ImageProcessor> _processorFactory(std::string file) {
        size_t extetion_position = file.find_last_of('.');

        if (extetion_position != std::string::npos) {
                std::string extention = file.substr(extetion_position);

                if (extention == ".bmp" || extention == ".dib")
                {return std::make_unique<k::BMPProcessor>();}
        }

        return nullptr;
}

k::Image::Image(const std::string file)
{this->load(file);}

bool k::Image::load(const std::string file) {
        std::unique_ptr<ImageProcessor> current_processor = _processorFactory(file);
        if (!this->setProcessor(std::move(current_processor))) {return false;}

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
