//
// Created by Achraf El Khnissi on 3/2/23.
//

#include <iostream>
#include <sys/stat.h>
#include <unistd.h>


int main() {

	std::string file = "0-isupper.c";
	std::string output = "0-isupper";
	std::string correctOutput = "correct_outputs/0-isupper.out";
	std::string mainFile = "tests/0-main.c";
	std::string CC = "gcc";
	std::string FLAGS = "-Wall -Wextra -Werror -pedantic -std=c99";

	int status;
	// Create a directory bin/ if it doesn't exist
//	if (!std::filesystem::exists("bin")) {
//		std::filesystem::create_directory("bin");
//	}
//	if (access("bin", F_OK) == -1) {
//		mkdir("bin", 0777);
//	}
//
//	std::string command = CC + " -I . " + FLAGS + " " + mainFile + " " + file + " -o bin/" + output;
//	std::cout << "Compile command: " << command << std::endl;
//
//
//	// Compile the file
//	int status = system(command.c_str());
//	if (status != 0) {
//		strerror(errno);
//		exit(EXIT_FAILURE);
//	} else {
//		std::cout << "Compilation successful" << std::endl;
//	}
//
//
//	// Run the program
//	std::string runCommand = "./bin/" + output + " > " + "bin/" + output + ".out";
//	std::cout << "Run command: " << runCommand << std::endl;
//	status = system(runCommand.c_str());
//	if (status != 0) {
//		strerror(errno);
//		exit(EXIT_FAILURE);
//	} else {
//		std::cout << "Run successful" << std::endl;
//	}

	// Compare the output
	std::string diffCommand = "diff -u " + correctOutput + " " + "bin/" + output + ".out";
	std::cout << "Diff command: " << diffCommand << std::endl;
	status = system(diffCommand.c_str());
	if (status != 0) {
		strerror(errno);
		exit(EXIT_FAILURE);
	} else {
		std::cout << "Diff successful" << std::endl;
	}

	return 0;
}