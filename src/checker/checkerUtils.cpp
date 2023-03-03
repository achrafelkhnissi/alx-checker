/**
 * @author: Achraf El Khnissi
 * @date: Thursday, 5 March 2023
*/

#include "Checker.hpp"

namespace alx
{
	int Checker::createDirectory(const std::string& path)
	{
		if (access(path.c_str(), F_OK) == -1) {
			return mkdir(path.c_str(), 0777);
		}
		return 0;
	}

	int Checker::compile(const std::string& file, const std::string& output)
	{
		std::string command = "gcc -I . " + _CFLAGS + " " + file + " -o " + output;
		std::cout << "Compile command: " << command << std::endl;
		return system(command.c_str());
	}

	int Checker::diff(const std::string& correctOutput, const std::string& output)
	{
		std::string diffCommand = "diff -u " + correctOutput + " " + output;
		std::cout << "Diff command: " << diffCommand << std::endl;
		return system(diffCommand.c_str());
	}

	std::string Checker::_getBasename(const std::string& path) const {
		size_t pos = path.find_last_of("/\\");
		if (pos != std::string::npos) {
			return path.substr(pos + 1);
		}
		return path;
	}

	std::string Checker::getParentDirectory(const std::string& path) {
	    std::string parent_dir;
	    size_t last_slash_pos = path.rfind('/');
	    if (last_slash_pos != std::string::npos) {
	        parent_dir = path.substr(0, last_slash_pos);
	    }
	    return getBasename(parent_dir);
	}

	bool Checker::directoryExists(const std::string &path) const {
        struct stat info{};
        if (stat(path.c_str(), &info) != 0) {
            return false;
        } else if (info.st_mode & S_IFDIR) {
            return true;
        } else {
            return false;
        }
    } /* directoryExists */

	std::string Checker::_getMainFile(const std::string& file) const {
		std::string mainFile = "test_files/" + _getBasename(file);
		mainFile.replace(mainFile.find(".c"), 2, "-main.c");
		return mainFile;
	}


}