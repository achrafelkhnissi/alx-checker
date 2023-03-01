//
// Created by Achraf El khnissi on 2/25/23.
//

#include "Installer.hpp"

namespace alx {

    void Installer::checkDependencies() const {

        _cout.info("Checking dependencies...\n");
        for (auto &dependency: _dependencies) {
            if (!checkDependency(dependency)) {
                _cout.error("\t-Dependency `" + dependency + "` is not installed.");
            } else {
                _dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), dependency),
                                    _dependencies.end());
            }
        }
    }

    bool Installer::checkDependency(const std::string &dependency) const {
        std::string command = "which " + dependency + " > /dev/null 2>&1";
        return system(command.c_str()) == 0;
    }

	void Installer::_deleteDependency(const std::string &dependency) const {
		_dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), dependency), _dependencies.end());
	}

    void Installer::installDependencies() const {
        if (!_dependencies.empty())
            _cout.info("Installing dependencies...");
        for (auto &dependency: _dependencies) {
            if (!checkDependency(dependency)) {
                _cout.print("\t-Executing: `" + _sudo + " " + _packageManager + " install " + dependency + "`...\n", YELLOW);
                installDependency(dependency);
            }
        }
		std::cout << "Dependencies is " << (_dependencies.empty() ? "empty" : "not empty") << std::endl;
		if (_dependencies.empty()) {
			_cout.success("\tDependencies installed successfully.");
		}
    }

    void Installer::installDependency(const std::string &dependency) const {
        std::string command = _sudo + " " + _packageManager + " install " + dependency;
        int status = system(command.c_str());
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