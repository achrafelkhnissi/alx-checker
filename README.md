<p align="center">  
<img src ="https://assets.imaginablefutures.com/media/images/ALX_Logo.max-200x150.png">
</p>

<h1 align="center">
	alx-low_level_programming_checkers
</h1>



This repository is a collection of checkers created for the ALX Low-Level Programming course projects. The checkers are designed to automate the checking process and ensure that the projects meet the requirements of the course. The checkers cover various aspects of the projects, such as coding style, syntax, and expected output. The repository is a useful tool for ALX students to ensure that their projects are up to the standard required by the course.


---

## Checkers
- [0x00-hello_world](./0x00-checker)
- [0x01-variables_if_else_while](./0x01-checker)
- [0x02-functions_nested_loops](./0x02-checker)
- [0x03-debugging](./0x03-checker)
- [0x04-more_functions_nested_loops](./0x04-checker)

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
