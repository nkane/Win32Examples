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

