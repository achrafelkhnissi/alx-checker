//
// Created by Achraf El khnissi on 2/24/23.
//

#ifndef ALX_CHECKER_INSTALLER_HPP
#define ALX_CHECKER_INSTALLER_HPP

#include <iostream>        // std::cout, std::cerr
#include <string>        // std::string
#include <vector>        // std::vector
#include <cstdlib>        // EXIT_SUCCESS
#include <unistd.h>        // access, getuid
#include <cstdlib>        // system
#include <fstream>        // std::ifstream
#include <sys/stat.h>    // stat
#include <filesystem>

#include "Printer.hpp" // TODO: make "Printer.hpp" work!

namespace alx {

    class Installer {

    private:
        mutable std::vector<std::string> _dependencies;
        Printer _cout;

        bool _isMacos;
        bool _isLinux;
        bool _isRoot;
        bool _isFtStudent;

        std::string _packageManager;

    public:

        /* Constructors & Destructor */
        Installer();

//        Installer(int ac, char **av);

        Installer(const std::vector<std::string> &dependencies);

        ~Installer();

        /* Installer main methods */
        void install() const;

        void uninstall() const;

        void update() const;

        void usage() const;

        void check() const;

        void checkArgs(int argc, char *argv[]) const;

        bool checkBetty() const;


        bool isMacos() const;

        bool isLinux() const;

        bool isRunningAsRoot() const;

        bool isFtStudent() const;


        std::string getHomeDir() const;

        bool directoryExists(const std::string &dirPath) const;


        /* Dependencies Methods */
        bool checkDependency(const std::string &dependency) const;

        void checkDependencies() const;

        void installDependency(const std::string &dependency) const;

        void installDependencies() const;

        const std::vector<std::string> &getDependencies() const;

        void setDependencies(const std::vector<std::string> &dependencies);
        /* End of Dependencies Methods */


        /* Install Methods */


        void installSvn() const;

        void installBetty() const;

        void installBrew() const;


    }; /* class Installer */

} /* namespace alx */



#endif //ALX_CHECKER_INSTALLER_HPP
