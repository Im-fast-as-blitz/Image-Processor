#include "edge_detection_filter.h"

EdgeDetection::EdgeDetection(double threshold) {
    if (threshold > 1) {
        threshold /= 255;
    }
    threshold_ = threshold;
}

Image EdgeDetection::Apply(const Image& image) {
    Image new_image(image);

    Grayscale filter_gs;
    new_image = filter_gs.Apply(new_image);

    for (size_t h = 0; h < new_image.height_; ++h) {
        for (size_t w = 0; w < new_image.width_; ++w) {
            new_image.pixels_[h][w] = MultiplyMatrix(image, h, w, matrix_);

            double value = (new_image.pixels_[h][w].blue_ > threshold_) ? 1. : 0.;
            new_image.pixels_[h][w].blue_ = value;
            new_image.pixels_[h][w].green_ = value;
            new_image.pixels_[h][w].red_ = value;
        }
    }

    return new_image;
}