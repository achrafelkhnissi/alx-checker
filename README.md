TODO:

[//]: # (- Make the user copy a script and type it to the terminal. The script will:)

[//]: # (  - Install the dependencies)

[//]: # (  - Build the project)

[//]: # (  - Cp the executable to /usr/bin)

[//]: # (  - Check if svn is installed)

[//]: # (- After that! the checker will automatically download the appropriate test files for the project.)

[//]: # (- Then for each task the checker will read all file contained in the directory containing the test files.)
- Then it will create a map of the test files and the expected output.
- Then it will run the executable with the test file as an argument and compare the output with the expected output.
- But I need to check if it's possible to compare the output of the executable with the expected output.
- I need to think if there's a more appropriate name for the tests/ directory and the expected_output/ directory.


1. Put all the files of `tests/` in a data structure! either a map or a vector<pair>. [filename, file_content]
2. Put all the files of `expected_output/` in a data structure! either a map or a vector<pair>. [filename, file_content]

- `sh -c "$(curl -fsSL https://raw.githubusercontent.com/achrafelkhnissi/alx-checker/0x00-checker/install.sh)"`

## SVN
- `svn export https://github.com/achrafelkhnissi/alx-checker/trunk/0x04-checker/` 

---

## Usage
- Clone the repository: `git clone https://github.com/achrafelkhnissi/low-level-programming-checkers.git`
- Copy your project to where your project's checker is located
    - Example: `cp -r /path/to/0x03-debugging /path/to/0x03-checker`
- Execute the following commands:
    - `make betty`: Checks for betty coding style errors of all files
    - `make [task number]`: Checks for one task if it has the correct output
    - `make check-all`: Checks for all tasks at the same time
    - `make clean`: Deletes generated files
=======

## Dependencies
- `sudo apt-get install -y git`
- `sudo apt-get install -y subversion`

[//]: # (- `sudo apt-get install -y curl`)

