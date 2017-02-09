# Chapter 1 - The Basics 

### Header Files
* WINDEF.H 	: Basic type definiton.
* WININT.H 	: Type definition for Unicode support.
* WINBASE.H 	: Kernel functions.
* WINUSER.H	: User interface functions.
* WINGDI.H	: Graphicsdevice interface functions.

### Program Entry Point
Windows program entry point is "WinMain", and it is declared in "WINBASE.H". WinMain can appear like the follow:

```C
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		   PSTR szCmdLine, int iCmdShow)
```
