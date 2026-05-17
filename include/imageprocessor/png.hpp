#include "imagedata.hpp"
#include "imageprocessor.hpp"
#include <cstdint>
#include <vector>

#define K_PNG_INFORMATION_HEADER 0x49484452
#define K_PNG_PALETTE            0x504C5445
#define K_PNG_IMAGE_DATA         0x49444154
#define K_PNG_IMAGE_END          0x49454E44

namespace k {
        namespace png {
                struct Chunk {
                        uint32_t length;
                        uint32_t type;
                        std::vector<std::byte> data;
                        uint32_t crc;
                };
        }

        class PNGProcessor : public ImageProcessor {
        public:
                virtual ~PNGProcessor() = default;

                virtual bool load(const std::string file_name) override;

                virtual std::vector<unsigned char> getData() override;

                virtual int32_t getWidth() override;
                virtual int32_t getHeight() override;
        private:
                ImageData data = {};
                int32_t width = 0;
                int32_t height = 0;

                std::vector<png::Chunk> chunks;

        private:
                bool loadChunks();
        };
}
