#include "Installer.hpp"

/**
 * @name alx namespace
 * @brief The alx namespace
 * @details This namespace contains all the classes and functions of the alx-checker project
 */
namespace alx {

    /**
 * @name Installer
 * @return bool: true if the program is running on MacOS, false otherwise
 */
    bool Installer::isMacos() const {
#ifdef __APPLE__
        return true;
#else
        return false;
#endif
    }

    /**
     * @name isLinux
     * @return bool: true if the program is running on Linux, false otherwise
     */
    bool Installer::isLinux() const {
#ifdef __linux__
        return true;
#else
        return false;
#endif
    }

    /**
     * @name isRunningAsRoot
     * @return bool: true if the program is running as root, false otherwise
     */
    bool Installer::isRunningAsRoot() const {
        return getuid() == 0;
    }


    /**
     * @name checkBetty
     * @return bool: true if betty is installed, false otherwise
     */
    bool Installer::checkBetty() const {
        return system("betty --version &> /dev/null");
    }


    /**
     * @name getHomeDir
     * @brief Gets the home directory of the user
     * @return $HOME env
     */
    std::string Installer::getHomeDir() const {
        return std::getenv("HOME");
    } /* getHomeDir */

    /**
     * @name directoryExists
     * @brief Checks if a directory exists
     * @param dirPath: path to the directory
     * @return true if the directory exists, false otherwise
     */
    bool Installer::directoryExists(const std::string &dirPath) const {
//    return std::filesystem::is_directory(dirPath);
        struct stat info{};

        return stat(dirPath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
    }


    bool Installer::isFtStudent() const {
        std::string goinfre = getHomeDir() + "/goinfre";
        return directoryExists(goinfre);
    } /* isFtStudent */

}
