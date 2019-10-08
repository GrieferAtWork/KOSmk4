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
#ifndef GUARD_MODPROCFS_FILES_SYS_KERNEL_RANDOMIZE_VA_SPACE_C
#define GUARD_MODPROCFS_FILES_SYS_KERNEL_RANDOMIZE_VA_SPACE_C 1
#define _KOS_SOURCE 1 /* snprintf returns size_t */

#include <kernel/compiler.h>

#include <kernel/vm.h>

#include <hybrid/atomic.h>

#include <unicode.h>

#include "../procfs.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Kernel_RandomizeVaSpace_Print(struct regular_node *__restrict UNUSED(self),
                                         pformatprinter printer, void *arg) {
	char buf[2];
	buf[0] = vm_get_aslr_disabled() ? '0' : '2';
	buf[1] = '\n';
	return (*printer)(arg, buf, 2);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_RandomizeVaSpace_Write(struct regular_node *__restrict UNUSED(self),
                                         USER CHECKED void const *buf,
                                         size_t bufsize) {
	USER CHECKED char *endp;
	char mode;
	endp = (USER CHECKED char *)buf + bufsize;
	while ((USER CHECKED char *)buf < endp &&
	       unicode_isspace(((USER CHECKED char *)buf)[0])) {
		buf = (USER CHECKED char *)buf + 1;
	}
	while (endp > (USER CHECKED char *)buf) {
		if (!unicode_isspace(endp[-1]))
			break;
		--endp;
	}
	if unlikely((USER CHECKED char *)buf + 1 != endp)
		goto err_badval;
	mode = ATOMIC_READ(((USER CHECKED char *)buf)[0]);
	if (mode == '0') {
		vm_set_aslr_disabled(true);
	} else if (mode == '1' || mode == '2') {
		vm_set_aslr_disabled(false);
	} else {
		goto err_badval;
	}
	return;
err_badval:
	THROW(E_INVALID_ARGUMENT_BAD_VALUE,
	      E_INVALID_ARGUMENT_CONTEXT_BAD_INTEGER);
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_SYS_KERNEL_RANDOMIZE_VA_SPACE_C */
