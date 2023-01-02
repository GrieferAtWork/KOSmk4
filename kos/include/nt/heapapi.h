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
#ifndef _NT_HEAPAPI_H
#define _NT_HEAPAPI_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#ifdef __CC__
__DECL_BEGIN

typedef struct _HEAP_SUMMARY {
	DWORD cb;
	SIZE_T cbAllocated;
	SIZE_T cbCommitted;
	SIZE_T cbReserved;
	SIZE_T cbMaxReserve;
} HEAP_SUMMARY, *PHEAP_SUMMARY, *LPHEAP_SUMMARY;

#define HEAP_NO_SERIALIZE             0x00000001
#define HEAP_GROWABLE                 0x00000002
#define HEAP_GENERATE_EXCEPTIONS      0x00000004
#define HEAP_ZERO_MEMORY              0x00000008
#define HEAP_REALLOC_IN_PLACE_ONLY    0x00000010
#define HEAP_TAIL_CHECKING_ENABLED    0x00000020
#define HEAP_FREE_CHECKING_ENABLED    0x00000040
#define HEAP_DISABLE_COALESCE_ON_FREE 0x00000080
#define HEAP_CREATE_ALIGN_16          0x00010000
#define HEAP_CREATE_ENABLE_TRACING    0x00020000
#define HEAP_CREATE_ENABLE_EXECUTE    0x00040000
#define HEAP_MAXIMUM_TAG              0x0FFF
#define HEAP_PSEUDO_TAG_FLAG          0x8000
#define HEAP_TAG_SHIFT                18

WINBASEAPI WINBOOL WINAPI HeapValidate(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem);
WINBASEAPI WINBOOL WINAPI HeapSummary(HANDLE hHeap, DWORD dwFlags, LPHEAP_SUMMARY lpSummary);
WINBASEAPI DWORD WINAPI GetProcessHeaps(DWORD NumberOfHeaps, PHANDLE ProcessHeaps);
WINBASEAPI WINBOOL WINAPI HeapLock(HANDLE hHeap);
WINBASEAPI WINBOOL WINAPI HeapUnlock(HANDLE hHeap);
WINBASEAPI HANDLE WINAPI HeapCreate(DWORD flOptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize);
WINBASEAPI SIZE_T WINAPI HeapCompact(HANDLE hHeap, DWORD dwFlags);
WINBASEAPI WINBOOL WINAPI HeapDestroy(HANDLE hHeap);
WINBASEAPI LPVOID WINAPI HeapAlloc(HANDLE hHeap, DWORD dwFlags, SIZE_T dwBytes);
WINBASEAPI LPVOID WINAPI HeapReAlloc(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem, SIZE_T dwBytes);
WINBASEAPI WINBOOL WINAPI HeapFree(HANDLE hHeap, DWORD dwFlags, LPVOID lpMem);
WINBASEAPI SIZE_T WINAPI HeapSize(HANDLE hHeap, DWORD dwFlags, LPCVOID lpMem);
WINBASEAPI HANDLE WINAPI GetProcessHeap(VOID);


#define LMEM_FIXED          0x0000
#define LMEM_MOVEABLE       0x0002
#define LMEM_NOCOMPACT      0x0010
#define LMEM_NODISCARD      0x0020
#define LMEM_ZEROINIT       0x0040
#define LMEM_MODIFY         0x0080
#define LMEM_DISCARDABLE    0x0f00
#define LMEM_VALID_FLAGS    0x0f72
#define LMEM_INVALID_HANDLE 0x8000
#define LHND                (LMEM_MOVEABLE | LMEM_ZEROINIT)
#define LPTR                (LMEM_FIXED | LMEM_ZEROINIT)
#define NONZEROLHND         (LMEM_MOVEABLE)
#define NONZEROLPTR         (LMEM_FIXED)

WINBASEAPI HLOCAL WINAPI LocalAlloc(UINT uFlags, SIZE_T uBytes);
WINBASEAPI HLOCAL WINAPI LocalReAlloc(HLOCAL hMem, SIZE_T uBytes, UINT uFlags);
WINBASEAPI SIZE_T WINAPI LocalShrink(HLOCAL hMem, UINT cbNewSize);
WINBASEAPI HLOCAL WINAPI LocalFree(HLOCAL hMem);
WINBASEAPI HLOCAL WINAPI LocalHandle(LPCVOID pMem);
WINBASEAPI LPVOID WINAPI LocalLock(HLOCAL hMem);
WINBASEAPI WINBOOL WINAPI LocalUnlock(HLOCAL hMem);
WINBASEAPI SIZE_T WINAPI LocalSize(HLOCAL hMem);

WINBASEAPI HGLOBAL WINAPI GlobalAlloc(UINT uFlags, SIZE_T dwBytes);
WINBASEAPI HGLOBAL WINAPI GlobalReAlloc(HGLOBAL hMem, SIZE_T dwBytes, UINT uFlags);
WINBASEAPI HGLOBAL WINAPI GlobalFree(HGLOBAL hMem);
WINBASEAPI HGLOBAL WINAPI GlobalHandle(LPCVOID pMem);
WINBASEAPI LPVOID WINAPI GlobalLock(HGLOBAL hMem);
WINBASEAPI WINBOOL WINAPI GlobalUnlock(HGLOBAL hMem);
WINBASEAPI SIZE_T WINAPI GlobalSize(HGLOBAL hMem);


__DECL_END
#endif /* __CC__ */

#endif /* !_NT_HEAPAPI_H */
