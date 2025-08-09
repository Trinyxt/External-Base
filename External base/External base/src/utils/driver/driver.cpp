#include "driver.hpp"
#include "../../Roblox/Variables/Globals.h"
#include <TlHelp32.h>
#include <thread>
#include <iostream>

bool driver::attach_to_process(const DWORD pid) {
    driver::Request r{};
    r.process_id = reinterpret_cast<HANDLE>(pid);

    return DeviceIoControl(Globals::Prhandle, driver::codes::attach, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
}

DWORD driver::GetProcId(const std::wstring& procName) {
    DWORD procId = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    PROCESSENTRY32W entry = { sizeof(entry) };

    if (Process32FirstW(hSnap, &entry)) {
        do {
            if (!_wcsicmp(entry.szExeFile, procName.c_str())) {
                procId = entry.th32ProcessID;
                break;
            }
        } while (Process32NextW(hSnap, &entry));
    }

    CloseHandle(hSnap);
    return procId;
}

uintptr_t driver::GetModuleBaseAddy(const std::wstring& modName) {
    DWORD procId = Globals::PID;
    uintptr_t modBase = 0;

    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    MODULEENTRY32W modEntry = { sizeof(modEntry) };

    if (Module32FirstW(hSnap, &modEntry)) {
        do {
            if (!_wcsicmp(modEntry.szModule, modName.c_str())) {
                modBase = (uintptr_t)modEntry.modBaseAddr;
                break;
            }
        } while (Module32NextW(hSnap, &modEntry));
    }

    CloseHandle(hSnap);
    return modBase;
}

std::filesystem::path driver::findExeInPath(const std::filesystem::path& baseDir, const std::string& exeName) {
    std::filesystem::path fullPath = baseDir / exeName;

    if (std::filesystem::exists(fullPath)) {
        return fullPath;
    }
    else {
        std::cerr << "[-] Could not find " << fullPath << "\n";
        return {};
    }
}
