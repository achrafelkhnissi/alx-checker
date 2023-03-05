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
	    return _getBasename(parent_dir);
	}

	bool Checker::directoryExists(const std::string &path) const {
        struct stat info{};
		return stat(path.c_str(), &info) == 0 && (info.st_mode & S_IFDIR);
    } /* directoryExists */

	std::string Checker::_getMainFile(const std::string& file) const {

		// get hyphen position
		std::size_t hyphenPos = file.find('-');
		if (hyphenPos == std::string::npos || hyphenPos == 0) {
			throw std::runtime_error("Invalid file name: " + file);
		}

		// get main file name
		std::string mainFile = "test_files/" + file.substr(0, hyphenPos) + "-main.c";

		// if it doesn't exist return empty string
		if (!std::filesystem::exists(mainFile))
			return "";

		return mainFile;
	}

	std::string Checker::_getCurrentDirectory() const {
		char buff[FILENAME_MAX];
		getcwd(buff, FILENAME_MAX);
		return {buff};
	}

	bool Checker::_checkScript(const std::string& file) const {

		std::ifstream f(file);
		std::string line;
		int count = 0;

		const std::string specialChars = "&&||;";
		bool shebang = true;
		bool endsWithNewLine = true;
		bool hasSpecialChars = false;

		while (std::getline(f, line)) {

			// check if the file has a shebang
			if (count == 0 && line != "#!/bin/bash")
				shebang = false;

			// check if the file has special characters
			if (count == 1 && line.find_first_of(specialChars) != std::string::npos)
				hasSpecialChars = true;

			count++;
		}
		f.close();

		std::ifstream f2(file);
		std::string fileContent;
		char c;
		int newLineCount = 0;
		while (f2.get(c)) {
			if (c == '\n')
				newLineCount++;
			fileContent += c;
		}
		f2.close();

		// std::cout << "newLineCount: " << newLineCount << std::endl;
		if (fileContent.at(fileContent.size() - 1) != '\n')
			endsWithNewLine = false;

		// Create a directory name test_output if it doesn't exist
		std::string testOutputDir = "test_output/";
		if (!fs::exists(testOutputDir) && fs::is_directory(testOutputDir))
			fs::create_directory(testOutputDir);

		// create a file with the same name but with .out extension
		std::string outFileName = file + ".out";
		std::ofstream out(testOutputDir + outFileName);
		out << "\nTest output for: " << file << std::endl << std::endl;
		out << std::setw(30) << std::left << "- newLineCount = 2?: " << (newLineCount == 2 ? ": [OK]" : ": [KO]") << std::endl;
		out << std::setw(30) << std::left << "- shebang = #!/bin/bash?: " << (shebang ? ": [OK]" : ": [KO]") << std::endl;
		out << std::setw(30) << std::left << "- endsWithNewLine = true?: " << (endsWithNewLine ? ": [OK]" : ": [KO]") << std::endl;
		out << std::setw(30) << std::left << "- hasSpecialChars = false?: " << (!hasSpecialChars ? ": [OK]" : ": [KO]") << std::endl;
		out << std::endl;
		if (newLineCount == 2 && shebang && endsWithNewLine && !hasSpecialChars)
			out << "Result: PASSED" << std::endl;
		else {
			out << "Result: FAILED" << std::endl << std::endl;
			out << "Please check the following:" << std::endl;
			out << "1. The file has a #!/bin/bash in the first line" << std::endl;
			out << "2. The file has no special characters (&&, ||, ;)" << std::endl;
			out << "3. The file ends with a new line" << std::endl;
			out << "4. The file has 2 new lines" << std::endl;
			out << std::endl;
		}
		out.close();

		return (newLineCount == 2 && shebang && endsWithNewLine && !hasSpecialChars);
	} /* _checkScript */

	void Checker::printFileContent(const std::string& fileName) {
		std::ifstream file(fileName);
		if (!file.is_open()) {
			throw std::runtime_error("Failed to open <" + fileName + "> file");
		}

		std::string fileContent((std::istreambuf_iterator<char>(file)),
								std::istreambuf_iterator<char>());

		std::cout << fileContent << std::endl;
	}

} /* alx namespace */
