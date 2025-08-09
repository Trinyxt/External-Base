#include <iostream>
#include <Windows.h>

#include "../Variables/Globals.h"
#include "../Variables/Offsets.hpp"
#include "../../utils/Driver/driver.hpp"
//#include "../../utils/structs/struct.hpp"

using namespace std;

/* Our Scheduler class. Using Scheduler->Function() we will be able to call the 
   function from everywhere we include Scheduler.h.
*/
class BaseScheduler
{
public:
	// helper functions
	std::string getName(uintptr_t addy);
	std::string getClassName(uintptr_t addy);
	std::vector<uintptr_t> getChildren(uintptr_t addy);
	uintptr_t FindFirstChild(uintptr_t addy, std::string name);
	uintptr_t FindFirstChildByClass(uintptr_t addy, std::string name);

	// main functions
	uintptr_t FindDatamodel();
	
	uintptr_t FindPlayerService();
	uintptr_t FindLocalPlayer();
	uintptr_t FindCharacter();
	uintptr_t FindHumanoid();

	void Scan();
};

inline auto Scheduler = std::make_unique<BaseScheduler>();