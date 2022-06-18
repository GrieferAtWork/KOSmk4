/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBKERNEL32_WINCON_C
#define GUARD_LIBKERNEL32_WINCON_C 1

#define _KOS_SOURCE 1
#define _UTF_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"

#include <kos/except.h>
#include <kos/ioctl/video.h>
#include <kos/types.h>
#include <nt/wincon.h>
#include <nt/winnls.h>
#include <sys/ioctl.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <format-printer.h>
#include <malloc.h>
#include <paths.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <uchar.h>
#include <unicode.h>
#include <unistd.h>
#include <wchar.h>

#include <libansitty/ctl.h>

DECL_BEGIN

/************************************************************************/
#ifndef _PATH_TTY
#define _PATH_TTY "/dev/tty"
#endif /* !_PATH_TTY */

#ifdef AT_FDCTTY
#define gettty() AT_FDCTTY
#elif defined(stdtty)
#define gettty() fileno(stdtty)
#else /* ... */
static fd_t saved_ttyfd = -1;
PRIVATE fd_t gettty(void) {
	fd_t result = saved_ttyfd;
	if (result == -1) {
		if (isatty(STDIN_FILENO))
			result = STDIN_FILENO;
		else {
			result = open(_PATH_TTY, O_RDONLY);
			if (result < 0)
				result = STDIN_FILENO; /* Shouldn't happen... */
		}
		saved_ttyfd = result;
	}
	return result;
}
#endif /* !... */


static WINBOOL cursor_visible  = TRUE;
static WORD console_attributes = (FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

PRIVATE char const fg_color_to_ansi_code[16][6] = {
	/* [(0)]                                                                          = */ AC_FG_BLACK,   /* ANSITTY_CL_BLACK */
	/* [(FOREGROUND_BLUE)]                                                            = */ AC_FG_NAVY,    /* ANSITTY_CL_NAVY */
	/* [(FOREGROUND_GREEN)]                                                           = */ AC_FG_GREEN,   /* ANSITTY_CL_GREEN */
	/* [(FOREGROUND_BLUE | FOREGROUND_GREEN)]                                         = */ AC_FG_TEAL,    /* ANSITTY_CL_TEAL */
	/* [(FOREGROUND_RED)]                                                             = */ AC_FG_MAROON,  /* ANSITTY_CL_MAROON */
	/* [(FOREGROUND_RED | FOREGROUND_BLUE)]                                           = */ AC_FG_PURPLE,  /* ANSITTY_CL_PURPLE */
	/* [(FOREGROUND_RED | FOREGROUND_GREEN)]                                          = */ AC_FG_OLIVE,   /* ANSITTY_CL_OLIVE */
	/* [(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)]                        = */ AC_FG_SILVER,  /* ANSITTY_CL_SILVER */
	/* [(FOREGROUND_INTENSITY)]                                                       = */ AC_FG_GREY,    /* ANSITTY_CL_GREY */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_BLUE)]                                     = */ AC_FG_BLUE,    /* ANSITTY_CL_BLUE */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_GREEN)]                                    = */ AC_FG_LIME,    /* ANSITTY_CL_LIME */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN)]                  = */ AC_FG_AQUA,    /* ANSITTY_CL_AQUA */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_RED)]                                      = */ AC_FG_RED,     /* ANSITTY_CL_RED */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE)]                    = */ AC_FG_FUCHSIA, /* ANSITTY_CL_FUCHSIA */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN)]                   = */ AC_FG_YELLOW,  /* ANSITTY_CL_YELLOW */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)] = */ AC_FG_WHITE,   /* ANSITTY_CL_WHITE */
};

PRIVATE char const bg_color_to_ansi_code[16][7] = {
	/* [(0)]                                                                          = */ AC_BG_BLACK,   /* ANSITTY_CL_BLACK */
	/* [(FOREGROUND_BLUE)]                                                            = */ AC_BG_NAVY,    /* ANSITTY_CL_NAVY */
	/* [(FOREGROUND_GREEN)]                                                           = */ AC_BG_GREEN,   /* ANSITTY_CL_GREEN */
	/* [(FOREGROUND_BLUE | FOREGROUND_GREEN)]                                         = */ AC_BG_TEAL,    /* ANSITTY_CL_TEAL */
	/* [(FOREGROUND_RED)]                                                             = */ AC_BG_MAROON,  /* ANSITTY_CL_MAROON */
	/* [(FOREGROUND_RED | FOREGROUND_BLUE)]                                           = */ AC_BG_PURPLE,  /* ANSITTY_CL_PURPLE */
	/* [(FOREGROUND_RED | FOREGROUND_GREEN)]                                          = */ AC_BG_OLIVE,   /* ANSITTY_CL_OLIVE */
	/* [(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)]                        = */ AC_BG_SILVER,  /* ANSITTY_CL_SILVER */
	/* [(FOREGROUND_INTENSITY)]                                                       = */ AC_BG_GREY,    /* ANSITTY_CL_GREY */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_BLUE)]                                     = */ AC_BG_BLUE,    /* ANSITTY_CL_BLUE */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_GREEN)]                                    = */ AC_BG_LIME,    /* ANSITTY_CL_LIME */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_BLUE | FOREGROUND_GREEN)]                  = */ AC_BG_AQUA,    /* ANSITTY_CL_AQUA */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_RED)]                                      = */ AC_BG_RED,     /* ANSITTY_CL_RED */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE)]                    = */ AC_BG_FUCHSIA, /* ANSITTY_CL_FUCHSIA */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN)]                   = */ AC_BG_YELLOW,  /* ANSITTY_CL_YELLOW */
	/* [(FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)] = */ AC_BG_WHITE,   /* ANSITTY_CL_WHITE */
};

INTERN WINBOOL WINAPI
libk32_SetConsoleTextAttribute(HANDLE hConsoleOutput, WORD wAttributes) {
	fd_t ttyfd;
	TRACE("SetConsoleTextAttribute(%p, %#x)", hConsoleOutput, wAttributes);
	(void)hConsoleOutput;
	if (wAttributes == console_attributes)
		return TRUE;
	ttyfd = gettty();
	if ((console_attributes & 0xf) != (wAttributes & 0xf)) {
		char const *str = fg_color_to_ansi_code[wAttributes & 0xf];
		if (writeall(ttyfd, str, strlen(str) * sizeof(char)) < 0)
			return FALSE;
	}
	if ((console_attributes & 0xf0) != (wAttributes & 0xf0)) {
		char const *str = bg_color_to_ansi_code[(wAttributes & 0xf0) >> 4];
		if (writeall(ttyfd, str, strlen(str) * sizeof(char)) < 0)
			return FALSE;
	}
	if ((console_attributes & COMMON_LVB_GRID_HORIZONTAL) != (wAttributes & COMMON_LVB_GRID_HORIZONTAL)) {
		if (wAttributes & COMMON_LVB_GRID_HORIZONTAL) {
			if (writeall(ttyfd, AC_STRIKETHROUGH_ON, sizeof(AC_STRIKETHROUGH_ON) - sizeof(char)) <= 0)
				return FALSE;
		} else {
			if (writeall(ttyfd, AC_STRIKETHROUGH_OFF, sizeof(AC_STRIKETHROUGH_OFF) - sizeof(char)) <= 0)
				return FALSE;
		}
	}
	if ((console_attributes & COMMON_LVB_UNDERSCORE) != (wAttributes & COMMON_LVB_UNDERSCORE)) {
		if (wAttributes & COMMON_LVB_UNDERSCORE) {
			if (writeall(ttyfd, AC_UNDERLINE_ON, sizeof(AC_UNDERLINE_ON) - sizeof(char)) <= 0)
				return FALSE;
		} else {
			if (writeall(ttyfd, AC_UNDERLINE_OFF, sizeof(AC_UNDERLINE_OFF) - sizeof(char)) <= 0)
				return FALSE;
		}
	}
	console_attributes = wAttributes;
	return TRUE;
}


INTERN WINBOOL WINAPI
libk32_SetConsoleCursorPosition(HANDLE hConsoleOutput, COORD dwCursorPosition) {
	char buffer[64];
	size_t len;
	fd_t ttyfd;
	TRACE("SetConsoleCursorPosition(%p, {%u,%u})",
	      hConsoleOutput, dwCursorPosition.X, dwCursorPosition.Y);
	ttyfd = gettty();
	(void)hConsoleOutput;
	len = sprintf(buffer, AC_CUP("%u", "%u"),
	              dwCursorPosition.Y,
	              dwCursorPosition.X);
	return writeall(ttyfd, buffer, len * sizeof(char)) >= 0;
}


INTERN WINBOOL WINAPI
libk32_GetConsoleCursorInfo(HANDLE hConsoleOutput, PCONSOLE_CURSOR_INFO lpConsoleCursorInfo) {
	TRACE("GetConsoleCursorInfo(%p, %p)", hConsoleOutput, lpConsoleCursorInfo);
	(void)hConsoleOutput;
	if (lpConsoleCursorInfo->dwSize != sizeof(CONSOLE_CURSOR_INFO)) {
		errno = EINVAL;
		return FALSE;
	}
	lpConsoleCursorInfo->bVisible = cursor_visible;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_SetConsoleCursorInfo(HANDLE hConsoleOutput, CONST CONSOLE_CURSOR_INFO *lpConsoleCursorInfo) {
	TRACE("SetConsoleCursorInfo(%p, %p)", hConsoleOutput, lpConsoleCursorInfo);
	(void)hConsoleOutput;
	if (lpConsoleCursorInfo->dwSize != sizeof(CONSOLE_CURSOR_INFO)) {
		errno = EINVAL;
		return FALSE;
	}
	if (cursor_visible != lpConsoleCursorInfo->bVisible) {
		static_assert(sizeof(AC_SHOWCURSOR) == sizeof(AC_HIDECURSOR));
		cursor_visible = lpConsoleCursorInfo->bVisible;
		return writeall(gettty(),
		                cursor_visible ? AC_SHOWCURSOR
		                               : AC_HIDECURSOR,
		                (sizeof(AC_SHOWCURSOR) - sizeof(char))) < 0;
	}
	return TRUE;
}

INTERN COORD WINAPI
libk32_GetLargestConsoleWindowSize(HANDLE hConsoleOutput) {
	COORD result;
	struct winsize wsz;
	TRACE("GetLargestConsoleWindowSize(%p)", hConsoleOutput);
	(void)hConsoleOutput;
	result.X = 80;
	result.Y = 25;
	if (ioctl(gettty(), TIOCGWINSZ, &wsz) >= 0) {
		result.X = wsz.ws_col;
		result.Y = wsz.ws_row;
	}
	return result;
}

PRIVATE BOOL CC
libk32_GetConsoleCursorPosition(fd_t ttyfd, COORD *pResult) {
	unsigned int x, y;
	char response[64];
	static char const req[] = _AC_ESC "[6n"; /* DSR */
	size_t resplen;
	if (writeall(ttyfd, req, sizeof(req) - sizeof(char)) < 0)
		return FALSE;
	do {
		resplen = read(ttyfd, response, sizeof(response));
	} while (resplen == 0 || (resplen < 0 && errno == EINTR));
	if (resplen <= 0)
		return FALSE;
	if (sscanf(response, _AC_ESC "[%u;%uR", &x, &y) != 2)
		return FALSE;
	pResult->X = x;
	pResult->Y = y;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_GetConsoleScreenBufferInfo(HANDLE hConsoleOutput,
                                  PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo) {
	fd_t ttyfd;
	struct winsize wsz;
	TRACE("GetConsoleScreenBufferInfo(%p, %p)", hConsoleOutput, lpConsoleScreenBufferInfo);
	(void)hConsoleOutput;
	ttyfd = gettty();
	lpConsoleScreenBufferInfo->dwSize.X        = 80;
	lpConsoleScreenBufferInfo->dwSize.Y        = 25;
	lpConsoleScreenBufferInfo->srWindow.Left   = 0;
	lpConsoleScreenBufferInfo->srWindow.Top    = 0;
	lpConsoleScreenBufferInfo->srWindow.Right  = 80 * 9;
	lpConsoleScreenBufferInfo->srWindow.Bottom = 25 * 16;
	if (ioctl(ttyfd, TIOCGWINSZ, &wsz) >= 0) {
		lpConsoleScreenBufferInfo->dwSize.X        = wsz.ws_col;
		lpConsoleScreenBufferInfo->dwSize.Y        = wsz.ws_row;
		lpConsoleScreenBufferInfo->srWindow.Right  = wsz.ws_xpixel;
		lpConsoleScreenBufferInfo->srWindow.Bottom = wsz.ws_ypixel;
	}
	lpConsoleScreenBufferInfo->dwMaximumWindowSize = lpConsoleScreenBufferInfo->dwSize;
	if (!libk32_GetConsoleCursorPosition(ttyfd, &lpConsoleScreenBufferInfo->dwCursorPosition))
		return FALSE;
	lpConsoleScreenBufferInfo->wAttributes = console_attributes;
	return TRUE;
}


static COLORREF const default_ColorTable[16] = {
#define RGB(r, g, b) ((r) | ((g) << 8) | ((b) << 16))
	/* [ANSITTY_CL_BLACK]   = */ RGB(0x00, 0x00, 0x00),
	/* [ANSITTY_CL_MAROON]  = */ RGB(0xaa, 0x00, 0x00),
	/* [ANSITTY_CL_GREEN]   = */ RGB(0x00, 0xaa, 0x00),
	/* [ANSITTY_CL_OLIVE]   = */ RGB(0xaa, 0x55, 0x00),
	/* [ANSITTY_CL_NAVY]    = */ RGB(0x00, 0x00, 0xaa),
	/* [ANSITTY_CL_PURPLE]  = */ RGB(0xaa, 0x00, 0xaa),
	/* [ANSITTY_CL_TEAL]    = */ RGB(0x00, 0xaa, 0xaa),
	/* [ANSITTY_CL_SILVER]  = */ RGB(0xaa, 0xaa, 0xaa),
	/* [ANSITTY_CL_GREY]    = */ RGB(0x55, 0x55, 0x55),
	/* [ANSITTY_CL_RED]     = */ RGB(0xff, 0x55, 0x55),
	/* [ANSITTY_CL_LIME]    = */ RGB(0x55, 0xff, 0x55),
	/* [ANSITTY_CL_YELLOW]  = */ RGB(0xff, 0xff, 0x55),
	/* [ANSITTY_CL_BLUE]    = */ RGB(0x55, 0x55, 0xff),
	/* [ANSITTY_CL_FUCHSIA] = */ RGB(0xff, 0x55, 0xff),
	/* [ANSITTY_CL_AQUA]    = */ RGB(0x55, 0xff, 0xff),
	/* [ANSITTY_CL_WHITE]   = */ RGB(0xff, 0xff, 0xff),
#undef RGB
};

INTERN WINBOOL WINAPI
libk32_GetConsoleScreenBufferInfoEx(HANDLE hConsoleOutput, PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx) {
	fd_t ttyfd;
	struct winsize wsz;
	TRACE("GetConsoleScreenBufferInfoEx(%p, %p)", hConsoleOutput, lpConsoleScreenBufferInfoEx);
	ttyfd = gettty();
	(void)hConsoleOutput;
	if (lpConsoleScreenBufferInfoEx->cbSize != sizeof(*lpConsoleScreenBufferInfoEx)) {
		errno = EINVAL;
		return FALSE;
	}
	lpConsoleScreenBufferInfoEx->dwSize.X        = 80;
	lpConsoleScreenBufferInfoEx->dwSize.Y        = 25;
	lpConsoleScreenBufferInfoEx->srWindow.Left   = 0;
	lpConsoleScreenBufferInfoEx->srWindow.Top    = 0;
	lpConsoleScreenBufferInfoEx->srWindow.Right  = 80 * 9;
	lpConsoleScreenBufferInfoEx->srWindow.Bottom = 25 * 16;
	if (ioctl(ttyfd, TIOCGWINSZ, &wsz) >= 0) {
		lpConsoleScreenBufferInfoEx->dwSize.X        = wsz.ws_col;
		lpConsoleScreenBufferInfoEx->dwSize.Y        = wsz.ws_row;
		lpConsoleScreenBufferInfoEx->srWindow.Right  = wsz.ws_xpixel;
		lpConsoleScreenBufferInfoEx->srWindow.Bottom = wsz.ws_ypixel;
	}
	lpConsoleScreenBufferInfoEx->dwMaximumWindowSize = lpConsoleScreenBufferInfoEx->dwSize;
	if (!libk32_GetConsoleCursorPosition(ttyfd, &lpConsoleScreenBufferInfoEx->dwCursorPosition))
		return FALSE;
	lpConsoleScreenBufferInfoEx->wAttributes          = console_attributes;
	lpConsoleScreenBufferInfoEx->wPopupAttributes     = console_attributes; /* ??? */
	lpConsoleScreenBufferInfoEx->bFullscreenSupported = TRUE;
	memcpy(lpConsoleScreenBufferInfoEx->ColorTable, default_ColorTable, sizeof(default_ColorTable));
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_SetConsoleScreenBufferInfoEx(HANDLE hConsoleOutput,
                                    PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx) {
	CONSOLE_SCREEN_BUFFER_INFOEX oldattr = { sizeof(oldattr) };
	TRACE("SetConsoleScreenBufferInfoEx(%p, %p)", hConsoleOutput, lpConsoleScreenBufferInfoEx);
	if (!libk32_GetConsoleScreenBufferInfoEx(hConsoleOutput, &oldattr))
		return FALSE;
	if (memcmp(&lpConsoleScreenBufferInfoEx->srWindow, &oldattr.srWindow, sizeof(oldattr.srWindow)) != 0)
		goto illegal;
	if (memcmp(&lpConsoleScreenBufferInfoEx->dwSize, &oldattr.dwSize, sizeof(oldattr.dwSize)) != 0)
		goto illegal;
	if (memcmp(&lpConsoleScreenBufferInfoEx->dwMaximumWindowSize, &oldattr.dwMaximumWindowSize, sizeof(oldattr.dwMaximumWindowSize)) != 0)
		goto illegal;
	if (lpConsoleScreenBufferInfoEx->bFullscreenSupported != oldattr.bFullscreenSupported)
		goto illegal;
	if (memcmp(lpConsoleScreenBufferInfoEx->ColorTable, oldattr.ColorTable, sizeof(oldattr.ColorTable)) != 0)
		goto illegal;
	if (memcmp(&lpConsoleScreenBufferInfoEx->dwCursorPosition,
	           &oldattr.dwCursorPosition, sizeof(oldattr.dwCursorPosition)) != 0) {
		if (!libk32_SetConsoleCursorPosition(hConsoleOutput, lpConsoleScreenBufferInfoEx->dwCursorPosition))
			return FALSE;
	}
	if (lpConsoleScreenBufferInfoEx->wAttributes != oldattr.wAttributes) {
		if (!libk32_SetConsoleTextAttribute(hConsoleOutput, lpConsoleScreenBufferInfoEx->wAttributes))
			return FALSE;
	}
	return TRUE;
illegal:
	errno = EINVAL;
	return FALSE;
}

INTERN WINBOOL WINAPI
libk32_GetNumberOfConsoleMouseButtons(LPDWORD lpNumberOfMouseButtons) {
	TRACE("GetNumberOfConsoleMouseButtons(%p)", lpNumberOfMouseButtons);
	*lpNumberOfMouseButtons = 3;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_SetConsoleActiveScreenBuffer(HANDLE hConsoleOutput) {
	TRACE("SetConsoleActiveScreenBuffer(%p)", hConsoleOutput);
	(void)hConsoleOutput;
	return ioctl(gettty(), VID_IOC_ACTIVATE) >= 0;
}

INTERN WINBOOL WINAPI
libk32_FlushConsoleInputBuffer(HANDLE hConsoleInput) {
	TRACE("FlushConsoleInputBuffer(%p)", hConsoleInput);
	(void)hConsoleInput;
	return ioctl(gettty(), TCFLSH, TCIFLUSH) >= 0;
}


PRIVATE PHANDLER_ROUTINE ctrl_handler   = NULL;
PRIVATE sighandler_t old_sigint_handler = NULL;
PRIVATE void LIBCCALL sigint_handler(int UNUSED(signo)) {
	if (ctrl_handler != NULL)
		(*ctrl_handler)(CTRL_C_EVENT);
}

INTERN WINBOOL WINAPI
libk32_SetConsoleCtrlHandler(PHANDLER_ROUTINE HandlerRoutine, WINBOOL Add) {
	TRACE("SetConsoleCtrlHandler(%p, %u)", HandlerRoutine, Add);
	if (Add) {
		if (ctrl_handler) {
			errno = ENOMEM;
			return FALSE;
		}
		ctrl_handler = HandlerRoutine;
		old_sigint_handler = signal(SIGINT, &sigint_handler);
		return old_sigint_handler != SIG_ERR;
	} else {
		if (ctrl_handler != HandlerRoutine) {
			errno = EINVAL;
			return FALSE;
		}
		signal(SIGINT, old_sigint_handler);
		ctrl_handler = NULL;
	}
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_GenerateConsoleCtrlEvent(DWORD dwCtrlEvent, DWORD dwProcessGroupId) {
	TRACE("GenerateConsoleCtrlEvent(%#x, %#x)", dwCtrlEvent, dwProcessGroupId);
	if (dwCtrlEvent == CTRL_C_EVENT)
		return kill(-(pid_t)dwProcessGroupId, SIGINT) >= 0;
	errno = EINVAL;
	return FALSE;
}

INTERN WINBOOL WINAPI
libk32_SetConsoleTitleA(LPCSTR lpConsoleTitle) {
	TRACE("SetConsoleTitleA(%q)", lpConsoleTitle);
	return dprintf(gettty(),
	               _AC_ESC "]" /* OSC */
	               "2;"        /* Command #2: Set window title */
	               "%s"        /* Actual window title */
	               "\7",       /* BEL to terminate string */
	               lpConsoleTitle) >= 0;
}

INTERN WINBOOL WINAPI
libk32_SetConsoleTitleW(LPCWSTR lpConsoleTitle) {
	WINBOOL result;
	char *utf8;
	TRACE("SetConsoleTitleW(%I16q)", lpConsoleTitle);
	utf8 = convert_c16tombs(lpConsoleTitle);
	if (!utf8)
		return FALSE;
	result = libk32_SetConsoleTitleA(utf8);
	free(utf8);
	return result;
}

INTERN WINBOOL WINAPI
libk32_ReadConsoleA(HANDLE hConsoleInput, LPVOID lpBuffer,
                    DWORD nNumberOfCharsToRead,
                    LPDWORD lpNumberOfCharsRead, LPVOID lpReserved) {
	fd_t ttyfd;
	ssize_t total;
	TRACE("ReadConsoleA(%p, %p, %#x, %p, %p)",
	      hConsoleInput, lpBuffer, nNumberOfCharsToRead,
	      lpNumberOfCharsRead, lpReserved);
	ttyfd = gettty();
	(void)hConsoleInput;
	(void)lpReserved;
	total = read(ttyfd, lpBuffer, nNumberOfCharsToRead);
	if (total < 0)
		return FALSE;
	*lpNumberOfCharsRead = (DWORD)total;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_ReadConsoleW(HANDLE hConsoleInput, LPVOID lpBuffer,
                    DWORD nNumberOfCharsToRead,
                    LPDWORD lpNumberOfCharsRead, LPVOID lpReserved) {
	PRIVATE mbstate_t incomplete = MBSTATE_INIT;
	fd_t ttyfd;
	struct format_c16snprintf_data printer;
	struct format_8to16_data convert;
	TRACE("ReadConsoleW(%p, %p, %#x, %p, %p)",
	      hConsoleInput, lpBuffer, nNumberOfCharsToRead,
	      lpNumberOfCharsRead, lpReserved);
	ttyfd = gettty();
	(void)hConsoleInput;
	(void)lpReserved;
	printer.sd_buffer     = (char16_t *)lpBuffer;
	printer.sd_bufsiz     = nNumberOfCharsToRead;
	convert.fd_arg        = &printer;
	convert.fd_printer    = &format_c16snprintf_printer;
	convert.fd_incomplete = incomplete;
	while (printer.sd_bufsiz != 0) {
		char buf[1];
		ssize_t total = read(ttyfd, buf, sizeof(buf));
		if (total < 0)
			goto err;
		if (total == 0)
			break;
		/* Feed into the unicode converter. */
		format_8to16(&convert, buf, total);
	}
	incomplete           = convert.fd_incomplete;
	*lpNumberOfCharsRead = nNumberOfCharsToRead - (DWORD)printer.sd_bufsiz;
	return TRUE;
err:
	incomplete = convert.fd_incomplete;
	return FALSE;
}

INTERN WINBOOL WINAPI
libk32_WriteConsoleA(HANDLE hConsoleOutput, CONST VOID *lpBuffer,
                     DWORD nNumberOfCharsToWrite,
                     LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved) {
	fd_t ttyfd;
	ssize_t total;
	TRACE("WriteConsoleA(%p, %p, %#x, %p, %p)",
	      hConsoleOutput, lpBuffer, nNumberOfCharsToWrite,
	      lpNumberOfCharsWritten, lpReserved);
	ttyfd = gettty();
	(void)hConsoleOutput;
	(void)lpReserved;
	total = write(ttyfd, lpBuffer, nNumberOfCharsToWrite);
	if (total < 0)
		return FALSE;
	*lpNumberOfCharsWritten = (DWORD)total;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_WriteConsoleW(HANDLE hConsoleOutput, CONST VOID *lpBuffer,
                     DWORD nNumberOfCharsToWrite,
                     LPDWORD lpNumberOfCharsWritten, LPVOID lpReserved) {
	PRIVATE char16_t surrogate = 0;
	struct format_16to8_data convert;
	fd_t ttyfd;
	TRACE("WriteConsoleW(%p, %p, %#x, %p, %p)",
	      hConsoleOutput, lpBuffer, nNumberOfCharsToWrite,
	      lpNumberOfCharsWritten, lpReserved);
	ttyfd = gettty();
	(void)hConsoleOutput;
	(void)lpReserved;
	convert.fd_printer   = &write_printer;
	convert.fd_arg       = WRITE_PRINTER_ARG(ttyfd);
	convert.fd_surrogate = surrogate;
	if (format_16to8(&convert, (char16_t const *)lpBuffer, nNumberOfCharsToWrite) < 0)
		return FALSE;
	surrogate = convert.fd_surrogate;
	*lpNumberOfCharsWritten = nNumberOfCharsToWrite;
	return TRUE;
}

INTERN UINT WINAPI
libk32_GetConsoleCP(VOID) {
	TRACE("GetConsoleCP()");
	COMPILER_IMPURE();
	return CP_UTF8;
}

INTERN WINBOOL WINAPI
libk32_SetConsoleCP(UINT wCodePageID) {
	TRACE("SetConsoleCP(%u)", wCodePageID);
	(void)wCodePageID;
	COMPILER_IMPURE();
	return TRUE;
}

INTERN UINT WINAPI
libk32_GetConsoleOutputCP(VOID) {
	TRACE("GetConsoleOutputCP()");
	COMPILER_IMPURE();
	return CP_UTF8;
}

INTERN WINBOOL WINAPI
libk32_SetConsoleOutputCP(UINT wCodePageID) {
	TRACE("SetConsoleOutputCP(%u)", wCodePageID);
	(void)wCodePageID;
	COMPILER_IMPURE();
	return TRUE;
}

DEFINE_PUBLIC_ALIAS(GetConsoleCursorInfo, libk32_GetConsoleCursorInfo);
DEFINE_PUBLIC_ALIAS(SetConsoleCursorInfo, libk32_SetConsoleCursorInfo);
DEFINE_PUBLIC_ALIAS(GetLargestConsoleWindowSize, libk32_GetLargestConsoleWindowSize);
DEFINE_PUBLIC_ALIAS(GetConsoleScreenBufferInfo, libk32_GetConsoleScreenBufferInfo);
DEFINE_PUBLIC_ALIAS(GetConsoleScreenBufferInfoEx, libk32_GetConsoleScreenBufferInfoEx);
DEFINE_PUBLIC_ALIAS(SetConsoleScreenBufferInfoEx, libk32_SetConsoleScreenBufferInfoEx);
DEFINE_PUBLIC_ALIAS(GetNumberOfConsoleMouseButtons, libk32_GetNumberOfConsoleMouseButtons);
DEFINE_PUBLIC_ALIAS(SetConsoleActiveScreenBuffer, libk32_SetConsoleActiveScreenBuffer);
DEFINE_PUBLIC_ALIAS(FlushConsoleInputBuffer, libk32_FlushConsoleInputBuffer);
DEFINE_PUBLIC_ALIAS(SetConsoleCursorPosition, libk32_SetConsoleCursorPosition);
DEFINE_PUBLIC_ALIAS(SetConsoleTextAttribute, libk32_SetConsoleTextAttribute);
DEFINE_PUBLIC_ALIAS(SetConsoleCtrlHandler, libk32_SetConsoleCtrlHandler);
DEFINE_PUBLIC_ALIAS(GenerateConsoleCtrlEvent, libk32_GenerateConsoleCtrlEvent);
DEFINE_PUBLIC_ALIAS(SetConsoleTitleA, libk32_SetConsoleTitleA);
DEFINE_PUBLIC_ALIAS(SetConsoleTitleW, libk32_SetConsoleTitleW);
DEFINE_PUBLIC_ALIAS(ReadConsoleA, libk32_ReadConsoleA);
DEFINE_PUBLIC_ALIAS(ReadConsoleW, libk32_ReadConsoleW);
DEFINE_PUBLIC_ALIAS(WriteConsoleA, libk32_WriteConsoleA);
DEFINE_PUBLIC_ALIAS(WriteConsoleW, libk32_WriteConsoleW);
DEFINE_PUBLIC_ALIAS(GetConsoleCP, libk32_GetConsoleCP);
DEFINE_PUBLIC_ALIAS(SetConsoleCP, libk32_SetConsoleCP);
DEFINE_PUBLIC_ALIAS(GetConsoleOutputCP, libk32_GetConsoleOutputCP);
DEFINE_PUBLIC_ALIAS(SetConsoleOutputCP, libk32_SetConsoleOutputCP);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_WINCON_C */
