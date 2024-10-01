# Command Shell Library

This project implements a customizable command-line shell in C++ using the `CShell` class. It allows users to register, unregister, and execute custom commands based on user input. The shell continuously runs, processes input, and supports argument parsing.

## Features

- **Command Registration**: Easily register and unregister commands with callback functions.
- **Argument Handling**: Commands can accept and process arguments passed as strings.
- **Input Parsing**: User input is parsed into commands and arguments.
- **Customizable Prompt**: Supports customizable prefix and suffix for the shell prompt.
- **Infinite Command Loop**: Continuously listens for and executes commands until explicitly exited.

## Example
```
    CShell Shell;
    Shell.RegisterCommand("test", Command_Test);
    Shell.RegisterCommand("exit", Command_Exit);
    Shell.RegisterCommand("args", Command_Args);

    while (true)
    {
        Shell.Run();
    }

    return 0;
```
