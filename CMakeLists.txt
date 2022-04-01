cmake_minimum_required(VERSION 3.21)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_executable(image_processor
        image_processor.cpp
        image.cpp image.h
        base_filter.h base_filter.cpp
        crop_filter.h crop_filter.cpp
        grayscale_filter.h grayscale_filter.cpp
        negative_filter.cpp negative_filter.h
        sharpening_filter.cpp sharpening_filter.h
        edge_detection_filter.cpp edge_detection_filter.h
        gaussian_blur_filter.cpp gaussian_blur_filter.h
        anaglyph3D_filter.cpp anaglyph3D_filter.h
        project_exception.h
        programme.h programme.cpp)

add_executable(test_image_processor
        test.cpp
        programme.cpp
        image.cpp
        base_filter.cpp
        crop_filter.cpp
        grayscale_filter.cpp
        negative_filter.cpp
        sharpening_filter.cpp
        edge_detection_filter.cpp
        gaussian_blur_filter.cpp
        anaglyph3D_filter.cpp)
