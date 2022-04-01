#include "sharpening_filter.h"

Image Sharpening::Apply(const Image& image) {
    Image new_image(image);

    for (size_t h = 0; h < new_image.height_; ++h) {
        for (size_t w = 0; w < new_image.width_; ++w) {
            new_image.pixels_[h][w] = MultiplyMatrix(image, h, w, matrix_);
        }
    }

    return new_image;
}
