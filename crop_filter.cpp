#include "crop_filter.h"

Image Crop::Apply(const Image& image) {
    if (height_ >= image.height_ && width_ >= image.width_) {
        return image;
    }

    Image new_image;

    if (height_ > image.height_) {
        height_ = image.height_;
    }
    if (width_ > image.width_) {
        width_ = image.width_;
    }

    for (size_t h = image.height_ - height_; h < image.height_; ++h) {
        std::vector<Image::Pixel> row;
        for (size_t w = 0; w < width_; ++w) {
            row.push_back(image.pixels_[h][w]);
        }
        new_image.pixels_.push_back(row);
    }

    std::memcpy(new_image.header_, image.header_, 54);

    new_image.UpdateImageSize(width_, height_);

    return new_image;
}
