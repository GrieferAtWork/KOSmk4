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
#ifndef GUARD_MODPROCFS_FILES_PERPROC_C
#define GUARD_MODPROCFS_FILES_PERPROC_C 1
#define _KOS_SOURCE 1
#define FNODE_FSDATA_T struct taskpid

#include <kernel/compiler.h>

DECL_BEGIN
struct taskpid;
DECL_END

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/execabi.h> /* execabi_system_rtld_file */
#include <kernel/fs/constdir.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/printnode.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/mman.h>
#include <kernel/mman/driver.h>
#include <kernel/mman/enum.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/memfd.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/ramfile.h>
#include <kernel/mman/rw.h>
#include <kernel/mman/stat.h>
#include <kernel/printk.h>
#include <kernel/user.h>
#include <sched/comm.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/epoll.h>
#include <sched/eventfd.h>
#include <sched/group.h>
#include <sched/posix-signalfd.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/overflow.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/illop.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/io.h>
#include <kos/exec/peb.h>
#include <kos/exec/rtld.h> /* RTLD_LIBDL */
#include <sys/mkdev.h>
#include <sys/param.h>
#include <sys/stat.h>

#include <assert.h>
#include <atomic.h>
#include <format-printer.h>
#include <inttypes.h>
#include <signal.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

#if defined(__x86_64__) || defined(__i386__)
#include <sched/x86/iopl.h>
#endif /* __x86_64__ || __i386__ */

#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/exec/peb.h>
#include <compat/kos/exec/rtld.h> /* COMPAT_RTLD_LIBDL */
#include <compat/kos/types.h>
#include <compat/pointer.h>
#endif /* __ARCH_HAVE_COMPAT */

/**/
#include "procfs.h"

/* Per-process files (all of these have `REF struct taskpid *fn_fsdata') */

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset(p, c, n) memset(p, c, n)
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(p, c, n) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define print(p, len) (*printer)(arg, p, len)
#define printf(...)   format_printf(printer, arg, __VA_ARGS__)
#define PRINT(str)    print(str, COMPILER_STRLEN(str))

/* Forward declarations (to cause compiler errors if laster declarations are incompatible) */
#define MKREG_RO(ops_symbol_name, printer)     \
	INTDEF NONNULL((1, 2)) void KCALL          \
	printer(struct printnode *__restrict self, \
	        pformatprinter printer, void *arg, \
	        pos_t offset_hint);
#define MKREG_RW(ops_symbol_name, printer, writer)             \
	INTDEF NONNULL((1, 2)) void KCALL                          \
	printer(struct printnode *__restrict self,                 \
	        pformatprinter printer_, void *arg,                \
	        pos_t offset_hint);                                \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL                   \
	writer(struct mfile *__restrict self, NCX void const *src, \
	       size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
#define MKLNK(ops_symbol_name, readlink)       \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL   \
	readlink(struct flnknode *__restrict self, \
	         NCX /*utf-8*/ char *buf,          \
	         size_t bufsize)                   \
			THROWS(E_SEGFAULT, E_IOERROR, ...);
#include "perproc.def"


/* Common operators for all per-process files. */
#define procfs_perproc_v_changed fnode_v_changed
#define procfs_perproc_v_wrattr  fnode_v_wrattr_noop
#define procfs_perproc_v_ioctl   fnode_v_ioctl
#define procfs_perproc_v_free    (*(typeof_field(struct fnode_ops, no_free))(void *)-1)
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_perproc_v_destroy)(struct mfile *__restrict self);

/* NIBBLES_PER_PTR == __SIZEOF_POINTER__*2 */
#if __SIZEOF_POINTER__ == 8
#define NIBBLES_PER_PTR 16
#elif __SIZEOF_POINTER__ == 4
#define NIBBLES_PER_PTR 8
#elif __SIZEOF_POINTER__ == 2
#define NIBBLES_PER_PTR 4
#elif __SIZEOF_POINTER__ == 1
#define NIBBLES_PER_PTR 2
#elif !defined(__DEEMON__) /* __SIZEOF_POINTER__ == ... */
#error "Unsupported `__SIZEOF_POINTER__'"
#endif /* __SIZEOF_POINTER__ != ... */

/* Print a signal set in that hexadecimal format that linux likes to use. */
PRIVATE NONNULL((1, 3)) ssize_t KCALL
print_sigset(pformatprinter printer, void *arg,
             sigset_t const *__restrict ss) {
	ssize_t temp, result = 0;
	bool got_nonzero = false;
	unsigned int i;
	i = lengthof(ss->__val) - 1;
	for (;;) {
		ulongptr_t val;
		val = atomic_read(&ss->__val[i]);
		if (val != 0 || got_nonzero || i < CEILDIV(64, BITSOF(ulongptr_t))) {
			temp = printf(got_nonzero ? "%." PP_STR(NIBBLES_PER_PTR) PRIxPTR
			                          : "%" PRIxPTR,
			              val);
			if unlikely(temp < 0)
				goto err;
			result += temp;
			got_nonzero = true;
		}
		if (i == 0)
			break;
		--i;
	}
	return result;
err:
	return temp;
}


PRIVATE BLOCKING NONNULL((1, 2, 3)) void KCALL
procfs_perproc_v_getown(struct fnode *__restrict self,
                        uid_t *__restrict powner,
                        gid_t *__restrict pgroup)
		THROWS(E_IOERROR, ...) {
	REF struct task *thread = taskpid_gettask(self->fn_fsdata);

	/* Fill uid/gid based on thread credentials. */
	if (thread) {
		REF struct cred *thread_cred;
		thread_cred = task_getcred(thread);
		decref_unlikely(thread);
		FINALLY_DECREF_UNLIKELY(thread_cred);

		/* NOTE: Yes, we need to use the effective U/G-id here (linux does the same) */
		*powner = atomic_read(&thread_cred->c_euid);
		*pgroup = atomic_read(&thread_cred->c_egid);
	} else {
		/* Fallback... */
		*powner = 0;
		*pgroup = 0;
	}
}

/* Permissions operators for per-process files. */
INTERN_CONST struct fnode_perm_ops const procfs_perproc_v_perm_ops = {
	.npo_getown = &procfs_perproc_v_getown
};

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_v_stat_common(struct mfile *__restrict self,
                             NCX struct stat *result)
		THROWS(...) {
	struct fnode *me        = mfile_asnode(self);
	REF struct task *thread = taskpid_gettask(me->fn_fsdata);
	/* Set timestamps based on thread times. */
	if (thread) {
		struct timespec ts;
		FINALLY_DECREF_UNLIKELY(thread);

		/* Creation-time: store the time when the thread was started. */
		ts = task_getstarttime(thread);
		result->st_btime     = ts.tv_sec;
		result->st_btimensec = ts.tv_nsec;

		/* a/m/c: store the last point in time when the thread got executed. */
		ts = thread == THIS_TASK ? realtime() : ktime_to_timespec(FORTASK(thread, this_stoptime));
		result->st_atime     = ts.tv_sec;
		result->st_atimensec = ts.tv_nsec;
		result->st_mtime     = ts.tv_sec;
		result->st_mtimensec = ts.tv_nsec;
		result->st_ctime     = ts.tv_sec;
		result->st_ctimensec = ts.tv_nsec;
	} else {
		/* Fallback: just write the current time... */
		struct timespec now  = realtime();
		result->st_atime     = now.tv_sec;
		result->st_atimensec = now.tv_nsec;
		result->st_mtime     = now.tv_sec;
		result->st_mtimensec = now.tv_nsec;
		result->st_ctime     = now.tv_sec;
		result->st_ctimensec = now.tv_nsec;
		result->st_btime     = now.tv_sec;
		result->st_btimensec = now.tv_nsec;
	}
}

INTERN NONNULL((1)) void KCALL
procfs_perproc_dir_v_stat(struct mfile *__restrict self,
                          NCX struct stat *result)
		THROWS(...) {
	procfs_perproc_v_stat_common(self, result);
	fdirnode_v_stat(self, result);
}

INTERN NONNULL((1)) void KCALL
procfs_perproc_printnode_v_stat(struct mfile *__restrict self,
                                NCX struct stat *result)
		THROWS(...) {
	procfs_perproc_v_stat_common(self, result);
	printnode_v_stat(self, result);
}

INTERN NONNULL((1)) void KCALL
procfs_perproc_lnknode_v_stat(struct mfile *__restrict self,
                              NCX struct stat *result)
		THROWS(...) {
	size_t lnksize;
	struct flnknode *me            = mfile_aslnk(self);
	struct flnknode_ops const *ops = flnknode_getops(me);
	procfs_perproc_v_stat_common(self, result);
	lnksize           = (*ops->lno_readlink)(me, NULL, 0);
	result->st_blocks = CEILDIV(lnksize, PAGESIZE);
	result->st_size   = lnksize;
}
#define procfs_perproc_lnknode_v_destroy      procfs_perproc_v_destroy
#define procfs_perproc_lnknode_v_changed      procfs_perproc_v_changed
#define procfs_perproc_lnknode_v_ioctl        flnknode_v_ioctl
#define procfs_perproc_lnknode_v_free         procfs_perproc_v_free
#define procfs_perproc_lnknode_v_wrattr       procfs_perproc_v_wrattr
#define procfs_perproc_lnknode_v_perm_ops     procfs_perproc_v_perm_ops
#define procfs_perproc_printnode_v_destroy    procfs_perproc_v_destroy
#define procfs_perproc_printnode_v_loadblocks printnode_v_loadblocks
#define procfs_perproc_printnode_v_changed    procfs_perproc_v_changed
#define procfs_perproc_printnode_v_free       procfs_perproc_v_free
#define procfs_perproc_printnode_v_wrattr     procfs_perproc_v_wrattr
#define procfs_perproc_printnode_v_ioctl      printnode_v_ioctl
#define procfs_perproc_printnode_v_perm_ops   procfs_perproc_v_perm_ops

INTERN_CONST struct mfile_stream_ops const procfs_perproc_lnknode_v_stream_ops = {
	.mso_stat  = &procfs_perproc_lnknode_v_stat,
	.mso_ioctl = &procfs_perproc_lnknode_v_ioctl,
};

INTERN_CONST struct mfile_stream_ops const procfs_perproc_printnode_v_stream_ops = {
	.mso_pread  = &printnode_v_pread,
	.mso_preadv = &printnode_v_preadv,
	.mso_stat   = &procfs_perproc_printnode_v_stat,
	.mso_ioctl  = &procfs_perproc_printnode_v_ioctl,
};

/* Operators for per-process directories */
#define procfs_perproc_dir_v_free     procfs_perproc_v_free
#define procfs_perproc_dir_v_destroy  procfs_perproc_v_destroy
#define procfs_perproc_dir_v_changed  procfs_perproc_v_changed
#define procfs_perproc_dir_v_wrattr   procfs_perproc_v_wrattr
#define procfs_perproc_dir_v_open     fdirnode_v_open
#define procfs_perproc_dir_v_ioctl    fdirnode_v_ioctl
#define procfs_perproc_dir_v_perm_ops procfs_perproc_v_perm_ops
INTERN_CONST struct mfile_stream_ops const procfs_perproc_dir_v_stream_ops = {
	.mso_open  = &procfs_perproc_dir_v_open,
	.mso_stat  = &procfs_perproc_dir_v_stat,
	.mso_ioctl = &procfs_perproc_dir_v_ioctl,
};





/* Helper for printing `struct fs' member paths. */
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
ProcFS_PerProc_FsSpecificPath_ReadLink(struct flnknode *__restrict self,
                                       NCX /*utf-8*/ char *buf,
                                       size_t bufsize,
                                       ptrdiff_t struct_fs_offsetof_path)
		THROWS(E_SEGFAULT, ...) {
	REF struct fs *threadfs;
	REF struct path *thread_pth, *caller_root;
	REF struct task *thread = taskpid_gettask(self->fn_fsdata);
	if unlikely(!thread)
		return snprintf(buf, bufsize, "/");
	threadfs = task_getfs(thread);
	decref_unlikely(thread);
	{
		FINALLY_DECREF_UNLIKELY(threadfs);
		fs_pathlock_read(threadfs);
		thread_pth = incref(*(struct path **)((byte_t *)threadfs + struct_fs_offsetof_path));
		fs_pathlock_endread(threadfs);
	}
	FINALLY_DECREF_UNLIKELY(thread_pth);
	caller_root = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(caller_root);
	return path_sprint_without_nul(thread_pth, buf, bufsize, 0, caller_root);
}

#ifndef __OPTIMIZE_SIZE__
PRIVATE WUNUSED NONNULL((1)) REF struct path *KCALL
ProcFS_PerProc_FsSpecificPath_WalkLink(struct flnknode *__restrict self,
                                       ptrdiff_t struct_fs_offsetof_path)
		THROWS(E_SEGFAULT, ...) {
	REF struct fs *threadfs;
	REF struct task *thread = taskpid_gettask(self->fn_fsdata);
	REF struct path *result;
	if unlikely(!thread)
		return NULL;
	threadfs = task_getfs(thread);
	decref_unlikely(thread);
	{
		FINALLY_DECREF_UNLIKELY(threadfs);
		fs_pathlock_read(threadfs);
		result = incref(*(struct path **)((byte_t *)threadfs + struct_fs_offsetof_path));
		fs_pathlock_endread(threadfs);
	}
	return result;
}
#endif /* !__OPTIMIZE_SIZE__ */





/************************************************************************/
/* /proc/[PID]/cwd                                                      */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
procfs_pp_cwd_v_readlink(struct flnknode *__restrict self,
                         NCX /*utf-8*/ char *buf,
                         size_t bufsize)
		THROWS(E_SEGFAULT, ...) {
	return ProcFS_PerProc_FsSpecificPath_ReadLink(self, buf, bufsize, offsetof(struct fs, fs_cwd));
}

#ifndef __OPTIMIZE_SIZE__
PRIVATE WUNUSED NONNULL((1, 2)) REF struct path *KCALL
procfs_pp_cwd_v_walklink(struct flnknode *__restrict self,
                         /*in|out*/ u32 *__restrict UNUSED(premaining_symlinks)) {
	return ProcFS_PerProc_FsSpecificPath_WalkLink(self, offsetof(struct fs, fs_cwd));
}
#endif /* !__OPTIMIZE_SIZE__ */

INTERN_CONST struct flnknode_ops const procfs_pp_cwd = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_lnknode_v_destroy,
			.mo_changed = &procfs_perproc_lnknode_v_changed,
			.mo_stream  = &procfs_perproc_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_perproc_lnknode_v_free,
		.no_wrattr = &procfs_perproc_lnknode_v_wrattr,
		.no_perm   = &procfs_perproc_lnknode_v_perm_ops,
	},
	.lno_readlink = &procfs_pp_cwd_v_readlink,
#ifndef __OPTIMIZE_SIZE__
	.lno_walklink = &procfs_pp_cwd_v_walklink, /* Optimization operator! */
#endif /* !__OPTIMIZE_SIZE__ */
};



/************************************************************************/
/* /proc/[PID]/root                                                     */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
procfs_pp_root_v_readlink(struct flnknode *__restrict self,
                          NCX /*utf-8*/ char *buf,
                          size_t bufsize)
		THROWS(E_SEGFAULT, ...) {
	return ProcFS_PerProc_FsSpecificPath_ReadLink(self, buf, bufsize, offsetof(struct fs, fs_root));
}

#ifndef __OPTIMIZE_SIZE__
PRIVATE WUNUSED NONNULL((1, 2)) REF struct path *KCALL
procfs_pp_root_v_walklink(struct flnknode *__restrict self,
                          /*in|out*/ u32 *__restrict UNUSED(premaining_symlinks)) {
	return ProcFS_PerProc_FsSpecificPath_WalkLink(self, offsetof(struct fs, fs_root));
}
#endif /* !__OPTIMIZE_SIZE__ */

INTERN_CONST struct flnknode_ops const procfs_pp_root = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_lnknode_v_destroy,
			.mo_changed = &procfs_perproc_lnknode_v_changed,
			.mo_stream  = &procfs_perproc_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_perproc_lnknode_v_free,
		.no_wrattr = &procfs_perproc_lnknode_v_wrattr,
		.no_perm   = &procfs_perproc_lnknode_v_perm_ops,
	},
	.lno_readlink = &procfs_pp_root_v_readlink,
#ifndef __OPTIMIZE_SIZE__
	.lno_walklink = &procfs_pp_root_v_walklink, /* Optimization operator! */
#endif /* !__OPTIMIZE_SIZE__ */
};



/************************************************************************/
/* /proc/[PID]/exe                                                      */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
ProcFS_PerProc_Exe_Printer(struct flnknode *__restrict self,
                           NCX /*utf-8*/ char *buf,
                           size_t bufsize)
		THROWS(E_SEGFAULT, ...) {
	REF struct task *thread;
	REF struct mman *thread_mm;
	REF struct path *exec_path;
	REF struct fdirent *exec_name;
	REF struct path *caller_root;
	thread    = taskpid_gettask_srch(self->fn_fsdata);
	thread_mm = task_getmman(thread);
	decref_unlikely(thread);
	{
		FINALLY_DECREF_UNLIKELY(thread_mm);
		mman_lock_read(thread_mm);
		exec_name = xincref(FORMMAN(thread_mm, thismman_execinfo).mei_dent);
		exec_path = xincref(FORMMAN(thread_mm, thismman_execinfo).mei_path);
		mman_lock_endread(thread_mm);
	}
	if unlikely(!exec_name) {
		xdecref_unlikely(exec_path);
		THROW(E_FSERROR_FILE_NOT_FOUND);
	}
	FINALLY_DECREF_UNLIKELY(exec_name);
	if unlikely(!exec_path) {
		return snprintf(buf, bufsize, "%s%$s",
		                exec_name->fd_name[0] == '/' ? "" : "?/",
		                (size_t)exec_name->fd_namelen,
		                exec_name->fd_name);
	}
	FINALLY_DECREF_UNLIKELY(exec_path);
	caller_root = fs_getroot(THIS_FS);
	return path_sprintent_without_nul(exec_path, exec_name->fd_name,
	                                  exec_name->fd_namelen, buf, bufsize,
	                                  /* The kernel always interprets symbolic link texts using POSIX semantics.
	                                   * As such, symbolic link texts should  also only be printed using  those! */
	                                  /*fs_atflags(0) | */ AT_PATHPRINT_INCTRAIL,
	                                  caller_root);
}

#ifndef __OPTIMIZE_SIZE__
PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) REF struct fnode *KCALL
ProcFS_PerProc_Exe_ExpandLink(struct flnknode *__restrict self,
                              /*out[1..1]_opt*/ REF struct path **presult_path,
                              /*out[1..1]_opt*/ REF struct fdirent **presult_dirent,
                              /*in|out*/ u32 *__restrict UNUSED(premaining_symlinks))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	REF struct task *thread;
	REF struct mman *thread_mm;
	REF struct fnode *result;
	thread = taskpid_gettask(self->fn_fsdata);
	if (!thread)
		return NULL;
	thread_mm = task_getmman(thread);
	decref_unlikely(thread);
	{
		FINALLY_DECREF_UNLIKELY(thread_mm);
		mman_lock_read(thread_mm);
		if (!FORMMAN(thread_mm, thismman_execinfo).mei_dent ||
		    !FORMMAN(thread_mm, thismman_execinfo).mei_path ||
		    !FORMMAN(thread_mm, thismman_execinfo).mei_file) {
			mman_lock_endread(thread_mm);
			return NULL;
		}
		*presult_dirent = incref(FORMMAN(thread_mm, thismman_execinfo).mei_dent);
		*presult_path   = incref(FORMMAN(thread_mm, thismman_execinfo).mei_path);
		result          = mfile_asnode(incref(FORMMAN(thread_mm, thismman_execinfo).mei_file));
		mman_lock_endread(thread_mm);
	}
	return result;
}
#endif /* !__OPTIMIZE_SIZE__ */

INTERN_CONST struct flnknode_ops const procfs_pp_exe = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_lnknode_v_destroy,
			.mo_changed = &procfs_perproc_lnknode_v_changed,
			.mo_stream  = &procfs_perproc_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_perproc_lnknode_v_free,
		.no_wrattr = &procfs_perproc_lnknode_v_wrattr,
		.no_perm   = &procfs_perproc_lnknode_v_perm_ops,
	},
	.lno_readlink   = &ProcFS_PerProc_Exe_Printer,
#ifndef __OPTIMIZE_SIZE__
	.lno_expandlink = &ProcFS_PerProc_Exe_ExpandLink, /* Optimization operator! */
#endif /* !__OPTIMIZE_SIZE__ */
};



/************************************************************************/
/* /proc/[PID]/cmdline                                                  */
/************************************************************************/

/* Print the given c-string, or do nothing if the address is faulty.
 * NOTE: The trailing NUL-character is also printed by this function! */
PRIVATE NONNULL((1, 2)) ssize_t KCALL
print_userspace_cstring(struct mman *__restrict mm, pformatprinter printer,
                        void *arg, NCX char const *cstr) {
	char buf[512], *endptr;
	size_t num_bytes;
again:
	num_bytes = sizeof(buf) - mman_read_nopf(mm, cstr, buf, sizeof(buf));
	endptr    = (char *)memchr(buf, 0, num_bytes);
	if (endptr)
		num_bytes = (size_t)((endptr + 1) - buf);
	if unlikely((*printer)(arg, buf, num_bytes) < 0)
		return -1;
	if (!endptr) {
		/* Keep reading more data until we hit the trailing NUL! */
		cstr += num_bytes;
		mman_read(mm, cstr, buf, 1); /* Force read 1 bytes */
		if unlikely((*printer)(arg, buf, 1) < 0)
			return -1;
		if likely(buf[0] != 0) {
			/* Keep reading. */
			++cstr;
			goto again;
		}
	}
	return 0;
}

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PrintUserSpaceStringArray(struct mman *__restrict mm, pformatprinter printer, void *arg,
                                 size_t strc, char const *NCX UNCHECKED const *NCX strv) {
	size_t i;

	/* Verify bounds. */
	if unlikely(OVERFLOW_UMUL(strc, sizeof(*strv), &i))
		return;
	if unlikely(OVERFLOW_UADD((uintptr_t)strv, i, &i))
		return;
	if unlikely(!ADDRRANGE_ISUSER(strv, i))
		return;
	while (strc) {
		NCX UNCHECKED char const *strings[32];
		size_t count = strc;
		if (count > lengthof(strings))
			count = lengthof(strings);
		mman_read(mm, strv, strings, count * sizeof(NCX UNCHECKED char const *));
		for (i = 0; i < count; ++i) {
			NCX UNCHECKED char const *str = strings[i];
			if (!str || !ADDR_ISUSER(str))
				return;
			if (print_userspace_cstring(mm, printer, arg, str))
				return;
		}
		strv += count;
		strc -= count;
	}
}

#ifdef __ARCH_HAVE_COMPAT
INTERN NONNULL((1, 2)) void KCALL
ProcFS_PrintCompatUserSpaceStringArray(struct mman *__restrict mm, pformatprinter printer, void *arg,
                                       size_t strc, compat_uintptr_t NCX UNCHECKED const *NCX strv) {
	size_t i;

	/* Verify bounds. */
	if unlikely(OVERFLOW_UMUL(strc, sizeof(*strv), &i))
		return;
	if unlikely(OVERFLOW_UADD((uintptr_t)strv, i, &i))
		return;
	if unlikely(!ADDRRANGE_ISUSER(strv, i))
		return;
	while (strc) {
		NCX UNCHECKED compat_uintptr_t strings[32];
		size_t count = strc;
		if (count > lengthof(strings))
			count = lengthof(strings);
		mman_read(mm, strv, strings, count * sizeof(NCX UNCHECKED compat_uintptr_t));
		for (i = 0; i < count; ++i) {
			NCX UNCHECKED compat_uintptr_t str = strings[i];
			if (!str || !ADDR_ISUSER(str))
				return;
			if (print_userspace_cstring(mm, printer, arg,
			                            (NCX char const *)(uintptr_t)str))
				return;
		}
		strv += count;
		strc -= count;
	}
}
#endif /* __ARCH_HAVE_COMPAT */

struct _peb_cmdline_buffer {
#if OFFSET_PROCESS_PEB_ARGC < OFFSET_PROCESS_PEB_ARGV
	size_t pp_argc;
#if (OFFSET_PROCESS_PEB_ARGC + __SIZEOF_SIZE_T__) < OFFSET_PROCESS_PEB_ARGV
	byte_t __pp_pad[OFFSET_PROCESS_PEB_ARGV - (OFFSET_PROCESS_PEB_ARGC + __SIZEOF_SIZE_T__)];
#elif (OFFSET_PROCESS_PEB_ARGC + __SIZEOF_SIZE_T__) > OFFSET_PROCESS_PEB_ARGV
#error "Invalid offsets"
#endif /* ... */
	char const *NCX UNCHECKED const *NCX UNCHECKED pp_argv;
#else /* OFFSET_PROCESS_PEB_ARGC < OFFSET_PROCESS_PEB_ARGV */
	char const *NCX UNCHECKED const *NCX UNCHECKED pp_argv;
#if (OFFSET_PROCESS_PEB_ARGV + __SIZEOF_SIZE_T__) < OFFSET_PROCESS_PEB_ARGC
	byte_t __pp_pad[OFFSET_PROCESS_PEB_ARGC - (OFFSET_PROCESS_PEB_ARGV + __SIZEOF_SIZE_T__)];
#elif (OFFSET_PROCESS_PEB_ARGV + __SIZEOF_SIZE_T__) > OFFSET_PROCESS_PEB_ARGC
#error "Invalid offsets"
#endif /* ... */
	size_t pp_argc;
#endif /* OFFSET_PROCESS_PEB_ARGC >= OFFSET_PROCESS_PEB_ARGV */
};

PRIVATE NONNULL((1, 2)) void KCALL
peb_print_cmdline(struct mman *__restrict mm, pformatprinter printer,
                  void *arg, NCX struct process_peb const *peb) {
	struct _peb_cmdline_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_PROCESS_PEB_ARGC, &info, sizeof(info));
	ProcFS_PrintUserSpaceStringArray(mm, printer, arg, info.pp_argc, info.pp_argv);
}

#ifdef __ARCH_HAVE_COMPAT
struct _compat_peb_cmdline_buffer {
#if OFFSET_COMPAT_PROCESS_PEB_ARGC < OFFSET_COMPAT_PROCESS_PEB_ARGV
	compat_size_t pp_argc;
#if (OFFSET_COMPAT_PROCESS_PEB_ARGC + __ARCH_COMPAT_SIZEOF_SIZE_T) < OFFSET_COMPAT_PROCESS_PEB_ARGV
	byte_t __pp_pad[OFFSET_COMPAT_PROCESS_PEB_ARGV - (OFFSET_COMPAT_PROCESS_PEB_ARGC + __ARCH_COMPAT_SIZEOF_SIZE_T)];
#elif (OFFSET_COMPAT_PROCESS_PEB_ARGC + __ARCH_COMPAT_SIZEOF_SIZE_T) > OFFSET_COMPAT_PROCESS_PEB_ARGV
#error "Invalid offsets"
#endif /* ... */
	compat_ptr(compat_uintptr_t) pp_argv;
#else /* OFFSET_COMPAT_PROCESS_PEB_ARGC < OFFSET_COMPAT_PROCESS_PEB_ARGV */
	compat_ptr(compat_uintptr_t) pp_argv;
#if (OFFSET_COMPAT_PROCESS_PEB_ARGV + __ARCH_COMPAT_SIZEOF_SIZE_T) < OFFSET_COMPAT_PROCESS_PEB_ARGC
	byte_t __pp_pad[OFFSET_COMPAT_PROCESS_PEB_ARGC - (OFFSET_COMPAT_PROCESS_PEB_ARGV + __ARCH_COMPAT_SIZEOF_SIZE_T)];
#elif (OFFSET_COMPAT_PROCESS_PEB_ARGV + __ARCH_COMPAT_SIZEOF_SIZE_T) > OFFSET_COMPAT_PROCESS_PEB_ARGC
#error "Invalid offsets"
#endif /* ... */
	size_t pp_argc;
#endif /* OFFSET_COMPAT_PROCESS_PEB_ARGC >= OFFSET_COMPAT_PROCESS_PEB_ARGV */
};

PRIVATE NONNULL((1, 2)) void KCALL
compat_peb_print_cmdline(struct mman *__restrict mm, pformatprinter printer,
                         void *arg, NCX struct compat_process_peb const *peb) {
	struct _compat_peb_cmdline_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_COMPAT_PROCESS_PEB_ARGC, &info, sizeof(info));
	ProcFS_PrintCompatUserSpaceStringArray(mm, printer, arg, info.pp_argc, info.pp_argv);
}
#endif /* __ARCH_HAVE_COMPAT */

INTERN NONNULL((1, 2)) void KCALL
procfs_pp_cmdline_print(struct printnode *__restrict self,
                        pformatprinter printer, void *arg,
                        pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *threadmm;
	NCX void *peb;

	/* Lookup the relevant mman. */
	thread   = taskpid_gettask_srch(self->fn_fsdata);
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	if (threadmm == &mman_kernel) {
		/* Special case: printing the commandline of a kernel thread. */
		char const *cmd;
		size_t length;
		decref_nokill(threadmm);
		cmd    = kernel_driver.d_cmdline;
		length = strlen(cmd);
		while (cmd[length + 1]) {
			++length;
			length += strlen(cmd + length);
		}
		(*printer)(arg, cmd, length);
		return;
	}
	FINALLY_DECREF_UNLIKELY(threadmm);
	peb = atomic_read(&FORMMAN(threadmm, thismman_execinfo).mei_peb);
#ifdef __ARCH_HAVE_COMPAT
	if (atomic_read(&FORMMAN(threadmm, thismman_execinfo).mei_peb_iscompat)) {
		compat_peb_print_cmdline(threadmm, printer, arg,
		                         (NCX struct compat_process_peb const *)peb);
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
		peb_print_cmdline(threadmm, printer, arg,
		                  (NCX struct process_peb const *)peb);
	}
}



/************************************************************************/
/* /proc/[PID]/comm                                                     */
/************************************************************************/
INTERN NONNULL((1, 2)) void KCALL
procfs_pp_comm_print(struct printnode *__restrict self,
                     pformatprinter printer, void *arg,
                     pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	char name[TASK_COMM_LEN];
	thread = taskpid_gettask_srch(self->fn_fsdata);
	FINALLY_DECREF_UNLIKELY(thread);
	task_getcomm_of(thread, name);
	(*printer)(arg, name, strlen(name));
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
procfs_pp_comm_write(struct mfile *__restrict self, NCX void const *src,
                     size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	REF struct task *thread;
	struct printnode *me = mfile_asprintnode(self);
	char newname[TASK_COMM_LEN];
	size_t setlen;

	/* Can only write at addr=0 */
	if (addr != 0)
		THROW(E_IOERROR_BADBOUNDS, E_IOERROR_SUBSYSTEM_FILE);

	/* Must be within the same process. */
	if (taskpid_getprocpid(me->fn_fsdata) != task_getprocpid()) {
		THROW(E_ILLEGAL_BECAUSE_GROUPING,
		      E_ILLEGAL_OPERATION_CONTEXT_PROC_COMM_DIFFERENT_PROCESS,
		      taskpid_gettid_s(me->fn_fsdata));
	}
	thread = taskpid_gettask_srch(me->fn_fsdata);
	FINALLY_DECREF_UNLIKELY(thread);
	setlen = num_bytes;
	if (setlen > TASK_COMM_LEN * sizeof(char))
		setlen = TASK_COMM_LEN * sizeof(char);
	memcpy(newname, src, setlen);

	/* NOTE: `task_setcomm_of()' does all of the
	 * NUL-termination and sanitization for  us! */
	if (!task_setcomm_of(thread, newname))
		THROW(E_PROCESS_EXITED, taskpid_gettid_s(me->fn_fsdata));
	return num_bytes;
}



/************************************************************************/
/* /proc/[PID]/environ                                                  */
/************************************************************************/
struct _peb_environ_buffer {
#if OFFSET_PROCESS_PEB_ENVC < OFFSET_PROCESS_PEB_ENVP
	size_t pp_envc;
#if (OFFSET_PROCESS_PEB_ENVC + __SIZEOF_SIZE_T__) < OFFSET_PROCESS_PEB_ENVP
	byte_t __pp_pad[OFFSET_PROCESS_PEB_ENVP - (OFFSET_PROCESS_PEB_ENVC + __SIZEOF_SIZE_T__)];
#elif (OFFSET_PROCESS_PEB_ENVC + __SIZEOF_SIZE_T__) > OFFSET_PROCESS_PEB_ENVP
#error "Invalid offsets"
#endif /* ... */
	char const *NCX UNCHECKED const *NCX UNCHECKED pp_envp;
#else /* OFFSET_PROCESS_PEB_ENVC < OFFSET_PROCESS_PEB_ENVP */
	char const *NCX UNCHECKED const *NCX UNCHECKED pp_envp;
#if (OFFSET_PROCESS_PEB_ENVP + __SIZEOF_SIZE_T__) < OFFSET_PROCESS_PEB_ENVC
	byte_t __pp_pad[OFFSET_PROCESS_PEB_ENVC - (OFFSET_PROCESS_PEB_ENVP + __SIZEOF_SIZE_T__)];
#elif (OFFSET_PROCESS_PEB_ENVP + __SIZEOF_SIZE_T__) > OFFSET_PROCESS_PEB_ENVC
#error "Invalid offsets"
#endif /* ... */
	size_t pp_envc;
#endif /* OFFSET_PROCESS_PEB_ENVC >= OFFSET_PROCESS_PEB_ENVP */
};

PRIVATE NONNULL((1, 2)) void KCALL
peb_print_environ(struct mman *__restrict mm, pformatprinter printer,
                   void *arg, NCX struct process_peb const *peb) {
	struct _peb_environ_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_PROCESS_PEB_ENVC, &info, sizeof(info));
	ProcFS_PrintUserSpaceStringArray(mm, printer, arg, info.pp_envc, info.pp_envp);
}

#ifdef __ARCH_HAVE_COMPAT
struct _compat_peb_environ_buffer {
#if OFFSET_COMPAT_PROCESS_PEB_ENVC < OFFSET_COMPAT_PROCESS_PEB_ENVP
	compat_size_t pp_envc;
#if (OFFSET_COMPAT_PROCESS_PEB_ENVC + __ARCH_COMPAT_SIZEOF_SIZE_T) < OFFSET_COMPAT_PROCESS_PEB_ENVP
	byte_t __pp_pad[OFFSET_COMPAT_PROCESS_PEB_ENVP - (OFFSET_COMPAT_PROCESS_PEB_ENVC + __ARCH_COMPAT_SIZEOF_SIZE_T)];
#elif (OFFSET_COMPAT_PROCESS_PEB_ENVC + __ARCH_COMPAT_SIZEOF_SIZE_T) > OFFSET_COMPAT_PROCESS_PEB_ENVP
#error "Invalid offsets"
#endif /* ... */
	compat_ptr(compat_uintptr_t) pp_envp;
#else /* OFFSET_COMPAT_PROCESS_PEB_ENVC < OFFSET_COMPAT_PROCESS_PEB_ENVP */
	compat_ptr(compat_uintptr_t) pp_envp;
#if (OFFSET_COMPAT_PROCESS_PEB_ENVP + __ARCH_COMPAT_SIZEOF_SIZE_T) < OFFSET_COMPAT_PROCESS_PEB_ENVC
	byte_t __pp_pad[OFFSET_COMPAT_PROCESS_PEB_ENVC - (OFFSET_COMPAT_PROCESS_PEB_ENVP + __ARCH_COMPAT_SIZEOF_SIZE_T)];
#elif (OFFSET_COMPAT_PROCESS_PEB_ENVP + __ARCH_COMPAT_SIZEOF_SIZE_T) > OFFSET_COMPAT_PROCESS_PEB_ENVC
#error "Invalid offsets"
#endif /* ... */
	size_t pp_envc;
#endif /* OFFSET_COMPAT_PROCESS_PEB_ENVC >= OFFSET_COMPAT_PROCESS_PEB_ENVP */
};

PRIVATE NONNULL((1, 2)) void KCALL
compat_peb_print_environ(struct mman *__restrict mm, pformatprinter printer,
                         void *arg, NCX struct compat_process_peb const *peb) {
	struct _compat_peb_environ_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_COMPAT_PROCESS_PEB_ENVC, &info, sizeof(info));
	ProcFS_PrintCompatUserSpaceStringArray(mm, printer, arg, info.pp_envc, info.pp_envp);
}
#endif /* __ARCH_HAVE_COMPAT */

INTERN NONNULL((1, 2)) void KCALL
procfs_pp_environ_print(struct printnode *__restrict self,
                        pformatprinter printer, void *arg,
                        pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *threadmm;
	NCX void *peb;

	/* Lookup the relevant mman. */
	thread   = taskpid_gettask_srch(self->fn_fsdata);
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(threadmm);
	peb = atomic_read(&FORMMAN(threadmm, thismman_execinfo).mei_peb);
#ifdef __ARCH_HAVE_COMPAT
	if (atomic_read(&FORMMAN(threadmm, thismman_execinfo).mei_peb_iscompat)) {
		compat_peb_print_environ(threadmm, printer, arg,
		                         (NCX struct compat_process_peb const *)peb);
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
		peb_print_environ(threadmm, printer, arg,
		                  (NCX struct process_peb const *)peb);
	}
}



/************************************************************************/
/* /proc/[PID]/maps                                                     */
/************************************************************************/
/* Check if `self' has a special names, and if so: return that name. */
INTERN NOBLOCK ATTR_CONST WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL nameof_special_file)(struct mfile *__restrict self) {
	/* The libdl program hard-coded into the kernel. */
	if (self == &execabi_system_rtld_file.mrf_file)
		return RTLD_LIBDL;
#ifdef __ARCH_HAVE_COMPAT
	if (self == &compat_execabi_system_rtld_file.mrf_file)
		return COMPAT_RTLD_LIBDL;
#endif /* __ARCH_HAVE_COMPAT */
	if (self == &mfile_zero)
		return "/dev/zero";
	if (self == &mfile_phys)
		return "/dev/mem";
	if (self >= mfile_anon && self < COMPILER_ENDOF(mfile_anon))
		return "[anon]";
	if (self == &mfile_ndef)
		return "[undef]";
#ifdef CONFIG_HAVE_KERNEL_DEBUG_HEAP
	if (self == &mfile_dbgheap)
		return "[dbgheap]";
#endif /* CONFIG_HAVE_KERNEL_DEBUG_HEAP */
	return NULL;
}


struct maps_printer_data {
	pformatprinter   pd_printer; /* [1..1] The target printer. */
	void            *pd_arg;     /* [?..?] Argument for `pd_printer' */
	REF struct path *pd_root;    /* [0..1] Lazily initialized root directory of parent. */
	atflag_t         pd_atflags; /* [valid_if(pd_root)] AT_* flags */
};

INTERN NONNULL((1)) ssize_t FCALL
maps_print_name(struct maps_printer_data *__restrict ctx,
                struct mfile *file, struct path *fspath,
                struct fdirent *fsname) {
	ssize_t result;
	pformatprinter printer;
	void *arg;
	printer = ctx->pd_printer;
	arg     = ctx->pd_arg;
	if (fsname) {
		if (fspath) {
			if (!ctx->pd_root) {
				ctx->pd_atflags = fs_atflags(0) | AT_PATHPRINT_INCTRAIL;
				ctx->pd_root    = fs_getroot(THIS_FS);
			}
			result = path_printent(fspath, fsname->fd_name,
			                       fsname->fd_namelen, printer, arg,
			                       ctx->pd_atflags, ctx->pd_root);
		} else if (fsname->fd_name[0] == '/') {
			result = print(fsname->fd_name,
			               fsname->fd_namelen);
		} else {
			result = printf("?/%$#q",
			                (size_t)fsname->fd_namelen,
			                fsname->fd_name);
		}
	} else if (file) {
		/* Check if it's a device file (in which case we can extract the filename). */
		if (mfile_isdevice(file)) {
			REF struct path *devfs_mount;
			struct devdirent *name;
			struct device *dev = mfile_asdevice(file);
			device_getname_lock_acquire(dev);
			name = incref(dev->dv_dirent);
			device_getname_lock_release(dev);
			FINALLY_DECREF_UNLIKELY(name);
			devfs_mount = vfs_mount_location(THIS_VFS, &devfs.fs_root);
			if (devfs_mount) {
				if (!ctx->pd_root) {
					ctx->pd_atflags = fs_atflags(0) | AT_PATHPRINT_INCTRAIL;
					ctx->pd_root    = fs_getroot(THIS_FS);
				}
				FINALLY_DECREF_UNLIKELY(devfs_mount);
				result = path_printent(devfs_mount, name->dd_dirent.fd_name,
				                       name->dd_dirent.fd_namelen, printer, arg,
				                       ctx->pd_atflags, ctx->pd_root);
			} else {
				result = printf("devfs:/%$s",
				                (size_t)name->dd_dirent.fd_namelen,
				                name->dd_dirent.fd_name);
			}
		} else {
			/* Lastly, there are a couple of special files for which we know names. */
			char const *special_name;
			special_name = nameof_special_file(file);
			if (special_name) {
				result = print(special_name, strlen(special_name));
			} else {
				/* For everything else, just print the /proc/[pid]/fd/[fdno] link text. */
				result = mfile_uprintlink(file, printer, arg);
			}
		}
	} else {
		result = 0;
	}
	return result;
}

PRIVATE ssize_t FCALL
maps_printer_cb(void *maps_arg, struct mmapinfo *__restrict info) {
	dev_t dev = 0;
	ino_t ino = 0;
	struct maps_printer_data *ctx;
	pformatprinter printer;
	void *arg;
	ctx     = (struct maps_printer_data *)maps_arg;
	printer = ctx->pd_printer;
	arg     = ctx->pd_arg;

	if (info->mmi_file && mfile_isnode(info->mmi_file)) {
		struct fnode *node = mfile_asnode(info->mmi_file);
		struct mfile *superdev;
		mfile_tslock_acquire(node);
		ino = node->fn_ino;
		mfile_tslock_release(node);
		superdev = node->fn_super->fs_dev;
		if (superdev != NULL && mfile_isdevnode(superdev))
			dev = mfile_asdevnode(superdev)->dn_devno;
	}

	if (printf("%.8" PRIxPTR "-%.8" PRIxPTR " "     /* from-to */
	           "%c%c%c%c "                          /* [r-][w-][x-][sp] */
	           "%.8" PRIxN(__SIZEOF_OFF64_T__) " "  /* offset */
	           "%.2" PRIxN(__SIZEOF_MAJOR_T__) ":"  /* dev:major */
	           "%.2" PRIxN(__SIZEOF_MINOR_T__) " "  /* dev:minor */
	           "%-7" PRIuN(__SIZEOF_INO64_T__) " ", /* inode */
	           info->mmi_min, (byte_t *)info->mmi_max + 1,
	           info->mmi_flags & MNODE_F_PREAD /* */ ? 'r' : '-',
	           info->mmi_flags & MNODE_F_PWRITE /**/ ? 'w' : '-',
	           info->mmi_flags & MNODE_F_PEXEC /* */ ? 'x' : '-',
	           info->mmi_flags & MNODE_F_SHARED /**/ ? 's' : 'p',
	           info->mmi_offset,
	           major(dev), minor(dev), ino) < 0)
		goto err;
	if (maps_print_name(ctx, info->mmi_file, info->mmi_fspath, info->mmi_fsname) < 0)
		goto err;
	if (PRINT("\n") < 0)
		goto err;
	return 0;
err:
	return -1;
}

INTERN NONNULL((1, 2)) void KCALL
procfs_pp_maps_print(struct printnode *__restrict self,
                     pformatprinter printer, void *arg,
                     pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *threadmm;
	struct maps_printer_data pd;
	thread = taskpid_gettask(self->fn_fsdata);
	if unlikely(!thread)
		return;
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(threadmm);
	pd.pd_printer = printer;
	pd.pd_arg     = arg;
	pd.pd_root    = NULL;
	RAII_FINALLY { xdecref_unlikely(pd.pd_root); };

	/* Enumerate nodes and print the maps-file. */
	mman_enum_userspace(threadmm, &maps_printer_cb, &pd);
}




/************************************************************************/
/* /proc/[PID]/smaps                                                    */
/************************************************************************/
PRIVATE ssize_t FCALL
smaps_printer_cb(void *maps_arg, struct mmapinfo_ex *__restrict info) {
	struct maps_printer_data *ctx;
	pformatprinter printer;
	void *arg;
	if (maps_printer_cb(maps_arg, info))
		return -1;
	ctx     = (struct maps_printer_data *)maps_arg;
	printer = ctx->pd_printer;
	arg     = ctx->pd_arg;
	if (printf("Size:\t" /*           */ "%" PRIuSIZ " kB\n"
	           "Rss:\t" /*            */ "0 kB\n" /* ??? */
	           "Pss:\t" /*            */ "0 kB\n" /* ??? */
	           "Shared_Clean:\t" /*   */ "%" PRIuSIZ " kB\n"
	           "Shared_Dirty:\t" /*   */ "%" PRIuSIZ " kB\n"
	           "Private_Clean:\t" /*  */ "%" PRIuSIZ " kB\n"
	           "Private_Dirty:\t" /*  */ "%" PRIuSIZ " kB\n"
	           "Referenced:\t" /*     */ "%" PRIuSIZ " kB\n"
	           "Anonymous:\t" /*      */ "%" PRIuSIZ " kB\n"
	           "AnonHugePages:\t" /*  */ "0 kB\n" /* KOS does huge page merging automatically */
	           "Shared_Hugetlb:\t" /* */ "0 kB\n" /* KOS does huge page merging automatically */
	           "Private_Hugetlb:\t" /**/ "0 kB\n" /* KOS does huge page merging automatically */
	           "Swap:\t" /*           */ "%" PRIuSIZ " kB\n"
	           "SwapPss:\t" /*        */ "0 kB\n" /* ??? */
	           "KernelPageSize:\t" /* */ "%" PRIuSIZ " kB\n"
	           "MMUPageSize:\t" /*    */ "%" PRIuSIZ " kB\n"
	           "Locked:\t" /*         */ "%" PRIuSIZ " kB\n"
	           "VmFlags:",
	           mmapinfo_size(info) / 1024,                                                                  /* Size */
	           !(info->mmi_flags & MNODE_F_SHARED) ? 0 : ((info->mmix_loaded - info->mmix_changed) / 1024), /* Shared_Clean */
	           !(info->mmi_flags & MNODE_F_SHARED) ? 0 : (info->mmix_changed / 1024),                       /* Shared_Dirty */
	           (info->mmi_flags & MNODE_F_SHARED) ? 0 : (info->mmix_loaded - info->mmix_changed) / 1024,    /* Private_Clean */
	           (info->mmi_flags & MNODE_F_SHARED) ? 0 : (info->mmix_changed / 1024),                        /* Private_Dirty */
	           info->mmix_loaded / 1024,                                                                    /* Referenced */
	           !info->mmi_file || !mfile_isanon(info->mmi_file) ? 0 : info->mmix_loaded / 1024,             /* Anonymous */
	           info->mmix_swap / 1024,                                                                      /* Swap */
	           PAGESIZE / 1024 /* ??? */,                                                                   /* KernelPageSize */
	           PAGESIZE / 1024 /* ??? */,                                                                   /* MMUPageSize */
	           info->mmix_locked / 1024                                                                     /* Locked */
	           ) < 0)
		return -1;
	if (info->mmi_flags & MNODE_F_PREAD)
		PRINT(" rd");
	if (info->mmi_flags & MNODE_F_PWRITE)
		PRINT(" wr");
	if (info->mmi_flags & MNODE_F_PEXEC)
		PRINT(" ex");
	if (info->mmi_flags & MNODE_F_SHARED)
		PRINT(" sh");

	/* linux: VM_MAYREAD (XXX: am I doing this right?)
	 * On KOS, anything that is mmap-able can be mapped for reading */
	PRINT(" mr");

	/* linux: VM_MAYWRITE  (XXX:  am I  doing  this right?)
	 * Files marked as READONLY cannot be PROT_WRITE-mapped */
	if (!(info->mmi_file->mf_flags & MFILE_F_READONLY))
		PRINT(" mw");

	/* linux: VM_MAYEXEC (XXX: am I doing this right?)
	 * XXX: maybe disallow if:
	 * >> mfile_isnode(info->mmi_file) != NULL &&
	 * >> mfile_asnode(info->mmi_file)->fn_super->fs_root.mf_flags & MFILE_FS_NOEXEC */
	PRINT(" me");

	/* linux: VM_MAYSHARE (XXX: am I doing this right?)
	 * All file mappings allow for sharing. */
	PRINT(" ms");

	if (info->mmi_flags & MNODE_F_MLOCK)
		PRINT(" lo");
	return PRINT("\n");
}

INTERN NONNULL((1, 2)) void KCALL
procfs_pp_smaps_print(struct printnode *__restrict self,
                      pformatprinter printer, void *arg,
                      pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *threadmm;
	struct maps_printer_data pd;
	thread = taskpid_gettask(self->fn_fsdata);
	if unlikely(!thread)
		return;
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(threadmm);
	pd.pd_printer = printer;
	pd.pd_arg     = arg;
	pd.pd_root    = NULL;
	RAII_FINALLY { xdecref_unlikely(pd.pd_root); };

	/* Enumerate nodes and print the maps-file. */
	mman_enum_userspace_ex(threadmm, &smaps_printer_cb, &pd);
}




/************************************************************************/
/* /proc/[PID]/mounts                                                   */
/************************************************************************/
PRIVATE NONNULL((1, 2, 3)) ssize_t KCALL
print_mounting_point(struct path *__restrict fsroot,
                     struct pathmount *__restrict self,
                     pformatprinter printer, void *arg) {
	char flagsbuf[128], *writer;
	struct fsuper *super = path_getsuper(self);
	uintptr_t flags;

	/* Name of the mounted device, or filename system. */
	if (super->fs_dev) {
		mfile_uprintlink(super->fs_dev, printer, arg);
	} else {
		print(super->fs_sys->ffs_name, strlen(super->fs_sys->ffs_name));
	}
	if (PRINT(" ") < 0)
		goto err;

	/* Mounting point path name. */
	path_print(self, printer, arg, 0, fsroot);
	if (PRINT(" ") < 0)
		goto err;

	/* Filename system. */
	if (printf("%s ", super->fs_sys->ffs_name) < 0)
		goto err;

	/* Filesystem flags. */
	flags = atomic_read(&super->fs_root.mf_flags);
	if (super->fs_dev)
		flags |= atomic_read(&super->fs_dev->mf_flags) & MFILE_F_READONLY;

	writer = flagsbuf;
	writer = stpcpy(writer, (flags & MFILE_F_READONLY) ? "ro" : "rw");
//TODO:	if (flags & MS_SYNCHRONOUS)
//TODO:		writer = stpcpy(writer, ",sync");
//TODO:	if (flags & MS_DIRSYNC)
//TODO:		writer = stpcpy(writer, ",dirsync");
//TODO:	if (flags & MS_MANDLOCK)
//TODO:		writer = stpcpy(writer, ",mand");
	if (flags & MFILE_F_LAZYTIME)
		writer = stpcpy(writer, ",lazytime");
	if (flags & MFILE_FS_NOSUID)
		writer = stpcpy(writer, ",nosuid");
	if (super->fs_dev == NULL)
		writer = stpcpy(writer, ",nodev");
	if (flags & MFILE_FS_NOEXEC)
		writer = stpcpy(writer, ",noexec");
	if (flags & MFILE_F_NOATIME)
		writer = stpcpy(writer, ",noatime");
	if (flags & MFILE_FN_NODIRATIME)
		writer = stpcpy(writer, ",nodiratime");
	if (flags & MFILE_F_RELATIME)
		writer = stpcpy(writer, ",relatime");
	if (print(flagsbuf, strlen(flagsbuf)) < 0)
		goto err;
	/* TODO: Filesystem drivers should also be able to print additional options:
	 * - e.g.: "fat" should print `user_id=...,group_id=...' */

	/* When  parsed by `getmntent(3)', these 2 values become `mnt_freq' and `mnt_passno'.
	 * Note that we unconditionally print `0' for both of them since linux does the same. */
	return PRINT(" 0 0\n");
err:
	return -1;
}

INTERN NONNULL((1, 2)) void KCALL
procfs_pp_mounts_print(struct printnode *__restrict self,
                       pformatprinter printer, void *arg,
                       pos_t UNUSED(offset_hint)) {
	REF struct path *fsroot;
	REF struct pathmount *iter;
	REF struct vfs *threadvfs;
	REF struct task *thread = taskpid_gettask(self->fn_fsdata);
	if unlikely(!thread)
		return;
	threadvfs = task_getvfs(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(threadvfs);
	fsroot = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(fsroot);
	iter = vfs_mounts_next(threadvfs, NULL);
	while (iter) {
		FINALLY_DECREF_UNLIKELY(iter);
		if (print_mounting_point(fsroot, iter, printer, arg))
			break;
		iter = vfs_mounts_next(threadvfs, iter);
	}
}




/************************************************************************/
/* /proc/[PID]/stat                                                     */
/************************************************************************/
/* Return the total # of bytes of mapped memory from `self'. */
PRIVATE NOBLOCK ATTR_PURE NONNULL((1, 2)) size_t
NOTHROW(FCALL mnode_tree_get_total_mapped_bytes)(struct mnode const *root,
                                                 struct mnode const *skipme) {
	size_t result = 0;
again:
	if (root != skipme)
		result += mnode_getsize(root);
	if (root->mn_mement.rb_lhs) {
		if (root->mn_mement.rb_rhs)
			result += mnode_tree_get_total_mapped_bytes(root->mn_mement.rb_rhs, skipme);
		root = root->mn_mement.rb_lhs;
		goto again;
	}
	if (root->mn_mement.rb_rhs) {
		root = root->mn_mement.rb_rhs;
		goto again;
	}
	return result;
}

PRIVATE NOBLOCK ATTR_PURE NONNULL((1)) size_t
NOTHROW(FCALL mman_get_total_mapped_bytes)(struct mman const *__restrict self) {
	if unlikely(!self->mm_mappings)
		return 0;
	return mnode_tree_get_total_mapped_bytes(self->mm_mappings,
	                                         &FORMMAN(self, thismman_kernel_reservation));
}

INTERN NONNULL((1, 2)) void KCALL
procfs_pp_stat_print(struct printnode *__restrict self,
                     pformatprinter printer, void *arg,
                     pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *mm = NULL;
	struct taskpid *tpid;
#ifdef CONFIG_HAVE_KERNEL_TASK_COMM
	char comm_name[TASK_COMM_LEN];
#endif /* CONFIG_HAVE_KERNEL_TASK_COMM */
	tpid   = self->fn_fsdata;
	thread = taskpid_gettask(tpid);
	FINALLY_XDECREF_UNLIKELY(thread);
	if (thread)
		mm = task_getmman(thread);
	FINALLY_XDECREF_UNLIKELY(mm);
	if (printf("%" PRIuN(__SIZEOF_PID_T__) " (",
	           taskpid_gettid_s(tpid)) < 0)
		return;
#ifdef CONFIG_HAVE_KERNEL_TASK_COMM
	comm_name[0] = '\0';
	if (thread)
		task_getcomm_of(thread, comm_name);
	if (comm_name[0] != '\0') {
		/* Print custom thread command name. */
		printf("%#q", comm_name);
	} else
#endif /* CONFIG_HAVE_KERNEL_TASK_COMM */
	if (mm) {
		bool has_path;
		REF struct fdirent *exec_name;
		char const *exec_namestr;
		u16 exec_namelen;
		mman_lock_read(mm);
		has_path  = FORMMAN(mm, thismman_execinfo.mei_path) != NULL;
		exec_name = xincref(FORMMAN(mm, thismman_execinfo.mei_dent));
		mman_lock_endread(mm);
		if (!exec_name)
			goto no_exec;
		FINALLY_DECREF_UNLIKELY(exec_name);
		exec_namestr = exec_name->fd_name;
		exec_namelen = exec_name->fd_namelen;
		if (!has_path) {
			/* The path may be embedded within the exec name. */
			char const *newbase;
			newbase = (char const *)memrend(exec_namestr, '/', exec_namelen);
			exec_namelen -= (size_t)(newbase - exec_namestr);
			exec_namestr = newbase;
		}
		print(exec_namestr, exec_namelen);
	} else {
no_exec:
		PRINT("?");
	}
	PRINT(") ");
	{
		char state;
		if (thread) {
			uintptr_t flags;
			flags = atomic_read(&thread->t_flags);
			if (flags & TASK_FRUNNING) {
				state = 'R'; /* Running */
			} else if (flags & (TASK_FSUSPENDED | TASK_FGDB_STOPPED)) {
				state = 'T'; /* Stopped */
			} else if (flags & TASK_FSTARTED) {
				state = 'S'; /* Sleeping */
			} else {
				/* XXX: 'W' For waking??? */
				state = 'P'; /* Parked? */
			}
		} else {
			/* XXX: 'X' For dead??? */
			state = 'Z'; /* Zombie */
		}
		print(&state, 1);
	}
	if (printf(" %" PRIuN(__SIZEOF_PID_T__) " ",
	           taskpid_getppid_s(tpid)) < 0)
		return;
	{
		dev_t tty_devno;
		u32 tty_devno_encoded;
		pid_t fgpid;
		REF struct procgrp *grp;
		REF struct ttydev *tty;
		grp = taskpid_getprocgrp(tpid);
		FINALLY_DECREF_UNLIKELY(grp);
		if (printf("%" PRIuN(__SIZEOF_PID_T__) " "
		           "%" PRIuN(__SIZEOF_PID_T__) " ",
		           procgrp_getpgid_s(grp),
		           procgrp_getsid_s(grp)) < 0)
			return;
		tty_devno = 0;
		fgpid     = 0;
		tty       = procgrp_getctty(grp);
		if (tty) {
			REF struct procgrp *fg;
			tty_devno = device_getdevno(tty);
			fg        = ttydev_getfproc(tty);
			decref_unlikely(tty);
			if (fg) {
				fgpid = procgrp_getpgid_s(fg);
				decref_unlikely(fg);
			}
		}
		tty_devno_encoded = ((major(tty_devno) & 0xff) << 8) |
		                    ((minor(tty_devno) & 0xff) |
		                     (minor(tty_devno) & 0xffff00) << 8);
		if (printf("%" PRIu32 " "
		           "%" PRIuN(__SIZEOF_PID_T__) " ",
		           tty_devno_encoded, fgpid) < 0)
			return;
	}
	if ((*printer)(arg, "0 ", 2) < 0)
		return; /* Flags? */
	if ((*printer)(arg, "1 ", 2) < 0)
		return; /* TODO: minflt */
	if ((*printer)(arg, "1 ", 2) < 0)
		return; /* TODO: cminflt */
	if ((*printer)(arg, "1 ", 2) < 0)
		return; /* TODO: majflt */
	if ((*printer)(arg, "1 ", 2) < 0)
		return; /* TODO: cmajflt */
	if ((*printer)(arg, "1 ", 2) < 0)
		return; /* TODO: utime */
	if ((*printer)(arg, "1 ", 2) < 0)
		return; /* TODO: stime */
	if ((*printer)(arg, "1 ", 2) < 0)
		return; /* TODO: cutime */
	if ((*printer)(arg, "1 ", 2) < 0)
		return; /* TODO: cstime */
	if ((*printer)(arg, "20 ", 2) < 0)
		return; /* TODO: priority */
	if ((*printer)(arg, "0 ", 2) < 0)
		return; /* TODO: nice */
	/* num_threads */
	if (mm) {
		size_t thread_count = 0;
		struct task *iter;
		mman_threadslock_acquire(mm);
		LIST_FOREACH (iter, &mm->mm_threads, t_mman_tasks) {
			++thread_count;
		}
		mman_threadslock_release(mm);
		if (printf("%" PRIuSIZ " ",
		                  thread_count) < 0)
			return;
	} else {
		if ((*printer)(arg, "1 ", 2) < 0)
			return;
	}
	if ((*printer)(arg, "0 ", 2) < 0)
		return; /* itrealvalue */
	/* starttimes */
	if ((*printer)(arg, "0 ", 2) < 0)
		return;
	if (mm) {
		size_t vsize;
		mman_lock_read(mm);
		vsize = mman_get_total_mapped_bytes(mm);
		mman_lock_endread(mm);
		if (printf("%" PRIuSIZ " ", vsize) < 0)
			return;
	} else {
		if ((*printer)(arg, "0 ", 2) < 0)
			return; /* vsize */
	}
	if (printf("1 "            /* TODO: rss */
	           "1 "            /* TODO: rsslim */
	           "%" PRIuPTR " " /* startcode */
	           "%" PRIuPTR " " /* endcode */
	           "%" PRIuPTR " " /* startstack */
	           "%" PRIuPTR " " /* kstkesp */
	           "%" PRIuPTR " " /* kstkeip */
	           "",
#ifdef KERNELSPACE_HIGHMEM
	           0,                /* TODO: startcode */
	           KERNELSPACE_BASE, /* TODO: endcode */
#else /* KERNELSPACE_HIGHMEM */
	           KERNEL_CEILING, /* TODO: startcode */
	           (void *)-1,     /* TODO: endcode */
#endif /* !KERNELSPACE_HIGHMEM */
	           (void *)1234,     /* TODO: startstack */
	           (void *)1234,     /* TODO: kstkesp */
	           (void *)1234      /* TODO: kstkeip */
	           ) < 0)
		return;

	if (printf("0 "                              /* TODO: signal */
	           "0 "                              /* TODO: blocked */
	           "0 "                              /* TODO: sigignore */
	           "0 "                              /* TODO: sigcatch */
	           "0 "                              /* TODO: wchan */
	           "0 "                              /* TODO: nswap */
	           "0 "                              /* TODO: cnswap */
	           "%" PRIuN(__SIZEOF_SIGNO_T__) " " /* exit_signal */
	           "%u "                             /* processor */
	           ,
	           /* TODO: exit_signal (as set by clone_flags & CSIGNAL) */
	           SIGCLD,
	           /* processor */
	           thread ? (unsigned int)thread->t_cpu->c_id
	                  : (unsigned int)bootcpu.c_id) < 0)
		return;
	if (PRINT("0 " /* TODO: rt_priority */
	          "0 " /* TODO: rt_priority */
	          "0 " /* TODO: rt_priority */
	          "0 " /* TODO: policy */
	          "0 " /* TODO: delayacct_blkio_ticks */
	          "0 " /* TODO: guest_time */
	          "0 " /* TODO: cguest_time */
	          ) < 0)
		return;
	printf("%" PRIuPTR " " /* start_data */
	       "%" PRIuPTR " " /* end_data */
	       "0 "            /* TODO: start_brk... (NOTE: This is maintained by libc, so we can't actually know this one...) */
	       "0 "            /* TODO: arg_start */
	       "0 "            /* TODO: arg_end */
	       "0 "            /* TODO: env_start */
	       "0 "            /* TODO: env_end */
	       "%" PRIu16,     /* exit_code */
#ifdef KERNELSPACE_HIGHMEM
	       0,                /* TODO: start_data */
	       KERNELSPACE_BASE, /* TODO: end_data */
#else /* KERNELSPACE_HIGHMEM */
	       KERNEL_CEILING, /* TODO: start_data */
	       (void *)-1,     /* TODO: end_data */
#endif /* !KERNELSPACE_HIGHMEM */
	       tpid->tp_status);
}




/************************************************************************/
/* /proc/[PID]/status                                                   */
/************************************************************************/
PRIVATE ATTR_PURE WUNUSED NONNULL((1)) uint64_t
NOTHROW(FCALL credcap_as_u64)(struct credcap const *__restrict self) {
	uint64_t result = 0;
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
	memcpy(&result, self->cc_caps, MIN(8, sizeof(self->cc_caps)));
#else /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
	memcpy((byte_t *)&result + 8 - MIN(8, sizeof(self->cc_caps)),
	       self->cc_caps, MIN(8, sizeof(self->cc_caps)));
#endif /* __BYTE_ORDER__ != __ORDER_LITTLE_ENDIAN__ */
	return result;
}

INTERN NONNULL((1, 2)) void KCALL
procfs_pp_status_print(struct printnode *__restrict self,
                       pformatprinter printer, void *arg,
                       pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *thread_mm      = NULL;
	REF struct task *parent         = NULL;
	REF struct cred *thread_cred    = NULL;
	REF struct handman *thread_hman = NULL;
	struct taskpid *tpid;
	char const *state;
	struct mman_statinfo mmstat;
	tpid   = self->fn_fsdata;
	thread = taskpid_gettask(tpid);
	RAII_FINALLY {
		xdecref_unlikely(thread);
		xdecref_unlikely(thread_mm);
		xdecref_unlikely(thread_cred);
		xdecref_unlikely(parent);
		xdecref_unlikely(thread_hman);
	};
	if (thread) {
		thread_mm   = task_getmman(thread);
		thread_cred = task_getcred(thread);
		parent      = task_getparentprocess_of(thread);
		thread_hman = task_gethandman(thread);
	}
	PRINT("Name:\t");
	if (thread_mm) {
		REF struct fdirent *exec_name;
		mman_lock_read(thread_mm);
		exec_name = xincref(FORMMAN(thread_mm, thismman_execinfo).mei_dent);
		mman_lock_endread(thread_mm);
		if (!exec_name)
			goto no_exec;
		FINALLY_DECREF_UNLIKELY(exec_name);
		print(exec_name->fd_name, exec_name->fd_namelen);
	} else {
no_exec:
		PRINT("?");
	}
	if (thread) {
		uintptr_t flags;
		flags = atomic_read(&thread->t_flags);
		if (flags & TASK_FRUNNING) {
			state = "R (running)"; /* Running */
		} else if (flags & (TASK_FSUSPENDED | TASK_FGDB_STOPPED)) {
			state = "T (stopped)"; /* Stopped */
		} else if (flags & TASK_FSTARTED) {
			state = "S (sleeping)"; /* Sleeping */
		} else {
			/* XXX: 'W' For waking??? */
			state = "P (parked)"; /* Parked? */
		}
	} else {
		/* XXX: 'X' For dead??? */
		state = "Z (zombie)";
	}
	if (printf("\n"
	           "State:\t%s\n"
	           "Tgid:\t%" PRIuN(__SIZEOF_PID_T__) "\n"
	           "Ngid:\t0\n" /* Numa group id (not supported by KOS (yet?)) */
	           "Pid:\t%" PRIuN(__SIZEOF_PID_T__) "\n"
	           "PPid:\t%" PRIuN(__SIZEOF_PID_T__) "\n"
	           "TracerPid:\t0\n"
	           "Uid:\t%" PRIuN(__SIZEOF_UID_T__) "\t"
	                 "%" PRIuN(__SIZEOF_UID_T__) "\t"
	                 "%" PRIuN(__SIZEOF_UID_T__) "\t"
	                 "%" PRIuN(__SIZEOF_UID_T__) "\n"
	           "Gid:\t%" PRIuN(__SIZEOF_GID_T__) "\t"
	                 "%" PRIuN(__SIZEOF_GID_T__) "\t"
	                 "%" PRIuN(__SIZEOF_GID_T__) "\t"
	                 "%" PRIuN(__SIZEOF_GID_T__) "\n"
	           "FDSize:\t%u\n"
	           "Groups:\t%" PRIuN(__SIZEOF_GID_T__),
	           state,
	           thread ? task_getpid_of_s(thread) : 0, /* Tgid  (actually: PID) */
	           thread ? task_gettid_of_s(thread) : 0, /* Pid   (actually: TID) */
	           parent ? task_gettid_of_s(parent) : 0, /* PPid */
	           thread_cred ? atomic_read(&thread_cred->c_ruid) : 0,
	           thread_cred ? atomic_read(&thread_cred->c_euid) : 0,
	           thread_cred ? atomic_read(&thread_cred->c_suid) : 0,
	           thread_cred ? atomic_read(&thread_cred->c_fsuid) : 0,
	           thread_cred ? atomic_read(&thread_cred->c_rgid) : 0,
	           thread_cred ? atomic_read(&thread_cred->c_egid) : 0,
	           thread_cred ? atomic_read(&thread_cred->c_sgid) : 0,
	           thread_cred ? atomic_read(&thread_cred->c_fsgid) : 0,
	           thread_hman ? atomic_read(&thread_hman->hm_maxhand) : 0,
	           thread_cred ? atomic_read(&thread_cred->c_fsgid) : 0) < 0)
		return;
	if (thread_cred) {
		size_t i;
		REF struct cred_groups *groups;
		groups = arref_get(&thread_cred->c_groups);
		FINALLY_DECREF_UNLIKELY(groups);
		for (i = 0; i < groups->cg_count; ++i) {
			printf(" %" PRIuN(__SIZEOF_GID_T__),
			       groups->cg_groups[i]);
		}
	}

	bzero(&mmstat, sizeof(mmstat));
	if (thread_mm)
		mman_stat(thread_mm, &mmstat);
	if (printf("\n"
	           "VmPeak:\t" /*      */ "%" PRIuSIZ " kB\n"
	           "VmSize:\t" /*      */ "%" PRIuSIZ " kB\n"
	           "VmLck:\t" /*       */ "%" PRIuSIZ " kB\n"
	           "VmPin:\t" /*       */ "0 kB\n" /* ??? */
	           "VmHWM:\t" /*       */ "%" PRIuSIZ " kB\n"
	           "VmRSS:\t" /*       */ "%" PRIuSIZ " kB\n"
	           "RssAnon:\t" /*     */ "%" PRIuSIZ " kB\n"
	           "RssFile:\t" /*     */ "%" PRIuSIZ " kB\n"
	           "RssShmem:\t" /*    */ "0 kB\n"
	           "VmData:\t" /*      */ "%" PRIuSIZ " kB\n"
	           "VmStk:\t" /*       */ "%" PRIuSIZ " kB\n"
	           "VmExe:\t" /*       */ "%" PRIuSIZ " kB\n"
	           "VmLib:\t" /*       */ "0 kB\n" /* Linux diffs from `VmExe' by keeping track of the original
	                                            * exe's code start/end (but KOS doesn't keep track of that) */
	           "VmPTE:\t" /*       */ "0 kB\n" /* Memory consumed by page directory structures??? */
	           "VmSwap:\t" /*      */ "%" PRIuSIZ " kB\n"
	           "HugetlbPages:\t" /**/ "0 kB\n"
	           "Threads:\t" /*     */ "%" PRIuSIZ "\n",
	           mmstat.msi_size / 1024,                     /* TODO: VmPeak */
	           mmstat.msi_size / 1024,                     /* VmSize */
	           mmstat.msi_lock / 1024,                     /* VmLck */
	           mmstat.msi_size / 1024,                     /* ??? VmHWM */
	           mmstat.msi_size / 1024,                     /* ??? VmRSS */
	           mmstat.msi_anon / 1024,                     /* RssAnon */
	           (mmstat.msi_size - mmstat.msi_anon) / 1024, /* RssFile */
	           mmstat.msi_ndat / 1024,                     /* VmData */
	           mmstat.msi_ndat / 1024,                     /* ??? VmStk */
	           mmstat.msi_nexe / 1024,                     /* VmExe */
	           mmstat.msi_swap / 1024,                     /* VmSwap */
	           thread_mm ? mman_nrthreads(thread_mm) : 0   /* Threads */
	           ) < 0)
		return;

	/* TODO: SigQ:   0/14747 */
	/* TODO: SigPnd: 0000000000000000 */
	/* TODO: ShdPnd: 0000000000000000 */
	/* TODO: SigBlk: 0000000000000000 */
	/* TODO: SigIgn: 0000000000000000 */
	/* TODO: SigCgt: 0000000000000000 */

	if (printf("CapInh:\t" /*    */ "%.16" PRIx64 "\n"
	           "CapPrm:\t" /*    */ "%.16" PRIx64 "\n"
	           "CapEff:\t" /*    */ "%.16" PRIx64 "\n"
	           "CapBnd:\t" /*    */ "%.16" PRIx64 "\n"
	           "CapAmb:\t" /*    */ "%.16" PRIx64 "\n"
	           "NoNewPrivs:\t" /**/ "%" PRIu8 "\n",
	           thread_cred ? credcap_as_u64(&thread_cred->c_cap_inheritable) : 0,
	           thread_cred ? credcap_as_u64(&thread_cred->c_cap_permitted) : 0,
	           thread_cred ? credcap_as_u64(&thread_cred->c_cap_effective) : 0,
	           thread_cred ? credcap_as_u64(&thread_cred->c_cap_bounding) : 0,
	           thread_cred ? credcap_as_u64(&thread_cred->c_cap_ambient) : 0,
	           thread_cred ? thread_cred->c_no_new_privs : 0) < 0)
		return;

	/* TODO: Cpus_allowed:   3 */
	/* TODO: Cpus_allowed_list:      0-1 */

	/* TODO: voluntary_ctxt_switches:        0 */
	/* TODO: nonvoluntary_ctxt_switches:     2 */
}



/************************************************************************/
/* /proc/[PID]/attr/current                                             */
/************************************************************************/
INTERN NONNULL((1, 2)) void KCALL
procfs_pp_attr_current_print(struct printnode *__restrict self,
                             pformatprinter printer, void *arg,
                             pos_t UNUSED(offset_hint)) {
	(void)self;
	PRINT("unconfined");
}



/************************************************************************/
/* /proc/[PID]/kos/peb-addr                                             */
/************************************************************************/
INTERN NONNULL((1, 2)) void KCALL
procfs_pp_kos_peb_addr_print(struct printnode *__restrict self,
                             pformatprinter printer, void *arg,
                             pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *threadmm;
	NCX void *peb;

	/* Lookup the relevant mman. */
	thread   = taskpid_gettask_srch(self->fn_fsdata);
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	peb = atomic_read(&FORMMAN(threadmm, thismman_execinfo).mei_peb);
	decref_unlikely(threadmm);
	format_printf(printer, arg, "%#" PRIxPTR, peb);
}

INTERN NONNULL((1, 2)) size_t KCALL
procfs_pp_kos_peb_addr_write(struct mfile *__restrict self, NCX void const *src,
                             size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) {
	struct printnode *me = mfile_asprintnode(self);
	REF struct task *thread;
	REF struct mman *threadmm;
	NCX void *peb;
	/* Can only write at addr=0 */
	if (addr != 0)
		THROW(E_IOERROR_BADBOUNDS, E_IOERROR_SUBSYSTEM_FILE);

	/* Lookup the relevant mman. */
	thread   = taskpid_gettask_srch(me->fn_fsdata);
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(threadmm);
	if (threadmm != THIS_MMAN) {
		/* May only set the PEB address for your own process. */
		THROW(E_ILLEGAL_BECAUSE_GROUPING,
		      E_ILLEGAL_OPERATION_CONTEXT_PROC_PEB_DIFFERENT_PROCESS,
		      taskpid_gettid_s(me->fn_fsdata));
	}
	peb = ProcFS_ParsePtr(src, num_bytes);
	validate_readableaddr(peb);
	mman_lock_acquire(threadmm);
	atomic_write(&FORMMAN(threadmm, thismman_execinfo).mei_peb, peb);
	mman_lock_release(threadmm);
	return num_bytes;
}



#ifdef __ARCH_HAVE_COMPAT
/************************************************************************/
/* /proc/[PID]/kos/peb-compat                                           */
/************************************************************************/
INTERN NONNULL((1, 2)) void KCALL
procfs_pp_kos_peb_compat_print(struct printnode *__restrict self,
                               pformatprinter printer, void *arg,
                               pos_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *threadmm;
	bool peb_iscompat;

	/* Lookup the relevant mman. */
	thread   = taskpid_gettask_srch(self->fn_fsdata);
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	peb_iscompat = atomic_read(&FORMMAN(threadmm, thismman_execinfo).mei_peb_iscompat);
	decref_unlikely(threadmm);
	ProcFS_PrintBool(printer, arg, peb_iscompat);
}

INTERN NONNULL((1, 2)) size_t KCALL
procfs_pp_kos_peb_compat_write(struct mfile *__restrict self, NCX void const *src,
                               size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) {
	struct printnode *me = mfile_asprintnode(self);
	REF struct task *thread;
	REF struct mman *threadmm;
	bool peb_iscompat;
	/* Can only write at addr=0 */
	if (addr != 0)
		THROW(E_IOERROR_BADBOUNDS, E_IOERROR_SUBSYSTEM_FILE);

	/* Lookup the relevant mman. */
	thread   = taskpid_gettask_srch(me->fn_fsdata);
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(threadmm);
	if (threadmm != THIS_MMAN) {
		/* May only set the PEB address for your own process. */
		THROW(E_ILLEGAL_BECAUSE_GROUPING,
		      E_ILLEGAL_OPERATION_CONTEXT_PROC_PEB_DIFFERENT_PROCESS,
		      taskpid_gettid_s(me->fn_fsdata));
	}
	peb_iscompat = ProcFS_ParseBool(src, num_bytes);
	mman_lock_acquire(threadmm);
	atomic_write(&FORMMAN(threadmm, thismman_execinfo).mei_peb_iscompat, peb_iscompat);
	mman_lock_release(threadmm);
	return num_bytes;
}
#endif /* __ARCH_HAVE_COMPAT */



/************************************************************************/
/* /proc/[PID]/x86/iopl                                                 */
/************************************************************************/
#if defined(__x86_64__) || defined(__i386__)
INTERN NONNULL((1, 2)) void KCALL
procfs_pp_x86_iopl_print(struct printnode *__restrict self,
                         pformatprinter printer, void *arg,
                         pos_t UNUSED(offset_hint)) {
	unsigned int iopl;
	REF struct task *thread;
	thread = taskpid_gettask_srch(self->fn_fsdata);
	{
		FINALLY_DECREF_UNLIKELY(thread);
		iopl = x86_getiopl(thread);
	}
	ProcFS_PrintUInt(printer, arg, iopl);
}

INTERN WUNUSED NONNULL((1)) size_t KCALL
procfs_pp_x86_iopl_write(struct mfile *__restrict self, NCX void const *src,
                         size_t num_bytes, pos_t addr, iomode_t UNUSED(mode)) THROWS(...) {
	struct fnode *me = mfile_asnode(self);
	unsigned int new_iopl;
	REF struct task *thread;
	/* Can only write at addr=0 */
	if (addr != 0)
		THROW(E_IOERROR_BADBOUNDS, E_IOERROR_SUBSYSTEM_FILE);
	new_iopl = ProcFS_ParseUInt(src, num_bytes, 0, 3);
	thread   = taskpid_gettask_srch(me->fn_fsdata);
	FINALLY_DECREF_UNLIKELY(thread);
	x86_setiopl(thread, new_iopl, /* check_creds: */ true);
	return num_bytes;
}
#endif /* __x86_64__ || __i386__ */














/************************************************************************/
/* Special file types (with custom implementations)                     */
/************************************************************************/

/************************************************************************/
/* /proc/[pid]/fd                                                       */
/************************************************************************/

struct procfs_fd_lnknode: flnknode {
	struct handle pfl_hand; /* [1..1][const] Handle. */
};

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_fd_lnknode_v_destroy)(struct mfile *__restrict self) {
	struct procfs_fd_lnknode *me;
	me = (struct procfs_fd_lnknode *)mfile_aslnk(self);
	assert(!LIST_ISBOUND(me, fn_allnodes));
	assert(me->fn_supent.rb_rhs == FSUPER_NODES_DELETED);
	assert(me->mf_parts == MFILE_PARTS_ANONYMOUS);
	handle_decref(me->pfl_hand);
	decref_unlikely(me->fn_fsdata);
	kfree(me);
}
#define procfs_fd_lnknode_v_changed    procfs_perproc_lnknode_v_changed
#define procfs_fd_lnknode_v_wrattr     procfs_perproc_lnknode_v_wrattr
#define procfs_fd_lnknode_v_perm_ops   procfs_perproc_lnknode_v_perm_ops
#define procfs_fd_lnknode_v_free       procfs_perproc_lnknode_v_free
#define procfs_fd_lnknode_v_stream_ops procfs_perproc_lnknode_v_stream_ops

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
procfs_fd_lnknode_v_readlink(struct flnknode *__restrict self,
                             NCX /*utf-8*/ char *buf,
                             size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	struct procfs_fd_lnknode *me;
	struct format_snprintf_data dat;
	me = (struct procfs_fd_lnknode *)mfile_aslnk(self);
	dat.sd_buffer = buf;
	dat.sd_bufsiz = bufsize;
	return (size_t)handle_printlink(me->pfl_hand, &format_snprintf_printer, &dat);
}

PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) bool KCALL
procfs_fd_lnknode_v_openlink(struct flnknode *__restrict self,
                             struct handle *__restrict result,
                             struct path *__restrict UNUSED(access_path),
                             struct fdirent *__restrict UNUSED(access_dent),
                             oflag_t oflags)
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct procfs_fd_lnknode *me;
	unsigned int access_mode;
	static_assert(O_RDONLY == IO_RDONLY);
	static_assert(O_WRONLY == IO_WRONLY);
	static_assert(O_RDWR == IO_RDWR);
	static_assert(O_ACCMODE == IO_ACCMODE);

	/* This is the function that implements the magic for open("/proc/[pid]/fd/[no]"),
	 * such  that  such a  call  behaves as  a  dup(2), rather  than open(readlink())! */
	me = (struct procfs_fd_lnknode *)mfile_aslnk(self);

	/* Access checks */

	/* Is caller allowed to access files of this process? */
	if (taskpid_getprocpid(me->fn_fsdata) != task_getprocpid())
		fnode_access(self, R_OK);

	/* Check if file-access-permissions got less restrictive.
	 * -> If so, assert that the caller may open an underlying fnode.
	 * -> If there is no underlying fnode, we also permit the reopen,
	 *    since  this  appears to  be  some kind  of  special object. */
	access_mode = fnode_access_accmode[oflags & O_ACCMODE];
	if (access_mode & ~fnode_access_accmode[me->pfl_hand.h_mode & IO_ACCMODE]) {
		switch (me->pfl_hand.h_type) {

		case HANDLE_TYPE_MFILE: {
			struct mfile *obj;
			obj = (struct mfile *)me->pfl_hand.h_data;
			if (mfile_isnode(obj))
				fnode_access(mfile_asnode(obj), access_mode);
		}	break;

		case HANDLE_TYPE_PATH: {
			struct path *obj;
			obj = (struct path *)me->pfl_hand.h_data;
			fnode_access(obj->p_dir, access_mode);
		}	break;

		case HANDLE_TYPE_FILEHANDLE:
		case HANDLE_TYPE_TEMPHANDLE:
		case HANDLE_TYPE_FIFOHANDLE: {
			struct filehandle *obj;
			static_assert(offsetof(struct filehandle, fh_path) == offsetof(struct fifohandle, fu_path));
			static_assert(offsetof(struct filehandle, fh_dirent) == offsetof(struct fifohandle, fu_dirent));
			static_assert(offsetof(struct filehandle, fh_file) == offsetof(struct fifohandle, fu_fifo));
			obj = (struct filehandle *)me->pfl_hand.h_data;
			if (mfile_isnode(obj->fh_file))
				fnode_access(mfile_asnode(obj->fh_file), access_mode);
		}	break;

		case HANDLE_TYPE_DIRHANDLE: {
			struct dirhandle *hand;
			hand = (struct dirhandle *)me->pfl_hand.h_data;
			fnode_access(hand->dh_enum.de_dir, access_mode);
		}	break;

		default:
			break;
		}
	}

	/* Permit the open, and re-return an exact duplicate of the old object.
	 * NOTE: The caller will fill in `result->h_mode'. */
	result->h_data = me->pfl_hand.h_data;
	result->h_type = me->pfl_hand.h_type;
	(*handle_type_db.h_incref[result->h_type])(result->h_data);
	return true;
}

#ifndef __OPTIMIZE_SIZE__
PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) REF struct fnode *KCALL
procfs_fd_lnknode_v_expandlink(struct flnknode *__restrict self,
                               /*out[1..1]_opt*/ REF struct path **__restrict presult_path,
                               /*out[1..1]_opt*/ REF struct fdirent **__restrict presult_dirent,
                               /*in|out*/ u32 *__restrict UNUSED(premaining_symlinks))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct procfs_fd_lnknode *me;
	/* This is the function that implements the magic for open("/proc/[pid]/fd/[no]"),
	 * such  that  such a  call  behaves as  a  dup(2), rather  than open(readlink())! */
	me = (struct procfs_fd_lnknode *)mfile_aslnk(self);

	/* Certain handles  types  which  are  known  to
	 * reference path+name+file triples are checked. */
	switch (me->pfl_hand.h_type) {

	case HANDLE_TYPE_FILEHANDLE:
	case HANDLE_TYPE_TEMPHANDLE:
	case HANDLE_TYPE_FIFOHANDLE: {
		struct filehandle *hand;
		static_assert(offsetof(struct filehandle, fh_path) == offsetof(struct fifohandle, fu_path));
		static_assert(offsetof(struct filehandle, fh_dirent) == offsetof(struct fifohandle, fu_dirent));
		static_assert(offsetof(struct filehandle, fh_file) == offsetof(struct fifohandle, fu_fifo));
		hand = (struct filehandle *)me->pfl_hand.h_data;
		if (hand->fh_path && hand->fh_dirent && mfile_isnode(hand->fh_file)) {
			*presult_path   = incref(hand->fh_path);
			*presult_dirent = incref(hand->fh_dirent);
			return mfile_asnode(incref(hand->fh_file));
		}
	}	break;

	case HANDLE_TYPE_DIRHANDLE: {
		struct dirhandle *hand;
		hand = (struct dirhandle *)me->pfl_hand.h_data;
		if (hand->dh_path && hand->dh_dirent) {
			*presult_path   = incref(hand->dh_path);
			*presult_dirent = incref(hand->dh_dirent);
			return mfile_asdir(incref(hand->dh_enum.de_dir));
		}
	}	break;

	case HANDLE_TYPE_MFILE: {
		/* Device handles are known  to be relative to  the
		 * devfs root (so-long as they've not been deleted) */
		if (mfile_isdevice((struct mfile *)me->pfl_hand.h_data)) {
			struct device *dev;
			dev = mfile_asdevice((struct mfile *)me->pfl_hand.h_data);
			devfs_byname_read();
			if (dev->dv_byname_node.rb_lhs == DEVICE_BYNAME_DELETED) {
				devfs_byname_endread();
				break;
			}
			*presult_dirent = incref(&dev->dv_dirent->dd_dirent);
			devfs_byname_endread();
			/* The associated path is the mounting point for devfs in the current VFS */
			TRY {
				*presult_path = vfs_mount_location(THIS_VFS, &devfs.fs_root);
			} EXCEPT {
				decref_unlikely(*presult_dirent);
				RETHROW();
			}
			if unlikely(!*presult_path) {
				decref_unlikely(*presult_dirent);
				break;
			}
			return mfile_asnode(incref(dev));
		}
	}	break;

	case HANDLE_TYPE_PATH: {
		/* This case is somewhat special, in that we need to return information
		 * about the path's parent+name+dir to  construct a valid data  triple. */
		struct path *pth = (struct path *)me->pfl_hand.h_data;
		if (!path_isroot(pth)) {
			path_get_parent_and_name(pth, presult_path, presult_dirent);
			return mfile_asnode(incref(pth->p_dir));
		}
	}	break;

	default:
		break;
	}
	return NULL;
}

/* This operator is called when user-space does `open("/proc/[pid]/fd/[fdno]/foo/bar/foobar")',
 * in with case we're  to return the path  to-be used as basis  for the "foo/bar/foobar"  tail. */
PRIVATE WUNUSED NONNULL((1, 2)) REF struct path *KCALL
procfs_fd_lnknode_v_walklink(struct flnknode *__restrict self,
                             /*in|out*/ u32 *__restrict UNUSED(premaining_symlinks))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct procfs_fd_lnknode *me;
	me = (struct procfs_fd_lnknode *)mfile_aslnk(self);
	if (me->pfl_hand.h_type == HANDLE_TYPE_PATH)
		return incref((struct path *)me->pfl_hand.h_data);
	return NULL;
}
#endif /* !__OPTIMIZE_SIZE__ */


INTERN_CONST struct flnknode_ops const procfs_pp_fdlnk_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &procfs_fd_lnknode_v_destroy,
			.mo_changed = &procfs_fd_lnknode_v_changed,
			.mo_stream  = &procfs_fd_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_fd_lnknode_v_free,
		.no_wrattr = &procfs_fd_lnknode_v_wrattr,
		.no_perm   = &procfs_fd_lnknode_v_perm_ops,
	},
	.lno_readlink   = &procfs_fd_lnknode_v_readlink,
	.lno_openlink   = &procfs_fd_lnknode_v_openlink,
#ifndef __OPTIMIZE_SIZE__
	.lno_expandlink = &procfs_fd_lnknode_v_expandlink, /* Optimization operator! */
	.lno_walklink   = &procfs_fd_lnknode_v_walklink,   /* Optimization operator! */
#endif /* !__OPTIMIZE_SIZE__ */
};

/* Template for files from  "/proc/[PID]/fd/[NO]"
 * Has to be defined in "./perproc.c" because the
 * static init needs  `__WANT_FS_INIT', which  we
 * don't define. */
INTDEF struct flnknode const procfs_pp_fdlnk_template;


struct procfs_fd_dirent {
	REF struct taskpid *pfd_thread; /* [1..1][const] The thread being accessed. */
	REF struct handle   pfd_handle; /* [1..1][const] Handle. */
	struct fdirent      pfd_ent;    /* Underlying directory entry. */
};
#define fdirent_asfd(self) container_of(self, struct procfs_fd_dirent, pfd_ent)


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_fd_dirent_v_destroy)(struct fdirent *__restrict self) {
	struct procfs_fd_dirent *me = fdirent_asfd(self);
	handle_decref(me->pfd_handle);
	decref_unlikely(me->pfd_thread);
	kfree(me);
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_fd_dirent_v_opennode(struct fdirent *__restrict self,
                            struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_fd_dirent *me = fdirent_asfd(self);
	REF struct procfs_fd_lnknode *result;
	result = (REF struct procfs_fd_lnknode *)kmalloc(sizeof(REF struct procfs_fd_lnknode), GFP_NORMAL);
	result = (REF struct procfs_fd_lnknode *)memcpy(result, &procfs_pp_fdlnk_template, sizeof(struct flnknode));
	memcpy(&result->pfl_hand, &me->pfd_handle, sizeof(struct handle));
	result->fn_fsdata = incref(me->pfd_thread);
	result->fn_ino    = procfs_perproc_ino(me->pfd_handle.h_data, &procfs_pp_fdlnk_ops);
	handle_incref(result->pfl_hand);
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t
NOTHROW(FCALL procfs_fd_dirent_v_getino)(struct fdirent *__restrict self,
                                         struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_fd_dirent *me = fdirent_asfd(self);
	return procfs_perproc_ino(me->pfd_handle.h_data, &procfs_pp_fdlnk_ops);
}

PRIVATE struct fdirent_ops const procfs_fd_dirent_ops = {
	.fdo_destroy  = &procfs_fd_dirent_v_destroy,
	.fdo_opennode = &procfs_fd_dirent_v_opennode,
	.fdo_getino   = &procfs_fd_dirent_v_getino,
};



PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_fd_v_lookup(struct fdirnode *__restrict self,
                           struct flookup_info *__restrict info) {
	struct taskpid *pid = self->fn_fsdata;
	REF struct task *thread;
	REF struct handman *hm;
	char ch;

	thread = taskpid_gettask(pid);
	if (!thread)
		return NULL;
	hm = task_gethandman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(hm);

	/* Decode handle number */
	if unlikely(info->flu_namelen == 0)
		goto notanfd;
	ch = atomic_read(&info->flu_name[0]);
	if ((ch >= '1' && ch <= '9') || (ch == '0' && info->flu_namelen == 1)) {
		REF struct procfs_fd_dirent *result;
		unsigned int fdno = (unsigned int)(ch - '0');
		struct handle hand;
		size_t i;

		for (i = 1; i < info->flu_namelen; ++i) {
			ch = atomic_read(&info->flu_name[i]);
			if unlikely(!(ch >= '0' && ch <= '9'))
				goto notanfd;
			fdno *= 10;
			fdno += (unsigned int)(ch - '0');
		}

		/* Lookup the handle in question. */
		hand = handman_trylookup(hm, (fd_t)fdno);
		if (hand.h_type == HANDLE_TYPE_UNDEFINED)
			return NULL; /* No such handle */

		/* Allocate the new directory entry. */
		result = (REF struct procfs_fd_dirent *)kmalloc(offsetof(struct procfs_fd_dirent, pfd_ent.fd_name) +
		                                                (info->flu_namelen + 1) * sizeof(char),
		                                                GFP_NORMAL);

		/* Fill in the directory entry. */
		memcpy(&result->pfd_handle, &hand, sizeof(struct handle));  /* Inherit reference */
		result->pfd_thread         = incref(pid);
		result->pfd_ent.fd_namelen = (u16)sprintf(result->pfd_ent.fd_name, "%u", fdno);
		assert(result->pfd_ent.fd_namelen == info->flu_namelen);
		if (info->flu_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->flu_name))
			info->flu_hash = fdirent_hash(result->pfd_ent.fd_name, result->pfd_ent.fd_namelen);
		result->pfd_ent.fd_hash   = info->flu_hash;
		result->pfd_ent.fd_refcnt = 1; /* +1: return */
		result->pfd_ent.fd_ops    = &procfs_fd_dirent_ops;
//		result->pfd_ent.fd_ino    = procfs_perproc_ino(hand.h_data, &procfs_pp_fdlnk_ops); /* Not needed; we've got `fdo_getino()' */
		DBG_memset(&result->pfd_ent.fd_ino, 0xcc, sizeof(result->pfd_ent.fd_ino));
		result->pfd_ent.fd_type   = DT_LNK;
		return &result->pfd_ent;
	}
notanfd:
	return NULL;
}

struct procfs_fd_enum
#ifdef __cplusplus
    : fdirenum                    /* Underlying enumerator */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirenum     pfe_enum; /* Underlying enumerator */
#endif /* !__cplusplus */
	REF struct handman *pfe_hman; /* [1..1][const] Handle manager being enumerated. */
	unsigned int        pfe_fd;   /* Lower bound for next handle to enumerate. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_fd_enum_v_fini)(struct fdirenum *__restrict self) {
	struct procfs_fd_enum *me = (struct procfs_fd_enum *)self;
	decref_unlikely(me->pfe_hman);
}

PRIVATE NONNULL((1)) size_t KCALL
procfs_fd_enum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                         size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(...) {
	unsigned int index, newindex;
	ssize_t result;
	struct procfs_fd_enum *me;
	u16 namelen;
	void *hdata;
	char namebuf[lengthof(PRIMAXu)];
	me = (struct procfs_fd_enum *)self;

again:
	/* Read current index. */
	index = atomic_read(&me->pfe_fd);

	/* Find the next handle. */
	newindex = (unsigned int)handman_tryfindnext(me->pfe_hman, (fd_t)index, &hdata);
	if (newindex == (unsigned int)-1)
		return 0; /* End-of-directory */
	namelen = (u16)sprintf(namebuf, "%u", newindex);
	/* Feed directory entry. */
	result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
	                             procfs_perproc_ino(hdata, &procfs_pp_fdlnk_ops),
	                             DT_LNK, namelen, namebuf);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */
	/* Advance directory position. */
	if (!atomic_cmpxch(&me->pfe_fd, index, newindex + 1))
		goto again;
	return (size_t)result;
}

PRIVATE WUNUSED NONNULL((1)) unsigned int KCALL
find_greatest_inuse_fd_plus_one(struct handman *__restrict self) {
	unsigned int result;
	handman_read(self);
	result = handman_usefdend(self);
	handman_endread(self);
	return result;
}

PRIVATE NONNULL((1)) pos_t KCALL
procfs_fd_enum_v_seekdir(struct fdirenum *__restrict self,
                         off_t offset, unsigned int whence)
		THROWS(...) {
	unsigned int newpos;
	struct procfs_fd_enum *me = (struct procfs_fd_enum *)self;
	switch (whence) {
	case SEEK_SET:
#if __SIZEOF_POS_T__ > __SIZEOF_INT__
		if unlikely((pos_t)offset >= UINT_MAX)
			THROW(E_OVERFLOW);
#endif /* __SIZEOF_POS_T__ > __SIZEOF_INT__ */
		newpos = (unsigned int)(pos_t)offset;
		atomic_write(&me->pfe_fd, newpos);
		break;

	case SEEK_CUR: {
		uintptr_t oldpos;
		do {
			oldpos = atomic_read(&me->pfe_fd);
			newpos = oldpos + (int)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!atomic_cmpxch_weak(&me->pfe_fd, oldpos, newpos));
	}	break;

	case SEEK_END: {
		unsigned int dirsiz;
		dirsiz = find_greatest_inuse_fd_plus_one(me->pfe_hman);
		newpos = dirsiz + (int)offset;
		if unlikely(offset < 0 ? newpos > dirsiz
		                       : newpos < dirsiz)
			THROW(E_OVERFLOW);
		atomic_write(&me->pfe_fd, newpos);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	return (pos_t)newpos;
}

PRIVATE struct fdirenum_ops const procfs_fd_enum_ops = {
	.deo_fini    = &procfs_fd_enum_v_fini,
	.deo_readdir = &procfs_fd_enum_v_readdir,
	.deo_seekdir = &procfs_fd_enum_v_seekdir,
};

#define procfs_perproc_fd_v_enumsz sizeof(struct procfs_fd_enum)
PRIVATE NONNULL((1)) void KCALL
procfs_perproc_fd_v_enum(struct fdirenum *__restrict result) {
	REF struct task *thread;
	struct procfs_fd_enum *rt = (struct procfs_fd_enum *)result;
	struct taskpid *pid       = rt->de_dir->fn_fsdata;
	thread = taskpid_gettask(pid);
	if unlikely(!thread) {
		/* Thread has already terminated. -> Set-up an empty directory */
		rt->de_ops = &fdirenum_empty_ops;
	} else {
		rt->pfe_hman = task_gethandman(thread);
		decref_unlikely(thread);
		rt->de_ops = &procfs_fd_enum_ops;
		rt->pfe_fd = 0;
	}
}

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY

#ifndef __mfile_awref_defined
#define __mfile_awref_defined
AWREF(mfile_awref, mfile);
#endif /* !__mfile_awref_defined */

struct procfs_perproc_fd_notify_controller {
	WEAK refcnt_t         pfppfdnc_refcnt;             /* Reference counter. */
	struct mfile_awref    pfppfdnc_procfd_folder;      /* [0..1] File to which events should be posted. */
	struct sig_completion pfppfdnc_addhand_completion; /* Hook for `[handman]->hm_addhand' */
	struct sig_completion pfppfdnc_delhand_completion; /* Hook for `[handman]->hm_delhand' */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procfs_perproc_fd_notify_controller_destroy)(struct procfs_perproc_fd_notify_controller *__restrict self) {
	sig_completion_disconnect(&self->pfppfdnc_addhand_completion);
	sig_completion_disconnect(&self->pfppfdnc_delhand_completion);
	kfree(self);
}

DEFINE_REFCNT_FUNCTIONS(struct procfs_perproc_fd_notify_controller, pfppfdnc_refcnt,
                        procfs_perproc_fd_notify_controller_destroy);


/* Structure that is passed via the dynamic buffer to `procfs_perproc_fd_hand_postcompletion()' */
struct procfs_perproc_fd_event {
	REF struct mfile *pfppfde_file; /* [1..1] File to which to post events. */
	uint16_t          pfppfde_mask; /* The type of event (either IN_CREATE or IN_DELETE) */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procfs_perproc_fd_hand_postcompletion)(struct sig_completion_context *__restrict context,
                                                     void *buf) {
	struct procfs_perproc_fd_event *e;
	fd_t fd = HANDMAN_HANDSIG_DECODE(context->scc_sender);
	e = (struct procfs_perproc_fd_event *)buf;

	/* Post the filesystem event to the /fd directory. */
	_mfile_postfsfilevent_ex(e->pfppfde_file, e->pfppfde_mask, 0,
	                         NOTIFYFD_EVENT_NAME_DECIMAL(fd));
	decref_unlikely(e->pfppfde_file);
}


PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL procfs_perproc_fd_hand_completion)(struct sig_completion *__restrict self,
                                                 struct sig_completion_context *__restrict context,
                                                 struct procfs_perproc_fd_notify_controller *__restrict controller,
                                                 void *buf, size_t bufsize, uint16_t mask) {
	struct procfs_perproc_fd_event *e = (struct procfs_perproc_fd_event *)buf;
	if (bufsize < sizeof(struct procfs_perproc_fd_event))
		return sizeof(struct procfs_perproc_fd_event);

	/* Load the mfile of the `/proc/[pid]/fd' directory. */
	e->pfppfde_file = awref_get(&controller->pfppfdnc_procfd_folder);
	if unlikely(e->pfppfde_file == NULL)
		return 0; /* Special case: /fd directory was unloaded (stop monitoring) */
	e->pfppfde_mask = mask;
	context->scc_post = &procfs_perproc_fd_hand_postcompletion;

	/* Re-prime the signal completion handler so we keep monitoring *all* events. */
	sig_completion_reprime(self, true);
	return sizeof(struct procfs_perproc_fd_event);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL procfs_perproc_fd_addhand_completion)(struct sig_completion *__restrict self,
                                                    struct sig_completion_context *__restrict context,
                                                    void *buf, size_t bufsize) {
	return procfs_perproc_fd_hand_completion(self, context,
	                                         container_of(self, struct procfs_perproc_fd_notify_controller, pfppfdnc_addhand_completion),
	                                         buf, bufsize, IN_CREATE);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL procfs_perproc_fd_delhand_completion)(struct sig_completion *__restrict self,
                                                    struct sig_completion_context *__restrict context,
                                                    void *buf, size_t bufsize) {
	return procfs_perproc_fd_hand_completion(self, context,
	                                         container_of(self, struct procfs_perproc_fd_notify_controller, pfppfdnc_delhand_completion),
	                                         buf, bufsize, IN_DELETE);
}


PRIVATE BLOCKING NONNULL((1)) void *KCALL
procfs_perproc_fd_v_notify_attach(struct mfile *__restrict self)
		THROWS(E_BADALLOC, ...) {
	REF struct procfs_perproc_fd_notify_controller *result;
	struct taskpid *tpid;
	REF struct task *thread;
	REF struct handman *handman;
	assert(mfile_isnode(self));
	tpid    = mfile_asnode(self)->fn_fsdata;
	thread  = taskpid_gettask_srch(tpid);
	handman = task_gethandman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(handman);

	/* Allocate the notify controller. */
	result = (REF struct procfs_perproc_fd_notify_controller *)kmalloc(sizeof(struct procfs_perproc_fd_notify_controller),
	                                                                   GFP_NORMAL);

	/* Initialize the controller and connect it to the handle manager's add/del-hand signals. */
	result->pfppfdnc_refcnt = 1;
	awref_init(&result->pfppfdnc_procfd_folder, self);
	sig_completion_init(&result->pfppfdnc_addhand_completion, &procfs_perproc_fd_addhand_completion);
	sig_completion_init(&result->pfppfdnc_delhand_completion, &procfs_perproc_fd_delhand_completion);
	sig_connect_completion_for_poll(&handman->hm_addhand, &result->pfppfdnc_addhand_completion);
	sig_connect_completion_for_poll(&handman->hm_delhand, &result->pfppfdnc_delhand_completion);
	printk(KERN_INFO "[procfs] Notify object attached to '/proc/%d/fd' [cookie:%p]\n",
	       taskpid_getroottid(tpid), result);
	return result;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_perproc_fd_v_notify_detach)(struct mfile *__restrict self, void *cookie) {
	REF struct procfs_perproc_fd_notify_controller *controller;
	(void)self;
	assert(mfile_isnode(self));
	printk(KERN_INFO "[procfs] Notify object detached from '/proc/%d/fd' [cookie:%p]\n",
	       taskpid_getroottid(mfile_asnode(self)->fn_fsdata), cookie);
	controller = (struct procfs_perproc_fd_notify_controller *)cookie;
	awref_clear(&controller->pfppfdnc_procfd_folder);
	decref_likely(controller);
}

PRIVATE struct mfile_stream_ops const procfs_perproc_fd_v_stream_ops = {
	.mso_open          = &procfs_perproc_dir_v_open,
	.mso_stat          = &procfs_perproc_dir_v_stat,
	.mso_ioctl         = &procfs_perproc_dir_v_ioctl,
	.mso_notify_attach = &procfs_perproc_fd_v_notify_attach,
	.mso_notify_detach = &procfs_perproc_fd_v_notify_detach,
};
#else /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#define procfs_perproc_fd_v_stream_ops procfs_perproc_dir_v_stream_ops
#endif /* !CONFIG_HAVE_KERNEL_FS_NOTIFY */

INTERN_CONST struct fdirnode_ops const procfs_pp_fd = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_fd_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
		.no_perm   = &procfs_perproc_dir_v_perm_ops,
	},
	.dno_lookup = &procfs_perproc_fd_v_lookup,
	.dno_enumsz = procfs_perproc_fd_v_enumsz,
	.dno_enum   = &procfs_perproc_fd_v_enum,
};



/************************************************************************/
/* /proc/[pid]/fdinfo                                                   */
/************************************************************************/

struct procfs_fdinfo_regnode: printnode {
	struct handle pfir_hand; /* [const] Relevant handle. */
};

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_pp_fdinfo_v_destroy)(struct mfile *__restrict self) {
	struct procfs_fdinfo_regnode *me;
	me = (struct procfs_fdinfo_regnode *)mfile_asreg(self);
	assert(!LIST_ISBOUND(me, fn_allnodes));
	assert(me->fn_supent.rb_rhs == FSUPER_NODES_DELETED);
	assert(me->mf_parts == MFILE_PARTS_ANONYMOUS);
	(*handle_type_db.h_decref[me->pfir_hand.h_type])(me->pfir_hand.h_data);
	decref_unlikely(me->fn_fsdata);
	kfree(me);
}

/* Return the effective file-position of `ptr' */
PRIVATE BLOCKING NONNULL((2)) pos_t KCALL
handle_get_fpos(uintptr_half_t typ, void *__restrict ptr)
		THROWS(...) {
	pos_t fpos;
	switch (typ) {

	case HANDLE_TYPE_FILEHANDLE:
	case HANDLE_TYPE_TEMPHANDLE: {
		struct filehandle *hand;
		hand = (struct filehandle *)ptr;
		fpos = (pos_t)atomic64_read(&hand->fh_offset);
	}	break;

	case HANDLE_TYPE_DIRHANDLE: {
		struct dirhandle *hand;
		hand = (struct dirhandle *)ptr;
		TRY {
			fpos = fdirenum_seekdir(&hand->dh_enum, 0, SEEK_CUR);
		} EXCEPT {
			if (!was_thrown(E_INVALID_ARGUMENT_UNKNOWN_COMMAND))
				RETHROW();
			fpos = 0;
		}
	}	break;

	default:
		fpos = 0;
		break;
	}
	return fpos;
}

PRIVATE BLOCKING NONNULL((1, 2)) void KCALL
procfs_pp_fdinfo_v_print(struct printnode *__restrict self,
                         pformatprinter printer, void *arg,
                         pos_t UNUSED(offset_hint))
		THROWS(...) {
	pos_t fpos;
	struct procfs_fdinfo_regnode *me;
	me = (struct procfs_fdinfo_regnode *)self;

	/* Figure out the handle's file position. */
	fpos = handle_get_fpos(me->pfir_hand.h_type, me->pfir_hand.h_data);

	/* Print basic file information. */
	if (printf("pos:\t%" PRIuN(__SIZEOF_POS_T__) "\n"
	           "flags:\t%" PRIoN(__SIZEOF_OFLAG_T__) "\n"
	           "mnt_id:\t0\n", /* TODO: Related to (currently missing) "/proc/[pid]/mountinfo" */
	           (pos_t)fpos,
	           (oflag_t)IO_TO_OPENFLAG(me->pfir_hand.h_mode)) < 0)
		return;

	/* Some handles have type-specific fields. */
	switch (me->pfir_hand.h_type) {

	case HANDLE_TYPE_EVENTFD_FENCE:
	case HANDLE_TYPE_EVENTFD_SEMA: {
		struct eventfd *hand;
		uint64_t tickets;
		hand    = (struct eventfd *)me->pfir_hand.h_data;
		tickets = atomic64_read(&hand->ef_value);
		if (printf("eventfd-count:\t%" PRIu64 "\n", tickets) < 0)
			return;
	}	break;

	case HANDLE_TYPE_EPOLL: {
		size_t i;
		struct epoll_controller *hand;
		hand = (struct epoll_controller *)me->pfir_hand.h_data;
		__COMPILER_WORKAROUND_GCC_105689(&hand->ec_lock);
		for (i = 0;;) {
			struct epoll_handle_monitor *mon;
			uint32_t mon_fdkey;
			uint32_t mon_events;
			union epoll_data mon_data;
			uintptr_half_t mon_hand_typ;
			REF void *mon_hand_ptr;
			REF struct mfile *mon_hand_mf;
			pos_t mon_hand_fpos;
#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
			bool mon_isrpc;
#endif /* CONFIG_HAVE_KERNEL_EPOLL_RPC */
			epoll_controller_lock_acquire(hand);
epoll_nextmon_locked:
			if (i > hand->ec_mask) {
				epoll_controller_lock_release(hand);
				break;
			}
			mon = hand->ec_list[i].ece_mon;
			++i;
			if (mon == NULL || mon->ehm_handtyp == HANDLE_TYPE_UNDEFINED)
				goto epoll_nextmon_locked;
			mon_fdkey    = mon->ehm_fdkey;
			mon_events   = mon->ehm_events;
			mon_data     = mon->ehm_data;
			mon_hand_typ = mon->ehm_handtyp;
			mon_hand_ptr = mon->ehm_handptr;
			(*handle_type_db.h_incref[mon_hand_typ])(mon_hand_ptr);
#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
			mon_isrpc = epoll_handle_monitor_isrpc(mon);
#endif /* CONFIG_HAVE_KERNEL_EPOLL_RPC */
			epoll_controller_lock_release(hand);
			RAII_FINALLY { (*handle_type_db.h_decref[mon_hand_typ])(mon_hand_ptr); };
			printf("tfd: %8" PRIu32 " events: %8" PRIx32 " ", mon_fdkey, mon_events);
#ifdef CONFIG_HAVE_KERNEL_EPOLL_RPC
			/* For RPC monitors, this would be `mon_data' becomes `ehm_rpc',
			 * which is a pointers to internal kernel data that must not  be
			 * exposed! */
			if (mon_isrpc) {
				PRINT("rpc: 1 ");
			} else
#endif /* CONFIG_HAVE_KERNEL_EPOLL_RPC */
			{
				printf("data: %16" PRIx64 " ", mon_data.u64);
			}
			mon_hand_fpos = handle_get_fpos(mon_hand_typ, mon_hand_ptr);
			printf("pos:%" PRIuN(__SIZEOF_POS_T__), (pos_t)mon_hand_fpos);
			if (mon_hand_typ == HANDLE_TYPE_MFILE) {
				mon_hand_mf = incref((REF struct mfile *)mon_hand_ptr);
			} else {
				mon_hand_mf = (REF struct mfile *)(*handle_type_db.h_tryas[mon_hand_typ])(mon_hand_ptr, HANDLE_TYPE_MFILE);
			}
			/* Linux includes all of the below fields unconditionally since it assigns
			 * inode numbers and device files to everything, even if doing so wouldn't
			 * make sense.
			 * Because KOS likes to make sense (for  the most part ;), it only  assigns
			 * inode  numbers and devices  for objects that are  actually apart of some
			 * filesystem. As  such, file  descriptors don't  automatically have  inode
			 * and device numbers, so we only print them here for handles that actually
			 * do. */
			if (mon_hand_mf) {
				FINALLY_DECREF_UNLIKELY(mon_hand_mf);
				if (mfile_isnode(mon_hand_mf)) {
					ino_t ino;
					struct fnode *fn = mfile_asnode(mon_hand_mf);
					struct mfile *dev;
					mfile_tslock_acquire(fn);
					ino = fn->fn_ino;
					mfile_tslock_release(fn);
					printf(" ino:%" PRIxN(__SIZEOF_INO_T__), ino);
					dev = fn->fn_super->fs_dev;
					if (dev && mfile_isdevice(dev)) {
						dev_t devno = mfile_asdevice(dev)->dn_devno;
						printf(" sdev:%" PRIxN(__SIZEOF_DEV_T__), devno);
					}
				}
			}
			if (PRINT("\n") < 0)
				return;
		}
	}	break;

	case HANDLE_TYPE_SIGNALFD: {
		struct signalfd *hand;
		hand = (struct signalfd *)me->pfir_hand.h_data;
		PRINT("sigmask:\t");
		print_sigset(printer, arg, &hand->sf_mask);
		PRINT("\n");
	}	break;

	case HANDLE_TYPE_PIDFD: {
		struct pidns *myns = THIS_PIDNS;
		struct taskpid *hand;
		pid_t tpid;
		hand = (struct taskpid *)me->pfir_hand.h_data;
		tpid = -1;
		if likely(myns->pn_ind <= hand->tp_ns->pn_ind)
			tpid = (pid_t)_taskpid_slot_getpidno(hand->tp_pids[myns->pn_ind]);
		if (printf("Pid:\t%" PRIdN(__SIZEOF_PID_T__) "\n", tpid) < 0)
			return;
		if likely(myns->pn_ind >= hand->tp_ns->pn_ind) {
			size_t i;
			PRINT("NSpid:");
			for (i = myns->pn_ind; i <= hand->tp_ns->pn_ind; ++i) {
				if (printf("\t%" PRIdN(__SIZEOF_PID_T__), hand->tp_pids[i]) < 0)
					return;
			}
			PRINT("\n");
		}
	}	break;

	default:
		break;
	}
}


#define procfs_pp_fdinfo_v_loadblocks procfs_perproc_printnode_v_loadblocks
#define procfs_pp_fdinfo_v_changed    procfs_perproc_printnode_v_changed
#define procfs_pp_fdinfo_v_wrattr     procfs_perproc_printnode_v_wrattr
#define procfs_pp_fdinfo_v_perm_ops   procfs_perproc_printnode_v_perm_ops
#define procfs_pp_fdinfo_v_free       procfs_perproc_printnode_v_free
#define procfs_pp_fdinfo_v_stream_ops procfs_perproc_printnode_v_stream_ops

INTERN_CONST struct printnode_ops const procfs_pp_fdinfo_ops = {
	.pno_reg = {{
		.no_file = {
			.mo_destroy    = &procfs_pp_fdinfo_v_destroy,
			.mo_loadblocks = &procfs_pp_fdinfo_v_loadblocks,
			.mo_changed    = &procfs_pp_fdinfo_v_changed,
			.mo_stream     = &procfs_pp_fdinfo_v_stream_ops,
		},
		.no_free   = &procfs_pp_fdinfo_v_free,
		.no_wrattr = &procfs_pp_fdinfo_v_wrattr,
		.no_perm   = &procfs_pp_fdinfo_v_perm_ops,
	}},
	.pno_print = &procfs_pp_fdinfo_v_print,
};

/* Template for files from  "/proc/[PID]/fdinfo/[NO]" */
INTDEF struct printnode const procfs_pp_fdinfo_template;

struct procfs_fdinfo_dirent {
	REF struct taskpid *pfd_thread;  /* [1..1][const] The thread being accessed. */
	struct handle       pfd_hand;    /* [const] Associated handle. */
	struct fdirent      pfd_ent;     /* Underlying directory entry. */
};
#define fdirent_asfdinfo(self) container_of(self, struct procfs_fdinfo_dirent, pfd_ent)


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_fdinfo_dirent_v_destroy)(struct fdirent *__restrict self) {
	struct procfs_fdinfo_dirent *me = fdirent_asfdinfo(self);
	(*handle_type_db.h_decref[me->pfd_hand.h_type])(me->pfd_hand.h_data);
	decref_unlikely(me->pfd_thread);
	kfree(me);
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_fdinfo_dirent_v_opennode(struct fdirent *__restrict self,
                                struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_fdinfo_dirent *me = fdirent_asfdinfo(self);
	REF struct procfs_fdinfo_regnode *result;
	result = (REF struct procfs_fdinfo_regnode *)kmalloc(sizeof(REF struct procfs_fdinfo_regnode), GFP_NORMAL);
	result = (REF struct procfs_fdinfo_regnode *)memcpy(result, &procfs_pp_fdinfo_template, sizeof(struct printnode));
	result->pfir_hand = me->pfd_hand;
	result->fn_fsdata = incref(me->pfd_thread);
	result->fn_ino    = procfs_perproc_ino(me->pfd_hand.h_data, &procfs_pp_fdinfo_ops);
	(*handle_type_db.h_incref[me->pfd_hand.h_type])(me->pfd_hand.h_data);
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t
NOTHROW(FCALL procfs_fdinfo_dirent_v_getino)(struct fdirent *__restrict self,
                                             struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_fdinfo_dirent *me = fdirent_asfdinfo(self);
	return procfs_perproc_ino(me->pfd_hand.h_data, &procfs_pp_fdinfo_ops);
}

PRIVATE struct fdirent_ops const procfs_fdinfo_dirent_ops = {
	.fdo_destroy  = &procfs_fdinfo_dirent_v_destroy,
	.fdo_opennode = &procfs_fdinfo_dirent_v_opennode,
	.fdo_getino   = &procfs_fdinfo_dirent_v_getino,
};



PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_fdinfo_v_lookup(struct fdirnode *__restrict self,
                               struct flookup_info *__restrict info) {
	struct taskpid *pid = self->fn_fsdata;
	REF struct task *thread;
	REF struct handman *hm;
	char ch;

	thread = taskpid_gettask(pid);
	if (!thread)
		return NULL;
	hm = task_gethandman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(hm);

	/* Decode handle number */
	if unlikely(info->flu_namelen == 0)
		goto notanfd;
	ch = atomic_read(&info->flu_name[0]);
	if ((ch >= '1' && ch <= '9') || (ch == '0' && info->flu_namelen == 1)) {
		REF struct procfs_fdinfo_dirent *result;
		unsigned int fdno = (unsigned int)(ch - '0');
		struct handle hand;
		size_t i;

		for (i = 1; i < info->flu_namelen; ++i) {
			ch = atomic_read(&info->flu_name[i]);
			if unlikely(!(ch >= '0' && ch <= '9'))
				goto notanfd;
			fdno *= 10;
			fdno += (unsigned int)(ch - '0');
		}

		/* Lookup the handle in question. */
		hand = handman_trylookup(hm, (fd_t)fdno);
		if (hand.h_type == HANDLE_TYPE_UNDEFINED)
			return NULL; /* No such handle */

		/* Allocate the new directory entry. */
		result = (REF struct procfs_fdinfo_dirent *)kmalloc(offsetof(struct procfs_fdinfo_dirent, pfd_ent.fd_name) +
		                                                    (info->flu_namelen + 1) * sizeof(char),
		                                                    GFP_NORMAL);

		/* Fill in the directory entry. */
		result->pfd_hand           = hand; /* Inherit reference */
		result->pfd_thread         = incref(pid);
		result->pfd_ent.fd_namelen = (u16)sprintf(result->pfd_ent.fd_name, "%u", fdno);
		assert(result->pfd_ent.fd_namelen == info->flu_namelen);
		if (info->flu_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->flu_name))
			info->flu_hash = fdirent_hash(result->pfd_ent.fd_name, result->pfd_ent.fd_namelen);
		result->pfd_ent.fd_hash   = info->flu_hash;
		result->pfd_ent.fd_refcnt = 1; /* +1: return */
		result->pfd_ent.fd_ops    = &procfs_fdinfo_dirent_ops;
//		result->pfd_ent.fd_ino    = procfs_perproc_ino(hand.h_data, &procfs_pp_fdinfo_ops); /* Not needed; we've got `fdo_getino()' */
		DBG_memset(&result->pfd_ent.fd_ino, 0xcc, sizeof(result->pfd_ent.fd_ino));
		result->pfd_ent.fd_type   = DT_REG;
		return &result->pfd_ent;
	}
notanfd:
	return NULL;
}


#define procfs_fdinfo_enum_v_fini procfs_fd_enum_v_fini
PRIVATE NONNULL((1)) size_t KCALL
procfs_fdinfo_enum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                             size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(...) {
	unsigned int index, newindex;
	ssize_t result;
	struct procfs_fd_enum *me;
	u16 namelen;
	void *hdata;
	char namebuf[lengthof(PRIMAXu)];
	me = (struct procfs_fd_enum *)self;

again:
	/* Read current index. */
	index = atomic_read(&me->pfe_fd);

	/* Find the next handle. */
	newindex = (unsigned int)handman_tryfindnext(me->pfe_hman, (fd_t)index, &hdata);
	if (newindex == (unsigned int)-1)
		return 0; /* End-of-directory */
	namelen = (u16)sprintf(namebuf, "%u", newindex);
	/* Feed directory entry. */
	result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
	                             procfs_perproc_ino(hdata, &procfs_pp_fdinfo_ops),
	                             DT_REG, namelen, namebuf);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */
	/* Advance directory position. */
	if (!atomic_cmpxch(&me->pfe_fd, index, newindex + 1))
		goto again;
	return (size_t)result;
}

#define procfs_fdinfo_enum_v_seekdir procfs_fd_enum_v_seekdir

PRIVATE struct fdirenum_ops const procfs_fdinfo_enum_ops = {
	.deo_fini    = &procfs_fdinfo_enum_v_fini,
	.deo_readdir = &procfs_fdinfo_enum_v_readdir,
	.deo_seekdir = &procfs_fdinfo_enum_v_seekdir,
};

#define procfs_perproc_fdinfo_v_enumsz procfs_perproc_fd_v_enumsz
PRIVATE NONNULL((1)) void KCALL
procfs_perproc_fdinfo_v_enum(struct fdirenum *__restrict result) {
	REF struct task *thread;
	struct procfs_fd_enum *rt = (struct procfs_fd_enum *)result;
	struct taskpid *pid       = rt->de_dir->fn_fsdata;
	thread = taskpid_gettask(pid);
	if unlikely(!thread) {
		/* Thread has already terminated. -> Set-up an empty directory */
		rt->de_ops = &fdirenum_empty_ops;
	} else {
		rt->pfe_hman = task_gethandman(thread);
		decref_unlikely(thread);
		rt->de_ops = &procfs_fdinfo_enum_ops;
		rt->pfe_fd = 0;
	}
}

/* Files in `/fdinfo' and `/fd' share names, so filesystem notifications for `/fd' also apply
 * to `/fdinfo'. As  such, we  can simply  re-use stream  operators for  `/fd' in  `/fdinfo'. */
#define procfs_perproc_fdinfo_v_stream_ops procfs_perproc_fd_v_stream_ops

INTERN_CONST struct fdirnode_ops const procfs_pp_fdinfo = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_fdinfo_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
		.no_perm   = &procfs_perproc_dir_v_perm_ops,
	},
	.dno_lookup = &procfs_perproc_fdinfo_v_lookup,
	.dno_enumsz = procfs_perproc_fdinfo_v_enumsz,
	.dno_enum   = &procfs_perproc_fdinfo_v_enum,
};



/************************************************************************/
/* /proc/[pid]/map_files                                                */
/************************************************************************/
struct perproc_mapfile_lnknode: flnknode {
	REF struct fnode   *ppml_file;   /* [1..1] Mapped file */
	REF struct path    *ppml_fspath; /* [1..1] Mapped filesystem path */
	REF struct fdirent *ppml_fsname; /* [1..1] Mapped filesystem name */
};

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL perproc_mapfile_lnknode_v_destroy)(struct mfile *__restrict self) {
	struct perproc_mapfile_lnknode *me;
	me = (struct perproc_mapfile_lnknode *)mfile_aslnk(self);
	assert(!LIST_ISBOUND(me, fn_allnodes));
	assert(me->fn_supent.rb_rhs == FSUPER_NODES_DELETED);
	assert(me->mf_parts == MFILE_PARTS_ANONYMOUS);
	/*mmapinfo_fini(&me->ppmd_info);*/
	decref_unlikely(me->ppml_file);
	decref_unlikely(me->ppml_fspath);
	decref_unlikely(me->ppml_fsname);
	decref_unlikely(me->fn_fsdata);
	kfree(me);
}


PRIVATE WUNUSED NONNULL((1)) size_t KCALL
perproc_mapfile_lnknode_v_readlink(struct flnknode *__restrict self,
                                   NCX /*utf-8*/ char *buf,
                                   size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	struct perproc_mapfile_lnknode *me;
	REF struct path *fsroot = fs_getroot(THIS_FS);
	me = (struct perproc_mapfile_lnknode *)mfile_aslnk(self);
	FINALLY_DECREF_UNLIKELY(fsroot);
	return path_sprintent_without_nul(me->ppml_fspath,
	                                  me->ppml_fsname->fd_name,
	                                  me->ppml_fsname->fd_namelen,
	                                  buf, bufsize, AT_PATHPRINT_INCTRAIL,
	                                  fsroot);
}

#ifndef __OPTIMIZE_SIZE__
PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) REF struct fnode *KCALL
perproc_mapfile_lnknode_v_expandlink(struct flnknode *__restrict self,
                                     /*out[1..1]_opt*/ REF struct path **__restrict presult_path,
                                     /*out[1..1]_opt*/ REF struct fdirent **__restrict presult_dirent,
                                     /*in|out*/ u32 *__restrict UNUSED(premaining_symlinks))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct perproc_mapfile_lnknode *me;
	me = (struct perproc_mapfile_lnknode *)mfile_aslnk(self);
	*presult_path   = incref(me->ppml_fspath);
	*presult_dirent = incref(me->ppml_fsname);
	return mfile_asnode(incref(me->ppml_file));
}
#endif /* !__OPTIMIZE_SIZE__ */

#define perproc_mapfile_lnknode_v_changed    procfs_perproc_lnknode_v_changed
#define perproc_mapfile_lnknode_v_wrattr     procfs_perproc_lnknode_v_wrattr
#define perproc_mapfile_lnknode_v_perm_ops   procfs_perproc_lnknode_v_perm_ops
#define perproc_mapfile_lnknode_v_free       procfs_perproc_lnknode_v_free
#define perproc_mapfile_lnknode_v_stream_ops procfs_perproc_lnknode_v_stream_ops

INTDEF struct flnknode const perproc_mapfile_lnknode_template;
INTERN_CONST struct flnknode_ops const perproc_mapfile_lnknode_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &perproc_mapfile_lnknode_v_destroy,
			.mo_changed = &perproc_mapfile_lnknode_v_changed,
			.mo_stream  = &perproc_mapfile_lnknode_v_stream_ops,
		},
		.no_free   = &perproc_mapfile_lnknode_v_free,
		.no_wrattr = &perproc_mapfile_lnknode_v_wrattr,
		.no_perm   = &perproc_mapfile_lnknode_v_perm_ops,
	},
	.lno_readlink   = &perproc_mapfile_lnknode_v_readlink,
#ifndef __OPTIMIZE_SIZE__
	.lno_expandlink = &perproc_mapfile_lnknode_v_expandlink, /* Optimization operator! */
#endif /* !__OPTIMIZE_SIZE__ */
};

struct perproc_mapfile_dirent {
	REF struct fnode   *ppmd_file;   /* [1..1][const] Mapped file */
	REF struct path    *ppmd_fspath; /* [1..1][const] Mapped filesystem path */
	REF struct fdirent *ppmd_fsname; /* [1..1][const] Mapped filesystem name */
	REF struct taskpid *ppmd_thread; /* [1..1][const] Thread in question */
	struct fdirent      ppmd_ent;    /* Underlying directory entry. */
};
#define fdirent_asmapfile(self) container_of(self, struct perproc_mapfile_dirent, ppmd_ent)

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL perproc_mapfile_dirent_v_destroy)(struct fdirent *__restrict self) {
	struct perproc_mapfile_dirent *me = fdirent_asmapfile(self);
	decref_unlikely(me->ppmd_file);
	decref_unlikely(me->ppmd_fspath);
	decref_unlikely(me->ppmd_fsname);
	decref_unlikely(me->ppmd_thread);
	kfree(me);
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
perproc_mapfile_dirent_v_opennode(struct fdirent *__restrict self,
                                  struct fdirnode *__restrict UNUSED(dir)) {
	struct perproc_mapfile_dirent *me = fdirent_asmapfile(self);
	REF struct perproc_mapfile_lnknode *result;
	result = (REF struct perproc_mapfile_lnknode *)kmalloc(sizeof(REF struct perproc_mapfile_lnknode), GFP_NORMAL);
	result = (REF struct perproc_mapfile_lnknode *)memcpy(result, &perproc_mapfile_lnknode_template, sizeof(struct flnknode));
	result->ppml_file   = mfile_asnode(incref(me->ppmd_file));
	result->ppml_fspath = incref(me->ppmd_fspath);
	result->ppml_fsname = incref(me->ppmd_fsname);
	result->fn_fsdata   = incref(me->ppmd_thread);
	result->fn_ino      = me->ppmd_ent.fd_ino;
	return result;
}

PRIVATE struct fdirent_ops const perproc_mapfile_dirent_ops = {
	.fdo_destroy  = &perproc_mapfile_dirent_v_destroy,
	.fdo_opennode = &perproc_mapfile_dirent_v_opennode,
};

/* GCC complains that `minaddr' may be used uninitialized, but it isn't because it's only
 * used when `state == STATE_END', which can only happen if it goes through `STATE_END0',
 * which it only does on a control-path that initializes `minaddr'! */
__pragma_GCC_diagnostic_push_ignored(Wmaybe_uninitialized)

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_map_files_v_lookup(struct fdirnode *__restrict self,
                                  struct flookup_info *__restrict info) {
	REF struct perproc_mapfile_dirent *result;
	struct mmapinfo mminfo;
	uintptr_t minaddr, endaddr;
	NCX char const *reader, *end;
	unsigned int state;
#define STATE_MIN0 0
#define STATE_MIN  1
#define STATE_END0 2
#define STATE_END  3

	/* Decode address string */
	reader  = info->flu_name;
	end     = info->flu_name + info->flu_namelen;
	endaddr = 0;
	state   = STATE_MIN0;
	while (reader < end) {
		char ch;
		ch = atomic_read(reader);
		++reader;
		if (ch >= '0' && ch <= '9') {
			if (ch == '0' && (state == STATE_MIN0 || state == STATE_END0))
				return NULL;
			ch -= '0';
		} else if (ch >= 'a' && ch <= 'f') {
			ch += 10 - 'a';
		} else if ((ch >= 'A' && ch <= 'F') && (info->flu_flags & AT_DOSPATH)) {
			ch += 10 - 'A';
		} else if (ch == '-' && state == STATE_MIN) {
			minaddr = endaddr;
			state   = STATE_END0;
			endaddr = 0;
			continue;
		} else {
			return NULL;
		}
		if unlikely(((endaddr << 4) >> 4) != endaddr)
			return NULL;
		endaddr <<= 4;
		endaddr += (unsigned char)ch;
		state |= 1; /* STATE_MIN0 -> STATE_MIN, STATE_END0 -> STATE_END */
	}
	if unlikely(state != STATE_END)
		return NULL;

	/* Lookup address information. */
	{
		REF struct task *thread;
		REF struct mman *mm;
		thread = taskpid_gettask(self->fn_fsdata);
		if unlikely(!thread)
			return NULL;
		mm = task_getmman(thread);
		decref_unlikely(thread);
		FINALLY_DECREF_UNLIKELY(mm);
		if unlikely(!mman_mapinfo(mm, &mminfo, (NCX UNCHECKED void *)minaddr))
			return NULL;
	}

	/* Verify min/max bounds of mapping info */
	if unlikely(mminfo.mmi_min != (UNCHECKED void *)minaddr)
		goto err_mminfo;
	if unlikely(mminfo.mmi_max != (UNCHECKED void *)(endaddr - 1))
		goto err_mminfo;

	/* Verify that this mapping really should appear in /proc/[PID]/map_files */
	if unlikely(!mminfo.mmi_file)
		goto err_mminfo;
	if unlikely(!mminfo.mmi_fsname)
		goto err_mminfo;
	if unlikely(!mminfo.mmi_fspath)
		goto err_mminfo;
	if unlikely(!mfile_isnode(mminfo.mmi_file))
		goto err_mminfo;

	/* Construct the new directory entry. */
	TRY {
		result = (REF struct perproc_mapfile_dirent *)kmalloc(offsetof(struct perproc_mapfile_dirent,
		                                                               ppmd_ent.fd_name) +
		                                                      (info->flu_namelen + 1) * sizeof(char),
		                                                      GFP_NORMAL);
	} EXCEPT {
		mmapinfo_fini(&mminfo);
		RETHROW();
	}
	sprintf(result->ppmd_ent.fd_name, "%" PRIxPTR "-%" PRIxPTR, minaddr, endaddr);
	result->ppmd_file           = mfile_asnode(mminfo.mmi_file); /* Inherit reference */
	result->ppmd_fspath         = mminfo.mmi_fspath;             /* Inherit reference */
	result->ppmd_fsname         = mminfo.mmi_fsname;             /* Inherit reference */
	result->ppmd_thread         = incref(self->fn_fsdata);
	result->ppmd_ent.fd_refcnt  = 1;
	result->ppmd_ent.fd_ops     = &perproc_mapfile_dirent_ops;
	result->ppmd_ent.fd_ino     = procfs_perproc_ino(mminfo._mmi_node, &perproc_mapfile_lnknode_ops);
	result->ppmd_ent.fd_namelen = info->flu_namelen;
	result->ppmd_ent.fd_type    = DT_LNK;
	result->ppmd_ent.fd_hash    = fdirent_hash(result->ppmd_ent.fd_name, info->flu_namelen);
	return &result->ppmd_ent;
err_mminfo:
	mmapinfo_fini(&mminfo);
	return NULL;

#undef STATE_MIN0
#undef STATE_MIN
#undef STATE_END0
#undef STATE_END
}

__pragma_GCC_diagnostic_pop_ignored(Wmaybe_uninitialized)

struct perproc_mapfile_direnum
#ifdef __cplusplus
    : fdirenum                  /* Underlying enumerator */
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct fdirenum  ppmd_enum; /* Underlying enumerator */
#endif /* !__cplusplus */
	REF struct mman *ppmd_mm;   /* [1..1][const] The mman being enumerated. */
	UNCHECKED void  *ppmd_addr; /* [lock(ATOMIC)] Lower bound for mappings still needing enumeration. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL perproc_mapfile_direnum_v_fini)(struct fdirenum *__restrict self) {
	struct perproc_mapfile_direnum *me = (struct perproc_mapfile_direnum *)self;
	decref_unlikely(me->ppmd_mm);
}

PRIVATE BLOCKING NONNULL((1)) size_t KCALL
perproc_mapfile_direnum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                                  size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	ssize_t result;
	bool should_enum;
	struct mmapinfo mminfo;
	char rangename[lengthof(PRIMAXxPTR "-" PRIMAXxPTR)];
	u16 namelen;
	struct perproc_mapfile_direnum *me = (struct perproc_mapfile_direnum *)self;
	UNCHECKED void *oldaddr, *newaddr;

again:
	oldaddr = atomic_read(&me->ppmd_addr);
	if unlikely(oldaddr == (UNCHECKED void *)(uintptr_t)-1)
		return 0; /* Forced end-of-directory. */
	newaddr = oldaddr;

again_lookup:
	/* Lookup mapping information. */
	if (!mman_mapinfo_above(me->ppmd_mm, &mminfo, newaddr))
		return 0;

	/* Check if this range should be enumerated. */
	should_enum = mminfo.mmi_file && mminfo.mmi_fsname &&
	              mminfo.mmi_fspath && mfile_isnode(mminfo.mmi_file);
	mmapinfo_fini(&mminfo);
	if (OVERFLOW_UADD((uintptr_t)mminfo.mmi_max, 1, (uintptr_t *)&newaddr)) {
		if (!should_enum)
			return 0;
		newaddr = (UNCHECKED void *)(uintptr_t)-1;
	} else {
		if (!should_enum)
			goto again_lookup;
	}

	/* Yield info on this range. */
	namelen = (u16)sprintf(rangename, "%" PRIxPTR "-%" PRIxPTR,
	                       mminfo.mmi_min, newaddr);
	result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
	                             procfs_perproc_ino(mminfo._mmi_node, &perproc_mapfile_lnknode_ops),
	                             DT_LNK, namelen, rangename);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */

	/* Advance directory position. */
	if (!atomic_cmpxch(&me->ppmd_addr, oldaddr, newaddr))
		goto again;
	return (size_t)result;
}


PRIVATE NONNULL((1)) pos_t KCALL
perproc_mapfile_direnum_v_seekdir(struct fdirenum *__restrict self,
                                  off_t offset, unsigned int whence)
		THROWS(...) {
	UNCHECKED void *newpos;
	struct perproc_mapfile_direnum *me = (struct perproc_mapfile_direnum *)self;
	switch (whence) {
	case SEEK_SET:
#if __SIZEOF_POS_T__ > __SIZEOF_POINTER__
		if unlikely((pos_t)offset >= (uintptr_t)-1)
			THROW(E_OVERFLOW);
#endif /* __SIZEOF_POS_T__ > __SIZEOF_POINTER__ */
		newpos = (UNCHECKED void *)(uintptr_t)(pos_t)offset;
		atomic_write(&me->ppmd_addr, newpos);
		break;

	case SEEK_CUR: {
		UNCHECKED void *oldpos;
		do {
			oldpos = atomic_read(&me->ppmd_addr);
			newpos = (UNCHECKED byte_t *)oldpos + (intptr_t)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!atomic_cmpxch_weak(&me->ppmd_addr, oldpos, newpos));
	}	break;

	case SEEK_END: {
		if unlikely(offset >= 0)
			THROW(E_OVERFLOW);
#if __SIZEOF_POS_T__ > __SIZEOF_POINTER__
		offset = (-offset) - 1;
		if (OVERFLOW_USUB((uintptr_t)-1, offset, (uintptr_t *)&newpos))
			THROW(E_OVERFLOW);
#else /* __SIZEOF_POS_T__ > __SIZEOF_POINTER__ */
		newpos = (UNCHECKED void *)((uintptr_t)0 - offset);
#endif /* __SIZEOF_POS_T__ <= __SIZEOF_POINTER__ */
		atomic_write(&me->ppmd_addr, newpos);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	return (pos_t)(uintptr_t)newpos;
}

PRIVATE struct fdirenum_ops const perproc_mapfile_direnum_ops = {
	.deo_fini    = &perproc_mapfile_direnum_v_fini,
	.deo_readdir = &perproc_mapfile_direnum_v_readdir,
	.deo_seekdir = &perproc_mapfile_direnum_v_seekdir,
};


#define procfs_perproc_map_files_v_enumsz sizeof(struct perproc_mapfile_direnum)
PRIVATE NONNULL((1)) void KCALL
procfs_perproc_map_files_v_enum(struct fdirenum *__restrict result) {
	struct perproc_mapfile_direnum *rt;
	REF struct task *thread;
	rt = (struct perproc_mapfile_direnum *)result;
	thread = taskpid_gettask(result->de_dir->fn_fsdata);
	if unlikely(!thread) {
		/* Thread exited. -> Enumerate an empty directory. */
		rt->de_ops = &fdirenum_empty_ops;
		return;
	}
	rt->ppmd_mm = task_getmman(thread);
	decref_unlikely(thread);
	rt->de_ops    = &perproc_mapfile_direnum_ops;
	rt->ppmd_addr = (UNCHECKED void *)0;
}

INTERN_CONST struct fdirnode_ops const procfs_pp_map_files = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_dir_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
		.no_perm   = &procfs_perproc_dir_v_perm_ops,
	},
	.dno_lookup = &procfs_perproc_map_files_v_lookup,
	.dno_enumsz = procfs_perproc_map_files_v_enumsz,
	.dno_enum   = &procfs_perproc_map_files_v_enum,
};



/************************************************************************/
/* /proc/[pid]/task                                                     */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_task_v_lookup(struct fdirnode *__restrict self,
                             struct flookup_info *__restrict info) {
	/* NOTE: The directory entry created here is very similar to procfs_perproc_root_dirent_ops,
	 *       except that instead of moving on to open the normal `procfs_perproc_root_files', it
	 *       opens a custom version that doesn't include the "task" sub-folder. */
	struct taskpid *master_pid = self->fn_fsdata;
	char ch;

	/* Evaluate running process PIDs */
	if unlikely(info->flu_namelen == 0)
		goto notapid;
	ch = atomic_read(&info->flu_name[0]);
	if (ch >= '1' && ch <= '9') {
		REF struct taskpid *pid;
		pid_t pidno = ch - '0';
		size_t i;
		for (i = 1; i < info->flu_namelen; ++i) {
			ch = atomic_read(&info->flu_name[i]);
			if unlikely(!(ch >= '0' && ch <= '9'))
				goto notapid;
			pidno *= 10;
			pidno += ch - '0';
		}
		pid = pidns_lookup(THIS_PIDNS, pidno);
		if likely(pid) {
			REF struct procfs_perproc_root_dirent *result;
			if (pid != master_pid) {
				/* Check that this is actually a child thread of `master_pid' */
				if (taskpid_getprocpid(pid) != master_pid) {
					decref_unlikely(pid);
					return NULL;
				}
			}

			/* Allocate the directory entry. */
			TRY {
				result = (REF struct procfs_perproc_root_dirent *)kmalloc(offsetof(struct procfs_perproc_root_dirent,
				                                                                   pprd_ent.fd_name) +
				                                                          (info->flu_namelen + 1) * sizeof(char),
				                                                          GFP_NORMAL);
			} EXCEPT {
				decref_unlikely(pid);
				RETHROW();
			}

			/* Fill in the directory entry. */
			result->pprd_pid            = pid; /* Inherit reference */
			result->pprd_ent.fd_namelen = (u16)sprintf(result->pprd_ent.fd_name, "%" PRIuN(__SIZEOF_PID_T__), pidno);
			assert(result->pprd_ent.fd_namelen == info->flu_namelen);
			if (info->flu_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->flu_name))
				info->flu_hash = fdirent_hash(result->pprd_ent.fd_name, result->pprd_ent.fd_namelen);
			result->pprd_ent.fd_hash   = info->flu_hash;
			result->pprd_ent.fd_refcnt = 1; /* +1: return */
			result->pprd_ent.fd_ops    = &procfs_pertask_root_dirent_ops;
//			result->pprd_ent.fd_ino    = procfs_perproc_ino(pid, &procfs_pertask_root_ops); /* Not needed; we've got `fdo_getino()' */
			DBG_memset(&result->pprd_ent.fd_ino, 0xcc, sizeof(result->pprd_ent.fd_ino));
			result->pprd_ent.fd_type   = DT_DIR;
			return &result->pprd_ent;
		}
	}
notapid:
	return NULL;
}

struct procfs_task_direnum: fdirenum {
	upid_t          ptd_index; /* [lock(ATOMIC)] Lowest pid of next thread to enumerate. */
	struct taskpid *ptd_pid;   /* [const][== de_dir->fn_fsdata] PID of the process leader. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_task_direnum_v_fini)(struct fdirenum *__restrict UNUSED(self)) {
	/* No-op */
	COMPILER_IMPURE();
}

PRIVATE NOBLOCK WUNUSED NONNULL((1)) REF struct taskpid *
NOTHROW(KCALL find_first_thread_greater_or_equal)(struct taskpid *__restrict master,
                                                  upid_t pid, size_t myind) {
	struct procctl *ctl = master->tp_pctl;
	struct taskpid *iter;
	REF struct taskpid *result;
	upid_t result_pid;
	result     = NULL;
	result_pid = (upid_t)-1;
	procctl_thrds_acquire(ctl);
	FOREACH_procctl_thrds(iter, ctl) {
		upid_t iter_pid;
		if unlikely(iter->tp_ns->pn_ind < myind)
			continue; /* Cannot be represented */
		iter_pid = _taskpid_slot_getpidno(iter->tp_pids[myind]);
		if (iter_pid < pid)
			continue; /* Not part of range which interests us. */
		if (result_pid < iter_pid)
			continue; /* Current `result' is better. */
		if (!tryincref(iter))
			continue; /* Dead... */
		xdecref_unlikely(result);
		result     = iter;
		result_pid = iter_pid;
	}
	procctl_thrds_release(ctl);
	return result;
}

PRIVATE NOBLOCK WUNUSED NONNULL((1)) upid_t
NOTHROW(KCALL get_greatest_child_pid_plus_one)(struct taskpid *__restrict master) {
	struct procctl *ctl = master->tp_pctl;
	struct taskpid *iter;
	upid_t result;
	size_t myind;
	myind  = THIS_PIDNS->pn_ind;
	result = 0;
	procctl_thrds_acquire(ctl);
	FOREACH_procctl_thrds(iter, ctl) {
		upid_t iter_pid;
		if unlikely(iter->tp_ns->pn_ind < myind)
			continue; /* Cannot be represented */
		iter_pid = _taskpid_slot_getpidno(iter->tp_pids[myind]) + 1;
		if (result < iter_pid)
			result = iter_pid;
	}
	procctl_thrds_release(ctl);
	return result;
}


PRIVATE BLOCKING NONNULL((1)) size_t KCALL
procfs_task_direnum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                              size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	REF struct taskpid *pid;
	upid_t pid_id;
	u16 namelen;
	size_t myind = THIS_PIDNS->pn_ind;
	upid_t index, newindex;
	ssize_t result;
	struct procfs_task_direnum *me;
	me = (struct procfs_task_direnum *)self;

again:
	/* Read current index. */
	index = atomic_read(&me->ptd_index);

	/* Lookup next taskpid entry. */
	if (index == 0) {
		/* Special behavior for PID=0: The original process itself (but as a thread) */
		pid = me->ptd_pid;
		if likely(pid->tp_ns->pn_ind >= myind) {
			incref(pid);
			pid_id   = _taskpid_slot_getpidno(pid->tp_pids[myind]);
			newindex = 1; /* Start enumeration threads the next time around */
			goto gotpid;
		}
	}
	pid = find_first_thread_greater_or_equal(me->ptd_pid, index, myind);
	if (!pid)
		return 0; /* End-of-directory */
	pid_id   = _taskpid_slot_getpidno(pid->tp_pids[myind]);
	newindex = pid_id + 1; /* Next time around, yield a process with a greater PID */
	{
		char namebuf[lengthof(PRIMAXuN(__SIZEOF_PID_T__))];
gotpid:
		FINALLY_DECREF_UNLIKELY(pid);
		namelen = (u16)sprintf(namebuf, "%" PRIuN(__SIZEOF_PID_T__), pid_id);

		/* Feed directory entry. */
		result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
		                             procfs_perproc_ino(pid, &procfs_pertask_root_ops),
		                             DT_DIR, namelen, namebuf);
	}
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */

	/* Advance directory position. */
	if (!atomic_cmpxch(&me->ptd_index, index, newindex))
		goto again;
	return (size_t)result;
}

PRIVATE BLOCKING NONNULL((1)) pos_t KCALL
procfs_task_direnum_v_seekdir(struct fdirenum *__restrict self,
                              off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_IOERROR, ...) {
	uintptr_t newpos;
	struct procfs_task_direnum *me = (struct procfs_task_direnum *)self;
	switch (whence) {

	case SEEK_SET:
#if __SIZEOF_POS_T__ > __SIZEOF_PID_T__
		if unlikely((pos_t)offset > (pos_t)(upid_t)-1)
			THROW(E_OVERFLOW);
#endif /* __SIZEOF_POS_T__ > __SIZEOF_PID_T__ */
		newpos = (upid_t)(pos_t)offset;
		atomic_write(&me->ptd_index, newpos);
		break;

	case SEEK_CUR: {
		uintptr_t oldpos;
		do {
			oldpos = atomic_read(&me->ptd_index);
			newpos = oldpos + (intptr_t)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!atomic_cmpxch_weak(&me->ptd_index, oldpos, newpos));
	}	break;

	case SEEK_END: {
		upid_t dirsiz = 0;
		/* The end of the directory is relative to the largest in-use PID */
		dirsiz = get_greatest_child_pid_plus_one(me->ptd_pid);
		newpos = dirsiz + (pid_t)offset;
		if unlikely(offset < 0 ? newpos > dirsiz
		                       : newpos < dirsiz)
			THROW(E_OVERFLOW);
		atomic_write(&me->ptd_index, newpos);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	return (pos_t)newpos;
}


PRIVATE struct fdirenum_ops const procfs_task_direnum_ops = {
	.deo_fini    = &procfs_task_direnum_v_fini,
	.deo_readdir = &procfs_task_direnum_v_readdir,
	.deo_seekdir = &procfs_task_direnum_v_seekdir,
};

#define procfs_perproc_task_v_enumsz sizeof(struct procfs_task_direnum)
PRIVATE NONNULL((1)) void KCALL
procfs_perproc_task_v_enum(struct fdirenum *__restrict result) {
	struct procfs_task_direnum *rt;
	struct taskpid *pid;
	rt  = (struct procfs_task_direnum *)result;
	pid = rt->de_dir->fn_fsdata;

	/* Fill in fields. */
	rt->de_ops    = &procfs_task_direnum_ops;
	rt->ptd_index = 0;
	rt->ptd_pid   = pid;
}

#ifdef CONFIG_HAVE_KERNEL_FS_NOTIFY

#ifndef __mfile_awref_defined
#define __mfile_awref_defined
AWREF(mfile_awref, mfile);
#endif /* !__mfile_awref_defined */

struct procfs_perproc_task_notify_controller {
	WEAK refcnt_t         pfpptnc_refcnt;             /* Reference counter. */
	struct taskpid       *pfpptnc_proc;               /* [1..1][const] Process main() thread (filter for thread events). (not a reference because we never need to deref it) */
	struct mfile_awref    pfpptnc_task_folder;        /* [0..1] File to which events should be posted. */
	struct sig_completion pfpptnc_addproc_completion; /* Hook for `pidns_root.pn_addproc' */
	struct sig_completion pfpptnc_delproc_completion; /* Hook for `pidns_root.pn_delproc' */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procfs_perproc_task_notify_controller_destroy)(struct procfs_perproc_task_notify_controller *__restrict self) {
	sig_completion_disconnect(&self->pfpptnc_addproc_completion);
	sig_completion_disconnect(&self->pfpptnc_delproc_completion);
	kfree(self);
}

DEFINE_REFCNT_FUNCTIONS(struct procfs_perproc_task_notify_controller, pfpptnc_refcnt,
                        procfs_perproc_task_notify_controller_destroy);


/* Structure that is passed via the dynamic buffer to `procfs_perproc_task_hand_postcompletion()' */
struct procfs_perproc_task_event {
	REF struct mfile *pfppfde_file; /* [1..1] File to which to post events. */
	uint16_t          pfppfde_mask; /* The type of event (either IN_CREATE or IN_DELETE) */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(FCALL procfs_perproc_task_hand_postcompletion)(struct sig_completion_context *__restrict context,
                                                       void *buf) {
	struct taskpid *tpid;
	struct procfs_perproc_task_event *e;
	notifyfd_event_name_t name;
	e = (struct procfs_perproc_task_event *)buf;

	/* FIXME: Don't unconditionally use the root namespace PID (the  PID
	 * used should differ for each inotify receiver, and be based on the
	 * receiver's  canonical PID namespace. Additionally, omit the event
	 * if the receiver isn't supposed to see the process) */
	tpid = PIDNS_PROCSIG_DECODE(context->scc_sender);
	name = NOTIFYFD_EVENT_NAME_DECIMAL(taskpid_getroottid(tpid));

	/* Post the filesystem event to the /task directory. */
	_mfile_postfsfilevent_ex(e->pfppfde_file, e->pfppfde_mask | IN_ISDIR, 0, name);
	decref_unlikely(e->pfppfde_file);
}


PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2, 3)) size_t
NOTHROW(FCALL procfs_perproc_task_hand_completion)(struct sig_completion *__restrict self,
                                                   struct sig_completion_context *__restrict context,
                                                   struct procfs_perproc_task_notify_controller *__restrict controller,
                                                   void *buf, size_t bufsize, uint16_t mask) {
	struct taskpid *tpid = PIDNS_PROCSIG_DECODE(context->scc_sender);
	struct procfs_perproc_task_event *e = (struct procfs_perproc_task_event *)buf;
	if (taskpid_getprocpid(tpid) != controller->pfpptnc_proc) {
		sig_completion_reprime(self, true);
		return 0; /* Thread belongs to some other process (but not ours) */
	}
	if (bufsize < sizeof(struct procfs_perproc_task_event))
		return sizeof(struct procfs_perproc_task_event);

	/* Load the mfile of the `/proc/[pid]/task' directory. */
	e->pfppfde_file = awref_get(&controller->pfpptnc_task_folder);
	if unlikely(e->pfppfde_file == NULL)
		return 0; /* Special case: /task directory was unloaded (stop monitoring) */
	e->pfppfde_mask = mask;
	context->scc_post = &procfs_perproc_task_hand_postcompletion;

	/* Re-prime the signal completion handler so we keep monitoring *all* events. */
	sig_completion_reprime(self, true);
	return sizeof(struct procfs_perproc_task_event);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL procfs_perproc_task_addhand_completion)(struct sig_completion *__restrict self,
                                                      struct sig_completion_context *__restrict context,
                                                      void *buf, size_t bufsize) {
	return procfs_perproc_task_hand_completion(self, context,
	                                           container_of(self, struct procfs_perproc_task_notify_controller, pfpptnc_addproc_completion),
	                                           buf, bufsize, IN_CREATE);
}

PRIVATE NOBLOCK NOPREEMPT NONNULL((1, 2)) size_t
NOTHROW(FCALL procfs_perproc_task_delhand_completion)(struct sig_completion *__restrict self,
                                                      struct sig_completion_context *__restrict context,
                                                      void *buf, size_t bufsize) {
	return procfs_perproc_task_hand_completion(self, context,
	                                           container_of(self, struct procfs_perproc_task_notify_controller, pfpptnc_delproc_completion),
	                                           buf, bufsize, IN_DELETE);
}


PRIVATE BLOCKING NONNULL((1)) void *KCALL
procfs_perproc_task_v_notify_attach(struct mfile *__restrict self)
		THROWS(E_BADALLOC, ...) {
	REF struct procfs_perproc_task_notify_controller *result;
	struct taskpid *tpid;
	assert(mfile_isnode(self));
	tpid = mfile_asnode(self)->fn_fsdata;

	/* Allocate the notify controller. */
	result = (REF struct procfs_perproc_task_notify_controller *)kmalloc(sizeof(struct procfs_perproc_task_notify_controller),
	                                                                     GFP_NORMAL);

	/* Initialize the controller and connect it to the handle manager's add/del-hand signals. */
	result->pfpptnc_refcnt = 1;
	result->pfpptnc_proc   = taskpid_getprocpid(tpid);
	awref_init(&result->pfpptnc_task_folder, self);
	sig_completion_init(&result->pfpptnc_addproc_completion, &procfs_perproc_task_addhand_completion);
	sig_completion_init(&result->pfpptnc_delproc_completion, &procfs_perproc_task_delhand_completion);
	sig_connect_completion_for_poll(&pidns_root.pn_addproc, &result->pfpptnc_addproc_completion);
	sig_connect_completion_for_poll(&pidns_root.pn_delproc, &result->pfpptnc_delproc_completion);
	printk(KERN_INFO "[procfs] Notify object attached to '/proc/%d/task' [cookie:%p]\n",
	       taskpid_getroottid(tpid), result);
	return result;
}

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_perproc_task_v_notify_detach)(struct mfile *__restrict self, void *cookie) {
	REF struct procfs_perproc_task_notify_controller *controller;
	(void)self;
	assert(mfile_isnode(self));
	printk(KERN_INFO "[procfs] Notify object detached from '/proc/%d/task' [cookie:%p]\n",
	       taskpid_getroottid(mfile_asnode(self)->fn_fsdata), cookie);
	controller = (struct procfs_perproc_task_notify_controller *)cookie;
	awref_clear(&controller->pfpptnc_task_folder);
	decref_likely(controller);
}

PRIVATE struct mfile_stream_ops const procfs_perproc_task_v_stream_ops = {
	.mso_open          = &procfs_perproc_dir_v_open,
	.mso_stat          = &procfs_perproc_dir_v_stat,
	.mso_ioctl         = &procfs_perproc_dir_v_ioctl,
	.mso_notify_attach = &procfs_perproc_task_v_notify_attach,
	.mso_notify_detach = &procfs_perproc_task_v_notify_detach,
};
#else /* CONFIG_HAVE_KERNEL_FS_NOTIFY */
#define procfs_perproc_task_v_stream_ops procfs_perproc_dir_v_stream_ops
#endif /* !CONFIG_HAVE_KERNEL_FS_NOTIFY */

INTERN_CONST struct fdirnode_ops const procfs_pp_task = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_task_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
		.no_perm   = &procfs_perproc_dir_v_perm_ops,
	},
	.dno_lookup = &procfs_perproc_task_v_lookup,
	.dno_enumsz = procfs_perproc_task_v_enumsz,
	.dno_enum   = &procfs_perproc_task_v_enum,
};



/************************************************************************/
/* /proc/[pid]/kos/dcwd + /proc/[pid]/kos/drives                        */
/************************************************************************/
INTDEF struct flnknode const procfs_perproc_dcwdlink_template;
INTDEF struct flnknode const procfs_perproc_drivelink_template;
struct procfs_perproc_drivelnk: flnknode {
	uint8_t ppdl_driveno; /* [const] Driver number (in `[0,VFS_DRIVECOUNT)') */
};

PRIVATE WUNUSED NONNULL((1)) REF struct path *FCALL
procfs_perproc_drivelnk_getcwd(struct procfs_perproc_drivelnk *__restrict self)
		THROWS(E_WOULDBLOCK) {
	REF struct path *drivepath;
	REF struct fs *threadfs;
	REF struct task *thread;
	thread = taskpid_gettask(self->fn_fsdata);
	if unlikely(!thread)
		return NULL;
	threadfs = task_getfs(thread);
	decref_unlikely(thread);
	{
		struct vfs *threadvfs;
		FINALLY_DECREF_UNLIKELY(threadfs);
		fs_pathlock_read(threadfs);
		drivepath = threadfs->fs_dcwd[self->ppdl_driveno];
		if (drivepath) {
			incref(drivepath);
			fs_pathlock_endread(threadfs);
			return drivepath;
		}
		fs_pathlock_endread(threadfs);
		threadvfs = threadfs->fs_vfs;
		vfs_driveslock_read(threadvfs);
		drivepath = xincref(threadvfs->vf_drives[self->ppdl_driveno]);
		vfs_driveslock_endread(threadvfs);
	}
	return drivepath;
}

PRIVATE WUNUSED NONNULL((1)) REF struct path *FCALL
procfs_perproc_drivelnk_getroot(struct procfs_perproc_drivelnk *__restrict self)
		THROWS(E_WOULDBLOCK) {
	REF struct path *drivepath;
	REF struct fs *threadfs;
	REF struct task *thread;
	thread = taskpid_gettask(self->fn_fsdata);
	if unlikely(!thread)
		return NULL;
	threadfs = task_getfs(thread);
	decref_unlikely(thread);
	{
		struct vfs *threadvfs = threadfs->fs_vfs;
		FINALLY_DECREF_UNLIKELY(threadfs);
		vfs_driveslock_read(threadvfs);
		drivepath = xincref(threadvfs->vf_drives[self->ppdl_driveno]);
		vfs_driveslock_endread(threadvfs);
	}
	return drivepath;
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
procfs_perproc_dcwdlink_v_readlink(struct flnknode *__restrict self,
                                   NCX /*utf-8*/ char *buf,
                                   size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	struct procfs_perproc_drivelnk *me;
	REF struct path *caller_root;
	REF struct path *drivepath;
	me        = (struct procfs_perproc_drivelnk *)self;
	drivepath = procfs_perproc_drivelnk_getcwd(me);
	if unlikely(!drivepath)
		return snprintf(buf, bufsize, "/");
	FINALLY_DECREF_UNLIKELY(drivepath);
	caller_root = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(caller_root);
	return path_sprint_without_nul(drivepath, buf, bufsize, 0, caller_root);
}

PRIVATE BLOCKING WUNUSED NONNULL((1)) size_t KCALL
procfs_perproc_drivelink_v_readlink(struct flnknode *__restrict self,
                                    NCX /*utf-8*/ char *buf,
                                    size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	struct procfs_perproc_drivelnk *me;
	REF struct path *caller_root;
	REF struct path *drivepath;
	me        = (struct procfs_perproc_drivelnk *)self;
	drivepath = procfs_perproc_drivelnk_getroot(me);
	if unlikely(!drivepath)
		return snprintf(buf, bufsize, "/");
	FINALLY_DECREF_UNLIKELY(drivepath);
	caller_root = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(caller_root);
	return path_sprint_without_nul(drivepath, buf, bufsize, 0, caller_root);
}

#ifndef __OPTIMIZE_SIZE__
PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct path *KCALL
procfs_perproc_dcwdlink_v_walklink(struct flnknode *__restrict self,
                                   /*in|out*/ u32 *__restrict UNUSED(premaining_symlinks))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct procfs_perproc_drivelnk *me;
	me = (struct procfs_perproc_drivelnk *)self;
	return procfs_perproc_drivelnk_getcwd(me);
}

PRIVATE BLOCKING WUNUSED NONNULL((1, 2)) REF struct path *KCALL
procfs_perproc_drivelink_v_walklink(struct flnknode *__restrict self,
                                    /*in|out*/ u32 *__restrict UNUSED(premaining_symlinks))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct procfs_perproc_drivelnk *me;
	me = (struct procfs_perproc_drivelnk *)self;
	return procfs_perproc_drivelnk_getroot(me);
}
#endif /* !__OPTIMIZE_SIZE__ */


INTERN_CONST struct flnknode_ops const procfs_perproc_dcwdlink_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_lnknode_v_destroy,
			.mo_changed = &procfs_perproc_lnknode_v_changed,
			.mo_stream  = &procfs_perproc_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_perproc_lnknode_v_free,
		.no_wrattr = &procfs_perproc_lnknode_v_wrattr,
		.no_perm   = &procfs_perproc_lnknode_v_perm_ops,
	},
	.lno_readlink = &procfs_perproc_dcwdlink_v_readlink,
#ifndef __OPTIMIZE_SIZE__
	.lno_walklink = &procfs_perproc_dcwdlink_v_walklink, /* Optimization operator! */
#endif /* !__OPTIMIZE_SIZE__ */
};

INTERN_CONST struct flnknode_ops const procfs_perproc_drivelink_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_lnknode_v_destroy,
			.mo_changed = &procfs_perproc_lnknode_v_changed,
			.mo_stream  = &procfs_perproc_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_perproc_lnknode_v_free,
		.no_wrattr = &procfs_perproc_lnknode_v_wrattr,
		.no_perm   = &procfs_perproc_lnknode_v_perm_ops,
	},
	.lno_readlink = &procfs_perproc_drivelink_v_readlink,
#ifndef __OPTIMIZE_SIZE__
	.lno_walklink = &procfs_perproc_drivelink_v_walklink, /* Optimization operator! */
#endif /* !__OPTIMIZE_SIZE__ */
};

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_perproc_dcwd_v_opennode(struct fdirent *__restrict self,
                               struct fdirnode *__restrict dir) {
	REF struct procfs_perproc_drivelnk *result;
	result = (REF struct procfs_perproc_drivelnk *)kmalloc(sizeof(struct procfs_perproc_drivelnk), GFP_NORMAL);
	result = (REF struct procfs_perproc_drivelnk *)memcpy(result, &procfs_perproc_dcwdlink_template, sizeof(struct flnknode));

	/* Fill in fields. */
	result->mf_ops       = &procfs_perproc_dcwdlink_ops.lno_node.no_file;
	result->fn_fsdata    = incref(dir->fn_fsdata);
	result->fn_ino       = procfs_perproc_ino((uintptr_t)result->fn_fsdata ^ (uintptr_t)self, &procfs_perproc_dcwdlink_ops);
	result->ppdl_driveno = (uint8_t)self->fd_ino;
	return result;
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_perproc_drives_v_opennode(struct fdirent *__restrict self,
                                 struct fdirnode *__restrict dir) {
	REF struct procfs_perproc_drivelnk *result;
	result = (REF struct procfs_perproc_drivelnk *)kmalloc(sizeof(struct procfs_perproc_drivelnk), GFP_NORMAL);
	result = (REF struct procfs_perproc_drivelnk *)memcpy(result, &procfs_perproc_drivelink_template, sizeof(struct flnknode));

	/* Fill in fields. */
	result->mf_ops       = &procfs_perproc_drivelink_ops.lno_node.no_file;
	result->fn_fsdata    = incref(dir->fn_fsdata);
	result->fn_ino       = procfs_perproc_ino((uintptr_t)result->fn_fsdata ^ (uintptr_t)self, &procfs_perproc_drivelink_ops);
	result->ppdl_driveno = (uint8_t)self->fd_ino;
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t FCALL
procfs_perproc_dcwd_v_getino(struct fdirent *__restrict self,
                             struct fdirnode *__restrict dir) {
	return procfs_perproc_ino((uintptr_t)dir->fn_fsdata ^ (uintptr_t)self,
	                          &procfs_perproc_dcwdlink_ops);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t FCALL
procfs_perproc_drives_v_getino(struct fdirent *__restrict self,
                               struct fdirnode *__restrict dir) {
	return procfs_perproc_ino((uintptr_t)dir->fn_fsdata ^ (uintptr_t)self,
	                          &procfs_perproc_drivelink_ops);
}

PRIVATE struct fdirent_ops const procfs_perproc_dcwd_dirent_ops = {
	.fdo_destroy  = (typeof_field(struct fdirent_ops, fdo_destroy))(void *)-1,
	.fdo_opennode = &procfs_perproc_dcwd_v_opennode,
	.fdo_getino   = &procfs_perproc_dcwd_v_getino,
};

PRIVATE struct fdirent_ops const procfs_perproc_drives_dirent_ops = {
	.fdo_destroy  = (typeof_field(struct fdirent_ops, fdo_destroy))(void *)-1,
	.fdo_opennode = &procfs_perproc_drives_v_opennode,
	.fdo_getino   = &procfs_perproc_drives_v_getino,
};

#ifndef VFS_DRIVECOUNT
#define VFS_DRIVECOUNT 26
#endif /* !VFS_DRIVECOUNT */

/*[[[deemon
#undef print
import * from deemon;
import * from ....misc.libgen.fdirent_hash;
print("/" "* FOREACH_DRIVE(cb(LETTER, letterChr, hash)) *" "/");
print("#define FOREACH_DRIVE(cb) \\");
for (local x: [:VFS_DRIVECOUNT]) {
	local letter = string.chr("A".ord() + x);
	print("\tcb(", letter, ", '", letter, "', ", fdirent_hash(letter), ")"),;
	if (x != (VFS_DRIVECOUNT - 1))
		print("      \\"),;
	print;
}
]]]*/
/* FOREACH_DRIVE(cb(LETTER, letterChr, hash)) */
#define FOREACH_DRIVE(cb) \
	cb(A, 'A', 0x41)      \
	cb(B, 'B', 0x42)      \
	cb(C, 'C', 0x43)      \
	cb(D, 'D', 0x44)      \
	cb(E, 'E', 0x45)      \
	cb(F, 'F', 0x46)      \
	cb(G, 'G', 0x47)      \
	cb(H, 'H', 0x48)      \
	cb(I, 'I', 0x49)      \
	cb(J, 'J', 0x4a)      \
	cb(K, 'K', 0x4b)      \
	cb(L, 'L', 0x4c)      \
	cb(M, 'M', 0x4d)      \
	cb(N, 'N', 0x4e)      \
	cb(O, 'O', 0x4f)      \
	cb(P, 'P', 0x50)      \
	cb(Q, 'Q', 0x51)      \
	cb(R, 'R', 0x52)      \
	cb(S, 'S', 0x53)      \
	cb(T, 'T', 0x54)      \
	cb(U, 'U', 0x55)      \
	cb(V, 'V', 0x56)      \
	cb(W, 'W', 0x57)      \
	cb(X, 'X', 0x58)      \
	cb(Y, 'Y', 0x59)      \
	cb(Z, 'Z', 0x5a)
/*[[[end]]]*/

struct procfs_drive_fdirent {
	_FDIRENT_FIELDS_WITHOUT_NAME
	char fd_name[2];
};

#define procfs_drive_fdirent_asdirent(self) ((struct fdirent *)(self))


PRIVATE struct procfs_drive_fdirent procfs_perproc_dirent_dcwd[VFS_DRIVECOUNT] = {
#define DEFINE_DCWD_DIRENT(name, letter, hash)         \
	{                                                  \
		.fd_refcnt  = 1,                               \
		.fd_ops     = &procfs_perproc_dcwd_dirent_ops, \
		.fd_ino     = (ino_t)(letter - 'A'),           \
		.fd_hash    = hash,                            \
		.fd_namelen = 1,                               \
		.fd_type    = DT_LNK,                          \
		/* .fd_name = */ { letter, 0 }                 \
	},
	FOREACH_DRIVE(DEFINE_DCWD_DIRENT)
#undef DEFINE_DCWD_DIRENT
};

PRIVATE struct procfs_drive_fdirent procfs_perproc_dirent_drives[VFS_DRIVECOUNT] = {
#define DEFINE_DRIVE_DIRENT(name, letter, hash)          \
	{                                                    \
		.fd_refcnt  = 1,                                 \
		.fd_ops     = &procfs_perproc_drives_dirent_ops, \
		.fd_ino     = (ino_t)(letter - 'A'),             \
		.fd_hash    = hash,                              \
		.fd_namelen = 1,                                 \
		.fd_type    = DT_LNK,                            \
		/* .fd_name = */ { letter, 0 }                   \
	},
	FOREACH_DRIVE(DEFINE_DRIVE_DIRENT)
#undef DEFINE_DRIVE_DIRENT
};


/* Returns the drive ID referenced by `info' or `0xff' if
 * `info' isn't a drive name or the drive doesn't  exist. */
PRIVATE WUNUSED NONNULL((1)) uint8_t KCALL
get_driveid(struct fdirnode *__restrict self,
            struct flookup_info const *__restrict info) {
	REF struct task *thread;
	REF struct fs *threadfs;
	bool exists;
	uint8_t id;
	if (info->flu_namelen != 1)
		return 0xff;
	id = (uint8_t)atomic_read(&info->flu_name[0]);
	if (id >= 'A' && id <= 'Z') {
		id -= 'A';
	} else if (id >= 'a' && id <= 'z' && (info->flu_flags & AT_DOSPATH)) {
		id -= 'a';
	} else {
		return 0xff;
	}
	thread = taskpid_gettask(self->fn_fsdata);
	if unlikely(!thread)
		return 0xff;
	threadfs = task_getfs(thread);
	decref_unlikely(thread);
	exists = atomic_read(&threadfs->fs_vfs->vf_drives[id]) != NULL;
	decref_unlikely(threadfs);
	if unlikely(!exists)
		return 0xff;
	return id;
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_kos_dcwd_v_lookup(struct fdirnode *__restrict self,
                                 struct flookup_info *__restrict info) {
	uint8_t id = get_driveid(self, info);
	if unlikely(id == 0xff)
		return NULL;
	return incref(procfs_drive_fdirent_asdirent(&procfs_perproc_dirent_dcwd[id]));
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_kos_drives_v_lookup(struct fdirnode *__restrict self,
                                   struct flookup_info *__restrict info) {
	uint8_t id = get_driveid(self, info);
	if unlikely(id == 0xff)
		return NULL;
	return incref(procfs_drive_fdirent_asdirent(&procfs_perproc_dirent_drives[id]));
}

struct procfs_perproc_drives_enum: fdirenum {
	REF struct vfs *ppde_vfs;     /* [1..1][const] VFS who's drives are being enumerated. */
	uint8_t         ppde_driveno; /* [lock(ATOMIC)] Next drive id to enumerate is >= this. */
};

#define procfs_perproc_dcwd_enum_v_fini procfs_perproc_drives_enum_v_fini
PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_perproc_drives_enum_v_fini)(struct fdirenum *__restrict self) {
	struct procfs_perproc_drives_enum *me;
	me = (struct procfs_perproc_drives_enum *)self;
	decref_unlikely(me->ppde_vfs);
}

PRIVATE BLOCKING NONNULL((1, 5)) size_t KCALL
procfs_perproc_drives_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                              size_t bufsize, readdir_mode_t readdir_mode,
                              struct flnknode_ops const *__restrict ops)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	struct procfs_perproc_drives_enum *me;
	char namebuf[2];
	uint8_t oldindex, newindex;
	ssize_t result;
	me = (struct procfs_perproc_drives_enum *)self;
again:
	/* Read current index. */
	oldindex = atomic_read(&me->ppde_driveno);
	newindex = oldindex;

	for (;;) {
		if (newindex >= VFS_DRIVECOUNT)
			return 0; /* End-of-directory */
		if (atomic_read(&me->ppde_vfs->vf_drives[newindex]) != NULL)
			break; /* This one's bound! */
		++newindex;
	}

	/* Construct filename. */
	namebuf[0] = 'A' + newindex;
	namebuf[1] = '\0';

	/* Feed directory entry. */
	result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
	                             procfs_perproc_ino((uintptr_t)self->de_dir->fn_fsdata ^
	                                                (uintptr_t)self,
	                                                ops),
	                             DT_LNK, 1, namebuf);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */

	/* Advance directory position. */
	if (!atomic_cmpxch(&me->ppde_driveno, oldindex, newindex + 1))
		goto again;
	return (size_t)result;
}

PRIVATE BLOCKING NONNULL((1)) size_t KCALL
procfs_perproc_dcwd_enum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                                   size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	return procfs_perproc_drives_readdir(self, buf, bufsize, readdir_mode, &procfs_perproc_dcwdlink_ops);
}

PRIVATE BLOCKING NONNULL((1)) size_t KCALL
procfs_perproc_drives_enum_v_readdir(struct fdirenum *__restrict self, NCX struct dirent *buf,
                                     size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	return procfs_perproc_drives_readdir(self, buf, bufsize, readdir_mode, &procfs_perproc_drivelink_ops);
}

#define procfs_perproc_dcwd_enum_v_seekdir procfs_perproc_drives_enum_v_seekdir
PRIVATE BLOCKING NONNULL((1)) pos_t KCALL
procfs_perproc_drives_enum_v_seekdir(struct fdirenum *__restrict self,
                                     off_t offset, unsigned int whence)
		THROWS(E_OVERFLOW, E_INVALID_ARGUMENT_UNKNOWN_COMMAND, E_IOERROR, ...) {
	uint8_t newpos;
	struct procfs_perproc_drives_enum *me = (struct procfs_perproc_drives_enum *)self;
	switch (whence) {

	case SEEK_SET:
#if __SIZEOF_POS_T__ > __SIZEOF_PID_T__
		if unlikely((pos_t)offset > (pos_t)(uint8_t)-1)
			THROW(E_OVERFLOW);
#endif /* __SIZEOF_POS_T__ > __SIZEOF_PID_T__ */
		newpos = (uint8_t)(pos_t)offset;
		atomic_write(&me->ppde_driveno, newpos);
		break;

	case SEEK_CUR: {
		uint8_t oldpos;
		do {
			oldpos = atomic_read(&me->ppde_driveno);
			newpos = oldpos + (int8_t)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!atomic_cmpxch_weak(&me->ppde_driveno, oldpos, newpos));
	}	break;

	case SEEK_END: {
		newpos = VFS_DRIVECOUNT + (int8_t)offset;
		if unlikely(offset < 0 ? newpos > VFS_DRIVECOUNT
		                       : newpos < VFS_DRIVECOUNT)
			THROW(E_OVERFLOW);
		atomic_write(&me->ppde_driveno, newpos);
	}	break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_LSEEK_WHENCE,
		      whence);
	}
	return (pos_t)newpos;
}

PRIVATE struct fdirenum_ops const procfs_perproc_dcwd_enum_ops = {
	.deo_fini    = &procfs_perproc_dcwd_enum_v_fini,
	.deo_readdir = &procfs_perproc_dcwd_enum_v_readdir,
	.deo_seekdir = &procfs_perproc_dcwd_enum_v_seekdir,
};
PRIVATE struct fdirenum_ops const procfs_perproc_drives_enum_ops = {
	.deo_fini    = &procfs_perproc_drives_enum_v_fini,
	.deo_readdir = &procfs_perproc_drives_enum_v_readdir,
	.deo_seekdir = &procfs_perproc_drives_enum_v_seekdir,
};

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_drives_enum_init(struct fdirenum *__restrict result,
                                struct fdirenum_ops const *__restrict ops) {
	struct procfs_perproc_drives_enum *rt;
	REF struct task *thread;
	REF struct fs *threadfs;
	rt     = (struct procfs_perproc_drives_enum *)result;
	thread = taskpid_gettask(rt->de_dir->fn_fsdata);
	if unlikely(!thread) {
		rt->de_ops = &fdirenum_empty_ops;
		return;
	}
	threadfs = task_getfs(thread);
	decref_unlikely(thread);
	rt->ppde_vfs = incref(threadfs->fs_vfs);
	decref_unlikely(threadfs);
	rt->ppde_driveno = 0;
	rt->de_ops       = ops;
}

#define procfs_perproc_kos_dcwd_v_enumsz sizeof(struct procfs_perproc_drives_enum)
PRIVATE NONNULL((1)) void KCALL
procfs_perproc_kos_dcwd_v_enum(struct fdirenum *__restrict result) {
	procfs_perproc_drives_enum_init(result, &procfs_perproc_dcwd_enum_ops);
}

#define procfs_perproc_kos_drives_v_enumsz sizeof(struct procfs_perproc_drives_enum)
PRIVATE NONNULL((1)) void KCALL
procfs_perproc_kos_drives_v_enum(struct fdirenum *__restrict result) {
	procfs_perproc_drives_enum_init(result, &procfs_perproc_drives_enum_ops);
}

INTERN_CONST struct fdirnode_ops const procfs_pp_kos_dcwd = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_dir_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
		.no_perm   = &procfs_perproc_dir_v_perm_ops,
	},
	.dno_lookup = &procfs_perproc_kos_dcwd_v_lookup,
	.dno_enumsz = procfs_perproc_kos_dcwd_v_enumsz,
	.dno_enum   = &procfs_perproc_kos_dcwd_v_enum,
};

INTERN_CONST struct fdirnode_ops const procfs_pp_kos_drives = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_dir_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
		.no_perm   = &procfs_perproc_dir_v_perm_ops,
	},
	.dno_lookup = &procfs_perproc_kos_drives_v_lookup,
	.dno_enumsz = procfs_perproc_kos_drives_v_enumsz,
	.dno_enum   = &procfs_perproc_kos_drives_v_enum,
};




DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_C */
