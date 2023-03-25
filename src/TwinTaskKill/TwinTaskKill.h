#pragma once

#include <atlstr.h>
#include <iostream>
#include <psapi.h>
#include <stdio.h>
#include <string>
#include <tchar.h>
#include <windows.h>

void killProcess(const std::string &processName)
{
    // Get the list of process identifiers.
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;

    if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        std::cerr << "Enum processes failed!\n";
        return;
    }

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);

    bool isFindProcess = false;
    // Traversal the name and process identifier for each process.
    for (i = 0; i < cProcesses; i++)
    {
        if (aProcesses[i] != 0)
        {
            auto processID = aProcesses[i];
            CHAR szProcessName[MAX_PATH];

            // Get a handle to the process.
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID);

            // Get the process name.
            if (NULL != hProcess)
            {
                HMODULE hMod;
                DWORD cbNeeded;

                if (EnumProcessModules(hProcess, &hMod, sizeof(hMod), &cbNeeded))
                {
                    GetModuleBaseNameA(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
                }
            }

            // Kill process
            if (strcmp(szProcessName, processName.c_str()) == 0)
            {
                std::string strKill = "taskkill /pid " + std::to_string(processID) + " /f";
                system(strKill.c_str());
                isFindProcess = true;
            }

            CloseHandle(hProcess);
            if (isFindProcess)
            {
                std::cout << "Process " + processName + " has been killed!\n";
                return;
            }
        }
    }

    std::cout << "Process " + processName + " not found!\n";
}