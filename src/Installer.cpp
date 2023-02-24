#include "Installer.hpp"

namespace alx {

	Installer::Installer() : _dependencies() { }

	Installer::~Installer() {}

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
	 * @name checkDependencies
	 * @brief Checks if the dependencies are installed
	 * @details This function checks if the following dependencies are installed:
	 * 		- svn (subversion) to download the tests
	 * 		- betty (linter) to check the code style
	 */
	void Installer::checkDependencies() const {

		int status = system("command -v svn &> /dev/null");
		if (status != 0) {
			_dependencies.push_back("subversion");
			return;
		} else {
			_cout.print("svn is installed.", GREEN);
		}

		if (checkBetty() == STATUS_KO) {
			_dependencies.push_back("betty");
		} else {
			_cout.print("betty is installed.", GREEN);
		}

	} /* checkDependencies */

	void Installer::installDependencies() const {

		if (_dependencies.empty()) {
			_cout.print("All dependencies are installed.", GREEN);
			return;
		}

		std::string cmd = "sudo apt-get install ";
		for (auto dep : _dependencies) {

			if (dep == "betty") {

				if (checkBetty() == STATUS_KO) {
					installBetty();
					// remove betty from the dependencies list
					_dependencies.remove("betty");
					_dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), "betty"), _dependencies.end());
				}
				continue;
			}

			int status = system(cmd.c_str() + dep);
			if (status != 0) {
				_cout.print("Error: failed to install " + dep, RED);
				exit(EXIT_FAILURE);
			} else {
				_cout.print(dep + " installed successfully.", GREEN);
			}

		}

	}

	/**
	 * @name installSvn
	 * @brief Installs svn
	 * @details This function does the following:
	 * 		- Asks the user if he wants to install svn
	 * 		- If yes, it installs svn
	 * 		- If no, it exits the program
	 */
	void Installer::installSvn() const {

		std::cout << "Error: svn is not installed. Do you want to install it? [y/n]";

		std::string answer;
		std::getline(std::cin, answer);
		std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		if (answer != "y" && answer != "yes") {
			std::cout << "OK. Bye!" << std::endl;
			exit(EXIT_SUCCESS);
		}

		int status = system("sudo apt-get install subversion");
		if (status != 0) {
			_cout.print("Error: svn is not installed.", RED);
			exit(EXIT_FAILURE);
		}

		// remove svn from the dependencies list
		_dependencies.remove("svn");
	} /* installSvn */

	/**
	 * @name checkBetty
	 * @return bool: true if betty is installed, false otherwise
	 */
	bool Installer::checkBetty() const {
		return system("betty --version &> /dev/null");
	}


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
	void Installer::installBetty() const {

		std::cout << "Error: betty is not installed. Do you want to install it? [y/n]: ";

		std::string answer;
		std::getline(std::cin, answer);
		std::transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

		if (answer != "y" && answer != "yes") {
			std::cout << "OK. Bye!" << std::endl;
			exit(EXIT_SUCCESS);
		}

		int status = system("git clone https://github.com/holbertonschool/Betty.git && cd Betty && ./install.sh && cd .. && rm -rf Betty");
		if (status != 0) {
			_cout.print("Error: Cloning betty repo failed.", RED);
			exit(EXIT_FAILURE);
		} else {
			_cout.print("Betty repo cloned successfully.", GREEN);
		}

		std::ofstream file("/betty");
		status = system("chmod +x /usr/local/bin/betty");
		if (status != 0) {
			throw std::runtime_error("Failed to give betty execute permission");
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

		_cout.success("betty installed successfully.");

		// remove betty from the dependencies list
		_dependencies.remove("betty");

	} /* installBetty */


} /* namespace alx */
