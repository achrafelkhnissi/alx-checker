/**
 * @file main.cpp
 * @brief Main file
 * @author Achraf El Khnissi
 * @version 0.1
 */

#include "main.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

int main(int ac, char **av) {

	(void)ac;
	(void)av;

    try {
		std::cout << "ALX_CHECKER_VERSION: " << ALX_CHECKER_VERSION << std::endl;

//		alx::Checker checker(--ac, ++av);

		if (status != 0) {
			std::cerr << "[" << RED << "ERROR" << END << "]: " << "Failed to move the executable to /usr/local/bin" << std::endl;
			return EXIT_FAILURE;
		}
		*/
    } catch (const std::exception &e) {
        std::cerr << "[" << RED << "ERROR" << END << "]: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
