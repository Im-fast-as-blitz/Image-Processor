#include "negative_filter.h"

Image Negative::Apply(const Image& image) {
    Image new_image(image);

    for (size_t h = 0; h < new_image.height_; ++h) {
        for (size_t w = 0; w < new_image.width_; ++w) {
            new_image.pixels_[h][w].blue_ = 1 - new_image.pixels_[h][w].blue_;
            new_image.pixels_[h][w].green_ = 1 - new_image.pixels_[h][w].green_;
            new_image.pixels_[h][w].red_ = 1 - new_image.pixels_[h][w].red_;
        }
    }

    return new_image;
}
