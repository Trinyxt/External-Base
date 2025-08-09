#include "Windows.h"
#include <iostream>
#include <winddi.h>

#include "Roblox/Variables/Globals.h"
#include "utils/driver/Driver.hpp"
#include "Roblox/Scheduler/Scheduler.h"

using namespace std;
const wstring& roblox = L"RobloxPlayerBeta.exe";

// Creates a communication to the driver.
// The driver is in ring 0 and the application is running in ring 3.
int Driver()
{
	// To Use Another Ioctl Driver change "\\\\.\\paysoniscoolio" to "\\\\.\\yourdriver"
	Globals::Prhandle = CreateFileA(
		"\\\\.\\paysoniscoolio",
		GENERIC_READ,
		0,
		nullptr,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		nullptr
	);

	if (Globals::Prhandle == INVALID_HANDLE_VALUE) {
		cout << "Couldn't Find The Driver" << endl;
	}
	cout << "[+] Successfully Created A Handle to the driver" << endl;

	Globals::PID = driver::GetProcId(roblox);
	if (Globals::PID == 0) {
		cout << "[-] Make sure Roblox is opened!" << endl;
		CloseHandle(Globals::Prhandle);
		exit(0);
		return 1;
	}

	Globals::baseaddy = driver::GetModuleBaseAddy(roblox);

	if (Globals::baseaddy == 0) {
		cerr << "[-] Failed to get module base address." << endl;
		CloseHandle(Globals::Prhandle);
		exit(0);
		return 1;
	}

	cout << "[+] Module base address: " << hex << Globals::baseaddy << endl;


	if (driver::attach_to_process(Globals::PID) == true)
	{
		cout << "[+] Attached to roblox's process successfully." << endl << endl;
	}
	else {
		cout << "[-] Couldn't attach to roblox's process. Make sure to tell trinyxt that he's a dumbass";
		CloseHandle(Globals::Prhandle);
		exit(0);
		return 1;
	}
}

void printCred()
{
	std::cout <<
		R"(___________         __                             .__    __________                       
\_   _____/__  ____/  |_  ___________  ____ _____  |  |   \______   \_____    ______ ____  
 |    __)_\  \/  /\   __\/ __ \_  __ \/    \\__  \ |  |    |    |  _/\__  \  /  ___// __ \ 
 |        \>    <  |  | \  ___/|  | \/   |  \/ __ \|  |__  |    |   \ / __ \_\___ \\  ___/ 
/_______  /__/\_ \ |__|  \___  >__|  |___|  (____  /____/  |______  /(____  /____  >\___  >
        \/      \/           \/           \/     \/               \/      \/     \/     \/ 
	)"
		<< endl;
	cout << "Made by trinyxt" << endl;
}

int main()
{
	printCred();

	Driver();
	Scheduler->Scan();

	cout << endl << "Desired WalkSpeed Amount (Number only): ";
	float amount = cin.get();
	cout << endl;
	driver::write<float>(Globals::Humanoid + offsets::WalkSpeed, amount);
	driver::write<float>(Globals::Humanoid + offsets::WalkSpeedCheck, amount);
}