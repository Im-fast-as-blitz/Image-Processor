#pragma once

#include "base_filter.h"
#include "grayscale_filter.h"

class EdgeDetection : public Filter {
public:
    EdgeDetection(double threshold);
    Image Apply(const Image& image) override;

private:
    double threshold_;
    const std::vector<double> matrix_ = {0, -1, 0, -1, 4, -1, 0, -1, 0};
};
