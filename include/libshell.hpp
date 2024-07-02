#pragma once

#include <cstdio>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

class CShell
{
private:
    using CommandFn = std::function<void(const std::vector<std::string>)>;
    std::map<std::string, CommandFn> m_mapCommands;
    std::string m_szPrefix;

public:
    explicit CShell(const std::string& szPrefix) : m_szPrefix(szPrefix)
    {
    }

    CShell()
    {
        m_szPrefix = "> ";
    }

    void RegisterCommand(std::string szCommand, CommandFn fnFunction)
    {
        m_mapCommands[szCommand] = fnFunction;
    }

    enum Status_e
    {
        STATUS_SUCCESS = 0,
        STATUS_FAILED,
        STATUS_UNKNOWN_COMMAND,
    };

    void SetPrefix(std::string szPrefix)
    {
        m_szPrefix = szPrefix;
    }

    Status_e Run()
    {
        std::string szInput;

        printf(m_szPrefix.c_str());
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
            printf("Unknown command: %s", szCommand.c_str());
            return STATUS_UNKNOWN_COMMAND;
        }

        return STATUS_SUCCESS;
    }

private:
    std::vector<std::string> ParseInput(const std::string& szInput)
    {
        std::istringstream iss(szInput);
        std::vector<std::string> vecTokens;
        std::string szToken;
        while (iss >> szToken)
            vecTokens.push_back(szToken);

        return vecTokens;
    }
};
