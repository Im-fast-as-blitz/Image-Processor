#include "catch.hpp"

#include "programme.h"

char first[] = "./image_processor";
char input[] = "../projects/image_processor/examples/example.bmp";
char output[] = "../projects/image_processor/examples/output.bmp";

void RequireImageSize(uint32_t width, uint32_t height) {
    std::ifstream input_stream(output, std::ios::binary);
    uint32_t file_width;
    uint32_t file_height;

    input_stream.seekg(0x12);
    input_stream.read(reinterpret_cast<char*>(&file_width), sizeof(file_width));
    input_stream.read(reinterpret_cast<char*>(&file_height), sizeof(file_height));

    REQUIRE(file_width == width);
    REQUIRE(file_height == height);
}

TEST_CASE("Anaglyph3DFilter") {
    Programme test;
    char filter[] = "-an";
    {
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter)};
        test.ParseArguments(4, argv);
    }
    {
        char main_file[] = "../projects/image_processor/examples/an_test_1.bmp";
        char sub_file[] = "../projects/image_processor/examples/an_test_2.bmp";
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(main_file),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                        reinterpret_cast<char *>(sub_file)};
        test.ParseArguments(5, argv);
    }
}

TEST_CASE("CropFilter") {
    Programme test;
    char filter[] = "-crop";
    {
        char arg1[] = "3000";
        char arg2[] = "3000";
        char *argv[] = {reinterpret_cast<char *>(first),  reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                        reinterpret_cast<char *>(arg1),   reinterpret_cast<char *>(arg2)};
        test.ParseArguments(6, argv);
        RequireImageSize(2048, 2048);
    }
    {
        char arg1[] = "3000";
        char arg2[] = "1024";
        char *argv[] = {reinterpret_cast<char *>(first),  reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                        reinterpret_cast<char *>(arg1),   reinterpret_cast<char *>(arg2)};
        test.ParseArguments(6, argv);
        RequireImageSize(2048, 1024);
    }
    {
        char arg1[] = "1024";
        char arg2[] = "3000";
        char *argv[] = {reinterpret_cast<char *>(first),  reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                        reinterpret_cast<char *>(arg1),   reinterpret_cast<char *>(arg2)};
        test.ParseArguments(6, argv);
        RequireImageSize(1024, 2048);
    }
    {
        char arg1[] = "1024";
        char arg2[] = "1024";
        char *argv[] = {reinterpret_cast<char *>(first),  reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                        reinterpret_cast<char *>(arg1),   reinterpret_cast<char *>(arg2)};
        test.ParseArguments(6, argv);
        RequireImageSize(1024, 1024);
    }
    {
        char arg1[] = "1";
        char arg2[] = "999";
        char *argv[] = {reinterpret_cast<char *>(first),  reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                        reinterpret_cast<char *>(arg1),   reinterpret_cast<char *>(arg2)};
        test.ParseArguments(6, argv);
        RequireImageSize(1, 999);
    }
}

TEST_CASE("EdgeDetectionFilter") {
    Programme test;
    char filter[] = "-edge";
    char arg[] = "0.05";
    char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input), reinterpret_cast<char *>(output),
                    reinterpret_cast<char *>(filter), reinterpret_cast<char *>(arg)};
    test.ParseArguments(5, argv);
}

TEST_CASE("GaussianBlurFilter") {
    Programme test;
    char filter[] = "-blur";
    char arg[] = "10";
    char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input), reinterpret_cast<char *>(output),
                    reinterpret_cast<char *>(filter), reinterpret_cast<char *>(arg)};
    test.ParseArguments(5, argv);
}

TEST_CASE("GrayscaleFilter") {
    Programme test;
    char filter[] = "-gs";
    char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input), reinterpret_cast<char *>(output),
                    reinterpret_cast<char *>(filter)};
    test.ParseArguments(4, argv);
}

TEST_CASE("NegativeFilter") {
    Programme test;
    char filter[] = "-neg";
    char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input), reinterpret_cast<char *>(output),
                    reinterpret_cast<char *>(filter)};
    test.ParseArguments(4, argv);
}

TEST_CASE("SharpeningFilter") {
    Programme test;
    char filter[] = "-sharp";
    char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input), reinterpret_cast<char *>(output),
                    reinterpret_cast<char *>(filter)};
    test.ParseArguments(4, argv);
}

TEST_CASE("MultipleFilters") {
    Programme test;
    char filter1[] = "-blur";
    char filter2[] = "-edge";
    char arg1[] = "2";
    char arg2[] = "2";
    char *argv[] = {reinterpret_cast<char *>(first),  reinterpret_cast<char *>(input),
                    reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter1),
                    reinterpret_cast<char *>(arg1),   reinterpret_cast<char *>(filter2),
                    reinterpret_cast<char *>(arg2)};
    test.ParseArguments(7, argv);
}

TEST_CASE("ExceptionsTest") {
    Programme test;
    char fail[] = "lol";
    {
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input)};
        test.ParseArguments(2, argv);
        std::cout << std::endl;
    }
    {
        char *argv[] = {reinterpret_cast<char *>(first)};
        test.ParseArguments(1, argv);
        std::cout << std::endl;
    }
    {
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(fail),
                        reinterpret_cast<char *>(output)};
        test.ParseArguments(3, argv);
        std::cout << std::endl;
    }
    {
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(fail)};
        test.ParseArguments(3, argv);
        std::cout << std::endl;
    }
    {
        char fail_file[] = "../projects/image_processor/examples/lol.png";
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(fail_file),
                        reinterpret_cast<char *>(output)};
        test.ParseArguments(3, argv);
        std::cout << std::endl;
    }
    {
        char fail_file[] = "./fail";
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(fail_file),
                        reinterpret_cast<char *>(output)};
        test.ParseArguments(3, argv);
        std::cout << std::endl;
    }
    {
        char filter[] = "-crop";
        {
            char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                            reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter)};
            test.ParseArguments(4, argv);
            std::cout << std::endl;
        }
        {
            char *argv[] = {reinterpret_cast<char *>(first),  reinterpret_cast<char *>(input),
                            reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                            reinterpret_cast<char *>(fail),   reinterpret_cast<char *>(fail)};
            test.ParseArguments(6, argv);
            std::cout << std::endl;
        }
    }
    {
        char filter[] = "-edge";
        {
            char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                            reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter)};
            test.ParseArguments(4, argv);
            std::cout << std::endl;
        }
        {
            char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                            reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                            reinterpret_cast<char *>(fail)};
            test.ParseArguments(5, argv);
            std::cout << std::endl;
        }
    }
    {
        char filter[] = "-blur";
        {
            char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                            reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter)};
            test.ParseArguments(4, argv);
            std::cout << std::endl;
        }
        {
            char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                            reinterpret_cast<char *>(output), reinterpret_cast<char *>(filter),
                            reinterpret_cast<char *>(fail)};
            test.ParseArguments(5, argv);
            std::cout << std::endl;
        }
    }
    {
        char fail_filter[] = "-lol";
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(fail_filter)};
        test.ParseArguments(4, argv);
        std::cout << std::endl;
    }
    {
        char *argv[] = {reinterpret_cast<char *>(first), reinterpret_cast<char *>(input),
                        reinterpret_cast<char *>(output), reinterpret_cast<char *>(fail)};
        test.ParseArguments(4, argv);
        std::cout << std::endl;
    }
}
