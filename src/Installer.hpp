//
// Created by Achraf El khnissi on 2/24/23.
//

#ifndef ALX_CHECKER_INSTALLER_HPP
#define ALX_CHECKER_INSTALLER_HPP

#include <iostream>		// std::cout, std::cerr
#include <string>		// std::string
#include <vector>		// std::vector
#include <cstdlib>		// EXIT_SUCCESS

#include "Print.hpp"

namespace alx {

	class Installer {

	private:
		std::vector<std::string> _dependencies;

	public:
		Installer();
		~Installer();

		void install() const;
		void uninstall() const;
		void update() const;
		void usage() const;
		void checkArgs(int argc, char *argv[]) const;
		void check() const;


		void checkDependencies() const;
		void installDependencies() const;
		void installSvn() const;

		void downloadTests(void) const;

		void checkBetty() const;
		void installBetty() const;
		bool isRunningAsRoot() const;

		bool isMacos() const;
		bool isLinux() const;

	}; /* class Installer */

} /* namespace alx */



#endif //ALX_CHECKER_INSTALLER_HPP
