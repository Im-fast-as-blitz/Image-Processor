#pragma once

#include "base_filter.h"

class Grayscale : public Filter {
public:
    Image Apply(const Image& image) override;
};
