#include <libshell.hpp>

#include <iostream>
#include <string>
#include <vector>

int main()
{
    Shell shell;

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
    shell.run();

    // Save history to file (optional)
    shell.saveHistory(".shell_history");

    return 0;
}
