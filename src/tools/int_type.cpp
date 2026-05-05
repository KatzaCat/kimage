#include "tools/int_type.hpp"
#include <cstdint>

uint16_t k::tools::toInt16(std::byte byte1, std::byte byte2) {
        uint16_t return_value = 0;

        return_value =
                static_cast<uint16_t>(byte1) << 8 |
                static_cast<uint16_t>(byte2);

        return return_value;
}

uint32_t k::tools::toInt32(uint16_t frount, uint16_t back) {
        uint32_t return_value = 0;

        return_value =
                static_cast<uint32_t>(frount) << 16 |
                static_cast<uint32_t>(back);

        return return_value;
}
