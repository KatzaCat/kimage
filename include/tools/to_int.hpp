#pragma once

#include <cstddef>
#include <cstdint>

namespace k {
        namespace tool {
                uint16_t toUint16LSB(std::byte byte1, std::byte byte2);
                uint32_t toUint32LSB(std::byte byte1, std::byte byte2, std::byte byte3, std::byte byte4);

                uint16_t toUint16MSB(std::byte byte1, std::byte byte2);
                uint32_t toUint32MSB(std::byte byte1, std::byte byte2, std::byte byte3, std::byte byte4);
        }
}
