//
// Created by Achraf El Khnissi on 3/4/23.
//

#include "Checker.hpp"
#include <functional>
#include <sstream>

namespace alx {

	void Checker::init0x07() {
		_taskProjectMap["101-crackme_password"] = []() {

			// read the password from the file
			std::ifstream file("101-crackme_password");
			std::string password;
			file >> password;
			file.close();

			std::cout << NP << NP;

			// check if the password is correct
			bool correct = password == "abc123";

			correct ? std::cout << OK : std::cout << KO;

			return correct;
		};
	}

	void Checker::init0x00() {
		_taskProjectMap["0-preprocessor"] = []() {
			std::string cmd = "./0-preprocessor";

			std::cout << NP;

			int status = system(cmd.c_str());
			!status ? std::cout << OK : std::cout << KO;

			// check if a file named c exists
			int exist = fs::exists("c");
			exist ? std::cout << OK : std::cout << KO;

			return !status && exist;
		};

		_taskProjectMap["1-compiler"] = []() {

			std::string cmd = "./1-compiler";

			std::cout << NP;

			int status = system(cmd.c_str());
			!status ? std::cout << OK : std::cout << KO;

			// Check if file ends with .o
			std::string obj = getenv("CFILE");

			// repleace .c with .o
			obj = obj.substr(0, obj.find_last_of('.')) + ".o";

//			std::cout << "`.o` file created\t: ";
			int exist = fs::exists(obj);
			exist ? std::cout << OK : std::cout << KO;

			return !status && exist;
		};

		_taskProjectMap["2-assembler"] = []() {

			std::string cmd = "./2-assembler";

			std::cout << NP;

			int status = system(cmd.c_str());
			!status ? std::cout << OK : std::cout << KO;

			std::string s = getenv("CFILE");
			s = s.substr(0, s.find_last_of('.')) + ".s";

			int exist = fs::exists(s);
			exist ? std::cout << OK : std::cout << KO;

			return !status && exist;
		};

		_taskProjectMap["3-name"] = []() {

			std::string cmd = "./3-name";
			std::cout << NP;

			int status = system(cmd.c_str());
			!status ? std::cout << OK : std::cout << KO;

			int exist = fs::exists("cisfun");
			exist ? std::cout << OK : std::cout << KO;

			return !status && exist;
		};

		_taskProjectMap["100-intel"] = []() {

			std::string cmd = "./100-intel";

			std::cout << NP;

			int status = system(cmd.c_str());
			!status ? std::cout << OK : std::cout << KO;

			// Check if file ends with .o
			std::string obj = getenv("CFILE");
			obj = obj.substr(0, obj.find_last_of('.')) + ".s";
			int exist = fs::exists(obj);

			std::ifstream file(obj);
			std::string line;
			bool found = false;

			while (std::getline(file, line)) {
				if (line.find("intel") != std::string::npos) {
					found = true;
					break;
				}
			}

			found && exist ? std::cout << OK : std::cout << KO;

			return !status && found && exist;
		};

	}

	void Checker::initProjectMap() {

		/**
		 * Note: At first I tried  .. = &Checker::init0x00; but it didn't work!
		 * I don't know why but it didn't work!
		 * Then I used = std::bind(&Checker::init0x00, this); and it worked!
		 * But I found a better way to do it using lambda functions.
		 */

		// get project prefix number
		int projectNumber_;
		std::istringstream iss(_project);
		iss >> std::hex >> projectNumber_;


		switch (projectNumber_) {
			case 0x00:
				_projectMap["0x00-hello_world"] = [this] { init0x00(); };
				break;
			case 0x07:
				_projectMap["0x07-pointers_arrays_strings"] = [this] { init0x07(); };
				break;
		}


		// todo: find why this doesn't work
		// _projectMap["0x00-hello_world"] = [this] { init0x00(); }; // works
		// _projectMap["0x01-variables_if_else_while"] = [this] { init0x01(); };
		// _projectMap["0x02-functions_nested_loops"] = [this] { init0x02(); };
		// _projectMap["0x03-debugging"] = [this] { init0x03(); };
		// _projectMap["0x04-more_functions_nested_loops"] = [this] { init0x04(); };
		// _projectMap["0x05-pointers_arrays_strings"] = [this] { init0x05(); };
		// _projectMap["0x06-pointers_arrays_strings"] = [this] { init0x06(); };
		// _projectMap["0x07-pointers_arrays_strings"] = [this] { init0x07(); };

	}

	// void Checker::init0x01() {}
	// void Checker::init0x02() {}
	// void Checker::init0x03() {}
	// void Checker::init0x04() {}
	// void Checker::init0x05() {}
	// void Checker::init0x06() {}

} /* alx */
