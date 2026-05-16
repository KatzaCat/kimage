#pragma once

#include "../imageprocessor.hpp"

namespace k {
        class ErrorProcessor : public ImageProcessor {
        public:
                virtual ~ErrorProcessor() = default;

                virtual bool load(const std::string file_name) override;

                virtual std::vector<unsigned char> getData() override;

                virtual int32_t getWidth() override;
                virtual int32_t getHeight() override;
        };
}
