#include "image.h"

void Image::ReadImage(std::string input_path) {
    std::ifstream input_stream(input_path, std::ios::binary);
    if (!input_stream.is_open()) {
        throw Exception("invalid path to the file");
    }

    input_stream.read(reinterpret_cast<char*>(&header_), sizeof(header_));

    input_stream.seekg(0x12);
    input_stream.read(reinterpret_cast<char*>(&width_), sizeof(width_));
    input_stream.read(reinterpret_cast<char*>(&height_), sizeof(height_));

    if (!((uint8_t(header_[0]) == 66 && uint8_t(header_[1]) == 77) ||
          (uint8_t(header_[10]) == 54 && uint8_t(header_[11]) == 0 && uint8_t(header_[12]) == 0 &&
           uint8_t(header_[13]) == 0) ||
          (uint8_t(header_[28]) == 24))) {
        input_stream.close();
        throw Exception("invalid format of the file");
    }

    input_stream.seekg(0x36);
    for (size_t h = 0; h < height_; ++h) {
        std::vector<Pixel> row;
        for (size_t w = 0; w < width_; ++w) {
            uint8_t blue;
            uint8_t green;
            uint8_t red;
            input_stream.read(reinterpret_cast<char*>(&blue), sizeof(blue));
            input_stream.read(reinterpret_cast<char*>(&green), sizeof(green));
            input_stream.read(reinterpret_cast<char*>(&red), sizeof(red));
            row.push_back(Pixel(blue, green, red));
        }
        for (size_t i = 0; i < GetPaddingSize(); ++i) {
            char a;
            input_stream.read(reinterpret_cast<char*>(&a), sizeof(a));
        }
        pixels_.push_back(row);
    }

    input_stream.close();
}

void Image::WriteImage(std::string output_path) {
    std::ofstream out(output_path);

    if (!out.is_open()) {
        throw Exception("invalid path to the file");
    }

    out.write(header_, sizeof(header_));

    for (size_t h = 0; h < height_; ++h) {
        for (size_t w = 0; w < width_; ++w) {
            uint8_t blue = Image::Pixel::ConvertToInt(pixels_[h][w].blue_);
            uint8_t green = Image::Pixel::ConvertToInt(pixels_[h][w].green_);
            uint8_t red = Image::Pixel::ConvertToInt(pixels_[h][w].red_);
            out.write(reinterpret_cast<char*>(&blue), sizeof(blue));
            out.write(reinterpret_cast<char*>(&green), sizeof(green));
            out.write(reinterpret_cast<char*>(&red), sizeof(red));
        }

        char a = 0;
        for (size_t i = 0; i < GetPaddingSize(); ++i) {
            out.write(reinterpret_cast<char*>(&a), sizeof(a));
        }
    }

    out.close();
}

Image::Image(const Image& other) {
    for (size_t i = 0; i < 54; ++i) {
        header_[i] = other.header_[i];
    }
    pixels_ = other.pixels_;
    width_ = other.width_;
    height_ = other.height_;
}

Image& Image::operator=(const Image& other) {
    for (size_t i = 0; i < 54; ++i) {
        header_[i] = other.header_[i];
    }
    pixels_ = other.pixels_;
    width_ = other.width_;
    height_ = other.height_;
    return *this;
}

bool Image::operator==(const Image& other) const {
    if (!(height_ == other.height_ && width_ == other.width_)) {
        return false;
    }

    for (size_t h = 0; h < height_; ++h) {
        for (size_t w = 0; w < width_; ++w) {
            if (pixels_[h][w] != other.pixels_[h][w]) {
                return false;
            }
        }
    }

    return true;
}

uint16_t Image::GetPaddingSize() const {
    return (4 - (width_ * 3) % 4) % 4;
}

Image::Pixel::Pixel(uint8_t blue, uint8_t green, uint8_t red) {
    blue_ = double(blue) / 255;
    green_ = double(green) / 255;
    red_ = double(red) / 255;
}

uint8_t Image::Pixel::ConvertToInt(double color) {
    return uint8_t(color * 255);
}

bool Image::Pixel::operator==(const Pixel& other) const {
    return red_ == other.red_ && green_ == other.green_ && blue_ == other.blue_;
}

void Image::UpdateImageSize(uint32_t new_width, uint32_t new_height) {
    height_ = new_height;
    width_ = new_width;

    for (size_t i = 21, d = 24; i >= 18; --i, d -= 8) {
        header_[i] = (new_width >> d);
    }

    for (size_t i = 25, d = 24; i >= 22; --i, d -= 8) {
        header_[i] = (new_height >> d);
    }
}