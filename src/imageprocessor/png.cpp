#include "imageprocessor/png.hpp"
#include "tools/int_type.hpp"

#include <cstddef>
#include <cstdint>
#include <fstream>
#include <print>

#define INFORMATION_HEADER 0x49484452
#define IMAGE_DATA         0x49444154

// debug
std::string _u32ToString(uint32_t number) {
        char byte1 = (number >> 24) & 0b11111111;
        char byte2 = (number >> 16) & 0b11111111;
        char byte3 = (number >> 8)  & 0b11111111;
        char byte4 = (number)       & 0b11111111;

        std::string string{byte1, byte2, byte3, byte4};

        return string;
}

bool k::PNGProcessor::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        if (!this->data.populateFromFile(binary_file))
        {return false;}
        if (!this->isValid()) {
                std::println(stderr, "File is not a valid PNG file");
                return false;
        }

        this->loadChunks();

        // debug
        for (size_t index = 0; index < this->chunks.size(); index++) {
                std::println("Length : {:08X}", this->chunks.at(index).length);
                std::println("Type   : {}", _u32ToString(this->chunks.at(index).type));

                std::print("Data   : ");
                for (size_t data_index = 0; data_index < this->chunks.at(index).data.size(); data_index++) {
                        std::print("{:02X} ", static_cast<unsigned char>(this->chunks.at(index).data.at(data_index)));
                }
                std::println("");

                std::println("C.R.C  : {:08X}", this->chunks.at(index).crc);

                std::println("");
        }

        if (!this->processChunks()) {
                std::println(stderr, "Failed to process chunks");
                return false;
        }

        // debug
        std::println("Bit Depth          : {}", static_cast<unsigned char>(this->bit_depth));
        std::println("Color Type         : {}", static_cast<unsigned char>(this->image_type));
        std::println("Compression Method : {}", static_cast<unsigned char>(this->compression_method));
        std::println("Filter Method      : {}", static_cast<unsigned char>(this->filter_method));
        std::println("Interlace Method   : {}", static_cast<unsigned char>(this->interlace_method));

        binary_file.close();

        return true;
}

std::vector<unsigned char> k::PNGProcessor::getData() 
{return this->data.format(this->getWidth(), this->getHeight());}

int32_t k::PNGProcessor::getWidth()
{return this->width;}

int32_t k::PNGProcessor::getHeight()
{return this->height;}

std::string k::PNGProcessor::getName() 
{return "PNG Processor";}

bool k::PNGProcessor::isValid() {
        if (static_cast<unsigned char>(this->data.getByte(0)) != 0x89) {return false;}
        if (static_cast<unsigned char>(this->data.getByte(1)) != 'P')  {return false;}
        if (static_cast<unsigned char>(this->data.getByte(2)) != 'N')  {return false;}
        if (static_cast<unsigned char>(this->data.getByte(3)) != 'G')  {return false;}
        if (static_cast<unsigned char>(this->data.getByte(4)) != 0x0D) {return false;}
        if (static_cast<unsigned char>(this->data.getByte(5)) != 0x0A) {return false;}
        if (static_cast<unsigned char>(this->data.getByte(6)) != 0x1A) {return false;}
        if (static_cast<unsigned char>(this->data.getByte(7)) != 0x0A) {return false;}

        return true;
}

void k::PNGProcessor::loadChunks() {
        size_t increment = 0;

        for (size_t index = 8; index < this->data.getByteArraySize(); index += increment) {
                increment = 0;
                png::Chunk chunk = {};
                
                chunk.length = k::tools::toInt32(
                        k::tools::toInt16(this->data.getByte(index),     this->data.getByte(index + 1)),
                        k::tools::toInt16(this->data.getByte(index + 2), this->data.getByte(index + 3))
                );
                increment += 4;

                chunk.type = k::tools::toInt32(
                        k::tools::toInt16(this->data.getByte(increment + index),     this->data.getByte(increment + index + 1)),
                        k::tools::toInt16(this->data.getByte(increment + index + 2), this->data.getByte(increment + index + 3))
                );
                increment += 4;

                for (size_t data_index = 0; data_index < chunk.length; data_index++) 
                {chunk.data.push_back(this->data.getByte((increment + index) + data_index));}
                increment += chunk.length;

                chunk.crc = k::tools::toInt32(
                        k::tools::toInt16(this->data.getByte(increment + index),     this->data.getByte(increment + index + 1)),
                        k::tools::toInt16(this->data.getByte(increment + index + 2), this->data.getByte(increment + index + 3))
                );
                increment += 4;

                this->chunks.push_back(chunk);
        }
}

bool k::PNGProcessor::processChunks() {
        bool return_value = true;
        for (size_t index = 0; index < this->chunks.size(); index++) {
                switch (this->chunks.at(index).type) {
                        case INFORMATION_HEADER: return_value = this->processInformationHeader(index); break;
                        case IMAGE_DATA:         return_value = this->processImageData(index);         break;

                        default: break;
                }
        }

        return return_value;
}

static k::png::ImageType _getImageType(int color_type) {
        k::png::ImageType type = k::png::ImageType::Error;

        switch (color_type) {
                case 0: type = k::png::ImageType::Greyscale;          break;
                case 2: type = k::png::ImageType::Truecolor;          break;
                case 3: type = k::png::ImageType::Indexed;            break;
                case 4: type = k::png::ImageType::GreyscaleWithAlpha; break;
                case 6: type = k::png::ImageType::TrueColorWithAlpha; break;

                default: type = k::png::ImageType::Error; break;
        }

        return type;
}

static bool _isValidImageType(k::png::ImageType image_type, std::byte bit_depth) {
        int depth = static_cast<int>(bit_depth);

        switch (image_type) {
                case k::png::ImageType::Greyscale:                                                       return true;   break;
                case k::png::ImageType::Truecolor:          if (depth == 1 || depth == 2 || depth == 4) {return false;} break;
                case k::png::ImageType::Indexed:            if (depth == 16)                            {return false;} break;
                case k::png::ImageType::GreyscaleWithAlpha: if (depth == 1 || depth == 2 || depth == 4) {return false;} break;
                case k::png::ImageType::TrueColorWithAlpha: if (depth == 1 || depth == 2 || depth == 4) {return false;} break;
                case k::png::ImageType::Error:                                                           return false;  break;
        }

        return true;
}

bool k::PNGProcessor::processInformationHeader(size_t index) {
        this->width = k::tools::toInt32(
                k::tools::toInt16(this->chunks.at(index).data.at(0), this->chunks.at(index).data.at(1)),
                k::tools::toInt16(this->chunks.at(index).data.at(2), this->chunks.at(index).data.at(3))
        );
        this->height = k::tools::toInt32(
                k::tools::toInt16(this->chunks.at(index).data.at(4), this->chunks.at(index).data.at(5)),
                k::tools::toInt16(this->chunks.at(index).data.at(6), this->chunks.at(index).data.at(7))
        );

        this->bit_depth = this->chunks.at(index).data.at(8);
        this->image_type = _getImageType(static_cast<int>(this->chunks.at(index).data.at(9)));
        if (!_isValidImageType(this->image_type, this->bit_depth)) {return false;}

        this->compression_method = this->chunks.at(index).data.at(10);
        this->filter_method = this->chunks.at(index).data.at(11);
        this->interlace_method = this->chunks.at(index).data.at(12); 

        return true;
}



bool k::PNGProcessor::processImageData(size_t index) {
        Data data = this->chunks.at(index).data;

        std::byte compression_method_and_flags = data.at(0);
        uint8_t data_compression_method = (static_cast<uint8_t>(compression_method_and_flags) >> 5) & 0b11111111;
        uint8_t data_compression_information = static_cast<uint8_t>(compression_method_and_flags) & 0b00011111;

        std::println("data_compression_method      : {}", data_compression_method);
        std::println("data_compression_information : {}", data_compression_information);


        return true;
}
