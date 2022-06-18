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
#ifndef GUARD_LIBKERNEL32_PROCESSENV_C
#define GUARD_LIBKERNEL32_PROCESSENV_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _UTF_SOURCE 1

#include "api.h"
/**/

#include <kos/types.h>
#include <nt/handleapi.h>
#include <nt/processenv.h>

#include <errno.h>
#include <fcntl.h>
#include <format-printer.h>
#include <malloc.h>
#include <stddef.h>
#include <string.h>
#include <uchar.h>
#include <unistd.h>
#include <wchar.h>

DECL_BEGIN

/************************************************************************/
/* GetCurrentDirectory() / SetCurrentDirectory()                        */
/************************************************************************/
__LIBC int LIBDCALL DOS$chdir(char const *dir);
__LIBC int LIBDCALL DOS$_wchdir(char16_t const *dir);
__LIBC char *LIBDCALL DOS$_getcwd(char *buf, size_t bufsize);
__LIBC char16_t *LIBDCALL DOS$_wgetcwd(char16_t *buf, size_t bufsize);

INTERN WINBOOL WINAPI
libk32_SetCurrentDirectoryA(LPCSTR lpPathName) {
	TRACE("SetCurrentDirectoryA(%q)", lpPathName);
	return DOS$chdir(lpPathName) == 0;
}

INTERN WINBOOL WINAPI
libk32_SetCurrentDirectoryW(LPCWSTR lpPathName) {
	TRACE("SetCurrentDirectoryW(%I16q)", lpPathName);
	return DOS$_wchdir(lpPathName) == 0;
}

INTERN DWORD WINAPI
libk32_GetCurrentDirectoryA(DWORD nBufferLength, LPSTR lpBuffer) {
	char *wd = DOS$_getcwd(NULL, 0);
	size_t len;
	TRACE("GetCurrentDirectoryA(%#x, %p): %q", nBufferLength, lpBuffer, wd);
	if (!wd)
		return 0;
	len = strlen(wd) + 1;
	if (nBufferLength >= len) {
		memcpy(lpBuffer, wd, len, sizeof(CHAR));
		--len;
	}
	free(wd);
	return len;
}

INTERN DWORD WINAPI
libk32_GetCurrentDirectoryW(DWORD nBufferLength, LPWSTR lpBuffer) {
	char16_t *wd = DOS$_wgetcwd(NULL, 0);
	size_t len;
	TRACE("GetCurrentDirectoryW(%#x, %p): %I16q", nBufferLength, lpBuffer, wd);
	if (!wd)
		return 0;
	len = c16len(wd) + 1;
	if (nBufferLength >= len) {
		memcpy(lpBuffer, wd, len, sizeof(WCHAR));
		--len;
	}
	free(wd);
	return len;
}

DEFINE_PUBLIC_ALIAS(SetCurrentDirectoryA, libk32_SetCurrentDirectoryA);
DEFINE_PUBLIC_ALIAS(SetCurrentDirectoryW, libk32_SetCurrentDirectoryW);
DEFINE_PUBLIC_ALIAS(GetCurrentDirectoryA, libk32_GetCurrentDirectoryA);
DEFINE_PUBLIC_ALIAS(GetCurrentDirectoryW, libk32_GetCurrentDirectoryW);
/************************************************************************/



/************************************************************************/
/* GetStdHandle() / SetStdHandle()                                      */
/************************************************************************/
INTERN HANDLE WINAPI
libk32_GetStdHandle(DWORD nStdHandle) {
	TRACE("GetStdHandle(%#x)", nStdHandle);
	switch (nStdHandle) {
	case STD_INPUT_HANDLE:
		return NTHANDLE_FROMFD(STDIN_FILENO);
	case STD_OUTPUT_HANDLE:
		return NTHANDLE_FROMFD(STDOUT_FILENO);
	case STD_ERROR_HANDLE:
		return NTHANDLE_FROMFD(STDERR_FILENO);
	default:
		break;
	}
	return INVALID_HANDLE_VALUE;
}

INTERN WINBOOL WINAPI
libk32_SetStdHandleEx(DWORD nStdHandle, HANDLE hHandle, PHANDLE phPrevValue) {
	fd_t fd;
	TRACE("SetStdHandleEx(%#x, %p, %p)",
	      nStdHandle, hHandle, phPrevValue);
	if (!NTHANDLE_ISFD(hHandle)) {
		errno = EBADF;
		return FALSE;
	}
	switch (nStdHandle) {
	case STD_INPUT_HANDLE:
		fd = STDIN_FILENO;
		break;
	case STD_OUTPUT_HANDLE:
		fd = STDOUT_FILENO;
		break;
	case STD_ERROR_HANDLE:
		fd = STDERR_FILENO;
		break;
	default:
		errno = EINVAL;
		return FALSE;
	}
	if (phPrevValue) {
		int result;
		fd_t d = fcntl(fd, F_DUPFD_CLOEXEC);
		if (d == -1)
			return FALSE;
		result = dup2(NTHANDLE_ASFD(hHandle), fd);
		if (result < 0) {
			close(d);
			return FALSE;
		}
		*phPrevValue = NTHANDLE_FROMFD(d);
		return TRUE;
	}
	return dup2(NTHANDLE_ASFD(hHandle), fd) == 0;
}

INTERN WINBOOL WINAPI
libk32_SetStdHandle(DWORD nStdHandle, HANDLE hHandle) {
	TRACE("SetStdHandle(%#x, %p)", nStdHandle, hHandle);
	return libk32_SetStdHandleEx(nStdHandle, hHandle, NULL);
}

DEFINE_PUBLIC_ALIAS(GetStdHandle, libk32_GetStdHandle);
DEFINE_PUBLIC_ALIAS(SetStdHandle, libk32_SetStdHandle);
DEFINE_PUBLIC_ALIAS(SetStdHandleEx, libk32_SetStdHandleEx);
/************************************************************************/





/************************************************************************/
/* GetCommandLine()                                                     */
/************************************************************************/
__LIBC char **LIBDCALL DOS$__p__acmdln(void);
__LIBC char16_t **LIBDCALL DOS$__p__wcmdln(void);

INTERN LPSTR WINAPI libk32_GetCommandLineA(VOID) {
	TRACE("GetCommandLineA()");
	return *DOS$__p__acmdln();
}

INTERN LPWSTR WINAPI libk32_GetCommandLineW(VOID) {
	TRACE("GetCommandLineW()");
	return *DOS$__p__wcmdln();
}

DEFINE_PUBLIC_ALIAS(GetCommandLineA, libk32_GetCommandLineA);
DEFINE_PUBLIC_ALIAS(GetCommandLineW, libk32_GetCommandLineW);
/************************************************************************/





/************************************************************************/
/* ENVIRON                                                              */
/************************************************************************/

/* Let libc deal  with converting  stuff like  `$PATH'
 * from "/bin:/usr/bin" to "C:\bin;C:\usr\bin", etc... */
__LIBC char ***LIBDCALL DOS$__p__environ(void);
__LIBC char *LIBDCALL DOS$getenv(char const *name);
__LIBC int LIBDCALL DOS$setenv(char const *varname, char const *val, int replace);

PRIVATE ATTR_MALLOC LPCH WINAPI
libk32_GetEnvironmentStringsImpl(size_t *plen) {
	struct format_aprintf_data dat;
	char **env = *DOS$__p__environ();
	size_t i;
	format_aprintf_data_init(&dat);
	if (env) {
		for (i = 0; env[i]; ++i) {
			char *line = env[i];
			if (format_aprintf_printer(&dat, line, strlen(line) + 1) < 0)
				goto err;
		}
	}
	if (format_aprintf_printer(&dat, "\0", 1) < 0)
		goto err;
	return format_aprintf_pack(&dat, plen);
err:
	format_aprintf_data_fini(&dat);
	return NULL;
}

INTERN ATTR_MALLOC LPCH WINAPI
libk32_GetEnvironmentStrings(VOID) {
	TRACE("GetEnvironmentStrings()");
	return libk32_GetEnvironmentStringsImpl(NULL);
}

INTERN ATTR_MALLOC LPWCH WINAPI
libk32_GetEnvironmentStringsW(VOID) {
	LPWCH result;
	size_t len;
	LPCH str;
	TRACE("GetEnvironmentStringsW()");
	str = libk32_GetEnvironmentStringsImpl(&len);
	if (!str)
		return NULL;
	result = convert_mbstoc16n(str, len, NULL);
	free(str);
	return result;
}

INTERN WINBOOL WINAPI
libk32_FreeEnvironmentStringsA(LPCH penv) {
	TRACE("FreeEnvironmentStringsA()");
	free(penv);
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_FreeEnvironmentStringsW(LPWCH penv) {
	TRACE("FreeEnvironmentStringsW()");
	free(penv);
	return TRUE;
}

INTERN DWORD WINAPI
libk32_GetEnvironmentVariableA(LPCSTR lpName, LPSTR lpBuffer, DWORD nSize) {
	size_t len;
	char *value = DOS$getenv(lpName);
	TRACE("GetEnvironmentVariableA(%q, %p, %#x): %q", lpName, lpBuffer, nSize, value);
	if (!value) {
		_nterrno = ERROR_ENVVAR_NOT_FOUND;
		return 0;
	}
	len = strlen(value) + 1;
	if (nSize >= len) {
		memcpy(lpBuffer, value, len, sizeof(CHAR));
		--len;
	}
	return len;
}

INTERN DWORD WINAPI
libk32_GetEnvironmentVariableW(LPCWSTR lpName, LPWSTR lpBuffer, DWORD nSize) {
	size_t len;
	char *utf8_name = convert_c16tombs(lpName);
	char *utf8_value;
	char16_t *value;
	if (!utf8_name) {
		TRACE("GetEnvironmentVariableW(%I16q, %p, %#x): %q", lpName, lpBuffer, nSize, (char *)NULL);
		return 0;
	}
	utf8_value = DOS$getenv(utf8_name);
	free(utf8_name);
	TRACE("GetEnvironmentVariableW(%I16q, %p, %#x): %q", lpName, lpBuffer, nSize, utf8_value);
	if (!utf8_value) {
		_nterrno = ERROR_ENVVAR_NOT_FOUND;
		return 0;
	}
	value = convert_mbstoc16(utf8_value);
	if (!value)
		return 0;
	len = c16len(value) + 1;
	if (nSize >= len) {
		memcpy(lpBuffer, value, len, sizeof(WCHAR));
		--len;
	}
	free(value);
	return len;
}

INTERN WINBOOL WINAPI
libk32_SetEnvironmentVariableA(LPCSTR lpName, LPCSTR lpValue) {
	TRACE("SetEnvironmentVariableA(%q, %q)", lpName, lpValue);
	return DOS$setenv(lpName, lpValue, 1) == 0;
}

INTERN WINBOOL WINAPI
libk32_SetEnvironmentVariableW(LPCWSTR lpName, LPCWSTR lpValue) {
	int result;
	char *name, *value;
	TRACE("SetEnvironmentVariableW(%I16q, %I16q)", lpName, lpValue);
	name = convert_c16tombs(lpName);
	if (!name)
		return FALSE;
	value = convert_c16tombs(lpValue);
	if (!value) {
		free(name);
		return FALSE;
	}
	result = DOS$setenv(name, value, 1);
	free(value);
	free(name);
	return result;
}

INTERN ATTR_MALLOC char *WINAPI
libk32_ExpandEnvironmentStringsAImpl(LPCSTR lpSrc) {
	struct format_aprintf_data dat;
	LPCSTR flush_start = lpSrc;
	format_aprintf_data_init(&dat);
	for (;;) {
		char *repl;
		LPSTR envname;
		LPCSTR tokend;
		CHAR ch = *lpSrc;
		if (ch == '\0')
			break;
		if (ch != '%') {
			++lpSrc;
			continue;
		}
		if (format_aprintf_printer(&dat, flush_start, (size_t)(lpSrc - flush_start)) < 0)
			goto err;
		++lpSrc;
		tokend = strchr(lpSrc, '%');
		if (!tokend) {
			errno = EINVAL;
			goto err;
		}
		envname = strndup(lpSrc, (size_t)(tokend - lpSrc));
		if (!envname)
			goto err;
		repl = DOS$getenv(envname);
		free(envname);
		if (repl) {
			if (format_aprintf_printer(&dat, repl, strlen(repl)) < 0)
				goto err;
		}
		flush_start = lpSrc = tokend + 1;
	}
	if (format_aprintf_printer(&dat, flush_start, (size_t)(lpSrc - flush_start)) < 0)
		goto err;
	return format_aprintf_pack(&dat, NULL);
err:
	format_aprintf_data_fini(&dat);
	return NULL;
}

INTERN DWORD WINAPI
libk32_ExpandEnvironmentStringsA(LPCSTR lpSrc, LPSTR lpDst, DWORD nSize) {
	size_t len;
	char *str;
	str = libk32_ExpandEnvironmentStringsAImpl(lpSrc);
	TRACE("ExpandEnvironmentStringsA(%q, %p, %#x): %q", lpSrc, lpDst, nSize, str);
	if (!str)
		return 0;
	len = strlen(str) + 1;
	if (nSize >= len)
		memcpy(lpDst, str, len, sizeof(CHAR));
	free(str);
	return len;
}

INTERN DWORD WINAPI
libk32_ExpandEnvironmentStringsW(LPCWSTR lpSrc, LPWSTR lpDst, DWORD nSize) {
	size_t len;
	char16_t *str;
	char *utf8_str = NULL;
	char *utf8_src = convert_c16tombs(lpSrc);
	if likely(utf8_src) {
		utf8_str = libk32_ExpandEnvironmentStringsAImpl(utf8_src);
		free(utf8_src);
	}
	TRACE("ExpandEnvironmentStringsW(%I16q, %p, %#x): %q", lpSrc, lpDst, nSize, utf8_str);
	if (!utf8_str)
		return 0;
	str = convert_mbstoc16(utf8_str);
	free(utf8_str);
	if (!str)
		return 0;
	len = c16len(str) + 1;
	if (nSize >= len)
		memcpy(lpDst, str, len, sizeof(WCHAR));
	free(str);
	return len;
}

DEFINE_PUBLIC_ALIAS(GetEnvironmentStrings, libk32_GetEnvironmentStrings);
DEFINE_PUBLIC_ALIAS(GetEnvironmentStringsW, libk32_GetEnvironmentStringsW);
DEFINE_PUBLIC_ALIAS(FreeEnvironmentStringsA, libk32_FreeEnvironmentStringsA);
DEFINE_PUBLIC_ALIAS(FreeEnvironmentStringsW, libk32_FreeEnvironmentStringsW);
DEFINE_PUBLIC_ALIAS(GetEnvironmentVariableA, libk32_GetEnvironmentVariableA);
DEFINE_PUBLIC_ALIAS(GetEnvironmentVariableW, libk32_GetEnvironmentVariableW);
DEFINE_PUBLIC_ALIAS(SetEnvironmentVariableA, libk32_SetEnvironmentVariableA);
DEFINE_PUBLIC_ALIAS(SetEnvironmentVariableW, libk32_SetEnvironmentVariableW);
DEFINE_PUBLIC_ALIAS(ExpandEnvironmentStringsA, libk32_ExpandEnvironmentStringsA);
DEFINE_PUBLIC_ALIAS(ExpandEnvironmentStringsW, libk32_ExpandEnvironmentStringsW);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_PROCESSENV_C */
