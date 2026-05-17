#include "imagedata.hpp"
#include "imageprocessor.hpp"

namespace k {
        class PngProcessor : public ImageProcessor {
        public:
                virtual ~PngProcessor() = default;

                virtual bool load(const std::string file_name) override;

                virtual std::vector<unsigned char> getData() override;

                virtual int32_t getWidth() override;
                virtual int32_t getHeight() override;
        private:
                ImageData data = {};
        };
}
