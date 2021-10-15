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
#ifndef GUARD_MODDBX_OBNOTE_C
#define GUARD_MODDBX_OBNOTE_C 1
#define __WANT_MPART__mp_nodlsts
#define _KOS_SOURCE 1

/* DeBug eXtensions. */

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_DEBUGGER

/**/
#include <dev/block.h>
#include <dev/char.h>
#include <fs/file.h>
#include <fs/vfs.h>
#include <kernel/driver.h>
#include <kernel/except.h>
#include <kernel/execabi.h>
#include <kernel/heap.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/mpartmeta.h>
#include <kernel/mman/ramfile.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <compat/config.h>
#include <kos/exec/rtld.h>

#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "include/obnote.h"

/**/
#include "../core/memory/mman/module-userelf.h"

#ifndef ELF_ARCH_MAXSHSTRTAB_SIZ
#define ELF_ARCH_MAXSHSTRTAB_SIZ 65536
#endif /* !ELF_ARCH_MAXSHSTRTAB_SIZ */

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/rtld.h>
#endif /* __ARCH_HAVE_COMPAT */

DECL_BEGIN

#define DO(expr)                 \
	do {                         \
		if ((temp = (expr)) < 0) \
			goto err;            \
		result += temp;          \
	}	__WHILE0
#define RAWPRINT(str)     (*printer)(arg, str, COMPILER_STRLEN(str))
#define PRINT(str)        DO(RAWPRINT(str))
#define REPEAT(ch, count) DO(format_repeat(printer, arg, ch, count))
#define PRINTF(...)       DO(format_printf(printer, arg, __VA_ARGS__))

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


PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_task)(pformatprinter printer, void *arg,
                         KERNEL CHECKED void const *pointer,
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
			if (dent->de_refcnt == 0)
				goto badobj;
			if (dent->de_heapsize < offsetof(struct fdirent, de_name) +
			                        (dent->de_namelen + 1) * sizeof(char))
				goto badobj;
			exec_name    = dent->de_name;
			exec_namelen = dent->de_namelen;
			if (exec_namelen > 16)
				exec_namelen = 16;
			readmem(exec_name, exec_namelen * sizeof(char));
		}
		pid = task_getrootpid_of_s(thread);
		tid = task_getroottid_of_s(thread);
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

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_taskpid)(pformatprinter printer, void *arg,
                            KERNEL CHECKED void const *pointer,
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
		ns = thread->tp_pidns;
		if (!ns || !ADDR_ISKERN(ns))
			goto badobj;
		ind = ns->pn_indirection;
		expected_indirection = 0;
		for (;;) {
			ns = ns->pn_parent;
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
		tid = thread->tp_pids[ind];
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


PRIVATE bool
NOTHROW(FCALL verify_driver)(struct driver *__restrict me) {
	TRY {
		if (__driver_refcnt(me) == 0)
			goto badobj;
		if (__driver_weakrefcnt(me) == 0)
			goto badobj;
		if (!ADDR_ISKERN(me->d_name))
			goto badobj;
	} EXCEPT {
		goto badobj;
	}
	return true;
badobj:
	return false;
}

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_module)(pformatprinter printer, void *arg,
                           KERNEL CHECKED void const *pointer,
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
		if (me->md_ops->mo_free == &_driver_free) {
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
			module_name    = me->md_fsname->de_name;
			module_namelen = me->md_fsname->de_namelen;
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
		*(void **)&pdyn__userelf_module_free = driver_dlsym_global("_userelf_module_free");
	return pdyn__userelf_module_free;
}



PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_module_section)(pformatprinter printer, void *arg,
                                   KERNEL CHECKED void const *pointer,
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
			if (ops->mo_free == &_driver_free) {
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
					module_name    = mod->md_fsname->de_name;
					module_namelen = mod->md_fsname->de_namelen;
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

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_fdirent)(pformatprinter printer, void *arg,
                            KERNEL CHECKED void const *pointer,
                            unsigned int *__restrict pstatus) {
	struct fdirent *me = (struct fdirent *)pointer;
	char const *dent_name;
	size_t dent_namelen;
	unsigned char dent_type;
	TRY {
		if (me->de_refcnt == 0)
			goto badobj;
		dent_name    = me->de_name;
		dent_namelen = me->de_namelen;
		if (me->de_heapsize < offsetof(struct fdirent, de_name) +
		                      (dent_namelen + 1) * sizeof(char))
			goto badobj;
		dent_type    = me->de_type;
		if (me->de_hash != fdirent_hash(dent_name, dent_namelen))
			goto badobj;
		readmem(dent_name, dent_namelen * sizeof(char));
		/* TODO: Verify  `dent_type',  and  print  its  name.
		 *       as  `reg'  for `DT_REG',  etc...,  such that
		 *       the actual string printed is something like:
		 *       `reg:init' */
		(void)dent_type;
	} EXCEPT {
		goto badobj;
	}
	return (*printer)(arg, dent_name, dent_namelen);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_character_device)(pformatprinter printer, void *arg,
                                     KERNEL CHECKED void const *pointer,
                                     unsigned int *__restrict pstatus) {
	struct character_device *me = (struct character_device *)pointer;
	char const *dev_name;
	size_t dev_namelen;
	TRY {
		if (me->cd_refcnt == 0)
			goto badobj;
		if (me->cd_heapsize < sizeof(struct character_device))
			goto badobj;
		if (!verify_driver(me->cd_type.ct_driver))
			goto badobj;
		dev_name    = me->cd_name;
		dev_namelen = strnlen(me->cd_name, COMPILER_LENOF(me->cd_name));
		readmem(dev_name, dev_namelen * sizeof(char));
	} EXCEPT {
		goto badobj;
	}
	return (*printer)(arg, dev_name, dev_namelen);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_block_device)(pformatprinter printer, void *arg,
                                 KERNEL CHECKED void const *pointer,
                                 unsigned int *__restrict pstatus) {
	struct block_device *me = (struct block_device *)pointer;
	char const *dev_name;
	size_t dev_namelen;
	TRY {
		if (me->bd_refcnt == 0)
			goto badobj;
		if (me->bd_heapsize < sizeof(struct block_device))
			goto badobj;
		dev_name    = me->bd_name;
		dev_namelen = strnlen(me->bd_name, COMPILER_LENOF(me->bd_name));
		readmem(dev_name, dev_namelen * sizeof(char));
	} EXCEPT {
		goto badobj;
	}
	return (*printer)(arg, dev_name, dev_namelen);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_cpu)(pformatprinter printer, void *arg,
                        KERNEL CHECKED void const *pointer,
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

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_path_impl)(pformatprinter printer, void *arg,
                              KERNEL CHECKED void const *pointer,
                              unsigned int *__restrict pstatus,
                              bool want_root_directory_slash) {
	ssize_t temp, result;
	struct path *me = (struct path *)pointer;
	struct path *parent_path = NULL;
	struct fdirent *dent;
	TRY {
		if (me->p_refcnt == 0)
			goto badobj;
		if (me->p_vfs == NULL || !ADDR_ISKERN(me->p_vfs))
			goto badobj;
		parent_path = me->p_parent;
		if (parent_path && !ADDR_ISKERN(parent_path))
			goto badobj;
		if ((parent_path == NULL) != (me == me->p_vfs))
			goto badobj;
		if (me->p_vfs->p_refcnt == 0)
			goto badobj;
		dent = me->p_dirent;
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
	temp = note_fdirent(printer, arg, dent, pstatus);
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

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_path)(pformatprinter printer, void *arg,
                         KERNEL CHECKED void const *pointer,
                         unsigned int *__restrict pstatus) {
	return note_path_impl(printer, arg, pointer, pstatus, true);
}

PRIVATE NONNULL((1, 4, 5)) ssize_t
NOTHROW(KCALL note_pathpair)(pformatprinter printer, void *arg,
                             KERNEL CHECKED struct path const *p,
                             KERNEL CHECKED struct fdirent const *d,
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
	temp = note_fdirent(printer, arg, d, pstatus);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_mman)(pformatprinter printer, void *arg,
                         KERNEL CHECKED void const *pointer,
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
		if (me->mm_pagedir_p != (PHYS pagedir_t *)(uintptr_t)pagedir_translate(me))
			goto badobj;
#else /* ARCH_PAGEDIR_GETSET_USES_POINTER */
		if (me->mm_pagedir_p != pagedir_translate(me))
			goto badobj;
#endif /* !ARCH_PAGEDIR_GETSET_USES_POINTER */
		exec_path = FORMMAN(me, thismman_execinfo).mei_path;
		exec_dent = FORMMAN(me, thismman_execinfo).mei_dent;
		if (!exec_dent)
			exec_path = NULL;
		else {
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

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_file)(pformatprinter printer, void *arg,
                         KERNEL CHECKED void const *pointer,
                         unsigned int *__restrict pstatus) {
	ssize_t result;
	struct filehandle *me = (struct filehandle *)pointer;
	struct path *file_path;
	struct fdirent *file_dent;
	TRY {
		if (me->f_refcnt == 0)
			goto badobj;
		if (!me->f_node || !ADDR_ISKERN(me->f_node))
			goto badobj;
		file_path = me->f_path;
		file_dent = me->f_dirent;
		if (!file_dent)
			file_path = NULL;
		else {
			if (!ADDR_ISKERN(file_dent))
				goto badobj;
			if (file_path && !ADDR_ISKERN(file_path))
				goto badobj;
		}
	} EXCEPT {
		goto badobj;
	}
	if (file_dent) {
		result = note_pathpair(printer, arg,
		                       file_path,
		                       file_dent,
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
		result = RTLD_LIBDL;
#ifdef __ARCH_HAVE_COMPAT
	} else if (self == &compat_execabi_system_rtld_file.mrf_file) {
		result = COMPAT_RTLD_LIBDL;
#endif /* __ARCH_HAVE_COMPAT */
#ifdef CONFIG_DEBUG_HEAP
	} else if (self == &mfile_dbgheap) {
		result = "[dbgheap]";
#endif /* CONFIG_DEBUG_HEAP */
	} else if (self == &mfile_zero) {
		result = "[/dev/zero]";
	} else if (self >= mfile_anon && self < COMPILER_ENDOF(mfile_anon)) {
		result = buf;
		sprintf(buf, "[/dev/zero:anon:%u]", (unsigned int)(self - mfile_anon));
	} else if (self == &mfile_ndef) {
		result = "[undef]";
	} else if (self == &mfile_phys) {
		result = "[/dev/mem]";
	} else if (ops >= mfile_anon_ops && ops < COMPILER_ENDOF(mfile_anon_ops)) {
		result = buf;
		sprintf(buf, "[?/dev/zero:anon:%u]", (unsigned int)(ops - mfile_anon_ops));
	} else if (ops == &mfile_ndef_ops) {
		result = "[?undef]";
	}
	return result;
}


PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_mnode)(pformatprinter printer, void *arg,
                          KERNEL CHECKED void const *pointer,
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
			if (!file_dent)
				file_path = NULL;
			else {
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
mpart_tree_extract_name(KERNEL CHECKED struct mpart *self,
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
	return true;
badobj:
	return false;
}

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_mfile)(pformatprinter printer, void *arg,
                          KERNEL CHECKED void const *pointer,
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
			PRINT("??" "?");
		}
	}
	return result;
err:
	return temp;
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}


PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_mpart)(pformatprinter printer, void *arg,
                          KERNEL CHECKED void const *pointer,
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
		for (i = 0; i < COMPILER_LENOF(me->_mp_nodlsts); ++i) {
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


PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_mfutex)(pformatprinter printer, void *arg,
                           KERNEL CHECKED void const *pointer,
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
			for (i = 0; i < COMPILER_LENOF(part->_mp_nodlsts); ++i) {
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



PRIVATE struct obnote_entry const notes[] = {
	{ "ansitty_device", &note_character_device },
	{ "basic_block_device", &note_block_device },
	{ "block_device", &note_block_device },
	{ "character_device", &note_character_device },
	{ "cpu", &note_cpu },
	{ "dirhandle", &note_file },
	{ "driver", &note_module },
	{ "driver_section", &note_module_section },
	{ "fdirent", &note_fdirent },
	{ "filehandle", &note_file },
	/* TODO: `struct handle'                 (print the contents handle's /proc/self/fd-style link) */
	{ "keyboard_device", &note_character_device },
	{ "mbnode", &note_mnode },
	{ "mfile", &note_mfile },
	{ "mfutex", &note_mfutex },
	{ "mman", &note_mman },
	{ "mnode", &note_mnode },
	{ "module", &note_module },
	{ "module_section", &note_module_section },
	{ "mouse_device", &note_character_device },
	{ "mpart", &note_mpart },
	{ "nic_device", &note_character_device },
	{ "path", &note_path },
	{ "pty_master", &note_character_device },
	{ "pty_slave", &note_character_device },
	{ "task", &note_task },
	{ "taskpid", &note_taskpid },
	{ "ttybase_device", &note_character_device },
	{ "userelf_module", &note_module },
	{ "userelf_module_section", &note_module_section },
};


/* Print extended information (if available)
 * that   related   to  the   given  `name'.
 * @param: pstatus: [out] Set to one of `OBNOTE_PRINT_STATUS_*'.
 * @return: * :     The usual pformatprinter return value. */
PUBLIC NONNULL((1, 3, 4, 5)) ssize_t
NOTHROW(KCALL obnote_print)(pformatprinter printer, void *arg,
                            KERNEL CHECKED void const *pointer,
                            char const *__restrict name,
                            unsigned int *__restrict pstatus) {
	size_t i;
	for (i = 0; i < COMPILER_LENOF(notes); ++i) {
		if (strcmp(notes[i].one_name, name) == 0) {
			/* Found the note! */
			*pstatus = OBNOTE_PRINT_STATUS_SUCCESS;
			return (*notes[i].one_cb)(printer, arg, pointer, pstatus);
		}
	}
	*pstatus = OBNOTE_PRINT_STATUS_BADNAME;
	return 0;
}


DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_MODDBX_OBNOTE_C */
