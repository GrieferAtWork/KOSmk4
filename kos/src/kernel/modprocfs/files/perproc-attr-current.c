/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_FILES_PERPROC_ATTR_CURRENT_C
#define GUARD_MODPROCFS_FILES_PERPROC_ATTR_CURRENT_C 1

#include <kernel/compiler.h>

#include <sched/pid.h>

#include <format-printer.h>

#include "../procfs.h"

DECL_BEGIN

INTERN NONNULL((1)) ssize_t KCALL
ProcFS_PerProc_Attr_Current_Printer(struct regular_node *__restrict self,
                                    pformatprinter printer, void *arg) {
	(void)self;
	return (ssize_t)format_printf(printer, arg, "unconfined");
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_ATTR_CURRENT_C */
