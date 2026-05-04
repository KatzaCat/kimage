#include "imagereader/bmp.hpp"
#include "imagereader.hpp"

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <memory>
#include <print>
#include <string>
#include <vector>

bool k::BMPReader::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        this->populateDataFromFile(binary_file);
        this->populateFileHeader();
        this->populateInformationHeader();
        this->populateColorTable();
        this->populatePixelArray();

        binary_file.close();

        return true;
}

k::image_data::Response k::BMPReader::getData() {
        std::println("TODO: BMP getData");

        image_data::Response response;
        response.type = image_data::DATA;

        std::unique_ptr<std::byte> data_pointer(this->data.data());
        response.information = std::move(data_pointer);

        return response;
}

void k::BMPReader::printData() {
        std::println("---- File in Bytes ----");

        for (size_t index = 0; index < this->data.size(); index++) {
                std::print("{:02X} ", static_cast<char>(this->data.at(index)));

                if (((index + 1) % 16) == 0) {std::print("\n");}
        }
        std::println("");

        std::println("---- Bit Map File Header ----");

        std::println("signature          : {}{}",
                static_cast<char>(this->file_header.signature[0]),
                static_cast<char>(this->file_header.signature[1])
        );
        std::println("file size          : {:5}", this->file_header.file_size);
        std::println("reserved1          : {:5}", this->file_header.reserved1);
        std::println("reserved2          : {:5}", this->file_header.reserved2);
        std::println("pixel array offset : {:5}", this->file_header.pixel_array_offset);

        std::println("---- Bit Map Information Header ----");

        std::println("header_size           : {:5}", this->information_header.header_size);
        std::println("image_width           : {:5}", this->information_header.image_width);
        std::println("image_height          : {:5}", this->information_header.image_height);
        std::println("plains                : {:5}", this->information_header.plains);
        std::println("bits_per_pixel        : {:5}", this->information_header.bits_per_pixel);
        std::println("compression           : {:5}", static_cast<int>(this->information_header.compression));
        std::println("image_size            : {:5}", this->information_header.image_size);
        std::println("horizontal_resolution : {:5}", this->information_header.horizontal_resolution);
        std::println("vertical_resolution   : {:5}", this->information_header.vertical_resolution);
        std::println("color_table_colors    : {:5}", this->information_header.color_table_colors);
        std::println("important_colors      : {:5}", this->information_header.important_colors);

        std::println("---- Color Table ----");

        std::println("color table: [");
        for (size_t index = 0; index < this->color_table.size(); index++) {
                std::println("\t0x{:02X}{:02X}{:02X},",
                        this->color_table[index].red,
                        this->color_table[index].green,
                        this->color_table[index].blue
                );
        }
        std::println("]");

}

void k::BMPReader::populateFileHeader() {
        this->file_header.signature[0] = this->getCurrentByte();
        this->file_header.signature[1] = this->getCurrentByte();

        this->file_header.file_size = this->getCurrentFourBytesLittleEndian();

        this->file_header.reserved1 = this->getCurrentTwoBytesLittleEndian();
        this->file_header.reserved2 = this->getCurrentTwoBytesLittleEndian();

        this->file_header.pixel_array_offset = this->getCurrentFourBytesLittleEndian();
}

static k::bm::Compression getCompressionFromValue(uint32_t value) {
        switch (value) {
                case 0:  return k::bm::Compression::BI_RGB;            break;
                case 1:  return k::bm::Compression::BI_RLE8;           break;
                case 2:  return k::bm::Compression::BI_RLE4;           break;
                case 3:  return k::bm::Compression::BI_BITFIELDS;      break;
                case 4:  return k::bm::Compression::BI_JPEG;           break;
                case 5:  return k::bm::Compression::BI_PNG;            break;
                case 6:  return k::bm::Compression::BI_ALPHABITFIELDS; break;
                case 11: return k::bm::Compression::BI_CMYK;           break;
                case 12: return k::bm::Compression::BI_CMYKRLE8;       break;
                case 13: return k::bm::Compression::BI_CMYKRLE4;       break;

                default: return k::bm::Compression::BI_RGB;
        }
}

void k::BMPReader::populateInformationHeader() {
        this->information_header.header_size = this->getCurrentFourBytesLittleEndian();

        this->information_header.image_width = this->getCurrentFourBytesLittleEndian();
        this->information_header.image_height = this->getCurrentFourBytesLittleEndian();

        this->information_header.plains = this->getCurrentTwoBytesLittleEndian();
        this->information_header.bits_per_pixel = this->getCurrentTwoBytesLittleEndian();

        uint32_t compression_number = this->getCurrentFourBytesLittleEndian();
        this->information_header.compression = getCompressionFromValue(compression_number);

        this->information_header.image_size = this->getCurrentFourBytesLittleEndian();
        this->information_header.horizontal_resolution = this->getCurrentFourBytesLittleEndian();
        this->information_header.vertical_resolution = this->getCurrentFourBytesLittleEndian();

        this->information_header.color_table_colors = this->getCurrentFourBytesLittleEndian();
        this->information_header.important_colors = this->getCurrentFourBytesLittleEndian();
}

void k::BMPReader::populateColorTable() {
        if (this->information_header.bits_per_pixel >= 16)
        {this->color_table.resize(0); return;}

        this->color_table.resize(this->information_header.color_table_colors);
        for (size_t index = 0; index < this->color_table.size(); index++) {
                this->color_table[index].blue  = static_cast<unsigned char>(this->getCurrentByte());
                this->color_table[index].green = static_cast<unsigned char>(this->getCurrentByte());
                this->color_table[index].red   = static_cast<unsigned char>(this->getCurrentByte());
                this->color_table[index].alfa  = static_cast<unsigned char>(this->getCurrentByte());
        }
}

void k::BMPReader::populatePixelArray() {
        size_t row_size = floor((this->information_header.bits_per_pixel * this->information_header.image_width + 31) / 32);
        size_t pixel_array_size_in_bytes = row_size * std::abs(this->information_header.image_height);

        this->pixel_array.resize(this->information_header.image_width * this->information_header.image_height);

        std::vector<std::byte> pixels_in_bytes = {};
        pixels_in_bytes.resize(pixel_array_size_in_bytes);
        for (size_t index = 0; index < pixels_in_bytes.size(); index++) {
                pixels_in_bytes.at(index) = this->getCurrentByte();
        }

        if (this->information_header.bits_per_pixel <= 8 && this->color_table.size() <= 0)
        {return;}

        switch (this->information_header.bits_per_pixel) {
                case 1:  loadPixelArrayOneBit(pixels_in_bytes);        break;
                case 2:  loadPixelArrayTwoBit(pixels_in_bytes);        break;
                case 4:  loadPixelArrayFourBit(pixels_in_bytes);       break;
                case 8:  loadPixelArrayEightBit(pixels_in_bytes);      break;
                case 16: loadPixelArraySixteenBit(pixels_in_bytes);    break;
                case 24: loadPixelArrayTwentyFourBit(pixels_in_bytes); break;
                case 32: loadPixelArrayThirtyFourBit(pixels_in_bytes); break;

                default: break;
        }
}

void k::BMPReader::loadPixelArrayOneBit(std::vector<std::byte> pixels_in_bytes) {
}

void k::BMPReader::loadPixelArrayTwoBit(std::vector<std::byte> pixels_in_bytes) {}

void k::BMPReader::loadPixelArrayFourBit(std::vector<std::byte> pixels_in_bytes) {}

void k::BMPReader::loadPixelArrayEightBit(std::vector<std::byte> pixels_in_bytes) {}

void k::BMPReader::loadPixelArraySixteenBit(std::vector<std::byte> pixels_in_bytes) {}

void k::BMPReader::loadPixelArrayTwentyFourBit(std::vector<std::byte> pixels_in_bytes) {}

void k::BMPReader::loadPixelArrayThirtyFourBit(std::vector<std::byte> pixels_in_bytes) {}
