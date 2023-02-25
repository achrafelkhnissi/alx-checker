//
// Created by Achraf El khnissi on 2/25/23.
//

#include "Installer.hpp"

namespace alx {

    void Installer::checkDependencies() const {
        for (auto &dependency: _dependencies) {
            if (!checkDependency(dependency))
                std::cout << "Dependency `" << dependency << "` is not installed." << std::endl;
        }
    }

    bool Installer::checkDependency(const std::string &dependency) const {
        std::string command = "which " + dependency + " > /dev/null 2>&1";
        return system(command.c_str()) == 0;
    }

    void Installer::installDependencies() const {
        for (auto &dependency: _dependencies) {
            if (!checkDependency(dependency)) {
                std::cout << "Executing: `sudo " << _packageManager << " install " << dependency << "`..." << std::endl;
                installDependency(dependency);
            }
        }
    }

    void Installer::installDependency(const std::string &dependency) const {
        std::string command = "sudo " + _packageManager + " install " + dependency;
        system(command.c_str());
    }

    const std::vector<std::string> &Installer::getDependencies() const {
        return _dependencies;
    }

    void Installer::setDependencies(const std::vector<std::string> &dependencies) {
        _dependencies = dependencies;
    }

} /* namespace alx */