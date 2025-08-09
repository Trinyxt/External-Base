// globals are globals, able to be accessed in every file they are included

#pragma once
#include "../../utils/structs/struct.hpp"
#include <cstdint>
#include <Windows.h>
#include <string>

namespace Globals
{
	// Primary things
	inline DWORD PID = 0;
	inline HANDLE Prhandle;
	inline uintptr_t baseaddy = 0;

	// addresses
	inline uintptr_t dm = 0;

	// Plr
	inline uintptr_t localPlr = 0;
	inline uintptr_t Character = 0;
	inline uintptr_t Humanoid = 0;

	// Services
	inline uintptr_t PlayerService = 0;
}