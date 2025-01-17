/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBKERNEL32_HANDLEAPI_C
#define GUARD_LIBKERNEL32_HANDLEAPI_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _KOS_KERNEL_SOURCE 1

#include "api.h"

#include <kos/syscalls.h>
#include <kos/types.h>
#include <linux/kcmp.h>
#include <nt/handleapi.h>

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

DECL_BEGIN

/************************************************************************/
INTERN WINBOOL WINAPI
libk32_CloseHandle(HANDLE hObject) {
	TRACE("CloseHandle(%p)", hObject);
	if (!NTHANDLE_ISFD(hObject)) {
		/* XXX: decref() a user-space wrapper object? */
		errno = EBADF;
		return FALSE;
	}
	return close(NTHANDLE_ASFD(hObject)) == 0;
}

INTERN WINBOOL WINAPI
libk32_DuplicateHandle(HANDLE hSourceProcessHandle, HANDLE hSourceHandle,
                       HANDLE hTargetProcessHandle, LPHANDLE lpTargetHandle,
                       DWORD dwDesiredAccess, WINBOOL bInheritHandle, DWORD dwOptions) {
	fd_t newfd;
	TRACE("DuplicateHandle(%p, %p, %p, %p, %#x, %u, %#x)",
	      hSourceProcessHandle, hSourceHandle,
	      hTargetProcessHandle, lpTargetHandle,
	      dwDesiredAccess, bInheritHandle, dwOptions);
	if (hTargetProcessHandle != NTHANDLE_FROMFD(AT_FDPROC)) {
		errno = EACCES;
		return FALSE;
	}
	if (hSourceProcessHandle != NTHANDLE_FROMFD(AT_FDPROC)) {
		/* TODO: This can be done via `open("/proc/[pid]/fd/[fdno]")' */
		errno = ENOTSUP;
		return FALSE;
	}
	(void)dwDesiredAccess;
	(void)dwOptions;
	if (!NTHANDLE_ISFD(hSourceHandle)) {
		/* XXX: incref() a user-space wrapper object? */
		errno = EBADF;
		return FALSE;
	}
	newfd = bInheritHandle
	        ? dup(NTHANDLE_ASFD(hSourceHandle)) /* NOLINT */
	        : fcntl(NTHANDLE_ASFD(hSourceHandle), F_DUPFD_CLOEXEC);
	if (newfd == -1)
		return FALSE;
	*lpTargetHandle = NTHANDLE_FROMFD(newfd);
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_CompareObjectHandles(HANDLE hFirstObjectHandle, HANDLE hSecondObjectHandle) {
	errno_t error;
	pid_t pid;
	TRACE("CompareObjectHandles(%p, %p)",
	      hFirstObjectHandle, hSecondObjectHandle);
	if (hFirstObjectHandle == hSecondObjectHandle)
		return TRUE;
	if (!NTHANDLE_ISFD(hFirstObjectHandle) ||
	    !NTHANDLE_ISFD(hSecondObjectHandle))
		return FALSE;
	pid   = gettid();
	error = sys_kcmp(pid, pid, KCMP_FILES,
	                 NTHANDLE_ASFD(hFirstObjectHandle),
	                 NTHANDLE_ASFD(hSecondObjectHandle));
	if (E_ISERR(error)) {
		errno = -error;
		return FALSE;
	}
	return error == 0; /* 0: KCMP_ORDER_EQUAL */
}

INTERN WINBOOL WINAPI
libk32_GetHandleInformation(HANDLE hObject, LPDWORD lpdwFlags) {
	int flags;
	TRACE("GetHandleInformation(%p, %p)", hObject, lpdwFlags);
	if (!NTHANDLE_ISFD(hObject)) {
		*lpdwFlags = 0;
		return TRUE;
	}
	flags = fcntl(NTHANDLE_ASFD(hObject), F_GETFD);
	if (flags == -1)
		return FALSE;
	*lpdwFlags = flags & FD_CLOEXEC ? 0 : HANDLE_FLAG_INHERIT;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_SetHandleInformation(HANDLE hObject, DWORD dwMask, DWORD dwFlags) {
	int flags, new_flags;
	TRACE("SetHandleInformation(%p, %#x, %#x)", hObject, dwMask, dwFlags);
	if (!(dwMask & HANDLE_FLAG_INHERIT))
		return TRUE;
	if (!NTHANDLE_ISFD(hObject)) {
		if (!(dwFlags & HANDLE_FLAG_INHERIT))
			return TRUE;
		errno = ENOTSUP;
		return FALSE;
	}
	flags = fcntl(NTHANDLE_ASFD(hObject), F_GETFD);
	if (flags == -1)
		return FALSE;
	new_flags = flags & ~FD_CLOEXEC;
	if (!(dwFlags & HANDLE_FLAG_INHERIT))
		new_flags |= FD_CLOEXEC;
	if (flags == new_flags)
		return TRUE;
	return fcntl(NTHANDLE_ASFD(hObject), F_SETFD, new_flags) == 0;
}

DEFINE_PUBLIC_ALIAS(CloseHandle, libk32_CloseHandle);
DEFINE_PUBLIC_ALIAS(DuplicateHandle, libk32_DuplicateHandle);
DEFINE_PUBLIC_ALIAS(CompareObjectHandles, libk32_CompareObjectHandles);
DEFINE_PUBLIC_ALIAS(GetHandleInformation, libk32_GetHandleInformation);
DEFINE_PUBLIC_ALIAS(SetHandleInformation, libk32_SetHandleInformation);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_HANDLEAPI_C */
