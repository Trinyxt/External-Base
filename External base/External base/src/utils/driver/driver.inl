#pragma once

#include "../../Roblox/Variables/Globals.h"

namespace driver {

    template <typename T>
    T read(uintptr_t addr) {
        T temp{};
        driver::Request r{};
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = &temp;
        r.size = sizeof(T);

        DeviceIoControl(Globals::Prhandle, driver::codes::read, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
        return temp;
    }

    template <typename T>
    void write(uintptr_t addr, T value) {
        driver::Request r{};
        r.target = reinterpret_cast<PVOID>(addr);
        r.buffer = reinterpret_cast<PVOID>(&value);
        r.size = sizeof(T);

        DeviceIoControl(Globals::Prhandle, driver::codes::write, &r, sizeof(r), &r, sizeof(r), nullptr, nullptr);
    }

}
