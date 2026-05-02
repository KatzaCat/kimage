#include "tools/to_int.hpp"

#include <cstdint>

uint16_t k::tool::toUint16LSB(std::byte byte1, std::byte byte2) {
        uint16_t return_value = 0;
        return_value = (static_cast<uint16_t>(byte2) << 8) | static_cast<uint16_t>(byte1);
        return return_value;
}

uint32_t k::tool::toUint32LSB(std::byte byte1, std::byte byte2, std::byte byte3, std::byte byte4) {
        uint32_t return_value = 0;
        uint16_t front_bytes = 0;
        uint16_t back_bytes = 0;
        front_bytes = (static_cast<uint16_t>(byte4) << 8) | static_cast<uint16_t>(byte3);
        back_bytes = (static_cast<uint16_t>(byte2) << 8) | static_cast<uint16_t>(byte1);
        return_value = (static_cast<uint32_t>(front_bytes) << 16) | static_cast<uint32_t>(back_bytes);
        return return_value;
}

uint16_t k::tool::toUint16MSB(std::byte byte1, std::byte byte2) {
        uint16_t return_value = 0;
        return_value = (static_cast<uint16_t>(byte1) << 8) | static_cast<uint16_t>(byte2);
        return return_value;
}

uint32_t k::tool::toUint32MSB(std::byte byte1, std::byte byte2, std::byte byte3, std::byte byte4) {
        uint32_t return_value = 0;
        uint16_t front_bytes = 0;
        uint16_t back_bytes = 0;
        front_bytes = (static_cast<uint16_t>(byte1) << 8) | static_cast<uint16_t>(byte2);
        back_bytes = (static_cast<uint16_t>(byte3) << 8) | static_cast<uint16_t>(byte4);
        return_value = (static_cast<uint32_t>(front_bytes) << 16) | static_cast<uint32_t>(back_bytes);
        return return_value;
}
