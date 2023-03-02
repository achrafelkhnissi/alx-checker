/**
 * @file Checker.cpp
 * @brief Checker class implementation
 * @author Achraf El Khnissi
 * @version 1.0
 */

#include "Checker.hpp"

namespace alx {

    Checker::Checker() : _cout(), _installer() {
		_projectPath = fs::current_path();
		_project = _projectPath.filename();
		_testFilesUrl += _project.string() + "/test_files";

		std::cout << "Project: " << _project << std::endl;
		std::cout << "Project path: " << _projectPath << std::endl;
		std::cout << "Test directory: " << _testFilesUrl << std::endl;

		_installer.checkDependencies();
		if (!_installer.getDependencies().empty())
			_installer.installDependencies();
		else
			_cout.info("No dependencies to install.");
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
        exit(EXIT_SUCCESS);
    }

    void Checker::checkArgs(int argc, char *argv[]) {
        if (argc > 2) {
            usage();
            throw std::invalid_argument("Too many arguments.");
        }

        std::string file;
        std::string log;

        for (int i = 1; i < argc; i++) {
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
            } else if (strcmp(argv[i], "-l") == 0 || strcmp(argv[i], "--log") == 0) {
                if (i + 1 < argc) {
                    _log.assign(argv[i + 1]);
                    i++;
                } else
                    throw std::invalid_argument("-l or --log option requires one argument.");
            } else
                throw std::invalid_argument("Unknown option " + std::string(argv[i]));
        }

        if (file.empty())
            throw std::invalid_argument("No file specified.");
    } /* checkArgs */

    void Checker::printVersion() const {
//        std::cout << "alx-checker version " << ALX_CHECKER_VERSION << std::endl;
    }

    bool Checker::directoryExists(const std::string &path) const {
        struct stat info{};
        if (stat(path.c_str(), &info) != 0) {
            return false;
        } else if (info.st_mode & S_IFDIR) {
            return true;
        } else {
            return false;
        }
    } /* directoryExists */

    bool Checker::_isRunningAsRoot() const {
        return getuid() == 0;
    }

//    void Checker::checkProject() const {
//        _cout.print("Checking project " + _project.string(), GREEN);
//        _cout.print("Checking for betty...", GREEN);
//        if (checkBetty() == STATUS_KO) {
//            if (isRunningAsRoot()) {
//                installBetty();
//            } else {
//                _cout.print("Error: betty is not installed.", RED);
//                _cout.print("You must be root to install betty.", RED);
//                _cout.print("Please run the checker as root.", RED);
//                _cout.print("Example: sudo alx-checker", RED);
//                exit(EXIT_FAILURE);
//            }
//        } else {
//            _cout.print("betty is already installed.", GREEN);
//        }
//    } /* checkProject */
//
//    bool Checker::checkBetty() const {
//        return system("betty --version &> /dev/null");
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

	}

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

	}

	void Checker::_printTestFiles() const {
		std::cout << std::endl;
		_cout.print("Test files:", GREEN);
		for (const auto &file : _testFiles) {
			std::cout << "\t" << file.first << std::endl;
			std::cout << "\t\t" << file.second << std::endl;
		}
		std::cout << std::endl;
	}
	/* _downloadTests */


} /* namespace alx */
