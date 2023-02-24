/**
 * @file main.cpp
 * @brief Main file
 * @author Achraf El Khnissi
 * @version 0.1
 * @date 2020-05-01
 */

#include "main.hpp"

int main(int ac, char** av)
{
	(void)ac;
	(void)av;

//	alx::Checker checker;

	try {
		alx::Installer installer;

//		installer.checkDependencies();
		installer.installBrew();

	} catch (const std::exception& e) {
		std::cerr << "[" << RED << "ERROR" << END << "]: "<< e.what() << std::endl;
	}


	return EXIT_SUCCESS;
}