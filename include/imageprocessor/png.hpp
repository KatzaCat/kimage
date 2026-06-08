#include "imagedata.hpp"
#include "imageprocessor.hpp"
#include <vector>

namespace k {
        namespace png {
                struct Chunk {
                        uint32_t length = 0;
                        uint32_t type = 0;
                        std::vector<std::byte> data = {};
                        uint32_t crc = 0;
                };

                enum struct ImageType : int {
                        Error,
                        Greyscale,
                        Truecolor,
                        Indexed,
                        GreyscaleWithAlpha,
                        TrueColorWithAlpha
                };
        }

        class PNGProcessor : public ImageProcessor {
        public:
                virtual ~PNGProcessor() = default;

                virtual bool load(const std::string file_name) override;

                virtual std::vector<unsigned char> getData() override;

                virtual int32_t getWidth() override;
                virtual int32_t getHeight() override;

                virtual std::string getName() override;
        private:
                ImageData data = {};
                int32_t width = 0;
                int32_t height = 0;

                std::vector<png::Chunk> chunks = {};

                std::byte bit_depth = std::byte(0);

                std::byte color_type = std::byte(0);
                png::ImageType image_type = {};

                std::byte compression_method = std::byte(0);
                std::byte filter_method = std::byte(0);
                std::byte interlace_method = std::byte(0);
        private:
                bool isValid();

                void loadChunks();
                bool processChunks();
                bool processInformationHeader(size_t index);
        };
}
