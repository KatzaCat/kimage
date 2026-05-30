#include "imagedata.hpp"
#include "imageprocessor.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>

namespace k {
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
        };
}
