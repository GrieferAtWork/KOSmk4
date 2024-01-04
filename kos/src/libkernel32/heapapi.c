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
#ifndef GUARD_LIBKERNEL32_HEAPAPI_C
#define GUARD_LIBKERNEL32_HEAPAPI_C 1
#define _TIME64_SOURCE 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <kos/except.h>
#include <kos/malloc.h>
#include <kos/types.h>
#include <nt/heapapi.h>

#include <errno.h>
#include <malloc.h>
#include <string.h>

DECL_BEGIN

/************************************************************************/
struct ntheap {
	int placeholder;
};

static struct ntheap procheap = { 0 };

INTERN WINBOOL WINAPI
libk32_HeapValidate(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem) {
	COMPILER_IMPURE();
	(void)hHeap;
	(void)dwFlags;
	(void)lpMem;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_HeapSummary(HANDLE hHeap, DWORD dwFlags, LPHEAP_SUMMARY lpSummary) {
	(void)hHeap;
	(void)dwFlags;
	if (lpSummary->cb != sizeof(*lpSummary)) {
		errno = EINVAL;
		return FALSE;
	}
	/* ??? */
	lpSummary->cbAllocated  = 0x11000;
	lpSummary->cbCommitted  = 0x22000;
	lpSummary->cbReserved   = 0x01000;
	lpSummary->cbMaxReserve = 0x02000;
	return TRUE;
}

INTERN DWORD WINAPI
libk32_GetProcessHeaps(DWORD NumberOfHeaps, PHANDLE ProcessHeaps) {
	if (NumberOfHeaps >= 1)
		ProcessHeaps[0] = &procheap;
	return 1;
}

INTERN WINBOOL WINAPI
libk32_HeapLock(HANDLE hHeap) {
	COMPILER_IMPURE();
	(void)hHeap;
	return TRUE;
}

INTERN WINBOOL WINAPI
libk32_HeapUnlock(HANDLE hHeap) {
	COMPILER_IMPURE();
	(void)hHeap;
	return TRUE;
}

INTERN ATTR_MALLOC HANDLE WINAPI
libk32_HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) {
	struct ntheap *heap;
	heap = (struct ntheap *)malloc(sizeof(struct ntheap));
	(void)flOptions;
	(void)dwInitialSize;
	(void)dwMaximumSize;
	return heap;
}

INTERN SIZE_T WINAPI
libk32_HeapCompact(HANDLE hHeap, DWORD dwFlags) {
	COMPILER_IMPURE();
	(void)hHeap;
	(void)dwFlags;
	return 0;
}

INTERN WINBOOL WINAPI
libk32_HeapDestroy(HANDLE hHeap) {
	if (!hHeap) {
		errno = EBADF;
		return FALSE;
	}
	if (hHeap == &procheap) {
		errno = EINVAL;
		return FALSE;
	}
	free(hHeap);
	return TRUE;
}

INTERN LPVOID WINAPI
libk32_HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes) {
	void *result;
	(void)hHeap;
	if (dwFlags & HEAP_GENERATE_EXCEPTIONS) {
		if (dwFlags & HEAP_ZERO_MEMORY) {
			result = Calloc(1, dwBytes);
		} else {
			result = Malloc(dwBytes);
		}
	} else {
		if (dwFlags & HEAP_ZERO_MEMORY) {
			result = calloc(dwBytes);
		} else {
			result = malloc(dwBytes);
		}
	}
	if (result && !(dwFlags & HEAP_ZERO_MEMORY)) {
		size_t sz = malloc_usable_size(result);
		bzero((byte_t *)result + dwBytes, sz - dwBytes);
	}
	return result;
}

INTERN LPVOID WINAPI
libk32_HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes) {
	void *result;
	(void)hHeap;
	if (dwFlags & HEAP_GENERATE_EXCEPTIONS) {
		if (dwFlags & HEAP_ZERO_MEMORY) {
			result = recalloc(lpMem, dwBytes); /* XXX: Recalloc? */
			if unlikely(!result)
				THROW(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY, dwBytes);
		} else {
			result = Realloc(lpMem, dwBytes);
		}
	} else {
		if (dwFlags & HEAP_ZERO_MEMORY) {
			result = recalloc(lpMem, dwBytes);
		} else {
			result = realloc(lpMem, dwBytes);
		}
	}
	if (result && !(dwFlags & HEAP_ZERO_MEMORY)) {
		size_t sz = malloc_usable_size(result);
		bzero((byte_t *)result + dwBytes, sz - dwBytes);
	}
	return result;
}

INTERN WINBOOL WINAPI
libk32_HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem) {
	(void)dwFlags;
	(void)hHeap;
	free(lpMem);
	return TRUE;
}

INTERN ATTR_PURE SIZE_T WINAPI
libk32_HeapSize(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem) {
	(void)dwFlags;
	(void)hHeap;
	return malloc_usable_size((void *)lpMem);
}

INTERN HANDLE WINAPI
libk32_GetProcessHeap(VOID) {
	COMPILER_IMPURE();
	return &procheap;
}

DEFINE_PUBLIC_ALIAS(HeapValidate, libk32_HeapValidate);
DEFINE_PUBLIC_ALIAS(HeapSummary, libk32_HeapSummary);
DEFINE_PUBLIC_ALIAS(GetProcessHeaps, libk32_GetProcessHeaps);
DEFINE_PUBLIC_ALIAS(HeapLock, libk32_HeapLock);
DEFINE_PUBLIC_ALIAS(HeapUnlock, libk32_HeapUnlock);
DEFINE_PUBLIC_ALIAS(HeapCreate, libk32_HeapCreate);
DEFINE_PUBLIC_ALIAS(HeapCompact, libk32_HeapCompact);
DEFINE_PUBLIC_ALIAS(HeapDestroy, libk32_HeapDestroy);
DEFINE_PUBLIC_ALIAS(HeapAlloc, libk32_HeapAlloc);
DEFINE_PUBLIC_ALIAS(HeapReAlloc, libk32_HeapReAlloc);
DEFINE_PUBLIC_ALIAS(HeapFree, libk32_HeapFree);
DEFINE_PUBLIC_ALIAS(HeapSize, libk32_HeapSize);
DEFINE_PUBLIC_ALIAS(GetProcessHeap, libk32_GetProcessHeap);
/************************************************************************/






/************************************************************************/
INTERN ATTR_MALLOC HLOCAL WINAPI
libk32_LocalAlloc(UINT uFlags, SIZE_T uBytes) {
	void *result;
	result = (uFlags & LMEM_ZEROINIT) ? calloc(uBytes)
	                                  : malloc(uBytes);
	return result;
}

INTERN HLOCAL WINAPI
libk32_LocalReAlloc(HLOCAL hMem, SIZE_T uBytes, UINT uFlags) {
	void *result;
	result = (uFlags & LMEM_ZEROINIT) ? recalloc(hMem, uBytes)
	                                  : realloc(hMem, uBytes);
	return result;
}

INTERN SIZE_T WINAPI
libk32_LocalShrink(HLOCAL hMem, UINT cbNewSize) {
	size_t oldsz = malloc_usable_size(hMem);
	if (cbNewSize < oldsz) {
		realloc_in_place(hMem, cbNewSize);
		oldsz = malloc_usable_size(hMem);
	}
	return oldsz;
}

INTERN HLOCAL WINAPI
libk32_LocalFree(HLOCAL hMem) {
	free(hMem);
	return NULL;
}

INTERN HLOCAL WINAPI
libk32_LocalHandle(LPCVOID pMem) {
	COMPILER_IMPURE();
	return (HLOCAL)pMem;
}

INTERN LPVOID WINAPI
libk32_LocalLock(HLOCAL hMem) {
	COMPILER_IMPURE();
	return hMem;
}

INTERN WINBOOL WINAPI
libk32_LocalUnlock(HLOCAL hMem) {
	COMPILER_IMPURE();
	(void)hMem;
	return TRUE;
}

INTERN ATTR_PURE SIZE_T WINAPI
libk32_LocalSize(HLOCAL hMem) {
	return malloc_usable_size(hMem);
}

DEFINE_INTERN_ALIAS(libk32_GlobalAlloc, libk32_LocalAlloc);
DEFINE_INTERN_ALIAS(libk32_GlobalReAlloc, libk32_LocalReAlloc);
DEFINE_INTERN_ALIAS(libk32_GlobalFree, libk32_LocalFree);
DEFINE_INTERN_ALIAS(libk32_GlobalHandle, libk32_LocalHandle);
DEFINE_INTERN_ALIAS(libk32_GlobalLock, libk32_LocalLock);
DEFINE_INTERN_ALIAS(libk32_GlobalUnlock, libk32_LocalUnlock);
DEFINE_INTERN_ALIAS(libk32_GlobalSize, libk32_LocalSize);

DEFINE_PUBLIC_ALIAS(LocalAlloc, libk32_LocalAlloc);
DEFINE_PUBLIC_ALIAS(LocalReAlloc, libk32_LocalReAlloc);
DEFINE_PUBLIC_ALIAS(LocalShrink, libk32_LocalShrink);
DEFINE_PUBLIC_ALIAS(LocalFree, libk32_LocalFree);
DEFINE_PUBLIC_ALIAS(LocalHandle, libk32_LocalHandle);
DEFINE_PUBLIC_ALIAS(LocalLock, libk32_LocalLock);
DEFINE_PUBLIC_ALIAS(LocalUnlock, libk32_LocalUnlock);
DEFINE_PUBLIC_ALIAS(LocalSize, libk32_LocalSize);
DEFINE_PUBLIC_ALIAS(GlobalAlloc, libk32_GlobalAlloc);
DEFINE_PUBLIC_ALIAS(GlobalReAlloc, libk32_GlobalReAlloc);
DEFINE_PUBLIC_ALIAS(GlobalFree, libk32_GlobalFree);
DEFINE_PUBLIC_ALIAS(GlobalHandle, libk32_GlobalHandle);
DEFINE_PUBLIC_ALIAS(GlobalLock, libk32_GlobalLock);
DEFINE_PUBLIC_ALIAS(GlobalUnlock, libk32_GlobalUnlock);
DEFINE_PUBLIC_ALIAS(GlobalSize, libk32_GlobalSize);
/************************************************************************/


DECL_END

#endif /* !GUARD_LIBKERNEL32_HEAPAPI_C */
