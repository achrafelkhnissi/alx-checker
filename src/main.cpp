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

    try {

      alx::Checker checker(--ac, ++av);

      checker.checkProject();

    } catch (const std::exception &e) {
        std::cerr << "[" << RED << "ERROR" << END << "]: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
