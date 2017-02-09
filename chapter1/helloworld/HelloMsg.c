#include <windows.h>

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance,
	  	    PSTR szCmdLine, int iCmdShow)
{
	MessageBox(NULL, "Hello, World!", "HelloMsg", 0);
	return 0;
}
