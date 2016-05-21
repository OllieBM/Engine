
#include"SystemClass.h"



#include<memory>


SystemClass& SystemClass::GetInstance()
{
	static SystemClass instance;  // Guaranteed to be destroyed. // Instantiated on first use.
	return instance;
}

bool SystemClass::Initialise()
{
	// Initialise the swidth and height of the screen to zero
	// before sending into the function.
	int screenWidth = 0;
	int screenHeight = 0;
	bool result;
	// Initialise the windows Api
	InitialiseWindows(screenWidth, screenHeight);	
	return true;
}

void SystemClass::Shutdown()
{
	ShutdownWindows();
	
}

/*
This is the main loop for this function.
*/
// should this return false upon end
int WINAPI SystemClass::Run()
{
	
	
	bool result = true;

	// Initialise the message structure
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	// Loop until there is a quit message from the windows or the user.
	bool done = false;
	while (!done)
	{
		// Handle the windows messages.
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// If windows signals to end the application then exit out.
		if (msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			
			if (!Frame())
			{
				MessageBox(m_Hwnd, "Frame processing failed SystemClass::Run() ", "Error", MB_OK);
				done = true;
			}
		}
	
		
	}
	_CrtDumpMemoryLeaks();
	return static_cast<int>(msg.wParam);

}
/*
	Process the frame information and render the graphics scene/ update  // the frame is the same as the run(update/draw)
*/
bool SystemClass::Frame()
{

	
	return true;
}

LRESULT CALLBACK SystemClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
{
	return DefWindowProc(hwnd, umsg, wparam, lparam);
}

void SystemClass::InitialiseWindows(int& screenWidth, int& screenHeight)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// Get an external pointer to this object.
	SystemClass* m_ApplicationHandle = &SystemClass::GetInstance();

	// Get the instance of this application 
	m_HInstance = GetModuleHandle(NULL);

	// Give the application a name
	m_ApplicationName = "Engine";

	// Setup the windows class with default settings.
	WNDCLASSEX wc; 
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = m_HInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hIconSm = wc.hIcon;
	wc.hCursor= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = (LPCSTR)m_ApplicationName;
	wc.cbSize = sizeof(WNDCLASSEX);

	// Register the window class.
	RegisterClassEx(&wc);
	
	// Determine the resolution of the clients desktop screen.
	screenWidth = GetSystemMetrics(SM_CXSCREEN);
	screenHeight = GetSystemMetrics(SM_CYSCREEN);

	DEVMODE dmScreenSettings; 
	int posX, posY;
	// Setup the screen settings on wether it is running in full
	// screen or in windowed mode.
	if (FULL_SCREEN)
	{
		// If full screen set the screen to maximum size of the users 
		// Desktop and 32 bit
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = static_cast<unsigned long>(screenWidth);
		dmScreenSettings.dmPanningHeight = static_cast<unsigned long>(screenHeight);
		dmScreenSettings.dmBitsPerPel = 32;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;
		
		// Change the display settings to full screen
		ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

		// Set the position of the window to the top left corner.
		posX = posY = 0;
	}
	else
	{
		// if  windowed then set it to 800x600 resolution. 
		screenWidth = 800; 
		screenHeight = 600;

		// Place the window in the middle of the screen.
		posX = (GetSystemMetrics(SM_CXSCREEN) - screenWidth)/2;
		posY = (GetSystemMetrics(SM_CYSCREEN) - screenHeight)/2;

	}
	// Create the window with the screen settings and get the handle to it.
	//m_Hwnd = CreateWindowEx(WS_EX_APPWINDOW, (LPCSTR)m_ApplicationName, (LPCSTR)m_ApplicationName, WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_POPUP,
		//posX, posY, screenWidth, screenHeight, NULL, NULL, m_Hinstance, NULL);

	// second method to create window
	///m_Hwnd = CreateWindowA("Dx11WindowClass", "Demo", WS_OVERLAPPED, CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance, NULL);

	// so far the best this is the default
	m_Hwnd = CreateWindow(m_ApplicationName, m_ApplicationName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, screenWidth, screenHeight, NULL, NULL, m_HInstance, NULL);
	// Bring the window, up on the screen and set it as main focus.
	ShowWindow(m_Hwnd, SW_SHOW);
	SetForegroundWindow(m_Hwnd);
	SetFocus(m_Hwnd);

	// Hide the mouse cursor. 
	ShowCursor(false);
	return;
}
void SystemClass::ShutdownWindows()
{
	// show the mouse cursor.
	ShowCursor(true);

	// Fiz the display settings if leaving full screen mode.
	if (FULL_SCREEN)
	{
		ChangeDisplaySettings(NULL, 0);
	}
	// Remove the window.
	DestroyWindow(m_Hwnd); 
	m_Hwnd = NULL;

	// Remove the application instance.
	UnregisterClass((LPCSTR)m_ApplicationName, m_HInstance);
	m_HInstance = NULL;

	//// Release the pointer to this class
	//m_ApplicationHandle = NULL;

	return;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
{
	switch (umessage)
	{
		// chekc if the window is being destroyed.
		case WM_DESTROY:
		{
					   PostQuitMessage(0);
					   return 0;
		}
		// Check if the window is being closed.
		case WM_CLOSE:
		{
					 PostQuitMessage(0);
					 return 0;
		}
		// All other messages pass to the message handler in the system class.
		default:
		{
				   return SystemClass::GetInstance().MessageHandler(hwnd, umessage, wparam, lparam);
					//->MessageHandler(hwnd, umessage, wparam, lparam);
		}

	}
}