#include <libshell.hpp>

#include <algorithm>
#include <fstream>
#include <iostream>

void Shell::registerCommand(const std::string& name, CommandFunction func)
{
    commands.emplace_back(name, func);
}

void Shell::registerCommand(const std::string& name, CommandFunction func, const std::vector<std::string>& aliases)
{
    commands.emplace_back(name, func, aliases);
}

void Shell::unregisterCommand(const std::string& name)
{
    commands.erase(
        std::remove_if(commands.begin(), commands.end(), [&name](const Command& cmd) { return cmd.name == name; }),
        commands.end());
}

void Shell::clearHistory()
{
    history.clear();
}

size_t Shell::getHistorySize() const
{
    return history.size();
}

std::string Shell::getHistoryEntry(size_t index) const
{
    if (index >= history.size())
    {
        return "";
    }

    return history[index];
}

void Shell::saveHistory(const std::string& filepath) const
{
    std::ofstream file(filepath);
    if (file.is_open())
    {
        for (const auto& entry : history)
        {
            file << entry << "\n";
        }

        file.close();
    }
}

void Shell::loadHistory(const std::string& filepath)
{
    std::ifstream file(filepath);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            history.push_back(line);
        }

        file.close();
    }
}

Shell::Status Shell::run()
{
    std::string line;
    while (true)
    {
        std::cout << prefix;
        if (!std::getline(std::cin, line))
            break;

        if (!line.empty())
            executeCommand(line);
    }

    return Status::Success;
}

Shell::Status Shell::runOnce()
{
    std::string line;
    std::cout << prefix;
    if (std::getline(std::cin, line))
    {
        if (!line.empty())
            executeCommand(line);

        return Status::Success;
    }

    return Status::Failed;
}

void Shell::setPrompt(const std::string& prompt)
{
    prefix = prompt;
}

void Shell::setSuffix(const std::string& suffix)
{
    this->suffix = suffix;
}

void Shell::executeCommand(const std::string& command_line)
{
    addHistoryEntry(command_line);

    auto tokens = tokenize(command_line);
    if (tokens.empty())
        return;

    std::string command_name = getCommandName(tokens);
    for (const auto& cmd : commands)
    {
        if (cmd.name == command_name)
        {
            std::vector<std::string> args(tokens.begin() + 1, tokens.end());
            cmd.function(args);
            return;
        }
    }

    std::cout << "Command not found: " << command_name << "\n";
}

std::vector<std::string> Shell::tokenize(const std::string& line) const
{
    std::vector<std::string> tokens;
    std::string token;
    bool in_quotes = false;

    for (size_t i = 0; i < line.length(); ++i)
    {
        char c = line[i];

        if (c == '"')
            in_quotes = !in_quotes;
        else if (c == ' ' && !in_quotes)
        {
            if (!token.empty())
            {
                tokens.push_back(token);
                token.clear();
            }
        }
        else
            token += c;
    }

    if (!token.empty())

        tokens.push_back(token);

    return tokens;
}

std::string Shell::getCommandName(const std::vector<std::string>& tokens) const
{
    return tokens.empty() ? "" : tokens[0];
}

void Shell::addHistoryEntry(const std::string& entry)
{
    history.push_back(entry);
}
