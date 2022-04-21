/* Copyright (c) 2019-2022 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2022 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_MODPROCFS_FILES_C
#define GUARD_MODPROCFS_FILES_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _BSD_SOURCE 1 /* strmode() */

#include <kernel/compiler.h>

#include <kernel/driver.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/notify.h>
#include <kernel/fs/path.h>
#include <kernel/fs/super.h>
#include <kernel/handle.h>
#include <kernel/malloc.h>
#include <kernel/memory.h>
#include <kernel/mman.h>
#include <kernel/mman/cc.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/futexfd.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/mpart.h>
#include <kernel/mman/stat.h>
#include <kernel/mman/unmapped.h>
#include <kernel/pipe.h>
#include <kernel/uname.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/scheduler.h>
#include <sched/task.h> /* task_start_default_flags */
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/host.h>
#include <hybrid/overflow.h>
#include <hybrid/sched/preemption.h>
#include <hybrid/unaligned.h>

#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/exec/elf.h>
#include <kos/ioctl/leaks.h>
#include <network/socket.h>

#include <assert.h>
#include <elf.h>
#include <format-printer.h>
#include <inttypes.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unicode.h>

#include <libcmdline/encode.h>

#if defined(__x86_64__) || defined(__i386__)
#include <sched/x86/iopl.h>
#include <sched/x86/eflags-mask.h>
#endif /* __x86_64__ || __i386__ */

/**/
#include "procfs.h"

/* Implementations for I/O on static procfs files (iow: kernel config files) */

#define print(p, len) (*printer)(arg, p, len)
#define printf(...)   format_printf(printer, arg, __VA_ARGS__)
#define PRINT(str)    print(str, COMPILER_STRLEN(str))

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

INTDEF NOBLOCK ATTR_CONST WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL nameof_special_file)(struct mfile *__restrict self);


/* Create forward declarations. (Prevent declaration errors below) */
#define MKDIR_BEGIN(symbol_name, perm) \
	INTDEF struct constdir symbol_name;
#define MKREG_RO(symbol_name, perm, printer)                                          \
	INTDEF void KCALL printer(pformatprinter printer, void *arg, pos_t offset_hint); \
	INTDEF struct procfs_regfile symbol_name;
#define MKREG_RW(symbol_name, perm, printer, writer)                                  \
	INTDEF void KCALL printer(pformatprinter printer, void *arg, pos_t offset_hint); \
	INTDEF void KCALL writer(USER CHECKED void const *buf, size_t bufsize);           \
	INTDEF struct procfs_regfile symbol_name;
#define MKREG_CONSTSTR(symbol_name, perm, string_ptr) \
	INTDEF struct procfs_txtfile symbol_name;
#define MKLNK(symbol_name, perm, readlink)            \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL          \
	readlink(struct flnknode *__restrict self,        \
	         USER CHECKED /*utf-8*/ char *buf,        \
	         size_t bufsize) THROWS(E_SEGFAULT, ...); \
	INTDEF struct flnknode symbol_name;
#include "procfs.def"


PRIVATE NONNULL((1)) ssize_t KCALL
print_size_with_unit(pformatprinter printer, void *arg, uint64_t sizeval) {
	char const *unit;
	if (sizeval >= 1024 * 1024 * 1024) {
		sizeval = CEILDIV(sizeval, 1024 * 1024 * 1024);
		unit    = "GiB";
	} else if (sizeval >= 1024 * 1024) {
		sizeval = CEILDIV(sizeval, 1024 * 1024);
		unit    = "MiB";
	} else if (sizeval >= 1024) {
		sizeval = CEILDIV(sizeval, 1024);
		unit    = "KiB";
	} else {
		unit = "b";
	}
	return format_printf(printer, arg, "%" PRIu64 "%s", sizeval, unit);
}





/************************************************************************/
/* /proc/self                                                           */
/************************************************************************/
INTERN WUNUSED NONNULL((1)) size_t KCALL
procfs_self_printer(struct flnknode *__restrict UNUSED(self),
                    USER CHECKED /*utf-8*/ char *buf, size_t bufsize)
		THROWS(E_SEGFAULT, ...) {
	return snprintf(buf, bufsize, "%" PRIuN(__SIZEOF_PID_T__), task_getpid());
}


/************************************************************************/
/* /proc/thread-self                                                    */
/************************************************************************/
INTERN WUNUSED NONNULL((1)) size_t KCALL
procfs_threadself_printer(struct flnknode *__restrict UNUSED(self),
                          USER CHECKED /*utf-8*/ char *buf, size_t bufsize)
		THROWS(E_SEGFAULT, ...) {
	return snprintf(buf, bufsize, "%" PRIuN(__SIZEOF_PID_T__) "/task/"
	                              "%" PRIuN(__SIZEOF_PID_T__),
	                task_getpid(), task_gettid());
}


/************************************************************************/
/* /proc/cmdline                                                        */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_cmdline_printer(pformatprinter printer, void *arg,
                       pos_t UNUSED(offset_hint)) {
	cmdline_encode(printer, arg, kernel_driver.d_argc, kernel_driver.d_argv);
	(*printer)(arg, "\n", 1);
}


/************************************************************************/
/* /proc/filesystems                                                    */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_filesystems_printer(pformatprinter printer, void *arg,
                           pos_t UNUSED(offset_hint)) {
	REF struct ffilesys *iter;
	iter = ffilesys_next(NULL);
	while (iter) {
		FINALLY_DECREF_UNLIKELY(iter);

		/* Print the filesystem type name in 1 of 2 ways:
		 *     - "        <name>\n"
		 *     - "nodev   <name>\n" */
		PRIVATE char const prefix[2][9] = {
			[0] = "        ",
			[1] = "nodev   ",
		};
		char const *used_prefix;
#if FFILESYS_F_NODEV == 1
		used_prefix = prefix[iter->ffs_flags & FFILESYS_F_NODEV];
#else /*FFILESYS_F_NODEV == 1 */
		used_prefix = prefix[(iter->ffs_flags & FFILESYS_F_NODEV) ? 1 : 0];
#endif /* FFILESYS_F_NODEV != 1 */

		/* Print the info-line */
		if (printf("%s%s\n", used_prefix, iter->ffs_name) < 0)
			break;

		/* Load the next filesystem type. */
		iter = ffilesys_next(iter);
	}
}


/************************************************************************/
/* /proc/mounts                                                         */
/************************************************************************/
INTERN WUNUSED NONNULL((1)) size_t KCALL
procfs_mounts_printer(struct flnknode *__restrict UNUSED(self),
                      USER CHECKED /*utf-8*/ char *buf, size_t bufsize)
		THROWS(E_SEGFAULT, ...) {
	return snprintf(buf, bufsize, "%" PRIuN(__SIZEOF_PID_T__) "/mounts", task_getpid());
}




/************************************************************************/
/* /proc/modules                                                        */
/************************************************************************/

/* Check if `dependency' is a dependency of `self' */
PRIVATE NOBLOCK WUNUSED NONNULL((1, 2)) bool
NOTHROW(FCALL driver_depends_on)(struct driver *self,
                                 struct driver *dependency) {
	size_t i;
	for (i = 0; i < self->d_depcnt; ++i) {
		if (axref_ptr(&self->d_depvec[i]) == dependency)
			return true;
	}
	return false;
}

INTERN NONNULL((1)) void KCALL
procfs_modules_printer(pformatprinter printer, void *arg,
                       pos_t UNUSED(offset_hint)) {
	bool show_pointers = capable(CAP_SYS_MODULE);
	REF struct driver_loadlist *ll;
	size_t i, j;
	ll = get_driver_loadlist();
	FINALLY_DECREF_UNLIKELY(ll);
	for (i = 0; i < ll->dll_count; ++i) {
		uintptr_t state;
		bool got_something;
		REF struct driver *drv = ll->dll_drivers[i];
		if (!tryincref(drv))
			continue;
		FINALLY_DECREF_UNLIKELY(drv);
		printf("%s %" PRIuSIZ " %" PRIuPTR " ",
		       drv->d_name,
		       (size_t)(drv->md_loadmax - drv->md_loadmin) + 1,
		       /* Subtract 1 from refcnt because we're holding one ourselves! */
		       ATOMIC_READ(drv->md_refcnt) - 1);
		/* Print a list of all drivers that have dependencies on this one. */
		got_something = false;
		for (j = 0; j < ll->dll_count; ++j) {
			REF struct driver *other;
			other = ll->dll_drivers[j];
			if (!tryincref(other))
				continue;
			FINALLY_DECREF_UNLIKELY(other);
			if (!driver_depends_on(other, drv))
				continue;
			/* Found a driver which `drv' is a dependency of */
			printf("%s,", other->d_name);
			got_something = true;
		}
		if (drv == &kernel_driver) {
			PRINT("[permanent],");
			got_something = true;
		}
		if (!got_something)
			PRINT("-");
		state = ATOMIC_READ(drv->d_state);
		if (printf(" %s %#" PRIxPTR "\n",
		           state < DRIVER_STATE_LOADED
		           ? "Loading"
		           : state == DRIVER_STATE_LOADED
		             ? "Live"
		             : "Unloading",
		           show_pointers
		           ? drv->md_loadaddr
		           : 0) < 0)
			return;
	}
}




/************************************************************************/
/* /proc/uptime                                                         */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_uptime_printer(pformatprinter printer, void *arg,
                      pos_t UNUSED(offset_hint)) {
	ktime_t now, idle = 0;
	unsigned int i;
	now = ktime();

	/* Figure how much time out CPU's IDLE task has spent being active. */
	for (i = 0; i < cpu_count; ++i) {
		struct cpu *c   = cpu_vector[i];
		struct task *ci = &FORCPU(c, thiscpu_idle);
		ktime_t ci_active;
		/* FIXME: When `c' isn't currently online, its `this_activetime'
		 *        won't be updated. -- iow: offline CPUs look like  they
		 *        were active the entire time until they're brought back
		 *        online and are able to update their activetime field. */
#if __SIZEOF_POINTER__ >= __SIZEOF_KTIME_T__
		ci_active = ATOMIC_READ(FORTASK(ci, this_activetime));
#else /* __SIZEOF_POINTER__ >= __SIZEOF_KTIME_T__ */
		{
			preemption_flag_t was;
			preemption_pushoff(&was);
			if (c == THIS_CPU) {
				ci_active = FORTASK(ci, this_activetime);
			} else {
				unsigned int attempt;
				for (attempt = 0; attempt < 32; ++i) {
					COMPILER_READ_BARRIER();
					ci_active = FORTASK(ci, this_activetime);
					COMPILER_READ_BARRIER();
					if unlikely(ci_active <= now)
						break; /* Makes sense... */
					/* Maybe the other CPU is changing the variable right now? */
					preemption_tryyield_nopr();
				}
			}
			preemption_pop(&was);
		}
#endif /* __SIZEOF_POINTER__ < __SIZEOF_KTIME_T__ */
		idle += ci_active;
	}

	/* Print information */
	printf("%" PRIu64 ".%.2u "
	       "%" PRIu64 ".%.2u\n",
	       (uint64_t)(now / NSEC_PER_SEC),
	       (unsigned int)((now % NSEC_PER_SEC) / (NSEC_PER_SEC / 100)),
	       (uint64_t)(idle / NSEC_PER_SEC),
	       (unsigned int)((idle % NSEC_PER_SEC) / (NSEC_PER_SEC / 100)));
}




/************************************************************************/
/* /proc/kcore                                                          */
/************************************************************************/

#define kcore_ehdr_size sizeof(ElfW(Ehdr))
PRIVATE ElfW(Ehdr) const kcore_ehdr_template = {
	.e_ident = {
		[EI_MAG0]       = ELFMAG0,
		[EI_MAG1]       = ELFMAG1,
		[EI_MAG2]       = ELFMAG2,
		[EI_MAG3]       = ELFMAG3,
		[EI_CLASS]      = ELF_ARCH_CLASS,
		[EI_DATA]       = ELF_ARCH_DATA,
		[EI_VERSION]    = EV_CURRENT,
		[EI_OSABI]      = ELFOSABI_SYSV, /* XXX: Something just for KOS? */
		[EI_ABIVERSION] = 0,
	},
	.e_type      = ET_CORE,
	.e_machine   = ELF_ARCH_MACHINE,
	.e_version   = EV_CURRENT,
	.e_phoff     = kcore_ehdr_size,
	.e_ehsize    = kcore_ehdr_size,
	.e_phentsize = sizeof(ElfW(Phdr)),
	.e_phnum     = 0, /* Will be overwritten */
};

PRIVATE ssize_t KCALL
kcore_ehdr_print(pformatprinter printer, void *arg) {
	ElfW(Ehdr) ehdr;
	memcpy(&ehdr, &kcore_ehdr_template, sizeof(ElfW(Ehdr)));
	/* TODO */
	return (*printer)(arg, (char *)&ehdr, sizeof(ehdr));
}

INTERN NONNULL((1)) void KCALL
procfs_kcore_printer(pformatprinter printer, void *arg,
                     pos_t offset_hint) {
	/* ELF executable header */
	if (offset_hint < kcore_ehdr_size) {
		if (kcore_ehdr_print(printer, arg) < 0)
			return;
	} else {
		(*printer)(arg, NULL, kcore_ehdr_size);
	}


	/* TODO: Print a coredump for the kernel core itself */
	PRINT("TODO");
}



/************************************************************************/
/* /proc/kos/fs/allow-fs-oob                                            */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_kos_fs_allow_fs_oob_print(pformatprinter printer, void *arg,
                                 pos_t UNUSED(offset_hint)) {
	ProcFS_PrintBool(printer, arg, fsuper_allow_fs_oob);
}
INTERN void KCALL
procfs_kos_fs_allow_fs_oob_write(USER CHECKED void const *buf,
                                 size_t bufsize) {
	bool newval;
	newval = ProcFS_ParseBool(buf, bufsize);
	ATOMIC_WRITE(fsuper_allow_fs_oob, newval);
}



/************************************************************************/
/* /proc/kos/fs/nodes                                                   */
/************************************************************************/
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) ssize_t KCALL
print_fsuper_mounting_points(struct fsuper *__restrict self,
                             pformatprinter printer, void *arg) {
	REF struct path *myroot;
	ssize_t result = 0;
	bool is_first = true;
	REF struct pathmount *iter;
	REF struct pathmount *prev = NULL;
	size_t index = 0;
	myroot = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(myroot);
	fsuper_mounts_read(self);
	iter = LIST_FIRST(&self->fs_mounts);
	for (;;) {
		size_t num_destroyed;
		num_destroyed = 0;
		while (iter && !tryincref(iter)) {
			iter = LIST_NEXT(iter, pm_fsmount);
			++num_destroyed;
		}
		fsuper_mounts_endread(self);
		xdecref_unlikely(prev);
		TRY {
			if (num_destroyed != 0) {
				if (!is_first) {
					result = PRINT(",");
					if (result < 0)
						break;
				}
				is_first = false;
				index += num_destroyed;
				result = printf("<destroyed> (x%" PRIuSIZ ")", num_destroyed);
				if (result < 0)
					break;
			}
			if (!iter)
				break;
			if (!is_first) {
				result = PRINT(",");
				if (result < 0)
					break;
			}
			is_first = false;
			result   = path_print(iter, printer, arg, fs_atflags(0), myroot);
			if (result < 0)
				break;
			fsuper_mounts_read(self);
		} EXCEPT {
			xdecref_unlikely(iter);
			RETHROW();
		}
		prev = iter;
		if (!LIST_ISBOUND(iter, pm_fsmount)) {
			/* Find  the `index'th node in the global list.
			 * This is not failsafe (elements before `node'
			 * may have been removed, so `index' may not be
			 * correct), but it's better than nothing. */
			size_t i;
			iter = LIST_FIRST(&self->fs_mounts);
			for (i = 0; iter && i < index; ++i) {
				iter = LIST_NEXT(iter, pm_fsmount);
			}
			if (!iter) {
				fsuper_mounts_endread(self);
				iter = prev;
				break;
			}
		}
		iter = LIST_NEXT(iter, pm_fsmount);
		++index;
	}
	xdecref_unlikely(iter);
	if (is_first)
		result = PRINT("-");
	return result;
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2)) ssize_t KCALL
print_fnode_desc(struct fnode *__restrict self,
                 pformatprinter printer, void *arg) {
	refcnt_t refcnt;
	ssize_t result;
	char const *specname;
	char modename[12];
	mode_t mode;
	uintptr_t flags;
	mfile_tslock_acquire(self);
	refcnt = ATOMIC_READ(self->mf_refcnt);
	mode   = self->fn_mode;
	flags  = self->mf_flags;
	mfile_tslock_release(self);
	--refcnt;
	if (flags & MFILE_FN_GLOBAL_REF)
		--refcnt;

	/* Basic attribute information */
	strmode(mode, modename);
	result = format_printf(printer, arg,
	                       "%" PRIuSIZ "\t%s\t",
	                       refcnt, self->fn_super->fs_sys->ffs_name);
	if (result < 0)
		return result;
	result = print_fsuper_mounting_points(self->fn_super, printer, arg);
	if (result < 0)
		return result;
	strmode(mode, modename);
	result = format_printf(printer, arg,
	                       "\t%s\t"
	                       "%s,%c%c%c%c%c%c\t",
	                       modename,
	                       flags & MFILE_F_READONLY ? "ro" : "rw",
	                       flags & MFILE_FN_GLOBAL_REF ? 'g' : '-',
	                       flags & MFILE_F_DELETED ? 'D' : '-',
	                       flags & MFILE_F_ATTRCHANGED ? 'a' : '-',
	                       flags & MFILE_F_CHANGED ? 'c' : '-',
	                       flags & MFILE_F_PERSISTENT ? 'p' : '-',
	                       flags & MFILE_FN_ATTRREADONLY ? 'R' : '-');
	if (result < 0)
		return result;

	/* Generic file info. */
	specname = nameof_special_file(self);
	if (specname) {
		result = (*printer)(arg, specname, strlen(specname));
	} else {
		result = mfile_uprintlink(self, printer, arg);
	}
	if (result < 0)
		return result;
	return (*printer)(arg, "\n", 1);
}

INTERN NONNULL((1)) void KCALL
procfs_kos_fs_nodes_printer(pformatprinter printer, void *arg,
                            pos_t UNUSED(offset_hint)) {
	REF struct fnode *node;
	REF struct fnode *prev = NULL;
	size_t index = 0;
	fallnodes_acquire();
	node = LIST_FIRST(&fallnodes_list);
	for (;;) {
		size_t num_destroyed;
		num_destroyed = 0;
		while (node && !tryincref(node)) {
			node = LIST_NEXT(node, fn_allnodes);
			++num_destroyed;
		}
		fallnodes_release();
		xdecref_unlikely(prev);
		TRY {
			if (num_destroyed != 0) {
				index += num_destroyed;
				if (printf("<destroyed> (x%" PRIuSIZ ")\n", num_destroyed) < 0)
					break;
			}
			if (!node)
				break;
			if (print_fnode_desc(node, printer, arg) < 0)
				break;
			fallnodes_acquire();
		} EXCEPT {
			xdecref_unlikely(node);
			RETHROW();
		}
		prev = node;
		if (!LIST_ISBOUND(node, fn_allnodes)) {
			/* Find  the `index'th node in the global list.
			 * This is not failsafe (elements before `node'
			 * may have been removed, so `index' may not be
			 * correct), but it's better than nothing. */
			size_t i;
			node = LIST_FIRST(&fallnodes_list);
			for (i = 0; node && i < index; ++i) {
				node = LIST_NEXT(node, fn_allnodes);
			}
			if (!node) {
				fallnodes_release();
				node = prev;
				break;
			}
		}
		node = LIST_NEXT(node, fn_allnodes);
		++index;
	}
	xdecref_unlikely(node);
}



/************************************************************************/
/* /proc/kos/fs/stat                                                    */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_kos_fs_stat_printer(pformatprinter printer, void *arg,
                           pos_t UNUSED(offset_hint)) {
	size_t allnodes    = fallnodes_getsize();
	size_t allsuper    = fallsuper_getsize();
	size_t changesuper = fchangedsuper_getsize();
	printf("nodes:\t%" PRIuSIZ "\n"
	       "super:\t%" PRIuSIZ "\n"
	       "super (changed):\t%" PRIuSIZ "\n",
	       allnodes, allsuper, changesuper);
}



/************************************************************************/
/* /proc/kos/mm/kernel-stat                                             */
/************************************************************************/
struct mmk_stat: mman_statinfo {
	size_t mks_reserved; /* # of bytes mapped by reserved nodes. */
	size_t mks_prepared; /* # of bytes mapped by nodes w/ `MNODE_F_MPREPARED'. */
	size_t mks_krnpart;  /* # of bytes mapped by nodes w/ `MNODE_F_KERNPART'. */
	size_t mks_nosplit;  /* # of bytes mapped by nodes w/ `MNODE_F_NOSPLIT'. */
	size_t mks_nomerge;  /* # of bytes mapped by nodes w/ `MNODE_F_NOMERGE'. */
};

PRIVATE NOBLOCK NONNULL((1, 2)) void
NOTHROW(FCALL kernel_mnode_tree_stat)(struct mnode *__restrict node,
                                      struct mmk_stat info[2]) {
	struct mpart *part;
	size_t nodesize;
	unsigned int i;
again:
	nodesize = mnode_getsize(node);
	for (i = 0; i < 2; ++i) {
		struct mmk_stat *set = &info[i];
		if (i == 1)
			nodesize = 1; /* Count # of nodes */
		set->msi_size += nodesize;
		if (node->mn_flags & MNODE_F_MLOCK)
			set->msi_lock += nodesize;
		if ((node->mn_flags & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD)) == (MNODE_F_PEXEC | MNODE_F_PREAD))
			set->msi_nexe += nodesize;
		if ((node->mn_flags & (MNODE_F_PEXEC | MNODE_F_PWRITE | MNODE_F_PREAD)) == (MNODE_F_PWRITE | MNODE_F_PREAD))
			set->msi_ndat += nodesize;
		if (node->mn_flags & MNODE_F_MPREPARED)
			set->mks_prepared += nodesize;
		if (node->mn_flags & MNODE_F_KERNPART)
			set->mks_krnpart += nodesize;
		if (node->mn_flags & MNODE_F_NOSPLIT)
			set->mks_nosplit += nodesize;
		if (node->mn_flags & MNODE_F_NOMERGE)
			set->mks_nomerge += nodesize;
		part = node->mn_part;
		if likely(part != NULL) {
			uintptr_quarter_t state;
			if (mpart_isanon_atomic(part))
				set->msi_anon += nodesize;
			state = ATOMIC_READ(part->mp_state);
			if (state == MPART_ST_SWP || state == MPART_ST_SWP_SC)
				set->msi_swap += nodesize;
		} else {
			set->mks_reserved += nodesize;
		}
	}

	if (node->mn_mement.rb_lhs) {
		if (node->mn_mement.rb_rhs)
			kernel_mnode_tree_stat(node->mn_mement.rb_rhs, info);
		node = node->mn_mement.rb_lhs;
		goto again;
	}
	if (node->mn_mement.rb_rhs) {
		node = node->mn_mement.rb_rhs;
		goto again;
	}
}

INTERN NONNULL((1)) void KCALL
procfs_kos_mm_kernel_stat_printer(pformatprinter printer, void *arg,
                                  pos_t UNUSED(offset_hint)) {
	struct mmk_stat km_stat[2];

	/* Gather information. */
	bzero(km_stat, sizeof(km_stat));
	mman_lock_read(&mman_kernel);
	if (mman_kernel.mm_mappings)
		kernel_mnode_tree_stat(mman_kernel.mm_mappings, km_stat);
	mman_lock_endread(&mman_kernel);

	/* Print some stats about the kernel mman. */
	printf("mapped:   %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "locked:   %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "exec:     %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "data:     %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "anon:     %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "swap:     %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "reserved: %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "prepared: %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "krnpart:  %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "nosplit:  %" PRIuSIZ "\t%" PRIuSIZ "p\n"
	       "nomerge:  %" PRIuSIZ "\t%" PRIuSIZ "p\n",
	       km_stat[1].msi_size, km_stat[0].msi_size / PAGESIZE,
	       km_stat[1].msi_lock, km_stat[0].msi_lock / PAGESIZE,
	       km_stat[1].msi_nexe, km_stat[0].msi_nexe / PAGESIZE,
	       km_stat[1].msi_ndat, km_stat[0].msi_ndat / PAGESIZE,
	       km_stat[1].msi_anon, km_stat[0].msi_anon / PAGESIZE,
	       km_stat[1].msi_swap, km_stat[0].msi_swap / PAGESIZE,
	       km_stat[1].mks_reserved, km_stat[0].mks_reserved / PAGESIZE,
	       km_stat[1].mks_prepared, km_stat[0].mks_prepared / PAGESIZE,
	       km_stat[1].mks_krnpart, km_stat[0].mks_krnpart / PAGESIZE,
	       km_stat[1].mks_nosplit, km_stat[0].mks_nosplit / PAGESIZE,
	       km_stat[1].mks_nomerge, km_stat[0].mks_nomerge / PAGESIZE);
}



/************************************************************************/
/* /proc/kos/mm/kernel-maps                                             */
/************************************************************************/
struct maps_printer_data {
	pformatprinter   pd_printer; /* [1..1] The target printer. */
	void            *pd_arg;     /* [?..?] Argument for `pd_printer' */
	REF struct path *pd_root;    /* [0..1] Lazily initialized root directory of parent. */
	atflag_t         pd_atflags; /* [valid_if(pd_root)] AT_* flags */
};

INTDEF NONNULL((1)) ssize_t FCALL /* From "./files-perproc.c" */
maps_print_name(struct maps_printer_data *__restrict ctx,
                struct mfile *file, struct path *fspath,
                struct fdirent *fsname);

INTERN NONNULL((1)) void KCALL
procfs_kos_mm_kernel_maps_printer(pformatprinter printer, void *arg,
                                  pos_t UNUSED(offset_hint)) {
	struct maps_printer_data ctx;
	void *minaddr = (void *)0;
	require(CAP_SYS_MODULE);
	ctx.pd_printer = printer;
	ctx.pd_arg     = arg;
	ctx.pd_root    = NULL;
	RAII_FINALLY { xdecref_unlikely(ctx.pd_root); };
	for (;;) {
		struct mnode node;
		struct mnode_tree_minmax mima;
		REF struct mfile *file;
		pos_t part_minaddr;
again:
		mman_lock_read(&mman_kernel);
		mnode_tree_minmaxlocate(mman_kernel.mm_mappings, minaddr, (void *)-1, &mima);
		if (!mima.mm_min) {
			mman_lock_endread(&mman_kernel);
			break;
		}
		memcpy(&node, mima.mm_min, sizeof(struct mnode));
		if (!(node.mn_flags & MNODE_F_UNMAPPED)) {
			if (node.mn_part) {
				if (!mpart_lock_tryacquire(node.mn_part)) {
					incref(node.mn_part);
					mman_lock_endread(&mman_kernel);
					FINALLY_DECREF_UNLIKELY(node.mn_part);
					mpart_lock_waitfor(node.mn_part);
					goto again;
				}
				incref(node.mn_part);
			}
		} else {
			node.mn_part = NULL;
		}
		xincref(node.mn_fspath);
		xincref(node.mn_fsname);
		mman_lock_endread(&mman_kernel);
		part_minaddr = 0;
		file         = NULL;
		if (node.mn_part) {
			file         = incref(node.mn_part->mp_file);
			part_minaddr = mpart_getminaddr(node.mn_part);
			mpart_lock_release(node.mn_part);
		}
		FINALLY_XDECREF_UNLIKELY(node.mn_fsname);
		FINALLY_XDECREF_UNLIKELY(node.mn_fspath);
		FINALLY_XDECREF_UNLIKELY(node.mn_part);
		FINALLY_XDECREF_UNLIKELY(file);
		if (printf("%.8" PRIxPTR "-%.8" PRIxPTR " "     /* from-to */
		           "%c%c%c%c"                           /* [r-][w-][x-][sp] */
		           "%c%c%c%c%c%c%c ",                   /* [U-][P-][K-][H-][L-][S-][M-] */
		           node.mn_minaddr, node.mn_maxaddr,
		           node.mn_flags & MNODE_F_PREAD ? 'r' : '-',
		           node.mn_flags & MNODE_F_PWRITE ? 'w' : '-',
		           node.mn_flags & MNODE_F_PEXEC ? 'x' : '-',
		           node.mn_flags & MNODE_F_SHARED ? 's' : 'p',
		           node.mn_flags & MNODE_F_UNMAPPED ? 'U' : '-',
		           node.mn_flags & MNODE_F_MPREPARED ? 'P' : '-',
		           node.mn_flags & MNODE_F_KERNPART ? 'K' : '-',
		           node.mn_flags & MNODE_F_MHINT ? 'H' : '-',
		           node.mn_flags & MNODE_F_MLOCK ? 'L' : '-',
		           node.mn_flags & MNODE_F_NOSPLIT ? 'S' : '-',
		           node.mn_flags & MNODE_F_NOMERGE ? 'M' : '-'))
			return;
		if (node.mn_part != NULL) {
			if (printf("%.8" PRIxN(__SIZEOF_OFF64_T__) " ", /* offset */
			           node.mn_partoff + part_minaddr) < 0)
				return;
		}
		if (maps_print_name(&ctx, file, node.mn_fspath, node.mn_fsname) < 0)
			return;
		if (PRINT("\n") < 0)
			return;
		if (OVERFLOW_UADD((uintptr_t)node.mn_maxaddr, 1, (uintptr_t *)&minaddr))
			break;
	}
}




/************************************************************************/
/* /proc/kos/mm/stat                                                    */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_kos_mm_stat_printer(pformatprinter printer, void *arg,
                           pos_t UNUSED(offset_hint)) {
	size_t partcount = mpart_all_getsize();
	printf("mparts:\t%" PRIuSIZ "\n",
	       partcount);
}




/************************************************************************/
/* /proc/kos/mm/parts                                                   */
/************************************************************************/
PRIVATE ATTR_NOINLINE NONNULL((1, 2)) ssize_t KCALL
print_mpart_desc(struct mpart *__restrict self,
                 pformatprinter printer, void *arg) {
	ssize_t result;
	char const *specname;
	REF struct mfile *file;
	pos_t minaddr, maxaddr;
	uintptr_quarter_t state;
	uintptr_half_t flags;
	char const *statename;
	REF struct mman *firstcopy;
	bool has_mappings;
	bool has_multiple_mmans;
	refcnt_t refcnt;
	firstcopy = NULL;
	mpart_lock_acquire(self);
	refcnt  = ATOMIC_READ(self->mp_refcnt) - 1;
	minaddr = self->mp_minaddr;
	maxaddr = self->mp_maxaddr;
	state   = self->mp_state;
	flags   = self->mp_flags;
	file    = incref(self->mp_file);
	has_mappings = !LIST_EMPTY(&self->mp_copy) ||
	               !LIST_EMPTY(&self->mp_share);
	has_multiple_mmans = false;
	if (!LIST_EMPTY(&self->mp_copy)) {
		struct mnode *node;
		node = LIST_FIRST(&self->mp_copy);
		do {
			if (firstcopy) {
				if (!wasdestroyed(node->mn_mman)) {
					has_multiple_mmans = true;
					break;
				}
			} else if (tryincref(node->mn_mman)) {
				firstcopy = node->mn_mman;
			}
			node = LIST_NEXT(node, mn_link);
		} while (node);
	}
	mpart_lock_release(self);
	FINALLY_DECREF_UNLIKELY(file);
	FINALLY_XDECREF_UNLIKELY(firstcopy);

	switch (state) {
	case MPART_ST_VOID:
		statename = "void";
		break;
	case MPART_ST_SWP:
	case MPART_ST_SWP_SC:
		statename = "swap";
		break;
	case MPART_ST_MEM:
	case MPART_ST_MEM_SC:
		statename = "mem";
		break;
#ifdef LIBVIO_CONFIG_ENABLED
	case MPART_ST_VIO:
		statename = "vio";
		break;
#endif /* LIBVIO_CONFIG_ENABLED */
	default:
		statename = "?";
		break;
	}
	if (flags & MPART_F_GLOBAL_REF)
		--refcnt;
	result = format_printf(printer, arg,
	                       "%" PRIuSIZ "\t%s\t%.6" PRIx64 "-%.6" PRIx64 "\t",
	                       refcnt, statename, minaddr, maxaddr);
	if (result < 0)
		return result;
	result = print_size_with_unit(printer, arg, (size_t)((maxaddr - minaddr) + 1));
	if (result < 0)
		return result;

	/* Print flags */
	result = format_printf(printer, arg,
	                       "\t%c%c%c\t",
	                       (flags & MPART_F_GLOBAL_REF)
	                       ? ((ATOMIC_READ(file->mf_flags) & MFILE_F_PERSISTENT)
	                          ? 'P'  /* global+persistent */
	                          : 'g') /* global */
	                       : mfile_isanon(file)
	                         ? 'a' /* Anonymous */
	                         : '-',
	                       flags & MPART_F_CHANGED ? 'c' : '-',
	                       flags & MPART_F_MLOCK
	                       ? (flags & MPART_F_MLOCK_FROZEN ? 'L' : 'l')
	                       : '-');
	if (result < 0)
		return result;
	if (firstcopy == &mman_kernel) {
		result = (*printer)(arg, "[kernel]", 8);
	} else if (firstcopy && !has_multiple_mmans) {
		/* Print the main executable of the first mman with a copy-on-write mapping. */
		REF struct fdirent *exec_dent;
		REF struct path *exec_path;
		struct mexecinfo *info;
		info = &FORMMAN(firstcopy, thismman_execinfo);
		mman_lock_read(firstcopy);
		exec_dent = xincref(info->mei_dent);
		exec_path = xincref(info->mei_path);
		mman_lock_endread(firstcopy);
		FINALLY_XDECREF_UNLIKELY(exec_path);
		if unlikely(!exec_dent)
			goto print_no_exe;
		FINALLY_DECREF_UNLIKELY(exec_dent);
		if (exec_path) {
			REF struct path *myroot = fs_getroot(THIS_FS);
			FINALLY_DECREF_UNLIKELY(myroot);
			result = path_printent(exec_path, exec_dent->fd_name, exec_dent->fd_namelen,
			                       printer, arg, fs_atflags(0) | AT_PATHPRINT_INCTRAIL,
			                       myroot);
		} else if (exec_dent->fd_name[0] == '/') {
			result = (*printer)(arg, exec_dent->fd_name, exec_dent->fd_namelen);
		} else {
			result = format_printf(printer, arg, "?/%$s",
			                       (size_t)exec_dent->fd_namelen,
			                       exec_dent->fd_name);
		}
	} else {
print_no_exe:
		result = (*printer)(arg,
		                    has_multiple_mmans
		                    ? "[shared]"
		                    : has_mappings
		                      ? "[mapped]"
		                      : "[cached]",
		                    8);
	}
	if (result < 0)
		return result;
	result = (*printer)(arg, "\t", 1);
	if (result < 0)
		return result;
	specname = nameof_special_file(file);
	if (specname) {
		result = (*printer)(arg, specname, strlen(specname));
	} else {
		result = mfile_uprintlink(file, printer, arg);
	}
	if (result < 0)
		return result;
	return (*printer)(arg, "\n", 1);
}

INTERN NONNULL((1)) void KCALL
procfs_kos_mm_parts_printer(pformatprinter printer, void *arg,
                            pos_t UNUSED(offset_hint)) {
	REF struct mpart *part;
	REF struct mpart *prev = NULL;
	size_t index = 0;
	mpart_all_acquire();
	part = LIST_FIRST(&mpart_all_list);
	for (;;) {
		size_t num_destroyed;
		num_destroyed = 0;
		while (part && !tryincref(part)) {
			part = LIST_NEXT(part, mp_allparts);
			++num_destroyed;
		}
		mpart_all_release();
		xdecref_unlikely(prev);
		TRY {
			if (num_destroyed != 0) {
				index += num_destroyed;
				if (printf("<destroyed> (x%" PRIuSIZ ")\n", num_destroyed) < 0)
					break;
			}
			if (!part)
				break;
			if (print_mpart_desc(part, printer, arg) < 0)
				break;
			mpart_all_acquire();
		} EXCEPT {
			xdecref_unlikely(part);
			RETHROW();
		}
		prev = part;
		if (!LIST_ISBOUND(part, mp_allparts)) {
			/* Find  the `index'th part in the global list.
			 * This is not failsafe (elements before `part'
			 * may have been removed, so `index' may not be
			 * correct), but it's better than nothing. */
			size_t i;
			part = LIST_FIRST(&mpart_all_list);
			for (i = 0; part && i < index; ++i) {
				part = LIST_NEXT(part, mp_allparts);
			}
			if (!part) {
				mpart_all_release();
				part = prev;
				break;
			}
		}
		part = LIST_NEXT(part, mp_allparts);
		++index;
	}
	xdecref_unlikely(part);
}




/************************************************************************/
/* /proc/kos/kstat                                                      */
/************************************************************************/
/* This file contains static text describing the KOS system configuration. */
PRIVATE NONNULL((1, 3)) ssize_t KCALL
print_kernel_section_size(pformatprinter printer, void *arg,
                          char const *__restrict section_name) {
	size_t section_size;
	REF struct module_section *sect;
	sect = module_locksection(&kernel_driver, section_name);
	if (!sect)
		return 0;
	section_size = sect->ms_size;
	decref_unlikely(sect); /* More like *_nokill, but whatever... */

	/* Special case for .permman, which normally doesn't include the page directory size. */
	if (strcmp(section_name, ".permman") == 0)
		section_size += sizeof(pagedir_t);

	/* Print section size. */
	printf("%s:\t%" PRIuSIZ " (", section_name, section_size);
	print_size_with_unit(printer, arg, section_size);
	return PRINT(")\n");
}

/* Internal structures for used by `kernel_symbol_table' (from `/kos/kernel/core/fs/driver.c') */
struct kernel_syment {
	char const *ks_name; /* [0..1] Symbol name (NULL for sentinel) */
	void       *ks_addr; /* Symbol address */
	u32         ks_size; /* Symbol size */
	u32         ks_hash; /* Symbol hash (s.a. `elf_symhash()') */
};
struct kernel_symtab {
	uintptr_t                                     ds_mask;  /* Hash mask. */
	COMPILER_FLEXIBLE_ARRAY(struct kernel_syment, ds_list); /* Symbol map. */
};

PRIVATE NOBLOCK ATTR_PURE WUNUSED size_t
NOTHROW(FCALL get_kernel_symbol_count)(void) {
	size_t result;
	static size_t symcount = 0;
	result = symcount;
	if (result == 0) {
		size_t i;
		struct kernel_symtab *ksymtab;
		ksymtab = (struct kernel_symtab *)driver_dlsym(&kernel_driver, "kernel_symbol_table");
		if likely(ksymtab) {
			for (i = 0; i <= ksymtab->ds_mask; ++i) {
				if (ksymtab->ds_list[i].ks_name != NULL)
					++result;
			}
		}
		symcount = result;
	}
	return result;
}

INTERN NONNULL((1)) void KCALL
procfs_kos_kstat_printer(pformatprinter printer, void *arg,
                         pos_t UNUSED(offset_hint)) {
	static char const section_names[][18] = {
		".pertask", ".permman", ".percpu", ".text", ".rodata",
		".gcc_except_table", ".eh_frame", ".data", ".bss",
		".dbg.hooks", ".shstrtab", ".debug_line", ".debug_info",
		".debug_aranges", ".debug_abbrev", ".debug_str",
		".debug_ranges", ".debug_loc",
	};
	unsigned int i;
	for (i = 0; i < COMPILER_LENOF(section_names); ++i) {
		if (print_kernel_section_size(printer, arg, section_names[i]) < 0)
			return;
	}
	printf("symbols:\t%" PRIuSIZ "\n", get_kernel_symbol_count());
}




/************************************************************************/
/* /proc/kos/meminfo                                                    */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_kos_meminfo_printer(pformatprinter printer, void *arg,
                           pos_t UNUSED(offset_hint)) {
	size_t i;
	for (i = 0; i < minfo.mb_bankc; ++i) {
		struct pmembank *bank;
		bank = &minfo.mb_banks[i];
		if (bank->mb_type == PMEMBANK_TYPE_UNDEF)
			continue;
		printf("%" PRIpN(__SIZEOF_PHYSADDR_T__) "-"
		       "%" PRIpN(__SIZEOF_PHYSADDR_T__) "\t"
		       "%-11s\t",
		       PMEMBANK_MINADDR(*bank), PMEMBANK_MAXADDR(*bank),
		       bank->mb_type < PMEMBANK_TYPE_COUNT ? pmembank_type_names[bank->mb_type] : "?");
		print_size_with_unit(printer, arg, (uint64_t)PMEMBANK_SIZE(*bank));
		if (PRINT("\n") < 0)
			return;
	}
}




/************************************************************************/
/* /proc/kos/raminfo                                                    */
/************************************************************************/
PRIVATE NONNULL((1)) ssize_t KCALL
print_size_with_unit_and_percent(pformatprinter printer, void *arg,
                                 uint64_t count, uint64_t total) {
	ssize_t result;
	unsigned int usage_percent;
	result = print_size_with_unit(printer, arg, count);
	if (result < 0)
		return result;
	usage_percent = 0;
	if (total != 0)
		usage_percent = (unsigned int)(((u64)count * 100 * 100) / total);
	/* Print usage percent (also include `count' represented in pages) */
	return printf("\t%" PRIu64 "p\t(%u.%.2u%%)",
	              count / PAGESIZE,
	              usage_percent / 100,
	              usage_percent % 100);
}

struct mpart_ram_usage {
	uint64_t mru_ram;     /* Total # of bytes associated with INCORE mem-parts. */
	uint64_t mru_locked;  /* Total # of bytes associated with LOCKED mem-parts. */
	uint64_t mru_file;    /* Sum of INCORE parts that aren't anonymous. */
	uint64_t mru_kernel;  /* Sum of INCORE parts that are exclusively mapped by the kernel. */
	uint64_t mru_private; /* Sum of INCORE parts that are are anonymous and mapped (and don't appear in `mru_kernel') */
	uint64_t mru_shared;  /* Sum of INCORE parts that are aren't anonymous and mapped (and don't appear in `mru_kernel') */
};

PRIVATE NONNULL((1)) void KCALL
gather_mpart_ramusage(struct mpart_ram_usage *__restrict info) {
	struct mpart *iter;
again:
	bzero(info, sizeof(*info));
	mpart_all_acquire();
	LIST_FOREACH (iter, &mpart_all_list, mp_allparts) {
		if (!tryincref(iter))
			continue; /* Skip */
		if (!mpart_lock_tryacquire(iter)) {
			mpart_all_release();
			FINALLY_DECREF_UNLIKELY(iter);
			mpart_lock_waitfor(iter);
			goto again;
		}
		if (MPART_ST_INCORE(iter->mp_state)) {
			struct mnode *exclusive_node;
			size_t partsize = mpart_getsize(iter);
			info->mru_ram += partsize;
			if (iter->mp_flags & MPART_F_MLOCK)
				info->mru_locked += partsize;
			if (!mpart_isanon(iter))
				info->mru_file += partsize;
			exclusive_node = LIST_FIRST(&iter->mp_copy);
			if (!LIST_EMPTY(&iter->mp_share)) {
				if (exclusive_node)
					exclusive_node = NULL;
				else {
					exclusive_node = LIST_FIRST(&iter->mp_share);
				}
			}
			if (exclusive_node && LIST_NEXT(exclusive_node, mn_link) != NULL)
				exclusive_node = NULL;
			if (exclusive_node && exclusive_node->mn_mman == &mman_kernel) {
				info->mru_kernel += partsize;
			} else if (!LIST_EMPTY(&iter->mp_share) || !LIST_EMPTY(&iter->mp_copy)) {
				if (mpart_isanon(iter)) {
					info->mru_private += partsize;
				} else {
					info->mru_shared += partsize;
				}
			}
		}
		mpart_lock_release(iter);
		decref_unlikely(iter);
	}
	mpart_all_release();
}

INTERN NONNULL((1)) void KCALL
procfs_kos_raminfo_printer(pformatprinter printer, void *arg,
                           pos_t UNUSED(offset_hint)) {
	struct pmemstat dynmem_st;
	struct page_usage_struct dynmem_usage;
	unsigned int i;
	uint64_t dynmem_total_reasons;
	uint64_t dynmem_misc_usage;
	physpagecnt_t dynmem_total;
	uint64_t ram_total;
	uint64_t ram_total_usable;
	uint64_t ram_total_kernel;
	uint64_t ram_total_unusable;
	struct mpart_ram_usage part_usage;

	/* Load memory usage stats. */
	page_stat(&dynmem_st);
	gather_mpart_ramusage(&part_usage);
	for (i = 0; i < sizeof(dynmem_usage) / sizeof(size_t); ++i)
		((size_t *)&dynmem_usage)[i] = ATOMIC_READ(((size_t *)&page_usage)[i]);
	dynmem_total_reasons = 0;
	for (i = 0; i < sizeof(dynmem_usage) / sizeof(size_t); ++i)
		dynmem_total_reasons += ((size_t *)&dynmem_usage)[i];
	if (OVERFLOW_USUB(dynmem_st.ps_used, dynmem_total_reasons, &dynmem_misc_usage))
		dynmem_misc_usage = 0;
	dynmem_total = dynmem_st.ps_free + dynmem_st.ps_used;
	dynmem_total *= PAGESIZE;
	dynmem_misc_usage *= PAGESIZE;

	ram_total_usable   = 0;
	ram_total_kernel   = 0;
	ram_total_unusable = 0;
	for (i = 0; i < minfo.mb_bankc; ++i) {
		uint64_t banksize = (uint64_t)PMEMBANK_SIZE(minfo.mb_banks[i]);
		switch (minfo.mb_banks[i].mb_type) {
		case PMEMBANK_TYPE_RAM:
			ram_total_usable += banksize;
			break;
		case PMEMBANK_TYPE_KFREE:
		case PMEMBANK_TYPE_KERNEL:
			ram_total_kernel += banksize;
			break;
		case PMEMBANK_TYPE_UNDEF:
		case PMEMBANK_TYPE_NVS:
		case PMEMBANK_TYPE_DEVICE:
			break;
		default:
			ram_total_unusable += banksize;
			break;
		}
	}
	ram_total = ram_total_usable + ram_total_kernel + ram_total_unusable;

	/* Print information */
#define PAGES(n) ((uint64_t)(n) * PAGESIZE)
#define print_stat(name, value, total)                                    \
	PRINT("\n" name);                                                     \
	if (print_size_with_unit_and_percent(printer, arg, value, total) < 0) \
		return
	PRINT     ("ram:             ");
	if (print_size_with_unit(printer, arg, ram_total) < 0)
		return;
	print_stat("  kernel:        ", ram_total_kernel, ram_total);
	print_stat("  usable:        ", ram_total_usable, ram_total);
	if (ram_total_unusable) {
	print_stat("  unusable:      ", ram_total_unusable, ram_total);
	}
	print_stat("dynmem:          ", dynmem_total, ram_total);
	print_stat("  free:          ", PAGES(dynmem_st.ps_free), dynmem_total);
	print_stat("    zero:        ", PAGES(dynmem_st.ps_zfree), PAGES(dynmem_st.ps_free));
	print_stat("  used:          ", PAGES(dynmem_st.ps_used), dynmem_total);
	print_stat("    misc:        ", dynmem_misc_usage, PAGES(dynmem_st.ps_used));
	print_stat("      mem-parts: ", part_usage.mru_ram, dynmem_misc_usage);
	print_stat("        locked:  ", part_usage.mru_locked, part_usage.mru_ram);
	print_stat("        file:    ", part_usage.mru_file, part_usage.mru_ram);
	print_stat("        kernel:  ", part_usage.mru_kernel, part_usage.mru_ram);
	print_stat("        private: ", part_usage.mru_private, part_usage.mru_ram);
	print_stat("        shared:  ", part_usage.mru_shared, part_usage.mru_ram);
	print_stat("    paging:      ", PAGES(dynmem_usage.pu_paging), PAGES(dynmem_st.ps_used));
	print_stat("    static:      ", PAGES(dynmem_usage.pu_static), PAGES(dynmem_st.ps_used));
#if defined(__x86_64__) || defined(__i386__)
	print_stat("    x86.iobm:    ", PAGES(dynmem_usage.pu_x86_iobm), dynmem_st.ps_used);
#endif /* __x86_64__ || __i386__ */
#undef PAGES
	PRINT("\n");
}




/************************************************************************/
/* /proc/kos/cc-max-attempts                                            */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_kos_cc_max_attempts_print(pformatprinter printer, void *arg,
                                 pos_t UNUSED(offset_hint)) {
	ProcFS_PrintUInt(printer, arg, system_cc_maxattempts);
}
INTERN void KCALL
procfs_kos_cc_max_attempts_write(USER CHECKED void const *buf,
                                 size_t bufsize) {
	unsigned int newmax;
	newmax = ProcFS_ParseUInt(buf, bufsize, 0, UINT_MAX);
	ATOMIC_WRITE(system_cc_maxattempts, newmax);
}




/************************************************************************/
/* /proc/kos/futexfd-maxexpr                                            */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_kos_futexfd_maxexpr_print(pformatprinter printer, void *arg,
                                 pos_t UNUSED(offset_hint)) {
	ProcFS_PrintSize(printer, arg, mfutexfd_maxexpr);
}
INTERN void KCALL
procfs_kos_futexfd_maxexpr_write(USER CHECKED void const *buf,
                                 size_t bufsize) {
	size_t newmax;
	newmax = ProcFS_ParseSize(buf, bufsize, 1, SIZE_MAX);
	ATOMIC_WRITE(mfutexfd_maxexpr, newmax);
}




#if defined(__x86_64__) || defined(__i386__)
PRIVATE void KCALL
KeepIopl_Write(USER CHECKED void const *buf, size_t bufsize, bool *pvalue) {
	bool new_value;
	new_value = ProcFS_ParseBool(buf, bufsize);
	for (;;) {
		bool old_value;
		old_value = ATOMIC_READ(*pvalue);
		if (old_value == new_value)
			break; /* Nothing to do here! */

		/* Need sysadmin to change the value. */
		cred_require_sysadmin();

		/* Need hwio to turn one of these on! */
		if (new_value)
			require(CAP_SYS_RAWIO);

		/* Change the value. */
		if (ATOMIC_CMPXCH_WEAK(*pvalue, old_value, new_value))
			break;
	}
}



/************************************************************************/
/* /proc/sys/x86/keepiopl/fork                                          */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Fork_Print(pformatprinter printer, void *arg,
                                   pos_t UNUSED(offset_hint)) {
	ProcFS_PrintBool(printer, arg, x86_iopl_keep_after_fork);
}

INTERN void KCALL
ProcFS_Sys_X86_KeepIopl_Fork_Write(USER CHECKED void const *buf,
                                   size_t bufsize) {
	KeepIopl_Write(buf, bufsize, &x86_iopl_keep_after_fork);
}


/************************************************************************/
/* /proc/sys/x86/keepiopl/clone                                         */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Clone_Print(pformatprinter printer, void *arg,
                                    pos_t UNUSED(offset_hint)) {
	ProcFS_PrintBool(printer, arg, x86_iopl_keep_after_clone);
}

INTERN void KCALL
ProcFS_Sys_X86_KeepIopl_Clone_Write(USER CHECKED void const *buf,
                                    size_t bufsize) {
	KeepIopl_Write(buf, bufsize, &x86_iopl_keep_after_clone);
}


/************************************************************************/
/* /proc/sys/x86/keepiopl/exec                                          */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_X86_KeepIopl_Exec_Print(pformatprinter printer, void *arg,
                                   pos_t UNUSED(offset_hint)) {
	bool keep;
	union x86_user_eflags_mask_union mask;
	mask.uem_word = atomic64_read(&x86_exec_eflags_mask);
	keep = (mask.uem_mask & EFLAGS_IOPLMASK) == EFLAGS_IOPLMASK;
	ProcFS_PrintBool(printer, arg, keep);
}

INTERN void KCALL
ProcFS_Sys_X86_KeepIopl_Exec_Write(USER CHECKED void const *buf, size_t bufsize) {
	bool keep;
	union x86_user_eflags_mask_union oldmask, newmask;
	KeepIopl_Write(buf, bufsize, &keep);
	for (;;) {
		oldmask.uem_word = atomic64_read(&x86_exec_eflags_mask);
		newmask.uem_word = oldmask.uem_word;
		newmask.uem_mask &= ~EFLAGS_IOPLMASK;
		if (keep)
			newmask.uem_mask |= EFLAGS_IOPLMASK;
		if (oldmask.uem_mask == newmask.uem_mask)
			break; /* Unchanged. */
		if (atomic64_cmpxch(&x86_exec_eflags_mask, oldmask.uem_word, newmask.uem_word))
			break;
	}
}
#endif /* __x86_64__ || __i386__ */


/************************************************************************/
/* /proc/sys/fs/pipe-max-size                                           */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_sys_fs_pipemaxsize_print(pformatprinter printer, void *arg,
                                pos_t UNUSED(offset_hint)) {
	ProcFS_PrintSize(printer, arg, ATOMIC_READ(pipe_max_bufsize_unprivileged));
}

INTERN void KCALL
procfs_sys_fs_pipemaxsize_write(USER CHECKED void const *buf,
                                size_t bufsize) {
	size_t oldsize, newsize;
	/* Setting  it lower than the default limit  can't be done, since the default
	 * limit is set regardless of what `pipe_max_bufsize_unprivileged' is set to. */
	newsize = ProcFS_ParseSize(buf, bufsize, RINGBUFFER_DEFAULT_LIMIT, (size_t)-1);
	do {
		oldsize = ATOMIC_READ(pipe_max_bufsize_unprivileged);
		if (newsize > oldsize)
			require(CAP_SYS_RESOURCE);
	} while (!ATOMIC_CMPXCH_WEAK(pipe_max_bufsize_unprivileged, oldsize, newsize));
}


#ifdef CONFIG_HAVE_FS_NOTIFY
/************************************************************************/
/* /proc/sys/fs/inotify/max_queued_events                               */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
procfs_sys_fs_inotify_maxqueuedevents_print(pformatprinter printer, void *arg,
                                            pos_t UNUSED(offset_hint)) {
	ProcFS_PrintUInt(printer, arg, ATOMIC_READ(notifyfd_default_maxevents));
}

INTERN void KCALL
procfs_sys_fs_inotify_maxqueuedevents_write(USER CHECKED void const *buf,
                                            size_t bufsize) {
	unsigned int new_maxevents;
	new_maxevents = ProcFS_ParseUInt(buf, bufsize, 1, (unsigned int)0x10000);
	ATOMIC_WRITE(notifyfd_default_maxevents, new_maxevents);
}
#endif /* CONFIG_HAVE_FS_NOTIFY */


/************************************************************************/
/* /proc/sys/kernel/domainname                                          */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_Domainname_Print(pformatprinter printer, void *arg,
                                   pos_t UNUSED(offset_hint)) {
	printf("%s\n", kernel_uname.domainname);
}

INTERN void KCALL
ProcFS_Sys_Kernel_Domainname_Write(USER CHECKED void const *buf,
                                   size_t bufsize) {
	char temp[_UTSNAME_DOMAIN_LENGTH];
	USER CHECKED char const *endp;
	endp = (USER CHECKED char const *)buf + bufsize;
	while (endp > (USER CHECKED char const *)buf &&
	       unicode_islf(endp[-1]))
		--endp;
	bufsize = (size_t)(endp - (USER CHECKED char const *)buf);
	if (bufsize > _UTSNAME_DOMAIN_LENGTH)
		THROW(E_BUFFER_TOO_SMALL, bufsize, _UTSNAME_DOMAIN_LENGTH);
	cred_require_sysadmin();
	memcpy(temp, buf, bufsize, sizeof(char));
	bzero(temp + bufsize, _UTSNAME_DOMAIN_LENGTH - bufsize, sizeof(char));
	COMPILER_READ_BARRIER();
	memcpy(kernel_uname.domainname, temp, sizeof(temp));
}


/************************************************************************/
/* /proc/sys/kernel/hostname                                            */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_Hostname_Print(pformatprinter printer, void *arg,
                                 pos_t UNUSED(offset_hint)) {
	printf("%s\n", kernel_uname.nodename);
}

INTERN void KCALL
ProcFS_Sys_Kernel_Hostname_Write(USER CHECKED void const *buf,
                                 size_t bufsize) {
	char temp[_UTSNAME_NODENAME_LENGTH];
	USER CHECKED char const *endp;
	endp = (USER CHECKED char const *)buf + bufsize;
	while (endp > (USER CHECKED char const *)buf &&
	       unicode_islf(endp[-1]))
		--endp;
	bufsize = (size_t)(endp - (USER CHECKED char const *)buf);
	if (bufsize > _UTSNAME_NODENAME_LENGTH)
		THROW(E_BUFFER_TOO_SMALL, bufsize, _UTSNAME_NODENAME_LENGTH);
	cred_require_sysadmin();
	memcpy(temp, buf, bufsize, sizeof(char));
	bzero(temp + bufsize, _UTSNAME_NODENAME_LENGTH - bufsize, sizeof(char));
	COMPILER_READ_BARRIER();
	memcpy(kernel_uname.nodename, temp, sizeof(temp));
}


/************************************************************************/
/* /proc/sys/kernel/pid_max                                             */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_PidMax_Print(pformatprinter printer, void *arg,
                               pos_t UNUSED(offset_hint)) {
	ProcFS_PrintUPid(printer, arg, ATOMIC_READ(pid_recycle_threshold));
}

INTERN void KCALL
ProcFS_Sys_Kernel_PidMax_Write(USER CHECKED void const *buf,
                               size_t bufsize) {
	upid_t newvalue;
	newvalue = ProcFS_ParseUPid(buf, bufsize, PID_MIN, PID_MAX);
	ATOMIC_WRITE(pid_recycle_threshold, newvalue);
}


/************************************************************************/
/* /proc/sys/kernel/randomize_va_space                                  */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_RandomizeVaSpace_Print(pformatprinter printer, void *arg,
                                         pos_t UNUSED(offset_hint)) {
	ProcFS_PrintUInt(printer, arg, mman_findunmapped_aslr_getenabled() ? 2 : 0);
}

INTERN void KCALL
ProcFS_Sys_Kernel_RandomizeVaSpace_Write(USER CHECKED void const *buf,
                                         size_t bufsize) {
	unsigned int mode;
	mode = ProcFS_ParseUInt(buf, bufsize, 0, 2);
	mman_findunmapped_aslr_setenabled(mode != 0);
}


/************************************************************************/
/* /proc/sys/kernel/sched_child_runs_first                              */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Kernel_SchedChildRunsFirst_Print(pformatprinter printer, void *arg,
                                            pos_t UNUSED(offset_hint)) {
	ProcFS_PrintBool(printer, arg, (task_start_default_flags & TASK_START_FHIGHPRIO) != 0);
}

INTERN void KCALL
ProcFS_Sys_Kernel_SchedChildRunsFirst_Write(USER CHECKED void const *buf,
                                            size_t bufsize) {
	bool mode;
	mode = ProcFS_ParseBool(buf, bufsize);
	if (mode) {
		ATOMIC_OR(task_start_default_flags, TASK_START_FHIGHPRIO);
	} else {
		ATOMIC_AND(task_start_default_flags, ~TASK_START_FHIGHPRIO);
	}
}


/************************************************************************/
/* /proc/sys/net/core/rmem_default                                      */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Net_Core_RmemDefault_Print(pformatprinter printer, void *arg,
                                      pos_t UNUSED(offset_hint)) {
	ProcFS_PrintSize(printer, arg, socket_default_rcvbufsiz);
}

INTERN void KCALL
ProcFS_Sys_Net_Core_RmemDefault_Write(USER CHECKED void const *buf, size_t bufsize) {
	size_t newval;
	newval = ProcFS_ParseSize(buf, bufsize, SOCKET_RCVBUFMIN, socket_default_rcvbufmax);
	ATOMIC_WRITE(socket_default_rcvbufsiz, newval);
}


/************************************************************************/
/* /proc/sys/net/core/wmem_default                                      */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Net_Core_WmemDefault_Print(pformatprinter printer, void *arg,
                                      pos_t UNUSED(offset_hint)) {
	ProcFS_PrintSize(printer, arg, socket_default_sndbufsiz);
}

INTERN void KCALL
ProcFS_Sys_Net_Core_WmemDefault_Write(USER CHECKED void const *buf, size_t bufsize) {
	size_t newval;
	newval = ProcFS_ParseSize(buf, bufsize, SOCKET_SNDBUFMIN, socket_default_sndbufmax);
	ATOMIC_WRITE(socket_default_sndbufsiz, newval);
}


/************************************************************************/
/* /proc/sys/net/core/rmem_max                                          */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Net_Core_RmemMax_Print(pformatprinter printer, void *arg,
                                  pos_t UNUSED(offset_hint)) {
	ProcFS_PrintSize(printer, arg, socket_default_rcvbufmax);
}

INTERN void KCALL
ProcFS_Sys_Net_Core_RmemMax_Write(USER CHECKED void const *buf, size_t bufsize) {
	size_t newval, old_dfl;
	newval = ProcFS_ParseSize(buf, bufsize, SOCKET_RCVBUFMIN);
	ATOMIC_WRITE(socket_default_rcvbufmax, newval);
	do {
		old_dfl = ATOMIC_READ(socket_default_rcvbufsiz);
		if (old_dfl <= newval)
			break;
	} while (!ATOMIC_CMPXCH_WEAK(socket_default_rcvbufsiz,
	                             old_dfl, newval));
}


/************************************************************************/
/* /proc/sys/net/core/wmem_max                                          */
/************************************************************************/
INTERN NONNULL((1)) void KCALL
ProcFS_Sys_Net_Core_WmemMax_Print(pformatprinter printer, void *arg,
                                  pos_t UNUSED(offset_hint)) {
	ProcFS_PrintSize(printer, arg, socket_default_sndbufmax);
}

INTERN void KCALL
ProcFS_Sys_Net_Core_WmemMax_Write(USER CHECKED void const *buf, size_t bufsize) {
	size_t newval, old_dfl;
	newval = ProcFS_ParseSize(buf, bufsize, SOCKET_SNDBUFMIN);
	ATOMIC_WRITE(socket_default_sndbufmax, newval);
	do {
		old_dfl = ATOMIC_READ(socket_default_sndbufsiz);
		if (old_dfl <= newval)
			break;
	} while (!ATOMIC_CMPXCH_WEAK(socket_default_sndbufsiz,
	                             old_dfl, newval));
}


/************************************************************************/
/* /proc/kos/leaks                                                      */
/************************************************************************/
#ifdef CONFIG_TRACE_MALLOC

struct memleaks: printnode {
	kmalloc_leaks_t ml_leaks;   /* [0..1][const] Memory leaks. */
	unsigned int    ml_relmode; /* Memory leaks release mode (one of `KMALLOC_LEAKS_RELEASE_*') */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL memleaks_v_destroy)(struct mfile *__restrict self) {
	struct memleaks *me;
	me = (struct memleaks *)mfile_asprintnode(self);
	kmalloc_leaks_release(me->ml_leaks, me->ml_relmode);
	printnode_v_destroy(me);
}

PRIVATE BLOCKING NONNULL((1, 2)) void KCALL
memleaks_v_print(struct printnode *__restrict self,
                 pformatprinter printer, void *arg,
                 pos_t UNUSED(offset_hint))
		THROWS(...) {
	struct memleaks *me = (struct memleaks *)self;
	kmalloc_leaks_print(me->ml_leaks, printer, arg);
}

PRIVATE NOBLOCK ATTR_CONST uint32_t
NOTHROW(FCALL encode_release_mode)(unsigned int mode) {
	uint32_t result;
	switch (mode) {
	case KMALLOC_LEAKS_RELEASE_RESTORE: result = LEAKS_ONCLOSE_RESTORE; break;
	case KMALLOC_LEAKS_RELEASE_DISCARD: result = LEAKS_ONCLOSE_DISCARD; break;
	case KMALLOC_LEAKS_RELEASE_FREE:    result = LEAKS_ONCLOSE_FREE; break;
	default:
		__builtin_unreachable();
	}
	return result;
}

PRIVATE unsigned int FCALL
decode_release_mode(uint32_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	unsigned int result;
	switch (mode) {
	case LEAKS_ONCLOSE_RESTORE: result = KMALLOC_LEAKS_RELEASE_RESTORE; break;
	case LEAKS_ONCLOSE_DISCARD: result = KMALLOC_LEAKS_RELEASE_DISCARD; break;
	case LEAKS_ONCLOSE_FREE:    result = KMALLOC_LEAKS_RELEASE_FREE; break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LEAKS_INVALID_CLOSEMODE,
		      mode);
	}
	return result;
}

PRIVATE uintptr_t FCALL
decode_leakattr(uint64_t attr)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND) {
	uintptr_t result;
	switch (attr) {
	case LEAK_ATTR_MINADDR:  result = MEMLEAK_ATTR_MINADDR; break;
	case LEAK_ATTR_MAXADDR:  result = MEMLEAK_ATTR_MAXADDR; break;
	case LEAK_ATTR_LEAKSIZE: result = MEMLEAK_ATTR_LEAKSIZE; break;
	case LEAK_ATTR_MINUSER:  result = MEMLEAK_ATTR_MINUSER; break;
	case LEAK_ATTR_MAXUSER:  result = MEMLEAK_ATTR_MAXUSER; break;
	case LEAK_ATTR_USERSIZE: result = MEMLEAK_ATTR_USERSIZE; break;
	case LEAK_ATTR_TID:      result = MEMLEAK_ATTR_TID; break;
	case LEAK_ATTR_TBSIZE:   result = MEMLEAK_ATTR_TBSIZE; break;
	case LEAK_ATTR_NOWALK:   result = MEMLEAK_ATTR_NOWALK; break;
	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LEAKS_INVALID_ATTRIB,
		      attr);
	}
	return result;
}

PRIVATE ATTR_RETNONNULL WUNUSED memleak_t FCALL
get_nth_leak(struct memleaks *__restrict self, uint64_t nth)
		THROWS(E_INVALID_ARGUMENT_BAD_VALUE) {
	size_t i = 0, count = 0;
	memleak_t result = memleak_next(self->ml_leaks, NULL);
	for (;;) {
		if (!result) {
			THROW(E_INVALID_ARGUMENT_BAD_VALUE,
			      E_INVALID_ARGUMENT_CONTEXT_LEAKS_INVALID_INDEX,
			      (uintptr_t)nth, count);
		}
		if (i >= nth)
			break;
		result = memleak_next(self->ml_leaks, result);
		++i;
	}
	return result;
}

PRIVATE BLOCKING NONNULL((1)) syscall_slong_t KCALL
memleaks_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode)
		THROWS(E_INVALID_ARGUMENT_UNKNOWN_COMMAND, ...) {
	struct memleaks *me = (struct memleaks *)mfile_asprintnode(self);
	switch (cmd) {

	case LEAKS_IOC_LEAKATTR: {
		memleak_t leak;
		uintptr_t attr, aval;
		USER CHECKED struct leakattr *info;
		validate_writable(arg, sizeof(struct leakattr));
		info = (USER CHECKED struct leakattr *)arg;
		attr = decode_leakattr(info->la_attr);
		leak = get_nth_leak(me, info->la_index);
		aval = (uintptr_t)memleak_getattr(leak, attr);

		/* Write-back the attribute value. */
		info->la_value = (uint64_t)aval;
		return 0;
	}	break;

	case LEAKS_IOC_LEAKTB: {
		memleak_t leak;
		USER CHECKED struct leaktb *info;
		size_t i, count, req;
		USER CHECKED uint64_t *uvec;
		validate_readwrite(arg, sizeof(struct leaktb));
		info  = (USER CHECKED struct leaktb *)arg;
		leak  = get_nth_leak(me, info->lt_index);
		count = (size_t)info->lt_count;
		uvec  = info->lt_elemp;
		COMPILER_READ_BARRIER();
		validate_writablem(uvec, count, sizeof(uint64_t));
		req = (size_t)memleak_getattr(leak, MEMLEAK_ATTR_TBSIZE);
		info->lt_count = req;
		if (req > count)
			req = count;
		for (i = 0; i < req; ++i)
			uvec[i] = (uint64_t)(uintptr_t)memleak_getattr(leak, MEMLEAK_ATTR_TBADDR(i));
		return 0;
	}	break;

	case LEAKS_IOC_READLEAKMEM:
	case LEAKS_IOC_READUSERMEM: {
		byte_t const *leak_addr;
		size_t leak_size;
		memleak_t leak;
		USER CHECKED struct leakmem *info;
		size_t size, offs, _temp;
		USER CHECKED byte_t *ubuf;
		validate_readwrite(arg, sizeof(struct leakmem));
		info = (USER CHECKED struct leakmem *)arg;
		leak = get_nth_leak(me, info->lm_index);
		offs = (size_t)info->lm_offset;
		size = (size_t)info->lm_size;
		ubuf = info->lm_buf;
		COMPILER_READ_BARRIER();

		/* Load leak attributes */
		if (cmd == LEAKS_IOC_READLEAKMEM) {
			leak_addr = (byte_t const *)memleak_getattr(leak, MEMLEAK_ATTR_MINADDR);
			leak_size = (size_t)memleak_getattr(leak, MEMLEAK_ATTR_LEAKSIZE);
		} else {
			leak_addr = (byte_t const *)memleak_getattr(leak, MEMLEAK_ATTR_MINUSER);
			leak_size = (size_t)memleak_getattr(leak, MEMLEAK_ATTR_USERSIZE);
		}

		/* Limit I/O size to relevant leak size. */
		if (OVERFLOW_UADD(offs, size, &_temp) || _temp > leak_size) {
			if (OVERFLOW_USUB(leak_size, offs, &size))
				size = 0;
			info->lm_size = size;
		}

		/* Copy leaked data into userspace. */
		validate_writable(ubuf, size);
		memcpy(ubuf, leak_addr, size);
		return 0;
	}	break;

	default:
		break;
	}
	switch (_IO_WITHSIZE(cmd, 0)) {

	case _IO_WITHSIZE(LEAKS_IOC_GETONCLOSE, 0): {
		uint32_t onclose = encode_release_mode(me->ml_relmode);
		return ioctl_intarg_setu32(cmd, arg, onclose);
	}	break;

	case _IO_WITHSIZE(LEAKS_IOC_SETONCLOSE, 0): {
		uint32_t onclose = ioctl_intarg_getu32(cmd, arg);
		me->ml_relmode   = decode_release_mode(onclose);
		return 0;
	}	break;

	case _IO_WITHSIZE(LEAKS_IOC_GETCOUNT, 0): {
		size_t count = kmalloc_leaks_count(me->ml_leaks);
		return ioctl_intarg_setu64(cmd, arg, count);
	}	break;

	default:
		break;
	}
	return printnode_v_ioctl(self, cmd, arg, mode);
}


PRIVATE struct mfile_stream_ops const memleaks_v_stream_ops = {
	.mso_pread  = &printnode_v_pread,
	.mso_preadv = &printnode_v_preadv,
	.mso_stat   = &printnode_v_stat,
	.mso_ioctl  = &memleaks_v_ioctl,
};
PRIVATE struct printnode_ops const memleaks_ops = {
	.pno_reg = {{
		.no_file = {
			.mo_destroy    = &memleaks_v_destroy,
			.mo_loadblocks = &printnode_v_loadblocks,
			.mo_changed    = &printnode_v_changed,
			.mo_stream     = &memleaks_v_stream_ops,
		},
		.no_wrattr = &printnode_v_wrattr,
	}},
	.pno_print = &memleaks_v_print,
};

/* Allocate a new memleaks file. */
PRIVATE WUNUSED REF struct memleaks *KCALL
memleaks_createfile(void) {
	REF struct memleaks *result;
	result = (struct memleaks *)kmalloc(sizeof(struct memleaks), GFP_NORMAL);
	TRY {
		/* Collect memory leaks. */
		result->ml_leaks = kmalloc_leaks_collect();
	} EXCEPT {
		kfree(result);
		RETHROW();
	}

	/* Fill in other fields. */
	_mfile_init_common(result);
	result->mf_ops   = &memleaks_ops.pno_reg.rno_node.no_file;
	result->mf_parts = NULL;
	SLIST_INIT(&result->mf_changed);
	result->mf_part_amask = PAGEMASK;
	result->mf_blockshift = PAGESHIFT;
	result->mf_iobashift  = PAGESHIFT;
	result->mf_flags      = MFILE_F_NORMAL;
	atomic64_init(&result->mf_filesize, (uint64_t)-1);
	result->mf_atime = realtime();
	result->mf_mtime = result->mf_atime;
	result->mf_ctime = result->mf_atime;
	mfile_tslock_acquire(&procfs_super.fs_root);
	result->mf_btime = procfs_super.fs_root.mf_btime;
	mfile_tslock_release(&procfs_super.fs_root);
	result->fn_nlink = 1;
	result->fn_mode  = S_IFREG | 0400;
	result->fn_uid   = 0;
	result->fn_gid   = 0;
	result->fn_ino   = (ino_t)skew_kernel_pointer(result);
	result->fn_super = incref(&procfs_super);
	LIST_ENTRY_UNBOUND_INIT(&result->fn_changed);
	DBG_memset(&result->fn_supent, 0xcc, sizeof(result->fn_supent));
	result->fn_supent.rb_rhs = FSUPER_NODES_DELETED;
	LIST_ENTRY_UNBOUND_INIT(&result->fn_allnodes);
	result->ml_relmode = KMALLOC_LEAKS_RELEASE_RESTORE;
	return result;
}

PRIVATE BLOCKING NONNULL((1, 2)) void KCALL
procfs_r_kos_leaks_v_open(struct mfile *__restrict self,
                          /*in|out*/ REF struct handle *__restrict hand,
                          struct path *access_path,
                          struct fdirent *access_dent,
                          oflag_t UNUSED(oflags)) {
	REF struct memleaks *file;
	REF struct filehandle *fh;

	/* Only the sysadmin is allowed to access memory leaks. */
	require(CAP_SYS_ADMIN);

	/* Create the leaks file. */
	file = memleaks_createfile();
	FINALLY_DECREF_UNLIKELY(file);

	/* Construct the filehandle wrapper object. */
	fh = filehandle_new(file, access_path, access_dent);

	/* Write-back the file-handle wrapper. */
	hand->h_type = HANDLE_TYPE_TEMPHANDLE; /* Self-delete on `close()' */
	hand->h_data = fh;                     /* Inherit reference */
	decref_nokill(self);                   /* Old reference from `hand->h_data' */
}

PRIVATE struct mfile_stream_ops const procfs_r_kos_leaks_v_stream_ops = {
	.mso_open = &procfs_r_kos_leaks_v_open,
};

INTERN_CONST struct fregnode_ops const procfs_r_kos_leaks_ops = {
	.rno_node = {
		.no_file = {
			.mo_destroy = (void (KCALL *)(struct mfile *__restrict))(void *)(uintptr_t)-1,
			.mo_changed = &fnode_v_changed,
			.mo_stream  = &procfs_r_kos_leaks_v_stream_ops,
		},
		.no_free   = (void (KCALL *)(struct fnode *__restrict))(void *)(uintptr_t)-1,
		.no_wrattr = &fnode_v_wrattr_noop,
	},
};
#endif /* CONFIG_TRACE_MALLOC */


DECL_END

#endif /* !GUARD_MODPROCFS_FILES_C */
