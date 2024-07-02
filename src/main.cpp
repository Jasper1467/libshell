#include "../include/libshell.hpp"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>
#include <vector>

void Command_Test(std::vector<std::string> vecArgs)
{
    printf("Working!\n");
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
    Shell.RegisterCommand("test", Command_Test);
    Shell.RegisterCommand("exit", Command_Exit);
    Shell.RegisterCommand("args", Command_Args);

    while (true)
    {
        Shell.Run();
    }

    return 0;
}
