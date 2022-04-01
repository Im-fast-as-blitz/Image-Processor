#include "grayscale_filter.h"

Image Grayscale::Apply(const Image& image) {
    Image new_image(image);

    for (size_t h = 0; h < new_image.height_; ++h) {
        for (size_t w = 0; w < new_image.width_; ++w) {
            double new_color = 0.299 * new_image.pixels_[h][w].red_ + 0.587 * new_image.pixels_[h][w].green_ +
                               0.114 * new_image.pixels_[h][w].blue_;
            new_image.pixels_[h][w].blue_ = new_color;
            new_image.pixels_[h][w].green_ = new_color;
            new_image.pixels_[h][w].red_ = new_color;
        }
    }

    return new_image;
}
