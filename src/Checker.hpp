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

#include "Print.hpp"

namespace fs = std::filesystem;

#define ALX_CHECKER_VERSION "0.1"

namespace alx {

	class Checker {

	private:
		Print _cout;

		fs::path _projectPath;
		fs::path _project;

		std::string	_file;
		std::string	_log;

	public:
		Checker();
		~Checker();

		void usage() const;
		void checkArgs(int argc, char *argv[]);
		void check() const;

		bool directoryExists(const std::string& path) const;

	};

}


#endif //ALX_CHECKER_CHECKER_HPP
