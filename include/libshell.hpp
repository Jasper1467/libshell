#pragma once

#include <functional>
#include <string>
#include <string_view>
#include <vector>

class Shell
{
public:
    using CommandFunction = std::function<void(const std::vector<std::string>&)>;

    enum class Status
    {
        Success = 0,
        Failed,
        UnknownCommand,
        EmptyInput,
        EmptyTokens,
    };

    struct Command
    {
        Command(std::string name, CommandFunction function, std::vector<std::string> aliases = {})
            : name(std::move(name)), aliases(std::move(aliases)), function(std::move(function))
        {
        }

        std::string name;
        std::vector<std::string> aliases;
        CommandFunction function;
    };

private:
    std::vector<Command> commands;

    std::string_view prefix;
    std::string_view suffix;

    std::vector<std::string> history;

public:
    // Constructor
    Shell() : prefix("> "), suffix("")
    {
    }

    // Command registration
    void registerCommand(const std::string& name, CommandFunction func);
    void registerCommand(const std::string& name, CommandFunction func, const std::vector<std::string>& aliases);
    void unregisterCommand(const std::string& name);

    // History management
    void clearHistory();
    size_t getHistorySize() const;
    std::string getHistoryEntry(size_t index) const;
    void saveHistory(const std::string& filepath) const;
    void loadHistory(const std::string& filepath);   

    // Main execution
    Status run();
    Status runOnce();

    // Configuration
    void setPrompt(const std::string& prompt);
    void setSuffix(const std::string& suffix);

private:
    void executeCommand(const std::string& command_line);
    std::vector<std::string> tokenize(const std::string& line) const;
    std::string getCommandName(const std::vector<std::string>& tokens) const;
    void addHistoryEntry(const std::string& entry);
};
