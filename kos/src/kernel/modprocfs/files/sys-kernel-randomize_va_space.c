/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
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

#include <kos/except-inval.h>

#include <unicode.h>

#include "../procfs.h"
#include "../util.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_Sys_Kernel_RandomizeVaSpace_Print(struct regular_node *__restrict UNUSED(self),
                                         pformatprinter printer, void *arg) {
	return ProcFS_PrintUInt(printer, arg, vm_get_aslr_disabled() ? 0 : 2);
}

INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_RandomizeVaSpace_Write(struct regular_node *__restrict UNUSED(self),
                                         USER CHECKED void const *buf,
                                         size_t bufsize) {
	unsigned int mode;
	mode = ProcFS_ParseUInt(buf, bufsize, 0, 2);
	vm_set_aslr_disabled(mode == 0);
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_SYS_KERNEL_RANDOMIZE_VA_SPACE_C */
