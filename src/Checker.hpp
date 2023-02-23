/**
 * @file Checker.hpp
 * @brief Checker class definition
 * @author Achraf El Khnissi
 * @version 1.0
 * @date 2021-02-23
 */

#ifndef ALX_CHECKER_CHECKER_HPP
#define ALX_CHECKER_CHECKER_HPP

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace alx {

	class Checker {

	private:
		fs::path _projectPath;
		fs::path _project;


	public:
		Checker();
		~Checker();

	};

}


#endif //ALX_CHECKER_CHECKER_HPP
