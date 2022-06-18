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
#ifndef GUARD_LIBKERNEL32_DEBUGAPI_C
#define GUARD_LIBKERNEL32_DEBUGAPI_C 1
#define _KOS_SOURCE 1
#define _UTF_SOURCE 1

#include "api.h"
/**/

#include <asm/intrin.h>
#include <kos/types.h>
#include <nt/debugapi.h>

#include <string.h>
#include <syslog.h>
#include <uchar.h>
#include <unicode.h>
#include <wchar.h>

DECL_BEGIN

/************************************************************************/
INTERN VOID WINAPI
libk32_DebugBreak(VOID) {
	TRACE("DebugBreak()");
	__int3();
}

INTERN WINBOOL WINAPI
libk32_IsDebuggerPresent(VOID) {
	TRACE("IsDebuggerPresent()");
	COMPILER_IMPURE();
	return TRUE;
}

INTERN VOID WINAPI
libk32_OutputDebugStringA(LPCSTR lpOutputString) {
//	TRACE("OutputDebugStringA(%q)", lpOutputString);
	syslog_printer(SYSLOG_PRINTER_CLOSURE(LOG_DEBUG),
	               lpOutputString,
	               strlen(lpOutputString));
}

PRIVATE struct format_16to8_data libk32_OutputDebugStringW_printer = {
	NULL, SYSLOG_PRINTER_CLOSURE(LOG_DEBUG), 0
};
INTERN VOID WINAPI
libk32_OutputDebugStringW(LPCWSTR lpOutputString) {
//	TRACE("OutputDebugStringW(%I16q)", lpOutputString);
	if (libk32_OutputDebugStringW_printer.fd_printer == NULL)
		libk32_OutputDebugStringW_printer.fd_printer = &syslog_printer;
	format_16to8(&libk32_OutputDebugStringW_printer, lpOutputString, c16len(lpOutputString));
}

DEFINE_PUBLIC_ALIAS(DebugBreak, libk32_DebugBreak);
DEFINE_PUBLIC_ALIAS(IsDebuggerPresent, libk32_IsDebuggerPresent);
DEFINE_PUBLIC_ALIAS(OutputDebugStringA, libk32_OutputDebugStringA);
DEFINE_PUBLIC_ALIAS(OutputDebugStringW, libk32_OutputDebugStringW);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_DEBUGAPI_C */
