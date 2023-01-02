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
#ifndef _NT_MEMORYAPI_H
#define _NT_MEMORYAPI_H 1

#include "__stdinc.h"
/**/

#include "types.h"
/**/

#ifdef __CC__
__DECL_BEGIN

#define PAGE_NOACCESS                   0x00000001
#define PAGE_READONLY                   0x00000002
#define PAGE_READWRITE                  0x00000004
#define PAGE_WRITECOPY                  0x00000008
#define PAGE_EXECUTE                    0x00000010
#define PAGE_EXECUTE_READ               0x00000020
#define PAGE_EXECUTE_READWRITE          0x00000040
#define PAGE_EXECUTE_WRITECOPY          0x00000080
#define PAGE_GUARD                      0x00000100
#define PAGE_NOCACHE                    0x00000200
#define PAGE_WRITECOMBINE               0x00000400
#define PAGE_GRAPHICS_NOACCESS          0x00000800
#define PAGE_GRAPHICS_READONLY          0x00001000
#define PAGE_GRAPHICS_READWRITE         0x00002000
#define PAGE_GRAPHICS_EXECUTE           0x00004000
#define PAGE_GRAPHICS_EXECUTE_READ      0x00008000
#define PAGE_GRAPHICS_EXECUTE_READWRITE 0x00010000
#define PAGE_GRAPHICS_COHERENT          0x00020000
#define PAGE_ENCLAVE_THREAD_CONTROL     0x80000000
#define PAGE_REVERT_TO_FILE_MAP         0x80000000
#define PAGE_TARGETS_NO_UPDATE          0x40000000
#define PAGE_TARGETS_INVALID            0x40000000
#define PAGE_ENCLAVE_UNVALIDATED        0x20000000
#define PAGE_ENCLAVE_DECOMMIT           0x10000000

typedef struct _MEMORY_BASIC_INFORMATION {
	PVOID BaseAddress;
	PVOID AllocationBase;
	DWORD AllocationProtect;
	SIZE_T RegionSize;
	DWORD State;
	DWORD Protect;
	DWORD Type;
} MEMORY_BASIC_INFORMATION, *PMEMORY_BASIC_INFORMATION;

WINBASEAPI SIZE_T WINAPI VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);
WINBASEAPI WINBOOL WINAPI VirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
WINBASEAPI WINBOOL WINAPI VirtualProtectEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
WINBASEAPI WINBOOL WINAPI ReadProcessMemory(HANDLE hProcess, LPCVOID lpBaseAddress, LPVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesRead);
WINBASEAPI WINBOOL WINAPI WriteProcessMemory(HANDLE hProcess, LPVOID lpBaseAddress, LPCVOID lpBuffer, SIZE_T nSize, SIZE_T *lpNumberOfBytesWritten);
WINBASEAPI WINBOOL WINAPI VirtualLock(LPVOID lpAddress, SIZE_T dwSize);
WINBASEAPI WINBOOL WINAPI VirtualUnlock(LPVOID lpAddress, SIZE_T dwSize);
WINBASEAPI WINBOOL WINAPI VirtualUnlockEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize);


/************************************************************************/
/* ALLOC / FREE                                                         */
/************************************************************************/
#define MEM_COMMIT                  0x00001000
#define MEM_RESERVE                 0x00002000
#define MEM_DECOMMIT                0x00004000
#define MEM_RELEASE                 0x00008000
#define MEM_FREE                    0x00010000
#define MEM_PRIVATE                 0x00020000
#define MEM_MAPPED                  0x00040000
#define MEM_RESET                   0x00080000
#define MEM_TOP_DOWN                0x00100000
#define MEM_WRITE_WATCH             0x00200000
#define MEM_PHYSICAL                0x00400000
#define MEM_ROTATE                  0x00800000
#define MEM_DIFFERENT_IMAGE_BASE_OK 0x00800000
#define MEM_RESET_UNDO              0x01000000
#define MEM_LARGE_PAGES             0x20000000
#define MEM_4MB_PAGES               0x80000000
#define MEM_64K_PAGES               (MEM_LARGE_PAGES | MEM_PHYSICAL)

WINBASEAPI LPVOID WINAPI VirtualAlloc(LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
WINBASEAPI LPVOID WINAPI VirtualAllocEx(HANDLE hProcess, LPVOID lpAddress, SIZE_T dwSize, DWORD flAllocationType, DWORD flProtect);
WINBASEAPI WINBOOL WINAPI VirtualFree(LPVOID lpAddress, SIZE_T dwSize, DWORD dwFreeType);


__DECL_END
#endif /* __CC__ */

#endif /* !_NT_MEMORYAPI_H */
