/**
 * @file Installer.cpp
 * @brief Installer class implementation
 * @author Achraf El Khnissi
 */

#include "Installer.hpp"

/**
 * @name alx namespace
 * @brief The alx namespace
 * @details This namespace contains all the classes and functions of the alx-checker project
 */
namespace alx {

    Installer::Installer() : _cout() {

		_sudo = "";

        _isMacos = isMacos();
        _isLinux = isLinux();
        _isRoot = isRunningAsRoot();
        _isFtStudent = isFtStudent();
        _packageManager = _isMacos ? "brew" : "apt-get";

		std::string command = "which " + _packageManager;
		int status = system(command.c_str());
		if (status != 0) {
			if (_isMacos) {
				std::cout << "Brew not installed!" << std::endl;
				installBrew();
			} else {
				// TODO: install apt-get
			}
		} else {
			std::cout << _packageManager <<  " already installed!" << std::endl;
		}

        _dependencies = {
                "svn",
                "betty",
        };
    } /* End of constructor */

//    Installer::Installer(int ac, char **av) : _cout() {
//        _isMacos = isMacos();
//        _isLinux = isLinux();
//        _isRoot = isRunningAsRoot();
//        _isFtStudent = isFtStudent();
//        _packageManager = _isMacos ? "brew" : "apt-get";
//
//        checkArgs(ac, av);
//    }

    Installer::Installer(const std::vector<std::string> &dependencies) : _cout() {
        _isMacos = isMacos();
        _isLinux = isLinux();
        _isRoot = isRunningAsRoot();
        _isFtStudent = isFtStudent();
        _packageManager = _isMacos ? "brew" : "apt-get";

        _dependencies = dependencies;
    }


    Installer::~Installer() {}

    void Installer::install() const {
//        std::cout << "Installing alx-checker..." << std::endl;
//        installDependencies();
//        std::cout << "alx-checker installed successfully." << std::endl;
    }

    void Installer::uninstall() const {
        /* TODO: Implement uninstall method */
    }

    void Installer::update() const {
        /* TODO: Implement update method */
    }

    void Installer::usage() const {
        _cout.print("Usage: <Installer-name> [OPTION]", "GREEN");
        _cout.print("Options:", "GREEN");
        _cout.print("  -i, --install", "GREEN");
        _cout.print("  -u, --uninstall", "GREEN");
        _cout.print("  -c, --check", "GREEN");
        _cout.print("  -h, --help", "GREEN");
        _cout.print("  -v, --version", "GREEN");
    }


    void Installer::check() const {
        /* TODO: Implement check method */
    }

//    void Installer::checkArgs(int argc, char **argv) const {
//
//    }

} /* namespace alx */
