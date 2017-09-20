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

A callback function is a function that is called through a function pointer. If a pointer (address) of a
function is passed to another function as an argument and the pointer is used to call the function it
points to it is said that a call back is made.

Fundamentally, Windows operating system is making calls to your program. Every window that a program creates
has an associated window procedure. That procedure is a function that could be either in the program itself
or in a dynamically-link library. The Windows operating systems sends a message to a window by calling the
window procedure. The define window procedure processes the messaged based on the type of message received
and returns control to the operating system.

A "window class" identifies the window procedure that processes the message to the window. The use of a
window class allows multiple windows to be based on the same window class and hence use the same window
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
* LoadIcon: 		Loads an icon for use by a program.

* LoadCursor: 		Loads a mouse cursor for use by a program.

* GetStockObject: 	Obtains a graphic object, in this case a brush used for painting the window's background.

* RegisterClass: 	Registers a window class for the program's window.

* MessageBox: 		Displays a message box.

* CreateWindow: 	Creates a window based on a window class.

* ShowWindow: 		Shows the window on the screen.

* UpdateWindow: 	Directs the window to paint itself.

* GetMessage: 		Obtains a message from the message queue.

* TranslateMessage: 	Translates some keyboard messages.

* DispatchMessage: 	Sends a message to a window procedure.

* PlaySound: 		Plays sound file.

* BeginPaint: 		Initiates the beginning of window painting.

* GetClientRect: 	Obtains the dimensions of the window's client area.

* DrawText: 		Displays a text string.

* EndPaint: 		Ends window painting.

* PostQuitMessage: 	Inserts a "quit" message into the message queue.

* DefWindowProc: 	Performs default processing of message.
```

These functions are described in the Platform SDK documentation, and they are declared in various header
files - WINUSER.H

### Uppercase Identifiers
In the example program source code HELLOWINDOW.C, there are quiet a few uppercase identifiers. These
identifiers are defined in the Windows header files:

```plain
CS_HREDRAW
DT_VCENTER		
SND_FILENAME
CS_VREDRAW
IDC_ARROW
WM_CREATE
CW_USEDEFAULT
IDI_APPLICATION
WM_DESTROY
DT_CENTER
MB_ICONERROR
WM_PAINT
DT_SINGLELINE
SND_ASYNC
WS_OVERLAPPEDWINDOW
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
for the third parameter to WinMain is a pointer to a non-wide character string, that is, a char * (pointer).

Some of the new data types are more cryptic, such as the third and fourth parameter to WndProc defined as
WPARAM and LPARAM. In order to understand these names, a bit of Windows history is necessary. When Windows
as a 16-bit operating system, the third parameter to WndProc was defined as a WORD, which was a 16-bit
unsigned short integer, and the fourth parameter was defined as a LONG, which was a 32-bit signed long
integer. That's the reason for the "W" and "L" prefixes on the word "PARAM". In the 32-bit version of
Windows WPARAM is defined as a UINT and LPARAM is defined as LONG (in C the long data type), so that both
parameters to the window procedure are 32-bit values. The "W" prefix to the "PARAM" creates a misnomer.

The WndProc function returns a value of type LRESULT, meaning a LONG. The WinMain function is given a type of
WINAPI (as well as every Windows function call  defined in the header files), and the WndProc function is given
a type of CALLBACK - both of these identifiers are defined as "__stdcall", which refers to a special calling
sequence for function calls that occur between Windows itself and an application.

The HELLOWINDOW.C example uses four data structures - below is a list:

```plain
Structure		Meaning
--------------		------------------------
MSG			Message structure
WNDCLASS		Window class structure
PAINTSTRUCT		Paint structure
RECT			Rectangle structure
```

### Getting a Handle on Handles
There are three uppercase identifiers for various types of "handles":

```plain
Identifier		Meaning
--------------		----------------------
HINSTANCE		Handle to an "instance" - the program itself
HWND			Handle to a window
HDC			Handle to a device context
```

Windows frequently makes use of handle. A handle is simply a number (usually 32 bits in size) that refers to
an object. The handles in Windows are similar to file handles used in conventional C or MS-DOS programming. A
program always obtains a handle by calling a Windows function. The program uses the handle in other Windows
functions to refer to the object. The actual value of the handle is unimportant to your program, but the Window
module that gives your program the handle knows how to use it to reference the object.

### Hungarian Notation
Many Windows programmers use a variable-naming convention known as "Hungarian Notation", in honor of the legendary
Microsoft programmer Charles Simonyi. How does Hungarian notation work? The variable name begins with a lowercase
letter or letters that denote the data type of the variable. For example, sz prefix in szCmdLIne stands for
"string terminated by zero", and the h prefix in hInstance and hPrevInstance stands for "handle"; additionally, the
i prefix in iCmdShow stands for "integer". The last two parameters WndProc use Hungarian Notation, but as explained
earlier the wParam should properly be named uiParam; however, because these two parameters are defined using the
data types WPARAM and LPARAM, the example was written to retain their traditional names.

When naming struct variables, use the structure's name (or an abbreviation of the structure name) in lowercase either
as a prefix to the variable name or as the entire variable name. For example, in the WinMain function in HELLOWINDOW.c,
the msg variable is a structure of the MSG type, wndclass is a structure of the WNDCLASS type. In the WndProc function,
ps is a PAINTSTRUCT structure and rect is a RECT structure.

Below is a list of prefixes that are commonly used in Hungarian notation:
```plain
Prefix			Data Type
-----------		------------------------------------
c			char or WCHAR or TCHAR
by			BYTE (unsigned char)
n			short
i			int
x, y			int used as x-coordinate or y-coordinate
cx, cy			int used as x or y length; c stans for "count"
b or f			BOOL (int); f stands for "flag"
w			WORD (unsigned short)
l			LONG (long)
dw			DWORD (unsigned long)
fn			function
s			string
sz			string terminated by 0 character
h			handle
p			pointer
```

### Registering the Window Class
A window is always created based on a window class. The window class identifies the window procedure that processes
messages to the window; additionally, multiple window can be created based on a single window class. An example of this
would be, buttons in windows - such as push buttons, check boxes, and radio button - these are created based on the same
window class. The window class defines the window procedure and other characteristics of the window that are created based
on that class.

Prior to creating an application window, a window class must be registered by calling RegisterClass funciton. This function
requires a single parameter - a pointer to a structure of type WNDCLASS. This structure has two different definitions in
WINUSER.h header file. First there is the ASCII version, WNDCLASSA:

```C
// lpfn means 'long pointer to a function'
// recall in Win32 API there is no distinction between long pointers
// and near pointers. This is a remnant of 16-bit Windows
// The cb prefix stands for "count of bytes" and is often used for
// a variable that denotes a byte size. The h prefix is a handle,
// and the hbr means "handle to a brush". The lpsz prefix is a "long pointer
// to a string terminated with a zero"
typedef struct tagWNDCLASSA
{
	UINT		style;
	WNDPROC		lpfnWndProc;
	int		cbClsExtra;
	int 		cbWndExtra;
	HINSTANCE	hInstance;
	HICON		hIcon;
	HCURSOR		hCursor;
	HBRUSH		hbrBackground;
	LPCSTR		lpszMenuName;
	LPCSTR		lpszClassName;
}
WNDCLASSA, * PWNDCLASSA, NEAR * NPWNDCLASSA, FAR * LPWNDCLASSA;
```

Second there is the Unicode version of the structure:

```C
typedef struct tagWNDCLASSW
{
	UINT		style;
	WNDPROC		lpfnWndProc;
	int		cbClsExtra;
	int		cbWndExtra;
	HINSTANCE	hInstance;
	HICON		hIcon;
	HCURSOR		hCursor;
	HBRUSH		hBrBackground;
	LPCWSTR		lpszMenuName;
	LPCWSTR		lpszClassName;
}
WNDCLASSW, * PWNDCLASSW, NEAR * NPWNDCLASSW, FAR * LPWNDCLASSW;
```

The only difference is that the last two fields are defined as pointers to constants wide character strings rather than
pointers to constant ASCII character strings. After defining both of these structures, preprocessor statements are
made in order to determine what to typedef properly:

```C
#ifdef UNICODE
typedef WNDCLASSW WNDCLASS;
typedef PWNDCLASSW PWNDCLASS;
typedef NPWNDCLASSW NPWNDCLASS;
typedef LPWNDCLASSW LPWNDCLASS;
#else
typedef WNDCLASSA WNDCLASS;
typedef PWNDLASSA PWNDCLASS
typedef NPWNDCLASSA NPWNDCLASS;
typedef LPWNDCLASSA LPWNDCLASS;
#endif
```

In WinMain, a WNDCLASS variable should be made with all 10 fields initialized and passed to the function RegisterClass.
The two most import fields in this structure is the second WNDPROC and last LPCSTR (or Unicode equivalent). The other fields
describe characteristics of the window class. The style field in the WNDCLASS struct is a bitmask field that can use
defined constants from the WINUSER.h header file for styling typically "CS_*". Example of WINUSER.h header defines:

```C

#define CS_VREDRAW		0x0001
#define CS_HREDRAW		0x0002
#define CS_KEYCVTWINDOW		0x0004
#define	CS_DBLCLKS		0x0008
#define CS_OWNDC		0x0020
#define CS_CLASSDC		0x0040
#define CS_PARENTDC		0x0080
#define	CS_NOKEYCVT		0x0100
#define CS_NOCLOSE		0x0200
#define	CS_SAVEBITS		0x0800
#define CS_BYTEALIGNCLIENT	0X1000
#define CS_BYTEALIGNWINDOW	0X2000
#define	CS_GLOBALCLASS		0x4000
#define CS_IME			0x00010000

```

These define fields are called "bit flags", because each identifier sets a single bit in a composite value. The two values used
in the example program hellowindow indicates that  all windows created based on this class are to be completed repainted whenever
the horizontal window size (CS_HREDRAW) or the vertical window size (CS_VREDRAW) changes. When the window is resized, you should
see that the text string is redrawn to be in the new center of the window.

The second field of the WNDCLASS structure is initialized by the statement:

```C
wndclass.lpfnWndProc = WndProc;
```

This sets the window procedure for this window class to WndProc, which is the second function in the example hellowindow.c. This
window procedure will process all message to all windows created based on this window class. In C, when you use a function name
in a statement like this, you are referring to a pointer to a function.

The next two fields are used to reverse extra space in the class structure and the window structure that Windows maintains
internally:

```C

wndclass.cbClsExtra = 0;
wndclass.cbWndExtra = 0;

```

A program can use this extra space for its own purposes. The example does not use this feature, so zero is specified. Otherwise,
as the Hungarian notation indicates, the field would be set to a "count of bytes".

The next field is simply the instance handle of the program (which is one of the parameters to WinMain):

```C

wndclass.hInstance = hInstance;

```

The following statement sets an icon for all windows created based on this window class. The icon is a small bitmap picture that
represents the program to the user. When the program is running, the icon appears in the Window taskbar and at the left side of
the program window's title bar.

```C

wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);

```

The following statement loads a predefined mouse cursor known as IDC_ARROW and returns a handle to the cursor. This handle is
assigned to the bCursor field of the WNDCLASS structure. When the mouse cursor appears over the client area of a window that is
created based on this class, the cursor becomes a small arrow.

```C

wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);

```

The next field specifies that background color of the client area of windows created based on this class. The hbr prefix of the
hbrBackground field name stands for "handle to a brush". A brush is a graphics term that refers to a colored patterned of pixel
used to fill an area. Windows has several standard, or "stock", brushes. The GetStockObject call shown here returns a handle to
a white brush. This means that the background of the client area of the window will be solid white, which is a common choice:

```C

wndclass.hbrBackground = GetStockObject(WHITE_BRUSH);

```

The next field specifies the window class menu, the example hellowindow does not have an application menu, so the field is set to
NULL.

```C

wndclass.lpszMenuName = NULL;

```

Finally the class must be given a name, the field lpszClassName stores the name of the class. This string is composed of either
ASCII characters or Unicode characters depending on whether the UNICODE identifier has been defined.

```C

wndclass.lpszClassName = szAppName;

```

When all ten fields of the structure have been initialized, the example program hellowindow registers the window class by calling
the RegisterClass function. The only argument to the function is a pointer to the WNDCLASS structure; however, there are two different
function calls in reality - RegisterClassA function that takes a WNDCLASSA and RegisterClassW function that takes a WNDCLASSW, which
function the program uses to register the window class determines whether messages are sent to the window will contain ASCII text
or Unicode text.

If you receive a failure from initializing a window from a window class, the GetLastError function helps your determine the cause of
the error. GetLastError is a general-purpose function in Windows to get extended error information when a function call fails. You
can look in WINERROR.H to see the values of error code identifiers.

### Creating the Windows
The window class defines general characteristics of a window, thus allowing the same window class to be used to create many different windows. When you create a window by calling CreateWindow, more specific information
is provided to the window.

The window class and the window are different, and this could cause confusion. All push-button windows are created based on the same window class. The window procedure associated with this class is located
inside Windows itself, and it is responsible for processing keyboard and mouse input to the push button and defining the button's visual appearance on the screen.

The CreateWindow function call returns a handle to the created window. This handle is typically saved in a variable. Programs will use this handle to refer to the window. If a program creates many windows,
each has a different handle. The handle to a window is one of the most important handles that a Windows program handles.

```C

hwnd = CreateWindow(szAppName,				// window class name
		    TEXT("The Hello Program"),		// window caption
		    WS_OVERLAPPEDWINDOW,		// window style
		    CW_USEDEFAULT,			// initial x position
		    CW_USEDEFAULT,			// initial y position
		    CW_USEDEFAULT,			// initial x size
		    CW_USEDEFAULT,			// initial y size
		    NULL,				// parent window handle
		    NULL, 				// window menu handle
		    hInstance,				// program instance handle
		    NULL);

```

### Displaying the Windows
After a window class has been registered and a window has been created internally in Windows - meaning that Windows has allocated a block of memory to hold all the information about the
window that was specified in the CreateWindow call.

In order to display the window, two more calls are needed. The first is ShowWindow(hwnd, iCmdShow). The ShowWindow function puts the window on the display. The function call UpdateWindow(hwnd), then causes the client
area to be painted. It accomplishes this by sending the window procedure (this is, the WndProc function) a WM_PAINT message.

### The Message Loop
After the UpdateWindow function call, the window is fully visible on the video display. The program must now make itself ready to read keyboard and mouse input from the user. Windows maintains a "message queue" for each Windows
program currently running under Windows. When an input event occurs, Windows translates the event into a "message" that it places in the program's message queue.

A program retrieves these message from the message queue by executing a block of code known as the "message loop":

```C

while(GetMessage(&msg, NULL, 0, 0))
{
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

```

The msg variable is a structure of type MSG, which is defined in WINUSER.H header file:

```C

typdef struct tagMSG
{
	HWND 	hwnd;
	UINT	message;
	WPARAM	wParam;
	LPARAM  lParam;
	DWORD	time;
	POINT	pt;
}
MSG, * PMSG;

```
The POINT data type is yet another structure, defined in the WINDDEF.H header file like this:

```C

typedef struct tagPOINT
{
	LONG	x;
	LONG	y;
}
POINT, *PPOINT;

```

The GetMessage call that begins the message loop retrieves a message from the message queue:

```C

GetMessage(&msg, NULL, 0, 0);

```

This call passes to Windows a pointer to a MSG structure named msg. THe second, third, and forth arguments are set to NULL or 0 to indicate that the program wants all messages for all window created by the program.
Windows fills in the fields of the message structure with the next message queue. The fields of the structure are:

```plain

* hwnd 		- the handle to the window which message is directed to.

* message 	- the message indentifier. this is the number that identifies the message. For each message, there is a corresponding identifier defined in the Windows header file (most of them in WINUSER.H) that begins
		  with the identifier WM ("window message").

* wParam 	- a 32-bit "message parameter", the meaning and value of which depend on the particular message.

* lParam 	- another 32-bit message was placed in the message queue.

* time 		- the time the message was placed in the message queue.

* pt 		- the mouse coordinate at the time the message was placed in the message queue.

```

If the message field of the message retrieved from the message queue is anything except WM_QUIT (which equals 0x0012), GetMessage returns a nonzero value. A WM_QUIT message causes GetMessage to return 0. TranslateMessage
function call passes the msg struct back to Windows for keyboard translation and the Dispatch function call passes the msg struct back to Windows. Windows then sends the messages to the appropriate window procedure for
processing. Meaning, Windows calls the WndProc function. AFter WndProc processes the message, it returns control to Windows, which is still servicing the DispatchMessage call. When Windows returns from the DispatchMessage
call, the message loop continuesd with the next GetMessage call.

```C

TranslateMessage(&msg);

DispatchMessage(&msg);

```

### The Window Procedure
The window procedure determines what the widnow displays in its client area and how the window responds to user input. A window procedure can have any name (as long as it doesn't conflict with some other name). A
Windows program can contain more than one window procedure. A window procedure is always associated with a particular window class that you register by calling RegisterClass. The CreateWindow function creates a window
based on a particular window class. More than one window can be created based on the same window class. A window procedure is always defined like this:

```C

/* 
 * hwnd 		- handle to window
 * message		- a number that identifies the message
 * wParam / lParam	- 32-bit message parameters that provide more information about
 * 			  the message. What these parameters contain is specific to each
 *			  type of message. Sometimes a message parameter is two 16-bit 
 *			  values stuck together, and sometimes a message parameter is a
 * 			  pointer to a text string or to a data structure.
 *
 */
LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)

```

If a program creates multiple windows based on the same window class (and hence the same window procedure), hwnd identifies the particular window receiving the message. Programs generally don't call window procedures
directly. A program can indirectly call its own window procedure by calling a function named SendMessage.

### Processing the Messages
Every message that a window procedure receives is identified by a number, which is the message parameter to the window procedure. The Windows header file WINUSER.H defines identifiers beginning with the prefix WM
("window message") for each type of message. A switch and case construction can be used to determine what message the window procedure is receiving and how to process accordingly. When a window procedure processes
a message, it should return 0 from the window procedure. All message that a window procedure chooses not to process must be passed to a Windows function named DefWindowProc. The vbalue returned from DefWindowProc
must be returned from the window procedure.

```C

switch (iMsg)
{
	case WM_CREATE:
		// [process WM_CREATE message]
		return 0;
	case WM_PAINT:
		// [process WM_PAINT message]
		return 0;
	case WM_DESTROY:
		// [process WM_DESTORY message]
		return 0;
}

return DefWindowProc(hwnd, iMsg, wParam, lParam);

```

It is important to call DefWindowProc for default processing of all messages that your window procedure does not process; otherwise, behavior regarded as normal such as beinng able to terminate the program, will not work.

### Playing a Sound File
The function PlaySound is called in order have a sound played - in the example, it was requested to have the sound played asynchronously - that is, the PlaySound function call is to return as soon as the sound file starts
playing without waiting for it to complete. 

```C

PlaySound(TEXT("hellwin.wav"), NULL, (SND_FILENAME | SND_ASYNC));

```

### The WM_PAINT Message
The WM_PAINT message is extremely important in Windows programming. It informs a program when part or all of the window's client area is "invalid" and must be "updated", which means that it must be redrawns or "painted".
The message is sent whenever the program calls UpdateWindow in WinMain, and it directs the window procedure to draw something on the client area; additionally, when resizing a window, the client area becomes invalid -
recall that the example HELLOWINDOW wndclass structure style field was set to the flags CS_HREDRAW and CS_VREDRAW, this directs Window to invalidate the whole window when the size changes. THe window procedure
then recieves a WM_PAINT message.

Whenever a window is minimized, Windows does not save the contents of the client area. This would be too data expensive to retain, and instead Windows invalidates the windows and starts to "rebroadcast"/"capture" paint
messages whenever the window is restored; additionally, when window overlaps another window - Windows does not save the area of a window covered by another window. When that area of the window later is unconvered, it
is flagged as invalid and paint messages are "broadcasted"/"received" again.

Usually, the WM_PAINT message being with a call to BeginPaint and ends with EndPaint:

```C
hdc = BeginPaint(hwnd, &ps);
EndPaint(hwnd, &ps);
```

In both cases, the first argument is a handle to the program's window, and the second argument is a pointer to a structure of type PAINTSTRUCT. The PAINTSTRUCT structure contains some information that window procedure
that a window procedure can use for painting the client area. These will be discussed later.

When calling BeginPaint, Windows erases the background of the client area if it hasnot been erased already. The background is erased using the brush specified in the hbrBackground field of the WNDCLASS structure used
to register the window class. This call validates the entire client area and returns a "handle to a device context". A device context refers to a physical output device (such as a video display) and its device driver.
The device context handle is needed to display text and graphics in the client area of the window. Using the device context handle returned from BeginPaint, you cannot draw outside the client area, even if it is
attempted. EndPaint releases the device context handle invalidating it.

If a window procedure does not process the WM_PAINT message, it must be passed on to DefWindowProc, which simply calls BeginPaint and EndPaint in succession validating the client area. After WndProc calls BeginPaint, 
GetClientRect is called

```C
GetClientRect(hwnd, &rect);
```

The first argument is the handle to the program's window, second argument is a pointer to a rectangle structure of type RECT. This structure has four LONG fields named left, top, right, and bottom. The GetClientRect
function sets these four fields to the dimensions of the client area of the window. The left and top fields are always set to 0, right and bottom fields represent the width and height of the client area in pixels.

WndProc does not do anything with the RECT structure except pass a pointer to it as the fourth argument to DrawText:

```C
DrawText(hdc, TEXT("Hello, Windows!"), -1, &rect, DT_SINGLELINE | DT_CENTER | CT_VCENTER);
```

DrawText, as the name impies, draws text - since this function draws something the first argument is a handle to the device context returned from BeginPaint, the second argument is the text to draw, and the third
argument is set to -1 to indicate that the text string is terminated with a zero character. The last argument to DrawText is a series of bit flags defined in WINUSER.H - although DrawText seems to be a GDI function
call because it displays output, it is actually considered part of the User module because it is fairly high-level drawing function.

### The WM_DESTORY Message
This message indicates that Windows is in the process of destorying a window based on a command from the user. THe message is a result of the user clicking on the close button or selecting close from
the program's system menu. Earlier it was mentioned that GetMessage returns nonzero for any message other than WM_QUIT that it retrieves from the message queue. When GetMessage retrieves a WM_QUIT message,
GetMessage returns 0 - causing WinMain to drop out of the message loop and executres the following state:

```C
return msg.wParam;
```

The wParam field of the structure is the value passed to the PostQuitMessage function (generally 0) - the above return statement exits from WinMain and terminates the program.

### The Windows Programming Hurdles
A standard simply Windows application - WinMain contains only program overhead necessary to register the window class, create the window, and retrieve and dispatch messages from the message queue. All the real
action of the program occures in the window procedure.

### Don't Call Me, I'll Call You
Windows makes calls to your program, specifically to the window procedure called WndProc in the example. The window procedure is associated with a window class that the program reigsters by calling RegisterClass.
A window that is created based on this window class uses the window procedure for processing all messages to the window. Windows sends a message to the window by calling the window procedure. Usually, 
all of the calls to WndProc are in the form of messages. In most Windows programs, the bulk of the program is dedicated to handling these messages. The messages that Windows can send to a program are generally
identified with names that begin with the letter WM and are defined in the WINUSER.H header file.

The idea of a rutine within a program that is called from outside of the program is not unheard of in character-mode programming. The signal function in C can trap a Ctrl-C break or other interrupts from the
operating system. Old programs written for MS-DOS often trapped hardware interrupts.

In Windows this concept is extended to cover everything. Everything that happens to a window is relayed to the window procedure in the form of a message. The window procedure then responds to this message
in some way or passes the message to DefWindowPRoc for default processing.

### Queued and Nonqueued Messages


