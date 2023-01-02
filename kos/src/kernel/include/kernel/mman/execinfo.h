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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EXECINFO_H
#define GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EXECINFO_H 1

#include <kernel/compiler.h>

#include <compat/config.h>

#ifdef __CC__
DECL_BEGIN

struct mfile;
struct fdirent;
struct path;

struct mexecinfo {
	/* NOTE: Fields of this structure are exposed in procfs:
	 * - mei_file:           $ cat /proc/[pid]/exe
	 * - mei_dent, mei_path: $ readlink /proc/[pid]/exe
	 * - mei_peb:            $ cat /proc/[pid]/kos/peb-addr   && echo 0x1234 > /proc/[pid]/kos/peb-addr
	 * - mei_peb_iscompat:   $ cat /proc/[pid]/kos/peb-compat && echo 0|1    > /proc/[pid]/kos/peb-compat
	 */

	REF struct mfile   *mei_file;         /* [0..1][lock(:THIS_MMAN->mm_lock)] Exec INode */
	REF struct fdirent *mei_dent;         /* [0..1][lock(:THIS_MMAN->mm_lock)] Exec directory entry */
	REF struct path    *mei_path;         /* [0..1][lock(:THIS_MMAN->mm_lock)] Exec path */
	USER CHECKED void  *mei_peb;          /* [?..1][lock(:THIS_MMAN->mm_lock)] PEB base address. */
#ifdef __ARCH_HAVE_COMPAT
	bool                mei_peb_iscompat; /* [lock(:THIS_MMAN->mm_lock)] True if the PEB is in compatibility mode. */
#endif /* __ARCH_HAVE_COMPAT */
};

/* MMan exec() information
 * NOTE: For `mman_kernel', this structure is initialized as:
 *  - mei_file         = NULL;  // or `kernel_driver.md_file'
 *  - mei_dent         = kernel_driver.md_fsname;
 *  - mei_path         = NULL;
 *  - mei_peb          = NULL;
 *  - mei_peb_iscompat = false; */
DATDEF ATTR_PERMMAN struct mexecinfo thismman_execinfo;

DECL_END
#endif /* __CC__ */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_MMAN_EXECINFO_H */
