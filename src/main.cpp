#include "../include/libshell.hpp"
#include <cstdio>
#include <cstdlib>
#include <vector>

void Command_Test(std::vector<std::string> vecArgs)
{
    printf("Working!\n");
}

void Command_Exit(std::vector<std::string> vecArgs)
{
    exit(0);
}

int main()
{
    CShell Shell;
    Shell.RegisterCommand("test", Command_Test);
    Shell.RegisterCommand("exit", Command_Exit);

    while (true)
    {
        Shell.Run();
    }

    return 0;
}
