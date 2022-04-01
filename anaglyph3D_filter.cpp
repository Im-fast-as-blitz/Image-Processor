#include "anaglyph3D_filter.h"

Image Anaglyph3D::Apply(const Image& right_image) {
    Image new_image(right_image);

    if (left_image_ == right_image) {
        Crop filter_crop(static_cast<uint32_t>(left_image_.width_ * 0.975), left_image_.height_);
        left_image_ = filter_crop.Apply(left_image_);
    }

    for (size_t h = 0; h < right_image.height_; ++h) {
        for (size_t w = 0; w < right_image.width_; ++w) {
            if (w >= right_image.width_ - left_image_.width_) {
                new_image.pixels_[h][w].red_ =
                    left_image_.pixels_[h][w + left_image_.width_ - right_image.width_].red_;
            } else {
                new_image.pixels_[h][w].red_ = 0.;
            }
        }
    }

    return new_image;
}
