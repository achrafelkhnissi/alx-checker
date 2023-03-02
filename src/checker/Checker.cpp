/**
 * @file Checker.cpp
 * @brief Checker class implementation
 * @author Achraf El Khnissi
 * @version 1.0
 */

#include "Checker.hpp"

namespace alx {

	void Checker::banner() const {
		std::cout << std::endl;
		_cout.yellow(" █████╗ ██╗     ██╗  ██╗     ██████╗██╗  ██╗███████╗ ██████╗██╗  ██╗███████╗██████╗ ");
		_cout.yellow("██╔══██╗██║     ╚██╗██╔╝    ██╔════╝██║  ██║██╔════╝██╔════╝██║ ██╔╝██╔════╝██╔══██╗");
		_cout.yellow("███████║██║      ╚███╔╝     ██║     ███████║█████╗  ██║     █████╔╝ █████╗  ██████╔╝");
		_cout.yellow("██╔══██║██║      ██╔██╗     ██║     ██╔══██║██╔══╝  ██║     ██╔═██╗ ██╔══╝  ██╔══██╗");
		_cout.yellow("██║  ██║███████╗██╔╝ ██╗    ╚██████╗██║  ██║███████╗╚██████╗██║  ██╗███████╗██║  ██║");
		_cout.yellow("╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝     ╚═════╝╚═╝  ╚═╝╚══════╝ ╚═════╝╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝");
		_cout.yellow("    version: v" + std::string(ALX_CHECKER_VERSION) + "\t\t\t\tAuthor: Achraf EL KHNISSI");
		std::cout << std::endl;
		std::cout << "Welcome to the alx-checker tool!" << std::endl;
		std::cout << "If you encounter any errors or bugs, please contact me for assistance." << std::endl;
		std::cout << "Twitter: "; _cout.green("@suprivada");

	} /*banner */

    Checker::Checker() : _cout(), _installer() {

		/* Get the current working directory and the project name */
		_projectPath = getenv("PWD");
		_project = getBasename(_projectPath);

		std::string parent_dir = getParentDirectory(_projectPath);
		_testFilesUrl += parent_dir + "/trunk/" + _project + "/test_files";

//		_projectPath = fs::current_path();
//		_project = _projectPath.filename();
//		_testFilesUrl += _project.string() + "/test_files";

		std::cout << "Project: " << _project << std::endl;
		std::cout << "Project path: " << _projectPath << std::endl;
		std::cout << "Test directory: " << _testFilesUrl << std::endl;

		_installer.checkDependencies();
		if (!_installer.getDependencies().empty())
			_installer.installDependencies();
		else
			_cout.info("No dependencies to install.");
    }

	Checker::Checker(int ac, char** av) : _cout(), _installer() {

		/* Get the current working directory and the project name */
		_projectPath = getenv("PWD");
		_project = getBasename(_projectPath);

		std::string parent_dir = getParentDirectory(_projectPath);
		_testFilesUrl += parent_dir + "/trunk/" + _project + "/test_files";

		// TODO: Check dependencies and install them if needed
		checkArgs(ac, av);

    	size_t dash_pos = _file.find_first_of('-');
		if (dash_pos == std::string::npos) {
			// No dash found, return -1 to indicate error
			throw std::invalid_argument("Invalid file name.");
		}
		// Extract the substring that precedes the dash
		std::string prefix = _file.substr(0, dash_pos);

		std::cout << "Prefix number: " << prefix << std::endl;

		std::string test = "0-main.c";

		// check the string start with the prefix number
		if (test.compare(0, prefix.length(), prefix) != 0) {
			std::cout << "File not matched with the prefix number." << std::endl;
		} else
			std::cout << "File matched with the prefix number." << std::endl;

		// Create a bin directory
		std::string bin_dir = _projectPath + "/bin";
		if (mkdir(bin_dir.c_str(), 0777) == -1) {
			std::cout << "Error: " << strerror(errno) << std::endl;
		} else
			std::cout << "Directory created successfully." << std::endl;

		// remove .c from the file name
		std::string output = _file.substr(0, _file.find_last_of('.'));

		// Compile the file
		std::string command = "gcc -I ." + _CFLAGS + " tests/" + test + " -o " + bin_dir + "/" + output;

		// Execute the command
		int status = system(command.c_str());
		if (status == -1) {
			std::cout << "Error: " << strerror(errno) << std::endl;
		} else
			std::cout << "File compiled successfully." << std::endl;

		// Execute the compiled file and save the output in a file
		command = bin_dir + "/" + output + " > " + bin_dir + "/" + output + ".out";
		status = system(command.c_str());
		if (status == -1) {
			std::cout << "Error: " << strerror(errno) << std::endl;
		} else
			std::cout << "File executed successfully." << std::endl;

		// Compare the output with the expected output
		std::string expected_output = "correct_outputs/" + output + ".out";
		command = "diff " + bin_dir + "/" + output + ".out " + expected_output;
		status = system(command.c_str());
		if (status == -1) {
			std::cout << "Error: " << strerror(errno) << std::endl;
		} else
			std::cout << "File executed successfully." << std::endl;


		exit(1);
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
        std::cout << "  -o, --output\t\t\tSpecify the log file" << std::endl;
        exit(EXIT_SUCCESS);
    }

    void Checker::checkArgs(int argc, char *argv[]) {
        if (argc > 2) {
            usage();
            throw std::invalid_argument("Too many arguments.");
        }

        for (int i = 0; i < argc; i++) {
            if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                usage();
            } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
                printVersion();
            } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
                if (i + 1 < argc) {
                    _file.assign(argv[i + 1]);
                    i++;
                } else
                    throw std::invalid_argument("-f or --file option requires one argument.");
            } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                if (i + 1 < argc) {
					_output.assign(argv[i + 1]);
                    i++;
                } else
                    throw std::invalid_argument("-o or --output option requires one argument.");
            } else
                throw std::invalid_argument("Unknown option " + std::string(argv[i]));
        }

//        if (file.empty())
//            throw std::invalid_argument("No file specified.");
    } /* checkArgs */

    void Checker::printVersion() const {
        std::cout << "alx-checker version " << ALX_CHECKER_VERSION << std::endl;
    }



    bool Checker::_isRunningAsRoot() const {
        return getuid() == 0;
    }

//    void Checker::checkProject() const {
//
//		for (const auto& file : fs::directory_iterator(_projectPath)) {
//			std::string fileName = file.path().filename().string();
//			std::cout << "File: " << fileName << std::endl;
//		}
//    }

    void Checker::_readDirectory(const std::string& directoryPath, files_t& files) const {

        DIR *dir;
        struct dirent *entry;

        if (!(dir = opendir(directoryPath.c_str()))) {
            throw std::runtime_error("Failed to open <" + directoryPath + "> directory");
        }

        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) { // check if file is a regular file
				std::string fileName = entry->d_name;
                std::string filePath = directoryPath + "/" + fileName;

				if (!isnumber(fileName[0])) {
					_cout.print("Skipping file <" + fileName + ">", RED);
					continue ;
				}

                std::ifstream file(filePath);
				if (!file.is_open()) {
					throw std::runtime_error("Failed to open <" + filePath + "> file");
				}

                std::string fileContent((std::istreambuf_iterator<char>(file)),
                                        std::istreambuf_iterator<char>());
                files[fileName] = fileContent;
            }
        }

        closedir(dir);

    }

	void Checker::downloadTests() const {

//		std::string url = _checkerRepository + "/" + _project.string();
		std::string cmd = "svn export " + _testFilesUrl;

		// check if the directory exists
		if (directoryExists("test_files")) {
			_cout.print("Directory <tests> already exists.", RED);
			_cout.print("Please remove it before downloading the tests.", RED);
			exit(EXIT_FAILURE);
		}

		int status = system(cmd.c_str());
		if (status != 0) {
			throw std::runtime_error("Failed to download tests."); // TODO: change the name of the directory ?
		} else {
			_cout.print("Tests downloaded successfully.", GREEN);
		}

	} /* _downloadTests */


	void Checker::_printTestFiles() const {
		std::cout << std::endl;
		_cout.print("Test files:", GREEN);
		for (const auto &file : _testFiles) {
			std::cout << "\t" << file.first << std::endl;
			std::cout << "\t\t" << file.second << std::endl;
		}
		std::cout << std::endl;
	}  /* _printTestFiles */

	void Checker::_checkProjectFile(const std::string& file) const {
		_cout.print("Checking project file...", GREEN);
		// Check the file using betty
		std::string cmd = "betty " + file;
		int status = system(cmd.c_str());
		if (status != 0) {
			_cout.print("Error: project file is not valid.", RED);
			exit(EXIT_FAILURE);
		}

		if (file.empty()) {
			_cout.print("Error: project file is empty.", RED);
			exit(EXIT_FAILURE);
		}
		_cout.print("Project file is not empty.", GREEN);
	} /* _checkProjectFile */

} /* namespace alx */
