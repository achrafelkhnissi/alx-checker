/**
 * @file Checker.cpp
 * @brief Checker class implementation
 * @author Achraf El Khnissi
 * @version 1.0
 * @date 2021-02-23
 */

#include "Checker.hpp"

namespace alx {

	Checker::Checker() {
		_projectPath = fs::current_path();
		_project = _projectPath.filename();
		std::cout << "Project path: " << _projectPath << std::endl;
		std::cout << "Project name: " << _project << std::endl;
	}

	Checker::~Checker() {
		// TODO
	}

}