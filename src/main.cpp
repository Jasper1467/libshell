#include "../include/libshell.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

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
