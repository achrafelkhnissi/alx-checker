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
		std::cout << std::endl << std::endl;

	} /*banner */

	Checker::Checker(int ac, char** av) : _cout(), _installer() {

		/* Get the current working directory and the project name */
		_projectPath = getenv("PWD");
		_project = _getBasename(_projectPath);

		std::string parent_dir = getParentDirectory(_projectPath);
		_testFilesUrl += parent_dir + "/trunk/" + _project + "/test_files";

		checkArgs(ac, av);

		_installer.checkDependencies();
		if (!_installer.getDependencies().empty())
			_installer.installDependencies();
		else
			_cout.info("No dependencies to install.");

		// todo; when a file requested, check if it exists
		// todo: when a checking a directory, check if its a project directory

		// After checking the arguments, we can display the banner.
		banner();

		initProjectMap();
		_projectMap.at(_project)();
	} /* Checker Constructor */

    Checker::~Checker() {
		footer();
    }

    void Checker::usage() const {
        std::cout << "Usage: alx-checker [options] [file]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help\t\t\tShow this help message and exit" << std::endl;
        std::cout << "  -v, --version\t\t\tShow program's version number and exit" << std::endl;
        std::cout << "  -f, --file\t\t\tSpecify the file to check" << std::endl;
        exit(EXIT_SUCCESS);
    }

	// TODO: Handle multiple flags
    void Checker::checkArgs(int argc, char *argv[]) {
        if (argc > 2) {
			_error(MSG("Too many arguments"), 0);
            usage();
        }

        for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "--update") == 0) {
				_update();
				exit(EXIT_SUCCESS);
			}
			if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "--all") == 0) {
				_flag = ALL; // it's not necessary
			} else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
                usage();
				exit(EXIT_SUCCESS);
            } else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--version") == 0) {
                printVersion();
				exit(EXIT_SUCCESS);
            } else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--file") == 0) {
				_flag = FILE;
                if (i + 1 < argc) {
                    _file.assign(argv[i + 1]);
                    i++;
                } else
					_error(MSG("-f or --file option requires one argument."), 0);
            } else if (strcmp(argv[i], "-o") == 0 || strcmp(argv[i], "--output") == 0) {
                if (i + 1 < argc) {
					_flag = OUTPUT;
					_output.assign(argv[i + 1]);
                    i++;
                } else
                    _error(MSG("-o or --output option requires one argument."), 0);
            } else
                _error("Unknown option " + std::string(argv[i]), 0);
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

	std::string Checker::_upperCase(const std::string& str) const {
		std::string upperCase = str;
		std::transform(upperCase.begin(), upperCase.end(), upperCase.begin(), ::toupper);
		return upperCase;
	}

    void Checker::checkProject() {

		bool readmeFound = false;

		std::cout << termcolor::bold << termcolor::bright_magenta << termcolor::blink << termcolor::underline
		          << _upperCase("\nproject: " + _project) << termcolor::reset << std::endl << std::endl;

		std::cout << termcolor::bold << termcolor::bright_blue << termcolor::underline;
		std::cout << std::setw(25) << std::left << "TASKS"
		          << std::setw(20) << std::left << "BETTY"
				  << std::setw(20) << std::left << "COMPILATION"
				  << std::setw(20) << std::left << "EXECUTION"
				  << std::setw(20) << std::left <<"OUTPUT"
				  << "STATUS";
		std::cout << termcolor::reset << std::endl;

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
			if (fileName == "README.md") {
				if (fileName.empty())
					_error(MSG("README.md file is empty"), 0);
				readmeFound = true;
			}
		} /* for */
		std::cout << termcolor::italic << termcolor::yellow <<
		std::setw(25) << std::left << "README.md" << termcolor::reset;
		std::cout << NP << NP << NP << NP;
		if (!readmeFound || fs::is_empty(_projectPath + "/README.md"))
			std::cout << termcolor::red << "FAILED" << termcolor::reset << std::endl;
		else
			std::cout << termcolor::green << "PASSED" << termcolor::reset << std::endl;

	} /* checkProject */

    void Checker::_readDirectory(const std::string& directoryPath, files_t& files) const {
        DIR *dir;
        struct dirent *entry;

        if (!(dir = opendir(directoryPath.c_str()))) {
			_error(MSG("Failed to open <" + directoryPath + "> directory"), 0);
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
					_error(MSG("Failed to open <" + filePath + "> file"), 0);
				}

                std::string fileContent((std::istreambuf_iterator<char>(file)),
                                        std::istreambuf_iterator<char>());
                files[fileName] = fileContent;
            }
        }

        closedir(dir);

    }

	void Checker::downloadTests() const {

		std::string cmd = "svn export " + _testFilesUrl;

		// check if the directory exists
		if (directoryExists("test_files"))
			_error(MSG("Directory <test_files> already exists.\n"
					   "Please remove it before downloading the tests"), 0);

		int status = system(cmd.c_str());
		if (status != 0) {
			_error(MSG("Failed to download tests"), 0);
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

		// TODO: calculate the total failed tasks
		/*
		 * example:
		 * 1 compilation failed (1/10)
		 * 2 execution failed (2/10)
		 * 3 output failed (3/10)
		 * 4 betty failed (4/10)
		 * 5 compilation failed (5/10)
		 *
		 * Total: 6/10
		 *
		 * A file containing failed tasks has been generated in /Users/<user>/failed_tasks.txt
		 *
		 */

		std::cout << termcolor::italic << termcolor::yellow <<
		std::setw(25) << std::left << fileName << termcolor::reset;

		// TODO: handle the case when the file is not a .c file
		if (fileName.find(".c") == std::string::npos) {
			// TODO: Check which project contains the file
			// TODO: Give the file to the appropriate project checker
			if (!_checkScript(fileName))
				std::cout << KO;

			// todo: put all special case filenames in a vector
			if (fileName == "101-crackme_password")
				std::cout << NP;
			else
				std::cout << OK;

			// Set env CFILE=main.c
			setenv("CFILE", "main.c", 1);
			bool status = _taskProjectMap.at(fileName)(); // error while using [] instead of at()
			status ? std::cout << SUCCESS << std::endl : std::cout << FAILED << std::endl;


			// todo: put all special case filenames in a vector
			if (_flag != FILE || fileName == "101-crackme_password")
				return ;

			std::cout << "========== OUTPUT ==========" << std::endl;
			std::string cmd = "cat test_output/" + fileName + ".out";
			status = system(cmd.c_str());
			if (status != 0)
				_error(MSG("Failed to print output file"), 1);
			std::cout << "============================" << std::endl;
			return ;
		}

		// handle special case files
		try {
			bool status = _taskProjectMap.at(fileName)();
			status ? std::cout << NP << std::endl : std::cout << FAILED << std::endl;
//			status ? std::cout << SUCCESS << std::endl : std::cout << FAILED << std::endl;
			return ;
		} catch (const std::out_of_range& e) {}

		// Check the file using betty
		std::string cmd = "betty " + fileName + " > /dev/null 2>&1";
		int betty = system(cmd.c_str());
		!betty ? std::cout << OK : std::cout << KO;

		if (fileName.empty()) {
			_error(MSG("Project file is empty"), 0);
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
		std::string dependencies = getTaskFilesDependencies();
		std::string command = "gcc -I . " + _CFLAGS + " " + fileName + " " + dependencies + main + " -o " + "bin/" + executable;
		int compile = system(command.c_str());
		compile == -1 ? std::cout << KO : std::cout << OK;

		// Execute the compiled file and save the output in a file
		_output = (_flag == OUTPUT) ? _output : "test_output/" + executable + ".out";
		std::string redirect = (fileName == "101-quote.c") ? " 2> " : " > "; // because 101-quote.c prints to stderr
		command = "bin/" + executable + redirect + _output;
		int execute = system(command.c_str());
		if (fileName == "101-quote.c") execute = 0; // because 101-quote.c prints to stderr
		execute == -1 ? std::cout << KO : std::cout << OK;

		// Compare the output with the expected output
		std::string expectedOutput = "expected_output/" + executable + ".out";
		command = "diff test_output/" + executable + ".out " + expectedOutput;
		int diff = system(command.c_str());
		diff == -1 ? std::cout << KO : std::cout << OK;

		if (betty == 0 && compile == 0 && execute == 0 && diff == 0)
			std::cout << SUCCESS << std::endl;
		else
			std::cout << FAILED << std::endl;

		if (_flag == FILE) {

			std::cout << std::endl;
			std::cout << "\n================================================  OUTPUT  ================================================\n" << std::endl;

			std::cout << termcolor::underline << termcolor::bold
					  << termcolor::bright_white <<  "Your output" << termcolor::reset << std::endl;
			printFileContent(_output);

			std::cout << termcolor::underline << termcolor::bold
					  << termcolor::bright_white <<  "Expected output" << termcolor::reset << std::endl;
			printFileContent(expectedOutput);

			std::cout << "==========================================================================================================" << std::endl;
		}

	} /* _checkProjectFile */

	std::string Checker::getTaskFilesDependencies() const {

		std::string dependencies = "";
		std::string testFilesPath = _projectPath + "/test_files/";

		for (const auto& file : fs::directory_iterator(testFilesPath)) {
			std::string fileName = file.path().filename().string();

			// check if the filename contains the string main
			if (fileName.find("main") == std::string::npos) {
				dependencies += testFilesPath + fileName + " ";
			}
		} /* for */

		return dependencies;
	}

	// todo: fix update
	void Checker::_update() const {

		int status;

		std::string cloneCommand = "git clone https://github.com/achrafelkhnissi/alx-checker.git ~/.alx-checker";
		std::string cmakeCommand = "cmake -B build && cmake --build build";
		std::string alxPath_ = std::string(getenv("HOME")) + "/.alx-checker";

		// TODO: check if the program is running as root

		_cout.info("Updating alx-checker...\n");

		// check if the directory exists
		if (directoryExists(alxPath_)) {

			// change the current directory to the cloned repository
			status = chdir(alxPath_.c_str());
			if (status != 0) {
				_error(MSG("Failed to change the current directory"), 0);
			}

			// pull the latest changes
			status = system("git pull");
			if (status != 0) {

				status = chdir(_projectPath.c_str());
				if (status != 0) {
					_error(MSG("Failed to change the current directory"), 0);
				}

				std::cout << "Removing ~/.alx-checker..." << std::endl;
				std::string rmCommand =  _sudo + "rm -rf " + alxPath_;
				status = system(rmCommand.c_str());
				if (status != 0) {
					_error(MSG("Failed to remove ~/.alx-checker"), 0);
				}

				// clone the repository
				status = system(cloneCommand.c_str());
				if (status != 0) {
					_error(MSG("Failed to clone the repository"), 0);
				}

				// change the current directory to the cloned repository
				status = chdir(alxPath_.c_str());
				if (status != 0) {
					_error(MSG("Failed to change the current directory"), 0);
				}

			}
		}

		// build the project
		status = system(cmakeCommand.c_str());
		if (status != 0) {
			_error(MSG("Failed to build the project"), 0);
		}


		// check if the alx-checker/bin directory is in the PATH
		std::string path = getenv("PATH");
		std::string alxPath = std::string(getenv("HOME")) + "/.alx-checker/bin";
		if (path.find(alxPath) == std::string::npos) {

			// get the shell
			std::string shell = getenv("SHELL");

			// get the shellrc
			std::string shellrc = std::string(getenv("HOME")) + "/." + shell + "rc";

			// add the executable to the PATH
			std::string exportCommand = "echo \"export PATH=$PATH:" + alxPath + "\" >> " + shellrc;
			status = system(exportCommand.c_str());
			if (status != 0) {
				_error(MSG("Failed to add the executable to the PATH"), 0);
			}
		}

		// Check if the alx-checker is installed
		status = system("which alx-checker");
		if (status != 0) {
			_error(MSG("Failed to update alx-checker"), 0);
		}

		std::cout << "alx-checker updated successfully!" << std::endl;

	} /* update */

	void Checker::footer() const {
		std::cout << std::endl;
		std::cout << "Thank you for using " << termcolor::bold << "alx-checker!" << termcolor::reset << std::endl;
		std::cout << "If you have any questions or suggestions or bug reports,"
				  << " please contact me at "
				  << termcolor::yellow << "@suprivada" << termcolor::reset
				  << " on Twitter." << std::endl;
		std::cout << std::endl;
	}

	void Checker::_error(const std::string &msg, int err) const {
		std::string errorMsg = msg + (!err ? "." : (std::string(" | ") + strerror(errno)));
		throw std::runtime_error(errorMsg);
	}

} /* namespace alx */
