#pragma once

#include "base_filter.h"

#include <cmath>

class GaussianBlur : public Filter {
public:
    GaussianBlur(double sigma);

    Image Apply(const Image& image) override;

    Image ApplyByWidthOrHeight(const Image& image, bool is_width);

private:
    double sigma_;
    ssize_t distance_;
    long double coefficient_;
};
