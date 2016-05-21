#ifndef _SYSTEM_CLASS_H_
#define _SYSTEM_CLASS_H_

#include<Windows.h>


class SystemClass 
{
public:

	static SystemClass& GetInstance();


	bool Initialise();
	void Shutdown();
	int WINAPI Run();

	
	LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

private:

	// Declare all the methods of creating an instance of this class
	SystemClass(){};
	SystemClass(const SystemClass&){} // copy constructor
	~SystemClass(){}
	void operator=(SystemClass const&){}

	// Private functions
	bool Frame();
	void InitialiseWindows(int&, int&); // Create a window
	void ShutdownWindows(); // close winddow


	
	const char* m_ApplicationName;
	HINSTANCE m_HInstance;
	HWND m_Hwnd;

	static const bool FULL_SCREEN = false;


};

static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);



#endif 