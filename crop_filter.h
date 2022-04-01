#pragma once

#include "base_filter.h"

class Crop : public Filter {
public:
    Crop(uint32_t width, uint32_t height) : width_(width), height_(height) {
    }

    Image Apply(const Image& image) override;

private:
    uint32_t width_;
    uint32_t height_;
};
