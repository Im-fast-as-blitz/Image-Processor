#pragma once

#include "base_filter.h"

class Negative : public Filter {
public:
    Image Apply(const Image& image) override;
};
