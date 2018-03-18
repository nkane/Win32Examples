/*
 *  devcaps
 *
 */

#include <windows.h>

#define numlines((int) (sizeof devcaps / sizeof devcaps[0]))

struct 
{
    int     iIndex;
    TCHAR   *szLabel;
    TCHAR   *szDesc;
}
devcaps [] =
{
    HORZSIZE,       TEXT("HORZSIZE"),     TEXT("Width in millimeters"),
    VERTSIZE,       TEXT("VERTSIZE"),     TEXT("Height in millimeters"),
    HORZRES,        TEXT("HORZRES"),      TEXT("Width in pixels:"),
    VERTRES,        TEXT("VERTRES"),      TEXT("Height in pixels"),
    BITSPIXEL,      TEXT("BITSPIXEL"),    TEXT("Color bits per pixel"),
    PLANES,         TEXT("PLANES"),       TEXT("Number of color planes:"),
    NUMBRUSHES,     TEXT("NUMBRUSHES"),   TEXT("Number of device brushes:"),
    NUMPENS,        TEXT("NUMPENS"),      TEXT("Number of device pens:"),
    NUMMARKERS,     TEXT("NUMMARKERS"),   TEXT("Number of device markers:"),
    NUMFONTS,       TEXT("NUMFONTS"),     TEXT("Number of device fonts:"),
    NUMCOLORS,      TEXT("NUMCOLORS"),    TEXT("Number of device colors:"),
    PDEVICESIZE,    TEXT("PDEVICESIZE"),  TEXT("Size of device structure:"),
    ASPECTX,        TEXT("ASPECTX"),      TEXT("Relative width of pixel:"),
    ASPECTY,        TEXT("ASPECTY"),      TEXT("Relative height of pixel:"),
    ASPECTXY,       TEXT("ASPECTXY"),     TEXT("Relative diagonal of pixel:"),
    LOGPIXELSX,     TEXT("LOGPIXELSX"),   TEXT("Horizonal dots per inch:"),
    LOGPIXELSY,     TEXT("LOGPIXELSY"),   TEXT("Vertical dots per inch:"),
    SIZEPALETTE,    TEXT("SIZEPALETTE"),  TEXT("Number of palette entries:"),
    NUMRESERVED,    TEXT("NUMRESERVED"),  TEXT("Reserved palette entries:"),
    COLORRES,       TEXT("COLORRES"),     TEXT("Actual color resolution:"),
};

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
