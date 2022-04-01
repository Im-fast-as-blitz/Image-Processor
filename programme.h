#pragma once

#include "image.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"
#include "edge_detection_filter.h"
#include "gaussian_blur_filter.h"
#include "anaglyph3D_filter.h"
#include "crop_filter.h"

#include <iostream>

class Programme {
public:
    void ParseArguments(int argc, char* argv[]);
};
