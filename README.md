# Command Shell Library

This project implements a simple and customizable command-line shell in C++ using a class-based approach. The shell allows users to register commands with corresponding functions and execute them based on user input. The core functionality is encapsulated in the `CShell` class.

## Features

- **Command Registration**: Register and unregister custom commands with the shell.
- **Argument Handling**: Commands can accept arguments, which are passed as a vector of strings.
- **Input Parsing**: The shell parses user input into commands and arguments.
- **Customizable Prompt**: The shell's prompt and suffix can be customized.
- **Command Execution Loop**: The shell continuously runs, waiting for user input, and executes registered commands.

## Getting Started

### Prerequisites

- A C++ compiler (e.g., `g++` or `clang++`).
- Basic understanding of C++ standard libraries and command-line applications.

### Cloning the Repository

To get a copy of this project, clone it using the following command:

```bash
git clone https://github.com/your-username/your-repo-name.git
