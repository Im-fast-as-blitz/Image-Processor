#pragma once

#include "project_exception.h"

#include <string>
#include <fstream>
#include <vector>

class Image {
public:
    struct Pixel {
        Pixel() {
        }
        Pixel(uint8_t blue, uint8_t green, uint8_t red);

        bool operator==(const Pixel& other) const;

        static uint8_t ConvertToInt(double color);

        double blue_ = 0;
        double green_ = 0;
        double red_ = 0;
    };

    Image() {
    }

    Image(const Image& other);

    Image& operator=(const Image& other);

    bool operator==(const Image& other) const;

    void ReadImage(std::string input_path);
    void WriteImage(std::string output_path);

    void UpdateImageSize(uint32_t new_width, uint32_t new_height);

    uint16_t GetPaddingSize() const;

    char header_[54];
    std::vector<std::vector<Pixel>> pixels_;
    uint32_t width_ = 0;
    uint32_t height_ = 0;
};