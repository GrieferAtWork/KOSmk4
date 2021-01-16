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
#include <kernel/vm.h>
#include <kernel/vm/exec.h>
#include <kernel/vm/usermod.h>
#include <sched/cpu.h>
#include <sched/pid.h>
#include <sched/scheduler.h>
#include <sched/task.h>

#include <hybrid/align.h>

#include <sys/mmio.h>

#include <format-printer.h>
#include <inttypes.h>
#include <stddef.h>
#include <string.h>

#include "include/obnote.h"

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
	struct vm_execinfo_struct *execinfo;
	char const *exec_name = NULL;
	u16 exec_namelen      = 0;
	uintptr_t thread_flags;
	pid_t pid, tid;
	struct cpu *thread_cpu;
	unsigned int thread_cpu_id;
	TRY {
		REF struct directory_entry *dent;
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
		execinfo      = &FORVM(thread->t_mman, thisvm_execinfo);
		dent          = execinfo->ei_dent;
		if (dent) {
			if (dent->de_refcnt == 0)
				goto badobj;
			if (dent->de_heapsize < offsetof(struct directory_entry, de_name) +
			                        (dent->de_namelen + 1) * sizeof(char))
				goto badobj;
			exec_name    = dent->de_name;
			exec_namelen = dent->de_namelen;
			if (exec_namelen > 16)
				exec_namelen = 16;
			peekb(exec_name);
			peekb(exec_name + exec_namelen - 1);
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
		referenced_thread = thread->tp_thread.m_pointer;
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
		if (me->d_refcnt == 0)
			goto badobj;
		if (me->d_weakrefcnt == 0)
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
NOTHROW(KCALL note_driver)(pformatprinter printer, void *arg,
                           KERNEL CHECKED void const *pointer,
                           unsigned int *__restrict pstatus) {
	struct driver *me = (struct driver *)pointer;
	char const *driver_name;
	size_t driver_namelen;
	TRY {
		if (me->d_refcnt == 0)
			goto badobj;
		if (me->d_weakrefcnt == 0)
			goto badobj;
		driver_name = me->d_name;
		if (!ADDR_ISKERN(driver_name))
			goto badobj;
		driver_namelen = strlen(driver_name);
	} EXCEPT {
		goto badobj;
	}
	return (*printer)(arg, driver_name, driver_namelen);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_driver_section)(pformatprinter printer, void *arg,
                                   KERNEL CHECKED void const *pointer,
                                   unsigned int *__restrict pstatus) {
	struct driver_section *me = (struct driver_section *)pointer;
	char const *driver_name;
	size_t driver_namelen;
	char const *section_name;
	size_t section_namelen;
	TRY {
		struct driver *drv;
		ElfW(Word) section_name_offset;
		if (me->ds_refcnt == 0)
			goto badobj;
		drv = me->ds_module;
		if (!ADDR_ISKERN(drv))
			goto badobj;
		if (drv->d_refcnt == 0)
			goto badobj;
		if (drv->d_weakrefcnt == 0)
			goto badobj;
		driver_name = drv->d_name;
		if (!ADDR_ISKERN(driver_name))
			goto badobj;
		driver_namelen = strlen(driver_name);
		if (me->ds_index >= drv->d_shnum)
			goto badobj;
		if (!ADDR_ISKERN(drv->d_shdr))
			goto badobj;
		section_name_offset = drv->d_shdr[me->ds_index].sh_name;
		if (!ADDR_ISKERN(drv->d_shstrtab))
			goto badobj;
		if (!ADDR_ISKERN(drv->d_shstrtab_end))
			goto badobj;
		if (drv->d_shstrtab_end <= drv->d_shstrtab)
			goto badobj;
		if (section_name_offset >= (size_t)(drv->d_shstrtab_end - drv->d_shstrtab))
			goto badobj;
		section_name    = drv->d_shstrtab + section_name_offset;
		section_namelen = strlen(section_name);
	} EXCEPT {
		goto badobj;
	}
	return format_printf(printer, arg, "%$s!%$s",
	                     driver_namelen, driver_name,
	                     section_namelen, section_name);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}

#ifdef CONFIG_HAVE_USERMOD
PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_usermod)(pformatprinter printer, void *arg,
                            KERNEL CHECKED void const *pointer,
                            unsigned int *__restrict pstatus) {
	struct usermod *me = (struct usermod *)pointer;
	char const *usermod_name;
	size_t usermod_namelen;
	TRY {
		if (me->um_refcnt == 0)
			goto badobj;
		if (!ADDR_ISUSER(me->um_loadstart))
			goto badobj;
		if (me->um_loadstart >= me->um_loadend)
			goto badobj;
		if (!ADDR_ISUSER(me->um_loadend - 1))
			goto badobj;
		if (!ADDR_ISKERN(me->um_file))
			goto badobj;
		if (!me->um_fsname) {
			usermod_name    = NULL;
			usermod_namelen = 0;
		} else {
			if (!ADDR_ISKERN(me->um_fsname))
				goto badobj;
			usermod_name    = me->um_fsname->de_name;
			usermod_namelen = me->um_fsname->de_namelen;
			if (usermod_namelen > 16)
				usermod_namelen = 16;
			if (usermod_namelen) {
				peekb(usermod_name);
				peekb(usermod_name + usermod_namelen - 1);
			}
		}
	} EXCEPT {
		goto badobj;
	}
	return (*printer)(arg, usermod_name, usermod_namelen);
badobj:
	*pstatus = OBNOTE_PRINT_STATUS_BADOBJ;
	return 0;
}
#endif /* CONFIG_HAVE_USERMOD */

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_directory_entry)(pformatprinter printer, void *arg,
                                    KERNEL CHECKED void const *pointer,
                                    unsigned int *__restrict pstatus) {
	struct directory_entry *me = (struct directory_entry *)pointer;
	char const *dent_name;
	size_t dent_namelen;
	unsigned char dent_type;
	TRY {
		if (me->de_refcnt == 0)
			goto badobj;
		if (me->de_heapsize < offsetof(struct directory_entry, de_name) +
		                      (me->de_namelen + 1) * sizeof(char))
			goto badobj;
		dent_name    = me->de_name;
		dent_namelen = me->de_namelen;
		dent_type    = me->de_type;
		if (me->de_hash != directory_entry_hash(dent_name, dent_namelen))
			goto badobj;
		/* TODO: Verify `dent_type', and print its name.
		 *       as `reg' for `DT_REG', etc..., such that
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
		peekb(dev_name);
		peekb(dev_name + dev_namelen - 1);
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
		peekb(dev_name);
		peekb(dev_name + dev_namelen - 1);
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
	struct directory_entry *dent;
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
	temp = note_directory_entry(printer, arg, dent, pstatus);
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
                             KERNEL CHECKED struct directory_entry const *d,
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
	temp = note_directory_entry(printer, arg, d, pstatus);
	if unlikely(temp < 0)
		goto err;
	result += temp;
done:
	return result;
err:
	return temp;
}

PRIVATE NONNULL((1, 3, 4)) ssize_t
NOTHROW(KCALL note_vm)(pformatprinter printer, void *arg,
                       KERNEL CHECKED void const *pointer,
                       unsigned int *__restrict pstatus) {
	ssize_t result;
	struct vm *me = (struct vm *)pointer;
	struct path *exec_path;
	struct directory_entry *exec_dent;
	TRY {
		if (!IS_ALIGNED((uintptr_t)me, PAGEDIR_ALIGN))
			goto badobj;
		if (me->v_refcnt == 0)
			goto badobj;
		if (me->v_weakrefcnt == 0)
			goto badobj;
#ifdef ARCH_PAGEDIR_GETSET_USES_POINTER
		if (me->v_pdir_phys != (PHYS pagedir_t *)(uintptr_t)pagedir_translate(me))
			goto badobj;
#else /* ARCH_PAGEDIR_GETSET_USES_POINTER */
		if (me->v_pdir_phys != pagedir_translate(me))
			goto badobj;
#endif /* !ARCH_PAGEDIR_GETSET_USES_POINTER */
		exec_path = FORVM(me, thisvm_execinfo).ei_path;
		exec_dent = FORVM(me, thisvm_execinfo).ei_dent;
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
	if (me == &vm_kernel) {
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
	struct file *me = (struct file *)pointer;
	struct path *file_path;
	struct directory_entry *file_dent;
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


PRIVATE struct obnote_entry const notes[] = {
	{ "ansitty_device", &note_character_device },
	{ "basic_block_device", &note_block_device },
	{ "block_device", &note_block_device },
	{ "character_device", &note_character_device },
	{ "cpu", &note_cpu },
	{ "directory_entry", &note_directory_entry },
	{ "driver", &note_driver },
	{ "driver_section", &note_driver_section },
	{ "file", &note_file },
	/* TODO: `struct handle'                 (print the contents handle's /proc/self/fd-style link) */
	{ "keyboard_device", &note_character_device },
	{ "mouse_device", &note_character_device },
	{ "nic_device", &note_character_device },
	{ "oneshot_directory_file", &note_file },
	{ "path", &note_path },
	{ "pty_master", &note_character_device },
	{ "pty_slave", &note_character_device },
	{ "ttybase_device", &note_character_device },
	{ "task", &note_task },
	{ "taskpid", &note_taskpid },
#ifdef CONFIG_HAVE_USERMOD
	{ "usermod", &note_usermod },
#endif /* CONFIG_HAVE_USERMOD */
	{ "vm", &note_vm },
};


/* Print extended information (if available)
 * that related to the given `name'.
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
