#include "imagereader/bmp.hpp"
#include "imagereader.hpp"

#include <cstddef>
#include <fstream>
#include <ios>
#include <print>
#include <string>

bool k::BMPReader::load(const std::string file_name) {
        std::ifstream binary_file(file_name, std::ios::binary);

        if (!binary_file.is_open())
        {return false;}

        this->populateDataFromFile(binary_file);
        this->populateInformation();

        binary_file.close();

        return true;
}

k::image_data::Response k::BMPReader::getData() {
        std::println("TODO: BMP getData");

        image_data::Response response;
        response.type = image_data::DATA;
        response.information = this->data;

        return response;
}

void k::BMPReader::printData() {
        for (size_t index = 0; index < this->data.size(); index++) {
                std::print("{:02X} ", static_cast<unsigned char>(this->data.at(index)));

                if (((index + 1) % 18) == 0)
                {std::print("\n");}
        }
        std::print("\n");

        std::println("signature               : {:>10}", this->header.signature);
        std::println("file_size               : {:>10}", this->header.file_size);
        std::println("reserved                : {:>10}", this->header.reserved);
        std::println("raster_data_offset      : {:>10}", this->header.raster_data_offset);
        std::println("info_header_size        : {:>10}", this->info_header.info_header_size);
        std::println("bitmap_width            : {:>10}", this->info_header.bitmap_width);
        std::println("bitmap_height           : {:>10}", this->info_header.bitmap_height);
        std::println("plane_amount            : {:>10}", this->info_header.plane_amount);
        std::println("bits_per_pixel          : {:>10}", this->info_header.bits_per_pixel);
        std::println("compression_type        : {:>10}", this->info_header.compression_type);
        std::println("image_size              : {:>10}", this->info_header.image_size);
        std::println("horizontal_resolution   : {:>10}", this->info_header.horizontal_resolution);
        std::println("vertical_resolution     : {:>10}", this->info_header.vertical_resolution);
        std::println("amount_colors_used      : {:>10}", this->info_header.amount_colors_used);
        std::println("amount_important_colors : {:>10}", this->info_header.amount_important_colors);

        for (size_t index = 0; index < this->raster_data.size(); index++) {
                std::print("{:02X}", static_cast<unsigned char>(this->raster_data.at(index)));

                if (((index + 1) % 10) == 0)
                {std::print("\n");}
        }
}

void k::BMPReader::populateInformation() {
        this->populateHeader();
        this->populateInfoHeader();
        this->populateRasterData();
}

void k::BMPReader::populateHeader() {
        this->header.signature          = this->getNextTwoBytesLSB();
        this->header.file_size          = this->getNextFourBytesLSB();
        this->header.reserved           = this->getNextFourBytesLSB();
        this->header.raster_data_offset = this->getNextFourBytesLSB();
}

void  k::BMPReader::populateColorTable() {
        this->info_header.color_table.resize(this->number_of_colors);

        for (size_t index = 0; index < this->info_header.color_table.size(); index++) {
                this->info_header.color_table[index] = this->getNextFourBytesLSB();
        }
}

void k::BMPReader::populateInfoHeader() {
        this->info_header.info_header_size        = this->getNextFourBytesLSB();
        this->info_header.bitmap_width            = this->getNextFourBytesLSB();
        this->info_header.bitmap_height           = this->getNextFourBytesLSB();
        this->info_header.plane_amount            = this->getNextTwoBytesLSB();
        this->info_header.bits_per_pixel          = this->getNextTwoBytesLSB();
        this->info_header.compression_type        = this->getNextFourBytesLSB();
        this->info_header.image_size              = this->getNextFourBytesLSB();
        this->info_header.horizontal_resolution   = this->getNextFourBytesLSB();
        this->info_header.vertical_resolution     = this->getNextFourBytesLSB();
        this->info_header.amount_colors_used      = this->getNextFourBytesLSB();
        this->info_header.amount_important_colors = this->getNextFourBytesLSB();

        if (this->info_header.bits_per_pixel == 1) {this->number_of_colors = 1;}
        else if (this->info_header.bits_per_pixel == 4) {this->number_of_colors = 16;}
        else if (this->info_header.bits_per_pixel == 8) {this->number_of_colors = 256;}
        else {this->number_of_colors = 65536;}

        if (this->info_header.bits_per_pixel <= 8) {this->populateColorTable();}
        else {this->info_header.color_table.resize(0);}
}

void k::BMPReader::populateRasterData() {
        this->raster_data.resize(this->info_header.image_size);

        for (size_t index = 0; index < this->raster_data.size(); index++) {
                this->raster_data[index] = this->getNextByte();
        }
}
