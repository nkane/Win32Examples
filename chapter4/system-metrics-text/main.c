/*
 *  main.c
 *
 */

#include <windows.h>

#include "sysmetrics.h"

LRESULT CALLBACK
WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow);

int WINAPI
WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("System-Metrics");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;

    wndclass.style          = (CS_HREDRAW | CS_VREDRAW);
    wndclass.lpfnWndProc    = WndProc;
    wndclass.cbClsExtra     = 0;
    wndclass.cbWndExtra     = 0;
    wndclass.hInstance       = hInstance;
    wndclass.hIcon          = LoadIcon(NULL, IDI_APPLICATION);
    wndclass.hCursor        = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground  = (HBRUSH) GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName   = NULL;
    wndclass.lpszClassName  = szAppName;

    if (!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("This program failed to register a window class"), szAppName, MB_ICONERROR);
        return 0;
    }

    hwnd = CreateWindow(szAppName, TEXT("Get System Metrics No. 1"),
                        WS_OVERLAPPEDWINDOW | WS_VSCROLL,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, CW_USEDEFAULT,
                        NULL, NULL, hInstance, NULL);

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK
WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static int cxChar, cxCaps, cyChar, cyClient, iVscrollPos;
    HDC hdc;
    int i, y;
    PAINTSTRUCT ps;
    TCHAR szBuffer[10];
    TEXTMETRIC tm;

    switch (message)
    {
        case WM_CREATE:
        {
            hdc = GetDC(hwnd);
            GetTextMetrics(hdc, &tm);
            cxChar = tm.tmAveCharWidth;
            cxCaps = (tm.tmPitchAndFamily & 1 ? 3 : 2) * cxChar / 2;
            cyChar = tm.tmHeight + tm.tmExternalLeading;

            ReleaseDC(hwnd, hdc);

            SetScrollRange(hwnd, SB_VERT, 0, numlines - 1, FALSE);
            SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);
            
            return 0;
        } break;

        case WM_SIZE:
        {
            cyClient = HIWORD(lParam);
            return 0;
        } break;

        case WM_VSCROLL:
        {
            switch (LOWORD(wParam))
            {
                case SB_LINEUP:
                {
                    iVscrollPos -= 1;
                } break;
                
                case SB_LINEDOWN:
                {
                    iVscrollPos += 1;
                } break;

                case SB_PAGEUP:
                {
                    iVscrollPos -= cyClient / cyChar;
                } break;

                case SB_PAGEDOWN:
                {
                    iVscrollPos += cyClient / cyChar;
                } break;

                case SB_THUMBPOSITION:
                {
                    iVscrollPos = HIWORD(wParam);
                } break;

                default:
                    break;
            }

            iVscrollPos = max(0, min(iVscrollPos, numlines -1));

            if (iVscrollPos != GetScrollPos(hwnd, SB_VERT))
            {
                SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE);
                InvalidateRect(hwnd, NULL, TRUE);
            }

            return 0;
        } break;

        case WM_PAINT:
        {
            hdc = BeginPaint(hwnd, &ps);
            for (i = 0; i < numlines; i++)
            {
                y = cyChar * (i - iVscrollPos);
                TextOut(hdc, 0, y,
                        sysMetrics[i].szLabel,
                        lstrlen(sysMetrics[i].szLabel));

                TextOut(hdc, 22 * cxCaps, y,
                        sysMetrics[i].szDescription,
                        lstrlen(sysMetrics[i].szDescription));

                SetTextAlign(hdc, TA_RIGHT | TA_TOP);

                TextOut(hdc, 22 * cxCaps + 40 * cxChar, y, szBuffer,
                        wsprintf(szBuffer, TEXT("%5d"),
                                 GetSystemMetrics(sysMetrics[i].iIndex)));

                SetTextAlign(hdc, TA_LEFT | TA_TOP);
            }
            EndPaint(hwnd, &ps);
            return 0;
        } break;

        case WM_DESTROY:
        {
            PostQuitMessage(0);
            return 0;
        } break;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}
