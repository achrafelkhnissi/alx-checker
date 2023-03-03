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

//
//
//    	size_t dash_pos = _file.find_first_of('-');
//		if (dash_pos == std::string::npos) {
//			// No dash found, return -1 to indicate error
//			throw std::invalid_argument("Invalid file name.");
//		}
//		// Extract the substring that precedes the dash
//		std::string prefix = _file.substr(0, dash_pos);
//
//		std::cout << "Prefix number: " << prefix << std::endl;
//
//		std::string test = "0-main.c";
//
//		// check the string start with the prefix number
//		if (test.compare(0, prefix.length(), prefix) != 0) {
//			std::cout << "File not matched with the prefix number." << std::endl;
//		} else
//			std::cout << "File matched with the prefix number." << std::endl;

//		// Create a bin directory
//		std::string bin_dir = _projectPath + "/bin";
//		if (mkdir(bin_dir.c_str(), 0777) == -1) {
//			std::cout << "Error: " << strerror(errno) << std::endl;
//		} else
//			std::cout << "Directory created successfully." << std::endl;
//
//		// remove .c from the file name
//		std::string output = _file.substr(0, _file.find_last_of('.'));
//
//		// Compile the file
//		std::string command = "gcc -I ." + _CFLAGS + " tests/" + test + " -o " + bin_dir + "/" + output;
//
//		// Execute the command
//		int status = system(command.c_str());
//		if (status == -1) {
//			std::cout << "Error: " << strerror(errno) << std::endl;
//		} else
//			std::cout << "File compiled successfully." << std::endl;
//
//		// Execute the compiled file and save the output in a file
//		command = bin_dir + "/" + output + " > " + bin_dir + "/" + output + ".out";
//		status = system(command.c_str());
//		if (status == -1) {
//			std::cout << "Error: " << strerror(errno) << std::endl;
//		} else
//			std::cout << "File executed successfully." << std::endl;
//
//		// Compare the output with the expected output
//		std::string expected_output = "correct_outputs/" + output + ".out";
//		command = "diff " + bin_dir + "/" + output + ".out " + expected_output;
//		status = system(command.c_str());
//		if (status == -1) {
//			std::cout << "Error: " << strerror(errno) << std::endl;
//		} else
//			std::cout << "File executed successfully." << std::endl;
//
//
//		exit(1);

	return 0;
}