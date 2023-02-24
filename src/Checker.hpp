/**
 * @file Checker.hpp
 * @brief Checker class definition
 * @author Achraf El Khnissi
 * @version 1.0
 * @date 2021-02-23
 */

#ifndef ALX_CHECKER_CHECKER_HPP
#define ALX_CHECKER_CHECKER_HPP

#include <iostream>		// std::cout, std::cerr
#include <filesystem>	// std::filesystem
#include <string>		// std::string
#include <cstring>		// strcmp
#include <sys/stat.h>	// stat
#include <algorithm>	// std::transform
#include <cstdlib>		// EXIT_SUCCESS
#include <fstream>		// std::ifstream
#include <unistd.h>		// access, getuid
#include <map>			// std::map
#include <dirent.h>		// opendir, readdir, closedir

#include "Print.hpp"
#include "Installer.hpp"

namespace fs = std::filesystem;

#define ALX_CHECKER_VERSION "0.1"

namespace alx {

	class Checker {

	private:
		typedef std::map<std::string, std::string> tests_t;

	private:
		Print		_cout;
		Installer	_installer;

		std::string	_checkerRepository = "https://github.com/achrafelkhnissi/alx-checker/trunk";
//
//		fs::path _projectPath;
//		fs::path _project;

		std::string	_file;
		std::string	_log;

		mutable tests_t _testFiles; // mutable to be able to use it in const methods

	public:
		Checker();
		~Checker();

		void usage() const;
		void checkArgs(int argc, char *argv[]);
		void check() const;

		bool directoryExists(const std::string& path) const;

		void checkDependencies() const;
		void installDependencies() const;
		void installSvn() const;

		void downloadTests(void) const;

		void checkProject() const;
		bool checkBetty() const;
		void installBetty() const;
		void checkReadme() const;
		bool isRunningAsRoot() const;


		void copyDirectoryContent() const;

		void printVersion() const;


	}; /* class Checker */

} /* namespace alx */


#endif /* ALX_CHECKER_CHECKER_HPP */
