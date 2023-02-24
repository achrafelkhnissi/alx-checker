TODO:
- Make the user copy a script and type it to the terminal. The script will:
  - Install the dependencies
  - Build the project
  - Cp the executable to /usr/bin
  - Check if svn is installed
- After that! the checker will automatically download the appropriate test files for the project.
- Then for each task the checker will read all file contained in the directory containing the test files.
- Then it will create a map of the test files and the expected output.
- Then it will run the executable with the test file as an argument and compare the output with the expected output.
- But I need to check if it's possible to compare the output of the executable with the expected output.

- `sh -c "$(curl -fsSL https://raw.githubusercontent.com/achrafelkhnissi/alx-checker/0x00-checker/install.sh)"`

## SVN
- `svn export https://github.com/achrafelkhnissi/alx-checker/trunk/0x04-checker/` 


## Dependencies
- `sudo apt-get install -y git`
- `sudo apt-get install -y subversion`

[//]: # (- `sudo apt-get install -y curl`)