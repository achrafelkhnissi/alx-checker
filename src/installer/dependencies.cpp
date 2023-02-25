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

    void Installer::installDependencies() const {
        if (!_dependencies.empty())
            _cout.info("Installing dependencies...");
        for (auto &dependency: _dependencies) {
            if (!checkDependency(dependency)) {
                _cout.print( "\t-Executing: `sudo " + _packageManager + " install -y " + dependency + "`...\n", YELLOW);
                installDependency(dependency);
            }
        }
        if (!_dependencies.empty())
            _cout.success("\tDependencies installed successfully.");
    }

    void Installer::installDependency(const std::string &dependency) const {
        std::string command = "sudo " + _packageManager + " install -y " + dependency;
        system(command.c_str());
    }

    const std::vector<std::string> &Installer::getDependencies() const {
        return _dependencies;
    }

    void Installer::setDependencies(const std::vector<std::string> &dependencies) {
        _dependencies = dependencies;
    }

} /* namespace alx */