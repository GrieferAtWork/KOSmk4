/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_MEMORY_MMAN_DEBUGGER_C
#define GUARD_KERNEL_SRC_MEMORY_MMAN_DEBUGGER_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/hook.h>
#include <debugger/io.h>
#include <debugger/rt.h>
#include <kernel/execabi.h> /* execabi_system_rtld_file */
#include <kernel/fs/devnode.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/super.h>
#include <kernel/mman.h>
#include <kernel/mman/enum.h>
#include <kernel/mman/map.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/ramfile.h>
#include <kernel/mman/unmapped.h>
#include <kernel/printk.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <compat/config.h>
#include <kos/exec/rtld.h> /* RTLD_LIBDL */
#include <sys/mkdev.h>

#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/rtld.h> /* COMPAT_RTLD_LIBDL */
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

PRIVATE ATTR_DBGSTRINGS char const lsmm_str_kernel[] = "kernel";
PRIVATE ATTR_DBGSTRINGS char const lsmm_str_user[] = "user";

DBG_AUTOCOMPLETE(lsmm,
                 /*size_t*/ argc, /*char **/ argv /*[]*/,
                 /*dbg_autocomplete_cb_t*/ cb, /*void **/arg) {
	(void)argv;
	if (argc == 1) {
		(*cb)(arg, lsmm_str_kernel, COMPILER_STRLEN(lsmm_str_kernel));
		(*cb)(arg, lsmm_str_user, COMPILER_STRLEN(lsmm_str_user));
	}
}

/* Check if `self' has a special names, and if so: return that name. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL nameof_special_mfile)(struct mfile *__restrict self) {
	/* The libdl program hard-coded into the kernel. */
	if (self == &execabi_system_rtld_file.mrf_file)
		return "[" RTLD_LIBDL "]";
#ifdef __ARCH_HAVE_COMPAT
	if (self == &compat_execabi_system_rtld_file.mrf_file)
		return "[" COMPAT_RTLD_LIBDL "]";
#endif /* __ARCH_HAVE_COMPAT */
	/* Since the new FS, these are literally the device files
	 * from  /dev/,  so don't  inclued  those [...]-brackets! */
	if (self == &mfile_phys)
		return "/dev/mem";
	if (self == &mfile_zero)
		return "/dev/zero";
	if (self >= mfile_anon && self < COMPILER_ENDOF(mfile_anon))
		return "[anon]";
	if (self == &mfile_ndef)
		return "[undef]";
	return NULL;
}


PRIVATE ATTR_DBGTEXT ssize_t FCALL
lsmm_enum_callback(void *UNUSED(arg), struct mmapinfo *__restrict info) {
	dev_t dev = 0;
	ino_t ino = 0;
	if (info->mmi_file && mfile_isnode(info->mmi_file)) {
		struct fnode *node = mfile_asnode(info->mmi_file);
		struct mfile *superdev;
		superdev = node->fn_super->fs_dev;
		if (superdev && mfile_isdevnode(superdev))
			dev = mfile_asdevnode(superdev)->dn_devno;
		ino = node->fn_ino;
	}
	dbg_printf(DBGSTR(AC_WHITE("%.8" PRIxPTR) "-"           /* from- */
	                  AC_WHITE("%.8" PRIxPTR) " "           /* to */
	                  "%c%c%c%c "                           /* [r-][w-][x-][sp] */
	                  "%.8" PRIxN(__SIZEOF_OFF64_T__) " "   /* offset */
	                  "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"   /* dev:major */
	                  "%.2" PRIxN(__SIZEOF_MINOR_T__) " "   /* dev:minor */
	                  "%-7" PRIuN(__SIZEOF_INO64_T__) " "), /* ino */
	           info->mmi_min, info->mmi_max,
	           info->mmi_flags & MNODE_F_PREAD /* */ ? 'r' : '-',
	           info->mmi_flags & MNODE_F_PWRITE /**/ ? 'w' : '-',
	           info->mmi_flags & MNODE_F_PEXEC /* */ ? 'x' : '-',
	           info->mmi_flags & MNODE_F_SHARED /**/ ? 's' : 'p',
	           info->mmi_offset,
	           major(dev), minor(dev), ino);
	dbg_savecolor();
	if (info->mmi_fspath) {
		char const *filename;
		u16 filename_len;
		dbg_setcolor(ANSITTY_CL_LIME, ANSITTY_CL_DARK_GRAY);
		if likely(info->mmi_fsname) {
			filename     = info->mmi_fsname->fd_name;
			filename_len = info->mmi_fsname->fd_namelen;
		} else {
			static ATTR_DBGSTRINGS char const str_unknown[] = "[unknown]";
			filename     = str_unknown;
			filename_len = COMPILER_STRLEN(str_unknown);
		}
		path_printent(info->mmi_fspath, filename,
		              filename_len, &dbg_printer, NULL);
	} else if (info->mmi_fsname) {
		dbg_setcolor(ANSITTY_CL_LIME, ANSITTY_CL_DARK_GRAY);
		if (info->mmi_fsname->fd_name[0] == '/') {
			dbg_printer(NULL,
			            info->mmi_fsname->fd_name,
			            info->mmi_fsname->fd_namelen);
		} else {
			dbg_printf(DBGSTR("[%$#q]"),
			           (size_t)info->mmi_fsname->fd_namelen,
			           info->mmi_fsname->fd_name);
		}
	} else {
		/* Check for special names for certain mfiles. */
		if (info->mmi_file) {
			char const *special_name;
			special_name = nameof_special_mfile(info->mmi_file);
			if (special_name) {
				dbg_setcolor(ANSITTY_CL_AQUA, ANSITTY_CL_DARK_GRAY);
				dbg_print(special_name);
			}
		}
	}
	dbg_loadcolor();
	dbg_putc('\n');
	return 0;
}

DBG_COMMAND_AUTO(lsmm, DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE,
                 "lsmm [kernel|user]\n"
                 "\tEnumerate memory mappings within the specified mman\n"
                 "\tIf no mman is given, select the one belonging to the current PC\n"
                 "\tOutput produced by this command follows " AC_WHITE("/proc/self/maps") "\n",
                 argc, argv) {
	struct mman *mm;
	void *minaddr = (void *)0;
	void *maxaddr = (void *)-1;
	if (argc > 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	/* Figure out  */
	if (argc == 1) {
		if (ADDR_ISUSER(dbg_getpcreg(DBG_RT_REGLEVEL_VIEW)))
			goto douser;
		mm = &mman_kernel;
	} else if (strcmp(argv[1], lsmm_str_kernel) == 0) {
		mm = &mman_kernel;
	} else if (strcmp(argv[1], lsmm_str_user) == 0) {
douser:
		mm = dbg_current->t_mman;
#ifdef USERSPACE_END
		maxaddr = (UNCHECKED void *)(USERSPACE_END - 1);
#else /* USERSPACE_END */
		minaddr = (UNCHECKED void *)USERSPACE_START;
#endif /* !USERSPACE_END */
	} else {
		return DBG_STATUS_INVALID_ARGUMENTS;
	}
	/* Enumerate all mappings from this mman. */
	mman_enum(mm, &lsmm_enum_callback, NULL, minaddr, maxaddr);
	return 0;
}


PRIVATE ATTR_DBGRODATA char const aslr_str_0[] = "0";
PRIVATE ATTR_DBGRODATA char const aslr_str_1[] = "1";

DBG_AUTOCOMPLETE(aslr,
                 /*size_t*/ argc, /*char **/ argv /*[]*/,
                 /*dbg_autocomplete_cb_t*/ cb, /*void **/arg) {
	(void)argv;
	if (argc == 1) {
		(*cb)(arg, aslr_str_0, COMPILER_STRLEN(aslr_str_0));
		(*cb)(arg, aslr_str_1, COMPILER_STRLEN(aslr_str_1));
	}
}

DBG_COMMAND_AUTO(aslr, DBG_COMMANDHOOK_FLAG_AUTOEXCLUSIVE,
                 "aslr [0|1]\n"
                 "\tCheck or enable/disable AddressSpaceLayoutRandomization\n",
                 argc, argv) {
	bool enabled;
	if (argc == 1) {
		enabled = mman_findunmapped_aslr_getenabled();
		dbg_print(enabled ? DBGSTR("enabled\n") : DBGSTR("disabled\n"));
		return enabled ? 0 : 1;
	}
	if (argc != 2)
		return DBG_STATUS_INVALID_ARGUMENTS;
	if (strcmp(argv[1], aslr_str_1) == 0) {
		enabled = true;
	} else if (strcmp(argv[1], aslr_str_0) == 0) {
		enabled = false;
	} else {
		return DBG_STATUS_INVALID_ARGUMENTS;
	}
	mman_findunmapped_aslr_setenabled(enabled);
	return 0;
}

DECL_END

#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_MEMORY_MMAN_DEBUGGER_C */
