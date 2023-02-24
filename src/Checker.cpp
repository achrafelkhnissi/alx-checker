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
		_project = "0x04-checker";
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

	void Checker::checkDependencies() const {

		int status = system("command -v svn &> /dev/null");
		if (status != 0) {
			installSvn();
			return;
		} else {
			_cout.print("svn is installed.", GREEN);
		}
	}

	void Checker::installSvn() const {

		std::cout << "Error: svn is not installed. Do you want to install it? [y/n]";

		std::string answer;
		std::getline(std::cin, answer);
		std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		if (answer != "y" && answer != "yes") {
			std::cout << "OK. Bye!" << std::endl;
			exit(EXIT_SUCCESS);
		}

		int status = system("sudo apt-get install subversion");
		if (status != 0) {
			_cout.print("Error: svn is not installed.", RED);
			exit(EXIT_FAILURE);
		}
	}

	void Checker::downloadTests(void) const {

		std::string url = _checkerRepository + "/" + _project.string();
		std::string cmd = "svn export " + url + "/tests";

		int status = system(cmd.c_str());
		if (status != 0) {
			_cout.error("Error: Can't download tests.");
			exit(EXIT_FAILURE);
		} else {
			_cout.print("Tests downloaded successfully.", GREEN);
		}
	}
}