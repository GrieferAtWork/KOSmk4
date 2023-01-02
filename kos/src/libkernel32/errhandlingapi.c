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
#ifndef GUARD_LIBKERNEL32_ERRHANDLINGAPI_C
#define GUARD_LIBKERNEL32_ERRHANDLINGAPI_C 1

#include "api.h"
/**/

#include <kos/types.h>
#include <nt/errhandlingapi.h>

#include <errno.h>
#include <stddef.h>
#include <syslog.h>

DECL_BEGIN

/************************************************************************/
INTERN LPTOP_LEVEL_EXCEPTION_FILTER WINAPI
libk32_SetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter) {
	TRACE("SetUnhandledExceptionFilter(%p)", lpTopLevelExceptionFilter);
	syslog(LOG_WARNING, "[k32] NotImplemented: SetUnhandledExceptionFilter(%p)\n", lpTopLevelExceptionFilter);
	return NULL;
}

INTERN LONG WINAPI
libk32_UnhandledExceptionFilter(struct _EXCEPTION_POINTERS *pExceptionInfo) {
	TRACE("UnhandledExceptionFilter(%p)", pExceptionInfo);
	syslog(LOG_WARNING, "[k32] NotImplemented: UnhandledExceptionFilter(%p)\n", pExceptionInfo);
	return 0;
}

DEFINE_PUBLIC_ALIAS(SetUnhandledExceptionFilter, libk32_SetUnhandledExceptionFilter);
DEFINE_PUBLIC_ALIAS(UnhandledExceptionFilter, libk32_UnhandledExceptionFilter);


/* Special functions exported by `libc.so' */
__LIBC NOBLOCK ATTR_PURE /*nt*/ errno_t NOTHROW(LIBDCALL __get_nterrno)(void);
__LIBC NOBLOCK syscall_slong_t NOTHROW(LIBDCALL __set_nterrno)(/*nt*/ errno_t value);

INTERN DWORD WINAPI
libk32_GetLastError(VOID) {
	TRACE("GetLastError()");
	return __get_nterrno();
}

INTERN VOID WINAPI
libk32_SetLastError(DWORD dwErrCode) {
	TRACE("SetLastError(%#x)", dwErrCode);
	__set_nterrno((errno_t)dwErrCode);
}

DEFINE_PUBLIC_ALIAS(GetLastError, libk32_GetLastError);
DEFINE_PUBLIC_ALIAS(SetLastError, libk32_SetLastError);
DEFINE_PUBLIC_ALIAS(RestoreLastError, libk32_SetLastError);
/************************************************************************/




/************************************************************************/
INTERN UINT WINAPI
libk32_GetErrorMode(VOID) {
	TRACE("GetErrorMode()");
	COMPILER_IMPURE();
	return SEM_FAILCRITICALERRORS |
	       SEM_NOGPFAULTERRORBOX |
	       SEM_NOALIGNMENTFAULTEXCEPT |
	       SEM_NOOPENFILEERRORBOX;
}

INTERN UINT WINAPI
libk32_SetErrorMode(UINT uMode) {
	TRACE("SetErrorMode(%#x)", uMode);
	COMPILER_IMPURE();
	(void)uMode;
	return libk32_GetErrorMode();
}

INTERN DWORD WINAPI
libk32_GetThreadErrorMode(VOID) {
	TRACE("GetThreadErrorMode()");
	return libk32_GetErrorMode();
}

INTERN WINBOOL WINAPI
libk32_SetThreadErrorMode(DWORD dwNewMode, LPDWORD lpOldMode) {
	DWORD mode;
	TRACE("SetThreadErrorMode(%#x, %p)", dwNewMode, lpOldMode);
	mode = libk32_GetThreadErrorMode();
	if (dwNewMode != mode) {
		errno = EINVAL;
		return FALSE;
	}
	if (lpOldMode)
		*lpOldMode = mode;
	return TRUE;
}


INTERN VOID WINAPI
libk32_RaiseException(DWORD dwExceptionCode, DWORD dwExceptionFlags,
                      DWORD nNumberOfArguments, CONST ULONG_PTR *lpArguments) {
	TRACE("RaiseException(%#x, %#x, %u, %p)",
	      dwExceptionCode, dwExceptionFlags,
	      nNumberOfArguments, lpArguments);
	syslog(LOG_WARNING, "[k32] NotImplemented: RaiseException(%#x, %#x, %u, %p)\n",
	       dwExceptionCode, dwExceptionFlags,
	       nNumberOfArguments, lpArguments);
}

DEFINE_PUBLIC_ALIAS(GetErrorMode, libk32_GetErrorMode);
DEFINE_PUBLIC_ALIAS(GetThreadErrorMode, libk32_GetThreadErrorMode);
DEFINE_PUBLIC_ALIAS(SetErrorMode, libk32_SetErrorMode);
DEFINE_PUBLIC_ALIAS(SetThreadErrorMode, libk32_SetThreadErrorMode);
DEFINE_PUBLIC_ALIAS(RaiseException, libk32_RaiseException);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_ERRHANDLINGAPI_C */
