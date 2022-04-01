#include "base_filter.h"

Image::Pixel Filter::MultiplyMatrix(const Image& image, size_t y_pos, size_t x_pos, std::vector<double> matrix) {
    Image::Pixel pixel;
    size_t new_pos_x;
    size_t new_pos_y;

    for (size_t i = 0; i < 9; ++i) {
        if (matrix[i] != 0) {
            switch (i) {
                case 0: {
                    if (x_pos == 0 && y_pos == 0) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos;
                    } else if (x_pos == 0) {
                        new_pos_y = y_pos - 1;
                        new_pos_x = x_pos;
                    } else if (y_pos == 0) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos - 1;
                    } else {
                        new_pos_y = y_pos - 1;
                        new_pos_x = x_pos - 1;
                    }
                    break;
                }
                case 1: {
                    if (y_pos == 0) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos;
                    } else {
                        new_pos_y = y_pos - 1;
                        new_pos_x = x_pos;
                    }
                    break;
                }
                case 2: {
                    if (y_pos == 0 && x_pos == image.width_ - 1) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos;
                    } else if (y_pos == 0) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos + 1;
                    } else if (x_pos == image.width_ - 1) {
                        new_pos_y = y_pos - 1;
                        new_pos_x = x_pos;
                    } else {
                        new_pos_y = y_pos - 1;
                        new_pos_x = x_pos + 1;
                    }
                    break;
                }
                case 3: {
                    if (x_pos == 0) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos;
                    } else {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos - 1;
                    }
                    break;
                }
                case 4: {
                    new_pos_y = y_pos;
                    new_pos_x = x_pos;
                    break;
                }
                case 5: {
                    if (x_pos == image.width_ - 1) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos;
                    } else {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos + 1;
                    }
                    break;
                }
                case 6: {
                    if (y_pos == image.height_ - 1 && x_pos == 0) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos;
                    } else if (y_pos == image.height_ - 1) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos - 1;
                    } else if (x_pos == 0) {
                        new_pos_y = y_pos + 1;
                        new_pos_x = x_pos;
                    } else {
                        new_pos_y = y_pos + 1;
                        new_pos_x = x_pos - 1;
                    }
                    break;
                }
                case 7: {
                    if (y_pos == image.height_ - 1) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos;
                    } else {
                        new_pos_y = y_pos + 1;
                        new_pos_x = x_pos;
                    }
                    break;
                }
                case 8: {
                    if (y_pos == image.height_ - 1 && x_pos == image.width_ - 1) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos;
                    } else if (y_pos == image.height_ - 1) {
                        new_pos_y = y_pos;
                        new_pos_x = x_pos + 1;
                    } else if (x_pos == image.width_ - 1) {
                        new_pos_y = y_pos + 1;
                        new_pos_x = x_pos;
                    } else {
                        new_pos_y = y_pos + 1;
                        new_pos_x = x_pos + 1;
                    }
                    break;
                }
            }

            pixel.blue_ += matrix[i] * image.pixels_[new_pos_y][new_pos_x].blue_;
            pixel.green_ += matrix[i] * image.pixels_[new_pos_y][new_pos_x].green_;
            pixel.red_ += matrix[i] * image.pixels_[new_pos_y][new_pos_x].red_;
        }
    }

    pixel.blue_ = std::min(1., std::max(0., pixel.blue_));
    pixel.green_ = std::min(1., std::max(0., pixel.green_));
    pixel.red_ = std::min(1., std::max(0., pixel.red_));

    return pixel;
}