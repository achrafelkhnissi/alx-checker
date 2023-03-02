/**
 * @file Checker.hpp
 * @brief Checker class definition
 * @author Achraf El Khnissi
 * @version 1.0
 * @date 2021-02-23
 */

#ifndef ALX_CHECKER_CHECKER_HPP
#define ALX_CHECKER_CHECKER_HPP

#include <iostream>                // std::cout, std::cerr
#include <filesystem>        // std::filesystem
#include <string>                // std::string
#include <cstring>                // strcmp
#include <sys/stat.h>        // stat
#include <algorithm>        // std::transform
#include <cstdlib>                // EXIT_SUCCESS
#include <fstream>                // std::ifstream
#include <unistd.h>                // access, getuid
#include <map>                        // std::map
#include <dirent.h>                // opendir, readdir, closedir

#include "Printer.hpp"
#include "Installer.hpp"
#include "config.hpp"

namespace fs = std::filesystem;

namespace alx {

    class Checker {

    private:

		typedef std::map<std::string, std::string> files_t;

    private:
        Printer _cout;
        Installer _installer;

		std::string _testFilesUrl = "https://github.com/achrafelkhnissi/";
        std::string _checkerRepository = "https://github.com/achrafelkhnissi/alx-checker/trunk";

//        fs::path _projectPath;  // error: 'path' is unavailable: introduced in macOS 10.15
//        fs::path _project;

		std::string _projectPath;
		std::string _project;

        std::string _file;
        std::string _output;

        files_t _testFiles; // mutable to be able to use it in const methods
		files_t _projectFiles;

    public:
        Checker();
		Checker(int ac, char** av);

        ~Checker();

		void banner() const;

        void usage() const;

        void checkArgs(int argc, char *argv[]);

        void check() const;

        bool directoryExists(const std::string &path) const;

        void downloadTests(void) const;

        void checkProject() const;

        void checkReadme() const;

		void _readDirectory(const std::string& directoryPath, files_t& files) const;
		void _printTestFiles() const;

        void printVersion() const;

		void printHelp() const;

		bool _isRunningAsRoot() const;

		void _checkProjectFile(const std::string &file) const;

		std::string getBasename(const std::string &path);

		std::string getParentDirectory(const std::string &path);
	}; /* class Checker */

} /* namespace alx */


#endif /* ALX_CHECKER_CHECKER_HPP */
