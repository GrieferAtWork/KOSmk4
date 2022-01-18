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
#ifndef GUARD_LIBKERNEL32_MEMORYAPI_C
#define GUARD_LIBKERNEL32_MEMORYAPI_C 1

#include "api.h"
/**/

#include <kos/types.h>
#include <nt/memoryapi.h>
#include <sys/mman.h>

#include <syslog.h>
#include <errno.h>

DECL_BEGIN

DEFINE_PUBLIC_ALIAS(VirtualProtect, libk32_VirtualProtect);
INTERN WINBOOL WINAPI
libk32_VirtualProtect(LPVOID lpAddress, SIZE_T dwSize,
                      DWORD flNewProtect, PDWORD lpflOldProtect) {
	int prot;
	if (flNewProtect & (PAGE_EXECUTE_WRITECOPY | PAGE_EXECUTE_READWRITE)) {
		prot = PROT_READ | PROT_WRITE | PROT_EXEC;
	} else if (flNewProtect & PAGE_EXECUTE_READ) {
		prot = PROT_READ | PROT_EXEC;
	} else if (flNewProtect & PAGE_EXECUTE) {
		prot = PROT_EXEC;
	} else if (flNewProtect & (PAGE_WRITECOPY | PAGE_READWRITE)) {
		prot = PROT_READ | PROT_WRITE;
	} else if (flNewProtect & PAGE_READONLY) {
		prot = PROT_READ;
	} else if (flNewProtect & PAGE_NOACCESS) {
		prot = PROT_NONE;
	} else {
		prot = PROT_READ | PROT_WRITE; /* ??? */
	}
	*lpflOldProtect = PROT_READ | PROT_WRITE | PROT_EXEC; /* TODO */
	return mprotect(lpAddress, dwSize, prot) == 0;
}

DEFINE_PUBLIC_ALIAS(VirtualQuery, libk32_VirtualQuery);
WINBASEAPI SIZE_T WINAPI
libk32_VirtualQuery(LPCVOID lpAddress, PMEMORY_BASIC_INFORMATION lpBuffer, SIZE_T dwLength) {
	syslog(LOG_WARNING, "NotImplemented: VirtualQuery(%p, %p, %#Ix)\n",
	       lpAddress, lpBuffer, dwLength);
	return 0;
}



DECL_END

#endif /* !GUARD_LIBKERNEL32_MEMORYAPI_C */
