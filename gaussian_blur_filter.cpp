#include "gaussian_blur_filter.h"

Image GaussianBlur::Apply(const Image& image) {
    return ApplyByWidthOrHeight(ApplyByWidthOrHeight(image, true), false);
}

Image GaussianBlur::ApplyByWidthOrHeight(const Image& image, bool is_width) {
    Image new_image(image);

    long double sub_coefficient = 0.;

    for (ssize_t h0 = 0; h0 < image.height_; ++h0) {
        for (ssize_t w0 = 0; w0 < image.width_; ++w0) {
            new_image.pixels_[h0][w0].blue_ = 0.;
            new_image.pixels_[h0][w0].green_ = 0.;
            new_image.pixels_[h0][w0].red_ = 0.;

            for (ssize_t i = 0, w_left = w0, w_right = w0, h_up = h0, h_down = h0; i <= distance_; ++i) {
                if (is_width) {
                    if (w0 - i < 0) {
                        w_left = 0;
                    } else {
                        w_left = w0 - i;
                    }

                    if (w0 + i >= image.width_) {
                        w_right = image.width_ - 1;
                    } else {
                        w_right = w0 + i;
                    }
                } else {
                    if (h0 - i < 0) {
                        h_up = 0;
                    } else {
                        h_up = h0 - i;
                    }

                    if (h0 + i >= image.height_) {
                        h_down = image.height_ - 1;
                    } else {
                        h_down = h0 + i;
                    }
                }

                sub_coefficient = 1. / std::pow(M_E, (i * i) / (2 * sigma_ * sigma_));

                new_image.pixels_[h0][w0].blue_ +=
                    (image.pixels_[h_up][w_left].blue_ + image.pixels_[h_down][w_right].blue_) * sub_coefficient;
                new_image.pixels_[h0][w0].green_ +=
                    (image.pixels_[h_up][w_left].green_ + image.pixels_[h_down][w_right].green_) * sub_coefficient;
                new_image.pixels_[h0][w0].red_ +=
                    (image.pixels_[h_up][w_left].red_ + image.pixels_[h_down][w_right].red_) * sub_coefficient;

                if (i == 0) {
                    new_image.pixels_[h0][w0].blue_ /= 2;
                    new_image.pixels_[h0][w0].green_ /= 2;
                    new_image.pixels_[h0][w0].red_ /= 2;
                }
            }

            new_image.pixels_[h0][w0].blue_ *= coefficient_;
            new_image.pixels_[h0][w0].green_ *= coefficient_;
            new_image.pixels_[h0][w0].red_ *= coefficient_;
        }
    }

    return new_image;
}

GaussianBlur::GaussianBlur(double sigma) {
    sigma_ = sigma;
    distance_ = std::ceil(3 * sigma_);
    coefficient_ = 1. / std::sqrt(2 * M_PI * sigma_ * sigma_);
}
