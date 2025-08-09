#pragma once

#include <Windows.h>
#include <cstdint>
#include <string>
#include <filesystem>

namespace driver {
    namespace codes {
        constexpr ULONG attach = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x696, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
        constexpr ULONG read   = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x697, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
        constexpr ULONG write  = CTL_CODE(FILE_DEVICE_UNKNOWN, 0x698, METHOD_BUFFERED, FILE_SPECIAL_ACCESS);
    }

    struct Request {
        HANDLE process_id;
        PVOID target;
        PVOID buffer;
        SIZE_T size;
        SIZE_T return_size;
    };

    bool attach_to_process(DWORD pid);

    template <typename T>
    T read(uintptr_t addr);

    template <typename T>
    void write(uintptr_t addr, T value);

    DWORD GetProcId(const std::wstring& procName);
    uintptr_t GetModuleBaseAddy(const std::wstring& modName);
    std::filesystem::path findExeInPath(const std::filesystem::path& baseDir, const std::string& exeName);
}

#include "driver.inl"
