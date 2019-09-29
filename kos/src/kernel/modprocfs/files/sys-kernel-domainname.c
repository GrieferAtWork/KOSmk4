/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_FILES_SYS_KERNEL_DOMAINNAME_C
#define GUARD_MODPROCFS_FILES_SYS_KERNEL_DOMAINNAME_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <fs/pipe.h>
#include <kernel/except.h>
#include <kernel/uname.h>
#include <sched/cred.h>
#include <sched/pid.h>

#include <hybrid/atomic.h>
#include <format-printer.h>
#include <stdio.h>
#include <stdlib.h>
#include <unicode.h>
#include <string.h>

#include "../procfs.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Kernel_Domainname_Print(struct regular_node *__restrict UNUSED(self),
                                   pformatprinter printer, void *arg) {
	return format_printf(printer, arg, "%s\n", kernel_uname.domainname);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_Domainname_Write(struct regular_node *__restrict UNUSED(self),
                                   USER CHECKED void const *buf,
                                   size_t bufsize) {
	char temp[_UTSNAME_DOMAIN_LENGTH];
	USER CHECKED char const *endp;
	endp = (USER CHECKED char const *)buf + bufsize;
	while (endp > (USER CHECKED char const *)buf &&
	       unicode_islf(endp[-1]))
		--endp;
	bufsize = (size_t)(endp - (USER CHECKED char const *)buf);
	if (bufsize > _UTSNAME_DOMAIN_LENGTH)
		THROW(E_BUFFER_TOO_SMALL, bufsize, _UTSNAME_DOMAIN_LENGTH);
	cred_require_sysadmin();
	memcpy(temp, buf, bufsize * sizeof(char));
	memset(temp + bufsize, 0, (_UTSNAME_DOMAIN_LENGTH - bufsize) * sizeof(char));
	COMPILER_READ_BARRIER();
	memcpy(kernel_uname.domainname, temp, sizeof(temp));
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_SYS_KERNEL_DOMAINNAME_C */
