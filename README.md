# Command Shell Library

A customizable C++ command-line shell using the CShell class, allowing users to add, remove, and run commands with argument support.

## Features

- **Command Registration**: Easily register and unregister commands with callback functions.
- **Argument Handling**: Commands can accept and process arguments passed as strings.
- **Input Parsing**: User input is parsed into commands and arguments.
- **Customizable Prompt**: Supports customizable prefix and suffix for the shell prompt.
- **Infinite Command Loop**: Continuously listens for and executes commands until explicitly exited.

## Example
```cpp
#include <libshell.hpp>

#include <iostream>
#include <string>
#include <vector>

int main()
{
    libshell::Config shellConfig;
    libshell::Shell shell;

    // Register a simple command
    shell.registerCommand("hello", [](const std::vector<std::string>&) { std::cout << "Hello, World!\n"; });

    shell.registerCommand("echo",
                          [](const std::vector<std::string>& args)
                          {
                              for (const auto& arg : args)
                              {
                                  std::cout << arg << " ";
                              }
                              std::cout << "\n";
                          });

    // Load history from file (optional)
    shell.loadHistory(".shell_history");

    // Run the shell
    shell.run(shellConfig);

    // Save history to file (optional)
    shell.saveHistory(".shell_history");

    return 0;
}
```
