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

WINBASEAPI WINBOOL WINAPI VirtualProtect(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect);
WINBASEAPI SIZE_T WINAPI VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength);

__DECL_END
#endif /* __CC__ */

#endif /* !_NT_MEMORYAPI_H */
