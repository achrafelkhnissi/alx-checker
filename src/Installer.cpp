#include "Installer.hpp"

namespace alx {

	Installer::Installer() : _dependencies(), _animation(), _cout() {}

	Installer::~Installer() {}


	std::vector<std::string> Installer::getDependencies() const {
		return _dependencies;
	}

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

		int status = 0;

		if (isMacos()) {
			std::cout <<"MacOS detected." << std::endl;
		} else if (isLinux()) {
			std::cout <<"Linux detected." << std::endl;
		} else {
			std::cout << "Unsupported OS." << std::endl;
			exit(EXIT_FAILURE);
		}

		if (isRunningAsRoot()) {
			std::cout << "Running as root." << std::endl;
		} else {
			std::cout << "Running as user." << std::endl;
		}

//		if (isMacos()) {
//			_cout.print("Checking dependencies...", GREEN);
//			checkMacosDependencies();
//		} else if (isLinux()) {
//			_cout.print("Checking dependencies...", GREEN);
//			checkLinuxDependencies();
//		}
//
		if (isLinux()) {
			status = system("command -v apt-get &> /dev/null");
			if (status != 0) {
				std::cout << "Error: apt-get is not installed." << std::endl;
				_dependencies.push_back("apt-get");
				exit(EXIT_FAILURE);
			} else {
				std::cout << "apt-get is installed." << std::endl;
			}
		} else if (isMacos()) {
			status = system("command -v brew &> /dev/null");
			if (status != 0) {
				std::cout << "Error: brew is not installed." << std::endl;
				installBrew();
//				_dependencies.push_back("brew");
				exit(EXIT_FAILURE); // TODO: remove this line
			} else {
				std::cout << "brew is installed." << std::endl;
			}
		}

		status = system("command -v svn &> /dev/null");
		if (status != 0) {
			_dependencies.push_back("subversion");
			return;
		} else {
			std::cout << "subversion is installed." << std::endl;
		}

		if (checkBetty() == STATUS_KO) {
			_dependencies.push_back("betty");
		} else {
			std::cout << "betty is installed." << std::endl;
		}

	} /* checkDependencies */

	void Installer::installDependencies() const {

		std::cout << "Dependencies to install:" << std::endl;
		for (auto dep : _dependencies) {
			std::cout << dep << " ";
		}
		std::cout << std::endl;

		if (_dependencies.empty()) {
			std::cout << "All dependencies are installed." << std::endl;
			return;
		}

		std::string cmd = "sudo apt-get install ";
		for (auto dep : _dependencies) {

			if (dep == "betty") {
				installBetty();
				_dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), "betty"), _dependencies.end());
				continue;
			}


			cmd += dep;
			int status = system(cmd.c_str());
			if (status != 0) {
				std::cout << "Error: Failed to install " << dep << std::endl;
			} else {
				std::cout << dep << " installed successfully." << std::endl;
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
			std::cout << "Error: Failed to install svn." << std::endl;
			exit(EXIT_FAILURE);
		}

		// remove svn from the dependencies list
		_dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), "subversion"), _dependencies.end());
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
			std::cout << "Error: Cloning betty repo failed." << std::endl;
			exit(EXIT_FAILURE);
		} else {
			std::cout << "Betty installed successfully." << std::endl;
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

		std::cout << "Betty installed successfully! You can now run betty to check for style and documentation." << std::endl;

		// remove betty from the dependencies list
		_dependencies.erase(std::remove(_dependencies.begin(), _dependencies.end(), "betty"), _dependencies.end());

	} /* installBetty */

	std::string getHomeDir() {
		return std::getenv("HOME");
	}

	bool directoryExists(const std::string& dirPath) {
//    return std::filesystem::is_directory(dirPath);
		struct stat info;

		return stat(dirPath.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
	}

	void Installer::installBrew() const {

		int status;

		std::string goinfre = getHomeDir() + "/goinfre";
		std::cout << "goinfre: " << goinfre << std::endl;



		_cout.info("Checking if goinfre directory exists...");

		return ;
		if (directoryExists(goinfre)) {
			std::cout << goinfre << " directory exists." << std::endl;
		} else {
			throw std::runtime_error( goinfre + " directory does not exist");
		}

		std::string homebrew = goinfre + "/brew";


		if (directoryExists(homebrew)) {
			std::cout << homebrew << " directory already exists." << std::endl;
		} else {
			/* Install homebrew */
			std::cout << "Installing homebrew..." << std::endl;
			_animation.start();

			/* Start loading animation */
//			std::thread loadingThread(loadingAnimation); // todo fix this


//			int status = system("/bin/bash -c \"$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)\"");
//			if (status == STATUS_KO) {
//				throw std::runtime_error("Failed to install homebrew");
//			}

			/* Removing already existed homebrew directory */
			std::cout << "Removing already existed homebrew directory..." << std::endl;

			std::string command = "rm -rf " + homebrew + " &> /dev/null";
			status = system(command.c_str());
			if (status == STATUS_KO) {
//				throw std::runtime_error("Failed to remove already existed homebrew directory");
				std::cout << "Brew driectory already removed." << std::endl;
			} else {
				std::cout << "Successfully removed already existed homebrew directory." << std::endl;
			}

			command = "rm -rf " + goinfre + "/.brew &> /dev/null";
			status = system(command.c_str());
			if (status == STATUS_KO) {
//				throw std::runtime_error("Failed to remove already existed .brew directory");
				std::cout << "Brew driectory already removed." << std::endl;
			} else {
				std::cout << "Successfully removed already existed .brew directory." << std::endl;
			}

			/* Clean .zshrc file */
			status = system("sed -n '/brew/d' ~/.zshrc > ~/.zshrc.tmp && mv ~/.zshrc.tmp ~/.zshrc");
			if (status == STATUS_KO) {
//				throw std::runtime_error("Failed to clean .zshrc file");
				std::cout << "Failed to clean .zshrc file." << std::endl;
			} else {
				std::cout << "Successfully cleaned .zshrc file." << std::endl;
			}

			/* Curl brew */
			command = "cd " + goinfre + " && mkdir homebrew";
			command += " && curl -sL https://github.com/Homebrew/brew/tarball/master | tar xz --strip 1 -C homebrew > /dev/null 2>&1";
			status = system(command.c_str());
			if (status == STATUS_KO) {
//				throw std::runtime_error("Failed to curl brew");
				std::cout << "Failed to curl brew." << std::endl;
			} else {
				std::cout << "Successfully curled brew." << std::endl;
			}

			/* Add brew to .zshrc */
			command = "echo 'export PATH=" + goinfre + "/homebrew/bin:$PATH' >> ~/.zshrc";
			status = system(command.c_str());
			if (status == STATUS_KO) {
//				throw std::runtime_error("Failed to add brew to .zshrc");
				std::cout << "Failed to add brew to .zshrc." << std::endl;
			} else {
				std::cout << "Successfully added brew to .zshrc." << std::endl;
			}

			/* source .zshrc */
			status = system("source ~/.zshrc > /dev/null 2>&1");
			if (status == STATUS_KO) {
//				throw std::runtime_error("Failed to source .zshrc");
				std::cout << "Failed to source .zshrc." << std::endl;
			} else {
				std::cout << "Successfully sourced .zshrc." << std::endl;
			}

			/* Update brew */
			status = system("brew update > /dev/null 2>&1");
if (status == STATUS_KO) {
//				throw std::runtime_error("Failed to update brew");
				std::cout << "Failed to update brew." << std::endl;
			} else {
				std::cout << "Successfully updated brew." << std::endl;
			}

			/* Stop loading animation */
			_animation.stop();

			std::cout << GREEN << "Homebrew installed successfully!" << END << std::endl;

		}

		/* Installation Steps */


	} /* installBrew */


} /* namespace alx */
