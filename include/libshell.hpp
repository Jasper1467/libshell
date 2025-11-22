#pragma once

#include <functional>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

namespace libshell
{
    struct Config
    {
        bool enableAliases = true;
        bool enableAutocomplete = false;
        bool enableSuggestions = true;
        bool enableBuiltins = true;
        bool enableVariables = false;
        bool enablePiping = false;
        bool enableRedirection = false;

        std::string prompt = "> ";
        std::string suffix = "";
        size_t historyLimit = 1000;

        std::istream* input = &std::cin;
        std::ostream* output = &std::cout;

        // Optional custom handlers
        std::function<void(const std::string&)> autocompleteHandler = nullptr;
    };

    enum class Status
    {
        Success = 0,
        Failed,
        UnknownCommand,
        EmptyInput,
        EmptyTokens,
    };

    using CommandFunction = std::function<void(const std::vector<std::string>&)>;
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

    class Shell
    {
    public:
        explicit Shell() = default;

        Status run(const Config& config);
        Status runOnce(const Config& config);

        void registerCommand(const std::string&, CommandFunction);
        void registerCommand(const std::string&, CommandFunction, const std::vector<std::string>& aliases);
        void unregisterCommand(const std::string&);

        // History management
        void clearHistory();
        size_t getHistorySize() const;
        std::string getHistoryEntry(size_t index) const;
        void saveHistory(const std::string& filepath) const;
        void loadHistory(const std::string& filepath);

        Config setConfig(const Config& config) { currentConfig = config; }

    private:
        Config currentConfig;

        std::vector<Command> commands;
        std::vector<std::string> history;
        std::unordered_map<std::string, std::string> variables;

        void executeCommand(const std::string&);
        std::vector<std::string> tokenize(const std::string&) const;
        std::string getCommandName(const std::vector<std::string>&) const;
        void addHistoryEntry(const std::string&);
        void applyConfig(const Config& config);
    };

} // namespace libshell
