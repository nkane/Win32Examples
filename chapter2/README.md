# Chapter 2 - An Introduction to Unicode 

### Unicode
Unicode is an extension of ASCII character encoding. Rather than the 7 bitse used to represent each character in strict ACII,
or the 8 bits per character that have become common on computers, Unicode uses a full 16 bits for character encoding. This
allows Unicode to represent all the letters, ideographs, and other symbols used in all the written languages of the world
that are likely to be used in computer communication.

### American Standard Code for Information Interchange (ASCII)
ASCII, had it's origins in the late 1950s and was finalized in 1967. The American National Standards Institue (ANSI) documented
the ASCII coded character sets to be 7-bit in 1986. Below is a view of a ASCII table:

![ASCII Table](https://i.imgur.com/Xn6pBU9.gif)

### The char Data Type
To understand how C handles wide characters, an understanding of normal character definition for Win32 programs is necessary.

An example of how to define and initializes a variable containing a single character in C:
```C
char c = 'A';
```
The above code variable c requires 1 byte of storage and will be initialized with the hexadecimal value	0x41, which is the ASCII
code for the letter A.

An example of how to define a char pointer in C:
```C
char *p;
```
Depending on the operating system, the size of the pointer could vary. In Win32, the pointer variable require 4 bytes of storage.

An example of how to define a char pointer with a string value in C:
```C
char *p = "Hello!";
```
The variable p is still a pointer, so it requires at least 4 bytes of storage; additionally, the character stored in static memory
and uses 7 bytes of storage the 6 bytes for the string with another 1 byte for the terminating 0.

An example of how to define a char array in C:
```C
char a[10];
```
The variable a is a fixed length, so the compiler reserves 10 bytes of storage for the array. Using the "sizeof()" expression with
the variable a will return a result of 10.

An example of how to define and initialize a char array in C:
```C
char a[] = "Hello!";
```

An example of how to define and initialize a static char array in C:
```C
static char a[] = "Hello!";
```

### Wider Characters
Unicode or wide characters do not alter the meaning of the char data type in C. The char continues to indicate 1 byte of storage,
and the sizeof(char) continues to return 1; however, depending on architecture a byte in C can be greater than 8 bits. Wide characters
in C are based on the wchart_t data type. This type is defined in several different header files, including WHCAR.H - example:
```C
typedef unsigned short wchar_t;
```
The data type wchar_t is the same as an unsigned short integer (16 bits wide).

An example of how to define and initialize a wchar_t in C:
```C
wchar_t c = 'A';
```
The variable c has a two byte hexidecimal value of 0x0041 - this is the Unicode representation of the letter 'A'.
