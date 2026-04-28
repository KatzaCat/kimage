#include "kimage.hpp"

k::Image::Image() {}

k::Image::Image(const std::string file, ImageReader *reader)
{this->load(file, reader);}

bool k::Image::load(const std::string file, ImageReader *reader) {
        this->reader = reader;
        if (this->reader == nullptr) {return false;}

        bool error_value = this->reader->load(file);
        if (!error_value) {return false;}

        return true;
}

k::image::DataResopnce k::Image::getData()
{return this->reader->getData();}
