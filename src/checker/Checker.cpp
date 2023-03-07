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
            usage();
            throw std::invalid_argument("Too many arguments.");
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
		std::cout << std::setw(20) << std::left << "TASKS"
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
					throw std::runtime_error("README.md file is empty");
				readmeFound = true;
			}
		} /* for */
		std::cout << termcolor::italic << termcolor::yellow <<
		std::setw(20) << std::left << "README.md" << termcolor::reset;
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
		std::setw(20) << std::left << fileName << termcolor::reset;

		// TODO: handle the case when the file is not a .c file
		if (fileName.find(".c") == std::string::npos) {
			// TODO: Check which project contains the file
			// TODO: Give the file to the appropriate project checker
			if (!_checkScript(fileName))
				std::cout << KO;

			std::cout << OK;

			// Set env CFILE=main.c
			setenv("CFILE", "main.c", 1);
			bool status = _taskProjectMap.at(fileName)(); // error while using [] instead of at()
			status ? std::cout << SUCCESS << std::endl : std::cout << FAILED << std::endl;


			if (_flag != FILE)
				return ;

			std::cout << "========== OUTPUT ==========" << std::endl;
			std::string cmd = "cat test_output/" + fileName + ".out";
			status = system(cmd.c_str());
			if (status != 0) {
				throw std::runtime_error(strerror(errno));
			}
			std::cout << "============================" << std::endl;
			return ;
		}

		// Check the file using betty
		std::string cmd = "betty " + fileName + " > /dev/null 2>&1";
		int betty = system(cmd.c_str());
		!betty ? std::cout << OK : std::cout << KO;

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

	void Checker::footer() const {
		std::cout << std::endl;
		std::cout << "Thank you for using " << termcolor::bold << "alx-checker!" << termcolor::reset << std::endl;
		std::cout << "If you have any questions or suggestions or bug reports,"
				  << " please contact me at "
				  << termcolor::yellow << "@suprivada" << termcolor::reset
				  << " on Twitter." << std::endl;
		std::cout << std::endl;
	}

} /* namespace alx */
