//
// Created by Achraf El khnissi on 2/25/23.
//

#include "Installer.hpp"

namespace alx {

    void Installer::checkDependencies() const {
        for (auto &dependency: _dependencies) {
            if (!checkDependency(dependency)) {
                std::cout << "Dependency " << dependency << " is not installed." << std::endl;
            }
        }
    }

    bool Installer::checkDependency(const std::string &dependency) const {
        std::string command = "which " + dependency;
        return system(command.c_str()) == 0;
    }

    void Installer::installDependencies() const {
        std::cout << "Installing dependencies..." << std::endl;
        for (auto &dependency: _dependencies) {
            if (!checkDependency(dependency)) {
                installDependency(dependency);
            }
        }
    }

    void Installer::installDependency(const std::string &dependency) const {
        std::string command = "sudo apt install " + dependency;
        system(command.c_str());
    }

    const std::vector<std::string> &Installer::getDependencies() const {
        return _dependencies;
    }

    void Installer::setDependencies(const std::vector<std::string> &dependencies) {
        _dependencies = dependencies;
    }


}