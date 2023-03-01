/**
 * @file main.cpp
 * @brief Main file
 * @author Achraf El Khnissi
 * @version 0.1
 * @date 2020-05-01
 */

#include "../inc/main.hpp"
#include "config.hpp"

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>

void spinningAnimation(int status) {
    char spinChars[] = {'|', '/', '-', '\\'};
    int i = 0;
    while (!WIFEXITED(status)) {
        std::cout << "\r[ " << spinChars[i % 4] << " ] Loading... ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        i++;
    }
}

int main(int ac, char **av) {

    (void) ac;
    (void) av;

    try {

		alx::Checker checker;

		checker.printVersion();

    } catch (const std::exception &e) {
        std::cerr << "[" << RED << "ERROR" << END << "]: " << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
