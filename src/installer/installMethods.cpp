//
// Created by Achraf El khnissi on 2/25/23.
//

#include "Installer.hpp"
#include <algorithm>
#include <cstring>

namespace alx {


    /**
     * @name installBetty
     * @brief Installs the Betty linter
     * @details This functions does the following:
     * 		- Clones the Betty repo
     * 		- Installs Betty by running the install.sh script
     * 		- This script installs the betty-doc and betty-style scripts
     * 		- betty-doc: checks for documentation
     * 		- betty-style: checks for style
     * 		- Creates a wrapper script called betty that runs both scripts
     * 		- Gives the wrapper script execute permission
     * 		- This wrapper script is placed in /usr/local/bin
     */
    int Installer::installBetty() const {

        std::cout << "Error: betty is not installed. Do you want to install it? [y/n]: ";

        std::string answer;
        std::getline(std::cin, answer);
        std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

        if (answer != "y" && answer != "yes") {
            std::cout << "OK. Bye!" << std::endl;
			return EXIT_SUCCESS;
        }

        int status = system(
            "git clone https://github.com/holbertonschool/Betty.git && cd Betty && ./install.sh && cd .. && rm -rf Betty");
        if (status != 0) {
            std::cout << "Error: Cloning betty repo failed." << std::endl;
            return EXIT_FAILURE;
        } else {
            std::cout << "Betty cloned successfully." << std::endl;
        }

        std::ofstream file("/betty");
        status = system("chmod +x /usr/local/bin/betty");
        if (status != 0) {
			return EXIT_FAILURE;
//            throw std::runtime_error("Failed to give betty execute permission");
        }
        file << "#!/bin/bash\n";
        file << "# Simply a wrapper script to keep you from having to use betty-style\n";
        file << "# and betty-doc separately on every item.\n";
        file << "# Originally by Tim Britton (@wintermanc3r), multiargument added by\n";
        file << "# Larry Madeo (@hillmonkey)\n";
        file << "\n";
        file << "BIN_PATH=\"/usr/local/bin\"\n";
        file << "BETTY_STYLE=\"betty-style\"\n";
        file << "BETTY_DOC=\"betty-doc\"\n";
        file << "\n";
        file << "if [ \"$#\" = \"0\" ]; then\n";
        file << "    echo \"No arguments passed.\n";
        file << "    exit 1\n";
        file << "fi\n";
        file << "\n";
        file << "for argument in \"$@\"; do\n";
        file << "    echo -e \"\\n========== $argument ==========\"\n";
        file << "    ${BIN_PATH}/${BETTY_STYLE} \"$argument\"\n";
        file << "    ${BIN_PATH}/${BETTY_DOC} \"$argument\"\n";
        file << "done\n";
        file.close();

        std::cout << "Betty installed successfully! You can now run betty to check for style and documentation."
                  << std::endl;

        // remove betty from the dependencies list
        _dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), "betty"), _dependencies.end());

		return EXIT_SUCCESS;
    } /* installBetty */


    /**
  * @name installBrew
  * @brief Installs Homebrew
  * @details This function does the following:
  */
    void Installer::installBrew() const {


        /**
         * Things to consider:
         * 1. Mehod 1: Install brew using the install script
         *     - /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
         * 2. Method 2: Install brew using the install script and downgrade brew to 3.2.17
         * 3. Method 3: Install brew using the install script and downgrade brew to 3.2.17 and install valgrind
         *
         * Mantual installation:
         * 1. Using curl: Using curl
         *     - mkdir homebrew
         *     - curl -L https://github.com/Homebrew/brew/tarball/master
         *     - tar xz --strip 1 -C homebrew
         *
         * 2. Using git: Using git
         *    - git clone https://github.com/Homebrew/brew homebrew
         *
         * 3 Then add homebrew/bin to your PATH in ~/.bash_profile or ~/.zshrc:
         *    - eval "$(~/goinfre/homebrew/bin/brew shellenv)"
         *    - brew update --force --quiet
         *    - chmod -R go-w "$(brew --prefix)/share/zsh"
         */

        int status;
        std::string sudo = "sudo";
        std::string goinfre;
        std::string installDirectory = "/usr/local/Homebrew";
//                std::string     uninstallCommand = "/bin/bash -c \"$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/uninstall.sh)\"";
//                std::string     installCommand = "/bin/bash -c \"$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\"";
        std::string installCommand;
        std::string uninstallCommand;


        /*
         * NOTES:
         * 1. Brew binaries exits in "/goinfre/.brew/bin/" for FT students
         * 2. Brew binaries exits in "/usr/local/bin/" for non-FT students
         * 3. downgrade brew to 3.2.17 which can install valgrind for FT students
         *              * export HOMEBREW_NO_AUTO_UPDATE=1  //  prevent brew from updating itself
         *
         */

        if (_isFtStudent) {
            // TODO: Saparate the steps for installing brew and print each step
            sudo = "";
            goinfre = getHomeDir() + "/goinfre";
            installDirectory = goinfre + "/homebrew";
            installCommand = "git clone https://github.com/Homebrew/brew " + installDirectory +
                             " && eval \"$(" + installDirectory + "/bin/brew shellenv)\"" +
                             " && brew update --force --quiet" +
                             " && chmod -R go-w \"$(brew --prefix)/share/zsh\"";
            uninstallCommand = "rm -rf " + installDirectory;
        }


        if (directoryExists(installDirectory)) {
            status = system(uninstallCommand.c_str());
        }

        status = system(installCommand.c_str());
        if (status != 0) {
            throw std::runtime_error("Failed to install Homebrew [exit code: " + std::to_string(status) + "] " +
                                     "[errno: " + std::to_string(errno) + "] " +
                                     "[error message: " + std::strerror(errno) + "]");
        }

        _cout.print("Homebrew installed successfully!", GREEN);
    } /* installBrew */

} /* namespace alx */
