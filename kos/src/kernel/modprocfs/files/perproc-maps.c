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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_MAPS_C
#define GUARD_MODPROCFS_FILES_PERPROC_MAPS_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <fs/vfs.h>
#include <kernel/vm.h>
#include <kernel/exec.h> /* elfexec_system_rtld_file */
#include <sched/pid.h>

#include <kos/dev.h>

#include <format-printer.h>
#include <inttypes.h>

#include "../procfs.h"

DECL_BEGIN

/* Check if `self' has a special names, and if so: return that name. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL nameof_special_datablock)(struct vm_datablock *__restrict self) {
	/* The libdl program hard-coded into the kernel. */
	if (self == &elfexec_system_rtld_file.rf_block) {
#ifdef __ARCH_HAVE_COMPAT
#if __SIZEOF_POINTER__ == 8
		return "kernel.libdl64";
#else /* __SIZEOF_POINTER__ == 8 */
		return "kernel.libdl32";
#endif /* __SIZEOF_POINTER__ != 8 */
#else /* __ARCH_HAVE_COMPAT */
		return "kernel.libdl";
#endif /* !__ARCH_HAVE_COMPAT */
	}
#ifdef __ARCH_HAVE_COMPAT
	if (self == &compat_elfexec_system_rtld_file.rf_block)
		return "kernel.libdl";
#endif /* __ARCH_HAVE_COMPAT */
	if (self == &vm_datablock_physical)
		return "mem"; /* same as: /dev7mem */
	if (self == &vm_datablock_anonymous)
		return "anon";
	if (self == &vm_datablock_anonymous_zero)
		return "zero"; /* same as: /dev/zero */
	return NULL;
}


struct maps_printer_data {
	pformatprinter pd_printer; /* [1..1] The target printer. */
	void          *pd_arg;     /* [?..?] Argument for `pd_printer' */
};

PRIVATE ssize_t FCALL
maps_printer_cb(void *arg, struct vm_mapinfo *__restrict info) {
	struct maps_printer_data *ctx;
	dev_t dev;
	ino_t ino;
	ssize_t temp, result;
	dev = 0;
	ino = 0;
	if (info->vmi_block && vm_datablock_isinode(info->vmi_block)) {
		struct inode *node = (struct inode *)info->vmi_block;
		struct basic_block_device *superdev;
		ino      = node->i_fileino;
		superdev = node->i_super->s_device;
		if (superdev)
			dev = block_device_devno(superdev);
	}
	ctx = (struct maps_printer_data *)arg;
	result = format_printf(ctx->pd_printer,
	                       ctx->pd_arg,
	                       "%.8" PRIxPTR "-%.8" PRIxPTR " "     /* from-to */
	                       "%c%c%c%c "                          /* [r-][w-][x-][ps] */
	                       "%.8" PRIxN(__SIZEOF_OFF64_T__) " "  /* offset */
	                       "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"  /* dev:major */
	                       "%.2" PRIxN(__SIZEOF_MINOR_T__) " "  /* dev:minor */
	                       "%-7" PRIuN(__SIZEOF_INO64_T__) " ", /* inode */
	                       info->vmi_min, info->vmi_max,
	                       info->vmi_prot & VM_PROT_READ /*  */ ? 'r' : '-',
	                       info->vmi_prot & VM_PROT_WRITE /* */ ? 'w' : '-',
	                       info->vmi_prot & VM_PROT_EXEC /*  */ ? 'x' : '-',
	                       info->vmi_prot & VM_PROT_SHARED /**/ ? 's' : 'p',
	                       info->vmi_offset,
	                       MAJOR(dev), MINOR(dev), ino);
	if unlikely(result < 0)
		goto done;
	if (info->vmi_fspath) {
		char const *filename;
		u16 filename_len;
		if likely(info->vmi_fsname) {
			filename     = info->vmi_fsname->de_name;
			filename_len = info->vmi_fsname->de_namelen;
		} else {
			static char const str_unknown[] = "[unknown]";
			filename     = str_unknown;
			filename_len = COMPILER_STRLEN(str_unknown);
		}
		temp = path_printent(info->vmi_fspath,
		                     filename,
		                     filename_len,
		                     ctx->pd_printer,
		                     ctx->pd_arg);
	} else if (info->vmi_fsname) {
		temp = format_printf(ctx->pd_printer,
		                     ctx->pd_arg,
		                     "[%$#q]",
		                     (size_t)info->vmi_fsname->de_namelen,
		                     info->vmi_fsname->de_name);
	} else {
		temp = 0;
		/* Check for special names for certain datablocks. */
		if (info->vmi_block) {
			char const *special_name;
			special_name = nameof_special_datablock(info->vmi_block);
			if (special_name) {
				temp = format_printf(ctx->pd_printer,
				                     ctx->pd_arg,
				                     "[%s]",
				                     special_name);
			}
		}
	}
	if unlikely(temp < 0)
		goto err;
	result += temp;
	temp = (*ctx->pd_printer)(ctx->pd_arg, "\n", 1);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}


INTERN NONNULL((1)) ssize_t KCALL
ProcFS_PerProc_Maps_Printer(struct regular_node *__restrict self,
                            pformatprinter printer, void *arg) {
	REF struct task *thread;
	REF struct vm *threadvm;
	ssize_t result;
	upid_t pid;
	/* Lookup the associated thread. */
	pid    = (upid_t)(self->i_fileino & PROCFS_INOTYPE_PERPROC_PIDMASK);
	thread = pidns_trylookup_task(THIS_PIDNS, pid);
	if unlikely(!thread)
		goto done;
	/* Lookup the associated VM. */
	{
		FINALLY_DECREF_UNLIKELY(thread);
		threadvm = task_getvm(thread);
	}
	{
		struct maps_printer_data pd;
		FINALLY_DECREF_UNLIKELY(threadvm);
		pd.pd_printer = printer;
		pd.pd_arg     = arg;
		/* Enumerate nodes and print the maps-file. */
		result = vm_enum(threadvm,
		                 &maps_printer_cb,
		                 &pd);
	}
done:
	return result;
}


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_MAPS_C */
