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
#ifndef GUARD_KERNEL_CORE_FILESYS_SYSCALLS_C
#define GUARD_KERNEL_CORE_FILESYS_SYSCALLS_C 1
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/execabi.h>
#include <kernel/fs/allnodes.h>
#include <kernel/fs/devfs.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/dirhandle.h>
#include <kernel/fs/dirnode.h>
#include <kernel/fs/fifohandle.h>
#include <kernel/fs/filehandle.h>
#include <kernel/fs/filesys.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/ramfs.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/malloc.h>
#include <kernel/mman.h>
#include <kernel/mman/event.h>
#include <kernel/mman/exec.h>
#include <kernel/mman/execinfo.h>
#include <kernel/personality.h>
#include <kernel/printk.h>
#include <kernel/rt/except-syscall.h> /* CONFIG_HAVE_USERPROCMASK */
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/comm.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/rpc.h>
#include <sched/sigmask.h>
#include <sched/task.h>
#include <sched/tsc.h>

#include <hybrid/atomic.h>

#include <bits/os/statfs-convert.h>
#include <compat/config.h>
#include <kos/compat/linux-stat-convert.h>
#include <kos/compat/linux-stat.h>
#include <kos/except.h>
#include <kos/except/reason/fs.h>
#include <kos/except/reason/inval.h>
#include <kos/io.h>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <format-printer.h>
#include <malloca.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>
#include <utime.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/statfs-convert.h>
#include <compat/bits/os/statfs.h>
#include <compat/bits/os/timespec.h>
#include <compat/bits/os/timeval.h>
#include <compat/bits/os/utimbuf.h>
#include <compat/kos/compat/linux-stat-convert.h>
#include <compat/kos/compat/linux-stat.h>
#include <compat/pointer.h>
#endif /* __ARCH_HAVE_COMPAT */

#ifdef __ARCH_HAVE_COMPAT
#define IF_ARCH_HAVE_COMPAT(...) __VA_ARGS__
#else /* __ARCH_HAVE_COMPAT */
#define IF_ARCH_HAVE_COMPAT(...) /* nothing */
#endif /* !__ARCH_HAVE_COMPAT */

DECL_BEGIN

#if !defined(NDEBUG) && !defined(NDEBUG_FINI)
#define DBG_memset memset
#else /* !NDEBUG && !NDEBUG_FINI */
#define DBG_memset(...) (void)0
#endif /* NDEBUG || NDEBUG_FINI */

/************************************************************************/
/* Assert validity of IO_*, O_*, and FD_* macros, and their converters  */
/************************************************************************/

static_assert(IO_HANDLE_FFROM_FD(0) == 0);
static_assert(IO_HANDLE_FFROM_FD(FD_CLOEXEC) == IO_CLOEXEC);
static_assert(IO_HANDLE_FFROM_FD(FD_CLOFORK) == IO_CLOFORK);
static_assert(IO_HANDLE_FFROM_FD(FD_CLOEXEC | FD_CLOFORK) == (IO_CLOEXEC | IO_CLOFORK));
/* `IO_HANDLE_FFROM_FD()' doesn't need to behave when given invalid flags.
 * The caller of  `IO_HANDLE_FFROM_FD()' should have  already checked  the
 * user-given flags for validity! */

static_assert(IO_HANDLE_FTO_FD(0) == 0);
static_assert(IO_HANDLE_FTO_FD(IO_CLOEXEC) == FD_CLOEXEC);
static_assert(IO_HANDLE_FTO_FD(IO_CLOFORK) == FD_CLOFORK);
static_assert(IO_HANDLE_FTO_FD(IO_CLOEXEC | IO_CLOFORK) == (FD_CLOEXEC | FD_CLOFORK));
static_assert(IO_HANDLE_FTO_FD((-1 & ~(IO_CLOEXEC | IO_CLOFORK)) | 0) == 0);
static_assert(IO_HANDLE_FTO_FD((-1 & ~(IO_CLOEXEC | IO_CLOFORK)) | IO_CLOEXEC) == FD_CLOEXEC);
static_assert(IO_HANDLE_FTO_FD((-1 & ~(IO_CLOEXEC | IO_CLOFORK)) | IO_CLOFORK) == FD_CLOFORK);
static_assert(IO_HANDLE_FTO_FD((-1 & ~(IO_CLOEXEC | IO_CLOFORK)) | IO_CLOEXEC | IO_CLOFORK) == (FD_CLOEXEC | FD_CLOFORK));

static_assert(IO_TO_OPENFLAG(0) == 0);
static_assert(IO_TO_OPENFLAG(IO_CLOFORK) == O_CLOFORK);
static_assert(IO_TO_OPENFLAG(IO_CLOEXEC) == O_CLOEXEC);
static_assert(IO_TO_OPENFLAG(IO_CLOFORK | IO_CLOEXEC) == (O_CLOFORK | O_CLOEXEC));
static_assert(IO_TO_OPENFLAG(IO_ACCMODE) == O_ACCMODE);
static_assert(IO_TO_OPENFLAG(IO_RDONLY) == O_RDONLY);
static_assert(IO_TO_OPENFLAG(IO_WRONLY) == O_WRONLY);
static_assert(IO_TO_OPENFLAG(IO_RDWR) == O_RDWR);
static_assert(IO_TO_OPENFLAG(IO_APPEND) == O_APPEND);
static_assert(IO_TO_OPENFLAG(IO_NONBLOCK) == O_NONBLOCK);
static_assert(IO_TO_OPENFLAG(IO_DSYNC) == O_DSYNC);
static_assert(IO_TO_OPENFLAG(IO_ASYNC) == O_ASYNC);
static_assert(IO_TO_OPENFLAG(IO_DIRECT) == O_DIRECT);

static_assert(IO_TO_OPENFLAG_NOHANDLE(0) == 0);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_CLOFORK) == 0);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_CLOEXEC) == 0);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_CLOFORK | IO_CLOEXEC) == 0);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_ACCMODE) == O_ACCMODE);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_RDONLY) == O_RDONLY);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_WRONLY) == O_WRONLY);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_RDWR) == O_RDWR);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_APPEND) == O_APPEND);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_NONBLOCK) == O_NONBLOCK);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_DSYNC) == O_DSYNC);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_ASYNC) == O_ASYNC);
static_assert(IO_TO_OPENFLAG_NOHANDLE(IO_DIRECT) == O_DIRECT);

static_assert(IO_FROM_OPENFLAG(0) == 0);
static_assert(IO_FROM_OPENFLAG(O_CLOFORK) == IO_CLOFORK);
static_assert(IO_FROM_OPENFLAG(O_CLOEXEC) == IO_CLOEXEC);
static_assert(IO_FROM_OPENFLAG(O_CLOFORK | O_CLOEXEC) == (IO_CLOFORK | IO_CLOEXEC));
static_assert(IO_FROM_OPENFLAG(O_EXCL) == 0);
static_assert(IO_FROM_OPENFLAG(O_NOCTTY) == 0);
static_assert(IO_FROM_OPENFLAG(O_ACCMODE) == IO_ACCMODE);
static_assert(IO_FROM_OPENFLAG(O_RDONLY) == IO_RDONLY);
static_assert(IO_FROM_OPENFLAG(O_WRONLY) == IO_WRONLY);
static_assert(IO_FROM_OPENFLAG(O_RDWR) == IO_RDWR);
static_assert(IO_FROM_OPENFLAG(O_APPEND) == IO_APPEND);
static_assert(IO_FROM_OPENFLAG(O_NONBLOCK) == IO_NONBLOCK);
static_assert(IO_FROM_OPENFLAG(O_DSYNC) == IO_DSYNC);
static_assert(IO_FROM_OPENFLAG(O_ASYNC) == IO_ASYNC);
static_assert(IO_FROM_OPENFLAG(O_DIRECT) == IO_DIRECT);

static_assert(IO_FROM_OPENFLAG_NOHANDLE(0) == 0);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_CLOFORK) == 0);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_CLOEXEC) == 0);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_CLOFORK | O_CLOEXEC) == 0);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_EXCL) == 0);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_NOCTTY) == 0);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_ACCMODE) == IO_ACCMODE);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_RDONLY) == IO_RDONLY);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_WRONLY) == IO_WRONLY);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_RDWR) == IO_RDWR);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_APPEND) == IO_APPEND);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_NONBLOCK) == IO_NONBLOCK);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_DSYNC) == IO_DSYNC);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_ASYNC) == IO_ASYNC);
static_assert(IO_FROM_OPENFLAG_NOHANDLE(O_DIRECT) == IO_DIRECT);

static_assert(IO_HANDLE_FTO_OPENFLAG(0) == 0);
static_assert(IO_HANDLE_FTO_OPENFLAG(IO_CLOEXEC) == O_CLOEXEC);
static_assert(IO_HANDLE_FTO_OPENFLAG(IO_CLOFORK) == O_CLOFORK);
static_assert(IO_HANDLE_FTO_OPENFLAG(IO_CLOEXEC | IO_CLOFORK) == (O_CLOEXEC | O_CLOFORK));
static_assert(IO_HANDLE_FTO_OPENFLAG((-1 & ~(IO_CLOEXEC | IO_CLOFORK)) | 0) == 0);
static_assert(IO_HANDLE_FTO_OPENFLAG((-1 & ~(IO_CLOEXEC | IO_CLOFORK)) | IO_CLOEXEC) == O_CLOEXEC);
static_assert(IO_HANDLE_FTO_OPENFLAG((-1 & ~(IO_CLOEXEC | IO_CLOFORK)) | IO_CLOFORK) == O_CLOFORK);
static_assert(IO_HANDLE_FTO_OPENFLAG((-1 & ~(IO_CLOEXEC | IO_CLOFORK)) | IO_CLOEXEC | IO_CLOFORK) == (O_CLOEXEC | O_CLOFORK));

static_assert(IO_HANDLE_FFROM_OPENFLAG(0) == 0);
static_assert(IO_HANDLE_FFROM_OPENFLAG(O_CLOEXEC) == IO_CLOEXEC);
static_assert(IO_HANDLE_FFROM_OPENFLAG(O_CLOFORK) == IO_CLOFORK);
static_assert(IO_HANDLE_FFROM_OPENFLAG(O_CLOEXEC | O_CLOFORK) == (IO_CLOEXEC | IO_CLOFORK));
static_assert(IO_HANDLE_FFROM_OPENFLAG((-1 & ~(O_CLOEXEC | O_CLOFORK)) | 0) == 0);
static_assert(IO_HANDLE_FFROM_OPENFLAG((-1 & ~(O_CLOEXEC | O_CLOFORK)) | O_CLOEXEC) == IO_CLOEXEC);
static_assert(IO_HANDLE_FFROM_OPENFLAG((-1 & ~(O_CLOEXEC | O_CLOFORK)) | O_CLOFORK) == IO_CLOFORK);
static_assert(IO_HANDLE_FFROM_OPENFLAG((-1 & ~(O_CLOEXEC | O_CLOFORK)) | O_CLOEXEC | O_CLOFORK) == (IO_CLOEXEC | IO_CLOFORK));



/************************************************************************/
/* faccessat2(), faccessat(), access()                                  */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FACCESSAT) || defined(__ARCH_WANT_SYSCALL_ACCESS))
PRIVATE errno_t KCALL
sys_faccessat_impl(fd_t dirfd, USER UNCHECKED char const *filename,
                   syscall_ulong_t type, atflag_t atflags) {
	REF struct fnode *node;
	VALIDATE_FLAGSET(type, F_OK | R_OK | W_OK | X_OK,
	                 E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_TYPE);
	VALIDATE_FLAGSET(atflags, AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_FLAGS);
	atflags = fs_atflags(atflags);
	node    = path_traversefull(dirfd, filename, atflags);
	FINALLY_DECREF_UNLIKELY(node);
	/* TODO: AT_EACCESS */
	fnode_access(node, type);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FACCESSAT || __ARCH_WANT_SYSCALL_ACCESS */

#ifdef __ARCH_WANT_SYSCALL_FACCESSAT2
DEFINE_SYSCALL4(errno_t, faccessat2,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                syscall_ulong_t, type, atflag_t, atflags) {
	return sys_faccessat_impl(dirfd, filename, type, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FACCESSAT2 */

#ifdef __ARCH_WANT_SYSCALL_FACCESSAT
DEFINE_SYSCALL3(errno_t, faccessat,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                syscall_ulong_t, type) {
	return sys_faccessat_impl(dirfd, filename, type, 0);
}
#endif /* __ARCH_WANT_SYSCALL_FACCESSAT */

#ifdef __ARCH_WANT_SYSCALL_ACCESS
DEFINE_SYSCALL2(errno_t, access,
                USER UNCHECKED char const *, filename,
                syscall_ulong_t, type) {
	return sys_faccessat_impl(AT_FDCWD, filename, type, 0);
}
#endif /* __ARCH_WANT_SYSCALL_ACCESS */





/************************************************************************/
/* getcwd()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETCWD
DEFINE_SYSCALL2(ssize_t, getcwd,
                USER UNCHECKED char *, buf, size_t, bufsize) {
	struct fs *myfs = THIS_FS;
	REF struct path *cwd, *root;
	atflag_t atflags;
	size_t result;
	validate_writable(buf, bufsize);
	fs_pathlock_read(myfs);
	cwd  = incref(myfs->fs_cwd);
	root = incref(myfs->fs_root);
	fs_pathlock_endread(myfs);
	atflags = ATOMIC_READ(myfs->fs_mode.f_atflag) & AT_DOSPATH;
	{
		FINALLY_DECREF_UNLIKELY(cwd);
		FINALLY_DECREF_UNLIKELY(root);
		result = path_sprint(cwd, buf, bufsize, atflags, root);
	}
	if unlikely(result > bufsize) /* return -ERANGE; */
		THROW(E_BUFFER_TOO_SMALL, result, bufsize);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_GETCWD */





/************************************************************************/
/* fmknodat(), mknodat(), mknod()                                       */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FMKNODAT) || \
     defined(__ARCH_WANT_SYSCALL_MKNODAT) ||  \
     defined(__ARCH_WANT_SYSCALL_MKNOD))
PRIVATE errno_t KCALL
sys_fmknodat_impl(fd_t dirfd, USER UNCHECKED char const *nodename,
                  mode_t mode, dev_t dev, atflag_t atflags) {
	struct fmkfile_info mkinfo;
	REF struct path *nodename_path;
	unsigned int status;
	VALIDATE_FLAGSET(atflags, 0 | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FMKNODAT_FLAGS);
	validate_readable(nodename, 1);
	atflags = fs_atflags(atflags);
	mode &= ~ATOMIC_READ(THIS_FS->fs_umask);
	VALIDATE_FLAGSET(mode, 07777 | S_IFMT,
	                 E_INVALID_ARGUMENT_CONTEXT_MKNOD_MODE);
	/* sys_mknod() can only be used to create files of the following types. */
	if ((mode & S_IFMT) != S_IFREG && (mode & S_IFMT) != S_IFCHR &&
	    (mode & S_IFMT) != S_IFBLK && (mode & S_IFMT) != S_IFIFO) {
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_MASK,
		      E_INVALID_ARGUMENT_CONTEXT_MKNOD_MODE,
		      mode,
		      S_IFMT);
	}
	nodename_path = path_traverse_r(dirfd, nodename, &mkinfo.mkf_name,
	                                &mkinfo.mkf_namelen, atflags);
	{
		FINALLY_DECREF_UNLIKELY(nodename_path);
		fnode_access(nodename_path->p_dir, W_OK);
		mkinfo.mkf_flags         = atflags;
		mkinfo.mkf_hash          = FLOOKUP_INFO_HASH_UNSET;
		mkinfo.mkf_fmode         = mode;
		mkinfo.mkf_creat.c_owner = cred_getfsuid();
		mkinfo.mkf_creat.c_group = cred_getfsgid();
		mkinfo.mkf_creat.c_atime = realtime();
		mkinfo.mkf_creat.c_mtime = mkinfo.mkf_creat.c_atime;
		mkinfo.mkf_creat.c_ctime = mkinfo.mkf_creat.c_atime;
		mkinfo.mkf_creat.c_btime = mkinfo.mkf_creat.c_atime;
		mkinfo.mkf_creat.c_rdev  = dev;
		/* Create the new file. */
		status = fdirnode_mkfile(nodename_path->p_dir, &mkinfo);
	}
	decref_unlikely(mkinfo.mkf_rnode);
	decref_unlikely(mkinfo.mkf_dent);
	if (status == FDIRNODE_MKFILE_EXISTS)
		THROW(E_FSERROR_FILE_ALREADY_EXISTS);
	return -EOK;
}
#endif /* mknod... */
#ifdef __ARCH_WANT_SYSCALL_FMKNODAT
DEFINE_SYSCALL5(errno_t, fmknodat, fd_t, dirfd,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, __dev_t, dev, atflag_t, atflags) {
	return sys_fmknodat_impl(dirfd, nodename, mode, (dev_t)dev, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FMKNODAT */

#ifdef __ARCH_WANT_SYSCALL_MKNODAT
DEFINE_SYSCALL4(errno_t, mknodat, fd_t, dirfd,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, __dev_t, dev) {
	return sys_fmknodat_impl(dirfd, nodename, mode, (dev_t)dev, 0);
}
#endif /* __ARCH_WANT_SYSCALL_MKNODAT */

#ifdef __ARCH_WANT_SYSCALL_MKNOD
DEFINE_SYSCALL3(errno_t, mknod,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, __dev_t, dev) {
	return sys_fmknodat_impl(AT_FDCWD, nodename, mode, (dev_t)dev, 0);
}
#endif /* __ARCH_WANT_SYSCALL_MKNOD */





/************************************************************************/
/* fmkdirat(), mkdirat(), mkdir()                                       */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FMKDIRAT) || \
     defined(__ARCH_WANT_SYSCALL_MKDIRAT) ||  \
     defined(__ARCH_WANT_SYSCALL_MKDIR))
PRIVATE errno_t KCALL
sys_fmkdirat_impl(fd_t dirfd, USER UNCHECKED char const *pathname,
                  mode_t mode, atflag_t atflags) {
	struct fmkfile_info mkinfo;
	REF struct path *pathname_path;
	unsigned int status;
	VALIDATE_FLAGSET(atflags, 0 | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FMKDIRAT_FLAGS);
	validate_readable(pathname, 1);
	atflags = fs_atflags(atflags);
	if (has_personality(KP_MKDIR_CHECK_MODE))
		VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE);
	mode &= 07777 & ~ATOMIC_READ(THIS_FS->fs_umask);
	pathname_path = path_traverse_r(dirfd, pathname, &mkinfo.mkf_name,
	                                &mkinfo.mkf_namelen,
	                                atflags | AT_IGNORE_TRAILING_SLASHES);
	{
		FINALLY_DECREF_UNLIKELY(pathname_path);
		fnode_access(pathname_path->p_dir, W_OK);
		mkinfo.mkf_flags         = atflags;
		mkinfo.mkf_hash          = FLOOKUP_INFO_HASH_UNSET;
		mkinfo.mkf_fmode         = S_IFDIR | mode;
		mkinfo.mkf_creat.c_owner = cred_getfsuid();
		mkinfo.mkf_creat.c_group = cred_getfsgid();
		mkinfo.mkf_creat.c_atime = realtime();
		mkinfo.mkf_creat.c_mtime = mkinfo.mkf_creat.c_atime;
		mkinfo.mkf_creat.c_ctime = mkinfo.mkf_creat.c_atime;
		mkinfo.mkf_creat.c_btime = mkinfo.mkf_creat.c_atime;
		/* Create the new file. */
		status = fdirnode_mkfile(pathname_path->p_dir, &mkinfo);
	}
	decref_unlikely(mkinfo.mkf_rnode);
	decref_unlikely(mkinfo.mkf_dent);
	if (status == FDIRNODE_MKFILE_EXISTS)
		THROW(E_FSERROR_FILE_ALREADY_EXISTS);
	return -EOK;
}
#endif /* mkdir... */
#ifdef __ARCH_WANT_SYSCALL_FMKDIRAT
DEFINE_SYSCALL4(errno_t, fmkdirat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname, mode_t, mode,
                atflag_t, atflags) {
	return sys_fmkdirat_impl(dirfd, pathname, mode, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FMKDIRAT */

#ifdef __ARCH_WANT_SYSCALL_MKDIRAT
DEFINE_SYSCALL3(errno_t, mkdirat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname, mode_t, mode) {
	return sys_fmkdirat_impl(dirfd, pathname, mode, 0);
}
#endif /* __ARCH_WANT_SYSCALL_MKDIRAT */

#ifdef __ARCH_WANT_SYSCALL_MKDIR
DEFINE_SYSCALL2(errno_t, mkdir,
                USER UNCHECKED char const *, pathname, mode_t, mode) {
	return sys_fmkdirat_impl(AT_FDCWD, pathname, mode, 0);
}
#endif /* __ARCH_WANT_SYSCALL_MKDIR */





/************************************************************************/
/* unlinkat(), unlink(), rmdir()                                        */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_UNLINKAT) || \
     defined(__ARCH_WANT_SYSCALL_UNLINK) ||   \
     defined(__ARCH_WANT_SYSCALL_RMDIR))
PRIVATE errno_t KCALL
sys_unlinkat_impl(fd_t dirfd, USER UNCHECKED char const *pathname,
                  atflag_t atflags) {
	USER UNCHECKED char const *laststr;
	u16 lastlen;
	REF struct path *pathname_path;
	VALIDATE_FLAGSET(atflags,
	                 AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_UNLINKAT_FLAGS);
	validate_readable(pathname, 1);
	atflags = fs_atflags(atflags);
	if ((atflags & (AT_REMOVEDIR | AT_REMOVEREG)) == AT_REMOVEDIR)
		atflags |= AT_IGNORE_TRAILING_SLASHES; /* When only removing directories, ignore trailing slashes */
	pathname_path = path_traverse_r(dirfd, pathname, &laststr, &lastlen, atflags);
	FINALLY_DECREF_UNLIKELY(pathname_path);
	/* Check permissions because `path_remove()' won't do so for us! */
	fnode_access(pathname_path->p_dir, W_OK);
	path_remove(pathname_path, laststr, lastlen, atflags);
	return -EOK;
}
#endif /* unlink / rmdir */

#ifdef __ARCH_WANT_SYSCALL_UNLINKAT
DEFINE_SYSCALL3(errno_t, unlinkat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname,
                atflag_t, atflags) {
	if ((atflags & (AT_REMOVEDIR | AT_REMOVEREG)) == 0)
		atflags |= AT_REMOVEREG; /* When neither flag is given, remove regular files */
	return sys_unlinkat_impl(dirfd, pathname, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_UNLINKAT */

#ifdef __ARCH_WANT_SYSCALL_UNLINK
DEFINE_SYSCALL1(errno_t, unlink, USER UNCHECKED char const *, pathname) {
	return sys_unlinkat_impl(AT_FDCWD, pathname, AT_REMOVEREG);
}
#endif /* __ARCH_WANT_SYSCALL_UNLINK */

#ifdef __ARCH_WANT_SYSCALL_RMDIR
DEFINE_SYSCALL1(errno_t, rmdir, USER UNCHECKED char const *, pathname) {
	return sys_unlinkat_impl(AT_FDCWD, pathname, AT_REMOVEDIR);
}
#endif /* __ARCH_WANT_SYSCALL_RMDIR */





/************************************************************************/
/* fsymlinkat(), symlinkat(), symlink()                                 */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FSYMLINKAT) || \
     defined(__ARCH_WANT_SYSCALL_SYMLINKAT) ||  \
     defined(__ARCH_WANT_SYSCALL_SYMLINK))
PRIVATE errno_t KCALL
sys_fsymlinkat_impl(USER UNCHECKED char const *link_text, fd_t target_dirfd,
                    USER UNCHECKED char const *target_path, atflag_t atflags) {
	struct fmkfile_info mkinfo;
	REF struct path *pathname_path;
	unsigned int status;
	VALIDATE_FLAGSET(atflags, 0 | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FSYMLINKAT_FLAGS);
	validate_readable(link_text, 1);
	validate_readable(target_path, 1);
	atflags       = fs_atflags(atflags);
	pathname_path = path_traverse_r(target_dirfd, target_path, &mkinfo.mkf_name,
	                                &mkinfo.mkf_namelen, atflags);
	{
		FINALLY_DECREF_UNLIKELY(pathname_path);
		fnode_access(pathname_path->p_dir, W_OK);
		mkinfo.mkf_flags         = atflags;
		mkinfo.mkf_hash          = FLOOKUP_INFO_HASH_UNSET;
		mkinfo.mkf_fmode         = S_IFLNK | (07777 & ~ATOMIC_READ(THIS_FS->fs_umask));
		mkinfo.mkf_creat.c_owner = cred_getfsuid();
		mkinfo.mkf_creat.c_group = cred_getfsgid();
		mkinfo.mkf_creat.c_atime = realtime();
		mkinfo.mkf_creat.c_mtime = mkinfo.mkf_creat.c_atime;
		mkinfo.mkf_creat.c_ctime = mkinfo.mkf_creat.c_atime;
		mkinfo.mkf_creat.c_btime = mkinfo.mkf_creat.c_atime;
		mkinfo.mkf_creat.c_symlink.s_text = link_text;
		mkinfo.mkf_creat.c_symlink.s_size = strlen(link_text);
		/* Create the new file. */
		status = fdirnode_mkfile(pathname_path->p_dir, &mkinfo);
	}
	decref_unlikely(mkinfo.mkf_rnode);
	decref_unlikely(mkinfo.mkf_dent);
	if (status == FDIRNODE_MKFILE_EXISTS)
		THROW(E_FSERROR_FILE_ALREADY_EXISTS);
	return -EOK;
}
#endif /* symlink */

#ifdef __ARCH_WANT_SYSCALL_FSYMLINKAT
DEFINE_SYSCALL4(errno_t, fsymlinkat,
                USER UNCHECKED char const *, link_text, fd_t, target_dirfd,
                USER UNCHECKED char const *, target_path, atflag_t, atflags) {
	return sys_fsymlinkat_impl(link_text, target_dirfd, target_path, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FSYMLINKAT */

#ifdef __ARCH_WANT_SYSCALL_SYMLINKAT
DEFINE_SYSCALL3(errno_t, symlinkat,
                USER UNCHECKED char const *, link_text, fd_t, target_dirfd,
                USER UNCHECKED char const *, target_path) {
	return sys_fsymlinkat_impl(link_text, target_dirfd, target_path, 0);
}
#endif /* __ARCH_WANT_SYSCALL_SYMLINKAT */

#ifdef __ARCH_WANT_SYSCALL_SYMLINK
DEFINE_SYSCALL2(errno_t, symlink,
                USER UNCHECKED char const *, link_text,
                USER UNCHECKED char const *, target_path) {
	return sys_fsymlinkat_impl(link_text, AT_FDCWD, target_path, 0);
}
#endif /* __ARCH_WANT_SYSCALL_SYMLINK */





/************************************************************************/
/* linkat(), link()                                                     */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_LINKAT) || \
     defined(__ARCH_WANT_SYSCALL_LINK))
PRIVATE errno_t KCALL
sys_linkat_impl(fd_t olddirfd, USER UNCHECKED char const *oldpath,
                fd_t newdirfd, USER UNCHECKED char const *newpath,
                atflag_t atflags) {
	struct fmkfile_info mkinfo;
	REF struct path *pathname_path;
	unsigned int status;
	VALIDATE_FLAGSET(atflags, 0 | AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FSYMLINKAT_FLAGS);
	validate_readable(oldpath, 1);
	validate_readable(newpath, 1);
	atflags       = fs_atflags(atflags);
	pathname_path = path_traverse_r(newdirfd, newpath, &mkinfo.mkf_name,
	                                &mkinfo.mkf_namelen, atflags);
	{
		FINALLY_DECREF_UNLIKELY(pathname_path);
		fnode_access(pathname_path->p_dir, W_OK);
		mkinfo.mkf_flags = atflags;
		mkinfo.mkf_hash  = FLOOKUP_INFO_HASH_UNSET;
		mkinfo.mkf_fmode = 0;
		if ((mkinfo.mkf_flags & AT_EMPTY_PATH) && !*oldpath) {
			require(CAP_DAC_READ_SEARCH); /* Linux says the caller needs this perm... */
			mkinfo.mkf_hrdlnk.hl_node = handles_lookupfnode(olddirfd);
		} else {
			mkinfo.mkf_flags |= AT_SYMLINK_NOFOLLOW;
			if (mkinfo.mkf_flags & AT_SYMLINK_FOLLOW)
				mkinfo.mkf_flags &= ~AT_SYMLINK_NOFOLLOW;
			mkinfo.mkf_hrdlnk.hl_node = path_traversefull(olddirfd, oldpath, mkinfo.mkf_flags);
		}
		FINALLY_DECREF_UNLIKELY(mkinfo.mkf_hrdlnk.hl_node);
		if (fnode_isdir(mkinfo.mkf_hrdlnk.hl_node))
			THROW(E_FSERROR_IS_A_DIRECTORY, E_FILESYSTEM_IS_A_DIRECTORY_LINK);
		if (mkinfo.mkf_hrdlnk.hl_node->fn_super != path_getsuper(pathname_path))
			THROW(E_FSERROR_CROSS_DEVICE_LINK);

		/* Create the new hard-link. */
		status = fdirnode_mkfile(pathname_path->p_dir, &mkinfo);
	}
	decref_unlikely(mkinfo.mkf_rnode);
	decref_unlikely(mkinfo.mkf_dent);
	if (status == FDIRNODE_MKFILE_EXISTS)
		THROW(E_FSERROR_FILE_ALREADY_EXISTS);
	return -EOK;
}
#endif /* link */

#ifdef __ARCH_WANT_SYSCALL_LINKAT
DEFINE_SYSCALL5(errno_t, linkat,
                fd_t, olddirfd, USER UNCHECKED char const *, oldpath,
                fd_t, newdirfd, USER UNCHECKED char const *, newpath,
                atflag_t, atflags) {
	return sys_linkat_impl(olddirfd, oldpath, newdirfd, newpath, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_LINKAT */

#ifdef __ARCH_WANT_SYSCALL_LINK
DEFINE_SYSCALL2(errno_t, link,
                USER UNCHECKED char const *, oldpath,
                USER UNCHECKED char const *, newpath) {
	return sys_linkat_impl(AT_FDCWD, oldpath, AT_FDCWD, newpath, 0);
}
#endif /* __ARCH_WANT_SYSCALL_LINK */





/************************************************************************/
/* renameat2(), renameat(), rename()                                    */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FRENAMEAT) || \
     defined(__ARCH_WANT_SYSCALL_RENAMEAT) ||  \
     defined(__ARCH_WANT_SYSCALL_RENAME))
PRIVATE errno_t KCALL
sys_renameat2_impl(fd_t olddirfd, USER UNCHECKED char const *oldpath,
                   fd_t newdirfd, USER UNCHECKED char const *newpath,
                   atflag_t atflags) {
	REF struct path *oldpathob, *newpathob;
	USER CHECKED char const *oldname, *newname;
	u16 oldnamelen, newnamelen;
	VALIDATE_FLAGSET(atflags,
	                 AT_DOSPATH | AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE |
	                 __RENAME_WHITEOUT | AT_RENAME_MOVETODIR,
	                 E_INVALID_ARGUMENT_CONTEXT_RENAMEAT2_FLAGS);
	if unlikely((atflags & (AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE)) == (AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE)) {
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_RENAMEAT2_FLAGS, atflags,
		      AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE,
		      AT_RENAME_NOREPLACE | AT_RENAME_EXCHANGE);
	}
	validate_readable(oldpath, 1);
	validate_readable(newpath, 1);
	atflags = fs_atflags(atflags) | AT_IGNORE_TRAILING_SLASHES;

	/* Lookup paths. */
	oldpathob = path_traverse_r(olddirfd, oldpath, &oldname, &oldnamelen, atflags);
	FINALLY_DECREF_UNLIKELY(oldpathob);

	/* FIXME: When `oldname' points to a directory (and `AT_RENAME_MOVETODIR' isn't given),
	 *        then we have to ignore trailing slashes. Currently, we always ignore slashes.
	 * s.a. `gl_cv_func_rename_slash_dst_works'
	 *
	 * Expected behavior (after `echo hi > /tmp/file; mkdir /tmp/dir`):
	 *
	 * >> rename("/tmp/dir",   "/tmp/dir-new")    --> 0;                   (KOS is compliant)
	 * >> rename("/tmp/dir",   "/tmp/dir-new/")   --> 0;                   (KOS is compliant)
	 * >> rename("/tmp/dir/",  "/tmp/dir-new")    --> 0;                   (KOS is compliant)
	 * >> rename("/tmp/dir/",  "/tmp/dir-new/")   --> 0;                   (KOS is compliant)
	 * >> rename("/tmp/file",  "/tmp/file-new")   --> 0;                   (KOS is compliant)
	 * >> rename("/tmp/file",  "/tmp/file-new/")  --> -1; errno=ENOTDIR    (KOS is non-compliant)
	 * >> rename("/tmp/file/", "/tmp/file-new")   --> -1; errno=ENOTDIR    (KOS is non-compliant)
	 * >> rename("/tmp/file/", "/tmp/file-new/")  --> -1; errno=ENOTDIR    (KOS is non-compliant)
	 */
	newpathob = path_traverse_r(newdirfd, newpath, &newname, &newnamelen, atflags);
	FINALLY_DECREF_UNLIKELY(newpathob);

	/* Do the rename. */
	path_rename(oldpathob, oldname, oldnamelen,
	            newpathob, newname, newnamelen, atflags);
	return -EOK;
}
#endif /* rename */

#ifdef __ARCH_WANT_SYSCALL_RENAMEAT2
DEFINE_SYSCALL5(errno_t, renameat2,
                fd_t, olddirfd, USER UNCHECKED char const *, oldpath,
                fd_t, newdirfd, USER UNCHECKED char const *, newpath,
                atflag_t, atflags) {
	return sys_renameat2_impl(olddirfd, oldpath, newdirfd, newpath, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_RENAMEAT2 */

#ifdef __ARCH_WANT_SYSCALL_RENAMEAT
DEFINE_SYSCALL4(errno_t, renameat,
                fd_t, olddirfd, USER UNCHECKED char const *, oldpath,
                fd_t, newdirfd, USER UNCHECKED char const *, newpath) {
	return sys_renameat2_impl(olddirfd, oldpath, newdirfd, newpath, 0);
}
#endif /* __ARCH_WANT_SYSCALL_RENAMEAT */

#ifdef __ARCH_WANT_SYSCALL_RENAME
DEFINE_SYSCALL2(errno_t, rename,
                USER UNCHECKED char const *, oldpath,
                USER UNCHECKED char const *, newpath) {
	return sys_renameat2_impl(AT_FDCWD, oldpath, AT_FDCWD, newpath, 0);
}
#endif /* __ARCH_WANT_SYSCALL_RENAME */





/************************************************************************/
/* umount2(), umount()                                                  */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_UMOUNT2) || \
     defined(__ARCH_WANT_SYSCALL_UMOUNT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UMOUNT))
PRIVATE errno_t KCALL
sys_umount2_impl(fd_t dirfd, USER UNCHECKED char const *target,
                 syscall_ulong_t flags) {
	atflag_t atflags;
	REF struct path *unmount_me;
	VALIDATE_FLAGSET(flags,
	                 MNT_FORCE | MNT_DETACH | MNT_EXPIRE | UMOUNT_NOFOLLOW,
	                 E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS);
	/* Flags:
	 *  - MNT_FORCE:       KOS always does forced unmounts.
	 *  - MNT_DETACH:      Fully supported.
	 *  - MNT_EXPIRE:      Unsupported
	 *  - UMOUNT_NOFOLLOW: Fully supported.
	 */
	atflags = 0;
	if (flags & UMOUNT_NOFOLLOW)
		atflags |= AT_SYMLINK_NOFOLLOW;
	validate_readable(target, 1);
	atflags    = fs_atflags(atflags) | AT_IGNORE_TRAILING_SLASHES;
	unmount_me = path_traverse_r(dirfd, target, NULL, NULL, atflags);
	FINALLY_DECREF_UNLIKELY(unmount_me);
	if (path_ismount(unmount_me)) {
		/* Require mounting rights. */
		require(CAP_MOUNT);

		/* Force a sync before doing the unmount. (Don't unload in inconsistent state) */
		fsuper_sync(path_getsuper(unmount_me));

		/* Do the unmount. */
		path_umount(path_asmount(unmount_me), flags);
	}
	return -EOK;
}
#endif /* umount */

#ifdef __ARCH_WANT_SYSCALL_UMOUNT2
DEFINE_SYSCALL2(errno_t, umount2,
                USER UNCHECKED char const *, target,
                syscall_ulong_t, flags) {
	return sys_umount2_impl(AT_FDCWD, target, flags);
}
#endif /* __ARCH_WANT_SYSCALL_UMOUNT2 */

#ifdef __ARCH_WANT_SYSCALL_UMOUNT
DEFINE_SYSCALL1(errno_t, umount,
                USER UNCHECKED char const *, special_file) {
	return sys_umount2_impl(AT_FDCWD, special_file, 0);
}
#endif /* __ARCH_WANT_SYSCALL_UMOUNT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_UMOUNT
DEFINE_COMPAT_SYSCALL1(errno_t, umount,
                       USER UNCHECKED char const *, special_file) {
	return sys_umount2_impl(AT_FDCWD, special_file, 0);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UMOUNT */





/************************************************************************/
/* mount()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MOUNT
PRIVATE void KCALL
super_set_mount_flags(struct fsuper *__restrict self,
                      syscall_ulong_t mountflags) {
	uintptr_t old_flags, new_flags;
	do {
		old_flags = ATOMIC_READ(self->fs_root.mf_flags);
		new_flags = old_flags & ~(MFILE_F_NOATIME | MFILE_FS_NOEXEC |
		                          MFILE_FS_NOSUID | MFILE_F_READONLY |
		                          MFILE_FN_NODIRATIME | MFILE_F_STRICTATIME |
		                          MFILE_F_LAZYTIME | MFILE_F_RELATIME);
		if (mountflags & MS_NOATIME)
			new_flags |= MFILE_F_NOATIME | MFILE_FN_NODIRATIME;
		if (mountflags & MS_NODIRATIME)
			new_flags |= MFILE_FN_NODIRATIME;
		if (mountflags & MS_STRICTATIME)
			new_flags |= MFILE_F_STRICTATIME;
		if (mountflags & MS_LAZYTIME)
			new_flags |= MFILE_F_LAZYTIME;
		if (mountflags & MS_NOEXEC)
			new_flags |= MFILE_FS_NOEXEC;
		if (mountflags & MS_NOSUID)
			new_flags |= MFILE_FS_NOSUID;
		if (mountflags & MS_RDONLY)
			new_flags |= MFILE_F_READONLY;
		if (mountflags & MS_RELATIME)
			new_flags |= MFILE_F_RELATIME;
		/* TODO: MS_MANDLOCK */
		/* TODO: MS_NODEV */
		/* TODO: MS_SYNCHRONOUS */
		/* TODO: MS_DIRSYNC */
	} while (!ATOMIC_CMPXCH_WEAK(self->fs_root.mf_flags,
	                             old_flags, new_flags));
}

PRIVATE errno_t KCALL
sys_mount_impl(USER UNCHECKED char const *source,
               USER UNCHECKED char const *target,
               USER UNCHECKED char const *filesystemtype,
               syscall_ulong_t mountflags,
               USER UNCHECKED void const *data) {
	atflag_t atflags;
	validate_readable(target, 1);
	atflags = fs_atflags(0) | AT_IGNORE_TRAILING_SLASHES;
	if (mountflags & MS_MOVE) {
		REF struct path *source_path;
		REF struct path *target_path;
		validate_readable(source, 1);
		/* Move a mounting point. */
		if (mountflags & ~(MS_MOVE | MS_REMOUNT)) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS,
			      mountflags, ~(MS_REMOUNT), MS_MOVE);
		}
		source_path = path_traverse_r(AT_FDCWD, source, NULL, NULL, atflags);
		FINALLY_DECREF_UNLIKELY(source_path);
		target_path = path_traverse_r(AT_FDCWD, target, NULL, NULL, atflags);
		FINALLY_DECREF_UNLIKELY(target_path);
		if (path_ismount(target_path) && !(mountflags & MS_REMOUNT))
			THROW(E_FSERROR_PATH_ALREADY_MOUNTED);
		if (!path_ismount(source_path))
			THROW(E_FSERROR_NOT_A_MOUNTING_POINT);

		/* Require mounting rights. */
		require(CAP_MOUNT);
#if 1 /* TODO */
		THROW(E_NOT_IMPLEMENTED_TODO);
#else
		path_movemount(target_path, source_path,
		               (mountflags & MS_REMOUNT) != 0);
#endif
	} else if (mountflags & MS_BIND) {
		REF struct fnode *node;
		REF struct path *target_path;
		/* Create a bind mounting point. */
		if (mountflags & ~(MS_BIND | MS_REMOUNT | MS_REC)) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS,
			      mountflags, ~(MS_REC | MS_REMOUNT), MS_BIND);
		}
		if (mountflags & MS_REC) {
			/* Recursively bind all mounting points from `source' */
			THROW(E_NOT_IMPLEMENTED_TODO);
		}
		validate_readable(source, 1);
		node = path_traversefull(AT_FDCWD, source, atflags);
		FINALLY_DECREF_UNLIKELY(node);
		if (!fnode_isdir(node))
			THROW(E_FSERROR_NOT_A_DIRECTORY,
			      E_FILESYSTEM_NOT_A_DIRECTORY_MOUNT_BIND);
		target_path = path_traverse_r(AT_FDCWD, target, NULL, NULL, atflags);
		FINALLY_DECREF_UNLIKELY(target_path);
		if (path_ismount(target_path) && !(mountflags & MS_REMOUNT))
			THROW(E_FSERROR_PATH_ALREADY_MOUNTED);
		require(CAP_MOUNT);                                          /* Require mounting rights. */
		decref_unlikely(path_mount(target_path, fnode_asdir(node))); /* Mount the directory from the other node. */
	} else if (mountflags & MS_REMOUNT) {
		REF struct path *target_path;
		struct fsuper *super;
		/* Modify an existing mounting point. */
		if (mountflags & ~(MS_LAZYTIME | MS_MANDLOCK | MS_NOATIME | MS_NODEV | MS_NODIRATIME | MS_NOEXEC |
		                   MS_NOSUID | MS_RELATIME | MS_RDONLY | MS_SYNCHRONOUS | MS_DIRSYNC | MS_REMOUNT |
		                   MS_STRICTATIME)) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG, E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS,
			      mountflags,
			      ~(MS_LAZYTIME | MS_MANDLOCK | MS_NOATIME | MS_NODEV | MS_NODIRATIME | MS_NOEXEC |
			        MS_NOSUID | MS_RELATIME | MS_RDONLY | MS_SYNCHRONOUS | MS_DIRSYNC | MS_STRICTATIME),
			      MS_REMOUNT);
		}
		target_path = path_traverse_r(AT_FDCWD, target, NULL, NULL, atflags);
		FINALLY_DECREF_UNLIKELY(target_path);
		if (!path_ismount(target_path))
			THROW(E_FSERROR_NOT_A_MOUNTING_POINT);
		/* Require mounting rights. */
		require(CAP_MOUNT);
		super = path_getsuper(target_path);
		super_set_mount_flags(super, mountflags);
	} else {
		/* Regular, old mount() */
		REF struct ffilesys *type;
		REF struct path *mount_location;
		REF struct fsuper *super;
		REF struct fnode *dev;
		bool newsuper;
		VALIDATE_FLAGSET(mountflags,
		                 MS_RDONLY | MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_SYNCHRONOUS |
		                 MS_MANDLOCK | MS_DIRSYNC | MS_NOATIME | MS_NODIRATIME |
		                 MS_SILENT | MS_POSIXACL | MS_UNBINDABLE | MS_PRIVATE | MS_SLAVE |
		                 MS_SHARED | MS_RELATIME | MS_KERNMOUNT | MS_I_VERSION | MS_STRICTATIME |
		                 MS_LAZYTIME | MS_ACTIVE | MS_NOUSER,
		                 E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS);
		if (!filesystemtype) {
			/* NOTE: This right here (automatically determine filesystem type) is
			 *       actually a KOS extension;  linux doesn't support doing  this
			 *       and forces you to  try every fs-type /proc/filesystems  when
			 *       wanting to do a typeless mount. */
			type = NULL;
		} else {
			validate_readable(filesystemtype, 1);
			type = ffilesys_byname(filesystemtype, strlen(filesystemtype));
			if unlikely(!type)
				THROW(E_FSERROR_UNKNOWN_FILE_SYSTEM);
		}
		/* Require mounting rights. */
		require(CAP_MOUNT);

		/* IMPORTANT: `type' may only be decref'd _AFTER_ a mount has  happened.
		 * When `type' is  `FFILESYS_F_SINGLE', then  the associated  superblock
		 * may  be statically allocated within a secondary driver, in which case
		 * holding a reference to a static structure is pretty much meaningless.
		 *
		 * However, reference counting control for `ffilesys' is actually backed
		 * by the reference counter of  the underlying driver, meaning that  for
		 * as long as we're holding an explicit reference to `type', it's always
		 * guarantied that the driver won't unload before we're done here.
		 *
		 * HINT: Once a mounting point has been created (by `path_mount()'),  its
		 *       existence will keep on holding an explicit reference to the same
		 *       driver (`path->p_dir->fn_super->fs_sys->ffs_drv') for as long as
		 *       the  path hasn't been  destroyed (!wasdestroyed()), meaning that
		 *       until `path_mount()' got called, we  need to keep this  explicit
		 *       reference around. */
		FINALLY_XDECREF_UNLIKELY(type);
		if (type && type->ffs_flags & (FFILESYS_F_NODEV | FFILESYS_F_SINGLE)) {
			/* No device needed! */
			dev = NULL;
		} else {
			if unlikely(!source)
				THROW(E_FSERROR_MOUNT_NEEDS_DEVICE);
			validate_readable(source, 1);
			dev = path_traversefull(AT_FDCWD, source, atflags & ~AT_IGNORE_TRAILING_SLASHES);
			if (fnode_isdevnode(dev) && !fnode_isdevice(dev)) {
				/* Device node, but not a device file (dereference to get the pointed-to device) */
				dev_t devno;
				FINALLY_DECREF_UNLIKELY(dev);
				devno = fnode_asdevnode(dev)->dn_devno;
				dev   = device_lookup_bydev(S_IFBLK, devno);
				if unlikely(!dev)
					THROW(E_NO_DEVICE, E_NO_DEVICE_KIND_BLKDEV, devno);
			}
		}
		FINALLY_XDECREF_UNLIKELY(dev);

		/* Open the superblock with the associated device. */
again_open_superblock:
		super = type ? ffilesys_open(type, &newsuper, dev, (USER UNCHECKED char *)data)
		             : ffilesys_opendev(&newsuper, dev, (USER UNCHECKED char *)data);
		if unlikely(!super)
			THROW(E_FSERROR_WRONG_FILE_SYSTEM);
		FINALLY_DECREF_UNLIKELY(super);
		if (newsuper) {
			super_set_mount_flags(super, mountflags);
			/* Make the superblock globally visible. */
			assert(!(super->fs_root.mf_flags & MFILE_FN_GLOBAL_REF));
			super->fs_root.mf_flags |= MFILE_FN_GLOBAL_REF;
			TRY {
				fallsuper_acquire();
			} EXCEPT {
				if (dev != NULL)
					ffilesys_open_done(dev);
				assert(super->fs_root.mf_refcnt == 1);
				super->fs_root.mf_refcnt = 0;
				COMPILER_WRITE_BARRIER();
				destroy(super);
				RETHROW();
			}
			super->fs_root.mf_refcnt = 2;
			COMPILER_WRITE_BARRIER();
			fallsuper_insert(super);
			fallsuper_release();
			if (dev != NULL)
				ffilesys_open_done(dev);
		}
		TRY {
			/* Find out where the mount should happen */
			mount_location = path_traverse_r(AT_FDCWD, target, NULL, NULL, atflags);
			FINALLY_DECREF_UNLIKELY(mount_location);

			/* Do the mount */
			if (path_ismount(mount_location))
				THROW(E_FSERROR_PATH_ALREADY_MOUNTED);
			mount_location = path_mount(mount_location, &super->fs_root);
			if unlikely(!mount_location) {
				/* This can happen when trying to create secondary mounting  points
				 * for filesystems that have been unmounted due to lack of mounting
				 * points since it was originally returned by `ffilesys_open()'. */
				assert(!newsuper);
				goto again_open_superblock;
			}
			decref_unlikely(mount_location);

			/* Set flags for multi-mounted superblocks. */
			if (!newsuper)
				super_set_mount_flags(super, mountflags);
		} EXCEPT {
			/* If the superblock was newly created, delete it on exception. */
			if (newsuper)
				fsuper_delete(super);
			RETHROW();
		}
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MOUNT */

#ifdef __ARCH_WANT_SYSCALL_MOUNT
DEFINE_SYSCALL5(errno_t, mount,
                USER UNCHECKED char const *, source,
                USER UNCHECKED char const *, target,
                USER UNCHECKED char const *, filesystemtype,
                syscall_ulong_t, mountflags,
                USER UNCHECKED void const *, data) {
	return sys_mount_impl(source, target, filesystemtype, mountflags, data);
}
#endif /* __ARCH_WANT_SYSCALL_MOUNT */





/************************************************************************/
/* truncate(), truncate64()                                             */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_TRUNCATE) || \
     defined(__ARCH_WANT_SYSCALL_TRUNCATE64))
PRIVATE errno_t KCALL
sys_truncate_impl(USER UNCHECKED char const *pathname,
                  pos_t length) {
	REF struct fnode *node;
	validate_readable(pathname, 1);
	node = path_traversefull(AT_FDCWD, pathname, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	fnode_access(node, W_OK);
	mfile_utruncate(node, length);
	return -EOK;
}
#endif /* truncate */

#ifdef __ARCH_WANT_SYSCALL_TRUNCATE
DEFINE_SYSCALL2(errno_t, truncate,
                USER UNCHECKED char const *, pathname,
                syscall_ulong_t, length) {
	return sys_truncate_impl(pathname, (pos_t)length);
}
#endif /* __ARCH_WANT_SYSCALL_TRUNCATE */

#ifdef __ARCH_WANT_SYSCALL_TRUNCATE64
DEFINE_SYSCALL2(errno_t, truncate64,
                USER UNCHECKED char const *, pathname,
                uint64_t, length) {
	return sys_truncate_impl(pathname, (pos_t)length);
}
#endif /* __ARCH_WANT_SYSCALL_TRUNCATE64 */





/************************************************************************/
/* fchdirat(), fchdir(), chdir()                                        */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FCHDIRAT) || \
     defined(__ARCH_WANT_SYSCALL_FCHDIR) ||   \
     defined(__ARCH_WANT_SYSCALL_CHDIR))
PRIVATE errno_t KCALL
sys_fchdir_impl(/*inherit(always)*/ REF struct path *__restrict newpath) {
	REF struct path *oldpath;
	struct fs *myfs = THIS_FS;
	TRY {
		fnode_access(newpath->p_dir, X_OK | R_OK);
		fs_pathlock_write(myfs);
	} EXCEPT {
		decref_unlikely(newpath);
		RETHROW();
	}
	oldpath = myfs->fs_cwd; /* Inherit reference */
	myfs->fs_cwd = newpath; /* Inherit reference */

	/* Must update DOS drive CWDs when the drive of `newpath' differs from `oldpath'.
	 * In this case, `oldpath' must be saved as the new CWD for its associated drive.
	 *
	 * Behavior:
	 * >> chdir("C:\\foo\\bar");
	 * >> chdir("D:\\biz\\buz");
	 * >> chdir("C:");
	 * >> printf("%s\n", getcwd(NULL, 0));  // "C:\\foo\\bar"
	 *
	 * NOTE: This special handling isn't done by `dup2()'-style fchdir() */
	/* TODO */

	fs_pathlock_endwrite(myfs);
	decref(oldpath);
	return -EOK;
}
#endif /* chdir */

#if (defined(__ARCH_WANT_SYSCALL_FCHDIRAT) || \
     defined(__ARCH_WANT_SYSCALL_CHDIR))
PRIVATE errno_t KCALL
sys_fchdirat_impl(fd_t dirfd,
                  USER UNCHECKED char const *pathname,
                  atflag_t atflags) {
	REF struct path *newpath;
	validate_readable(pathname, 1);
	VALIDATE_FLAGSET(atflags, AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FCHDIRAT_FLAGS);
	atflags = fs_atflags(atflags) | AT_IGNORE_TRAILING_SLASHES;
	newpath = path_traverse(dirfd, pathname, NULL, NULL, atflags);
	return sys_fchdir_impl(newpath);
}
#endif /* chdir */

#ifdef __ARCH_WANT_SYSCALL_FCHDIRAT
DEFINE_SYSCALL3(errno_t, fchdirat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname, atflag_t, atflags) {
	return sys_fchdirat_impl(dirfd, pathname, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FCHDIRAT */

#ifdef __ARCH_WANT_SYSCALL_FCHDIR
DEFINE_SYSCALL1(errno_t, fchdir, fd_t, fd) {
	REF struct path *new_cwd;
	new_cwd = handles_lookuppath(fd);
	return sys_fchdir_impl(new_cwd);
}
#endif /* __ARCH_WANT_SYSCALL_FCHDIR */

#ifdef __ARCH_WANT_SYSCALL_CHDIR
DEFINE_SYSCALL1(errno_t, chdir,
                USER UNCHECKED char const *, pathname) {
	return sys_fchdirat_impl(AT_FDCWD, pathname, 0);
}
#endif /* __ARCH_WANT_SYSCALL_CHDIR */





/************************************************************************/
/* chroot()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_CHROOT
PRIVATE errno_t KCALL
sys_fchroot_impl(/*inherit(always)*/ REF struct path *__restrict newpath) {
	REF struct path *oldpath;
	struct fs *myfs = THIS_FS;
	TRY {
		fnode_access(newpath->p_dir, X_OK | R_OK);
		fs_pathlock_write(myfs);
	} EXCEPT {
		decref_unlikely(newpath);
		RETHROW();
	}
	oldpath = myfs->fs_root; /* Inherit reference */
	myfs->fs_root = newpath; /* Inherit reference */
	fs_pathlock_endwrite(myfs);
	decref(oldpath);
	return -EOK;
}

PRIVATE errno_t KCALL
sys_chroot_impl(USER UNCHECKED char const *pathname) {
	atflag_t atflags;
	REF struct path *newpath;
	validate_readable(pathname, 1);
	atflags = fs_atflags(0) | AT_IGNORE_TRAILING_SLASHES;
	newpath = path_traverse(AT_FDCWD, pathname, NULL, NULL, atflags);
	return sys_fchroot_impl(newpath);
}
#endif /* chroot */

#ifdef __ARCH_WANT_SYSCALL_CHROOT
DEFINE_SYSCALL1(errno_t, chroot,
                USER UNCHECKED char const *, pathname) {
	return sys_chroot_impl(pathname);
}
#endif /* __ARCH_WANT_SYSCALL_CHROOT */





/************************************************************************/
/* fchmodat(), fchmod(), chmod()                                        */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FCHMODAT) || \
     defined(__ARCH_WANT_SYSCALL_CHMOD))
PRIVATE errno_t KCALL
sys_fchmodat_impl(fd_t dirfd, USER CHECKED char const *filename,
                  mode_t mode, atflag_t atflags) {
	REF struct fnode *node;
	validate_readable(filename, 1);
	if (has_personality(KP_CHMOD_CHECK_MODE))
		VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE);
	VALIDATE_FLAGSET(atflags, 0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FCHMODAT_FLAGS);
	atflags = fs_atflags(atflags);
	node    = path_traversefull(dirfd, filename, atflags);
	FINALLY_DECREF_UNLIKELY(node);
	fnode_chmod(node, 0, mode & 07777);
	return -EOK;
}
#endif /* chmod */

#ifdef __ARCH_WANT_SYSCALL_FCHMODAT
DEFINE_SYSCALL4(errno_t, fchmodat, fd_t, dirfd,
                USER CHECKED char const *, filename,
                mode_t, mode, atflag_t, atflags) {
	return sys_fchmodat_impl(dirfd, filename, mode, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FCHMODAT */

#ifdef __ARCH_WANT_SYSCALL_FCHMOD
DEFINE_SYSCALL2(errno_t, fchmod, fd_t, fd, mode_t, mode) {
	REF struct fnode *node;
	if (has_personality(KP_CHMOD_CHECK_MODE))
		VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE);
	node = handles_lookupfnode(fd);
	FINALLY_DECREF_UNLIKELY(node);
	fnode_chmod(node, 0, mode & 07777);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FCHMOD */

#ifdef __ARCH_WANT_SYSCALL_CHMOD
DEFINE_SYSCALL2(errno_t, chmod, USER CHECKED char const *, filename, mode_t, mode) {
	return sys_fchmodat_impl(AT_FDCWD, filename, mode, 0);
}
#endif /* __ARCH_WANT_SYSCALL_CHMOD */





/************************************************************************/
/* fchownat(), fchown(), lchown(), chown()                              */
/* fchownat32(), fchown32(), lchown32(), chown32()                      */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FCHOWNAT32) || \
     defined(__ARCH_WANT_SYSCALL_FCHOWNAT) ||   \
     defined(__ARCH_WANT_SYSCALL_LCHOWN32) ||   \
     defined(__ARCH_WANT_SYSCALL_LCHOWN) ||     \
     defined(__ARCH_WANT_SYSCALL_CHOWN32) ||    \
     defined(__ARCH_WANT_SYSCALL_CHOWN))
PRIVATE errno_t KCALL
sys_fchownat_impl(fd_t dirfd, USER UNCHECKED char const *filename,
                  uid_t owner, gid_t group, atflag_t atflags) {
	REF struct fnode *node;
	validate_readable(filename, 1);
	VALIDATE_FLAGSET(atflags, 0| AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FCHOWNAT_FLAGS);
	atflags = fs_atflags(atflags);
	node    = path_traversefull(dirfd, filename, atflags);
	FINALLY_DECREF_UNLIKELY(node);
	fnode_chown(node, owner, group);
	return -EOK;
}
#endif /* chown */

#if (defined(__ARCH_WANT_SYSCALL_FCHOWN32) || \
     defined(__ARCH_WANT_SYSCALL_FCHOWN))
PRIVATE errno_t KCALL
sys_fchown_impl(fd_t fd, uid_t owner, gid_t group) {
	REF struct fnode *node;
	node = handles_lookupfnode(fd);
	FINALLY_DECREF_UNLIKELY(node);
	fnode_chown(node, owner, group);
	return -EOK;
}
#endif /* chown */

#ifdef __ARCH_WANT_SYSCALL_FCHOWNAT32
DEFINE_SYSCALL5(errno_t, fchownat32, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_fchownat32), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT3_fchownat32), group,
                atflag_t, atflags) {
	return sys_fchownat_impl(dirfd, filename, (uid_t)owner, (gid_t)group, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FCHOWNAT32 */

#ifdef __ARCH_WANT_SYSCALL_FCHOWNAT
DEFINE_SYSCALL5(errno_t, fchownat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_fchownat), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT3_fchownat), group,
                atflag_t, atflags) {
	return sys_fchownat_impl(dirfd, filename, (uid_t)owner, (gid_t)group, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FCHOWNAT */

#ifdef __ARCH_WANT_SYSCALL_FCHOWN32
DEFINE_SYSCALL3(errno_t, fchown32, fd_t, fd,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_fchown32), group) {
	return sys_fchown_impl(fd, (uid_t)owner, (gid_t)group);
}
#endif /* __ARCH_WANT_SYSCALL_FCHOWN32 */

#ifdef __ARCH_WANT_SYSCALL_FCHOWN
DEFINE_SYSCALL3(errno_t, fchown, fd_t, fd,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_fchown), group) {
	return sys_fchown_impl(fd, (uid_t)owner, (gid_t)group);
}
#endif /* __ARCH_WANT_SYSCALL_FCHOWN */

#ifdef __ARCH_WANT_SYSCALL_LCHOWN32
DEFINE_SYSCALL3(errno_t, lchown32,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_lchown32), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_lchown32), group) {
	return sys_fchownat_impl(AT_FDCWD, filename, (uid_t)owner, (gid_t)group, AT_SYMLINK_NOFOLLOW);
}
#endif /* __ARCH_WANT_SYSCALL_LCHOWN32 */

#ifdef __ARCH_WANT_SYSCALL_LCHOWN
DEFINE_SYSCALL3(errno_t, lchown,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_lchown), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_lchown), group) {
	return sys_fchownat_impl(AT_FDCWD, filename, (uid_t)owner, (gid_t)group, AT_SYMLINK_NOFOLLOW);
}
#endif /* __ARCH_WANT_SYSCALL_LCHOWN */

#ifdef __ARCH_WANT_SYSCALL_CHOWN32
DEFINE_SYSCALL3(errno_t, chown32,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_chown32), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_chown32), group) {
	return sys_fchownat_impl(AT_FDCWD, filename, (uid_t)owner, (gid_t)group, 0);
}
#endif /* __ARCH_WANT_SYSCALL_CHOWN32 */

#ifdef __ARCH_WANT_SYSCALL_CHOWN
DEFINE_SYSCALL3(errno_t, chown,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_chown), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_chown), group) {
	return sys_fchownat_impl(AT_FDCWD, filename, (uid_t)owner, (gid_t)group, 0);
}
#endif /* __ARCH_WANT_SYSCALL_CHOWN */





/************************************************************************/
/* umask()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_UMASK
DEFINE_SYSCALL1(mode_t, umask, mode_t, mode) {
	struct fs *myfs = THIS_FS;
	return ATOMIC_XCH(myfs->fs_umask, mode & 0777);
}
#endif /* __ARCH_WANT_SYSCALL_UMASK */





/************************************************************************/
/* fsmode()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FSMODE
/* Mask of AT_* flags that can be force-enabled/disable by `fsmode(2)' */
#define _AT_FLAGS_CHNG \
	(AT_NO_AUTOMOUNT | AT_DOSPATH)
DEFINE_SYSCALL1(uint64_t, fsmode, uint64_t, mode) {
	struct fs *myfs = THIS_FS;
	fs_mask_t new_mode;
	new_mode.f_mode = mode;

	/* Only very few AT_* flags can actually be force-enabled/disabled. */
	new_mode.f_atmask |= ~_AT_FLAGS_CHNG;
	new_mode.f_atflag &= _AT_FLAGS_CHNG;

	/* Set the new filesystem mode. */
	return atomic64_xch(&myfs->fs_mode.f_atom, new_mode.f_mode);
}
#endif /* __ARCH_WANT_SYSCALL_FSMODE */





/************************************************************************/
/* sync(), syncfs()                                                     */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SYNC
DEFINE_SYSCALL0(errno_t, sync) {
	TRY {
		fsuper_syncall();
	} EXCEPT {
		except_printf("sync()");
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SYNC */

#ifdef __ARCH_WANT_SYSCALL_SYNCFS
DEFINE_SYSCALL1(errno_t, syncfs, fd_t, fd) {
	REF struct fsuper *super;
	super = handles_lookupfsuper_relaxed(fd);
	FINALLY_DECREF_UNLIKELY(super);
	fsuper_sync(super);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SYNCFS */





/************************************************************************/
/* openat(), open(), creat()                                            */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_OPENAT) || \
     defined(__ARCH_WANT_SYSCALL_OPEN) ||   \
     defined(__ARCH_WANT_SYSCALL_CREAT))
PRIVATE fd_t KCALL
sys_openat_impl(fd_t dirfd, USER UNCHECKED char const *filename,
                oflag_t oflags, mode_t mode) {
	fd_t result;
	REF struct handle hand;
	struct handle_install_data install;
	validate_readable(filename, 1);
	result = handles_install_begin(&install);
	TRY {
		/* Do the open */
		hand = path_open(dirfd, filename, oflags, mode);
	} EXCEPT {
		handles_install_abort(&install);
		RETHROW();
	}

	/* Commit the new handle. */
	handles_install_commit_inherit(&install, &hand);
	return result;
}
#endif /* open... */

#ifdef __ARCH_WANT_SYSCALL_OPENAT
DEFINE_SYSCALL4(fd_t, openat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                oflag_t, oflags, mode_t, mode) {
	return sys_openat_impl(dirfd, filename, oflags, mode);
}
#endif /* __ARCH_WANT_SYSCALL_OPENAT */

#ifdef __ARCH_WANT_SYSCALL_OPEN
DEFINE_SYSCALL3(fd_t, open,
                USER UNCHECKED char const *, filename,
                oflag_t, oflags, mode_t, mode) {
	return sys_openat_impl(AT_FDCWD, filename, oflags, mode);
}
#endif /* __ARCH_WANT_SYSCALL_OPEN */

#ifdef __ARCH_WANT_SYSCALL_CREAT
DEFINE_SYSCALL2(fd_t, creat,
                USER UNCHECKED char const *, filename,
                mode_t, mode) {
	return sys_openat_impl(AT_FDCWD, filename, O_CREAT | O_WRONLY | O_TRUNC, mode);
}
#endif /* __ARCH_WANT_SYSCALL_CREAT */





/************************************************************************/
/* frealpath4(), frealpathat()                                          */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FREALPATH4
DEFINE_SYSCALL4(ssize_t, frealpath4,
                fd_t, fd, USER UNCHECKED char *, buf,
                size_t, buflen, atflag_t, atflags) {
	struct handle hand;
	size_t result;
	REF struct path *root;
	validate_writable(buf, buflen);
	VALIDATE_FLAGSET(atflags,
	                 AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS);
	atflags = fs_atflags(atflags);
	if (atflags & AT_ALTPATH)
		atflags ^= AT_DOSPATH;
	root = fs_getroot(THIS_FS);
	FINALLY_DECREF_UNLIKELY(root);
	hand = handles_lookup(fd);
	{
		RAII_FINALLY { decref_unlikely(hand); };
		switch (hand.h_type) {

		case HANDLE_TYPE_MFILE: {
			/* Allow frealpath on files that can be casted into a path/dirent pair.
			 * This is the case for (e.g.) device files! */
			struct mfile *me = (struct mfile *)hand.h_data;
			REF struct path *fspath;
			REF struct fdirent *fsname;
			fspath = (REF struct path *)mfile_utryas(me, HANDLE_TYPE_PATH);
			if unlikely(!fspath)
				goto bad_handle_type;
			FINALLY_DECREF_UNLIKELY(fspath);
			fsname = (REF struct fdirent *)mfile_utryas(me, HANDLE_TYPE_DIRENT);
			if unlikely(!fsname)
				goto bad_handle_type;
			FINALLY_DECREF_UNLIKELY(fsname);
			result = path_sprintent(fspath, fsname->fd_name,
			                        fsname->fd_namelen, buf, buflen,
			                        atflags | AT_PATHPRINT_INCTRAIL, root);
		}	break;

		case HANDLE_TYPE_FILEHANDLE:
		case HANDLE_TYPE_TEMPHANDLE:
		case HANDLE_TYPE_DIRHANDLE:
		case HANDLE_TYPE_FIFOHANDLE: {
			static_assert(offsetof(struct filehandle, fh_path) == offsetof(struct dirhandle, dh_path));
			static_assert(offsetof(struct filehandle, fh_dirent) == offsetof(struct dirhandle, dh_dirent));
			static_assert(offsetof(struct filehandle, fh_path) == offsetof(struct fifohandle, fu_path));
			static_assert(offsetof(struct filehandle, fh_dirent) == offsetof(struct fifohandle, fu_dirent));
			struct filehandle *me;
			me = (struct filehandle *)hand.h_data;
			if unlikely(!me->fh_path || !me->fh_dirent) {
				/* TODO: Do what `HANDLE_TYPE_MFILE' does and try to cast the file to a path/name. */
				goto bad_handle_type;
			}
			result = path_sprintent(me->fh_path, me->fh_dirent->fd_name,
			                        me->fh_dirent->fd_namelen, buf, buflen,
			                        atflags | AT_PATHPRINT_INCTRAIL, root);
		}	break;

		case HANDLE_TYPE_PATH:
			result = path_sprint((struct path *)hand.h_data, buf, buflen, atflags, root);
			break;

		default:
bad_handle_type:
			THROW(E_INVALID_HANDLE_FILETYPE,
			      /* fd:                 */ (syscall_slong_t)fd,
			      /* needed_handle_type: */ HANDLE_TYPE_PATH,
			      /* actual_handle_type: */ hand.h_type,
			      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
			      /* actual_handle_kind: */ handle_typekind(&hand));
			break;
		}
	}
	/* Throw a buffer error if the caller doesn't want the required size */
	if (result > buflen && !(atflags & AT_READLINK_REQSIZE))
		THROW(E_BUFFER_TOO_SMALL, result, buflen);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_FREALPATH4 */

#ifdef __ARCH_WANT_SYSCALL_FREALPATHAT
DEFINE_SYSCALL5(ssize_t, frealpathat,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                USER UNCHECKED char *, buf, size_t, buflen, atflag_t, atflags) {
	size_t result;
	REF struct path *root;
	REF struct path *containing_path;
	REF struct fdirent *containing_dentry;
	validate_writable(buf, buflen);
	VALIDATE_FLAGSET(atflags,
	                 AT_SYMLINK_NOFOLLOW | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS);
	atflags = fs_atflags(atflags);
	{
		/* Lookup the named file */
		REF struct fnode *node;
		node = path_traversefull(dirfd, filename, atflags,
		                         &containing_path,
		                         &containing_dentry);
		decref_unlikely(node);
	}
	{
		FINALLY_DECREF_UNLIKELY(containing_path);
		FINALLY_DECREF_UNLIKELY(containing_dentry);
		root = fs_getroot(THIS_FS);
		FINALLY_DECREF_UNLIKELY(root);
		if (atflags & AT_ALTPATH)
			atflags ^= AT_DOSPATH;
		/* Print the path */
		result = path_sprintent(containing_path, containing_dentry->fd_name,
		                        containing_dentry->fd_namelen, buf, buflen,
		                        atflags | AT_PATHPRINT_INCTRAIL, root);
	}
	/* Throw a buffer error if the caller doesn't want the required size */
	if (result > buflen && !(atflags & AT_READLINK_REQSIZE))
		THROW(E_BUFFER_TOO_SMALL, result, buflen);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_FREALPATHAT */






/************************************************************************/
/* Base implementation of all stat() functions                          */
/************************************************************************/
LOCAL errno_t KCALL
system_fstatat(fd_t dirfd,
               USER UNCHECKED char const *filename,
               USER CHECKED struct stat *statbuf,
               atflag_t atflags) {
	REF struct fnode *node;
	validate_readable(filename, 1);
	VALIDATE_FLAGSET(atflags,
	                 0 | AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_KFSTATAT_FLAGS);
	node = path_traversefull(dirfd, filename, atflags);
	FINALLY_DECREF_UNLIKELY(node);
	mfile_ustat(node, statbuf);
	return -EOK;
}

LOCAL errno_t KCALL
system_fstat(fd_t fd, USER CHECKED struct stat *statbuf) {
	struct handle hand;
	hand = handles_lookup(fd);
	RAII_FINALLY { decref_unlikely(hand); };
	handle_stat(hand, statbuf);
	return -EOK;
}

LOCAL errno_t KCALL
system_lstat(USER UNCHECKED char const *filename,
             USER CHECKED struct stat *statbuf) {
	return system_fstatat(AT_FDCWD, filename, statbuf, AT_SYMLINK_NOFOLLOW);
}

LOCAL errno_t KCALL
system_stat(USER UNCHECKED char const *filename,
            USER CHECKED struct stat *statbuf) {
	return system_fstatat(AT_FDCWD, filename, statbuf, 0);
}







/************************************************************************/
/* kfstatat(), kfstat(), klstat(), kstat()                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_KFSTATAT
DEFINE_SYSCALL4(errno_t, kfstatat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct __kos_stat *, statbuf,
                atflag_t, atflags) {
	validate_writable(statbuf, sizeof(*statbuf));
	return system_fstatat(dirfd, filename, statbuf, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_KFSTATAT */

#ifdef __ARCH_WANT_SYSCALL_KFSTAT
DEFINE_SYSCALL2(errno_t, kfstat, fd_t, fd,
                USER UNCHECKED struct __kos_stat *, statbuf) {
	validate_writable(statbuf, sizeof(*statbuf));
	return system_fstat(fd, statbuf);
}
#endif /* __ARCH_WANT_SYSCALL_KFSTAT */

#ifdef __ARCH_WANT_SYSCALL_KLSTAT
DEFINE_SYSCALL2(errno_t, klstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct __kos_stat *, statbuf) {
	validate_writable(statbuf, sizeof(*statbuf));
	return system_lstat(filename, statbuf);
}
#endif /* __ARCH_WANT_SYSCALL_KLSTAT */

#ifdef __ARCH_WANT_SYSCALL_KSTAT
DEFINE_SYSCALL2(errno_t, kstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct __kos_stat *, statbuf) {
	validate_writable(statbuf, sizeof(*statbuf));
	return system_stat(filename, statbuf);
}
#endif /* __ARCH_WANT_SYSCALL_KSTAT */





/************************************************************************/
/* oldfstatat(), oldfstat(), oldlstat(), oldstat() */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_OLDFSTATAT
DEFINE_SYSCALL4(errno_t, oldfstatat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_oldstat *, statbuf,
                atflag_t, atflags) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, atflags);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OLDFSTATAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_OLDFSTATAT
DEFINE_COMPAT_SYSCALL4(errno_t, oldfstatat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct linux_oldstat *, statbuf,
                       atflag_t, atflags) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, atflags);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_OLDFSTATAT */

#ifdef __ARCH_WANT_SYSCALL_OLDFSTAT
DEFINE_SYSCALL2(errno_t, oldfstat, fd_t, fd,
                USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstat(fd, &st);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OLDFSTAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_OLDFSTAT
DEFINE_COMPAT_SYSCALL2(errno_t, oldfstat, fd_t, fd,
                       USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstat(fd, &st);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_OLDFSTAT */

#ifdef __ARCH_WANT_SYSCALL_OLDLSTAT
DEFINE_SYSCALL2(errno_t, oldlstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_lstat(filename, &st);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OLDLSTAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_OLDLSTAT
DEFINE_COMPAT_SYSCALL2(errno_t, oldlstat,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_lstat(filename, &st);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_OLDLSTAT */

#ifdef __ARCH_WANT_SYSCALL_OLDSTAT
DEFINE_SYSCALL2(errno_t, oldstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_stat(filename, &st);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OLDSTAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_OLDSTAT
DEFINE_COMPAT_SYSCALL2(errno_t, oldstat,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_stat(filename, &st);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_OLDSTAT */





/************************************************************************/
/* fstatat(), fstat(), lstat(), stat()          */
/* fstatat64(), fstat64(), lstat64(), stat64()  */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FSTATAT
DEFINE_SYSCALL4(errno_t, fstatat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat32 *, statbuf,
                atflag_t, atflags) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, atflags);
	stat_to_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSTATAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FSTATAT
DEFINE_COMPAT_SYSCALL4(errno_t, fstatat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_linux_stat32 *, statbuf,
                       atflag_t, atflags) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, atflags);
	stat_to_compat_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTATAT */

#ifdef __ARCH_WANT_SYSCALL_FSTATAT64
DEFINE_SYSCALL4(errno_t, fstatat64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat64 *, statbuf,
                atflag_t, atflags) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, atflags);
	stat_to_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSTATAT64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FSTATAT64
DEFINE_COMPAT_SYSCALL4(errno_t, fstatat64, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_linux_stat64 *, statbuf,
                       atflag_t, atflags) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, atflags);
	stat_to_compat_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTATAT64 */

#ifdef __ARCH_WANT_SYSCALL_FSTAT
DEFINE_SYSCALL2(errno_t, fstat, fd_t, fd,
                USER UNCHECKED struct linux_stat32 *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstat(fd, &st);
	stat_to_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSTAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FSTAT
DEFINE_COMPAT_SYSCALL2(errno_t, fstat, fd_t, fd,
                       USER UNCHECKED struct compat_linux_stat32 *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstat(fd, &st);
	stat_to_compat_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTAT */

#ifdef __ARCH_WANT_SYSCALL_FSTAT64
DEFINE_SYSCALL2(errno_t, fstat64, fd_t, fd,
                USER UNCHECKED struct linux_stat64 *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstat(fd, &st);
	stat_to_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSTAT64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FSTAT64
DEFINE_COMPAT_SYSCALL2(errno_t, fstat64, fd_t, fd,
                       USER UNCHECKED struct compat_linux_stat64 *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstat(fd, &st);
	stat_to_compat_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTAT64 */

#ifdef __ARCH_WANT_SYSCALL_LSTAT
DEFINE_SYSCALL2(errno_t, lstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat32 *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_lstat(filename, &st);
	stat_to_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_LSTAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_LSTAT
DEFINE_COMPAT_SYSCALL2(errno_t, lstat,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_linux_stat32 *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_lstat(filename, &st);
	stat_to_compat_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_LSTAT */

#ifdef __ARCH_WANT_SYSCALL_LSTAT64
DEFINE_SYSCALL2(errno_t, lstat64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat64 *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_lstat(filename, &st);
	stat_to_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_LSTAT64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_LSTAT64
DEFINE_COMPAT_SYSCALL2(errno_t, lstat64,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_linux_stat64 *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_lstat(filename, &st);
	stat_to_compat_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_LSTAT64 */

#ifdef __ARCH_WANT_SYSCALL_STAT
DEFINE_SYSCALL2(errno_t, stat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat32 *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_stat(filename, &st);
	stat_to_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_STAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_STAT
DEFINE_COMPAT_SYSCALL2(errno_t, stat,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_linux_stat32 *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_stat(filename, &st);
	stat_to_compat_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_STAT */

#ifdef __ARCH_WANT_SYSCALL_STAT64
DEFINE_SYSCALL2(errno_t, stat64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat64 *, statbuf) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_stat(filename, &st);
	stat_to_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_STAT64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_STAT64
DEFINE_COMPAT_SYSCALL2(errno_t, stat64,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_linux_stat64 *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_stat(filename, &st);
	stat_to_compat_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_STAT64 */





/************************************************************************/
/* freadlinkat(), readlinkat(), readlink()                              */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FREADLINKAT) || \
     defined(__ARCH_WANT_SYSCALL_READLINKAT) ||  \
     defined(__ARCH_WANT_SYSCALL_READLINK))
PRIVATE ssize_t KCALL
sys_freadlinkat_impl(fd_t dirfd, USER UNCHECKED char const *filename,
                     USER UNCHECKED char *buf, size_t buflen, atflag_t atflags) {
	size_t result;
	REF struct fnode *node;
	validate_readable(filename, 1);
	validate_writable(buf, buflen);
	VALIDATE_FLAGSET(atflags, 0 | AT_READLINK_REQSIZE | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FREADLINKAT_FLAGS);
	atflags = fs_atflags(atflags);
	node    = path_traversefull(dirfd, filename, atflags | AT_SYMLINK_NOFOLLOW);
	{
		FINALLY_DECREF_UNLIKELY(node);
		fnode_access(node, R_OK);
		if (!fnode_islnk(node)) {
			THROW(E_FSERROR_NOT_A_SYMBOLIC_LINK);
		}
		/* Read the contents of the symbolic link. */
		result = flnknode_readlink(fnode_aslnk(node), buf, buflen);
	}
	if (atflags & AT_READLINK_REQSIZE) {
		/* Append a trailing NUL-character */
		if (result < buflen)
			buf[result] = '\0';
		++result;
	} else if (result >= buflen) {
		/* From `man':
		 *  ... It will (silently) truncate the contents (to a  length
		 *      of bufsiz characters), in case the buffer is too small
		 *      to hold all of the contents
		 * In other words, it's $h1t, which is why KOS offers the extension
		 * of using `AT_READLINK_REQSIZE'. */
		result = buflen;
	}
	return (ssize_t)result;
}
#endif /* readlink */

#ifdef __ARCH_WANT_SYSCALL_FREADLINKAT
DEFINE_SYSCALL5(ssize_t, freadlinkat,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                USER UNCHECKED char *, buf, size_t, buflen, atflag_t, atflags) {
	return sys_freadlinkat_impl(dirfd, filename, buf, buflen, atflags);
}
#endif /* __ARCH_WANT_SYSCALL_FREADLINKAT */

#ifdef __ARCH_WANT_SYSCALL_READLINKAT
DEFINE_SYSCALL4(ssize_t, readlinkat,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                USER UNCHECKED char *, buf, size_t, buflen) {
	return sys_freadlinkat_impl(dirfd, filename, buf, buflen, 0);
}
#endif /* __ARCH_WANT_SYSCALL_READLINKAT */

#ifdef __ARCH_WANT_SYSCALL_READLINK
DEFINE_SYSCALL3(ssize_t, readlink,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED char *, buf, size_t, buflen) {
	return sys_freadlinkat_impl(AT_FDCWD, filename, buf, buflen, 0);
}
#endif /* __ARCH_WANT_SYSCALL_READLINK */





/************************************************************************/
/* execveat(), execve()                                                 */
/************************************************************************/
typedef void (KCALL *kernel_permman_onexec_t)(void);
INTDEF kernel_permman_onexec_t __kernel_permman_onexec_start[];
INTDEF kernel_permman_onexec_t __kernel_permman_onexec_end[];

LOCAL void KCALL run_permman_onexec(void) {

	/* Close file handles marked as IO_CLOEXEC */
	handman_cloexec(THIS_HANDMAN);

	/* Functions defined by `DEFINE_PERMMAN_ONEXEC()' (TODO: Inline direct calls to all of these) */
	{
		kernel_permman_onexec_t *iter;
		for (iter = __kernel_permman_onexec_start;
		     iter < __kernel_permman_onexec_end; ++iter)
			(**iter)();
	}

	/* Invoke dynamic callbacks. */
	mman_onexec_callbacks();
}



PRIVATE void KCALL
kernel_do_execveat_impl(/*in|out*/ struct execargs *__restrict args) {
	uintptr_t thread_flags;
	thread_flags = PERTASK_GET(this_task.t_flags);
#ifdef CONFIG_HAVE_USERPROCMASK
	/* If the calling  thread uses userprocmask,  we must  copy
	 * their final process mask into kernel-space before we  do
	 * the exec. Note that the `TASK_FUSERPROCMASK' flag itself
	 * is later unset by `reset_user_except_handler()' */
	if (thread_flags & TASK_FUSERPROCMASK) {
		USER CHECKED struct userprocmask *um;
		USER UNCHECKED sigset_t *um_sigset;
		size_t um_sigsiz;
		um        = PERTASK_GET(this_userprocmask_address);
		um_sigset = um->pm_sigmask;
		um_sigsiz = um->pm_sigsize;
		COMPILER_READ_BARRIER();
		validate_readable(um_sigset, um_sigsiz);
		if (um_sigsiz > sizeof(sigset_t))
			um_sigsiz = sizeof(sigset_t);

		/* Copy the final user-space signal mask into kernel-space.
		 * If  the exec() ends up succeeding, then this will be the
		 * signal mask that  the new program  will start  execution
		 * under. */
		memset(mempcpy(&THIS_KERNEL_SIGMASK, um_sigset, um_sigsiz),
		       0xff, sizeof(sigset_t) - um_sigsiz);
	}
#endif /* CONFIG_HAVE_USERPROCMASK */

	/* Deal with the special VFORK mode. */
	args->ea_change_mman_to_effective_mman = true;
	if (thread_flags & TASK_FVFORK) {
		REF struct mman *newmm;
		/* Construct the new VM for the process after the exec. */
		newmm = mman_new();
		{
			FINALLY_DECREF_UNLIKELY(newmm);
			args->ea_mman = newmm;
			mman_exec(args);
			/* Load the newly initialized VM as our current VM */
			task_setmman(newmm);
		}
		/* ==== Point of no  return: This  is where  we
		 *      indicate success to our parent process. */
#ifdef CONFIG_HAVE_USERPROCMASK
		{
			uintptr_t old_flags;
			old_flags = ATOMIC_FETCHAND(THIS_TASK->t_flags,
			                            ~(TASK_FVFORK | TASK_FUSERPROCMASK |
			                              TASK_FUSERPROCMASK_AFTER_VFORK));
			/* Special case: If  userprocmask  was enabled  after  vfork(), then
			 *               we must write-back a NULL to its `pm_sigmask' field
			 *               in order  to indicate  to the  parent process  that
			 *               their userprocmask hasn't been enabled, yet.
			 * This is actually (kind-of) a libc-specific implementation detail,
			 * as other libcs which want  to implement userprocmask support  may
			 * choose a different mechanism for indicating that the mask  hasn't
			 * been  initialized for some given thread. Yet KOS's native libc is
			 * using  a NULL-pointer in `pm_sigmask' for this, so that's what we
			 * rely on here (s.a. `libc_sigprocmask(3)') */
			if (old_flags & TASK_FUSERPROCMASK_AFTER_VFORK) {
				USER CHECKED struct userprocmask *um;
				um = PERTASK_GET(this_userprocmask_address);
				printk(KERN_DEBUG "[userprocmask:%p] Uninstall during exec after vfork\n", um);
				TRY {
					ATOMIC_WRITE(um->pm_sigmask, NULL);
				} EXCEPT {
					except_class_t cls = except_class();
					if (EXCEPTCLASS_ISRTLPRIORITY(cls))
						RETHROW();
					except_printf("Handling TASK_FUSERPROCMASK_AFTER_VFORK");
				}
			}
		}
#else /* CONFIG_HAVE_USERPROCMASK */
		ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FVFORK);
#endif /* !CONFIG_HAVE_USERPROCMASK */
		{
			struct taskpid *mypid = THIS_TASKPID;
			if likely(mypid)
				sig_broadcast(&mypid->tp_changed);
		}
		/* With the VFORK flag cleared, check for pending POSIX signals,
		 * since this also means  that our thread's user-visible  signal
		 * mask has once again come into effect. */
		task_serve();
	} else {
		args->ea_mman = THIS_MMAN;
#ifdef CONFIG_HAVE_USERPROCMASK
		if (thread_flags & TASK_FUSERPROCMASK) {
			/* Disable USERPROCMASK during the exec.
			 * This is necessary so the task_serve() below, as well as any such
			 * called made from  within `mman_exec()' use  the kernel's  signal
			 * mask, rather than the user's! */
			ATOMIC_AND(THIS_TASK->t_flags, ~TASK_FUSERPROCMASK);
			TRY {
				mman_exec(args);
			} EXCEPT {
				/* Re-enable USERPROCMASK if the exec() failed. */
				ATOMIC_OR(THIS_TASK->t_flags, TASK_FUSERPROCMASK);
				RETHROW();
			}

			/* If the previous process used to have a userprocmask, and didn't make  proper
			 * use  of calling `sys_sigmask_check()',  we check for  pending signals in the
			 * context of the new process, just so it gets to start out with a clean slate.
			 *
			 * Note though that assuming the original program used the userprocmask API
			 * correctly, there shouldn't be any unmasked, pending signals from  before
			 * the  call to exec() at this point (of course, there could always be some
			 * from during the call...) */
			task_serve();
		} else
#endif /* CONFIG_HAVE_USERPROCMASK */
		{
			mman_exec(args);
		}
	}

	/* Rename calling thread. */
	task_setcomm(args->ea_xdentry->fd_name);

	/* Upon success, run onexec callbacks (which will clear all CLOEXEC handles). */
	run_permman_onexec();

#ifndef CONFIG_EVERYONE_IS_ROOT
	cred_onexec(args->ea_xfile);
#endif /* !CONFIG_EVERYONE_IS_ROOT */
}

PRIVATE void KCALL
kernel_do_execveat(/*in|out*/ struct execargs *__restrict args) {
	if (kernel_debugtrap_enabled() && args->ea_xdentry) {
		/* Trigger an EXEC debug trap. */
		if (args->ea_xpath) {
			char *buf, *dst;
			size_t reglen;
			reglen = (size_t)path_printent(args->ea_xpath,
			                               args->ea_xdentry->fd_name,
			                               args->ea_xdentry->fd_namelen,
			                               &format_length,
			                               NULL);
			/* Allocate  the  register  buffer  beforehand,  so  this
			 * allocation failing can still be handled by user-space.
			 * NOTE: We  always  allocate this  buffer on  the heap,  since  file paths  can get  quite long,
			 *       and  being as  close to the  bottom of  the kernel stack  as we  are, it could  be a bit
			 *       risky to allocate a huge stack-based structure when we still have to call `mman_exec()',
			 *       even when using `malloca()' (but maybe I'm just overlay cautios...) */
			buf = (char *)kmalloc((reglen + 1) * sizeof(char), GFP_NORMAL);
			RAII_FINALLY { kfree(buf); };
			dst = buf;
			path_printent(args->ea_xpath,
			              args->ea_xdentry->fd_name,
			              args->ea_xdentry->fd_namelen,
			              &format_sprintf_printer,
			              &dst);
			assert(dst == buf + reglen);
			*dst = '\0';
			/* Execute the specified program. */
			kernel_do_execveat_impl(args);
			{
				struct debugtrap_reason r;
				r.dtr_signo    = SIGTRAP;
				r.dtr_reason   = DEBUGTRAP_REASON_EXEC;
				r.dtr_strarg   = buf;
				args->ea_state = kernel_debugtrap_r(args->ea_state, &r);
			}
		} else {
			struct debugtrap_reason r;
			r.dtr_signo    = SIGTRAP;
			r.dtr_reason   = DEBUGTRAP_REASON_EXEC;
			r.dtr_strarg   = args->ea_xdentry->fd_name;
			args->ea_state = kernel_debugtrap_r(args->ea_state, &r);
		}
	} else {
		/* Execute the specified program. */
		kernel_do_execveat_impl(args);
	}
}


struct kernel_exec_rpc_data {
	WEAK refcnt_t         er_refcnt; /* Reference counter. */
	struct execargs       er_args;   /* Exec args. */
	struct exception_data er_except; /* Information about the exception that caused exec() to fail. */
	struct sig            er_error;  /* Signal broadcast upon error. */
};
#define kernel_exec_rpc_data_destroy(self) (execargs_fini(&(self)->er_args), kfree(self))
DEFINE_REFCNT_FUNCTIONS(struct kernel_exec_rpc_data, er_refcnt, kernel_exec_rpc_data_destroy)

PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
kernel_exec_rpc(struct rpc_context *__restrict ctx, void *cookie) {
	struct kernel_exec_rpc_data *data;
	data = (struct kernel_exec_rpc_data *)cookie;
	FINALLY_DECREF_UNLIKELY(data);
	/* Check  for  race  condition:  Our  RPC  only  got  executed  because  the
	 * main  thread is  currently being terminated.  - In this  case it wouldn't
	 * make any sense to try and load a new binary into the VM, so just indicate
	 * to the  receiving thread  that we've  been terminated  by propagating  an
	 * E_EXIT_THREAD exception to them. */
	if unlikely(ctx->rc_context == RPC_REASONCTX_SHUTDOWN) {
		assert(THIS_TASKPID);
		bzero(&data->er_except.e_args, sizeof(data->er_except.e_args));
		data->er_except.e_code                            = EXCEPT_CODEOF(E_EXIT_THREAD);
		data->er_except.e_args.e_exit_thread.et_exit_code = (uintptr_t)THIS_TASKPID->tp_status;
		goto error_completion;
	}
	TRY {
		data->er_args.ea_state = ctx->rc_state;
		kernel_do_execveat(&data->er_args);
		ctx->rc_state = data->er_args.ea_state;
	} EXCEPT {
		except_class_t cls = except_class();
		if (EXCEPTCLASS_ISRTLPRIORITY(cls))
			RETHROW();
		memcpy(&data->er_except, except_data(), sizeof(data->er_except));
		goto error_completion;
	}
	kfree(data);
	/* Don't try to restart the system call or something like that! */
	if (ctx->rc_context == RPC_REASONCTX_SYSCALL)
		ctx->rc_context = RPC_REASONCTX_SYSRET;
	return;
error_completion:
	sig_broadcast(&data->er_error);
}


#ifdef __ARCH_HAVE_COMPAT
#define KERNEL_EXECVEAT_ARGV_TYPE USER UNCHECKED void const *
#define KERNEL_EXECVEAT_ENVP_TYPE USER UNCHECKED void const *
#else /* __ARCH_HAVE_COMPAT */
#define KERNEL_EXECVEAT_ARGV_TYPE USER UNCHECKED char const *USER UNCHECKED const *
#define KERNEL_EXECVEAT_ENVP_TYPE USER UNCHECKED char const *USER UNCHECKED const *
#endif /* !__ARCH_HAVE_COMPAT */


/* Implementation of the execv() system call. */
INTERN struct icpustate *KCALL
kernel_execveat(fd_t dirfd,
                USER UNCHECKED char const *pathname,
                KERNEL_EXECVEAT_ARGV_TYPE argv,
                KERNEL_EXECVEAT_ENVP_TYPE envp,
                atflag_t atflags,
                IF_ARCH_HAVE_COMPAT(bool argv_is_compat,)
                struct icpustate *__restrict state) {
	struct task *caller = THIS_TASK;
	struct execargs args;
#ifdef __ARCH_HAVE_COMPAT
	validate_readable_opt(argv, 1);
	validate_readable_opt(envp, 1);
#else /* __ARCH_HAVE_COMPAT */
	validate_readable_opt(argv, sizeof(*argv));
	validate_readable_opt(envp, sizeof(*envp));
#endif /* !__ARCH_HAVE_COMPAT */
	VALIDATE_FLAGSET(atflags,
	                 AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_EXECVEAT_FLAGS);
	bzero(&args, sizeof(args));
	if ((atflags & AT_EMPTY_PATH) && !*pathname) {
		/* Special case: `fexecve()' */
		REF struct handle hand;
		hand = handles_lookup(dirfd);

		/* Convert  the handle into  the 3 relevant  objects. If any of
		 * these conversions fail, then the given handle can't be used. */
		TRY {
			args.ea_xdentry = (REF struct fdirent *)handle_tryas_noinherit(hand, HANDLE_TYPE_DIRENT);
			TRY {
				args.ea_xpath = (REF struct path *)handle_tryas_noinherit(hand, HANDLE_TYPE_PATH);
				TRY {
					args.ea_xfile = handle_as_mfile(hand); /* This inherits `hand' on success */
				} EXCEPT {
					xdecref_unlikely(args.ea_xpath);
					RETHROW();
				}
			} EXCEPT {
				xdecref_unlikely(args.ea_xdentry);
				RETHROW();
			}
		} EXCEPT {
			decref_unlikely(hand);
			RETHROW();
		}
	} else {
		args.ea_xfile = path_traversefull(dirfd, pathname, fs_atflags(atflags),
		                                  &args.ea_xpath, &args.ea_xdentry);
	}
	TRY {
		/* In order to allow for execution, the file itself must support mmaping.
		 * It's not OK if the file can be mmap'd indirectly (via an operator), or
		 * if mmap has been disabled for the file. */
		if unlikely(!mfile_hasrawio(args.ea_xfile))
			THROW(E_NOT_EXECUTABLE_NOT_REGULAR);

		/* For filesystem nodes there are a couple of additional checks. */
		if (mfile_isnode(args.ea_xfile)) {
			struct fnode *node = mfile_asnode(args.ea_xfile);
			if unlikely(node->fn_super->fs_root.mf_flags & MFILE_FS_NOEXEC)
				THROW(E_NOT_EXECUTABLE_NOEXEC); /* XXX: Some other exception for this case? */

			/* Check for execute permissions? */
			if (!fnode_mayaccess(node, R_OK | X_OK))
				THROW(E_NOT_EXECUTABLE_NOEXEC);
		}

		/* Fill in exec arguments. */
		args.ea_argv = argv;
		args.ea_envp = envp;
		IF_ARCH_HAVE_COMPAT(args.ea_argv_is_compat = argv_is_compat;)

		/* Check if we're the main thread. If no, send an
		 * RPC  to it and  have it do  the exec() for us. */
		if (!task_isaprocess(caller))
			goto send_rpc_to_main_thread;

		/* Immediately do the exec */
		args.ea_state = state;
		kernel_do_execveat(&args);
		state = args.ea_state;
	} EXCEPT {
		execargs_fini(&args);
		RETHROW();
	}
	execargs_fini(&args);
	return state;
	{
		struct kernel_exec_rpc_data *data;
		struct task *proc;
		bool rpc_ok;
send_rpc_to_main_thread:
		while ((proc = task_getproc()) == NULL)
			task_waitfor();
		TRY {
			data = (struct kernel_exec_rpc_data *)kmalloc(sizeof(struct kernel_exec_rpc_data), GFP_LOCKED);
		} EXCEPT {
			execargs_fini(&args);
			RETHROW();
		}
		memcpy(&data->er_args, &args, sizeof(struct execargs));
		sig_init(&data->er_error);
		data->er_refcnt = 2;
		assert(!task_wasconnected());
		task_connect(&data->er_error);
		/* XXX: Instead of using a cookie object, inline the RPC and use `_RPC_CONTEXT_DONTFREE' */
		TRY {
			rpc_ok = task_rpc_exec(proc, RPC_CONTEXT_KERN | RPC_SYNCMODE_F_USER | RPC_PRIORITY_F_HIGH,
			                       &kernel_exec_rpc, data);
		} EXCEPT {
			kernel_exec_rpc_data_destroy(data);
			RETHROW();
		}
		if unlikely(!rpc_ok) {
			/* The main thread was already terminated. */
			uint16_t status = FORTASK(caller, this_taskpid)->tp_status;
			task_disconnectall();
			kernel_exec_rpc_data_destroy(data);
			THROW(E_EXIT_THREAD, status);
		}
		FINALLY_DECREF_UNLIKELY(data);

		/* Wait for the main thread to send back an error, or terminate  our
		 * thread by use of an E_EXIT_THREAD-RPC (the later being the result
		 * of a successful exec())
		 *
		 * NOTE: We block all signals except for `SIGKILL' and `SIGSTOP' */
#ifdef NDEBUG
		task_waitfor_with_sigmask(&sigmask_full);
#else /* NDEBUG */
		{
			struct sig *recv;
			recv = task_waitfor_with_sigmask(&sigmask_full);
			assert(recv == &data->er_error);
		}
#endif /* !NDEBUG */

		/* We only get here if the exec failed, in which case  the
		 * proper error will have been stored in `data->er_except' */
		memcpy(except_data(), &data->er_except, sizeof(data->er_except));
	} /* Scope... */

	/* Throw the exception returned by the main thread. */
	except_throw_current();
}

#ifdef __ARCH_WANT_SYSCALL_EXECVEAT
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_execveat_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Actually service the exec() system call. */
	ctx->rc_state = kernel_execveat((fd_t)ctx->rc_scinfo.rsi_regs[0],
	                                (USER UNCHECKED char const *)ctx->rc_scinfo.rsi_regs[1],
	                                (KERNEL_EXECVEAT_ARGV_TYPE)ctx->rc_scinfo.rsi_regs[2],
	                                (KERNEL_EXECVEAT_ENVP_TYPE)ctx->rc_scinfo.rsi_regs[3],
	                                (atflag_t)ctx->rc_scinfo.rsi_regs[4],
	                                IF_ARCH_HAVE_COMPAT(false,)
	                                ctx->rc_state);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL5(errno_t, execveat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED char const *USER UNCHECKED const *, argv,
                USER UNCHECKED char const *USER UNCHECKED const *, envp,
                atflag_t, atflags) {
	(void)dirfd;
	(void)filename;
	(void)argv;
	(void)envp;
	(void)atflags;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_execveat_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_EXECVEAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_EXECVEAT
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
compat_sys_execveat_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Actually service the exec() system call. */
	ctx->rc_state = kernel_execveat((fd_t)ctx->rc_scinfo.rsi_regs[0],
	                                (USER UNCHECKED char const *)ctx->rc_scinfo.rsi_regs[1],
	                                (USER UNCHECKED void const *)ctx->rc_scinfo.rsi_regs[2],
	                                (USER UNCHECKED void const *)ctx->rc_scinfo.rsi_regs[3],
	                                (atflag_t)ctx->rc_scinfo.rsi_regs[4],
	                                true,
	                                ctx->rc_state);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL5(errno_t, execveat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED compat_ptr(char const) USER UNCHECKED const *, argv,
                       USER UNCHECKED compat_ptr(char const) USER UNCHECKED const *, envp,
                       atflag_t, atflags) {
	(void)dirfd;
	(void)filename;
	(void)argv;
	(void)envp;
	(void)atflags;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&compat_sys_execveat_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_EXECVEAT */

#ifdef __ARCH_WANT_SYSCALL_EXECVE
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
sys_execve_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Actually service the exec() system call. */
	ctx->rc_state = kernel_execveat(AT_FDCWD,
	                                (USER UNCHECKED char const *)ctx->rc_scinfo.rsi_regs[0],
	                                (KERNEL_EXECVEAT_ARGV_TYPE)ctx->rc_scinfo.rsi_regs[1],
	                                (KERNEL_EXECVEAT_ENVP_TYPE)ctx->rc_scinfo.rsi_regs[2],
	                                0, IF_ARCH_HAVE_COMPAT(false,) ctx->rc_state);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_SYSCALL3(errno_t, execve,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED char const *USER UNCHECKED const *, argv,
                USER UNCHECKED char const *USER UNCHECKED const *, envp) {
	(void)filename;
	(void)argv;
	(void)envp;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&sys_execve_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_SYSCALL_EXECVE */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_EXECVE
PRIVATE NONNULL((1)) void PRPC_EXEC_CALLBACK_CC
compat_sys_execve_rpc(struct rpc_context *__restrict ctx, void *UNUSED(cookie)) {
	if (ctx->rc_context != RPC_REASONCTX_SYSCALL)
		return;

	/* Actually service the exec() system call. */
	ctx->rc_state = kernel_execveat(AT_FDCWD,
	                                (USER UNCHECKED char const *)ctx->rc_scinfo.rsi_regs[0],
	                                (KERNEL_EXECVEAT_ARGV_TYPE)ctx->rc_scinfo.rsi_regs[1],
	                                (KERNEL_EXECVEAT_ENVP_TYPE)ctx->rc_scinfo.rsi_regs[2],
	                                0,
	                                true,
	                                ctx->rc_state);

	/* Indicate that the system call has completed; further RPCs should never try to restart it! */
	ctx->rc_context = RPC_REASONCTX_SYSRET;
}

DEFINE_COMPAT_SYSCALL3(errno_t, execve,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED compat_ptr(char const) USER UNCHECKED const *, argv,
                       USER UNCHECKED compat_ptr(char const) USER UNCHECKED const *, envp) {
	(void)filename;
	(void)argv;
	(void)envp;

	/* Send an RPC to ourselves, so we can gain access to the user-space register state. */
	task_rpc_userunwind(&compat_sys_execve_rpc, NULL);
	__builtin_unreachable();
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_EXECVE */




/************************************************************************/
/* getdrives()                                                          */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETDRIVES
DEFINE_SYSCALL0(syscall_slong_t, getdrives) {
	unsigned int i;
	syscall_ulong_t mask, result = 0;
	struct vfs *myvfs = THIS_VFS;
	vfs_driveslock_read(myvfs);
	for (i = 0, mask = 1; i < VFS_DRIVECOUNT; ++i, mask <<= 1) {
		if (myvfs->vf_drives[i] != NULL)
			result |= mask;
	}
	vfs_driveslock_endread(myvfs);
	return result;
}
#endif /* __ARCH_WANT_SYSCALL_GETDRIVES */




/************************************************************************/
/* fstatfs(), fstatfs64(), statfs(), statfs64()                         */
/************************************************************************/
typedef struct statfs32 struct_statfs32;
typedef struct statfs64 struct_statfs64;
#undef statfs32
#undef statfs64

#ifdef __ARCH_WANT_SYSCALL_FSTATFS
DEFINE_SYSCALL2(errno_t, fstatfs, fd_t, fd,
                USER UNCHECKED struct_statfs32 *, result) {
	REF struct fsuper *super;
#ifndef _STATFS_MATCHES_STATFS64
	struct statfs data;
#endif /* !_STATFS_MATCHES_STATFS64 */
	validate_writable(result, sizeof(*result));
	super = handles_lookupfsuper_relaxed(fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
#ifdef _STATFS_MATCHES_STATFS64
		fsuper_statfs(super, result);
#else /* _STATFS_MATCHES_STATFS64 */
		fsuper_statfs(super, &data);
#endif /* !_STATFS_MATCHES_STATFS64 */
	}
	COMPILER_WRITE_BARRIER();
#ifndef _STATFS_MATCHES_STATFS64
	statfs_to_statfs32(&data, result);
#endif /* !_STATFS_MATCHES_STATFS64 */
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSTATFS */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FSTATFS
DEFINE_COMPAT_SYSCALL2(errno_t, fstatfs, fd_t, fd,
                       USER UNCHECKED struct compat_statfs32 *, result) {
	REF struct fsuper *super;
	struct statfs data;
	validate_writable(result, sizeof(*result));
	super = handles_lookupfsuper_relaxed(fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
		fsuper_statfs(super, &data);
	}
	COMPILER_WRITE_BARRIER();
	statfs_to_compat_statfs32(&data, result);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTATFS */

#ifdef __ARCH_WANT_SYSCALL_FSTATFS64
DEFINE_SYSCALL2(errno_t, fstatfs64, fd_t, fd,
                USER UNCHECKED struct_statfs64 *, result) {
	REF struct fsuper *super;
	validate_writable(result, sizeof(*result));
	super = handles_lookupfsuper_relaxed(fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
#ifdef __USE_FILE_OFFSET64
		fsuper_statfs(super, result);
#else /* __USE_FILE_OFFSET64 */
		{
			struct statfs data;
			fsuper_statfs(super, &data);
			statfs_to_statfs64(&data, result);
		}
#endif /* !__USE_FILE_OFFSET64 */
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSTATFS64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FSTATFS64
DEFINE_COMPAT_SYSCALL2(errno_t, fstatfs64, fd_t, fd,
                       USER UNCHECKED struct compat_statfs64 *, result) {
	REF struct fsuper *super;
	struct statfs data;
	validate_writable(result, sizeof(*result));
	super = handles_lookupfsuper_relaxed(fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
		fsuper_statfs(super, &data);
	}
	COMPILER_WRITE_BARRIER();
	statfs_to_compat_statfs64(&data, result);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTATFS64 */

PRIVATE REF struct fsuper *KCALL
get_super_from_path(USER CHECKED char const *filename) {
	REF struct fnode *node;
	REF struct fsuper *result;
	/* Traverse the given path in its entirety. */
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	result = incref(node->fn_super);
	decref_unlikely(node);
	return result;
}

#ifdef __ARCH_WANT_SYSCALL_STATFS
DEFINE_SYSCALL2(errno_t, statfs,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct_statfs32 *, result) {
	REF struct fsuper *super;
#ifndef _STATFS_MATCHES_STATFS64
	struct statfs data;
#endif /* !_STATFS_MATCHES_STATFS64 */
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_super_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
#ifdef _STATFS_MATCHES_STATFS64
		fsuper_statfs(super, result);
#else /* _STATFS_MATCHES_STATFS64 */
		fsuper_statfs(super, &data);
#endif /* !_STATFS_MATCHES_STATFS64 */
	}
	COMPILER_WRITE_BARRIER();
#ifndef _STATFS_MATCHES_STATFS64
	statfs_to_statfs32(&data, result);
#endif /* !_STATFS_MATCHES_STATFS64 */
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_STATFS */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_STATFS
DEFINE_COMPAT_SYSCALL2(errno_t, statfs,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_statfs32 *, result) {
	REF struct fsuper *super;
	struct statfs data;
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_super_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
		fsuper_statfs(super, &data);
	}
	COMPILER_WRITE_BARRIER();
	statfs_to_compat_statfs32(&data, result);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_STATFS */

#ifdef __ARCH_WANT_SYSCALL_STATFS64
DEFINE_SYSCALL2(errno_t, statfs64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct_statfs64 *, result) {
	REF struct fsuper *super;
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_super_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
		fsuper_statfs(super, result);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_STATFS64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_STATFS64
DEFINE_COMPAT_SYSCALL2(errno_t, statfs64,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_statfs64 *, result) {
	struct statfs st;
	REF struct fsuper *super;
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_super_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
		fsuper_statfs(super, &st);
	}
	statfs_to_compat_statfs64(&st, result);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_STATFS64 */




/************************************************************************/
/* UTIME helper functions                                               */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_UTIME) ||                   \
     defined(__ARCH_WANT_SYSCALL_UTIME64) ||                 \
     defined(__ARCH_WANT_SYSCALL_UTIME_TIME64) ||            \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIME) ||            \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIME64) ||          \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIME_TIME64) ||     \
     defined(__ARCH_WANT_SYSCALL_UTIMES) ||                  \
     defined(__ARCH_WANT_SYSCALL_UTIMES64) ||                \
     defined(__ARCH_WANT_SYSCALL_UTIMES_TIME64) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMES) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMES64) ||         \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMES_TIME64) ||    \
     defined(__ARCH_WANT_SYSCALL_FUTIMESAT) ||               \
     defined(__ARCH_WANT_SYSCALL_FUTIMESAT64) ||             \
     defined(__ARCH_WANT_SYSCALL_FUTIMESAT_TIME64) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT64) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT_TIME64) || \
     defined(__ARCH_WANT_SYSCALL_UTIMENSAT) ||               \
     defined(__ARCH_WANT_SYSCALL_UTIMENSAT64) ||             \
     defined(__ARCH_WANT_SYSCALL_UTIMENSAT_TIME64) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT) ||        \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64) ||      \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT_TIME64))
/* Verify that the calling thread is allowed to assign  arbitrary
 * timestamp to the given `node's last-accessed and last-modified
 * fields. */
PRIVATE NONNULL((1)) void KCALL
fnode_request_arbitrary_timestamps(struct fnode *__restrict node)
		THROWS(E_INSUFFICIENT_RIGHTS) {
	/* Caller must be owner, or have `CAP_FOWNER' */
	if (fnode_getuid(node) != cred_getfsuid())
		require(CAP_FOWNER); /* FIXME: This fails with EACCES, but POSIX wants EPERM... */
}

PRIVATE NONNULL((1)) void KCALL
fnode_request_current_timestamps(struct fnode *__restrict node)
		THROWS(E_FSERROR_ACCESS_DENIED) {
	/* Caller must be owner, or have `CAP_DAC_OVERRIDE' or `CAP_FOWNER' */
	if (!fnode_mayaccess(node, W_OK) && !capable(CAP_DAC_OVERRIDE))
		THROW(E_FSERROR_ACCESS_DENIED);
}
#endif /* ... */




/************************************************************************/
/* utime(), utime64()                                                   */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_UTIME
DEFINE_SYSCALL2(errno_t, utime,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct utimbuf32 const *, times) {
	struct timespec atm, mtm;
	REF struct fnode *node;
	validate_readable(filename, 1);
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, sizeof(*times));
		atm.tv_sec  = (time_t)times->actime;
		atm.tv_nsec = 0;
		mtm.tv_sec  = (time_t)times->modtime;
		mtm.tv_nsec = 0;
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIME
DEFINE_COMPAT_SYSCALL2(errno_t, utime,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_utimbuf32 const *, times) {
	struct timespec atm, mtm;
	REF struct fnode *node;
	compat_validate_readable(filename, 1);
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, sizeof(*times));
		atm.tv_sec  = (time_t)times->actime;
		atm.tv_nsec = 0;
		mtm.tv_sec  = (time_t)times->modtime;
		mtm.tv_nsec = 0;
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		if (!capable(CAP_DAC_OVERRIDE))
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UTIME */

#if (defined(__ARCH_WANT_SYSCALL_UTIME64) || \
     defined(__ARCH_WANT_SYSCALL_UTIME_TIME64))
#ifdef __ARCH_WANT_SYSCALL_UTIME64
DEFINE_SYSCALL2(errno_t, utime64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct utimbuf64 const *, times)
#else /* __ARCH_WANT_SYSCALL_UTIME64 */
DEFINE_SYSCALL2(errno_t, utime_time64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct utimbuf64 const *, times)
#endif /* !__ARCH_WANT_SYSCALL_UTIME64 */
{
	struct timespec atm, mtm;
	REF struct fnode *node;
	validate_readable(filename, 1);
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, sizeof(*times));
		atm.tv_sec  = (time_t)times->actime;
		atm.tv_nsec = 0;
		mtm.tv_sec  = (time_t)times->modtime;
		mtm.tv_nsec = 0;
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIME64 || __ARCH_WANT_SYSCALL_UTIME_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_UTIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIME_TIME64))
DEFINE_COMPAT_SYSCALL2(errno_t, utime64,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_utimbuf64 const *, times) {
	struct timespec atm, mtm;
	REF struct fnode *node;
	compat_validate_readable(filename, 1);
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, sizeof(*times));
		atm.tv_sec  = (time_t)times->actime;
		atm.tv_nsec = 0;
		mtm.tv_sec  = (time_t)times->modtime;
		mtm.tv_nsec = 0;
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UTIME64 || __ARCH_WANT_COMPAT_SYSCALL_UTIME_TIME64 */




/************************************************************************/
/* utimes(), utimes64()                                                 */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_UTIMES
DEFINE_SYSCALL2(errno_t, utimes,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timeval32 const *, times) {
	struct timespec atm, mtm;
	REF struct fnode *node;
	validate_readable(filename, 1);
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIMES */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIMES
DEFINE_COMPAT_SYSCALL2(errno_t, utimes,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timeval32 const *, times) {
	struct timespec atm, mtm;
	REF struct fnode *node;
	compat_validate_readable(filename, 1);
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UTIMES */

#if (defined(__ARCH_WANT_SYSCALL_UTIMES64) || \
     defined(__ARCH_WANT_SYSCALL_UTIMES_TIME64))
#ifdef __ARCH_WANT_SYSCALL_UTIMES64
DEFINE_SYSCALL2(errno_t, utimes64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timeval64 const *, times)
#else /* __ARCH_WANT_SYSCALL_UTIMES64 */
DEFINE_SYSCALL2(errno_t, utimes_time64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timeval64 const *, times)
#endif /* !__ARCH_WANT_SYSCALL_UTIMES64 */
{
	struct timespec atm, mtm;
	REF struct fnode *node;
	validate_readable(filename, 1);
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIMES64 || __ARCH_WANT_SYSCALL_UTIMES_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMES64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMES_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIMES64
DEFINE_COMPAT_SYSCALL2(errno_t, utimes64,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timeval64 const *, times)
#else /* __ARCH_WANT_COMPAT_SYSCALL_UTIMES64 */
DEFINE_COMPAT_SYSCALL2(errno_t, utimes_time64,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timeval64 const *, times)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_UTIMES64 */
{
	struct timespec atm, mtm;
	REF struct fnode *node;
	compat_validate_readable(filename, 1);
	node = path_traversefull(AT_FDCWD, filename, fs_atflags(0));
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UTIMES64 || __ARCH_WANT_COMPAT_SYSCALL_UTIMES_TIME64 */




/************************************************************************/
/* futimesat(), futimesat64()                                           */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_FUTIMESAT) ||          \
     defined(__ARCH_WANT_SYSCALL_FUTIMESAT64) ||        \
     defined(__ARCH_WANT_SYSCALL_FUTIMESAT_TIME64) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT_TIME64))
PRIVATE ATTR_RETNONNULL WUNUSED REF struct fnode *KCALL
lookup_inode_for_futimesat(fd_t dirfd, USER UNCHECKED char const *filename) {
	REF struct fnode *result;
	if (filename) {
		validate_readable(filename, 1);
		result = path_traversefull(dirfd, filename, fs_atflags(0));
	} else {
		result = handles_lookupfnode(dirfd);
	}
	return result;
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_FUTIMESAT
DEFINE_SYSCALL3(errno_t, futimesat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timeval32 const *, times) {
	struct timespec atm, mtm;
	REF struct fnode *node;
	validate_readable(filename, 1);
	node = lookup_inode_for_futimesat(dirfd, filename);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FUTIMESAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT
DEFINE_COMPAT_SYSCALL3(errno_t, futimesat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timeval32 const *, times) {
	struct timespec atm, mtm;
	REF struct fnode *node;
	node = lookup_inode_for_futimesat(dirfd, filename);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT */

#if (defined(__ARCH_WANT_SYSCALL_FUTIMESAT64) || \
     defined(__ARCH_WANT_SYSCALL_FUTIMESAT_TIME64))
#ifdef __ARCH_WANT_SYSCALL_FUTIMESAT64
DEFINE_SYSCALL3(errno_t, futimesat64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timeval64 const *, times)
#else /* __ARCH_WANT_SYSCALL_FUTIMESAT64 */
DEFINE_SYSCALL3(errno_t, futimesat_time64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timeval64 const *, times)
#endif /* !__ARCH_WANT_SYSCALL_FUTIMESAT64 */
{
	struct timespec atm, mtm;
	REF struct fnode *node;
	node = lookup_inode_for_futimesat(dirfd, filename);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FUTIMESAT64 || __ARCH_WANT_SYSCALL_FUTIMESAT_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT64
DEFINE_COMPAT_SYSCALL3(errno_t, futimesat64, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timeval64 const *, times)
#else /* __ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT64 */
DEFINE_COMPAT_SYSCALL3(errno_t, futimesat_time64, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timeval64 const *, times)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT64 */
{
	struct timespec atm, mtm;
	REF struct fnode *node;
	node = lookup_inode_for_futimesat(dirfd, filename);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	mfile_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT64 || __ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT_TIME64 */




/************************************************************************/
/* utimensat(), utimensat64()                                           */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_UTIMENSAT) ||          \
     defined(__ARCH_WANT_SYSCALL_UTIMENSAT64) ||        \
     defined(__ARCH_WANT_SYSCALL_UTIMENSAT_TIME64) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT_TIME64))
PRIVATE ATTR_RETNONNULL WUNUSED REF struct fnode *KCALL
lookup_inode_for_utimensat(fd_t dirfd, USER UNCHECKED char const *filename,
                           atflag_t atflags) {
	REF struct fnode *result;
	if (filename) {
		VALIDATE_FLAGSET(atflags,
		                 AT_SYMLINK_NOFOLLOW | AT_CHANGE_BTIME | AT_DOSPATH,
		                 E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS);
		validate_readable(filename, 1);
		atflags = fs_atflags(atflags);
		result  = path_traversefull(dirfd, filename, atflags);
	} else {
		VALIDATE_FLAGSET(atflags, AT_CHANGE_BTIME,
		                 E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS_NOFILENAME);
		result = handles_lookupfnode(dirfd);
	}
	return result;
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_UTIMENSAT
DEFINE_SYSCALL4(errno_t, utimensat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timespec32 const *, times,
                atflag_t, atflags) {
	struct timespec atm, mtm, btm;
	struct timespec *patm, *pmtm;
	struct timespec *pbtm = NULL;
	REF struct fnode *node;
	node = lookup_inode_for_utimensat(dirfd, filename, atflags);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		atm.tv_sec  = (time_t)times[0].tv_sec;
		atm.tv_nsec = (syscall_ulong_t)times[0].tv_nsec;
		mtm.tv_sec  = (time_t)times[1].tv_sec;
		mtm.tv_nsec = (syscall_ulong_t)times[1].tv_nsec;
		if unlikely(atflags & AT_CHANGE_BTIME) {
			btm.tv_sec  = (time_t)times[2].tv_sec;
			btm.tv_nsec = (syscall_ulong_t)times[2].tv_nsec;
			/* Specify BTIME as OMIT is the same as not passing `AT_CHANGE_BTIME'! */
			if (btm.tv_nsec != UTIME_OMIT) {
				require(CAP_AT_CHANGE_BTIME);
				pbtm = &btm;
			}
		}
		COMPILER_READ_BARRIER();
		if (atm.tv_nsec == UTIME_OMIT)
			patm = NULL;
		if (mtm.tv_nsec == UTIME_OMIT)
			pmtm = NULL;
		/* Deal with the case where at least one of the
		 * timestamp should be set to the current time. */
		if (atm.tv_nsec == UTIME_NOW || mtm.tv_nsec == UTIME_NOW ||
		    (pbtm && pbtm->tv_nsec == UTIME_NOW)) {
			struct timespec now;
			/* Special case: Less permissions are needed to do a touch! */
			if (atm.tv_nsec == UTIME_NOW &&
			    mtm.tv_nsec == UTIME_NOW && !pbtm)
				goto do_touch;
			now = realtime();
			if (atm.tv_nsec == UTIME_NOW)
				atm = now;
			if (mtm.tv_nsec == UTIME_NOW)
				mtm = now;
			if (pbtm && pbtm->tv_nsec == UTIME_NOW)
				*pbtm = now;
		}
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
do_touch:
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
		patm = &atm;
		pmtm = &mtm;
	}
	mfile_chtime(node, patm, pmtm, pbtm);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIMENSAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT
DEFINE_COMPAT_SYSCALL4(errno_t, utimensat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timespec32 const *, times,
                       atflag_t, atflags) {
	struct timespec atm, mtm, btm;
	struct timespec *patm, *pmtm;
	struct timespec *pbtm = NULL;
	REF struct fnode *node;
	node = lookup_inode_for_utimensat(dirfd, filename, atflags);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		atm.tv_sec  = (time_t)times[0].tv_sec;
		atm.tv_nsec = (syscall_ulong_t)times[0].tv_nsec;
		mtm.tv_sec  = (time_t)times[1].tv_sec;
		mtm.tv_nsec = (syscall_ulong_t)times[1].tv_nsec;
		if unlikely(atflags & AT_CHANGE_BTIME) {
			btm.tv_sec  = (time_t)times[2].tv_sec;
			btm.tv_nsec = (syscall_ulong_t)times[2].tv_nsec;
			/* Specify BTIME as OMIT is the same as not passing `AT_CHANGE_BTIME'! */
			if (btm.tv_nsec != UTIME_OMIT) {
				require(CAP_AT_CHANGE_BTIME);
				pbtm = &btm;
			}
		}
		COMPILER_READ_BARRIER();
		if (atm.tv_nsec == UTIME_OMIT)
			patm = NULL;
		if (mtm.tv_nsec == UTIME_OMIT)
			pmtm = NULL;
		/* Deal with the case where at least one of the
		 * timestamp should be set to the current time. */
		if (atm.tv_nsec == UTIME_NOW || mtm.tv_nsec == UTIME_NOW ||
		    (pbtm && pbtm->tv_nsec == UTIME_NOW)) {
			struct timespec now;
			/* Special case: Less permissions are needed to do a touch! */
			if (atm.tv_nsec == UTIME_NOW &&
			    mtm.tv_nsec == UTIME_NOW && !pbtm)
				goto do_touch;
			now = realtime();
			if (atm.tv_nsec == UTIME_NOW)
				atm = now;
			if (mtm.tv_nsec == UTIME_NOW)
				mtm = now;
			if (pbtm && pbtm->tv_nsec == UTIME_NOW)
				*pbtm = now;
		}
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
do_touch:
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
		patm = &atm;
		pmtm = &mtm;
	}
	mfile_chtime(node, patm, pmtm, pbtm);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT */

#if (defined(__ARCH_WANT_SYSCALL_UTIMENSAT64) || \
     defined(__ARCH_WANT_SYSCALL_UTIMENSAT_TIME64))
#ifdef __ARCH_WANT_SYSCALL_UTIMENSAT64
DEFINE_SYSCALL4(errno_t, utimensat64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timespec64 const *, times,
                atflag_t, atflags)
#else /* __ARCH_WANT_SYSCALL_UTIMENSAT64 */
DEFINE_SYSCALL4(errno_t, utimensat_time64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timespec64 const *, times,
                atflag_t, atflags)
#endif /* !__ARCH_WANT_SYSCALL_UTIMENSAT64 */
{
	struct timespec atm, mtm, btm;
	struct timespec *patm, *pmtm;
	struct timespec *pbtm = NULL;
	REF struct fnode *node;
	node = lookup_inode_for_utimensat(dirfd, filename, atflags);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		atm.tv_sec  = (time_t)times[0].tv_sec;
		atm.tv_nsec = (syscall_ulong_t)times[0].tv_nsec;
		mtm.tv_sec  = (time_t)times[1].tv_sec;
		mtm.tv_nsec = (syscall_ulong_t)times[1].tv_nsec;
		if unlikely(atflags & AT_CHANGE_BTIME) {
			btm.tv_sec  = (time_t)times[2].tv_sec;
			btm.tv_nsec = (syscall_ulong_t)times[2].tv_nsec;
			/* Specify BTIME as OMIT is the same as not passing `AT_CHANGE_BTIME'! */
			if (btm.tv_nsec != UTIME_OMIT) {
				require(CAP_AT_CHANGE_BTIME);
				pbtm = &btm;
			}
		}
		COMPILER_READ_BARRIER();
		if (atm.tv_nsec == UTIME_OMIT)
			patm = NULL;
		if (mtm.tv_nsec == UTIME_OMIT)
			pmtm = NULL;
		/* Deal with the case where at least one of the
		 * timestamp should be set to the current time. */
		if (atm.tv_nsec == UTIME_NOW || mtm.tv_nsec == UTIME_NOW ||
		    (pbtm && pbtm->tv_nsec == UTIME_NOW)) {
			struct timespec now;
			/* Special case: Less permissions are needed to do a touch! */
			if (atm.tv_nsec == UTIME_NOW &&
			    mtm.tv_nsec == UTIME_NOW && !pbtm)
				goto do_touch;
			now = realtime();
			if (atm.tv_nsec == UTIME_NOW)
				atm = now;
			if (mtm.tv_nsec == UTIME_NOW)
				mtm = now;
			if (pbtm && pbtm->tv_nsec == UTIME_NOW)
				*pbtm = now;
		}
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
do_touch:
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
		patm = &atm;
		pmtm = &mtm;
	}
	mfile_chtime(node, patm, pmtm, pbtm);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIMENSAT64 || __ARCH_WANT_SYSCALL_UTIMENSAT_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64
DEFINE_COMPAT_SYSCALL4(errno_t, utimensat64, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timespec64 const *, times,
                       atflag_t, atflags)
#else /* __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64 */
DEFINE_COMPAT_SYSCALL4(errno_t, utimensat_time64, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timespec64 const *, times,
                       atflag_t, atflags)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64 */
{
	struct timespec atm, mtm, btm;
	struct timespec *patm, *pmtm;
	struct timespec *pbtm = NULL;
	REF struct fnode *node;
	node = lookup_inode_for_utimensat(dirfd, filename, atflags);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		atm.tv_sec  = (time_t)times[0].tv_sec;
		atm.tv_nsec = (syscall_ulong_t)times[0].tv_nsec;
		mtm.tv_sec  = (time_t)times[1].tv_sec;
		mtm.tv_nsec = (syscall_ulong_t)times[1].tv_nsec;
		if unlikely(atflags & AT_CHANGE_BTIME) {
			btm.tv_sec  = (time_t)times[2].tv_sec;
			btm.tv_nsec = (syscall_ulong_t)times[2].tv_nsec;
			/* Specify BTIME as OMIT is the same as not passing `AT_CHANGE_BTIME'! */
			if (btm.tv_nsec != UTIME_OMIT) {
				require(CAP_AT_CHANGE_BTIME);
				pbtm = &btm;
			}
		}
		COMPILER_READ_BARRIER();
		if (atm.tv_nsec == UTIME_OMIT)
			patm = NULL;
		if (mtm.tv_nsec == UTIME_OMIT)
			pmtm = NULL;
		/* Deal with the case where at least one of the
		 * timestamp should be set to the current time. */
		if (atm.tv_nsec == UTIME_NOW || mtm.tv_nsec == UTIME_NOW ||
		    (pbtm && pbtm->tv_nsec == UTIME_NOW)) {
			struct timespec now;
			/* Special case: Less permissions are needed to do a touch! */
			if (atm.tv_nsec == UTIME_NOW &&
			    mtm.tv_nsec == UTIME_NOW && !pbtm)
				goto do_touch;
			now = realtime();
			if (atm.tv_nsec == UTIME_NOW)
				atm = now;
			if (mtm.tv_nsec == UTIME_NOW)
				mtm = now;
			if (pbtm && pbtm->tv_nsec == UTIME_NOW)
				*pbtm = now;
		}
		fnode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
do_touch:
		fnode_request_current_timestamps(node);
		atm = mtm = realtime();
		patm = &atm;
		pmtm = &mtm;
	}
	mfile_chtime(node, patm, pmtm, pbtm);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64 || __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT_TIME64 */


DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_SYSCALLS_C */
