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
void Command_Test(std::vector<std::string> vecArgs)
{
    std::cout << "Working!" << std::endl;
}

void Command_Exit(std::vector<std::string> vecArgs)
{
    exit(0);
}

void Command_Args(std::vector<std::string> vecArgs)
{
    for (std::string szArg : vecArgs)
        std::cout << szArg << std::endl;
}

int main()
{
    CShell Shell;
    Shell.RegisterCommand(CShell::Command_t("test", Command_Test, { "t" }));
    Shell.RegisterCommand(CShell::Command_t("exit", Command_Exit, { "x" }));
    Shell.RegisterCommand(CShell::Command_t("arguments", Command_Args, { "args" }));

    while (true)
    {
        Shell.Run();

        std::cout << "=== History ===" << std::endl;

        for (std::string szHistory : Shell.GetHistory())
            std::cout << szHistory << std::endl;

        std::cout << "===============" << std::endl;
    }

    return 0;
}
```
