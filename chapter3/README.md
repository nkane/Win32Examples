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

#### Thinking Globally - The Windows Function Calls
HELLOWINDOW.C makes calls to no fewer than 18 Windows functions. In the order they occur, these functions
are:

```plain
* LoadIcon: Loads an icon for use by a program.
```
