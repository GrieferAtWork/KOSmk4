/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_LIBKERNEL32_MEMORYAPI_C
#define GUARD_LIBKERNEL32_MEMORYAPI_C 1
#define _AT_SOURCE 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include "api.h"
/**/

#include <kos/types.h>
#include <nt/handleapi.h>
#include <nt/memoryapi.h>
#include <sys/mman.h>
#include <sys/uio.h>

#include <errno.h>
#include <fcntl.h>
#include <stddef.h>
#include <syslog.h>

DECL_BEGIN

/************************************************************************/
INTERN SIZE_T WINAPI
libk32_VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	TRACE("VirtualQuery(%p, %p, %#Ix)", lpAddress, lpBuffer, dwLength);
	syslog(LOG_WARNING, "[k32] NotImplemented: VirtualQuery(%p, %p, %#Ix)\n",
	       lpAddress, lpBuffer, dwLength);
	return 0;
}

PRIVATE ATTR_CONST int
NOTHROW(WINAPI libk32_MmanProtFromNtProt)(DWORD flProtect) {
	int prot;
	if (flProtect & (PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READWRITE)) {
		prot = PROT_READ | PROT_WRITE | PROT_EXEC;
	} else if (flProtect & PAGE_EXECUTE_READ) {
		prot = PROT_READ | PROT_EXEC;
	} else if (flProtect & PAGE_EXECUTE) {
		prot = PROT_EXEC;
	} else if (flProtect & (PAGE_WRITECOPY | PAGE_READWRITE)) {
		prot = PROT_READ | PROT_WRITE;
	} else if (flProtect & PAGE_READONLY) {
		prot = PROT_READ;
	} else if (flProtect & PAGE_NOACCESS) {
		prot = PROT_NONE;
	} else {
		prot = PROT_READ | PROT_WRITE; /* ??? */
	}
	return prot;
}

INTERN WINBOOL WINAPI
libk32_VirtualProtect(LPVOID lpAddress, SIZE_T dwSize,
                      DWORD flNewProtect, PDWORD lpflOldProtect) {
	int prot;
	TRACE("VirtualProtect(%p, %#Ix, %#x, %p)",
	      lpAddress, dwSize, flNewProtect, lpflOldProtect);
	prot = libk32_MmanProtFromNtProt(flNewProtect);
	*lpflOldProtect = PAGE_EXECUTE_READWRITE; /* TODO */
	return mprotect(lpAddress, dwSize, prot) == 0;
}

INTERN WINBOOL WINAPI
libk32_VirtualProtectEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize,
                        DWORD flNewProtect, PDWORD lpflOldProtect) {
	TRACE("VirtualProtectEx(%p, %p, %#Ix, %#x, %p)",
	      hProcess, lpAddress, dwSize, flNewProtect, lpflOldProtect);
	if (hProcess != NTHANDLE_FROMFD(AT_FDPROC)) {
		errno = EACCES;
		return FALSE;
	}
	return libk32_VirtualProtect(lpAddress, dwSize, flNewProtect, lpflOldProtect);
}

INTDEF DWORD WINAPI libk32_GetProcessId(HANDLE hProcess);

INTERN WINBOOL WINAPI
libk32_ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress,
                         LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead) {
	struct iovec src, dst;
	DWORD pid;
	ssize_t total;
	TRACE("ReadProcessMemory(%p, %p, %p, %#Ix, %p)",
	      hProcess, lpBaseAddress, lpBuffer,
	      nSize, lpNumberOfBytesRead);
	pid = libk32_GetProcessId(hProcess);
	if (pid == 0)
		return FALSE;
	src.iov_base = (void *)lpBaseAddress;
	src.iov_len  = nSize;
	dst.iov_base = lpBuffer;
	dst.iov_len  = nSize;
	total = process_vm_readv((pid_t)pid, &dst, 1, &src, 1, 0);
	if (total == -1)
		return FALSE;
	*lpNumberOfBytesRead = (SIZE_T)total;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress,
                          LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten) {
	struct iovec src, dst;
	DWORD pid;
	ssize_t total;
	TRACE("WriteProcessMemory(%p, %p, %p, %#Ix, %p)",
	      hProcess, lpBaseAddress, lpBuffer,
	      nSize, lpNumberOfBytesWritten);
	pid = libk32_GetProcessId(hProcess);
	if (pid == 0)
		return FALSE;
	src.iov_base = (void *)lpBuffer;
	src.iov_len  = nSize;
	dst.iov_base = lpBaseAddress;
	dst.iov_len  = nSize;
	total = process_vm_writev((pid_t)pid, &src, 1, &dst, 1, 0);
	if (total == -1)
		return FALSE;
	*lpNumberOfBytesWritten = (SIZE_T)total;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_VirtualLock(LPVOID lpAddress, SIZE_T dwSize) {
	TRACE("VirtualLock(%p, %#Ix)", lpAddress, dwSize);
	return mlock(lpAddress, dwSize) == 0;
}

INTERN WINBOOL WINAPI
libk32_VirtualUnlock(LPVOID lpAddress, SIZE_T dwSize) {
	TRACE("VirtualUnlock(%p, %#Ix)", lpAddress, dwSize);
	return munlock(lpAddress, dwSize) == 0;
}

INTERN WINBOOL WINAPI
libk32_VirtualUnlockEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize) {
	TRACE("VirtualUnlockEx(%p, %p, %#Ix)",hProcess, lpAddress, dwSize);
	if (hProcess != NTHANDLE_FROMFD(AT_FDPROC)) {
		errno = EACCES;
		return FALSE;
	}
	return libk32_VirtualUnlock(lpAddress, dwSize);
}

DEFINE_PUBLIC_ALIAS(VirtualQuery, libk32_VirtualQuery);
DEFINE_PUBLIC_ALIAS(VirtualProtect, libk32_VirtualProtect);
DEFINE_PUBLIC_ALIAS(VirtualProtectEx, libk32_VirtualProtectEx);
DEFINE_PUBLIC_ALIAS(ReadProcessMemory, libk32_ReadProcessMemory);
DEFINE_PUBLIC_ALIAS(WriteProcessMemory, libk32_WriteProcessMemory);
DEFINE_PUBLIC_ALIAS(VirtualLock, libk32_VirtualLock);
DEFINE_PUBLIC_ALIAS(VirtualUnlock, libk32_VirtualUnlock);
DEFINE_PUBLIC_ALIAS(VirtualUnlockEx, libk32_VirtualUnlockEx);
/************************************************************************/




/************************************************************************/
/* ALLOC / FREE                                                         */
/************************************************************************/
INTERN LPVOID WINAPI
libk32_VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize,
                    DWORD flAllocationType, DWORD flProtect) {
	void *result;
	int prot, flags;
	(void)flAllocationType;
	prot  = libk32_MmanProtFromNtProt(flProtect);
	flags = MAP_PRIVATE | MAP_ANON;
	if ((flAllocationType & MEM_COMMIT) && !(flAllocationType & MEM_RESERVE)) {
		/* Replace a RESERVE mapping with a COMMIT mapping
		 * -> Emulate by overwriting an exiting mapping */
		flags |= MAP_FIXED;
	}
	if (flAllocationType & MEM_LARGE_PAGES)
		flags |= MAP_HUGETLB;
	result = mmap(lpAddress, dwSize, prot, flags, -1, 0);
	if (result == MAP_FAILED)
		result = NULL;
	TRACE("VirtualAlloc(%p, %#Ix, %#x, %#x): %p",
	      lpAddress, dwSize, flAllocationType, flProtect, result);
	return result;
}

INTERN WINBOOL WINAPI
libk32_VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType) {
	TRACE("VirtualFree(%p, %#x, %#x)",
	      lpAddress, dwSize, dwFreeType);
	if (!(dwFreeType & MEM_RELEASE))
		return TRUE;
	return munmap(lpAddress, dwSize) == 0;
}

INTERN LPVOID WINAPI
libk32_VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress,
                      SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect) {
	TRACE("VirtualAllocEx(%p, %p, %#Ix, %#x, %#x)",
	      hProcess, lpAddress, dwSize, flAllocationType, flProtect);
	if (hProcess != NTHANDLE_FROMFD(AT_FDPROC)) {
		errno = EACCES;
		return NULL;
	}
	return libk32_VirtualAlloc(lpAddress, dwSize, flAllocationType, flProtect);
}

DEFINE_PUBLIC_ALIAS(VirtualAlloc, libk32_VirtualAlloc);
DEFINE_PUBLIC_ALIAS(VirtualAllocEx, libk32_VirtualAllocEx);
DEFINE_PUBLIC_ALIAS(VirtualFree, libk32_VirtualFree);
/************************************************************************/

DECL_END

#endif /* !GUARD_LIBKERNEL32_MEMORYAPI_C */
