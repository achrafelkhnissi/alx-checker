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
#include <cctype>                // std::tolower

#include "Printer.hpp"
#include "Installer.hpp"
#include "config.hpp"

namespace fs = std::filesystem;

#define OK termcolor::green << std::setw(20) << std::left << "OK" << termcolor::reset
#define KO termcolor::red << std::setw(20) << std::left << "KO" << termcolor::reset
#define FAILED termcolor::red << std::setw(20) << std::left << "FAILED" << termcolor::reset
#define SUCCESS termcolor::green << std::setw(20) << std::left << "SUCCESS" << termcolor::reset
#define NP termcolor::bright_grey << std::setw(20) << std::left << "NOT PRESENT" << termcolor::reset

namespace alx {

	enum option { HELP, VERSION, TEST, ALL, FILE, INSTALL, UNINSTALL, UPDATE, OUTPUT, DIFF};

    class Checker {

    private:

		typedef std::map<std::string, std::string> files_t;

    private:
        Printer _cout;
        Installer _installer;

		std::string _sudo;

		std::string _testFilesUrl = "https://github.com/achrafelkhnissi/";
        std::string _checkerRepository = "https://github.com/achrafelkhnissi/alx-checker/trunk";

//        fs::path _projectPath;  // error: 'path' is unavailable: introduced in macOS 10.15
//        fs::path _project;

		std::string _projectPath;
		std::string _project;

		enum option _flag = ALL;

        std::string _file;
        std::string _output;

        files_t _testFiles; // mutable to be able to use it in const methods
		files_t _projectFiles;

		std::string _CFLAGS = "-Wall -Wextra -Werror -pedantic -std=c99";

		std::map<std::string, std::map<std::string, bool(*)(void)> > _projectMap;
		std::map<std::string, bool(*)(void)> _taskMap;

    public:
        Checker();
		Checker(int ac, char** av);

        ~Checker();

		void banner() const;

        void usage() const;

        void checkArgs(int argc, char *argv[]);

        void check() const;

		void _update() const;

        bool directoryExists(const std::string &path) const;

        void downloadTests(void) const;

        void checkProject();

        void checkReadme() const;

		void _readDirectory(const std::string& directoryPath, files_t& files) const;
		void _printTestFiles() const;

        void printVersion() const;

		bool _isRunningAsRoot() const;

		void _checkTask(const std::string &file);

		std::string _getBasename(const std::string &path) const;

		std::string getParentDirectory(const std::string &path);

		std::string _getMainFile(const std::string &file) const;

		std::string _getCorrectOutput(const std::string &file) const;

		int diff(const std::string &correctOutput, const std::string &output);

		int compile(const std::string &file, const std::string &output);

		int createDirectory(const std::string &path);

		std::string _getCurrentDirectory() const;

		bool _is0x00(const std::string &file) const;

		void initTaskMap();

		bool _checkScript(const std::string &file) const;

		std::string _upperCase(const std::string &str) const;

		void footer() const;

		void initProjectMap();
	}; /* class Checker */

} /* namespace alx */


#endif /* ALX_CHECKER_CHECKER_HPP */
