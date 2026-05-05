#pragma once

#include <bitset>
#include <cstddef>
#include <cstdint>

namespace k {
        namespace tools {
                uint16_t toInt16(std::byte byte1, std::byte byte2);
                uint32_t toInt32(uint16_t frount, uint16_t back);

                std::bitset<8> toBitset(std::byte byte);
        }
}
