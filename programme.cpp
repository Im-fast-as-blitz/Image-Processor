#include "programme.h"

void Programme::ParseArguments(int argc, char* argv[]) {
    if (argc > 2) {
        try {
            std::string input_path = argv[1];
            std::string output_path = argv[2];

            if (!((input_path[0] == '.' && input_path[1] == '/') ||
                  (input_path[0] == '.' && input_path[1] == '.' && input_path[2] == '/'))) {
                throw Exception("invalid path to the file");
            }
            if (!((output_path[0] == '.' && output_path[1] == '/') ||
                  (output_path[0] == '.' && output_path[1] == '.' && output_path[2] == '/'))) {
                throw Exception("invalid path to the file");
            }

            Image image;
            image.ReadImage(input_path);

            for (size_t i = 3; i < argc; ++i) {
                if (std::string(argv[i]) == "-crop") {
                    if (i + 2 >= argc) {
                        throw Exception("invalid count of arguments for the -crop filter");
                    }
                    try {
                        Crop filter(std::stoi(std::string(argv[i + 1])), std::stoi(std::string(argv[i + 2])));
                        image = filter.Apply(image);
                        i += 2;
                    } catch (std::invalid_argument) {
                        throw Exception("invalid type of arguments for the -crop filter");
                    }
                } else if (std::string(argv[i]) == "-gs") {
                    Grayscale filter;
                    image = filter.Apply(image);
                } else if (std::string(argv[i]) == "-neg") {
                    Negative filter;
                    image = filter.Apply(image);
                } else if (std::string(argv[i]) == "-sharp") {
                    Sharpening filter;
                    image = filter.Apply(image);
                } else if (std::string(argv[i]) == "-edge") {
                    if (i + 1 >= argc) {
                        throw Exception("invalid count of arguments for the -edge filter");
                    }
                    try {
                        EdgeDetection filter_ed(std::stod(std::string(argv[i + 1])));
                        image = filter_ed.Apply(image);
                        ++i;
                    } catch (std::invalid_argument) {
                        throw Exception("invalid type of arguments for the -edge filter");
                    }
                } else if (std::string(argv[i]) == "-blur") {
                    if (i + 1 >= argc) {
                        throw Exception("invalid count of arguments for the -blur filter");
                    }
                    try {
                        GaussianBlur filter(std::stod(std::string(argv[i + 1])));
                        image = filter.Apply(image);
                        ++i;
                    } catch (std::invalid_argument) {
                        throw Exception("invalid type of arguments for the -blur filter");
                    }
                } else if (std::string(argv[i]) == "-an") {
                    Image sub_image;
                    if (i + 1 < argc) {
                        std::string arg_path = argv[i + 1];
                        ++i;
                        sub_image.ReadImage(arg_path);
                    } else {
                        sub_image = image;
                    }

                    Anaglyph3D filter_an(sub_image);
                    image = filter_an.Apply(image);
                } else {
                    if (std::string(argv[i])[0] == '-') {
                        throw Exception("invalid filter");
                    } else {
                        throw Exception("invalid argument");
                    }
                }
            }

            image.WriteImage(output_path);
        } catch (Exception& e) {
            std::cout << e.what() << std::endl;
        }
    } else if (argc == 2) {
        std::cout << "invalid number of arguments" << std::endl;
    } else {
        std::cout << "correct structure" << std::endl;
        std::cout << "./image_processor {path to the input file} {path to the output file} [-{filter name 1}] "
                     "[argument 1] ... [argument n] [-{filter name 2}] ..."
                  << std::endl;
        std::cout << "path to the file must start with ./ or ../" << std::endl;
        std::cout << std::endl;
        std::cout << "list of filters:" << std::endl;
        std::cout << "1) Crop: cropping the image" << std::endl;
        std::cout << "-crop [new_width] [new_height]" << std::endl;
        std::cout << "2) Grayscale: converts the image to grayscale" << std::endl;
        std::cout << "-gs" << std::endl;
        std::cout << "3) Negative: converts the image to negative" << std::endl;
        std::cout << "-neg" << std::endl;
        std::cout << "4) Sharpening: increases the sharpness of the image" << std::endl;
        std::cout << "-sharp" << std::endl;
        std::cout << "5) Edge Detection: highlighting image borders" << std::endl;
        std::cout << "-edge [threshold]" << std::endl;
        std::cout << "6) Gaussian Blur: blurring the image" << std::endl;
        std::cout << "-blur [sigma]" << std::endl;
        std::cout << "7) Anaglyph 3D: making an anaglyph 3D from the current or from another one" << std::endl;
        std::cout << "-an [path to the another image]" << std::endl;
    }
}
