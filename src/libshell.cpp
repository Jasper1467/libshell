#include <libshell.hpp>

#include <algorithm>
#include <fstream>

namespace libshell
{
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

    Status Shell::run(const Config& config)
    {
        applyConfig(config);

        std::string line;
        auto& in = *currentConfig.input;
        auto& out = *currentConfig.output;

        while (true)
        {
            out << currentConfig.prompt << currentConfig.suffix;
            out.flush();

            if (!std::getline(in, line))
                break;

            if (!line.empty())
                executeCommand(line);
        }

        return Status::Success;
    }

    Status Shell::runOnce(const Config& config)
    {
        applyConfig(config);

        std::string line;
        auto& in = *currentConfig.input;
        auto& out = *currentConfig.output;

        out << currentConfig.prompt << currentConfig.suffix;
        out.flush();

        if (std::getline(in, line))
        {
            if (!line.empty())
                executeCommand(line);

            return Status::Success;
        }

        return Status::Failed;
    }

    void Shell::applyConfig(const Config& config)
    {
        currentConfig = config;

        // Clamp history
        if (history.size() > currentConfig.historyLimit)
            history.erase(history.begin(), history.end() - currentConfig.historyLimit);

        // Install built-ins
        if (currentConfig.enableBuiltins)
        {
            registerCommand("help",
                            [this](const auto& args)
                            {
                                (*currentConfig.output) << "Available commands:\n";
                                for (const auto& cmd : commands)
                                    (*currentConfig.output) << "  - " << cmd.name << "\n";
                                return 0;
                            });

            registerCommand("exit",
                            [&](const auto&)
                            {
                                std::exit(0);
                                return 0;
                            });
        }
    }

    void Shell::executeCommand(const std::string& command_line)
    {
        addHistoryEntry(command_line);

        auto tokens = tokenize(command_line);
        if (tokens.empty())
            return;

        std::string command_name = tokens[0];
        auto& out = *currentConfig.output;

        for (const auto& cmd : commands)
        {
            bool nameMatch = (cmd.name == command_name);

            bool aliasMatch = currentConfig.enableAliases &&
                              std::find(cmd.aliases.begin(), cmd.aliases.end(), command_name) != cmd.aliases.end();

            if (nameMatch || aliasMatch)
            {
                std::vector<std::string> args(tokens.begin() + 1, tokens.end());
                cmd.function(args);
                return;
            }
        }

        out << "Command not found: " << command_name << "\n";

        if (currentConfig.enableSuggestions)
        {
            // Suggest similar commands (basic example)
            for (const auto& cmd : commands)
            {
                if (cmd.name.size() >= 2 && command_name.size() >= 2)
                {
                    if (cmd.name.substr(0, 2) == command_name.substr(0, 2))
                    {
                        out << "Did you mean: " << cmd.name << "?\n";
                        break;
                    }
                }
            }
        }
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
} // namespace libshell
