/**
 * @file main.cpp
 * @brief Main file
 * @author Achraf El Khnissi
 * @version 0.1
 * @date 2020-05-01
 */

#include "main.hpp"


#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

void spinningAnimation(bool status) {
    char spinChars[] = {'|', '/', '-', '\\'};
    int i = 0;
    while (!WIFEXITED(status)) {
        std::cout << "\r[ " << spinChars[i % 4] << " ] Loading... ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        i++;
    }
}

int main(int ac, char** av)
{
	(void)ac;
	(void)av;

        std::string     installCommand = "/bin/bash -c \"$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\" &";

	try {

        std::string     installTestsCommand = "svn export https://github.com/achrafelkhnissi/alx-low_level_programming/trunk/0x04-more_functions_nested_loops/tests &";
        int status = system(installTestsCommand.c_str());
        spinningAnimation(status);


	} catch (const std::exception& e) {
		std::cerr << "[" << RED << "ERROR" << END << "]: "<< e.what() << std::endl;
	}


	return EXIT_SUCCESS;
}
