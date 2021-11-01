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
#include <fs/vfs.h>
#include <kernel/execabi.h> /* execabi_system_rtld_file */
#include <kernel/fs/constdir.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/lnknode.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/printnode.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle.h>
#include <kernel/mman.h>
#include <kernel/mman/enum.h>
#include <kernel/mman/execinfo.h>
#include <kernel/mman/memfd.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/mnode.h>
#include <kernel/mman/ramfile.h>
#include <kernel/mman/rw.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/align.h>
#include <hybrid/atomic.h>
#include <hybrid/overflow.h>

#include <compat/config.h>
#include <kos/dev.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/except/reason/io.h>
#include <kos/exec/peb.h>
#include <kos/exec/rtld.h> /* RTLD_LIBDL */
#include <sys/stat.h>

#include <assert.h>
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
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

#define print(p, len) (*printer)(arg, p, len)
#define printf(...)   format_printf(printer, arg, __VA_ARGS__)
#define PRINT(str)    print(str, COMPILER_STRLEN(str))

/* Forward declarations (to cause compiler errors if laster declarations are incompatible) */
#define MKREG_RO(ops_symbol_name, printer)     \
	INTDEF NONNULL((1, 2)) void KCALL          \
	printer(struct printnode *__restrict self, \
	        pformatprinter printer, void *arg, \
	        size_t offset_hint);
#define MKREG_RW(ops_symbol_name, printer, writer)                      \
	INTDEF NONNULL((1, 2)) void KCALL                                   \
	printer(struct printnode *__restrict self,                          \
	        pformatprinter printer_, void *arg,                         \
	        size_t offset_hint);                                        \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL                            \
	writer(struct mfile *__restrict self, USER CHECKED void const *src, \
	       size_t num_bytes, pos_t addr, iomode_t mode) THROWS(...);
#define MKLNK(ops_symbol_name, readlink)       \
	INTDEF WUNUSED NONNULL((1)) size_t KCALL   \
	readlink(struct flnknode *__restrict self, \
	         USER CHECKED /*utf-8*/ char *buf, \
	         size_t bufsize)                   \
			THROWS(E_SEGFAULT, E_IOERROR, ...);
#include "perproc.def"


/* Common operators for all per-process files. */
#define procfs_perproc_v_changed fnode_v_changed
#define procfs_perproc_v_wrattr  fnode_v_wrattr_noop
#define procfs_perproc_v_free    (*((void(KCALL *)(struct fnode *__restrict))(void *)(uintptr_t)-1))
INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_perproc_v_destroy)(struct mfile *__restrict self);

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_v_stat_common(struct mfile *__restrict self,
                             USER CHECKED struct stat *result)
		THROWS(...) {
	struct fnode *me        = mfile_asnode(self);
	REF struct task *thread = taskpid_gettask(me->fn_fsdata);
	/* Set timestamps based on thread times. */
	if (thread) {
		struct timespec ts;
		REF struct cred *thread_cred;
		FINALLY_DECREF_UNLIKELY(thread);

		/* Creation-time: store the time when the thread was started. */
		ts = task_getstarttime(thread);
		result->st_ctimespec.tv_sec  = (typeof(result->st_ctimespec.tv_sec))ts.tv_sec;
		result->st_ctimespec.tv_nsec = (typeof(result->st_ctimespec.tv_nsec))ts.tv_nsec;

		/* Last-accessed + last-modified: store the last point in time when the thread got executed. */
		ts = thread == THIS_TASK ? realtime() : ktime_to_timespec(FORTASK(thread, this_stoptime));
		result->st_atimespec.tv_sec  = (typeof(result->st_atimespec.tv_sec))ts.tv_sec;
		result->st_atimespec.tv_nsec = (typeof(result->st_atimespec.tv_nsec))ts.tv_nsec;
		result->st_mtimespec.tv_sec  = (typeof(result->st_mtimespec.tv_sec))ts.tv_sec;
		result->st_mtimespec.tv_nsec = (typeof(result->st_mtimespec.tv_nsec))ts.tv_nsec;

		/* Fill uid/gid based on thread credentials. */
		thread_cred = task_getcred(thread);
		FINALLY_DECREF_UNLIKELY(thread_cred);
		/* NOTE: Yes, we need to use the effective U/G-id here (linux does the same) */
		result->st_uid = (typeof(result->st_uid))ATOMIC_READ(thread_cred->c_euid);
		result->st_gid = (typeof(result->st_gid))ATOMIC_READ(thread_cred->c_egid);

	} else {
		/* Fallback: just write the current time... */
		struct timespec now          = realtime();
		result->st_atimespec.tv_sec  = (typeof(result->st_atimespec.tv_sec))now.tv_sec;
		result->st_atimespec.tv_nsec = (typeof(result->st_atimespec.tv_nsec))now.tv_nsec;
		result->st_mtimespec.tv_sec  = (typeof(result->st_mtimespec.tv_sec))now.tv_sec;
		result->st_mtimespec.tv_nsec = (typeof(result->st_mtimespec.tv_nsec))now.tv_nsec;
		result->st_ctimespec.tv_sec  = (typeof(result->st_ctimespec.tv_sec))now.tv_sec;
		result->st_ctimespec.tv_nsec = (typeof(result->st_ctimespec.tv_nsec))now.tv_nsec;
	}
}

INTERN NONNULL((1)) void KCALL
procfs_perproc_dir_v_stat(struct mfile *__restrict self,
                          USER CHECKED struct stat *result)
		THROWS(...) {
	procfs_perproc_v_stat_common(self, result);
	fdirnode_v_stat(self, result);
}

INTERN NONNULL((1)) void KCALL
procfs_perproc_printnode_v_stat(struct mfile *__restrict self,
                                USER CHECKED struct stat *result)
		THROWS(...) {
	procfs_perproc_v_stat_common(self, result);
	printnode_v_stat(self, result);
}

INTERN NONNULL((1)) void KCALL
procfs_perproc_lnknode_v_stat(struct mfile *__restrict self,
                              USER CHECKED struct stat *result)
		THROWS(...) {
	size_t lnksize;
	struct flnknode *me            = mfile_aslnk(self);
	struct flnknode_ops const *ops = flnknode_getops(me);
	procfs_perproc_v_stat_common(self, result);
	lnksize           = (*ops->lno_readlink)(me, NULL, 0);
	result->st_blocks = CEILDIV(lnksize, PAGESIZE);
	result->st_size   = lnksize;
}

INTERN_CONST struct mfile_stream_ops const procfs_perproc_lnknode_v_stream_ops = {
	.mso_stat = &procfs_perproc_lnknode_v_stat,
};

INTERN_CONST struct mfile_stream_ops const procfs_perproc_printnode_v_stream_ops = {
	.mso_pread  = &printnode_v_pread,
	.mso_preadv = &printnode_v_preadv,
	.mso_stat   = &procfs_perproc_printnode_v_stat,
};

/* Operators for per-process directories */
#define procfs_perproc_dir_v_free    procfs_perproc_v_free
#define procfs_perproc_dir_v_destroy procfs_perproc_v_destroy
#define procfs_perproc_dir_v_changed procfs_perproc_v_changed
#define procfs_perproc_dir_v_wrattr  procfs_perproc_v_wrattr
INTERN_CONST struct mfile_stream_ops const procfs_perproc_dir_v_stream_ops = {
	.mso_open = &fdirnode_v_open,
	.mso_stat = &procfs_perproc_dir_v_stat,
};
#define procfs_perproc_dir_v_open fdirnode_v_open





/* Helper for printing `struct fs' member paths. */
PRIVATE WUNUSED NONNULL((1)) size_t KCALL
ProcFS_PerProc_FsSpecificPath_ReadLink(struct flnknode *__restrict self,
                                       USER CHECKED /*utf-8*/ char *buf,
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
	return path_sprint(thread_pth, buf, bufsize,
	                   fs_atflags(0), caller_root);
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
                         USER CHECKED /*utf-8*/ char *buf,
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
			.mo_destroy = &procfs_perproc_v_destroy,
			.mo_changed = &procfs_perproc_v_changed,
			.mo_stream  = &procfs_perproc_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_perproc_v_free,
		.no_wrattr = &procfs_perproc_v_wrattr,
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
                          USER CHECKED /*utf-8*/ char *buf,
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
			.mo_destroy = &procfs_perproc_v_destroy,
			.mo_changed = &procfs_perproc_v_changed,
			.mo_stream  = &procfs_perproc_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_perproc_v_free,
		.no_wrattr = &procfs_perproc_v_wrattr,
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
                           USER CHECKED /*utf-8*/ char *buf,
                           size_t bufsize)
		THROWS(E_SEGFAULT, ...) {
	REF struct task *thread;
	REF struct mman *thread_mm;
	REF struct path *exec_path;
	REF struct fdirent *exec_dent;
	REF struct path *caller_root;
	thread    = taskpid_gettask_srch(self->fn_fsdata);
	thread_mm = task_getmman(thread);
	decref_unlikely(thread);
	{
		FINALLY_DECREF_UNLIKELY(thread_mm);
		mman_lock_read(thread_mm);
		exec_dent = xincref(FORMMAN(thread_mm, thismman_execinfo).mei_dent);
		exec_path = xincref(FORMMAN(thread_mm, thismman_execinfo).mei_path);
		mman_lock_endread(thread_mm);
	}
	if unlikely(!exec_dent) {
		xdecref_unlikely(exec_path);
		THROW(E_FSERROR_FILE_NOT_FOUND);
	}
	FINALLY_DECREF_UNLIKELY(exec_dent);
	if unlikely(!exec_path) {
		return snprintf(buf, bufsize, "%s%$s",
		                exec_dent->fd_name[0] == '/' ? "" : "?/",
		                (size_t)exec_dent->fd_namelen,
		                exec_dent->fd_name);
	}
	FINALLY_DECREF_UNLIKELY(exec_path);
	caller_root = fs_getroot(THIS_FS);
	return path_sprintent(exec_path, exec_dent->fd_name,
	                      exec_dent->fd_namelen, buf, bufsize,
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
			.mo_destroy = &procfs_perproc_v_destroy,
			.mo_changed = &procfs_perproc_v_changed,
			.mo_stream  = &procfs_perproc_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_perproc_v_free,
		.no_wrattr = &procfs_perproc_v_wrattr,
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
                        void *arg, USER CHECKED char const *cstr) {
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
                                 size_t strc, char const *USER UNCHECKED const *USER CHECKED strv) {
	size_t i;

	/* Verify bounds. */
	if unlikely(OVERFLOW_UMUL(strc, sizeof(*strv), &i))
		return;
	if unlikely(OVERFLOW_UADD((uintptr_t)strv, i, &i))
		return;
	if unlikely(!ADDRRANGE_ISUSER(strv, i))
		return;
	while (strc) {
		USER UNCHECKED char const *strings[32];
		size_t count = strc;
		if (count > COMPILER_STRLEN(strings))
			count = COMPILER_STRLEN(strings);
		mman_read(mm, strv, strings, count * sizeof(USER UNCHECKED char const *));
		for (i = 0; i < count; ++i) {
			USER UNCHECKED char const *str = strings[i];
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
                                       size_t strc, compat_uintptr_t USER UNCHECKED const *USER CHECKED strv) {
	size_t i;

	/* Verify bounds. */
	if unlikely(OVERFLOW_UMUL(strc, sizeof(*strv), &i))
		return;
	if unlikely(OVERFLOW_UADD((uintptr_t)strv, i, &i))
		return;
	if unlikely(!ADDRRANGE_ISUSER(strv, i))
		return;
	while (strc) {
		USER UNCHECKED compat_uintptr_t strings[32];
		size_t count = strc;
		if (count > COMPILER_STRLEN(strings))
			count = COMPILER_STRLEN(strings);
		mman_read(mm, strv, strings, count * sizeof(USER UNCHECKED compat_uintptr_t));
		for (i = 0; i < count; ++i) {
			USER UNCHECKED compat_uintptr_t str = strings[i];
			if (!str || !ADDR_ISUSER(str))
				return;
			if (print_userspace_cstring(mm, printer, arg,
			                            (USER CHECKED char const *)(uintptr_t)str))
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
	char const *USER UNCHECKED const *USER UNCHECKED pp_argv;
#else /* OFFSET_PROCESS_PEB_ARGC < OFFSET_PROCESS_PEB_ARGV */
	char const *USER UNCHECKED const *USER UNCHECKED pp_argv;
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
                  void *arg, USER CHECKED struct process_peb const *peb) {
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
                         void *arg, USER CHECKED struct compat_process_peb const *peb) {
	struct _compat_peb_cmdline_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_COMPAT_PROCESS_PEB_ARGC, &info, sizeof(info));
	ProcFS_PrintCompatUserSpaceStringArray(mm, printer, arg, info.pp_argc, info.pp_argv);
}
#endif /* __ARCH_HAVE_COMPAT */

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Cmdline_Printer(struct printnode *__restrict self,
                               pformatprinter printer, void *arg,
                               size_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *threadmm;
	USER CHECKED void *peb;

	/* Lookup the relevant mman. */
	thread   = taskpid_gettask_srch(self->fn_fsdata);
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(threadmm);
	peb = FORMMAN(threadmm, thismman_execinfo).mei_peb;
#ifdef __ARCH_HAVE_COMPAT
	if (FORMMAN(threadmm, thismman_execinfo).mei_peb_iscompat) {
		compat_peb_print_cmdline(threadmm, printer, arg,
		                         (USER CHECKED struct compat_process_peb const *)peb);
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
		peb_print_cmdline(threadmm, printer, arg,
		                  (USER CHECKED struct process_peb const *)peb);
	}
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
	char const *USER UNCHECKED const *USER UNCHECKED pp_envp;
#else /* OFFSET_PROCESS_PEB_ENVC < OFFSET_PROCESS_PEB_ENVP */
	char const *USER UNCHECKED const *USER UNCHECKED pp_envp;
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
                   void *arg, USER CHECKED struct process_peb const *peb) {
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
                         void *arg, USER CHECKED struct compat_process_peb const *peb) {
	struct _compat_peb_environ_buffer info;
	mman_read(mm, (byte_t const *)peb + OFFSET_COMPAT_PROCESS_PEB_ENVC, &info, sizeof(info));
	ProcFS_PrintCompatUserSpaceStringArray(mm, printer, arg, info.pp_envc, info.pp_envp);
}
#endif /* __ARCH_HAVE_COMPAT */

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Environ_Printer(struct printnode *__restrict self,
                               pformatprinter printer, void *arg,
                               size_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *threadmm;
	USER CHECKED void *peb;

	/* Lookup the relevant mman. */
	thread   = taskpid_gettask_srch(self->fn_fsdata);
	threadmm = task_getmman(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(threadmm);
	peb = FORMMAN(threadmm, thismman_execinfo).mei_peb;
#ifdef __ARCH_HAVE_COMPAT
	if (FORMMAN(threadmm, thismman_execinfo).mei_peb_iscompat) {
		compat_peb_print_environ(threadmm, printer, arg,
		                         (USER CHECKED struct compat_process_peb const *)peb);
	} else
#endif /* __ARCH_HAVE_COMPAT */
	{
		peb_print_environ(threadmm, printer, arg,
		                  (USER CHECKED struct process_peb const *)peb);
	}
}



/************************************************************************/
/* /proc/[PID]/maps                                                  */
/************************************************************************/
/* Check if `self' has a special names, and if so: return that name. */
PRIVATE NOBLOCK WUNUSED NONNULL((1)) char const *
NOTHROW(FCALL nameof_special_file)(struct mfile *__restrict self) {
	/* The libdl program hard-coded into the kernel. */
	if (self == &execabi_system_rtld_file.mrf_file)
		return RTLD_LIBDL;
#ifdef __ARCH_HAVE_COMPAT
	if (self == &compat_execabi_system_rtld_file.mrf_file)
		return COMPAT_RTLD_LIBDL;
#endif /* __ARCH_HAVE_COMPAT */
	if (self >= mfile_anon && self < COMPILER_ENDOF(mfile_anon))
		return "[anon]";
	if (self == &mfile_ndef)
		return "[undef]";
	return NULL;
}


struct maps_printer_data {
	pformatprinter   pd_printer; /* [1..1] The target printer. */
	void            *pd_arg;     /* [?..?] Argument for `pd_printer' */
	REF struct path *pd_root;    /* [0..1] Lazily initialized root directory of parent. */
	atflag_t         pd_atflags; /* [valid_if(pd_root)] AT_* flags */
};

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
	           info->mmi_min, info->mmi_max,
	           info->mmi_flags & MNODE_F_PREAD /* */ ? 'r' : '-',
	           info->mmi_flags & MNODE_F_PWRITE /**/ ? 'w' : '-',
	           info->mmi_flags & MNODE_F_PEXEC /* */ ? 'x' : '-',
	           info->mmi_flags & MNODE_F_SHARED /**/ ? 's' : 'p',
	           info->mmi_offset,
	           MAJOR(dev), MINOR(dev), ino) < 0)
		goto err;
	if (info->mmi_fsname) {
		if (info->mmi_fspath) {
			if (!ctx->pd_root) {
				ctx->pd_atflags = fs_atflags(0) | AT_PATHPRINT_INCTRAIL;
				ctx->pd_root    = fs_getroot(THIS_FS);
			}
			path_printent(info->mmi_fspath, info->mmi_fsname->fd_name,
			              info->mmi_fsname->fd_namelen, printer, arg,
			              ctx->pd_atflags, ctx->pd_root);
		} else if (info->mmi_fsname->fd_name[0] == '/') {
			print(info->mmi_fsname->fd_name,
			      info->mmi_fsname->fd_namelen);
		} else {
			printf("?/%$#q",
			       (size_t)info->mmi_fsname->fd_namelen,
			       info->mmi_fsname->fd_name);
		}
	} else if (info->mmi_file) {
		/* Check if it's a device file (in which case we can extract the filename). */
		if (mfile_isdevice(info->mmi_file)) {
			REF struct path *devfs_mount;
			struct devdirent *name;
			struct device *dev = mfile_asdevice(info->mmi_file);
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
				path_printent(devfs_mount, name->dd_dirent.fd_name,
				              name->dd_dirent.fd_namelen, printer, arg,
				              ctx->pd_atflags, ctx->pd_root);
			} else {
				printf("devfs:/%$s",
				       (size_t)name->dd_dirent.fd_namelen,
				       name->dd_dirent.fd_name);
			}
		} else {
			/* Lastly, there are a couple of special files for which we know names. */
			char const *special_name;
			special_name = nameof_special_file(info->mmi_file);
			if (special_name) {
				print(special_name, strlen(special_name));
			} else {
				/* For everything else, just print the /proc/[pid]/fd/[fdno] link text. */
				mfile_uprintlink(info->mmi_file, printer, arg);
			}
		}
	}
	if (PRINT("\n") < 0)
		goto err;
	return 0;
err:
	return -1;
}



/************************************************************************/
/* /proc/[PID]/mounts                                                   */
/************************************************************************/
PRIVATE NONNULL((1, 2, 3)) ssize_t KCALL
print_mounting_point(struct path *__restrict fsroot,
                     struct pathmount *__restrict self,
                     pformatprinter printer, void *arg) {
	char flagsbuf[128], *writer;
	struct fsuper *super = self->p_dir->fn_super;
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
	flags = ATOMIC_READ(super->fs_root.mf_flags);
	if (super->fs_dev)
		flags |= ATOMIC_READ(super->fs_dev->mf_flags) & MFILE_F_READONLY;

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
//TODO:	if (flags & MS_NODEV)
//TODO:		writer = stpcpy(writer, ",nodev");
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

	/* I have no idea what these 2 "0"-s are supposed to be, but looking at the
	 * linux kernel source, it too simply prints a string " 0 0\n" to terminate
	 * every line.
	 * There's no comment explaining it, but if I had to guess, it's probably
	 * related to some since-removed legacy feature... */
	return PRINT(" 0 0\n");
err:
	return -1;
}

INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Mounts_Printer(struct printnode *__restrict self,
                              pformatprinter printer, void *arg,
                              size_t UNUSED(offset_hint)) {
	REF struct path *fsroot;
	REF struct pathmount *iter;
	REF struct vfs *thread_vfs;
	REF struct task *thread = taskpid_gettask(self->fn_fsdata);
	if unlikely(!thread)
		return;
	thread_vfs = task_getvfs(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(thread_vfs);
	fsroot = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(fsroot);
	iter = vfs_mounts_next(thread_vfs, NULL);
	while (iter) {
		FINALLY_DECREF_UNLIKELY(iter);
		if (print_mounting_point(fsroot, iter, printer, arg))
			break;
		iter = vfs_mounts_next(thread_vfs, iter);
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
ProcFS_PerProc_Maps_Printer(struct printnode *__restrict self,
                            pformatprinter printer, void *arg,
                            size_t UNUSED(offset_hint)) {
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


INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Stat_Printer(struct printnode *__restrict self,
                            pformatprinter printer, void *arg,
                            size_t UNUSED(offset_hint)) {
	REF struct task *thread;
	REF struct mman *mm = NULL;
	struct taskpid *tpid;
	tpid   = self->fn_fsdata;
	thread = taskpid_gettask(tpid);
	FINALLY_XDECREF_UNLIKELY(thread);
	if (thread)
		mm = task_getmman(thread);
	FINALLY_XDECREF_UNLIKELY(mm);
	if (printf("%" PRIuN(__SIZEOF_PID_T__) " (",
	           taskpid_getpid_s(tpid)) < 0)
		return;
	if (mm) {
		REF struct fdirent *exec_dent;
		mman_lock_read(mm);
		exec_dent = xincref(FORMMAN(mm, thismman_execinfo).mei_dent);
		mman_lock_endread(mm);
		if (!exec_dent)
			goto no_exec;
		FINALLY_DECREF_UNLIKELY(exec_dent);
		print(exec_dent->fd_name, exec_dent->fd_namelen);
	} else {
no_exec:
		PRINT("?");
	}
	PRINT(") ");
	if ((*printer)(arg, ") ", 2) < 0)
		return;
	{
		char state;
		if (thread) {
			uintptr_t flags;
			flags = ATOMIC_READ(thread->t_flags);
			if (flags & TASK_FRUNNING)
				state = 'R'; /* Running */
			else if (flags & (TASK_FSUSPENDED | TASK_FGDB_STOPPED))
				state = 'T'; /* Stopped */
			else if (flags & TASK_FSTARTED)
				state = 'S'; /* Sleeping */
			else {
				/* XXX: 'W' For waking??? */
				state = 'P'; /* Parked? */
			}
		} else {
			/* XXX: 'X' For dead??? */
			state = 'Z'; /* Zombie */
		}
		print(&state, 1);
	}
	if (thread) {
		REF struct task *parent;
		parent = task_getprocessparent_of(thread);
		if unlikely(!parent)
			goto noparent;
		FINALLY_DECREF_UNLIKELY(parent);
		if (printf(" %" PRIuN(__SIZEOF_PID_T__) " ",
		           task_gettid_of_s(parent)) < 0)
			return;
	} else {
noparent:
		if (PRINT(" 0 ") < 0)
			return;
	}
	if (thread) {
		REF struct task *group;
		group = task_getprocessgroupleader_of(thread);
		if unlikely(!group)
			goto nogroup;
		FINALLY_DECREF_UNLIKELY(group);
		if (printf("%" PRIuN(__SIZEOF_PID_T__) " ",
		           task_gettid_of_s(group)) < 0)
			return;
	} else {
nogroup:
		if (PRINT("0 ") < 0)
			return;
	}
	if (thread) {
		REF struct task *session;
		REF struct ttydev *ctty;
		REF struct taskpid *fproc;
		dev_t tty_devno;
		u32 tty_devno_encoded;
		session = task_getsessionleader_of(thread);
		if unlikely(!session)
			goto nosession;
		FINALLY_DECREF_UNLIKELY(session);
		if (printf("%" PRIuN(__SIZEOF_PID_T__) " ",
		           task_gettid_of_s(session)) < 0)
			return;
		ctty = axref_get(&FORTASK(thread, this_taskgroup).tg_ctty);
		if (!ctty)
			goto noctty;
		FINALLY_DECREF_UNLIKELY(ctty);
		tty_devno = chrdev_getdevno(ctty);
		tty_devno_encoded = ((MAJOR(tty_devno) & 0xff) << 8) |
		                    ((MINOR(tty_devno) & 0xff) |
		                     (MINOR(tty_devno) & 0xffff00) << 8);
		if (printf("%" PRIu32 " ",
		           tty_devno_encoded) < 0)
			return;
		fproc = axref_get(&ctty->t_fproc);
		if (!fproc)
			goto nofproc;
		FINALLY_DECREF_UNLIKELY(fproc);
		if (printf("%" PRIuN(__SIZEOF_PID_T__) " ",
		                  taskpid_getpid_s(fproc)) < 0)
			return;
	} else {
nosession:
		if ((*printer)(arg, "0 ", 2) < 0)
			return;
noctty:
		if ((*printer)(arg, "0 ", 2) < 0)
			return;
nofproc:
		if ((*printer)(arg, "-1 ", 3) < 0)
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
		sync_read(mm);
		vsize = mman_get_total_mapped_bytes(mm);
		sync_endread(mm);
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
	       "%u",           /* exit_code */
#ifdef KERNELSPACE_HIGHMEM
	       0,                /* TODO: start_data */
	       KERNELSPACE_BASE, /* TODO: end_data */
#else /* KERNELSPACE_HIGHMEM */
	       KERNEL_CEILING, /* TODO: start_data */
	       (void *)-1,     /* TODO: end_data */
#endif /* !KERNELSPACE_HIGHMEM */
	       tpid->tp_status.w_status);
}



/************************************************************************/
/* /proc/[PID]/attr/current                                             */
/************************************************************************/
INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_Attr_Current_Printer(struct printnode *__restrict self,
                                    pformatprinter printer, void *arg,
                                    size_t UNUSED(offset_hint)) {
	(void)self;
	PRINT("unconfined");
}



/************************************************************************/
/* /proc/[PID]/x86/iopl                                                 */
/************************************************************************/
#if defined(__x86_64__) || defined(__i386__)
INTERN NONNULL((1, 2)) void KCALL
ProcFS_PerProc_X86_Iopl_Print(struct printnode *__restrict self,
                              pformatprinter printer, void *arg,
                              size_t UNUSED(offset_hint)) {
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
ProcFS_PerProc_X86_Iopl_Write(struct mfile *__restrict self, USER CHECKED void const *src,
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
	REF void      *pfl_handdat; /* [1..1][const] Handle data pointer. */
	uintptr_half_t pfl_handtyp; /* [const] Handle type (One of `HANDLE_TYPE_*') */
};

INTDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_fd_lnknode_v_destroy)(struct mfile *__restrict self) {
	struct procfs_fd_lnknode *me;
	me = (struct procfs_fd_lnknode *)mfile_aslnk(self);
	assert(!LIST_ISBOUND(me, fn_allnodes));
	assert(me->fn_supent.rb_rhs == FSUPER_NODES_DELETED);
	assert(me->mf_parts == MFILE_PARTS_ANONYMOUS);
	(*handle_type_db.h_decref[me->pfl_handtyp])(me->pfl_handdat);
	decref_unlikely(me->fn_fsdata);
	kfree(me);
}
#define procfs_fd_lnknode_v_changed    procfs_perproc_v_changed
#define procfs_fd_lnknode_v_wrattr     procfs_perproc_v_wrattr
#define procfs_fd_lnknode_v_free       procfs_perproc_v_free
#define procfs_fd_lnknode_v_stream_ops procfs_perproc_lnknode_v_stream_ops

PRIVATE WUNUSED NONNULL((1)) size_t KCALL
procfs_fd_lnknode_v_readlink(struct flnknode *__restrict self,
                             USER CHECKED /*utf-8*/ char *buf,
                             size_t bufsize)
		THROWS(E_SEGFAULT, E_IOERROR, ...) {
	struct procfs_fd_lnknode *me;
	struct format_snprintf_data dat;
	me = (struct procfs_fd_lnknode *)mfile_aslnk(self);
	dat.sd_buffer = buf;
	dat.sd_bufsiz = bufsize;
	return (size_t)((*handle_type_db.h_printlink[me->pfl_handtyp])(me->pfl_handdat,
	                                                               &format_snprintf_printer,
	                                                               &dat));
}

PRIVATE WUNUSED NONNULL((1, 2, 3, 4)) bool KCALL
procfs_fd_lnknode_v_openlink(struct flnknode *__restrict self,
                             struct handle *__restrict result,
                             struct path *__restrict UNUSED(access_path),
                             struct fdirent *__restrict UNUSED(access_dent))
		THROWS(E_IOERROR, E_BADALLOC, ...) {
	struct procfs_fd_lnknode *me;
	/* This is the function that implements the magic for open("/proc/[pid]/fd/[no]"),
	 * such  that  such a  call  behaves as  a  dup(2), rather  than open(readlink())! */
	me = (struct procfs_fd_lnknode *)mfile_aslnk(self);
	result->h_data = me->pfl_handdat;
	result->h_type = me->pfl_handtyp;
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
	switch (me->pfl_handtyp) {

	case HANDLE_TYPE_FILEHANDLE:
	case HANDLE_TYPE_FIFOHANDLE: {
		struct filehandle *hand;
		STATIC_ASSERT(offsetof(struct filehandle, fh_path) == offsetof(struct fifohandle, fu_path));
		STATIC_ASSERT(offsetof(struct filehandle, fh_dirent) == offsetof(struct fifohandle, fu_dirent));
		hand = (struct filehandle *)me->pfl_handdat;
		if (hand->fh_path && hand->fh_dirent && mfile_isnode(hand->fh_file)) {
			*presult_path   = incref(hand->fh_path);
			*presult_dirent = incref(hand->fh_dirent);
			return mfile_asnode(incref(hand->fh_file));
		}
	}	break;

	case HANDLE_TYPE_DIRHANDLE: {
		struct dirhandle *hand;
		hand = (struct dirhandle *)me->pfl_handdat;
		if (hand->dh_path && hand->dh_dirent) {
			*presult_path   = incref(hand->dh_path);
			*presult_dirent = incref(hand->dh_dirent);
			return mfile_asdir(incref(hand->dh_enum.de_dir));
		}
	}	break;

	case HANDLE_TYPE_MFILE: {
		/* Device handles are known  to be relative to  the
		 * devfs root (so-long as they've not been deleted) */
		if (mfile_isdevice((struct mfile *)me->fn_fsdata)) {
			struct device *dev;
			dev = mfile_asdevice((struct mfile *)me->fn_fsdata);
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
		struct path *pth = (struct path *)me->pfl_handdat;
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
	if (me->pfl_handtyp == HANDLE_TYPE_PATH)
		return incref((struct path *)me->pfl_handdat);
	return NULL;
}
#endif /* !__OPTIMIZE_SIZE__ */


INTERN_CONST struct flnknode_ops const procfs_perproc_fdlnk_ops = {
	.lno_node = {
		.no_file = {
			.mo_destroy = &procfs_fd_lnknode_v_destroy,
			.mo_changed = &procfs_fd_lnknode_v_changed,
			.mo_stream  = &procfs_fd_lnknode_v_stream_ops,
		},
		.no_free   = &procfs_fd_lnknode_v_free,
		.no_wrattr = &procfs_fd_lnknode_v_wrattr,
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
INTDEF struct flnknode const procfs_fdlnk_template;


struct procfs_fd_dirent {
	REF struct taskpid *pfd_thread;  /* [1..1][const] The thread being accessed. */
	REF void           *pfd_handptr; /* [1..1][const] Handle data pointer. */
	uintptr_half_t      pfd_handtyp; /* [const] Handle type (One of `HANDLE_TYPE_*') */
	struct fdirent      pfd_ent;     /* Underlying directory entry. */
};
#define fdirent_asfd(self) container_of(self, struct procfs_fd_dirent, pfd_ent)


PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_fd_dirent_v_destroy)(struct fdirent *__restrict self) {
	struct procfs_fd_dirent *me = fdirent_asfd(self);
	(*handle_type_db.h_decref[me->pfd_handtyp])(me->pfd_handptr);
	decref_unlikely(me->pfd_thread);
	kfree(me);
}

PRIVATE WUNUSED NONNULL((1, 2)) REF struct fnode *KCALL
procfs_fd_dirent_v_opennode(struct fdirent *__restrict self,
                            struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_fd_dirent *me = fdirent_asfd(self);
	REF struct procfs_fd_lnknode *result;
	result = (REF struct procfs_fd_lnknode *)kmalloc(sizeof(REF struct procfs_fd_lnknode), GFP_NORMAL);
	memcpy(result, &procfs_fdlnk_template, sizeof(struct flnknode));
	result->pfl_handtyp = me->pfd_handtyp;
	result->pfl_handdat = me->pfd_handptr;
	result->fn_fsdata   = incref(me->pfd_thread);
	result->fn_ino      = procfs_perproc_ino(me->pfd_handptr, &procfs_perproc_fdlnk_ops);
	(*handle_type_db.h_incref[me->pfd_handtyp])(me->pfd_handptr);
	return result;
}

PRIVATE ATTR_PURE WUNUSED NONNULL((1, 2)) ino_t
NOTHROW(FCALL procfs_fd_dirent_v_getino)(struct fdirent *__restrict self,
                                         struct fdirnode *__restrict UNUSED(dir)) {
	struct procfs_fd_dirent *me = fdirent_asfd(self);
	return procfs_perproc_ino(me->pfd_handptr, &procfs_perproc_fdlnk_ops);
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
	REF struct handle_manager *hm;
	char ch;

	thread = taskpid_gettask(pid);
	if (!thread)
		return NULL;
	hm = task_gethandlemanager(thread);
	decref_unlikely(thread);
	FINALLY_DECREF_UNLIKELY(hm);

	/* Decode handle number */
	if unlikely(info->flu_namelen == 0)
		goto notanfd;
	ch = ATOMIC_READ(info->flu_name[0]);
	if ((ch >= '1' && ch <= '9') || (ch == '0' && info->flu_namelen == 1)) {
		REF struct procfs_fd_dirent *result;
		unsigned int fdno = (unsigned int)(ch - '0');
		struct handle hand;
		size_t i;

		for (i = 1; i < info->flu_namelen; ++i) {
			ch = ATOMIC_READ(info->flu_name[i]);
			if unlikely(!(ch >= '0' && ch <= '9'))
				goto notanfd;
			fdno *= 10;
			fdno += (unsigned int)(ch - '0');
		}

		/* Lookup the handle in question. */
		hand = handle_trylookup(hm, fdno);
		if (hand.h_type == HANDLE_TYPE_UNDEFINED)
			return NULL; /* No such handle */

		/* Allocate the new directory entry. */
		result = (REF struct procfs_fd_dirent *)kmalloc(offsetof(struct procfs_fd_dirent, pfd_ent.fd_name) +
		                                                (info->flu_namelen + 1) * sizeof(char),
		                                                GFP_NORMAL);

		/* Fill in the directory entry. */
		result->pfd_handptr        = hand.h_data; /* Inherit reference */
		result->pfd_handtyp        = hand.h_type;
		result->pfd_thread         = incref(pid);
		result->pfd_ent.fd_namelen = (u16)sprintf(result->pfd_ent.fd_name, "%u", fdno);
		assert(result->pfd_ent.fd_namelen == info->flu_namelen);
		if (info->flu_hash == FLOOKUP_INFO_HASH_UNSET || ADDR_ISUSER(info->flu_name))
			info->flu_hash = fdirent_hash(result->pfd_ent.fd_name, result->pfd_ent.fd_namelen);
		result->pfd_ent.fd_hash   = info->flu_hash;
		result->pfd_ent.fd_refcnt = 1; /* +1: return */
		result->pfd_ent.fd_ops    = &procfs_fd_dirent_ops;
//		result->pfd_ent.fd_ino    = procfs_perproc_ino(hand.h_data, &procfs_perproc_fdlnk_ops); /* Not needed; we've got `fdo_getino()' */
		DBG_memset(&result->pfd_ent.fd_ino, 0xcc, sizeof(result->pfd_ent.fd_ino));
		result->pfd_ent.fd_type   = DT_LNK;
		return &result->pfd_ent;
	}
notanfd:
	return NULL;
}

struct procfs_fd_enum {
	FDIRENUM_HEADER
	REF struct handle_manager *pfe_hman; /* [1..1][const] Handle manager being enumerated. */
	unsigned int               pfe_fd;   /* Lower bound for next handle to enumerate. */
};

PRIVATE NOBLOCK NONNULL((1)) void
NOTHROW(KCALL procfs_fd_enum_v_fini)(struct fdirenum *__restrict self) {
	struct procfs_fd_enum *me = (struct procfs_fd_enum *)self;
	decref_unlikely(me->pfe_hman);
}

PRIVATE NONNULL((1)) size_t KCALL
procfs_fd_enum_v_readdir(struct fdirenum *__restrict self, USER CHECKED struct dirent *buf,
                         size_t bufsize, readdir_mode_t readdir_mode, iomode_t UNUSED(mode))
		THROWS(...) {
	unsigned int index, newindex;
	ssize_t result;
	struct procfs_fd_enum *me;
	u16 namelen;
#if __SIZEOF_INT__ == 4
	char namebuf[sizeof("4294967295")];
#elif __SIZEOF_INT__ == 8
	char namebuf[sizeof("18446744073709551615")];
#else /* __SIZEOF_INT__ == ... */
#error "Unsupported sizeof(pid_t)"
#endif /* __SIZEOF_INT__ != ... */
	me = (struct procfs_fd_enum *)self;

again:
	/* Read current index. */
	index = ATOMIC_READ(me->pfe_fd);

	/* Find the next handle. */
	newindex = handle_trynextfd(index, me->pfe_hman);
	if (newindex == (unsigned int)-1)
		return 0; /* End-of-directory */
	namelen = (u16)sprintf(namebuf, "%u", newindex);
	/* Feed directory entry. */
	result = fdirenum_feedent_ex(buf, bufsize, readdir_mode,
	                             procfs_perproc_ino(self->de_dir->fn_fsdata,
	                                                &procfs_perproc_fdlnk_ops),
	                             DT_LNK, namelen, namebuf);
	if (result < 0)
		return (size_t)~result; /* Don't advance directory position. */
	/* Advance directory position. */
	if (!ATOMIC_CMPXCH(me->pfe_fd, index, newindex + 1))
		goto again;
	return (size_t)result;
}

PRIVATE NOBLOCK ATTR_NOINLINE ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL handle_manager_get_max_linear_fd_plus_one)(struct handle_manager const *__restrict self) {
	unsigned int result = self->hm_linear.hm_alloc;
	while (result && self->hm_linear.hm_vector[result - 1].h_type == HANDLE_TYPE_UNDEFINED)
		--result;
	return result;
}

PRIVATE NOBLOCK ATTR_NOINLINE ATTR_PURE WUNUSED NONNULL((1)) unsigned int
NOTHROW(FCALL handle_manager_get_max_hashvector_fd_plus_one)(struct handle_manager const *__restrict self) {
	unsigned int result = 0;
	unsigned int i, mask;
	struct handle_hashent *map;
	map  = self->hm_hashvector.hm_hashvec;
	mask = self->hm_hashvector.hm_hashmsk;
	for (i = 0; i <= mask; ++i) {
		unsigned int fdno;
		if (map[i].hh_handle_id == HANDLE_HASHENT_SENTINEL_ID)
			continue;
		fdno = map[i].hh_vector_index;
		if (fdno != (unsigned int)-1) {
			if (result <= fdno)
				result = fdno + 1;
		}
	}
	return result;
}

PRIVATE WUNUSED NONNULL((1)) unsigned int KCALL
find_greatest_inuse_fd_plus_one(struct handle_manager *__restrict self) {
	unsigned int result;
	handle_manager_read(self);
	if (self->hm_mode == HANDLE_MANAGER_MODE_LINEAR) {
		result = handle_manager_get_max_linear_fd_plus_one(self);
	} else {
		result = handle_manager_get_max_hashvector_fd_plus_one(self);
	}
	handle_manager_endread(self);
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
		ATOMIC_WRITE(me->pfe_fd, newpos);
		break;

	case SEEK_CUR: {
		uintptr_t oldpos;
		do {
			oldpos = ATOMIC_READ(me->pfe_fd);
			newpos = oldpos + (int)offset;
			if unlikely(offset < 0 ? newpos > oldpos
			                       : newpos < oldpos)
				THROW(E_OVERFLOW);
		} while (!ATOMIC_CMPXCH_WEAK(me->pfe_fd, oldpos, newpos));
	}	break;

	case SEEK_END: {
		unsigned int dirsiz;
		dirsiz = find_greatest_inuse_fd_plus_one(me->pfe_hman);
		newpos = dirsiz + (int)offset;
		if unlikely(offset < 0 ? newpos > dirsiz
		                       : newpos < dirsiz)
			THROW(E_OVERFLOW);
		ATOMIC_WRITE(me->pfe_fd, newpos);
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

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_fd_v_enum(struct fdirenum *__restrict result) {
	REF struct task *thread;
	struct taskpid *pid = result->de_dir->fn_fsdata;
	struct procfs_fd_enum *rt;
	thread = taskpid_gettask(pid);
	if unlikely(!thread) {
		struct constdirenum *ret = (struct constdirenum *)result;
		/* Thread has already terminated. -> Set-up an empty directory */
		ret->de_ops    = &constdirenum_ops;
		ret->cde_index = 0;
		ret->cde_entc  = 0;
		ret->cde_entv  = NULL;
		return;
	}
	rt = (struct procfs_fd_enum *)result;
	rt->pfe_hman = task_gethandlemanager(thread);
	decref_unlikely(thread);
	rt->de_ops = &procfs_fd_enum_ops;
	rt->pfe_fd = 0;
}

INTERN_CONST struct fdirnode_ops const procfs_pp_fd = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_dir_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
	},
	.dno_lookup = &procfs_perproc_fd_v_lookup,
	.dno_enum   = &procfs_perproc_fd_v_enum,
};



/************************************************************************/
/* /proc/[pid]/map_files                                                */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_map_files_v_lookup(struct fdirnode *__restrict self,
                                  struct flookup_info *__restrict info) {
	struct taskpid *pid = self->fn_fsdata;

	/* TODO */
	(void)pid;
	(void)info;
	COMPILER_IMPURE();

	return NULL;
}

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_map_files_v_enum(struct fdirenum *__restrict result) {
	struct taskpid *pid = result->de_dir->fn_fsdata;

	/* TODO */
	(void)pid;
	COMPILER_IMPURE();

	struct constdirenum *ret = (struct constdirenum *)result;
	/* Fill in enumerator info */
	ret->de_ops    = &constdirenum_ops;
	ret->cde_index = 0;
	ret->cde_entc  = 0;
	ret->cde_entv  = NULL;
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
	},
	.dno_lookup = &procfs_perproc_map_files_v_lookup,
	.dno_enum   = &procfs_perproc_map_files_v_enum,
};



/************************************************************************/
/* /proc/[pid]/task                                                     */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_task_v_lookup(struct fdirnode *__restrict self,
                             struct flookup_info *__restrict info) {
	struct taskpid *pid = self->fn_fsdata;

	/* TODO */
	(void)pid;
	(void)info;
	COMPILER_IMPURE();

	return NULL;
}

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_task_v_enum(struct fdirenum *__restrict result) {
	struct taskpid *pid = result->de_dir->fn_fsdata;

	/* TODO */
	(void)pid;
	COMPILER_IMPURE();

	struct constdirenum *ret = (struct constdirenum *)result;
	/* Fill in enumerator info */
	ret->de_ops    = &constdirenum_ops;
	ret->cde_index = 0;
	ret->cde_entc  = 0;
	ret->cde_entv  = NULL;
}

INTERN_CONST struct fdirnode_ops const procfs_pp_task = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_dir_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
	},
	.dno_lookup = &procfs_perproc_task_v_lookup,
	.dno_enum   = &procfs_perproc_task_v_enum,
};



/************************************************************************/
/* /proc/[pid]/kos/dcwd                                                 */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_kos_dcwd_v_lookup(struct fdirnode *__restrict self,
                                 struct flookup_info *__restrict info) {
	struct taskpid *pid = self->fn_fsdata;

	/* TODO */
	(void)pid;
	(void)info;
	COMPILER_IMPURE();

	return NULL;
}

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_kos_dcwd_v_enum(struct fdirenum *__restrict result) {
	struct taskpid *pid = result->de_dir->fn_fsdata;

	/* TODO */
	(void)pid;
	COMPILER_IMPURE();

	struct constdirenum *ret = (struct constdirenum *)result;
	/* Fill in enumerator info */
	ret->de_ops    = &constdirenum_ops;
	ret->cde_index = 0;
	ret->cde_entc  = 0;
	ret->cde_entv  = NULL;
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
	},
	.dno_lookup = &procfs_perproc_kos_dcwd_v_lookup,
	.dno_enum   = &procfs_perproc_kos_dcwd_v_enum,
};



/************************************************************************/
/* /proc/[pid]/kos/drives                                               */
/************************************************************************/
PRIVATE WUNUSED NONNULL((1, 2)) REF struct fdirent *KCALL
procfs_perproc_kos_drives_v_lookup(struct fdirnode *__restrict self,
                                   struct flookup_info *__restrict info) {
	struct taskpid *pid = self->fn_fsdata;

	/* TODO */
	(void)pid;
	(void)info;
	COMPILER_IMPURE();

	return NULL;
}

PRIVATE NONNULL((1)) void KCALL
procfs_perproc_kos_drives_v_enum(struct fdirenum *__restrict result) {
	struct taskpid *pid = result->de_dir->fn_fsdata;

	/* TODO */
	(void)pid;
	COMPILER_IMPURE();

	struct constdirenum *ret = (struct constdirenum *)result;
	/* Fill in enumerator info */
	ret->de_ops    = &constdirenum_ops;
	ret->cde_index = 0;
	ret->cde_entc  = 0;
	ret->cde_entv  = NULL;
}

INTERN_CONST struct fdirnode_ops const procfs_pp_kos_drives = {
	.dno_node = {
		.no_file = {
			.mo_destroy = &procfs_perproc_dir_v_destroy,
			.mo_changed = &procfs_perproc_dir_v_changed,
			.mo_stream  = &procfs_perproc_dir_v_stream_ops,
		},
		.no_free   = &procfs_perproc_dir_v_free,
		.no_wrattr = &procfs_perproc_dir_v_wrattr,
	},
	.dno_lookup = &procfs_perproc_kos_drives_v_lookup,
	.dno_enum   = &procfs_perproc_kos_drives_v_enum,
};




DECL_END

#endif /* !GUARD_MODPROCFS_FILES_PERPROC_C */
