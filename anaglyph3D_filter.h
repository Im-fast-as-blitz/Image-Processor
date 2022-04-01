#pragma once

#include "base_filter.h"
#include "crop_filter.h"

class Anaglyph3D : public Filter {
public:
    Anaglyph3D(const Image& left_image) : left_image_(left_image) {
    }

    Image Apply(const Image& right_image) override;

private:
    Image left_image_;
};
