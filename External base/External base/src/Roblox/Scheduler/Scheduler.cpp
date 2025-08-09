#include "Scheduler.h"


std::string BaseScheduler::getName(uintptr_t addy) {
	uintptr_t nameptr = driver::read<uintptr_t>(addy + offsets::Name); // addy + 0x18

	std::string name; // empty name var

	if (driver::read<int>(nameptr + 0x10) >= 16) { // 0x10 returns size of string, if its bigger than 16 means its too big to driver::read as a string directly
		uintptr_t nameptr2 = driver::read<uintptr_t>(nameptr); // driver::read nameptr again
		while (driver::read<char>(nameptr2) != '\0') { // driver::read each character inside the nameptr2 until the character is = '\0' which is empty
			name += driver::read<char>(nameptr2); // add the character to name since its not 
			nameptr2++; // increase the index to the next one so that the next char gets driver::read
		}
	}
	else {
		name = driver::read<std::string>(nameptr); // not too big so we can driver::read directly
	}

	return name; // return the final name
}

std::string BaseScheduler::getClassName(uintptr_t addy)
{
	uintptr_t ClassDesc = driver::read<uintptr_t>(addy + offsets::ClassDescriptor);
	uintptr_t ClassName = driver::read<uintptr_t>(ClassDesc + offsets::ClassDescriptorToClassName);

	if (!ClassName) { // check if the classname ptr exists
		return "Unknown";
	}

	std::string name; // empty name var

	if (driver::read<int>(ClassName + 0x10) >= 16) { // 0x10 returns size of string, if its bigger than 16 means its too big to driver::read as a string directly
		uintptr_t nameptr2 = driver::read<uintptr_t>(ClassName); // driver::read nameptr again
		while (driver::read<char>(nameptr2) != '\0') { // driver::read each character inside the nameptr2 until the character is = '\0' which is empty
			name += driver::read<char>(nameptr2); // add the character to name since its not 
			nameptr2++; // increase the index to the next one so that the next char gets driver::read
		}
	}
	else {
		name = driver::read<std::string>(ClassName); // not too big so we can driver::read directly
	}

	return name;
}

std::vector<uintptr_t> BaseScheduler::getChildren(uintptr_t addy)
{
	std::vector<uintptr_t> children;

	uintptr_t childrenStart = driver::read<uintptr_t>(addy + offsets::Children); 
	uintptr_t childrenend = driver::read<uintptr_t>(childrenStart + offsets::ChildrenEnd);

	for (auto child = driver::read<uintptr_t>(childrenStart); child < childrenend; child += 0x10) { 
		children.push_back(driver::read<uintptr_t>(child));
	}

	return children;
}

uintptr_t BaseScheduler::FindFirstChild(uintptr_t addy, std::string name)
{
	for (auto child : Scheduler->getChildren(addy)) {
		if (Scheduler->getName(child) == name) {
			return child;
		}
	}
	return 0;
}

uintptr_t BaseScheduler::FindFirstChildByClass(uintptr_t addy, std::string name)
{
	for (auto child : Scheduler->getChildren(addy)) {
		if (Scheduler->getClassName(child) == name) {
			return child;
		}
	}
	return 0;
}

uintptr_t BaseScheduler::FindDatamodel()
{
	// Finding the datamodel
	uintptr_t Base = Globals::baseaddy;
	uintptr_t FakeDataModel = driver::read<uintptr_t>(Base + offsets::FakeDataModelPointer);
	uintptr_t Datamodel = driver::read<uintptr_t>(FakeDataModel + offsets::FakeDataModelToDataModel);

	// We Store the datamodel for later use.
	Globals::dm = Datamodel;

	return Datamodel;
}

uintptr_t BaseScheduler::FindPlayerService()
{
	// all these can be used in this file bcuz we have BaseScheduler:: but outside we have to use Scheduler->
	//uintptr_t Players = this->FindFirstChild(Globals::dm, "Players");
	//uintptr_t Players = Scheduler->FindFirstChild(Globals::dm, "Players");

	uintptr_t Players = FindFirstChild(Globals::dm, "Players");
	
	// Storing for further use
	Globals::PlayerService = Players;
	return Players;
}

uintptr_t BaseScheduler::FindLocalPlayer()
{
	uintptr_t LocalPlayer = driver::read<uintptr_t>(Globals::PlayerService + offsets::LocalPlayer);
	// Storing for further use
	Globals::localPlr = LocalPlayer;

	return LocalPlayer;
}

uintptr_t BaseScheduler::FindCharacter()
{
	uintptr_t Character = driver::read<uintptr_t>(Globals::localPlr + offsets::ModelInstance);
	// Storing for further use
	Globals::Character = Character;

	return Character;
}

uintptr_t BaseScheduler::FindHumanoid()
{
	uintptr_t Humanoid = FindFirstChild(Globals::Character, "Humanoid");
	// Storing for further use
	Globals::Humanoid = Humanoid;

	return Humanoid;
}

void BaseScheduler::Scan() 
{
	FindDatamodel();
	FindPlayerService();
	FindLocalPlayer();
	FindCharacter();
	FindHumanoid();
}