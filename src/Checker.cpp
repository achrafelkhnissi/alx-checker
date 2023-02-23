/**
 * @file Checker.cpp
 * @brief Checker class implementation
 * @author Achraf El Khnissi
 * @version 1.0
 * @date 2021-02-23
 */

#include "Checker.hpp"

namespace alx {

	Checker::Checker() : _cout() {
		_projectPath = fs::current_path();
		_project = _projectPath.filename();

//		_cout.print("Project: " + _project.string(), GREEN);
//		_cout.print("Path: " + _projectPath.string(), GREEN);
	}

	Checker::~Checker() {
		// TODO
	}

	void Checker::usage() const {
		std::cout << "Usage: alx-checker [options] [file]" << std::endl;
		std::cout << "Options:" << std::endl;
		std::cout << "  -h, --help\t\t\tShow this help message and exit" << std::endl;
		std::cout << "  -v, --version\t\t\tShow program's version number and exit" << std::endl;
		std::cout << "  -f, --file\t\t\tSpecify the file to check" << std::endl;
		std::cout << "  -l, --log\t\t\tSpecify the log file" << std::endl;
	}

	void Checker::checkArgs(int argc, char *argv[]) {
		if (argc > 2) {
			usage();
			return;
		}

		std::string file = "";
		std::string log = "";

		for (int i = 1; i < argc; i++) {
			if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
				usage();
				return;
			} else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
				std::cout << "alx-checker version " << ALX_CHECKER_VERSION << std::endl;
				return;
			} else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
				if (i + 1 < argc) {
					_file.assign(argv[i + 1]);
					i++;
				} else {
					std::cerr << "Error: -f or --file option requires one argument." << std::endl;
					return;
				}
			} else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--log") == 0) {
				if (i + 1 < argc) {
					_log.assign(argv[i + 1]);
					i++;
				} else {
					_cout.print("Error: -l or --log option requires one argument.", RED);
					return;
				}
			} else {
				_cout.print("Error: Unknown option " + std::string(argv[i]), RED);
				return;
			}
		}

		if (file == "") {
			std::cerr << "Error: No file specified." << std::endl;
			return;
		}

		return;
	}


	bool Checker::directoryExists(const std::string& path) const {
		struct stat info;
		if (stat(path.c_str(), &info) != 0) {
			return false;
		} else if (info.st_mode & S_IFDIR) {
			return true;
		} else {
			return false;
		}
	}

}