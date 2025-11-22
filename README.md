# Command Shell Library

A lightweight, extensible C++ command-line shell framework for embedding interactive consoles into applications

## Features
**Command System**
- Register and unregister commands dynamically
- Each command is a callback (```std::function<void(std::string)>``` or custom return type)
- Optional support for aliases

**Input Parsing**
- Tokenizes user input into command + arguments
- Quoted strings ("like this") are parsed as single arguments

**Customizable Shell Behaviour**
- Configurable prompt prefix & suffix
- Configurable input and output streams

**History**
- Built-in command history tracking
- Load/save history from a file
- Optional history size limits via ``Config``

**Runtime**
- ``run(config)`` for a persistent loop
- ``runOnce(config)`` for single-step execution (useful for GUIs/network shells)

# Installation
**Clone and build:**
```
git clone https://github.com/Jasper1467/libshell.git
cd libshell
cmake -B build
cmake --build build
```

**CMake integration:**
```
add_subdirectory(libshell)
target_link_libraries(your_target PRIVATE libshell)
```

Or if installed system-wide:
```
find_package(libshell REQUIRED)
target_link_libraries(your_target PRIVATE libshell::libshell)
```

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
