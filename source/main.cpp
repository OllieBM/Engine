#ifdef _WIN32
#include"SystemClass.h"
//#include"SystemClass.h"

#endif



int main()
{
	//WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)

	SystemClass* system = nullptr; // could make a static ISystemClass* variable and make ISystemClass

#ifdef _WIN32
	system = &SystemClass::GetInstance();
#endif

	if (!system)
	{
		return 0;
	}

	// Initialise and run the system object
	bool result = system->Initialise();
	if (result)
	{
		system->Run();
	}

	// Shutdown and releasr the system object.
	system->Shutdown();

	return 0;



}