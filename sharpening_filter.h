#pragma once

#include "base_filter.h"

class Sharpening : public Filter {
public:
    Image Apply(const Image& image) override;

private:
    const std::vector<double> matrix_ = {0, -1, 0, -1, 5, -1, 0, -1, 0};
};
