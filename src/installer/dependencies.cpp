/**
 * @file dependencies.cpp
 * @brief Installer dependencies functions implementation
 * @details This file contains the implementation of the functions used to install the dependencies of the alx-checker project
 * @author Achraf El Khnissi
 * @date Wednesday, March 1 2023
 */

#include "Installer.hpp"

namespace alx {

    void Installer::checkDependencies() const {
        _cout.info("Checking dependencies...");
		auto it = _dependencies.begin();
		while (it != _dependencies.end()) {
			if (checkDependency(*it)) {
				_cout.print("\t-Dependency `" + *it + "` is installed.", GREEN);
				it = _dependencies.erase(it);
				it = _dependencies.begin();
			} else {
				_cout.print("\t-Dependency `" + *it + "` is not installed.", RED);
				++it;
			}
		}
	}

    bool Installer::checkDependency(const std::string &dependency) const {
		if (dependency == "subversion") // TODO: find a better way to check for svn
			return system("which svn > /dev/null 2>&1") == 0;

        std::string command = "which " + dependency + " > /dev/null 2>&1";
        return system(command.c_str()) == 0;
    }

	void Installer::_deleteDependency(const std::string &dependency) const {
		// _dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), dependency), _dependencies.end());
	    _dependencies.erase(std::remove_if(_dependencies.begin(), _dependencies.end(), [dependency](const std::string& s){ return s == dependency; }), _dependencies.end());

	}

    void Installer::installDependencies() const {
        if (!_dependencies.empty())
            _cout.info("Installing dependencies...");
        for (auto &dependency: _dependencies) {
                _cout.print("\t-Executing: `" + _sudo + " " + _packageManager + " install " + dependency + "`...\n", YELLOW);
                installDependency(dependency);
        }
		std::cout << "Dependencies is " << (_dependencies.empty() ? "empty" : "not empty") << std::endl;
		if (_dependencies.empty()) {
			_cout.success("\tDependencies installed successfully.");
		}
    }

    void Installer::installDependency(const std::string &dependency) const {
        std::string command = _sudo + " " + _packageManager + " install " + dependency;

		int status;

		if (dependency == "betty")
			status = installBetty();
		else
			status = system(command.c_str());

		if (status != 0) {
			_cout.error("\t\t-Error while installing `" + dependency + "`.");
		} else
			_deleteDependency(dependency);
	}

    const std::vector<std::string> &Installer::getDependencies() const {
        return _dependencies;
    }

    void Installer::setDependencies(const std::vector<std::string> &dependencies) {
        _dependencies = dependencies;
    }

} /* namespace alx */