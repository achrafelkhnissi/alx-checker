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

		// TODO: Initialize the funciton pointers
		initTaskMap();

		if (_flag == FILE)
			_check00x00(_file);

		for (const auto& file : fs::directory_iterator(_projectPath)) {
			std::string fileName = file.path().filename().string();
			if (isdigit(fileName[0])) {
				if (fileName.find(".c") == std::string::npos) {
					// TODO: Check which project contains the file
					// TODO: Give the file to the appropriate project checker
					_check00x00(fileName);
				} else
					_checkTask(fileName);
			}
			if (fileName == "README.md") {
				// TODO: add a variable to hold a value true if README.md is found
				if (fileName.empty())
					throw std::runtime_error("README.md file is empty");
				continue;
			}
		}

	} /* Checker Constructor */

	void Checker::initTaskMap() {
		_taskMap["0-preprocessor"] = []() {

			std::string cmd = "./0-preprocessor";

			std::cout << "Execution: ";
			int status = system(cmd.c_str());
			std::cout << (status == 0 ? "OK" : "KO") << std::endl;

			// check if a file named c exists
			std::cout << (fs::exists("c") ? "OK" : "KO") << std::endl;
		};

		_taskMap["1-compiler"] = []() {

			std::string cmd = "./1-compiler";

			std::cout << "Execution: ";
			int status = system(cmd.c_str());
			std::cout << (status == 0 ? "OK" : "KO") << std::endl;

			// Check if file ends with .o
			std::string obj = getenv("CFILE");

			// repleace .c with .o
			obj = obj.substr(0, obj.find_last_of('.')) + ".o";

			std::cout << (fs::exists(obj) ? "OK" : "KO") << std::endl;
		};

		_taskMap["2-assembler"] = []() {

			std::string cmd = "./2-assembler";

			std::cout << "Execution: ";
			int status = system(cmd.c_str());
			std::cout << (status == 0 ? "OK" : "KO") << std::endl;

			// Check if file ends with .o
			std::string obj = getenv("CFILE");

			// repleace .c with .o
			obj = obj.substr(0, obj.find_last_of('.')) + ".s";

			std::cout << (fs::exists(obj) ? "OK" : "KO") << std::endl;
		};

		_taskMap["3-name"] = []() {

			std::string cmd = "./3-name";

			std::cout << "Execution: ";
			int status = system(cmd.c_str());
			std::cout << (status == 0 ? "OK" : "KO") << std::endl;

			std::cout << (fs::exists("cisfun") ? "OK" : "KO") << std::endl;
		};

		_taskMap["100-intel"] = []() {

			std::string cmd = "./100-intel";

			std::cout << "Execution: ";
			int status = system(cmd.c_str());
			std::cout << (status == 0 ? "OK" : "KO") << std::endl;

			// Check if file ends with .o
			std::string obj = getenv("CFILE");

			// repleace .c with .o
			obj = obj.substr(0, obj.find_last_of('.')) + ".s";

			std::cout << (fs::exists(obj) ? "OK" : "KO") << std::endl;

			std::ifstream file(obj);
			std::string line;
			bool found = false;

			while (std::getline(file, line)) {
				if (line.find("intel") != std::string::npos) {
					found = true;
					break;
				}
			}

			std::cout << "Intel: " << (found ? "OK" : "KO") << std::endl;
		};

	}

    Checker::~Checker() {
        // TODO
    }

	bool Checker::_is0x00(const std::string& file) const {
		return _taskMap.find(file) != _taskMap.end();
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

    void Checker::checkProject() {

		if (_flag == FILE) {
			_checkTask(_file);
			return;
		}

		for (const auto& file : fs::directory_iterator(_projectPath)) {
			std::string fileName = file.path().filename().string();
			if (isdigit(fileName[0])) {
				_checkTask(fileName);
				sleep(1);
			}
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

				if (!std::isdigit(fileName[0])) {
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

		// TODO: handle the case when the file is not a .c file

		_cout.print("Checking task <" + fileName + ">...", GREEN);

		// Check the file using betty
		std::string cmd = "betty " + fileName;
		int status = system(cmd.c_str());
		if (status != 0) {
			throw std::runtime_error("Failed to check file using betty.");
		}

		if (fileName.empty()) {
			throw std::runtime_error("Project file is empty.");
		}

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
		std::string command = "gcc -I . " + _CFLAGS + " " + fileName + " test_files/_putchar.c " + main + " -o " + "bin/" + executable;
		status = system(command.c_str());
		if (status == -1) {
			throw std::runtime_error(strerror(errno));
		}

		// Execute the compiled file and save the output in a file
		_output = (_flag == OUTPUT) ? _output : "test_output/" + executable + ".out";
		std::string redirect = (fileName == "101-quote.c") ? " 2> " : " > "; // because 101-quote.c prints to stderr
		command = "bin/" + executable + redirect + _output;
		status = system(command.c_str());
		if (status == -1) {
			throw std::runtime_error(strerror(errno));
		}

		// Compare the output with the expected output
		std::string expectedOutput = "expected_output/" + executable + ".out";
		command = "diff test_output/" + executable + ".out " + expectedOutput;
		status = system(command.c_str());
		if (status == -1) {
			throw std::runtime_error(strerror(errno));
		}

		if (_flag == FILE) {

			// TODO: fix wrong output for 0x00-hello_world/101-quote.c

			std::cout << std::endl;
			std::cout << "=====  Output  =====\n" << std::endl;

			std::ifstream file(_output);
			if (!file.is_open()) {
				throw std::runtime_error("Failed to open <" + _output + "> file");
			}

			std::string fileContent((std::istreambuf_iterator<char>(file)),
									std::istreambuf_iterator<char>());

			std::cout << fileContent << std::endl;
			
			std::cout << "====================" << std::endl;
		}

		std::cout << std::endl;
		std::cout << fileName << "\t: ";

		if (status == 0) {
			_cout.print("Test passed.\n", GREEN);
		} else {
			_cout.print("Test failed.\n", RED);
		}

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

	void Checker::_check00x00(const std::string& file) {

		// check if the file ends with .c
		if (file.substr(file.find_last_of('.') + 1) == "c") {
			_checkTask(file);
			exit(0); // TODO: handle this
		}

		if (!_checkScript(file))
			throw std::runtime_error("Failed.");

		// Set env CFILE=main.c
		setenv("CFILE", "main.c", 1);
		_taskMap.at(file)(); // error while using [] instead of at()

	} /* _check00x00 */

} /* namespace alx */
