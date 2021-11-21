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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_EXEC_EXECABI_C
#define GUARD_KERNEL_CORE_ARCH_I386_EXEC_EXECABI_C 1
#define DISABLE_BRANCH_PROFILING /* Don't profile this file */
#define __WANT_FS_INIT
#define __WANT_MPART_INIT

#include <kernel/compiler.h>

#include <kernel/execabi.h>
#include <kernel/mman/ramfile.h>

DECL_BEGIN

/* Define the RTLD file(s). */
INTDEF byte_t execabi_system_rtld_startpage_p[];
INTDEF byte_t execabi_system_rtld_numpages[];
#ifdef __x86_64__
INTDEF byte_t execabi_system_rtld32_startpage_p[];
INTDEF byte_t execabi_system_rtld32_numpages[];
#endif /* __x86_64__ */

PUBLIC struct mramfile execabi_system_rtld_file = {
	.mrf_file = {
		MFILE_INIT_mf_refcnt(1), /* +1: mfile_ndef */
		MFILE_INIT_mf_ops(&mfile_ndef_ops),
		MFILE_INIT_mf_lock,
		MFILE_INIT_mf_parts(&execabi_system_rtld_file.mrf_part),
		MFILE_INIT_mf_initdone,
		MFILE_INIT_mf_lockops,
		MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
		MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
		                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
		                    MFILE_F_FIXEDFILESIZE),
		MFILE_INIT_mf_trunclock,
		MFILE_INIT_mf_filesize(execabi_system_rtld_size),
		MFILE_INIT_mf_atime(0, 0),
		MFILE_INIT_mf_mtime(0, 0),
		MFILE_INIT_mf_ctime(0, 0),
	},
	.mrf_part = MPART_INIT_PHYS(&execabi_system_rtld_file.mrf_file,
	                            (physpage_t)execabi_system_rtld_startpage_p,
	                            (size_t)execabi_system_rtld_numpages,
	                            execabi_system_rtld_size),
};

#ifdef __x86_64__
PUBLIC struct mramfile execabi_system_rtld32_file = {
	.mrf_file = {
		MFILE_INIT_mf_refcnt(1), /* +1: mfile_ndef */
		MFILE_INIT_mf_ops(&mfile_ndef_ops),
		MFILE_INIT_mf_lock,
		MFILE_INIT_mf_parts(&execabi_system_rtld32_file.mrf_part),
		MFILE_INIT_mf_initdone,
		MFILE_INIT_mf_lockops,
		MFILE_INIT_mf_changed(MFILE_PARTS_ANONYMOUS),
		MFILE_INIT_mf_blockshift(PAGESHIFT, PAGESHIFT),
		MFILE_INIT_mf_flags(MFILE_F_ATTRCHANGED | MFILE_F_CHANGED |
		                    MFILE_F_NOATIME | MFILE_F_NOMTIME |
		                    MFILE_F_FIXEDFILESIZE),
		MFILE_INIT_mf_trunclock,
		MFILE_INIT_mf_filesize(execabi_system_rtld32_size),
		MFILE_INIT_mf_atime(0, 0),
		MFILE_INIT_mf_mtime(0, 0),
		MFILE_INIT_mf_ctime(0, 0),
	},
	.mrf_part = MPART_INIT_PHYS(&execabi_system_rtld32_file.mrf_file,
	                            (physpage_t)execabi_system_rtld32_startpage_p,
	                            (size_t)execabi_system_rtld32_numpages,
	                            execabi_system_rtld32_size),
};
#endif /* __x86_64__ */

DECL_END

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_EXEC_EXECABI_C */
