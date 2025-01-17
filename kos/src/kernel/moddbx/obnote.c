/* Copyright (c) 2019-2025 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2025 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODDBX_OBNOTE_C
#define GUARD_MODDBX_OBNOTE_C 1
#define __WANT_MPART__mp_nodlsts
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER

/**/
#include <debugger/rt.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/execabi.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/flat.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/notify-config.h> /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/heap.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/futexfd.h>
#include <kernel/mman/memfd.h>
#include <kernel/mman/mfile-misaligned.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/mman/ramfile.h>
#include <sched/cpu.h>
#include <sched/group.h>
#include <sched/scheduler.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/unaligned.h>

#include <compat/config.h>
#include <kos/exec/rtld.h>
#include <sys/mkdev.h>
#include <sys/poll.h>

#include <fcntl.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "include/obnote.h"

/**/
#include "../core/memory/mman/module-userelf.h"

#ifndef ELF_ARCH_MAXSHSTRTAB_SIZ
#define ELF_ARCH_MAXSHSTRTAB_SIZ 65536
#endif /* !ELF_ARCH_MAXSHSTRTAB_SIZ */

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/types.h>
#include <compat/kos/exec/rtld.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#define DO(expr)                 \
	do {                         \
		if ((temp = (expr)) < 0) \
			goto err;            \
		result += temp;          \
	}	__WHILE0
#define rawprint(str, len) (*printer)(arg, str, len)
#define RAWPRINT(str)      (*printer)(arg, str, COMPILER_STRLEN(str))
#define PRINT(str)         DO(RAWPRINT(str))
#define REPEAT(ch, count)  DO(format_repeat(printer, arg, ch, count))
#define PRINTF(...)        DO(format_printf(printer, arg, __VA_ARGS__))

/* Touch at least 1 byte from every page within the given address range. */
PRIVATE void KCALL
readmem(void const *__restrict ptr, size_t num_bytes) {
	if unlikely(!num_bytes)
		return;
	for (;;) {
		__asm__ __volatile__("" : : "r" (*(byte_t const *)ptr));
		if (num_bytes <= PAGESIZE)
			break;
		ptr = (byte_t const *)ptr + PAGESIZE;
		num_bytes -= PAGESIZE;
	}
}


PRIVATE ATTR_PURE WUNUSED bool KCALL verify_cpu(struct cpu *me) {
	unsigned int i;
	for (i = 0; i < cpu_count; ++i) {
		if (cpu_vector[i] == me)
			return me->c_id == i;
	}
	return false;
}


PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_task)(pformatprinter printer, void *arg,
                         NCX void const *pointer,
                         unsigned int *__restrict pstatus) {
	ssize_t temp, result = 0;
	struct task *thread = (struct task *)pointer;
	struct mexecinfo *execinfo;
	char const *exec_name = NULL;
	u16 exec_namelen      = 0;
	uintptr_t thread_flags;
	pid_t pid, tid;
	struct cpu *thread_cpu;
	unsigned int thread_cpu_id;
	TRY {
		REF struct fdirent *dent;
		/* Do some basic verification of the task header. */
		if (thread->t_self != thread)
			goto badobj;
		if (thread->t_refcnt == 0)
			goto badobj;
		thread_cpu = thread->t_cpu;
		if (!verify_cpu(thread_cpu))
			goto badobj;
		thread_cpu_id = thread_cpu->c_id;
		thread_flags  = thread->t_flags;
		execinfo      = &FORMMAN(thread->t_mman, thismman_execinfo);
		dent          = execinfo->mei_dent;
		if (dent) {
			if (dent->fd_refcnt == 0)
				goto badobj;
			exec_name    = dent->fd_name;
			exec_namelen = dent->fd_namelen;
			if (!ADDR_ISKERN(dent->fd_ops))
				goto badobj;
			if (exec_namelen > 16)
				exec_namelen = 16;
			readmem(exec_name, exec_namelen * sizeof(char));
		}
		pid = task_getrootpid_of(thread);
		tid = task_getroottid_of(thread);
	} EXCEPT {
		goto badobj;
	}
	/* Print the exec name of the thread. */
	if (thread == &FORCPU(thread_cpu, thiscpu_idle)) {
		PRINTF("idle!%u", thread_cpu_id);
		goto done;
	} else if (exec_namelen) {
		DO((*printer)(arg, exec_name, exec_namelen));
	} else if (thread_flags & TASK_FKERNTHREAD) {
		PRINT("kernel");
		if (!pid && !tid)
			goto done;
	} else {
		PRINT("??" "?");
	}
	PRINTF(" %" PRIuN(__SIZEOF_PID_T__), pid);
	if (pid != tid)
		PRINTF(" %" PRIuN(__SIZEOF_PID_T__), tid);
done:
	return result;
err:
	return temp;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_taskpid)(pformatprinter printer, void *arg,
                            NCX void const *pointer,
                            unsigned int *__restrict pstatus) {
	ssize_t result;
	struct taskpid *thread = (struct taskpid *)pointer;
	struct task *referenced_thread;
	pid_t tid;
	TRY {
		size_t ind, expected_indirection;
		struct pidns *ns;
		if (thread->tp_refcnt == 0)
			goto badobj;
		referenced_thread = thread->tp_thread.awr_obj;
		if (referenced_thread && !ADDR_ISKERN(referenced_thread))
			goto badobj;
		ns = thread->tp_ns;
		if (!ns || !ADDR_ISKERN(ns))
			goto badobj;
		ind = ns->pn_ind;
		expected_indirection = 0;
		for (;;) {
			ns = ns->pn_par;
			if (!ns)
				break;
			if (!ADDR_ISKERN(ns))
				goto badobj;
			++expected_indirection;
			if (expected_indirection > ind)
				goto badobj;
		}
		if (expected_indirection != ind)
			goto badobj;
		tid = _taskpid_slot_getpidno(thread->tp_pids[ind]);
	} EXCEPT {
		goto badobj;
	}
	if (referenced_thread) {
		result = note_task(printer, arg, referenced_thread, pstatus);
	} else {
		result = format_printf(printer, arg, "zombie %" PRIuN(__SIZEOF_PID_T__), tid);
	}
	return result;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}


PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_module)(pformatprinter printer, void *arg,
                           NCX void const *pointer,
                           unsigned int *__restrict pstatus) {
	struct module *me = (struct module *)pointer;
	char const *module_name;
	size_t module_namelen;
	TRY {
		if (me->md_refcnt == 0)
			goto badobj;
		if (me->md_weakrefcnt == 0)
			goto badobj;
		if (!ADDR_ISKERN(me->md_ops))
			goto badobj;
		if (module_isdriver(me)) {
			module_name = ((struct driver *)me)->d_name;
			if (!ADDR_ISKERN(module_name))
				goto badobj;
			module_namelen = strlen(module_name);
		} else if (me->md_fsname == NULL) {
			module_name    = "?";
			module_namelen = 1;
		} else {
			if (!ADDR_ISKERN(me->md_fsname))
				goto badobj;
			module_name    = me->md_fsname->fd_name;
			module_namelen = me->md_fsname->fd_namelen;
			if (!ADDRRANGE_ISKERN(module_name,
			                      module_name + module_namelen))
				goto badobj;
			if (module_name[0] == '/') {
				char const *tail;
				tail           = (char const *)rawmemrchr(module_name + module_namelen, '/') + 1;
				module_namelen = (size_t)((module_name + module_namelen) - tail);
				module_name    = tail;
			}
		}
		readmem(module_name, module_namelen * sizeof(char));
	} EXCEPT {
		goto badobj;
	}
	return (*printer)(arg, module_name, module_namelen);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}


typedef void (FCALL *PMODULE_OPERATOR_FREE)(struct module *__restrict self);
PRIVATE PMODULE_OPERATOR_FREE pdyn__userelf_module_free = (PMODULE_OPERATOR_FREE)(void *)-1;

PRIVATE NOBLOCK ATTR_PURE WUNUSED PMODULE_OPERATOR_FREE
NOTHROW(FCALL get__userelf_module_free)(void) {
	if (pdyn__userelf_module_free == (PMODULE_OPERATOR_FREE)(void *)-1)
		*(void **)&pdyn__userelf_module_free = driver_dlsym_local(&kernel_driver, "_userelf_module_free");
	return pdyn__userelf_module_free;
}



PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_module_section)(pformatprinter printer, void *arg,
                                   NCX void const *pointer,
                                   unsigned int *__restrict pstatus) {
	struct module_section *me = (struct module_section *)pointer;
	char const *module_name;
	size_t module_namelen;
	char const *section_name;
	size_t section_namelen;
	TRY {
		struct module *mod;
		if (me->ms_refcnt == 0)
			goto badobj;
		if (!ADDR_ISKERN(me->ms_ops))
			goto badobj;
		if (!ADDR_ISKERN(me->ms_ops->ms_destroy))
			goto badobj;
		if (!ADDR_ISKERN(me->ms_ops->ms_getname))
			goto badobj;
		mod = (struct module *)me->ms_module;
		if (!ADDR_ISKERN(mod))
			goto badobj;
		if (mod->md_weakrefcnt == 0)
			goto badobj;
		if (mod->md_refcnt == 0) {
			module_name     = "?";
			module_namelen  = 1;
			section_name    = "?";
			section_namelen = 1;
		} else {
			struct module_ops const *ops;
			ops = mod->md_ops;
			if (!ADDR_ISKERN(ops))
				goto badobj;
			if (module_ops_isdriver(ops)) {
				struct driver *drv;
				struct driver_section *sect;
				ElfW(Word) section_name_offset;
				ElfW(Shdr) *drv_shend;
				drv         = (struct driver *)mod;
				sect        = (struct driver_section *)me;
				module_name = drv->d_name;
				if (!ADDR_ISKERN(module_name))
					goto badobj;
				module_namelen = strlen(module_name);
				if (!ADDR_ISKERN(drv->d_shdr))
					goto badobj;
				drv_shend = drv->d_shdr + drv->d_shnum;
				if (!ADDR_ISKERN(drv_shend))
					goto badobj;
				if (!(drv->d_shdr < drv_shend))
					goto badobj;
				if (!(sect->ds_shdr >= drv->d_shdr && sect->ds_shdr < drv_shend))
					goto badobj;
				section_name_offset = sect->ds_shdr->sh_name;
				if (!ADDR_ISKERN(drv->d_shstrtab))
					goto badobj;
				if (section_name_offset >= drv->d_shstrsiz)
					goto badobj;
				section_name    = drv->d_shstrtab + section_name_offset;
				section_namelen = strlen(section_name);
			} else {
				if (mod->md_fsname == NULL) {
					module_name    = "?";
					module_namelen = 1;
				} else {
					if (!ADDR_ISKERN(mod->md_fsname))
						goto badobj;
					module_name    = mod->md_fsname->fd_name;
					module_namelen = mod->md_fsname->fd_namelen;
					if (!ADDRRANGE_ISKERN(module_name,
					                      module_name + module_namelen))
						goto badobj;
					if (module_name[0] == '/') {
						char const *tail;
						tail           = (char const *)rawmemrchr(module_name + module_namelen, '/') + 1;
						module_namelen = (size_t)((module_name + module_namelen) - tail);
						module_name    = tail;
					}
				}
				section_name    = "?";
				section_namelen = 1;

				/* We  can't safely invoke the `ms_getname' operator,
				 * since the section/module  may be  corrupt in  some
				 * way which we cannot forsee, in which case we  must
				 * not cause undefined behavior by calling a function
				 * that wasn't designed with guards against this kind
				 * of situation. */
#if 0
				section_name = (*me->ms_ops->ms_getname)(me);
				if (!section_name)
					section_name = "?";
				section_namelen = strlen(section_name);
#else
				/* Support for `userelf_module_section' names! */
				if (ops->mo_free == get__userelf_module_free()) {
					struct userelf_module *ue_mod;
					struct userelf_module_section *ue_sct;
					ue_mod = (struct userelf_module *)mod;
					ue_sct = (struct userelf_module_section *)me;
					if (UM_any(ue_mod->um_shdrs) && ue_mod->um_shstrtab) {
						size_t sizeof_ElfW_Shdr, shstrtab_siz;
						uintptr_t sh_name;
						sizeof_ElfW_Shdr = UM_sizeof(ue_mod, UM_ElfW_Shdr);
						if ((byte_t const *)ue_sct->ums_shdr < (byte_t const *)UM_any(ue_mod->um_shdrs) ||
						    (byte_t const *)ue_sct->ums_shdr >= ((byte_t const *)UM_any(ue_mod->um_shdrs) +
						                                         (size_t)ue_mod->um_shnum * sizeof_ElfW_Shdr))
							goto badobj;
						if ((((byte_t const *)ue_sct->ums_shdr -
						      (byte_t const *)UM_any(ue_mod->um_shdrs)) %
						     sizeof_ElfW_Shdr) != 0)
							goto badobj;
						if (!ADDR_ISKERN(ue_mod->um_shstrtab))
							goto badobj;
						if (ue_mod->um_shstrndx >= ue_mod->um_shnum)
							goto badobj;
						sh_name      = UM_field(ue_mod, *ue_sct->ums_shdr, .sh_name);
						shstrtab_siz = UM_field(ue_mod, ue_mod->um_shdrs, [ue_mod->um_shstrndx].sh_size);
						if (shstrtab_siz > ELF_ARCH_MAXSHSTRTAB_SIZ)
							goto badobj;
						if (sh_name >= shstrtab_siz)
							goto badobj;
						/* Extract the name from the section string table. */
						section_name    = ue_mod->um_shstrtab + sh_name;
						section_namelen = strnlen(section_name, shstrtab_siz - sh_name);
					}
				}
#endif
			}
		}
		readmem(module_name, module_namelen * sizeof(char));
		readmem(section_name, section_namelen * sizeof(char));
	} EXCEPT {
		goto badobj;
	}
	return format_printf(printer, arg, "%$s!%$s",
	                     module_namelen, module_name,
	                     section_namelen, section_name);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE ATTR_CONST WUNUSED char const *
NOTHROW(KCALL get_dirent_type_name)(unsigned char dt_type) {
	switch (dt_type) {
	case DT_UNKNOWN: return "unknown";
	case DT_FIFO:    return "fifo";
	case DT_CHR:     return "chr";
	case DT_DIR:     return "dir";
	case DT_BLK:     return "blk";
	case DT_REG:     return "reg";
	case DT_LNK:     return "lnk";
	case DT_SOCK:    return "sock";
	case DT_WHT:     return "wht";
	default: break;
	}
	return NULL;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_fdirent_ex)(pformatprinter printer, void *arg,
                               NCX void const *pointer,
                               unsigned int *__restrict pstatus,
                               bool print_type) {
	ssize_t result, temp;
	char const *typnam;
	struct fdirent *me = (struct fdirent *)pointer;
	char const *dent_name;
	size_t dent_namelen;
	TRY {
		if (me->fd_refcnt == 0)
			goto badobj;
		dent_name    = me->fd_name;
		dent_namelen = me->fd_namelen;
		if (!ADDR_ISKERN(me->fd_ops))
			goto badobj;
		if (me->fd_hash != fdirent_hash(dent_name, dent_namelen))
			goto badobj;
		readmem(dent_name, dent_namelen * sizeof(char));
		typnam = get_dirent_type_name(me->fd_type);
		if unlikely(!typnam)
			goto badobj;
	} EXCEPT {
		goto badobj;
	}
	result = 0;
	if (print_type)
		result = format_printf(printer, arg, "%s:", typnam);
	if likely(result >= 0)
		DO((*printer)(arg, dent_name, dent_namelen));
	return result;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
err:
	return temp;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_fdirent)(pformatprinter printer, void *arg,
                            NCX void const *pointer,
                            unsigned int *__restrict pstatus) {
	return note_fdirent_ex(printer, arg, pointer, pstatus, true);
}


PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_cpu)(pformatprinter printer, void *arg,
                        NCX void const *pointer,
                        unsigned int *__restrict pstatus) {
	struct cpu *me = (struct cpu *)pointer;
	unsigned int id;
	TRY {
		/* Search for the CPU within the set of valid CPUs. */
		for (id = 0; id < cpu_count; ++id) {
			if (cpu_vector[id] == me)
				goto ok;
		}
	} EXCEPT {
	}
	goto badobj;
ok:
	return format_printf(printer, arg, "%u", id);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_path_impl)(pformatprinter printer, void *arg,
                              NCX void const *pointer,
                              unsigned int *__restrict pstatus,
                              bool want_root_directory_slash) {
	ssize_t temp, result;
	struct path *me = (struct path *)pointer;
	struct path *parent_path = NULL;
	struct fdirent *dent;
	TRY {
		if (me->p_refcnt == 0)
			goto badobj;
		if (me->_p_vfs == NULL || !ADDR_ISKERN(me->_p_vfs))
			goto badobj;
		if (!path_isroot(me)) {
			parent_path = me->p_parent;
			if (!ADDR_ISKERN(parent_path))
				goto badobj;
		}
		dent = me->p_name;
		if (!dent || !ADDR_ISKERN(dent))
			goto badobj;
	} EXCEPT {
		goto badobj;
	}
	result = 0;
	if (parent_path) {
		result = note_path_impl(printer, arg, parent_path, pstatus, false);
		if unlikely(result < 0)
			goto done;
		if (*pstatus != OBNOTE_PRINT_STATUS_SUCCESS)
			goto done;
	}
	if (want_root_directory_slash || parent_path) {
		temp = (*printer)(arg, "/", 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	temp = note_fdirent_ex(printer, arg, dent, pstatus, false);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_path)(pformatprinter printer, void *arg,
                         NCX void const *pointer,
                         unsigned int *__restrict pstatus) {
	return note_path_impl(printer, arg, pointer, pstatus, true);
}

PRIVATE NONNULL((1, 4, 5)) ssize_t
NOTHROW(KCALL note_pathpair)(pformatprinter printer, void *arg,
                             NCX struct path const *p,
                             NCX struct fdirent const *d,
                             unsigned int *__restrict pstatus) {
	ssize_t temp, result = 0;
	if (p) {
		result = note_path_impl(printer, arg, p, pstatus, false);
		if (result < 0 || *pstatus != OBNOTE_PRINT_STATUS_SUCCESS)
			goto done;
		temp = (*printer)(arg, "/", 1);
		if unlikely(temp < 0)
			goto err;
		result += temp;
	}
	temp = note_fdirent_ex(printer, arg, d, pstatus, false);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_mman)(pformatprinter printer, void *arg,
                         NCX void const *pointer,
                         unsigned int *__restrict pstatus) {
	ssize_t result;
	struct mman *me = (struct mman *)pointer;
	struct path *exec_path;
	struct fdirent *exec_dent;
	TRY {
		if (!IS_ALIGNED((uintptr_t)me, PAGEDIR_ALIGN))
			goto badobj;
		if (me->mm_refcnt == 0)
			goto badobj;
		if (me->mm_weakrefcnt == 0)
			goto badobj;
#ifdef ARCH_PAGEDIR_GETSET_USES_POINTER
		if (me->mm_pagedir_p != (PHYS pagedir_t *)(uintptr_t)pagedir_translate(&me->mm_pagedir))
			goto badobj;
#else /* ARCH_PAGEDIR_GETSET_USES_POINTER */
		if (me->mm_pagedir_p != pagedir_translate(&me->mm_pagedir))
			goto badobj;
#endif /* !ARCH_PAGEDIR_GETSET_USES_POINTER */
		exec_path = FORMMAN(me, thismman_execinfo).mei_path;
		exec_dent = FORMMAN(me, thismman_execinfo).mei_dent;
		if (!exec_dent) {
			exec_path = NULL;
		} else {
			if (!ADDR_ISKERN(exec_dent))
				goto badobj;
			if (exec_path && !ADDR_ISKERN(exec_path))
				goto badobj;
		}
	} EXCEPT {
		goto badobj;
	}
	if (me == &mman_kernel) {
		result = RAWPRINT("kernel");
	} else if (exec_dent) {
		result = note_pathpair(printer, arg,
		                       exec_path,
		                       exec_dent,
		                       pstatus);
	} else {
		result = RAWPRINT("??" "?");
	}
	return result;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}


PRIVATE NOBLOCK NONNULL((1, 2, 3)) char const *
NOTHROW(FCALL mfile_known_name)(struct mfile *__restrict self,
                                struct mfile_ops const *__restrict ops,
                                char buf[64]) {
	char const *result = NULL;
	if (self == &execabi_system_rtld_file.mrf_file) {
		result = "[" RTLD_LIBDL "]";
#ifdef __ARCH_HAVE_COMPAT
	} else if (self == &compat_execabi_system_rtld_file.mrf_file) {
		result = "[" COMPAT_RTLD_LIBDL "]";
#endif /* __ARCH_HAVE_COMPAT */
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	} else if (self == &mfile_dbgheap) {
		result = "[dbgheap]";
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	} else if (self == &mfile_zero) {
		result = "/dev/zero";
	} else if (self >= mfile_anon && self < COMPILER_ENDOF(mfile_anon)) {
		result = buf;
		sprintf(buf, "[/dev/zero:anon:%u]", (unsigned int)(self - mfile_anon));
	} else if (self == &mfile_ndef) {
		result = "[undef]";
	} else if (self == &mfile_phys) {
		result = "/dev/mem";
	} else if (ops >= mfile_anon_ops && ops < COMPILER_ENDOF(mfile_anon_ops)) {
		result = buf;
		sprintf(buf, "[?/dev/zero:anon:%u]", (unsigned int)(ops - mfile_anon_ops));
	}
	return result;
}


PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_mnode)(pformatprinter printer, void *arg,
                          NCX void const *pointer,
                          unsigned int *__restrict pstatus) {
	ssize_t result, temp;
	struct mnode *me = (struct mnode *)pointer;
	struct path *file_path = NULL;
	struct fdirent *file_dent = NULL;
	struct mpart *part;
	struct mfile *file = NULL;
	struct mfile_ops const *file_ops = NULL;
	pos_t file_position = 0;
	byte_t *minaddr, *maxaddr;
	uintptr_t flags;
	bool isanon;
	TRY {
		minaddr = me->mn_minaddr;
		maxaddr = me->mn_maxaddr;
		if (!IS_ALIGNED((uintptr_t)minaddr, PAGESIZE))
			goto badobj;
		if (!IS_ALIGNED((uintptr_t)maxaddr + 1, PAGESIZE))
			goto badobj;
		if (minaddr >= maxaddr)
			goto badobj;
		if (ADDR_ISKERN(minaddr) != ADDR_ISKERN(maxaddr))
			goto badobj;
		flags = me->mn_flags;
		part  = me->mn_part;
		isanon = false;
		if (part != NULL) {
			if (!ADDR_ISKERN(part))
				goto badobj;
			file_position = (pos_t)me->mn_partoff;
			if (!IS_ALIGNED(file_position, PAGESIZE))
				goto badobj;
			if (!ADDR_ISKERN(me->mn_link.le_prev))
				goto badobj;
			if (*me->mn_link.le_prev != me)
				goto badobj;
			if (me->mn_link.le_next != NULL) {
				if (!ADDR_ISKERN(me->mn_link.le_next))
					goto badobj;
				if (me->mn_link.le_next->mn_link.le_prev != &me->mn_link.le_next)
					goto badobj;
			}
			if (!IS_ALIGNED(part->mp_minaddr, PAGESIZE))
				goto badobj;
			if (!IS_ALIGNED(part->mp_maxaddr + 1, PAGESIZE))
				goto badobj;
			file_position += part->mp_minaddr;
			if ((pos_t)(me->mn_partoff + (size_t)(maxaddr - minaddr) + 1) >
			    (pos_t)((part->mp_maxaddr - part->mp_minaddr) + 1))
				goto badobj;
			file = part->mp_file;
			if (!ADDR_ISKERN(file))
				goto badobj;
			file_ops = file->mf_ops;
			if (!ADDR_ISKERN(file_ops))
				goto badobj;
			file_path = me->mn_fspath;
			file_dent = me->mn_fsname;
			if (!file_dent) {
				file_path = NULL;
			} else {
				if (!ADDR_ISKERN(file_dent))
					goto badobj;
				if (file_path && !ADDR_ISKERN(file_path))
					goto badobj;
			}
			isanon = mpart_isanon(part);
		}
	} EXCEPT {
		goto badobj;
	}
	result = format_printf(printer, arg, "%p-%p:%c%c%c%c",
	                       minaddr, maxaddr,
	                       flags & MNODE_F_SHARED ? 's' : '-',
	                       flags & MNODE_F_PREAD ? 'r' : '-',
	                       flags & MNODE_F_PWRITE ? 'w' : '-',
	                       flags & MNODE_F_PEXEC ? 'x' : '-');
	if (result < 0)
		goto done;
	if (part) {
		PRINT(":");
		if (isanon)
			PRINT("{");
		if (file_dent) {
			DO(note_pathpair(printer, arg, file_path, file_dent, pstatus));
		} else {
			char const *known_name;
			char buf[64];
			known_name = mfile_known_name(file, file_ops, buf);
			if (known_name) {
				DO((*printer)(arg, known_name, strlen(known_name)));
			} else {
				PRINT("??" "?");
			}
		}
		if (isanon)
			PRINT("}");
		PRINTF("+%#" PRIxN(__SIZEOF_POS_T__), file_position);
	}
done:
	return result;
err:
	return temp;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 2, 3, 4)) bool FCALL
mpart_tree_extract_name(NCX struct mpart *self,
                        struct path **p_file_path,
                        struct fdirent **p_file_dent,
                        unsigned int *__restrict pstatus,
                        unsigned int depth_limit) {
	unsigned int i;
	struct mpart *lhs, *rhs;
again:
	for (i = 0; i < 2; ++i) {
		struct mnode *node;
		node = i ? self->mp_share.lh_first
		         : self->mp_copy.lh_first;
		while (node) {
			if (!ADDR_ISKERN(node))
				goto badobj;
			*p_file_path = node->mn_fspath;
			*p_file_dent = node->mn_fsname;
			if (*p_file_path && *p_file_dent) {
				if (!ADDR_ISKERN(*p_file_path))
					goto badobj;
				if (!ADDR_ISKERN(*p_file_dent))
					goto badobj;
				return true;
			}
			node = node->mn_link.le_next;
		}
	}
	if (depth_limit != 0) {
		--depth_limit;
		lhs = self->mp_filent.rb_lhs;
		rhs = self->mp_filent.rb_rhs;
		if (lhs && !ADDR_ISKERN(lhs))
			goto badobj;
		if (rhs && !ADDR_ISKERN(rhs))
			goto badobj;
		/* Recursively scan the entire tree. */
		if (lhs) {
			if (rhs) {
				if (mpart_tree_extract_name(rhs,
				                            p_file_path,
				                            p_file_dent,
				                            pstatus,
				                            depth_limit))
					return true;
			}
			self = lhs;
			goto again;
		}
		if (rhs) {
			self = rhs;
			goto again;
		}
	}
	return false;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return true;
}

PRIVATE NONNULL((2, 3, 4)) bool KCALL
mfile_extract_name(struct mfile const *self,
                   struct path **__restrict p_fspath,
                   struct fdirent **__restrict p_fsname,
                   unsigned int *__restrict pstatus) {
	struct mpart *root;
	if (!ADDR_ISKERN(self))
		goto badobj;
	if (!ADDR_ISKERN(self->mf_ops))
		goto badobj;
	root = self->mf_parts;
	/* Check if there's an mnode-mapping that includes fs-name info. */
	if (root && root != MFILE_PARTS_ANONYMOUS) {
		if (!ADDR_ISKERN(root))
			goto badobj;
		if (!mpart_tree_extract_name(root, p_fspath, p_fsname, pstatus, 16)) {
			if (*pstatus == OBNOTE_PRINT_STATUS_BADOBJ)
				goto badobj;
		}
	}
#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY
	/* TODO: If a dnotify_controller is attached to the inotify_controller of `self',
	 *       then we can determine (at least 1) name of `self' in some directory. But
	 *       in this case we still can't determine where that directory is... */
#endif /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
	return true;
badobj:
	return false;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_mfile)(pformatprinter printer, void *arg,
                          NCX void const *pointer,
                          unsigned int *__restrict pstatus) {
	ssize_t result, temp;
	struct mfile *me = (struct mfile *)pointer;
	struct mfile_ops const *ops;
	struct path *file_path = NULL;
	struct fdirent *file_dent = NULL;
	TRY {
		ops = me->mf_ops;
		if (!ADDR_ISKERN(ops))
			goto badobj;
		/* if it's a device file, extract the devfs filename. */
		if (ops->mo_changed == &fnode_v_changed &&
		    S_ISDEV(mfile_asnode(me)->fn_mode) &&
		    mfile_asnode(me)->fn_super == _ramfs_super_assuper(&devfs) &&
		    ops != &ramfs_devnode_ops.dvno_node.no_file) {
			REF struct devdirent *name;
			name = mfile_asdevice(me)->dv_dirent;
			if (!name || !ADDR_ISKERN(name))
				goto badobj;
			file_dent = &name->dd_dirent;
			goto do_print_devfs_name;
		}
		if (!mfile_extract_name(me, &file_path, &file_dent, pstatus))
			goto badobj;
	} EXCEPT {
		goto badobj;
	}
	result = 0;
	if (file_dent) {
		DO(note_pathpair(printer, arg, file_path, file_dent, pstatus));
	} else {
		char const *known_name;
		char buf[64];
		known_name = mfile_known_name(me, ops, buf);
		if (known_name) {
			DO((*printer)(arg, known_name, strlen(known_name)));
		} else {
			/* Special printing for specific sub-classes of `mfile' */
			TRY {
				if (ops->mo_changed == &fnode_v_changed) {
					struct fnode *node   = mfile_asnode(me);
					struct fsuper *super = node->fn_super;
					struct ffilesys *sys;
					struct mfile *dev;
					struct pathmount *somemount;
					char const *typnam;
					if (!super || !ADDR_ISKERN(super))
						goto badobj;
					sys = super->fs_sys;
					if (!sys || !ADDR_ISKERN(sys))
						goto badobj;
					dev = super->fs_dev;
					if (dev && (!ADDR_ISKERN(dev) || dev == &super->fs_root))
						goto badobj;
					typnam = get_dirent_type_name(IFTODT(node->fn_mode));
					if unlikely(!typnam)
						goto badobj;

					/* Print super-related information. */
					somemount = LIST_FIRST(&super->fs_mounts);
					result = rawprint(sys->ffs_name, strlen(sys->ffs_name));
					if unlikely(result < 0)
						goto done;
					PRINT(":");
					if (dev) {
						PRINT("[");
						DO(note_mfile(printer, arg, dev, pstatus));
						if (*pstatus != OBNOTE_PRINT_STATUS_SUCCESS)
							goto done;
						PRINT("]");
					}
					PRINT(":");
					if (somemount != NULL &&
					    somemount != FSUPER_MOUNTS_DELETED) {
						if (!ADDR_ISKERN(somemount))
							goto badobj;
						DO(note_path(printer, arg, (struct path *)somemount, pstatus));
						if (*pstatus != OBNOTE_PRINT_STATUS_SUCCESS)
							goto done;
					}
					if (node == &super->fs_root) {
						if (!S_ISDIR(node->fn_mode))
							goto badobj;
						goto done;
					}
					PRINTF(":%s:%04o:%" PRIuN(__SIZEOF_INO_T__),
					       typnam, node->fn_mode & 07777,
					       node->fn_ino);
					if (S_ISDEV(node->fn_mode)) {
						struct fdevnode *devnode;
						dev_t devno;
						devnode = fnode_asdevnode(node);
						devno   = devnode->dn_devno;
						PRINTF(":[%" PRIuN(__SIZEOF_MAJOR_T__) ":%" PRIuN(__SIZEOF_MINOR_T__) "]",
						       major(devno), minor(devno));
					}
					if (fnode_islnk(node)) {
						struct flnknode_ops const *lnkops;
						lnkops = container_of(ops, struct flnknode_ops, lno_node.no_file);
						if (lnkops->lno_linkstr == &clnknode_v_linkstr) {
							struct clnknode *clnk = (struct clnknode *)fnode_aslnk(node);
							PRINTF(":%#q", clnk->lnc_text);
						}
					}
					goto done;
				}
				if (ops == &memfd_ops) {
					struct memfd *mfd    = mfile_asmemfd(me);
					struct fdirent *name = mfd->mfd_name;
					if (!name || !ADDR_ISKERN(name))
						goto badobj;
					result = RAWPRINT("memfd:");
					if unlikely(result < 0)
						goto done;
					DO(note_fdirent_ex(printer, arg, name, pstatus, false));
					goto done;
				}
				if (ops == &misaligned_mfile_ops) {
					struct misaligned_mfile *msm = mfile_asmisaligned(me);
					struct mfile *base = msm->mam_base;
					if (!base || !ADDR_ISKERN(base))
						goto badobj;
					if (base->mf_ops == &misaligned_mfile_ops)
						goto badobj; /* Misaligned files can't have misaligned bases! */
					if (msm->mam_offs == 0)
						goto badobj; /* Misaligned files can't have offset=0 */
					result = RAWPRINT("misaligned:[");
					if unlikely(result < 0)
						goto done;
					DO(note_mfile(printer, arg, base, pstatus));
					PRINTF(":+%" PRIuSIZ "]", msm->mam_offs);
					goto done;
				}
			} EXCEPT {
				goto badobj;
			}
			/* Fallback: don't know... */
			PRINT("??" "?");
		}
	}
done:
	return result;
do_print_devfs_name:
	result = RAWPRINT("/dev/");
	if unlikely(result < 0)
		goto done;
	DO(note_fdirent_ex(printer, arg, file_dent, pstatus, false));
	return result;
err:
	return temp;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_fsuper)(pformatprinter printer, void *arg,
                           NCX void const *pointer,
                           unsigned int *__restrict pstatus) {
	struct fsuper *me = (struct fsuper *)pointer;
	return note_mfile(printer, arg, &me->fs_root, pstatus);
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_flatsuper)(pformatprinter printer, void *arg,
                              NCX void const *pointer,
                              unsigned int *__restrict pstatus) {
	struct flatsuper *me = (struct flatsuper *)pointer;
	return note_mfile(printer, arg, &me->ffs_super, pstatus);
}


PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_mpart)(pformatprinter printer, void *arg,
                          NCX void const *pointer,
                          unsigned int *__restrict pstatus) {
	ssize_t result, temp;
	struct mpart *me = (struct mpart *)pointer;
	struct path *file_path = NULL;
	struct fdirent *file_dent = NULL;
	struct mfile *file;
	struct mfile_ops const *file_ops;
	pos_t minaddr, maxaddr;
	bool isanon;
	TRY {
		unsigned int i;
		minaddr = me->mp_minaddr;
		maxaddr = me->mp_maxaddr;
		if (!IS_ALIGNED(minaddr, PAGESIZE))
			goto badobj;
		if (!IS_ALIGNED(maxaddr + 1, PAGESIZE))
			goto badobj;
		if (!(minaddr <= maxaddr))
			goto badobj;
		file = me->mp_file;
		if (!ADDR_ISKERN(file))
			goto badobj;
		file_ops = file->mf_ops;
		if (!ADDR_ISKERN(file_ops))
			goto badobj;
		isanon = mpart_isanon(me);
		/* Check if there's an mnode-mapping that includes fs-name info. */
		for (i = 0; i < lengthof(me->_mp_nodlsts); ++i) {
			struct mnode *node;
			LIST_FOREACH (node, &me->_mp_nodlsts[i], mn_link) {
				if (!ADDR_ISKERN(node))
					goto badobj;
				file_path = node->mn_fspath;
				file_dent = node->mn_fsname;
				if (file_path && file_dent) {
					if (!ADDR_ISKERN(file_path))
						goto badobj;
					if (!ADDR_ISKERN(file_dent))
						goto badobj;
					goto got_all_info;
				}
			}
		}
		if (!file_path && !file_dent) {
			if (!mfile_extract_name(file, &file_path, &file_dent, pstatus))
				goto badobj;
		}
	} EXCEPT {
		goto badobj;
	}
got_all_info:
	result = 0;
	if (isanon)
		PRINT("{");
	if (file_dent) {
		DO(note_pathpair(printer, arg, file_path, file_dent, pstatus));
	} else {
		char const *known_name;
		char buf[64];
		known_name = mfile_known_name(file, file_ops, buf);
		if (known_name) {
			DO((*printer)(arg, known_name, strlen(known_name)));
		} else {
			PRINT("??" "?");
		}
	}
	if (isanon)
		PRINT("}");
	PRINTF(":%" PRIxN(__SIZEOF_POS_T__) ""
	       "-%" PRIxN(__SIZEOF_POS_T__) "",
	       minaddr, maxaddr);
	return result;
err:
	return temp;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}


PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_filehandle_impl)(pformatprinter printer, void *arg,
                                    NCX void const *pointer,
                                    unsigned int *__restrict pstatus,
                                    bool is_dirhandle) {
	ssize_t result;
	struct filehandle *me = (struct filehandle *)pointer;
	struct path *file_path;
	struct fdirent *file_dent;
	struct mfile *file;
	TRY {
		if (me->fh_refcnt == 0)
			goto badobj;
		file_path = me->fh_path;
		file_dent = me->fh_dirent;
		if (!file_dent) {
			file_path = NULL;
		} else {
			if (!ADDR_ISKERN(file_dent))
				goto badobj;
			if (file_path && !ADDR_ISKERN(file_path))
				goto badobj;
		}
		file = me->fh_file;
		if (is_dirhandle)
			file = ((struct dirhandle *)me)->dh_enum.de_dir;
		if (!file || !ADDR_ISKERN(file))
			goto badobj;
	} EXCEPT {
		goto badobj;
	}
	if (file_dent) {
		result = note_pathpair(printer, arg, file_path, file_dent, pstatus);
	} else {
		result = note_mfile(printer, arg, file, pstatus);
	}
	return result;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_filehandle)(pformatprinter printer, void *arg,
                               NCX void const *pointer,
                               unsigned int *__restrict pstatus) {
	return note_filehandle_impl(printer, arg, pointer, pstatus, false);
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_dirhandle)(pformatprinter printer, void *arg,
                              NCX void const *pointer,
                              unsigned int *__restrict pstatus) {
	return note_filehandle_impl(printer, arg, pointer, pstatus, true);
}


PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_mfutex)(pformatprinter printer, void *arg,
                           NCX void const *pointer,
                           unsigned int *__restrict pstatus) {
	ssize_t result, temp;
	struct mfutex *me = (struct mfutex *)pointer;
	struct mpart *part;
	struct path *file_path            = NULL;
	struct fdirent *file_dent = NULL;
	struct mfile *file                = NULL;
	struct mfile_ops const *file_ops  = NULL;
	pos_t part_minaddr                = 0;
	bool isanon                       = false;
	mpart_reladdr_t part_reladdr;
	TRY {
		part         = me->mfu_part.awr_obj;
		part_reladdr = me->mfu_addr;
		if (!ADDR_ISKERN(part))
			goto badobj;
		if (part->mp_refcnt == 0) {
			/* Part has been destroyed. */
			part = NULL;
		} else {
			unsigned int i;
			pos_t part_maxaddr;
			if (part_reladdr >= mpart_getsize(part))
				goto badobj;
			part_minaddr = part->mp_minaddr;
			part_maxaddr = part->mp_maxaddr;
			if (!IS_ALIGNED(part_minaddr, PAGESIZE))
				goto badobj;
			if (!IS_ALIGNED(part_maxaddr + 1, PAGESIZE))
				goto badobj;
			if (!(part_minaddr <= part_maxaddr))
				goto badobj;
			file = part->mp_file;
			if (!ADDR_ISKERN(file))
				goto badobj;
			file_ops = file->mf_ops;
			if (!ADDR_ISKERN(file_ops))
				goto badobj;
			isanon = mpart_isanon(part);

			/* Check if there's an mnode-mapping that includes fs-name info. */
			for (i = 0; i < lengthof(part->_mp_nodlsts); ++i) {
				struct mnode *node;
				LIST_FOREACH (node, &part->_mp_nodlsts[i], mn_link) {
					if (!ADDR_ISKERN(node))
						goto badobj;
					file_path = node->mn_fspath;
					file_dent = node->mn_fsname;
					if (file_path && file_dent) {
						if (!ADDR_ISKERN(file_path))
							goto badobj;
						if (!ADDR_ISKERN(file_dent))
							goto badobj;
						goto got_all_info;
					}
				}
			}
			if (!file_path && !file_dent) {
				if (!mfile_extract_name(file, &file_path, &file_dent, pstatus))
					goto badobj;
			}
		}
	} EXCEPT {
		goto badobj;
	}
got_all_info:
	if (!part) {
		result = format_printf(printer, arg, "<destroyed>+%#" PRIxSIZ,
		                       part_reladdr);
	} else {
		result = 0;
		if (isanon)
			PRINT("{");
		if (file_dent) {
			DO(note_pathpair(printer, arg, file_path, file_dent, pstatus));
		} else {
			char const *known_name;
			char buf[64];
			known_name = mfile_known_name(file, file_ops, buf);
			if (known_name) {
				DO((*printer)(arg, known_name, strlen(known_name)));
			} else {
				PRINT("??" "?");
			}
		}
		if (isanon)
			PRINT("}");
		PRINTF("+%#" PRIxN(__SIZEOF_POS_T__),
		       (pos_t)(part_minaddr + part_reladdr));
	}
	return result;
err:
	return temp;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}


PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_mfutexfd)(pformatprinter printer, void *arg,
                             NCX void const *pointer,
                             unsigned int *__restrict pstatus) {
	ssize_t result, temp;
	struct mfutexfd *me = (struct mfutexfd *)pointer;
	struct mman *mm;
	struct mfutex *ftx;
	TRY {
		mm  = me->mfd_mman;
		ftx = me->mfd_futex;
		if (!mm || !ADDR_ISKERN(mm))
			goto badobj;
		if (!ftx || !ADDR_ISKERN(ftx))
			goto badobj;
		if (wasdestroyed(mm))
			mm = NULL;
	} EXCEPT {
		goto badobj;
	}
	result = 0;
	if (mm) {
		result = note_mman(printer, arg, mm, pstatus);
		if unlikely(result < 0)
			goto done;
		if (*pstatus != OBNOTE_PRINT_STATUS_SUCCESS)
			goto done;
		PRINT(":");
	}
	DO(note_mfutex(printer, arg, ftx, pstatus));
done:
	return result;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
err:
	return temp;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_handle)(pformatprinter printer, void *arg,
                           NCX void const *pointer,
                           unsigned int *__restrict pstatus);

PRIVATE NONNULL((1, 4, 5)) ssize_t
NOTHROW(KCALL print_path_with_prefix)(pformatprinter printer, void *arg,
                                      NCX void const *pointer,
                                      unsigned int *__restrict pstatus,
                                      char const *__restrict prefix) {
	ssize_t result, temp;
	result = rawprint(prefix, strlen(prefix));
	if unlikely(result < 0)
		return result;
	temp = note_path(printer, arg, pointer, pstatus);
	if unlikely(temp < 0)
		return temp;
	return result + temp;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_fd_t_value)(pformatprinter printer, void *arg, fd_t fd,
                               unsigned int *__restrict pstatus) {
	struct handle hand;
	struct handman *hman;
	TRY {
		struct handrange *range;
		unsigned int relfd;
		if (!dbg_current || !ADDR_ISKERN(dbg_current))
			goto badobj;
		hman = FORTASK(dbg_current, this_handman);
		if (!hman || !ADDR_ISKERN(hman))
			goto badobj;
		if (fd < 0) {
			/* Symbolic handles */
			struct fs *curfs = FORTASK(dbg_current, this_fs);
			struct vfs *curvfs;
			if (!curfs || !ADDR_ISKERN(curfs))
				goto badobj;
			curvfs = curfs->fs_vfs;
			if (!curvfs || !ADDR_ISKERN(curvfs))
				goto badobj;
			switch (fd) {

			case AT_FDCWD: {
				struct path *p = curfs->fs_cwd;
				if (!p || !ADDR_ISKERN(p))
					goto badobj;
				return print_path_with_prefix(printer, arg, p, pstatus, "AT_FDCWD:");
			}	break;

			case AT_FDROOT: {
				struct path *p = curfs->fs_root;
				if (!p || !ADDR_ISKERN(p))
					goto badobj;
				return print_path_with_prefix(printer, arg, p, pstatus, "AT_FDROOT:");
			}	break;

			case (AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX)):
			case (AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)): {
				char prefixstr[lengthof("AT_FDDRIVE_ROOT('Z')")];
				struct path *p = curfs->fs_dcwd[(unsigned int)fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN)];
				if (!p || (fd >= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN) &&
				           fd <= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)))
					p = curvfs->vf_drives[(unsigned int)fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)];
				if (!p || !ADDR_ISKERN(p))
					goto badobj;
				sprintf(prefixstr, "AT_FDDRIVE_%s('%c')",
				        fd >= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN) &&
				        fd <= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)
				        ? "ROOT"
				        : "CWD",
				        'A' + ((fd >= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN) &&
				                fd <= AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX))
				               ? (fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN))
				               : (fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN))));
				return print_path_with_prefix(printer, arg, p, pstatus, prefixstr);
			}	break;

			default:
				break;
			}
		}
		if (!hman->hm_ranges || !ADDR_ISKERN(hman->hm_ranges))
			goto badobj;
		range = handman_ranges_locate(hman, (unsigned int)fd);
		if (!range || !ADDR_ISKERN(range))
			goto badobj;
		if ((unsigned int)fd < range->hr_minfd)
			goto badobj;
		if ((unsigned int)fd > range->hr_maxfd)
			goto badobj;
		relfd = (unsigned int)fd - range->hr_minfd;
		if (!handrange_slotishand(range, relfd))
			goto badobj;
		hand = range->hr_hand[relfd].mh_hand;
		if (hand.h_type == HANDLE_TYPE_UNDEFINED)
			goto badobj;
	} EXCEPT {
		goto badobj;
	}
	return note_handle(printer, arg, &hand, pstatus);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_fd_t)(pformatprinter printer, void *arg,
                         NCX void const *pointer,
                         unsigned int *__restrict pstatus) {
	fd_t fdval;
	TRY {
		fdval = (fd_t)UNALIGNED_GET((unsigned int const *)pointer);
	} EXCEPT {
		goto badobj;
	}
	return note_fd_t_value(printer, arg, fdval, pstatus);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_pollfd)(pformatprinter printer, void *arg,
                           NCX void const *pointer,
                           unsigned int *__restrict pstatus) {
	struct pollfd *me;
	fd_t fd;
	TRY {
		me = (struct pollfd *)pointer;
		fd = me->fd;
	} EXCEPT {
		goto badobj;
	}
	return note_fd_t_value(printer, arg, fd, pstatus);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1)) ssize_t
NOTHROW(KCALL note_time_t_value)(pformatprinter printer, void *arg, time_t value) {
	struct tm t;
	localtime_r(&value, &t);
	return format_printf(printer, arg,
	                     "%.4u-%.2u-%.2uT%.2u:%.2u:%.2u",
	                     t.tm_year + 1900, t.tm_mon + 1, t.tm_mday,
	                     t.tm_hour, t.tm_min, t.tm_sec);
}

#if __SIZEOF_TIME_T__ == 4
#define NEED__note_timeu32_t
#define note_time_t _note_timeu32_t
#elif __SIZEOF_TIME_T__ == 8
#define NEED__note_timeu64_t
#define note_time_t _note_timeu64_t
#else /* __SIZEOF_TIME_T__ == 8 */
#error "Unsupported __SIZEOF_TIME_T__"
#endif /* __SIZEOF_TIME_T__ != 8 */

#if __SIZEOF_TIME32_T__ == 4
#define NEED__note_timeu32_t
#define note_time32_t _note_timeu32_t
#elif __SIZEOF_TIME32_T__ == 8
#define NEED__note_timeu64_t
#define note_time32_t _note_timeu64_t
#else /* __SIZEOF_TIME32_T__ == 8 */
#error "Unsupported __SIZEOF_TIME32_T__"
#endif /* __SIZEOF_TIME32_T__ != 8 */

#if __SIZEOF_TIME64_T__ == 4
#define NEED__note_timeu32_t
#define note_time64_t _note_timeu32_t
#elif __SIZEOF_TIME64_T__ == 8
#define NEED__note_timeu64_t
#define note_time64_t _note_timeu64_t
#else /* __SIZEOF_TIME64_T__ == 8 */
#error "Unsupported __SIZEOF_TIME64_T__"
#endif /* __SIZEOF_TIME64_T__ != 8 */

#ifdef __ARCH_HAVE_COMPAT
#if __ARCH_COMPAT_SIZEOF_TIME32_T == 4
#define NEED__note_timeu32_t
#define note_compat_time32_t _note_timeu32_t
#elif __ARCH_COMPAT_SIZEOF_TIME32_T == 8
#define NEED__note_timeu64_t
#define note_compat_time32_t _note_timeu64_t
#else /* __ARCH_COMPAT_SIZEOF_TIME32_T == 8 */
#error "Unsupported __ARCH_COMPAT_SIZEOF_TIME32_T"
#endif /* __ARCH_COMPAT_SIZEOF_TIME32_T != 8 */

#if __ARCH_COMPAT_SIZEOF_TIME64_T == 4
#define NEED__note_timeu32_t
#define note_compat_time64_t _note_timeu32_t
#elif __ARCH_COMPAT_SIZEOF_TIME64_T == 8
#define NEED__note_timeu64_t
#define note_compat_time64_t _note_timeu64_t
#else /* __ARCH_COMPAT_SIZEOF_TIME64_T == 8 */
#error "Unsupported __ARCH_COMPAT_SIZEOF_TIME64_T"
#endif /* __ARCH_COMPAT_SIZEOF_TIME64_T != 8 */
#endif /* __ARCH_HAVE_COMPAT */




#ifdef NEED__note_timeu32_t
#undef NEED__note_timeu32_t
PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL _note_timeu32_t)(pformatprinter printer, void *arg,
                               NCX void const *pointer,
                               unsigned int *__restrict pstatus) {
	time_t tmval;
	TRY {
		tmval = (time_t)UNALIGNED_GET((uint32_t const *)pointer);
	} EXCEPT {
		goto badobj;
	}
	return note_time_t_value(printer, arg, tmval);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}
#endif /* NEED__note_timeu32_t */


#ifdef NEED__note_timeu64_t
#undef NEED__note_timeu64_t
PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL _note_timeu64_t)(pformatprinter printer, void *arg,
                               NCX void const *pointer,
                               unsigned int *__restrict pstatus) {
	time_t tmval;
	TRY {
		tmval = (time_t)UNALIGNED_GET((uint64_t const *)pointer);
	} EXCEPT {
		goto badobj;
	}
	return note_time_t_value(printer, arg, tmval);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}
#endif /* NEED__note_timeu64_t */


PRIVATE NONNULL((1, 5)) ssize_t
NOTHROW(KCALL note_timespec_value)(pformatprinter printer, void *arg,
                                   time_t tv_sec, syscall_ulong_t tv_nsec,
                                   unsigned int *__restrict pstatus) {
	ssize_t result, temp;
	if unlikely(tv_nsec >= NSEC_PER_SEC)
		goto badobj;
	result = note_time_t_value(printer, arg, tv_sec);
	if likely(result >= 0) {
		temp = format_printf(printer, arg, ".%.9" PRIu32, tv_nsec);
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}
	return result;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 5)) ssize_t
NOTHROW(KCALL note_timeval_value)(pformatprinter printer, void *arg,
                                  time_t tv_sec, syscall_ulong_t tv_usec,
                                  unsigned int *__restrict pstatus) {
	ssize_t result, temp;
	if unlikely(tv_usec >= USEC_PER_SEC)
		goto badobj;
	result = note_time_t_value(printer, arg, tv_sec);
	if likely(result >= 0) {
		temp = format_printf(printer, arg, ".%.6" PRIu32, tv_usec);
		if unlikely(temp < 0)
			return temp;
		result += temp;
	}
	return result;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}


#define DEFINE_TIMESTRUCT_NOTE(name, T, note_time_value, a, b)     \
	PRIVATE NONNULL((1, 4)) ssize_t                                \
	NOTHROW(KCALL name)(pformatprinter printer, void *arg,         \
	                    NCX void const *pointer,                   \
	                    unsigned int *__restrict pstatus) {        \
		T tv;                                                      \
		TRY {                                                      \
			memcpy(&tv, pointer, sizeof(tv));                      \
		} EXCEPT {                                                 \
			goto badobj;                                           \
		}                                                          \
		return note_time_value(printer, arg, tv.a, tv.b, pstatus); \
	badobj:                                                        \
		*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;                     \
		return 0;                                                  \
	}
#define note_timespec32 note___timespec32
#define note_timeval32  note___timeval32
#define note_timespec64 note___timespec64
#define note_timeval64  note___timeval64
DEFINE_TIMESTRUCT_NOTE(note___timespec32, struct __timespec32, note_timespec_value, tv_sec, tv_nsec)
DEFINE_TIMESTRUCT_NOTE(note___timeval32, struct __timeval32, note_timeval_value, tv_sec, tv_usec)
#ifdef __HAVE_TIMESPEC32_IS_TIMESPEC64
#define note___timespec64 note___timespec32
#else /* __HAVE_TIMESPEC32_IS_TIMESPEC64 */
DEFINE_TIMESTRUCT_NOTE(note___timespec64, struct __timespec64, note_timespec_value, tv_sec, tv_nsec)
#endif /* !__HAVE_TIMESPEC32_IS_TIMESPEC64 */

#ifdef __HAVE_TIMEVAL32_IS_TIMEVAL64
#define note___timeval64 note___timeval32
#else /* __HAVE_TIMEVAL32_IS_TIMEVAL64 */
DEFINE_TIMESTRUCT_NOTE(note___timeval64, struct __timeval64, note_timeval_value, tv_sec, tv_usec)
#endif /* !__HAVE_TIMEVAL32_IS_TIMEVAL64 */

#ifdef __ARCH_HAVE_COMPAT
#ifdef __HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC32
#define note_compat_timespec32 note_timespec32
#elif defined(__HAVE_COMPAT_TIMESPEC32_IS_TIMESPEC64)
#define note_compat_timespec32 note_timespec64
#else /* ... */
DEFINE_TIMESTRUCT_NOTE(note_compat_timespec32, struct compat_timespec32, note_timespec_value, tv_sec, tv_nsec)
#endif /* !... */

#ifdef __HAVE_COMPAT_TIMESPEC32_IS_COMPAT_TIMESPEC64
#define note_compat_timespec64 note_compat_timespec32
#elif defined(__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC32)
#define note_compat_timespec64 note_timespec32
#elif defined(__HAVE_COMPAT_TIMESPEC64_IS_TIMESPEC64)
#define note_compat_timespec64 note_timespec64
#else /* ... */
DEFINE_TIMESTRUCT_NOTE(note_compat_timespec64, struct compat_timespec64, note_timespec_value, tv_sec, tv_nsec)
#endif /* !... */

#ifdef __HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL32
#define note_compat_timeval32 note_timeval32
#elif defined(__HAVE_COMPAT_TIMEVAL32_IS_TIMEVAL64)
#define note_compat_timeval32 note_timeval64
#else /* ... */
DEFINE_TIMESTRUCT_NOTE(note_compat_timeval32, struct compat_timeval32, note_timeval_value, tv_sec, tv_usec)
#endif /* !... */

#ifdef __HAVE_COMPAT_TIMEVAL32_IS_COMPAT_TIMEVAL64
#define note_compat_timeval64 note_compat_timeval32
#elif defined(__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL32)
#define note_compat_timeval64 note_timeval32
#elif defined(__HAVE_COMPAT_TIMEVAL64_IS_TIMEVAL64)
#define note_compat_timeval64 note_timeval64
#else /* ... */
DEFINE_TIMESTRUCT_NOTE(note_compat_timeval64, struct compat_timeval64, note_timeval_value, tv_sec, tv_usec)
#endif /* !... */
#endif /* __ARCH_HAVE_COMPAT */


#if __SIZEOF_TIME_T__ == __SIZEOF_TIME64_T__
#define note_timespec note_timespec64
#define note_timeval  note_timeval64
#elif __SIZEOF_TIME_T__ == __SIZEOF_TIME32_T__
#define note_timespec note_timespec32
#define note_timeval  note_timeval32
#else /* __SIZEOF_TIME_T__ == ... */
#error "Unsupported `__SIZEOF_TIME_T__'"
#endif /* __SIZEOF_TIME_T__ != ... */


PRIVATE NONNULL((1)) ssize_t
NOTHROW(KCALL note_ktime_t_value)(pformatprinter printer, void *arg,
                                  ktime_t ktm, unsigned int *__restrict pstatus) {
	struct timespec tms;
	if (ktm == KTIME_NONBLOCK)
		return RAWPRINT("NONBLOCK");
	if (ktm == KTIME_INFINITE)
		return RAWPRINT("INFINITE");
	tms = ktime_to_timespec(ktm);
	return note_timespec(printer, arg, &tms, pstatus);
}

PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_ktime_t)(pformatprinter printer, void *arg,
                            NCX void const *pointer,
                            unsigned int *__restrict pstatus) {
	ktime_t tmval;
	TRY {
		tmval = (ktime_t)UNALIGNED_GET((__CRT_PRIVATE_UINT(__SIZEOF_KTIME_T__) const *)pointer);
	} EXCEPT {
		goto badobj;
	}
	return note_ktime_t_value(printer, arg, tmval, pstatus);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}







/* NOTE: This list must be sorted lexicographically ascending! */
PRIVATE struct obnote_entry const notes[] = {
#ifdef __ARCH_HAVE_COMPAT
	{ "__compat_time32_t", &note_compat_time32_t },
	{ "__compat_time64_t", &note_compat_time64_t },
#endif /* __ARCH_HAVE_COMPAT */
	{ "__fd_t", &note_fd_t },
	{ "__time_t", &note_time_t },
	{ "__time32_t", &note_time32_t },
	{ "__time64_t", &note_time64_t },
	{ "__timespec32", &note___timespec64 },
	{ "__timespec64", &note___timespec64 },
	{ "__timeval32", &note___timeval64 },
	{ "__timeval64", &note___timeval64 },
	{ "ansittydev", &note_mfile },
	{ "blkdev", &note_mfile },
	{ "chrdev", &note_mfile },
	{ "clnknode", &note_mfile },
#ifdef __ARCH_HAVE_COMPAT
	{ "compat_time32_t", &note_compat_time32_t },
	{ "compat_time64_t", &note_compat_time64_t },
	{ "compat_timespec32", &note_compat_timespec32 },
	{ "compat_timespec64", &note_compat_timespec64 },
	{ "compat_timeval32", &note_compat_timeval32 },
	{ "compat_timeval64", &note_compat_timeval64 },
#endif /* __ARCH_HAVE_COMPAT */
	{ "constdir", &note_mfile },
	{ "cpu", &note_cpu },
	{ "device", &note_mfile },
	{ "dirhandle", &note_dirhandle },
	{ "driver", &note_module },
	{ "driver_section", &note_module_section },
	{ "fd_t", &note_fd_t },
	{ "fdevnode", &note_mfile },
	{ "fdirent", &note_fdirent },
	{ "fdirnode", &note_mfile },
	{ "ffifonode", &note_mfile },
	{ "fifohandle", &note_filehandle },
	{ "filehandle", &note_filehandle },
	{ "flatdirnode", &note_mfile },
	{ "flatsuper", &note_flatsuper },
	{ "flnknode", &note_mfile },
	{ "fnode", &note_mfile },
	{ "fregnode", &note_mfile },
	{ "fsocknode", &note_mfile },
	{ "fsuper", &note_fsuper },
	{ "handle", &note_handle },
	{ "kbddev", &note_mfile },
	{ "ktime_t", &note_ktime_t },
	{ "mbnode", &note_mnode },
	{ "mfile", &note_mfile },
	{ "mfutex", &note_mfutex },
	{ "mfutexfd", &note_mfutexfd },
	{ "mkttydev", &note_mfile },
	{ "mman", &note_mman },
	{ "mnode", &note_mnode },
	{ "module", &note_module },
	{ "module_section", &note_module_section },
	{ "mousedev", &note_mfile },
	{ "mpart", &note_mpart },
	{ "nicdev", &note_mfile },
	{ "path", &note_path },
	{ "pollfd", &note_pollfd },
	{ "printnode", &note_mfile },
	{ "ptymaster", &note_mfile },
	{ "ptyslave", &note_mfile },
	{ "ramfs_dirnode", &note_mfile },
	{ "ramfs_super", &note_fsuper },
	{ "task", &note_task },
	{ "taskpid", &note_taskpid },
	{ "time_t", &note_time_t },
	{ "time32_t", &note_time32_t },
	{ "time64_t", &note_time64_t },
	{ "timespec32", &note_timespec32 },
	{ "timespec64", &note_timespec64 },
	{ "timespec", &note_timespec },
	{ "timeval32", &note_timeval32 },
	{ "timeval64", &note_timeval64 },
	{ "timeval", &note_timeval },
	{ "ttydev", &note_mfile },
	{ "userelf_module", &note_module },
	{ "userelf_module_section", &note_module_section },
	{ "videodev", &note_mfile },
};

PRIVATE WUNUSED ATTR_PURE NONNULL((1)) struct obnote_entry const *
NOTHROW(KCALL obnote_entry_byname)(char const *__restrict name) {
	unsigned int i;
	for (i = 0; i < lengthof(notes); ++i) {
		if (strcmp(notes[i].one_name, name) == 0)
			return &notes[i];
	}
	return NULL;
}



PRIVATE NONNULL((1, 4)) ssize_t
NOTHROW(KCALL note_handle)(pformatprinter printer, void *arg,
                           NCX void const *pointer,
                           unsigned int *__restrict pstatus) {
	static char const accmode[4][2] = {
		[IO_RDONLY]   = { 'r', 'o' },
		[IO_WRONLY]   = { 'w', 'r' },
		[IO_RDWR]     = { 'r', 'w' },
		[IO_RDWR_ALT] = { 'r', 'w' },
	};
	ssize_t result, temp;
	struct handle hand;
	struct handle *me = (struct handle *)pointer;
	TRY {
		memcpy(&hand, me, sizeof(struct handle));
	} EXCEPT {
		goto badobj;
	}
	if (!hand.h_data || !ADDR_ISKERN(hand.h_data))
		goto badobj;
	if (hand.h_type >= HANDLE_TYPE_COUNT)
		goto badobj;
	result = rawprint(accmode[hand.h_mode & IO_ACCMODE], 2);
	if unlikely(result < 0)
		goto done;
	if (hand.h_mode & IO_CLOEXEC)
		PRINT(",cx");
	if (hand.h_mode & IO_CLOFORK)
		PRINT(",cf");
	if (hand.h_mode & IO_APPEND)
		PRINT(",ap");
	if (hand.h_mode & IO_NONBLOCK)
		PRINT(",nb");
	if (hand.h_mode & IO_DSYNC)
		PRINT(",ds");
	if (hand.h_mode & IO_ASYNC)
		PRINT(",as");
	if (hand.h_mode & IO_DIRECT)
		PRINT(",d");
	PRINTF(":%s", handle_type_db.h_typename[hand.h_type]);
	/* Print handle-type-specific notes. */
	{
		struct obnote_entry const *ent;
		ent = obnote_entry_byname(handle_type_db.h_typename[hand.h_type]);
		if (ent) {
			PRINT(":");
			DO((*ent->one_cb)(printer, arg, hand.h_data, pstatus));
		}
	}
done:
	return result;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
err:
	return temp;
}


/* Print extended information (if available)
 * that   related   to  the   given  `name'.
 * @param: pstatus: [out] Set to one of `OBNOTE_PRINT_STATUS_*'.
 * @return: * :     The usual pformatprinter return value. */
PUBLIC NONNULL((1, 4, 5)) ssize_t
NOTHROW(KCALL obnote_print)(pformatprinter printer, void *arg,
                            NCX void const *pointer,
                            char const *__restrict name,
                            unsigned int *__restrict pstatus) {
	struct obnote_entry const *ent;
	ent = obnote_entry_byname(name);
	if (ent) {
		/* Found the note! */
		*pstatus = OBNOTE_PRINT_STATUS_SUCCESS;
		return (*ent->one_cb)(printer, arg, pointer, pstatus);
	}
	*pstatus = OBNOTE_PRINT_STATUS_BADNAME;
	return 0;
}


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_MODDBX_OBNOTE_C */
