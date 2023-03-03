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

		_sudo = (_isRunningAsRoot()) ? "sudo " : "";

		/* Get the current working directory and the project name */
		_projectPath = getenv("PWD");
		_project = _getBasename(_projectPath);

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
		_project = _getBasename(_projectPath);

		std::string parent_dir = getParentDirectory(_projectPath);
		_testFilesUrl += parent_dir + "/trunk/" + _project + "/test_files";

		// TODO: Check dependencies and install them if needed
		checkArgs(ac, av);

		if (_flag == FILE)
			_checkTask(_file);
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

	// TODO: Handle multiple flags
    void Checker::checkArgs(int argc, char *argv[]) {
        if (argc > 2) {
            usage();
            throw std::invalid_argument("Too many arguments.");
        }

        for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "--update") == 0) {
				_update();
			}
			if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0) {
				_flag = ALL; // it's not necessary
			} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                usage();
            } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
                printVersion();
            } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
				_flag = FILE;
                if (i + 1 < argc) {
                    _file.assign(argv[i + 1]);
                    i++;
                } else
                    throw std::invalid_argument("-f or --file option requires one argument.");
				_checkTask(_file);
            } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                if (i + 1 < argc) {
					_flag = OUTPUT;
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

    void Checker::checkProject() const {

		for (const auto& file : fs::directory_iterator(_projectPath)) {
			std::string fileName = file.path().filename().string();
			std::cout << "File: " << fileName << std::endl;



		} /* for */

	} /* checkProject */

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

				if (!isdigit(fileName[0])) {
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

	void Checker::_checkTask(const std::string& fileName) {
		_cout.print("Checking project file...", GREEN);
		// Check the file using betty
		std::string cmd = "betty " + fileName;
		int status = system(cmd.c_str());
		if (status != 0) {
			throw std::runtime_error("Failed to check file using betty.");
		}

		if (fileName.empty()) {
			throw std::runtime_error("Project file is empty.");
		}
		_cout.print("Project file is not empty.", GREEN);

		// Create a bin/ directory if it doesn't exist
		if (!fs::exists(_projectPath + "/bin")) {
			fs::create_directory(_projectPath + "/bin");
		}

		// Create test_output/ directory if it doesn't exist
		if (!fs::exists(_projectPath + "/test_output")) {
			fs::create_directory(_projectPath + "/test_output");
		}

		// Get the appropriate main for the file
		std::string main = _getMainFile(fileName);

		// remove .c from the file name
		std::string executable = fileName.substr(0, fileName.find_last_of('.'));

		// Compile the file
		std::string command = "gcc -I . " + _CFLAGS + " " + fileName + " " + main + " -o " + "bin/" + executable;
		status = system(command.c_str());
		if (status == -1) {
			std::cout << "Error: " << strerror(errno) << std::endl;
			exit(1);
		} else
			std::cout << fileName << " OK." << std::endl;

		// Execute the compiled file and save the output in a file
		_output = (_flag == OUTPUT) ? _output : "test_output/" + executable + ".out";
		command = "bin/" + executable + " > " + _output;
		status = system(command.c_str());
		if (status == -1) {
			std::cout << "Error: " << strerror(errno) << std::endl;
			exit(1);
		} else
			std::cout << "File executed successfully." << std::endl;

		// Compare the output with the expected output
		std::string expectedOutput = "expected_output/" + executable + ".out";
		command = "diff test_output/" + executable + ".out " + expectedOutput;
		status = system(command.c_str());
		if (status == -1) {
			std::cout << "Error: " << strerror(errno) << std::endl;
			exit(1);
		} else
			std::cout << "diff executed successfully." << std::endl;

		if (_flag == OUTPUT) {
			std::cout << "Output saved in " << _output << std::endl;
		}
		if (_flag == DIFF) {
			std::cout << "Diff saved in " << _output << std::endl;
		}

		if (_flag == FILE) {
			command = "cat " + _output;
			status = system(command.c_str());
			if (status == -1) {
				std::cout << "Error: " << strerror(errno) << std::endl;
				exit(1);
			} else
				std::cout << "File printed successfully." << std::endl;
		}

//		if (status == 0) {
//			_cout.print("Test passed.", GREEN);
//		} else {
//			_cout.print("Test failed.", RED);
//		}

	} /* _checkProjectFile */

		void Checker::_update() const {

		int status;

		std::string cloneCommand = "git clone https://github.com/achrafelkhnissi/alx-checker.git ~/.alx-checker";
		std::string cmakeCommand = "cmake -B build && cmake --build build";

		// TODO: check if the program is running as root
		std::string moveCommand = _sudo + "mv bin/alx-checker /usr/local/bin";


		std::cout << "Updating alx-checker..." << std::endl;


		// check if the directory exists
		if (directoryExists("~/.alx-checker")) {
			status = system("rm -rf ~/.alx-checker");
			if (status != 0) {
				throw std::runtime_error("Failed to remove ~/.alx-checker");
			}
		}

		// clone the repository
		status = system(cloneCommand.c_str());
		if (status != 0) {
			throw std::runtime_error(strerror(errno));
		}

		// change the current directory to the cloned repository
		status = chdir("~/.alx-checker");
		if (status != 0) {
			throw std::runtime_error(strerror(errno));
		}

		// build the project
		status = system(cmakeCommand.c_str());
		if (status != 0) {
			throw std::runtime_error(strerror(errno));
		}

		// add the executable to the PATH
		std::string path = getenv("PATH");
		std::string alxPath = std::string(getenv("HOME")) + "/.alx-checker/bin";
		if (setenv("PATH", (alxPath + ":" + path).c_str(), 1)) {
			throw std::runtime_error(strerror(errno));
		}

		std::cout << "alx-checker updated successfully!" << std::endl;

	} /* update */

} /* namespace alx */
