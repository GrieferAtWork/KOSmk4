/* Copyright (c) 2019-2023 Griefer@Work                                       *
 *                                                                            *
 * This software is provided 'as-is', without any express or implied          *
 * warranty. In no event will the authors be held liable for any damages      *
 * arising from the use of this software.                                     *
 *                                                                            *
 * Permission is granted to anyone to use this software for any purpose,      *
 * including commercial applications, and to alter it and redistribute it     *
 * freely, subject to the following restrictions:                             *
 *                                                                            *
 * 1. The origin of this software must not be misrepresented; you must not    *
 *    claim that you wrote the original software. If you use this software    *
 *    in a product, an acknowledgement (see the following) in the product     *
 *    documentation is required:                                              *
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef _NT_WINCON_H
#define _NT_WINCON_H 1

#include "__stdinc.h"
/**/

#include "types.h"

#ifdef __CC__
__DECL_BEGIN

#define CONSOLE_REAL_OUTPUT_HANDLE LongToHandle(-2)
#define CONSOLE_REAL_INPUT_HANDLE  LongToHandle(-3)

#define CTRL_C_EVENT        0
#define CTRL_BREAK_EVENT    1
#define CTRL_CLOSE_EVENT    2
#define CTRL_LOGOFF_EVENT   5
#define CTRL_SHUTDOWN_EVENT 6

#define FOREGROUND_BLUE            0x0001
#define FOREGROUND_GREEN           0x0002
#define FOREGROUND_RED             0x0004
#define FOREGROUND_INTENSITY       0x0008
#define BACKGROUND_BLUE            0x0010
#define BACKGROUND_GREEN           0x0020
#define BACKGROUND_RED             0x0040
#define BACKGROUND_INTENSITY       0x0080
#define COMMON_LVB_LEADING_BYTE    0x0100
#define COMMON_LVB_TRAILING_BYTE   0x0200
#define COMMON_LVB_SBCSDBCS        0x0300
#define COMMON_LVB_GRID_HORIZONTAL 0x0400
#define COMMON_LVB_GRID_LVERTICAL  0x0800
#define COMMON_LVB_GRID_RVERTICAL  0x1000
#define COMMON_LVB_REVERSE_VIDEO   0x4000
#define COMMON_LVB_UNDERSCORE      0x8000

typedef WINBOOL(WINAPI *PHANDLER_ROUTINE)(DWORD CtrlType);

typedef struct _CONSOLE_CURSOR_INFO {
	DWORD dwSize;
	WINBOOL bVisible;
} CONSOLE_CURSOR_INFO, *PCONSOLE_CURSOR_INFO;

typedef struct _CONSOLE_SCREEN_BUFFER_INFO {
	COORD dwSize;
	COORD dwCursorPosition;
	WORD wAttributes;
	SMALL_RECT srWindow;
	COORD dwMaximumWindowSize;
} CONSOLE_SCREEN_BUFFER_INFO, *PCONSOLE_SCREEN_BUFFER_INFO;


typedef struct _CONSOLE_SCREEN_BUFFER_INFOEX {
	ULONG cbSize;
	COORD dwSize;
	COORD dwCursorPosition;
	WORD wAttributes;
	SMALL_RECT srWindow;
	COORD dwMaximumWindowSize;
	WORD wPopupAttributes;
	WINBOOL bFullscreenSupported;
	COLORREF ColorTable[16];
} CONSOLE_SCREEN_BUFFER_INFOEX, *PCONSOLE_SCREEN_BUFFER_INFOEX;

WINBASEAPI WINBOOL WINAPI GetConsoleCursorInfo(HANDLE hConsoleOutput, PCONSOLE_CURSOR_INFO lpConsoleCursorInfo);
WINBASEAPI WINBOOL WINAPI SetConsoleCursorInfo(HANDLE hConsoleOutput, CONST CONSOLE_CURSOR_INFO *lpConsoleCursorInfo);

WINBASEAPI COORD WINAPI GetLargestConsoleWindowSize(HANDLE hConsoleOutput);
WINBASEAPI WINBOOL WINAPI GetConsoleScreenBufferInfo(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo);
WINBASEAPI WINBOOL WINAPI GetConsoleScreenBufferInfoEx(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx);
WINBASEAPI WINBOOL WINAPI SetConsoleScreenBufferInfoEx(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx);
WINBASEAPI WINBOOL WINAPI GetNumberOfConsoleMouseButtons(LPDWORD lpNumberOfMouseButtons);
WINBASEAPI WINBOOL WINAPI SetConsoleActiveScreenBuffer(HANDLE hConsoleOutput);
WINBASEAPI WINBOOL WINAPI FlushConsoleInputBuffer(HANDLE hConsoleInput);
WINBASEAPI WINBOOL WINAPI SetConsoleCursorPosition(HANDLE hConsoleOutput, COORD dwCursorPosition);
WINBASEAPI WINBOOL WINAPI SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes);

WINBASEAPI WINBOOL WINAPI SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine, WINBOOL Add);
WINBASEAPI WINBOOL WINAPI GenerateConsoleCtrlEvent(DWORD dwCtrlEvent, DWORD dwProcessGroupId);

WINBASEAPI WINBOOL WINAPI SetConsoleTitleA(LPCSTR lpConsoleTitle);
WINBASEAPI WINBOOL WINAPI SetConsoleTitleW(LPCWSTR lpConsoleTitle);

WINBASEAPI WINBOOL WINAPI ReadConsoleA(HANDLE hConsoleInput, LPVOID lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead, LPVOID lpReserved);
WINBASEAPI WINBOOL WINAPI ReadConsoleW(HANDLE hConsoleInput, LPVOID lpBuffer, DWORD nNumberOfCharsToRead, LPDWORD lpNumberOfCharsRead, LPVOID lpReserved);
WINBASEAPI WINBOOL WINAPI WriteConsoleA(HANDLE hConsoleOutput, CONST VOID *lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved);
WINBASEAPI WINBOOL WINAPI WriteConsoleW(HANDLE hConsoleOutput, CONST VOID *lpBuffer, DWORD nNumberOfCharsToWrite, LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved);

WINBASEAPI UINT WINAPI GetConsoleCP(VOID);
WINBASEAPI WINBOOL WINAPI SetConsoleCP(UINT wCodePageID);
WINBASEAPI UINT WINAPI GetConsoleOutputCP(VOID);
WINBASEAPI WINBOOL WINAPI SetConsoleOutputCP(UINT wCodePageID);

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_WINCON_H */
