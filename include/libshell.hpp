#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

class CShell
{
public:
    using CommandFn = std::function<void(const std::vector<std::string>)>;

    enum Status_e
    {
        STATUS_SUCCESS = 0,
        STATUS_FAILED,
        STATUS_UNKNOWN_COMMAND,
        STATUS_EMPTY_INPUT,
        STATUS_EMPTY_TOKENS,
    };

    struct Command_t
    {
        Command_t(std::string szCommand, CommandFn fnFunction, std::vector<std::string> vecAliases = {})
            : m_szCommand(std::move(szCommand)), m_vecAliases(std::move(vecAliases)),
              m_fnFunction(std::move(fnFunction))
        {
        }

        std::string m_szCommand;
        std::vector<std::string> m_vecAliases;
        CommandFn m_fnFunction;
    };

private:
    std::vector<Command_t> m_vecCommands;

    std::string_view m_szPrefix;
    std::string_view m_szSuffix;

    std::vector<std::string> m_vecHistory;

public:
    explicit CShell(const std::string_view& szPrefix = "> ", const std::string_view& szSuffix = "")
        : m_szPrefix(szPrefix), m_szSuffix(szSuffix)
    {
    }

    void RegisterCommand(Command_t Cmd)
    {
        m_vecCommands.push_back(Cmd);
    }

    void UnregisterCommand(std::string szCommand)
    {
        for (auto it = m_vecCommands.begin(); it != m_vecCommands.end(); ++it)
        {
            if (it->m_szCommand == szCommand)
            {
                m_vecCommands.erase(it);
                break;
            }
        }
    }

    const std::vector<Command_t> GetCommands() const
    {
        return m_vecCommands;
    }

    const std::vector<std::string> GetHistory() const
    {
        return m_vecHistory;
    }

    void ClearCommands()
    {
        m_vecCommands.clear();
    }

    void SetPrefix(std::string_view szPrefix)
    {
        m_szPrefix = szPrefix;
    }

    std::string_view GetPrefix() const
    {
        return m_szPrefix;
    }

    void SetSuffix(std::string_view szSuffix)
    {
        m_szSuffix = szSuffix;
    }

    std::string_view GetSuffix() const
    {
        return m_szSuffix;
    }

    void ExecuteCommand(std::string szCommand, std::vector<std::string> vecArgs)
    {
        for (auto& Cmd : m_vecCommands)
        {
            if (Cmd.m_szCommand == szCommand ||
                std::find(Cmd.m_vecAliases.begin(), Cmd.m_vecAliases.end(), szCommand) != Cmd.m_vecAliases.end())
            {
                Cmd.m_fnFunction(vecArgs);

                std::string szFormatted = szCommand.append(" ");
                for (auto& Arg : vecArgs)
                    szFormatted += Arg + " ";

                m_vecHistory.push_back(szFormatted);
                return;
            }
        }
    }

    Status_e Run()
    {
        std::string szInput;

        std::cout << m_szPrefix;
        std::getline(std::cin, szInput);

        if (szInput.empty())
            return STATUS_EMPTY_INPUT;

        auto vecTokens = ParseInput(szInput);
        if (vecTokens.empty())
            return STATUS_EMPTY_TOKENS;

        auto szCommand = vecTokens[0];
        vecTokens.erase(vecTokens.begin());

        for (auto& Cmd : m_vecCommands)
        {
            if (Cmd.m_szCommand == szCommand ||
                std::find(Cmd.m_vecAliases.begin(), Cmd.m_vecAliases.end(), szCommand) != Cmd.m_vecAliases.end())
            {
                Cmd.m_fnFunction(vecTokens);

                m_vecHistory.push_back(szInput);
                return STATUS_SUCCESS;
            }
        }

        std::cout << "Unknown command: " << szCommand << std::endl;
        return STATUS_UNKNOWN_COMMAND;
    }

private:
    std::vector<std::string> ParseInput(const std::string szInput)
    {
        std::istringstream iss(szInput);
        std::vector<std::string> vecTokens;
        std::string szToken;
        while (iss >> szToken)
            vecTokens.push_back(szToken);

        return vecTokens;
    }
};
