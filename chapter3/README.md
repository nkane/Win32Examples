# Chapter 3 - Windows and Messages

### An Architectural Overview
Windows provides structures for objects known as a "window". These windows could contain a title bar, toolbar,
a scroll bar. Another type of window is the dialog box. Windows contains "child windows" or "control windows"
or "child window controls" that could be push buttons, check boxes, list boxes, scroll bars, and text-entry
fields. 

End users see these windows as objects on the screen and interact directly with them using the keyboard or
the mouse. From a programmer's perspective, the window receives the user input in the form of "messages"
to the window. These messages are used to communicate with other windows as well.

Windows translates a message and dispatches messages that is sent to a callback function defined in your
current program. The parameters to this function describe the particular message that is being sent by
Windows and received by your program - the name of this function is known as the "window procedure".

An example of a callback function:

```C
void populateArray(int *array, int arraySize, int (*getNextValue)(void))
{
	for (int i = 0; i < arraySize; ++i)
	{
		array[i] = getNextValue();
	}
}

int getNextRandomValue(void)
{
	return rand();
}

int main(void)
{
	int testArray[10];
	populateArray(testArray, 10, getNextRandomValue);
}
```
[Stack Overflow - C Callback](https://stackoverflow.com/questions/142789/what-is-a-callback-in-c-and-how-are-they-implemented)

A callback function is a function that is caled through a function pointer. If a pointer (address) of a
function is passed to another function as an argument and the pointer is used to call the function it
points to it is said that a call back is made.

Fundamentally, Windows operating system is making calls to your program. Every window that a program creates
has an associated window procedure. That procedure is a function that could be either in the program itself
or in a dynamica-link library. The Windows operating systems sends a message to a window by calling the
window procedure. The define window procedure processes the messaged based on the type of message received
and returns control to the operating system.

A "window class" identifies the window procedure that processes the message to the window. The use of a
window class alows multiple windows to be based on the same window class and hence use the same window
procedure.

When a Windows program begins execution, the operating system creates a "message queue" for the program.
This message queue stores messages to all the windows a program might create; additionally, the program
includes a code "message loop" to retrieve these messages from the queue and dispatch them to the
appropriate window procedure. Other messages are sent directly to the window procedure without being
placed in the message queue.

### Thinking Globally
The "hello window" example that has been provided is basically overhead found in every Windows program. The
source file HELLOWINDOW.C has a WinMain function, and a second function named WndProc - this is the window
procedure. Notice that the source code does not contain an explicit call to WndProc; however, these is a
reference to WndProc in WinMain, which is why the function is declared near the top of the program.

### The Windows Function Calls
HELLOWINDOW.C makes calls to no fewer than 18 Windows functions. In the order they occur, these functions
are:

```plain
* LoadIcon: Loads an icon for use by a program.

* LoadCursor: Loads a mouse cursor for use by a program.

* GetStockObject: Obtains a graphic object, in this case a brush used for painting the window's background.

* RegisterClass: Registers a window class for the program's window.

* MessageBox: Displays a message box.

* CreateWindow: Creates a window based on a window class.

* ShowWindow: Shows the window on the screen.

* UpdateWindow: Directs the window to paint intself.

* GetMessage: Obtains a message from the message queue.

* TranslateMessage: Translates some keyboard messages.

* DispatchMessage: Sends a message to a window procedure.

* PlaySound: Plays sound file.

* BeginPaint: Initiates the beginning of window painting.

* GetClientRect: Obtains the dimensions of the window's client area.

* DrawText: Displays a text string.

* EndPaint: Ends window painting.

* PostQuitMessage: Inserts a "quit" message into the message queue.

* DefWindowProc: Performs default processing of message.
```

These functions are described in the Platform SDK documentation, and they are declared in various header
files - WINUSER.H

### Uppercase Identifiers
In the example program source code HELLOWINDOW.C, there are quiet a few uppercase identifiers. These
identifiers are defined in the Windows header files:

```plain
CS_HREDRAW		DT_VCENTER		SND_FILENAME

CS_VREDRAW		IDC_ARROW		WM_CREATE

CW_USEDEFAULT		IDI_APPLICATION		WM_DESTROY

DT_CENTER		MB_ICONERROR		WM_PAINT

DT_SINGLELINE		SND_ASYNC		WS_OVERLAPPEDWINDOW
```

These are simply numeric constants. Here are what the prefixes stand for:

```plain
CS		Class style option
CW		Create window potion
DT		Draw text option
IDI		ID number for an icon
IDC		ID number for a cursor
MB		Message box option
SND		Sound option
WM		Window message
WS		Window style
```

### New Data Types
Other identifiers used in the example source code HELLOWINDOW.C are newer data types, also defined in the
Windows header files using either typedef or #define statements. Originally it was thought that this
would ease the transition of Windows programs from 16-bit systems to 32-bit technology; however, this did
not work as smoothly and transparently as it was thought at the time. 

Some of the new data types are just convenient abbreviations. For example, the UINT data type used for the
second parameter to WndProc is an unsigned int - in Win32 API is a 32-bit value. The PSTR data type used
for the third parameter to WinMain is a pointer to a nonwide character string, that is, a char * (pointer).

Some of the new data types are more cryptic, such as the third and fourth parameter to WndProc defined as
WPARAM and LPARAM. In order to understand these names, a bit of Windows history is necessary. When Windows
as a 16-bit operating system, the third parameter to WndProc was defined as a WORD, which was a 16-bit
unsigned short integer, and the fourth parameter was defined as a LONG, which was a 32-bit signed long
integer. That's the reason for the "W" and "L" prefixes on the word "PARAM". In the 32-bit version of
Windows WPARAM is defined as a UINT and LPARAM is defined as LONG (in C the long data type), so that both
parameters to the window procedure are 32-bit values.

