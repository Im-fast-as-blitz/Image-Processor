#pragma once

#include "image.h"

#include <vector>

class Filter {
public:
    virtual Image Apply(const Image& image) = 0;

    virtual ~Filter() {
    }

    Image::Pixel MultiplyMatrix(const Image& image, size_t y_pos, size_t x_pos, std::vector<double> matrix);
};
