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
void executeCommandWithAnimation(const std::string& command)
{
    // Print initial loading message
    std::cout << "Executing command: " << command << std::endl;
    std::cout << "Loading... ";

    // Define animation characters
    const std::string animationChars = "|/-\\";
    int animationIndex = 0;

    // Execute command
    system(command.c_str());

    // Update loading animation until command finishes
    while (system(NULL) && !system(command.c_str()))
    {
        std::cout << animationChars[animationIndex % animationChars.size()] << std::flush;
        animationIndex++;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        std::cout << "\b" << std::flush;
    }

    // Print completion message
    std::cout << "Done!" << std::endl;
}

int main(int ac, char** av)
{
	(void)ac;
	(void)av;


	try {


	} catch (const std::exception& e) {
		std::cerr << "[" << RED << "ERROR" << END << "]: "<< e.what() << std::endl;
	}


	return EXIT_SUCCESS;
}