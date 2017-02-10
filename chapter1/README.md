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

The WinMain function is declared as returning an int. The WINAPI identifier is defined in WINDEF.H with the statement:

```C
#define WINAPI __stdcall
```

The __stdcall calling convention is used to call Win32 API functions. The callee cleans the stack, so the compiler makes
vararg functions __cdecl. Functions that use this calling convention require a function prototype.

The __cdecl is the default calling convention for C and C++ programs. Because the stack is cleaned up by the caller, it can
do vararg functions. The __cdecl calling convention creates larger executables than __stdcall, because it requires each
function call to include stack cleanup code.


### MessageBox Function
The MessageBox function is designed to display short messages.


### Compile and Linking
During the compiling stage, the compiler generates an .OBJ (object) file from the C source code file. Next, during the linking stage the linker combines the .OBJ file with .LIB (library) files to create the .EXE (executable).
