/*
 * generate_yaml_examples.cpp
 *
 *  Created on: 17 avr. 2014
 *      Author: cady
 */

#include <fstream>

#include "yaml_data.hpp"

int main(int argc, const char* argv[])
{
    const std::string path = argc ? std::string(argv[1])+"/" : "";
    std::ofstream file1(path+"complete_example.yml"),
                  file2(path+"hydrostatic_integration_test.yml"),
                  file3(path+"falling_ball_test.yml"),
                  file4(path+"oscillating_cube_test.yml");

    file1 << test_data::full_example();
    file1.close();

    file2 << test_data::hydrostatic_test();
    file2.close();

    file3 << test_data::falling_ball_example();
    file3.close();

    file4 << test_data::oscillating_cube_example();
    file4.close();

    return 0;
}
