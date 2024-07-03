#pragma once

#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

class CShell
{
public:
    using CommandFn = std::function<void(const std::vector<std::string>)>;

private:
    std::map<std::string, CommandFn> m_mapCommands;
    std::string_view m_szPrefix;
    std::string_view m_szSuffix;

public:
    explicit CShell(const std::string_view& szPrefix = "> ", const std::string_view& szSuffix = "")
        : m_szPrefix(szPrefix), m_szSuffix(szSuffix)
    {
    }

    void RegisterCommand(std::string szCommand, CommandFn fnFunction)
    {
        m_mapCommands[szCommand] = fnFunction;
    }

    void UnregisterCommand(std::string szCommand)
    {
        m_mapCommands.erase(m_mapCommands.find(szCommand));
    }

    enum Status_e
    {
        STATUS_SUCCESS = 0,
        STATUS_FAILED,
        STATUS_UNKNOWN_COMMAND,
    };

    const std::map<std::string, CommandFn> GetCommands() const
    {
        return m_mapCommands;
    }

    void ClearCommands()
    {
        m_mapCommands.clear();
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
        auto it = m_mapCommands.find(szCommand);
        if (it != m_mapCommands.end())
            it->second(vecArgs);
    }

    Status_e Run()
    {
        std::string szInput;

        std::cout << m_szPrefix;
        std::getline(std::cin, szInput);

        if (szInput.empty())
            return STATUS_FAILED;

        auto vecTokens = ParseInput(szInput);
        if (vecTokens.empty())
            return STATUS_FAILED;

        auto szCommand = vecTokens[0];
        vecTokens.erase(vecTokens.begin());

        auto it = m_mapCommands.find(szCommand);
        if (it != m_mapCommands.end())
            it->second(vecTokens);
        else
        {
            printf("Unknown command: %s\n", szCommand.c_str());
            return STATUS_UNKNOWN_COMMAND;
        }

        return STATUS_SUCCESS;
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
