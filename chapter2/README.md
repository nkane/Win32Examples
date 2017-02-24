# Chapter 2 - An Introduction to Unicode 

### Unicode
Unicode is an extension of ASCII character encoding. Rather than the 7 bits used to represent each character in strict ACII,
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
in C are based on the wchar_t data type. This type is defined in several different header files, including WHCAR.H - example:
```C
typedef unsigned short wchar_t;
```
The data type wchar_t is the same as an unsigned short integer (16 bits wide).

An example of how to define and initialize a wchar_t single character in C:
```C
wchar_t c = 'A';
```
The variable c has a two byte hexidecimal value of 0x0041 - this is the Unicode representation of the letter 'A'. Keep in mind that 
Intel's architecture is little endian, so the bytes are stored by the least-significant byte. In memory the sequence it should be
0x41 next to 0x00.

An example of how to define and initialize a wchar_t string in C:
```C
wchar_t *p = L"Hello!";
```
The L (for long) preceding the first quotation mark indicates to the compiler that the string is to be stored with wide characters
with every character occupying 2 bytes. The pointer variable p requires 4 bytes of storage, but the character string requires
14 bytes - 2 bytes for each character with 2 bytes for the zeros at the end.

An example of how to define and initalize a wchar_t char array in c:
```C
static wchar_t a[] = L"Hello!";
```
Similiar to the wchar_t pointer initialization, the above wchar_t array requires 14 bytes of storage. Using the sizeof() expression
will return with the byte size 14. The value of a[1] is the wide character 'e', or the hexidecimal value 0x0065.

### Wide-Character Library Functions
The length of a normal 1 byte per character string can be found by using the strlen function call. Here is an exampl:
```C
char *pc = "Hello!";

iLength = strlen(pc);
```
The varaible iLength will be set to 6, the number of characters in the char pointer variable pc.


If we change the type to a wide character pointer, and attempt to call the strlen function a compiler warning will appear.
```C
wchar_t *pw = L"Hello!";

// NOTE: causes compiler warning!
// 'function' : incompatible types - from 'unsigned short *' to 'const char *'
iLenght = strlen(pw);
```
The compiler warning is attempting to notify you that the strlen function argument accepts a type char pointer, but instead
a unsigned short has been passed in. The program will still compile and run, but the value of iLength will not be accurate 
and instead be set to the value 1.

The 6 characters of the character string "Hello!" have the 16-bit values:
```plain
0x0048 0x0065 0x06C 0x006F 0x0021
```

Below is how a little endian system would ordre the bytes:
```plain
48 00 65 00 6C 00 6C 00 6F 00 21 00
```

The strlen function attempts to find the length of a string of characters by counting the bytes. In the above situation, 
the function would count the first byte as a character, but it would assume that the second byte is a zero byte denoting
the end of the string. This example illustrates the difference between the C language and the run-time library functions.
The comiler interprets the string L"Hello!" as a collection of 16-bit short integers and stores them in the wchar_t array.
The compiler also handles any array indexing and the sizeof operator, so these work properly; however, functions that are
added during link time such as strlen expect strings that comprise of single-byte characters do not perform the operations
that were intended.

Fortunately, a majority of the C library functions that accept string arguments were rewritten in order to accept wide
character arguments. An example is the function strlen, the wide character version is called wcslen ("wide character
string length"), and it is declared both in STRING.H (where the declaration for strlen resides) and WCHAR.H.

The strlen function declaration:
```C
size_t __cdecl strlen(const char*);
```

The wcslen function declaration:
```C
size_t __cdecl wcslen (const wchar_t*);
```

### Maintaining a Single Source
One of the major disadvantages to 16 bit Unicode is that a program using 15 bit Unicode strings will occupy twice as much
space; additionally, functions in the wide-character run-time library are larger than the usual functions. Creating two
different versions of a program - one for ASCII strings and the other with Unicode strings might be a solution; however,
another solution would be to attempt to maintain a single source base file that could compile for either ASCII or Unicode.
There is a problem here, though - the run-time library functions have different names, characters are defined differently,
and the preceding L in wide characters. 

In order to help maintain a single source code base the TCHAR.H file included with Mircosoft Visual C++ provides a set
of alternative names for the normal run-time library functions requiring string parameters. These are sometimes referred
to as "generic" function names becuase they can refer to either the Unicode or non-Unicode version of the functions.

If an identifier _UNICODE is defined and the TCHAR.H header file is included in the program, _tcslen is defined to be
wcslen:
```C
#define _tsclen wcslen
```

If UNICODE is not defined, _tcslen is defined to be strlen:
```C
#define _tcslen strlen
```

Examples of other cases handled by TCHAR.H
```C
// _UNICODE is defined
typedef wchar_t TCHAR;

// _UNICODE is not defined
typedef char TCHAR;

// Macro to address wide char preceeding L
#define __T(x) L##x
```

Lets describe what is going on with that macro, because the syntax is fairly obscure. In the ANSI C standard for the C
preprocessor, the pair of number signs is called a "token paste", and it causes the letter L to be appended to the macro
parameter. For example, if the macro parameter is "Hello!", then L##x is L"Hello!".

### Windows Header File Types
Windows program includes the header file WINDOW.H, and this file includes a number of other header files, including
WINDEF.H - this header file contains many of the basic type definitions used in Windows and which itself includes
WINNT.H. The WINNT.H header file handles the basic Unicode support.

The WINT.H header file includes the C header file CTYPE.H. The CTYPE.H header file is one of many C header files that have
a definition of wchar_t; however, the WINNT.H header file defines new data types named CHAR and WCHAR:

```C
typedef char CHAR;
typedef wchar_t WCHAR;
```

CHAR and WCHAR are the data tyapes recommended for your use in a Windows program when a 8-bit character and 16-bit character
needs to be defined; additonally, the WINNT.H header file goes on to define six data types that can be used as pointers to
8-bit character strings and for data types that can be used as pointers to const 8-bit character strings:

```C
typedef CHAR * PCHAR, * LPCH, * PCH, * NPSTR, * LPSTR, * PSTR;

typedef CONST CHAR * LPCCH, * PCCH, * LPCSTR, * PCSTR;
```

The N and L prefixes stand for "near" or "long" and refer to the two different sizes of pointers in 16-bit Windows. There
is no differentiation between near and long pointers in Win32.

The WINNT.H header file includes defines for another six data types that can be used as pointers to 16-bit character strings
and four data types that can be used as pointers to const 16-bit character strings:

```C
typedef WCHAR * PWCHAR, * LPWCH, * PWCH, * NWPSTR, * LPWSTR, * PWSTR;
typedef CONST WCHAR * LPCWHC, * PCWCH, * LPCWSTR, * PCWSTR;
``` 

An example of TCHAR.H:

```C
#ifdef UNICODE

typedef WCHAR TCHAR, * PTCHAR;
typedef LPWSTR LPTCH, PTCH, PTSTR, LPTSTR;
typedef LPCWSTR LPCTSTR;

#define __TEXT(quote) L##quote

#else

typedef char TCHAR, * PTCHAR;
typedef LPSTR LPTCH, PTCH, PTSTR, LPTSTR;
typedef LPCSTR LPCTSTR;

#define __TEXT(quote) quote

#endif

#define TEXT(quote) __TEXT(quote)

```

These definitions let you mix ASCII and Unicode characters strings in the same program or write a single program that can
be compiled for either ASCII or Unicode.

### The Windows Function Calls
In a 16-bit version of Windows the MessageBox function was located in the dynamic-link library USER.EXE. In the WINDOWS.H
header files, the MessageBox function was defined as follows:

```C
int WINAPI MessageBox (HWND, LPCSTR, LPCSTR, UINT);
```

The second and third arguments to the function are pointers to constant character strings. When a  Win16 program was compiled
and linked, Windows left the call to MessageBox unresolved. A table in the program's executable file allowed Windows to
dynamically link the call from the program to the MessageBox function located in the USER library.





