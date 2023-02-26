/**
 * @file Checker.cpp
 * @brief Checker class implementation
 * @author Achraf El Khnissi
 * @version 1.0
 * @date 2021-02-23
 */

#include "Checker.hpp"

namespace alx {

    Checker::Checker() : _cout(), _installer() {
		_projectPath = fs::current_path();
		_project = _projectPath.filename();

                std::cout << "Project: " << _project << std::endl;
                std::cout << "Project path: " << _projectPath << std::endl;

		_installer.checkDependencies();
		if (!_installer.getDependencies().empty()) {
			_installer.installDependencies();
		}
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
        std::cout << "alx-checker version " << ALX_CHECKER_VERSION << std::endl;
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


//    void Checker::downloadTests(void) const {
//
//        std::string url = _checkerRepository + "/" + _project.string();
//        std::string cmd = "svn export " + url + "/tests";
//
//        int status = system(cmd.c_str());
//        if (status != 0) {
//            throw std::runtime_error("Failed to download tests."); // TODO: change the name of the directory ?
//        } else {
//            _cout.print("Tests downloaded successfully.", GREEN);
//        }
//    } /* downloadTests */

//    bool Checker::isRunningAsRoot() const {
//        return getuid() == 0;
//    }

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


    void Checker::copyDirectoryContent() const {

        DIR *dir;
        struct dirent *entry;

        std::string testsDirectory = "tests";

        if (!(dir = opendir(testsDirectory.c_str()))) {
            throw std::runtime_error("Failed to open <" + testsDirectory + "> directory");
        }

        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_REG) { // check if file is a regular file
                std::string filePath = testsDirectory + "/" + entry->d_name;
                std::ifstream fileStream(filePath);
                std::string fileContent((std::istreambuf_iterator<char>(fileStream)),
                                        std::istreambuf_iterator<char>());
                _testFiles[entry->d_name] = fileContent;

                std::cout << GREEN << "File: " << std::string(entry->d_name).at(0) << END << std::endl;
                // std::cout << fileContent << std::endl;
            }
        }

        closedir(dir);

    } /* copyDirectoryContent */


} /* namespace alx */
