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
#ifndef GUARD_KERNEL_CORE_FS_SYSCALLS_C
#define GUARD_KERNEL_CORE_FS_SYSCALLS_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _LARGEFILE64_SOURCE 1
#define _TIME64_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <dev/ttybase.h>
#include <fs/fifo.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/ramfs.h>
#include <fs/special-node.h>
#include <fs/vfs.h>
#include <kernel/debugtrap.h>
#include <kernel/except.h>
#include <kernel/execabi.h>
#include <kernel/handle.h>
#include <kernel/mman.h>
#include <kernel/mman/event.h>
#include <kernel/mman/exec.h>
#include <kernel/personality.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cpu.h>
#include <sched/cred.h>
#include <sched/except-handler.h>
#include <sched/pid.h>
#include <sched/posix-signal.h>
#include <sched/rpc.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <bits/os/statfs-convert.h>
#include <bits/os/statfs.h>
#include <compat/config.h>
#include <kos/debugtrap.h>
#include <kos/except/reason/inval.h>
#include <kos/kernel/handle.h>
#include <sys/mount.h>
#include <sys/statfs.h>
#include <sys/time.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <format-printer.h>
#include <malloca.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <librpc/rpc.h>

#ifdef __ARCH_HAVE_COMPAT
#include <compat/bits/os/stat-convert.h>
#include <compat/bits/os/stat.h>
#include <compat/bits/os/statfs-convert.h>
#include <compat/bits/os/statfs.h>
#include <compat/bits/os/timespec.h>
#include <compat/bits/os/timeval.h>
#include <compat/bits/os/utimbuf.h>
#include <compat/pointer.h>
#endif /* __ARCH_HAVE_COMPAT */

#if (defined(__ARCH_WANT_SYSCALL_OLDFSTATAT) ||        \
     defined(__ARCH_WANT_SYSCALL_OLDFSTAT) ||          \
     defined(__ARCH_WANT_SYSCALL_OLDLSTAT) ||          \
     defined(__ARCH_WANT_SYSCALL_OLDSTAT) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_OLDFSTATAT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_OLDFSTAT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_OLDLSTAT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_OLDSTAT))
#define WANT_LINUX_OLDSTAT 1
#endif /* linux_oldstat()... */

#if (defined(__ARCH_WANT_SYSCALL_FSTATAT) ||        \
     defined(__ARCH_WANT_SYSCALL_FSTAT) ||          \
     defined(__ARCH_WANT_SYSCALL_LSTAT) ||          \
     defined(__ARCH_WANT_SYSCALL_STAT) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FSTATAT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FSTAT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_LSTAT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_STAT))
#define WANT_LINUX_STAT 1
#endif /* linux_stat()... */

#if (defined(__ARCH_WANT_SYSCALL_FSTATAT64) ||        \
     defined(__ARCH_WANT_SYSCALL_FSTAT64) ||          \
     defined(__ARCH_WANT_SYSCALL_LSTAT64) ||          \
     defined(__ARCH_WANT_SYSCALL_STAT64) ||           \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FSTATAT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_FSTAT64) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_LSTAT64) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_STAT64))
#define WANT_LINUX_STAT64 1
#endif /* linux_stat64()... */

#if (defined(WANT_LINUX_OLDSTAT) || \
     defined(WANT_LINUX_STAT) ||    \
     defined(WANT_LINUX_STAT64))
#include <kos/compat/linux-stat-convert.h>
#include <kos/compat/linux-stat.h>
#ifdef __ARCH_HAVE_COMPAT
#include <compat/kos/compat/linux-stat-convert.h>
#include <compat/kos/compat/linux-stat.h>
#endif /* __ARCH_HAVE_COMPAT */
#endif /* linux_stat... */


DECL_BEGIN

/* Ensure that AT_* flags map onto the correct FS_MODE_* flags. */
STATIC_ASSERT(AT_SYMLINK_NOFOLLOW == FS_MODE_FSYMLINK_NOFOLLOW);
STATIC_ASSERT(AT_NO_AUTOMOUNT == FS_MODE_FNO_AUTOMOUNT);
STATIC_ASSERT(AT_EMPTY_PATH == FS_MODE_FEMPTY_PATH);
STATIC_ASSERT(AT_SYMLINK_REGULAR == FS_MODE_FSYMLINK_REGULAR);
STATIC_ASSERT(AT_DOSPATH == FS_MODE_FDOSPATH);

STATIC_ASSERT((unsigned int)AT_FDCWD == (unsigned int)HANDLE_SYMBOLIC_FDCWD);
STATIC_ASSERT((unsigned int)AT_FDROOT == (unsigned int)HANDLE_SYMBOLIC_FDROOT);
STATIC_ASSERT((unsigned int)AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN) == (unsigned int)HANDLE_SYMBOLIC_DDRIVECWD(HANDLE_SYMBOLIC_DDRIVEMIN));
STATIC_ASSERT((unsigned int)AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX) == (unsigned int)HANDLE_SYMBOLIC_DDRIVECWD(HANDLE_SYMBOLIC_DDRIVEMAX));
STATIC_ASSERT((unsigned int)AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN) == (unsigned int)HANDLE_SYMBOLIC_DDRIVEROOT(HANDLE_SYMBOLIC_DDRIVEMIN));
STATIC_ASSERT((unsigned int)AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX) == (unsigned int)HANDLE_SYMBOLIC_DDRIVEROOT(HANDLE_SYMBOLIC_DDRIVEMAX));
STATIC_ASSERT(AT_DOS_DRIVEMIN == HANDLE_SYMBOLIC_DDRIVEMIN);
STATIC_ASSERT(AT_DOS_DRIVEMAX == HANDLE_SYMBOLIC_DDRIVEMAX);






/************************************************************************/
/* faccessat(), access()                                                */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FACCESSAT
DEFINE_SYSCALL4(errno_t, faccessat,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                syscall_ulong_t, type, atflag_t, flags) {
	REF struct inode *accessed_inode;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
	validate_readable(filename, 1);
	VALIDATE_FLAGSET(type, F_OK | R_OK | W_OK | X_OK,
	                 E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_TYPE);
	VALIDATE_FLAGSET(flags, AT_SYMLINK_NOFOLLOW | AT_EACCESS | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FACCESSAT_FLAGS);
	fsmode = fs_getmode_for(f, flags);
	accessed_inode = path_traversefull_at(f,
	                                      (unsigned int)dirfd,
	                                      filename,
	                                      !(flags & AT_SYMLINK_NOFOLLOW),
	                                      fsmode,
	                                      NULL,
	                                      NULL,
	                                      NULL,
	                                      NULL);
	FINALLY_DECREF_UNLIKELY(accessed_inode);
	inode_access(accessed_inode, type);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FACCESSAT */

#ifdef __ARCH_WANT_SYSCALL_ACCESS
DEFINE_SYSCALL2(errno_t, access,
                USER UNCHECKED char const *, filename,
                syscall_ulong_t, type) {
	return sys_faccessat(AT_FDCWD, filename, type, 0);
}
#endif /* __ARCH_WANT_SYSCALL_ACCESS */





/************************************************************************/
/* getcwd()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETCWD
DEFINE_SYSCALL2(ssize_t, getcwd,
                USER UNCHECKED char *, buf, size_t, bufsize) {
	struct fs *f = THIS_FS;
	REF struct path *cwd, *root;
	unsigned int mode;
	size_t reqlen;
	validate_writable(buf, bufsize);
	sync_read(&f->f_pathlock);
	cwd  = incref(f->f_cwd);
	root = incref(f->f_root);
	sync_endread(&f->f_pathlock);
	mode = PATH_PRINT_MODE_INCTRAIL;
#if PATH_PRINT_MODE_DOSPATH == FS_MODE_FDOSPATH
	mode |= ATOMIC_READ(f->f_mode.f_atflag) & PATH_PRINT_MODE_DOSPATH;
#else /* PATH_PRINT_MODE_DOSPATH == FS_MODE_FDOSPATH */
	if (ATOMIC_READ(f->f_mode.f_atflag) & FS_MODE_FDOSPATH)
		mode |= PATH_PRINT_MODE_DOSPATH;
#endif /* PATH_PRINT_MODE_DOSPATH != FS_MODE_FDOSPATH */
	{
		FINALLY_DECREF_UNLIKELY(cwd);
		FINALLY_DECREF_UNLIKELY(root);
		reqlen = path_sprintex(buf, bufsize, cwd, mode, root);
	}
	if unlikely(reqlen > bufsize) /* return -ERANGE; */
		THROW(E_BUFFER_TOO_SMALL, reqlen, bufsize);
	return reqlen;
}
#endif /* __ARCH_WANT_SYSCALL_GETCWD */





/************************************************************************/
/* fmknodat(), mknodat(), mknod()                                       */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FMKNODAT
DEFINE_SYSCALL5(errno_t, fmknodat, fd_t, dirfd,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, __dev_t, dev, atflag_t, flags) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir;
	REF struct inode *result_node;
	fsmode_t fsmode;
	VALIDATE_FLAGSET(flags,
	                 0 | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FMKNODAT_FLAGS);
	fsmode = fs_getmode_for(f, flags);
	validate_readable(nodename, 1);
	mode &= ~ATOMIC_READ(f->f_umask);
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
	p = path_traverse_at_recent(f,
	                            dirfd,
	                            nodename,
	                            &last_seg,
	                            &last_seglen,
	                            fsmode,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		sync_read(p);
		dir = (REF struct directory_node *)incref(p->p_inode);
		sync_endread(p);
	}
	{
		FINALLY_DECREF_UNLIKELY(dir);
		result_node = directory_mknod(dir,
		                              last_seg,
		                              last_seglen,
		                              mode,
		                              fs_getuid(f),
		                              fs_getgid(f),
		                              (dev_t)dev,
		                              fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKNOD_FNOCASE
		                                                        : DIRECTORY_MKNOD_FNORMAL,
		                              NULL);
	}
	decref(result_node);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FMKNODAT */

#ifdef __ARCH_WANT_SYSCALL_MKNODAT
DEFINE_SYSCALL4(errno_t, mknodat, fd_t, dirfd,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, __dev_t, dev) {
	return sys_fmknodat(dirfd, nodename, mode, dev, 0);
}
#endif /* __ARCH_WANT_SYSCALL_MKNODAT */

#ifdef __ARCH_WANT_SYSCALL_MKNOD
DEFINE_SYSCALL3(errno_t, mknod,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, __dev_t, dev) {
	return sys_fmknodat(AT_FDCWD, nodename, mode, dev, 0);
}
#endif /* __ARCH_WANT_SYSCALL_MKNOD */





/************************************************************************/
/* fmkdirat(), mkdirat(), mkdir()                                       */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FMKDIRAT
DEFINE_SYSCALL4(errno_t, fmkdirat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname, mode_t, mode,
                atflag_t, flags) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir, *result_dir;
	fsmode_t fsmode;
	VALIDATE_FLAGSET(flags,
	                 0 | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FMKDIRAT_FLAGS);
	fsmode = fs_getmode_for(f, flags);
	validate_readable(pathname, 1);
	if (has_personality(KP_MKDIR_CHECK_MODE))
		VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE);
	p = path_traverse_at_recent(f,
	                            (unsigned int)dirfd,
	                            pathname,
	                            &last_seg,
	                            &last_seglen,
	                            fsmode | FS_MODE_FIGNORE_TRAILING_SLASHES,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		sync_read(p);
		dir = (REF struct directory_node *)incref(p->p_inode);
		sync_endread(p);
	}
	{
		FINALLY_DECREF_UNLIKELY(dir);
		result_dir = directory_mkdir(dir,
		                             last_seg,
		                             last_seglen,
		                             mode & 07777 & ~ATOMIC_READ(f->f_umask),
		                             fs_getuid(f),
		                             fs_getgid(f),
		                             fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKDIR_FNOCASE
		                                                       : DIRECTORY_MKDIR_FNORMAL,
		                             NULL);
	}
	decref(result_dir);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FMKDIRAT */

#ifdef __ARCH_WANT_SYSCALL_MKDIRAT
DEFINE_SYSCALL3(errno_t, mkdirat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname, mode_t, mode) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir, *result_dir;
	fsmode_t fsmode = ATOMIC_READ(f->f_mode.f_atflag);
	validate_readable(pathname, 1);
	if (has_personality(KP_MKDIR_CHECK_MODE))
		VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE);
	p = path_traverse_at_recent(f,
	                            (unsigned int)dirfd,
	                            pathname,
	                            &last_seg,
	                            &last_seglen,
	                            fsmode | FS_MODE_FIGNORE_TRAILING_SLASHES,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		sync_read(p);
		dir = (REF struct directory_node *)incref(p->p_inode);
		sync_endread(p);
	}
	{
		FINALLY_DECREF_UNLIKELY(dir);
		result_dir = directory_mkdir(dir,
		                             last_seg,
		                             last_seglen,
		                             mode & 07777 & ~ATOMIC_READ(f->f_umask),
		                             fs_getuid(f),
		                             fs_getgid(f),
		                             fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKDIR_FNOCASE
		                                                       : DIRECTORY_MKDIR_FNORMAL,
		                             NULL);
	}
	decref(result_dir);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MKDIRAT */

#ifdef __ARCH_WANT_SYSCALL_MKDIR
DEFINE_SYSCALL2(errno_t, mkdir,
                USER UNCHECKED char const *, pathname, mode_t, mode) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir, *result_dir;
	fsmode_t fsmode = ATOMIC_READ(f->f_mode.f_atflag);
	validate_readable(pathname, 1);
	if (has_personality(KP_MKDIR_CHECK_MODE)) {
		VALIDATE_FLAGSET(mode, 07777,
		                 E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE);
	}
	p = path_traverse_recent(f,
	                         pathname,
	                         &last_seg,
	                         &last_seglen,
	                         fsmode | FS_MODE_FIGNORE_TRAILING_SLASHES,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		sync_read(p);
		dir = (REF struct directory_node *)incref(p->p_inode);
		sync_endread(p);
	}
	{
		FINALLY_DECREF_UNLIKELY(dir);
		result_dir = directory_mkdir(dir,
		                             last_seg,
		                             last_seglen,
		                             mode & 07777 & ~ATOMIC_READ(f->f_umask),
		                             fs_getuid(f),
		                             fs_getgid(f),
		                             fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKDIR_FNOCASE
		                                                       : DIRECTORY_MKDIR_FNORMAL,
		                             NULL);
	}
	decref(result_dir);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MKDIR */





/************************************************************************/
/* unlinkat(), unlink(), rmdir()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_UNLINKAT
DEFINE_SYSCALL3(errno_t, unlinkat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname,
                atflag_t, flags) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	fsmode_t fsmode;
	unsigned int remove_mode;
	validate_readable(pathname, 1);
	VALIDATE_FLAGSET(flags,
	                 AT_REMOVEDIR | AT_REMOVEREG | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_UNLINKAT_FLAGS);
	/* Figure out what should actually be removed. */
	remove_mode = (DIRECTORY_REMOVE_FREGULAR | DIRECTORY_REMOVE_FCHKACCESS);
	if (flags & AT_REMOVEDIR) {
		remove_mode = (DIRECTORY_REMOVE_FDIRECTORY | DIRECTORY_REMOVE_FCHKACCESS);
		/* KOS-extension: Remove either a directory, or a regular file. */
		if (flags & AT_REMOVEREG)
			remove_mode |= DIRECTORY_REMOVE_FREGULAR;
	}
	fsmode = fs_getmode_for(f, flags);
	/* Ignore casing when matching files to be removed whilst in DOS-mode. */
	if (fsmode & FS_MODE_FDOSPATH)
		remove_mode |= DIRECTORY_REMOVE_FNOCASE;
	/* Ignore trailing slashes within the input path when removing directories. */
	if ((remove_mode & (DIRECTORY_REMOVE_FREGULAR | DIRECTORY_REMOVE_FDIRECTORY)) == DIRECTORY_REMOVE_FDIRECTORY)
		fsmode |= FS_MODE_FIGNORE_TRAILING_SLASHES;
	p = path_traverse_at_recent(f,
	                            (unsigned int)dirfd,
	                            pathname,
	                            &last_seg,
	                            &last_seglen,
	                            fsmode,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		path_remove(p,
		            last_seg,
		            last_seglen,
		            directory_entry_hash(last_seg, last_seglen),
		            remove_mode,
		            NULL,
		            NULL,
		            NULL,
		            NULL);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UNLINKAT */

#ifdef __ARCH_WANT_SYSCALL_UNLINK
DEFINE_SYSCALL1(errno_t, unlink, USER UNCHECKED char const *, pathname) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	fsmode_t fsmode;
	unsigned int remove_mode;
	validate_readable(pathname, 1);
	/* Figure out what should actually be removed. */
	remove_mode = (DIRECTORY_REMOVE_FREGULAR | DIRECTORY_REMOVE_FCHKACCESS);
	fsmode      = ATOMIC_READ(f->f_mode.f_atflag);
	/* Ignore casing when matching files to be removed whilst in DOS-mode. */
	if (fsmode & FS_MODE_FDOSPATH)
		remove_mode |= DIRECTORY_REMOVE_FNOCASE;
	p = path_traverse_recent(f,
	                         pathname,
	                         &last_seg,
	                         &last_seglen,
	                         fsmode,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		path_remove(p,
		            last_seg,
		            last_seglen,
		            directory_entry_hash(last_seg, last_seglen),
		            remove_mode,
		            NULL,
		            NULL,
		            NULL,
		            NULL);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UNLINK */

#ifdef __ARCH_WANT_SYSCALL_RMDIR
DEFINE_SYSCALL1(errno_t, rmdir, USER UNCHECKED char const *, pathname) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	fsmode_t fsmode;
	unsigned int remove_mode;
	validate_readable(pathname, 1);
	/* Figure out what should actually be removed. */
	remove_mode = (DIRECTORY_REMOVE_FDIRECTORY | DIRECTORY_REMOVE_FCHKACCESS);
	fsmode      = ATOMIC_READ(f->f_mode.f_atflag) | FS_MODE_FIGNORE_TRAILING_SLASHES;
	/* Ignore casing when matching files to be removed whilst in DOS-mode. */
	if (fsmode & FS_MODE_FDOSPATH)
		remove_mode |= DIRECTORY_REMOVE_FNOCASE;
	p = path_traverse_recent(f,
	                         pathname,
	                         &last_seg,
	                         &last_seglen,
	                         fsmode,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		path_remove(p,
		            last_seg,
		            last_seglen,
		            directory_entry_hash(last_seg, last_seglen),
		            remove_mode,
		            NULL,
		            NULL,
		            NULL,
		            NULL);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_RMDIR */





/************************************************************************/
/* fsymlinkat(), symlinkat(), symlink()                                 */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FSYMLINKAT
DEFINE_SYSCALL4(errno_t, fsymlinkat,
                USER UNCHECKED char const *, link_text, fd_t, target_dirfd,
                USER UNCHECKED char const *, target_path, atflag_t, flags) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir;
	REF struct symlink_node *result_link;
	fsmode_t fsmode;
	VALIDATE_FLAGSET(flags,
	                 0 | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FSYMLINKAT_FLAGS);
	validate_readable(link_text, 1);
	validate_readable(target_path, 1);
	fsmode = fs_getmode_for(f, flags);
	p = path_traverse_at_recent(f,
	                            (unsigned int)target_dirfd,
	                            target_path,
	                            &last_seg,
	                            &last_seglen,
	                            fsmode,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		sync_read(p);
		dir = (REF struct directory_node *)incref(p->p_inode);
		sync_endread(p);
	}
	{
		FINALLY_DECREF_UNLIKELY(dir);
		result_link = directory_symlink(dir,
		                                last_seg,
		                                last_seglen,
		                                link_text,
		                                strlen(link_text),
		                                fs_getuid(f),
		                                fs_getgid(f),
		                                ~ATOMIC_READ(f->f_umask) & 0777,
		                                fsmode & FS_MODE_FDOSPATH ? DIRECTORY_SYMLINK_FNOCASE
		                                                          : DIRECTORY_SYMLINK_FNORMAL,
		                                NULL);
	}
	decref(result_link);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSYMLINKAT */

#ifdef __ARCH_WANT_SYSCALL_SYMLINKAT
DEFINE_SYSCALL3(errno_t, symlinkat,
                USER UNCHECKED char const *, link_text, fd_t, target_dirfd,
                USER UNCHECKED char const *, target_path) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir;
	REF struct symlink_node *result_link;
	fsmode_t fsmode;
	validate_readable(link_text, 1);
	validate_readable(target_path, 1);
	fsmode = ATOMIC_READ(f->f_mode.f_atflag);
	p = path_traverse_at_recent(f,
	                            (unsigned int)target_dirfd,
	                            target_path,
	                            &last_seg,
	                            &last_seglen,
	                            fsmode,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		sync_read(p);
		dir = (REF struct directory_node *)incref(p->p_inode);
		sync_endread(p);
	}
	{
		FINALLY_DECREF_UNLIKELY(dir);
		result_link = directory_symlink(dir,
		                                last_seg,
		                                last_seglen,
		                                link_text,
		                                strlen(link_text),
		                                fs_getuid(f),
		                                fs_getgid(f),
		                                ~ATOMIC_READ(f->f_umask) & 0777,
		                                fsmode & FS_MODE_FDOSPATH ? DIRECTORY_SYMLINK_FNOCASE
		                                                          : DIRECTORY_SYMLINK_FNORMAL,
		                                NULL);
	}
	decref(result_link);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SYMLINKAT */

#ifdef __ARCH_WANT_SYSCALL_SYMLINK
DEFINE_SYSCALL2(errno_t, symlink,
                USER UNCHECKED char const *, link_text,
                USER UNCHECKED char const *, target_path) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir;
	REF struct symlink_node *result_link;
	fsmode_t fsmode;
	validate_readable(link_text, 1);
	validate_readable(target_path, 1);
	fsmode = ATOMIC_READ(f->f_mode.f_atflag);
	p = path_traverse_recent(f,
	                         target_path,
	                         &last_seg,
	                         &last_seglen,
	                         fsmode,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		sync_read(p);
		dir = (REF struct directory_node *)incref(p->p_inode);
		sync_endread(p);
	}
	{
		FINALLY_DECREF_UNLIKELY(dir);
		result_link = directory_symlink(dir,
		                                last_seg,
		                                last_seglen,
		                                link_text,
		                                strlen(link_text),
		                                fs_getuid(f),
		                                fs_getgid(f),
		                                ~ATOMIC_READ(f->f_umask) & 0777,
		                                fsmode & FS_MODE_FDOSPATH ? DIRECTORY_SYMLINK_FNOCASE
		                                                          : DIRECTORY_SYMLINK_FNORMAL,
		                                NULL);
	}
	decref(result_link);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SYMLINK */





/************************************************************************/
/* linkat(), link()                                                     */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_LINKAT
DEFINE_SYSCALL5(errno_t, linkat,
                fd_t, olddirfd, USER UNCHECKED char const *, oldpath,
                fd_t, newdirfd, USER UNCHECKED char const *, newpath,
                atflag_t, flags) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *newdir;
	REF struct inode *linknode;
	fsmode_t fsmode;
	REF struct path *oldpath_cwd;
	REF struct path *newpath_cwd;
	REF struct path *root;
	validate_readable(oldpath, 1);
	validate_readable(newpath, 1);
	VALIDATE_FLAGSET(flags,
	                 AT_EMPTY_PATH | AT_SYMLINK_FOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_LINKAT_FLAGS);
	fsmode = fs_getmode_for(f, flags);
	if ((flags & AT_EMPTY_PATH) && !*oldpath) {
		/* Create a direct link to `olddirfd' */
		sync_read(&f->f_pathlock);
		root = incref(f->f_root);
		if (newdirfd == AT_FDCWD) {
			newpath_cwd = incref(f->f_cwd);
		} else if (newdirfd == AT_FDROOT) {
			newpath_cwd = incref(root);
		} else {
			sync_endread(&f->f_pathlock);
			newpath_cwd = handle_get_path((unsigned int)newdirfd);
			goto have_paths_empty;
		}
		sync_endread(&f->f_pathlock);
have_paths_empty:
		/* Load the INode pointed to by `olddirfd' */
		TRY {
			linknode = handle_get_inode((unsigned int)olddirfd);
			TRY {
				/* Walk the target path where the link should be placed. */
				p = path_traverse_ex_recent(f,
				                            newpath_cwd,
				                            root,
				                            newpath,
				                            &last_seg,
				                            &last_seglen,
				                            fsmode,
				                            NULL);
				TRY {
					sync_read(p);
				} EXCEPT {
					decref(p);
					RETHROW();
				}
				newdir = (REF struct directory_node *)incref(p->p_inode);
				sync_endread(p);
				TRY {
					/* Actually create the link. */
					directory_link(newdir,
					               last_seg,
					               last_seglen,
					               linknode,
					               fsmode & FS_MODE_FDOSPATH ? DIRECTORY_LINK_FNOCASE
					                                         : DIRECTORY_LINK_FNORMAL,
					               NULL);
				} EXCEPT {
					decref(newdir);
					RETHROW();
				}
				decref(newdir);
			} EXCEPT {
				decref(linknode);
				RETHROW();
			}
		} EXCEPT {
			decref(newpath_cwd);
			decref(root);
			RETHROW();
		}
#if 1
		goto done_decref_components;
#else
		decref(linknode);
		decref(newpath_cwd);
		decref(root);
		return -EOK;
#endif
	}
	/* Load base path nodes. */
	sync_read(&f->f_pathlock);
	root = incref(f->f_root);
	if (olddirfd == AT_FDCWD) {
		oldpath_cwd = incref(f->f_cwd);
	} else if (olddirfd == AT_FDROOT) {
		oldpath_cwd = incref(root);
	} else {
		if (newdirfd == AT_FDCWD) {
			newpath_cwd = incref(f->f_cwd);
		} else if (newdirfd == AT_FDROOT) {
			newpath_cwd = incref(root);
		} else {
			sync_endread(&f->f_pathlock);
			newpath_cwd = handle_get_path((unsigned int)newdirfd);
			goto do_load_oldpath_cwd_handle;
		}
		sync_endread(&f->f_pathlock);
do_load_oldpath_cwd_handle:
		TRY {
			oldpath_cwd = handle_get_path((unsigned int)olddirfd);
		} EXCEPT {
			decref(newpath_cwd);
			RETHROW();
		}
		goto have_paths;
	}
	if (newdirfd == AT_FDCWD) {
		newpath_cwd = incref(f->f_cwd);
	} else if (newdirfd == AT_FDROOT) {
		newpath_cwd = incref(root);
	} else {
		sync_endread(&f->f_pathlock);
		TRY {
			newpath_cwd = handle_get_path((unsigned int)newdirfd);
		} EXCEPT {
			decref(oldpath_cwd);
			RETHROW();
		}
		goto have_paths;
	}
	sync_endread(&f->f_pathlock);
have_paths:
	TRY {
		{
			FINALLY_DECREF_UNLIKELY(oldpath_cwd);
			linknode = path_traversefull_ex(f,
			                                oldpath_cwd,
			                                root,
			                                oldpath,
			                                flags & AT_SYMLINK_FOLLOW,
			                                fsmode,
			                                NULL,
			                                NULL,
			                                NULL,
			                                NULL);
		}
		TRY {
			p = path_traverse_ex_recent(f,
			                            newpath_cwd,
			                            root,
			                            newpath,
			                            &last_seg,
			                            &last_seglen,
			                            fsmode,
			                            NULL);
			{
				FINALLY_DECREF_UNLIKELY(p);
				sync_read(p);
				newdir = (REF struct directory_node *)incref(p->p_inode);
				sync_endread(p);
			}
			{
				FINALLY_DECREF_UNLIKELY(newdir);
				/* Actually create the link. */
				directory_link(newdir,
				               last_seg,
				               last_seglen,
				               linknode,
				               fsmode & FS_MODE_FDOSPATH ? DIRECTORY_LINK_FNOCASE
				                                         : DIRECTORY_LINK_FNORMAL,
				               NULL);
			}
		} EXCEPT {
			decref(linknode);
			RETHROW();
		}
	} EXCEPT {
		decref(root);
		decref(newpath_cwd);
		RETHROW();
	}
done_decref_components:
	decref(linknode);
	decref(newpath_cwd);
	decref(root);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_LINKAT */

#ifdef __ARCH_WANT_SYSCALL_LINK
DEFINE_SYSCALL2(errno_t, link,
                USER UNCHECKED char const *, oldpath,
                USER UNCHECKED char const *, newpath) {
	return sys_linkat(AT_FDCWD, oldpath,
	                  AT_FDCWD, newpath,
	                  0);
}
#endif /* __ARCH_WANT_SYSCALL_LINK */





/************************************************************************/
/* frenameat(), renameat(), rename()                                    */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FRENAMEAT
DEFINE_SYSCALL5(errno_t, frenameat,
                fd_t, olddirfd, USER UNCHECKED char const *, oldpath,
                fd_t, newdirfd, USER UNCHECKED char const *, newpath,
                atflag_t, flags) {
	char const *old_last_seg;
	u16 old_last_seglen;
	char const *new_last_seg;
	u16 new_last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *source_path;
	REF struct path *target_path;
	fsmode_t fsmode;
	REF struct path *oldpath_cwd;
	REF struct path *newpath_cwd;
	REF struct path *root;
	VALIDATE_FLAGSET(flags,
	                 0 | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FRENAMEAT_FLAGS);
	validate_readable(oldpath, 1);
	validate_readable(newpath, 1);
	fsmode = fs_getmode_for(f, flags);
	/* Load base path nodes. */
	sync_read(&f->f_pathlock);
	root = incref(f->f_root);
	if (olddirfd == AT_FDCWD) {
		oldpath_cwd = incref(f->f_cwd);
	} else if (olddirfd == AT_FDROOT) {
		oldpath_cwd = incref(root);
	} else {
		if (newdirfd == AT_FDCWD) {
			newpath_cwd = incref(f->f_cwd);
		} else if (newdirfd == AT_FDROOT) {
			newpath_cwd = incref(root);
		} else {
			sync_endread(&f->f_pathlock);
			newpath_cwd = handle_get_path((unsigned int)newdirfd);
			goto do_load_oldpath_cwd_handle;
		}
		sync_endread(&f->f_pathlock);
do_load_oldpath_cwd_handle:
		TRY {
			oldpath_cwd = handle_get_path((unsigned int)olddirfd);
		} EXCEPT {
			decref(newpath_cwd);
			RETHROW();
		}
		goto have_paths;
	}
	if (newdirfd == AT_FDCWD) {
		newpath_cwd = incref(f->f_cwd);
	} else if (newdirfd == AT_FDROOT) {
		newpath_cwd = incref(root);
	} else {
		sync_endread(&f->f_pathlock);
		TRY {
			newpath_cwd = handle_get_path((unsigned int)newdirfd);
		} EXCEPT {
			decref(oldpath_cwd);
			RETHROW();
		}
		goto have_paths;
	}
	sync_endread(&f->f_pathlock);
have_paths:
	TRY {
		FINALLY_DECREF_UNLIKELY(oldpath_cwd);
		source_path = path_traverse_ex_recent(f,
		                                      oldpath_cwd,
		                                      root,
		                                      oldpath,
		                                      &old_last_seg,
		                                      &old_last_seglen,
		                                      fsmode,
		                                      NULL);
	} EXCEPT {
		decref(root);
		decref(newpath_cwd);
		RETHROW();
	}
	{
		FINALLY_DECREF_UNLIKELY(source_path);
		{
			FINALLY_DECREF_UNLIKELY(newpath_cwd);
			FINALLY_DECREF_UNLIKELY(root);
			target_path = path_traverse_ex_recent(f,
			                                      newpath_cwd,
			                                      root,
			                                      newpath,
			                                      &new_last_seg,
			                                      &new_last_seglen,
			                                      fsmode,
			                                      NULL);
		}
		{
			FINALLY_DECREF_UNLIKELY(target_path);
			path_rename(source_path,
			            old_last_seg,
			            old_last_seglen,
			            directory_entry_hash(old_last_seg,
			                                 old_last_seglen),
			            target_path,
			            new_last_seg,
			            new_last_seglen,
			            fsmode & FS_MODE_FDOSPATH
			            ? (DIRECTORY_RENAME_FNORMAL | DIRECTORY_RENAME_FCHKACCESS | DIRECTORY_RENAME_FNOCASE)
			            : (DIRECTORY_RENAME_FNORMAL | DIRECTORY_RENAME_FCHKACCESS),
			            NULL /* OUT_OPT:psource_dirent */,
			            NULL /* OUT_OPT:ptarget_dirent */,
			            NULL /* OUT_OPT:psource_inode */,
			            NULL /* OUT_OPT:ptarget_inode */,
			            NULL /* OUT_OPT:psource_directory */,
			            NULL /* OUT_OPT:ptarget_directory */,
			            NULL /* OUT_OPT:premoved_path */);
		}
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FRENAMEAT */

#ifdef __ARCH_WANT_SYSCALL_RENAMEAT
DEFINE_SYSCALL4(errno_t, renameat,
                fd_t, olddirfd, USER UNCHECKED char const *, oldpath,
                fd_t, newdirfd, USER UNCHECKED char const *, newpath) {
	return sys_frenameat(olddirfd, oldpath,
	                     newdirfd, newpath, 0);
}
#endif /* __ARCH_WANT_SYSCALL_RENAMEAT */

#ifdef __ARCH_WANT_SYSCALL_RENAME
DEFINE_SYSCALL2(errno_t, rename,
                USER UNCHECKED char const *, oldpath,
                USER UNCHECKED char const *, newpath) {
	return sys_frenameat(AT_FDCWD, oldpath,
	                     AT_FDCWD, newpath, 0);
}
#endif /* __ARCH_WANT_SYSCALL_RENAME */





/************************************************************************/
/* umount2(), umount()                                                  */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_UMOUNT2
DEFINE_SYSCALL2(errno_t, umount2,
                USER UNCHECKED char const *, target,
                syscall_ulong_t, flags) {
	struct path *p;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
	VALIDATE_FLAGSET(flags,
	                 MNT_FORCE | MNT_DETACH | MNT_EXPIRE | UMOUNT_NOFOLLOW,
	                 E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS);
	(void)MNT_FORCE;  /* KOS always does this (though we could probably add a mode where we first
	                   * acquire locks to all cached files and ensure that none of them carry any
	                   * untraceable references, as would be indicative of them being opened, or
	                   * being mapped by some VM) */
	(void)MNT_DETACH; /* Just detaching would result in reference leaks (file data wouldn't get anonymized) */
	(void)MNT_EXPIRE; /* TODO: Only set the `SUPERBLOCK_FUNMOUNTED' flag for the associated superblock. */
	fsmode = fs_getmode_for(f, flags & UMOUNT_NOFOLLOW
	                           ? AT_SYMLINK_NOFOLLOW
	                           : 0);
	p = path_traverse_recent(f,
	                         target,
	                         NULL,
	                         NULL,
	                         fsmode | FS_MODE_FIGNORE_TRAILING_SLASHES,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(p);
		/* Require mounting rights. */
		require(CAP_MOUNT);
		path_umount(p);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UMOUNT2 */

#ifdef __ARCH_WANT_SYSCALL_UMOUNT
DEFINE_SYSCALL1(errno_t, umount,
                USER UNCHECKED char const *, special_file) {
	return sys_umount2(special_file, 0);
}
#endif /* __ARCH_WANT_SYSCALL_UMOUNT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_UMOUNT
DEFINE_COMPAT_SYSCALL1(errno_t, umount,
                       USER UNCHECKED char const *, special_file) {
	return sys_umount2(special_file, 0);
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UMOUNT */





/************************************************************************/
/* mount()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_MOUNT
DEFINE_SYSCALL5(errno_t, mount,
                USER UNCHECKED char const *, source,
                USER UNCHECKED char const *, target,
                USER UNCHECKED char const *, filesystemtype,
                syscall_ulong_t, mountflags,
                USER UNCHECKED void const *, data) {
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
	fsmode = ATOMIC_READ(f->f_mode.f_atflag) | FS_MODE_FIGNORE_TRAILING_SLASHES;
	if (mountflags & MS_MOVE) {
		REF struct path *source_path;
		REF struct path *target_path;
		validate_readable(target, 1);
		validate_readable(source, 1);
		/* Move a mounting point. */
		if (mountflags & ~(MS_MOVE | MS_REMOUNT)) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS,
			      mountflags, ~(MS_REMOUNT), MS_MOVE);
		}
		source_path = path_traverse(f, source, NULL, NULL, fsmode, NULL);
		{
			FINALLY_DECREF(source_path);
			target_path = path_traverse(f, target, NULL, NULL, fsmode, NULL);
			{
				FINALLY_DECREF(target_path);
				/* Require mounting rights. */
				require(CAP_MOUNT);
				path_movemount(target_path,
				               source_path,
				               (mountflags & MS_REMOUNT) != 0);
			}
		}
	} else if (mountflags & MS_BIND) {
		REF struct path *p;
		REF struct directory_node *node;
		/* Create a bind mounting point. */
		if (mountflags & ~(MS_BIND | MS_REMOUNT | MS_REC)) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS,
			      mountflags, ~(MS_REC | MS_REMOUNT), MS_BIND);
		}
		if (mountflags & MS_REC)
			THROW(E_NOT_IMPLEMENTED_TODO, "Recursively bind all mounting points from `src'");
		validate_readable(target, 1);
		validate_readable(source, 1);
		p = path_traverse(f, source, NULL, NULL, fsmode, NULL);
		{
			FINALLY_DECREF(p);
			sync_read(p);
			node = (REF struct directory_node *)incref(p->p_inode);
			sync_endread(p);
		}
		{
			FINALLY_DECREF(node);
			p = path_traverse(f, target, NULL, NULL, fsmode, NULL);
			{
				FINALLY_DECREF(p);
				/* Require mounting rights. */
				require(CAP_MOUNT);
				/* Mount the directory from the other node. */
				path_mount(p,
				           node,
				           (mountflags & MS_REMOUNT) != 0);
			}
		}
	} else if (mountflags & MS_REMOUNT) {
		REF struct path *mp;
		REF struct superblock *super;
		uintptr_t old_flags, new_flags;
		/* Modify an existing mounting point. */
		if (mountflags & ~(MS_LAZYTIME | MS_MANDLOCK | MS_NOATIME | MS_NODEV | MS_NODIRATIME | MS_NOEXEC |
		                   MS_NOSUID | MS_RELATIME | MS_RDONLY | MS_SYNCHRONOUS | MS_DIRSYNC | MS_REMOUNT)) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS,
			      mountflags, ~(MS_LAZYTIME | MS_MANDLOCK | MS_NOATIME | MS_NODEV | MS_NODIRATIME | MS_NOEXEC | MS_NOSUID | MS_RELATIME | MS_RDONLY | MS_SYNCHRONOUS | MS_DIRSYNC),
			      MS_REMOUNT);
		}
		validate_readable(target, 1);
		mp = path_traverse(f,
		                   target,
		                   NULL,
		                   NULL,
		                   fsmode,
		                   NULL);
		{
			FINALLY_DECREF(mp);
			sync_read(mp);
			if unlikely(mp->p_mount) {
				sync_endread(mp);
				THROW(E_FSERROR_NOT_A_MOUNTING_POINT);
			}
			super = (REF struct superblock *)incref(mp->p_mount->mp_super);
			sync_endread(mp);
		}
		FINALLY_DECREF_UNLIKELY(super);
		/* Require mounting rights. */
		require(CAP_MOUNT);
		do {
			old_flags = ATOMIC_READ(super->s_flags);
			new_flags = old_flags | SUPERBLOCK_FDOATIME;
			if (mountflags & MS_NOATIME)
				new_flags &= ~SUPERBLOCK_FDOATIME;
			/* TODO: MS_LAZYTIME */
			/* TODO: MS_MANDLOCK */
			/* TODO: MS_NODEV */
			/* TODO: MS_NODIRATIME */
			/* TODO: MS_NOEXEC */
			/* TODO: MS_NOSUID */
			/* TODO: MS_RELATIME */
			/* TODO: MS_RDONLY */
			/* TODO: MS_SYNCHRONOUS */
			/* TODO: MS_DIRSYNC */
		} while (!ATOMIC_CMPXCH_WEAK(super->s_flags, old_flags, new_flags));
	} else {
		struct superblock_type *type;
		REF struct path *mount_location;
		REF struct superblock *super;
		uintptr_t super_flags;
		validate_readable(target, 1);
		validate_readable(filesystemtype, 1);
		VALIDATE_FLAGSET(mountflags,
		                 MS_RDONLY | MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_SYNCHRONOUS |
		                 MS_MANDLOCK | MS_DIRSYNC | MS_NOATIME | MS_NODIRATIME |
		                 MS_SILENT | MS_POSIXACL | MS_UNBINDABLE | MS_PRIVATE | MS_SLAVE |
		                 MS_SHARED | MS_RELATIME | MS_KERNMOUNT | MS_I_VERSION | MS_STRICTATIME |
		                 MS_LAZYTIME | MS_ACTIVE | MS_NOUSER,
		                 E_INVALID_ARGUMENT_CONTEXT_UMOUNT2_FLAGS);
		/* Regular, old mount() */
		type = lookup_filesystem_type(filesystemtype);
		if unlikely(!type)
			THROW(E_FSERROR_UNKNOWN_FILE_SYSTEM);
		FINALLY_DECREF_UNLIKELY(type);
		mount_location = path_traverse_recent(f,
		                                      target,
		                                      NULL,
		                                      NULL,
		                                      fsmode,
		                                      NULL);
		FINALLY_DECREF_UNLIKELY(mount_location);
		/* Require mounting rights. */
		require(CAP_MOUNT);
		super_flags = SUPERBLOCK_FDOATIME;
		if (mountflags & MS_NOATIME)
			super_flags &= ~SUPERBLOCK_FDOATIME;
		/* TODO: MS_LAZYTIME */
		/* TODO: MS_MANDLOCK */
		/* TODO: MS_NODEV */
		/* TODO: MS_NODIRATIME */
		/* TODO: MS_NOEXEC */
		/* TODO: MS_NOSUID */
		/* TODO: MS_RELATIME */
		/* TODO: MS_RDONLY */
		/* TODO: MS_SYNCHRONOUS */
		/* TODO: MS_DIRSYNC */
		if (type->st_flags & (SUPERBLOCK_TYPE_FNODEV |
		                      SUPERBLOCK_TYPE_FSINGLE)) {
			/* Don't need a device */
			super = superblock_open(type,
			                        (struct basic_block_device *)NULL,
			                        super_flags,
			                        (char *)data,
			                        NULL);
		} else {
			REF struct inode *source_node;
			REF struct basic_block_device *source_dev;
			if unlikely(!source)
				THROW(E_FSERROR_NO_BLOCK_DEVICE);
			validate_readable(source, 1);
			source_node = path_traversefull(f,
			                                source,
			                                true,
			                                fsmode & ~FS_MODE_FIGNORE_TRAILING_SLASHES,
			                                NULL,
			                                NULL,
			                                NULL,
			                                NULL);
			FINALLY_DECREF(source_node);
			if unlikely(!S_ISBLK(source_node->i_filemode))
				THROW(E_FSERROR_NOT_A_BLOCK_DEVICE);
			inode_loadattr(source_node);
			source_dev = block_device_lookup(source_node->i_filerdev);
			if unlikely(!source_dev)
				THROW(E_NO_DEVICE, E_NO_DEVICE_KIND_BLOCK_DEVICE, source_node->i_filerdev);
			super = superblock_open(type,
			                        source_dev,
			                        super_flags,
			                        (char *)data,
			                        NULL);
		}
		FINALLY_DECREF_UNLIKELY(super);
		/* Mount the superblock at the specified location */
		path_mount(mount_location,
		           super,
		           false);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_MOUNT */





/************************************************************************/
/* truncate(), truncate64()                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_TRUNCATE
DEFINE_SYSCALL2(errno_t, truncate,
                USER UNCHECKED char const *, pathname,
                syscall_ulong_t, length) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(pathname, 1);
	node = path_traversefull(f,
	                         pathname,
	                         true,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_truncate(node, (pos_t)length);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TRUNCATE */

#ifdef __ARCH_WANT_SYSCALL_TRUNCATE64
DEFINE_SYSCALL2(errno_t, truncate64,
                USER UNCHECKED char const *, pathname,
                uint64_t, length) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(pathname, 1);
	node = path_traversefull(f,
	                         pathname,
	                         true,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_truncate(node, (pos_t)length);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_TRUNCATE64 */





/************************************************************************/
/* fchdirat(), fchdir(), chdir()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FCHDIRAT
DEFINE_SYSCALL3(errno_t, fchdirat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname, atflag_t, flags) {
	REF struct path *old_cwd;
	REF struct path *new_cwd;
	REF struct path *root;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
	VALIDATE_FLAGSET(flags,
	                 AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FCHDIRAT_FLAGS);
again:
	sync_read(&f->f_pathlock);
	fsmode  = fs_getmode_for(f, flags);
	root    = incref(f->f_root);
	old_cwd = incref(f->f_cwd);
	sync_endread(&f->f_pathlock);
	TRY {
		REF struct path *path_base;
		if (dirfd == AT_FDCWD) {
			path_base = incref(old_cwd);
		} else if (dirfd == AT_FDROOT) {
			path_base = incref(root);
		} else {
			path_base = handle_get_path((unsigned int)dirfd);
		}
		{
			FINALLY_DECREF_UNLIKELY(path_base);
			new_cwd = path_traverse_ex(f,
			                           old_cwd,
			                           root,
			                           pathname,
			                           NULL,
			                           NULL,
			                           fsmode,
			                           NULL);
			TRY {
				sync_write(&f->f_pathlock);
			} EXCEPT {
				decref(new_cwd);
				RETHROW();
			}
		}
	} EXCEPT {
		decref(old_cwd);
		decref(root);
		RETHROW();
	}
	if (f->f_cwd != old_cwd) {
		/* CWD changed in the mean time... (try again) */
		sync_endwrite(&f->f_pathlock);
		decref(root);
		decref(old_cwd);
		goto again;
	}
	f->f_cwd = new_cwd; /* Inherit reference (x2) */
	sync_endwrite(&f->f_pathlock);
	decref_nokill(old_cwd); /* Inherited from `f->f_cwd' */
	decref(old_cwd);
	decref(root);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FCHDIRAT */

#ifdef __ARCH_WANT_SYSCALL_FCHDIR
DEFINE_SYSCALL1(errno_t, fchdir, fd_t, fd) {
	REF struct path *old_cwd;
	REF struct path *new_cwd;
	struct fs *f = THIS_FS;
	new_cwd      = handle_get_path((unsigned int)fd);
	TRY {
		sync_write(&f->f_pathlock);
	} EXCEPT {
		decref(new_cwd);
		RETHROW();
	}
	old_cwd  = f->f_cwd; /* Inherit reference. */
	f->f_cwd = new_cwd;  /* Inherit reference. */
	sync_endwrite(&f->f_pathlock);
	decref(old_cwd);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FCHDIR */

#ifdef __ARCH_WANT_SYSCALL_CHDIR
DEFINE_SYSCALL1(errno_t, chdir,
                USER UNCHECKED char const *, pathname) {
	REF struct path *old_cwd;
	REF struct path *new_cwd;
	REF struct path *root;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
again:
	sync_read(&f->f_pathlock);
	fsmode  = ATOMIC_READ(f->f_mode.f_atflag);
	root    = incref(f->f_root);
	old_cwd = incref(f->f_cwd);
	sync_endread(&f->f_pathlock);
	TRY {
		new_cwd = path_traverse_ex(f,
		                           old_cwd,
		                           root,
		                           pathname,
		                           NULL,
		                           NULL,
		                           fsmode,
		                           NULL);
		TRY {
			sync_write(&f->f_pathlock);
		} EXCEPT {
			decref(new_cwd);
			RETHROW();
		}
	} EXCEPT {
		decref(old_cwd);
		decref(root);
		RETHROW();
	}
	if (f->f_cwd != old_cwd) {
		/* CWD changed in the mean time... (try again) */
		sync_endwrite(&f->f_pathlock);
		decref(root);
		decref(old_cwd);
		goto again;
	}
	f->f_cwd = new_cwd; /* Inherit reference (x2) */
	sync_endwrite(&f->f_pathlock);
	decref_nokill(old_cwd); /* Inherited from `f->f_cwd' */
	decref(old_cwd);
	decref(root);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CHDIR */





/************************************************************************/
/* chroot()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_CHROOT
DEFINE_SYSCALL1(errno_t, chroot,
                USER UNCHECKED char const *, pathname) {
	REF struct path *cwd;
	REF struct path *new_root;
	REF struct path *old_root;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
again:
	fsmode = ATOMIC_READ(f->f_mode.f_atflag);
	sync_read(&f->f_pathlock);
	old_root = incref(f->f_root);
	cwd      = incref(f->f_cwd);
	sync_endread(&f->f_pathlock);
	TRY {
		new_root = path_traverse_ex(f,
		                            cwd,
		                            old_root,
		                            pathname,
		                            NULL,
		                            NULL,
		                            fsmode,
		                            NULL);
		TRY {
			sync_write(&f->f_pathlock);
		} EXCEPT {
			decref(new_root);
			RETHROW();
		}
	} EXCEPT {
		decref(cwd);
		decref(old_root);
		RETHROW();
	}
	if (f->f_root != old_root) {
		/* ROOT changed in the mean time... (try again) */
		sync_endwrite(&f->f_pathlock);
		decref(old_root);
		decref(cwd);
		goto again;
	}
	f->f_root = new_root; /* Inherit reference (x2) */
	sync_endwrite(&f->f_pathlock);
	decref(cwd);
	decref(old_root);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CHROOT */





/************************************************************************/
/* fchmodat(), fchmod(), chmod()                                        */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FCHMODAT
DEFINE_SYSCALL4(errno_t, fchmodat, fd_t, dirfd,
                USER CHECKED char const *, filename,
                mode_t, mode, atflag_t, flags) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	if (has_personality(KP_CHMOD_CHECK_MODE))
		VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE);
	VALIDATE_FLAGSET(flags,
	                 AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FCHMODAT_FLAGS);
	node = path_traversefull_at(f,
	                            (unsigned int)dirfd,
	                            filename,
	                            !(flags & AT_SYMLINK_NOFOLLOW),
	                            fs_getmode_for(f, flags),
	                            NULL,
	                            NULL,
	                            NULL,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chmod(node, 0, mode & 07777);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FCHMODAT */

#ifdef __ARCH_WANT_SYSCALL_FCHMOD
DEFINE_SYSCALL2(errno_t, fchmod, fd_t, fd, mode_t, mode) {
	REF struct inode *node;
	if (has_personality(KP_CHMOD_CHECK_MODE))
		VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE);
	node = handle_get_inode((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chmod(node, 0, mode & 07777);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FCHMOD */

#ifdef __ARCH_WANT_SYSCALL_CHMOD
DEFINE_SYSCALL2(errno_t, chmod, USER CHECKED char const *, filename, mode_t, mode) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	if (has_personality(KP_CHMOD_CHECK_MODE))
		VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chmod(node, 0, mode & 07777);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CHMOD */





/************************************************************************/
/* fchownat(), fchown(), lchown(), chown()                              */
/* fchownat32(), fchown32(), lchown32(), chown32()                      */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FCHOWNAT32
DEFINE_SYSCALL5(errno_t, fchownat32, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_fchownat32), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT3_fchownat32), group,
                atflag_t, flags) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	VALIDATE_FLAGSET(flags,
	                 AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FCHOWNAT_FLAGS);
	node = path_traversefull_at(f,
	                            (unsigned int)dirfd,
	                            filename,
	                            !(flags & AT_SYMLINK_NOFOLLOW),
	                            fs_getmode_for(f, flags),
	                            NULL,
	                            NULL,
	                            NULL,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chown(node,
		            (uid_t)owner,
		            (gid_t)group);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FCHOWNAT32 */

#ifdef __ARCH_WANT_SYSCALL_FCHOWNAT
DEFINE_SYSCALL5(errno_t, fchownat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_fchownat), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT3_fchownat), group,
                atflag_t, flags) {
#ifdef __ARCH_WANT_SYSCALL_FCHOWNAT32
	return sys_fchownat32(dirfd, filename,
	                      (__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32))owner,
	                      (__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32))group,
	                      flags);
#else /* __ARCH_WANT_SYSCALL_FCHOWNAT32 */
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	VALIDATE_FLAGSET(flags,
	                 AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FCHOWNAT_FLAGS);
	node = path_traversefull_at(f,
	                            (unsigned int)dirfd,
	                            filename,
	                            !(flags & AT_SYMLINK_NOFOLLOW),
	                            fs_getmode_for(f, flags),
	                            NULL,
	                            NULL,
	                            NULL,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chown(node,
		            (uid_t)owner,
		            (gid_t)group);
	}
	return -EOK;
#endif /* !__ARCH_WANT_SYSCALL_FCHOWNAT32 */
}
#endif /* __ARCH_WANT_SYSCALL_FCHOWNAT */

#ifdef __ARCH_WANT_SYSCALL_FCHOWN32
DEFINE_SYSCALL3(errno_t, fchown32, fd_t, fd,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_fchown32), group) {
	REF struct inode *node;
	node = handle_get_inode((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chown(node,
		            (uid_t)owner,
		            (gid_t)group);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FCHOWN32 */

#ifdef __ARCH_WANT_SYSCALL_FCHOWN
DEFINE_SYSCALL3(errno_t, fchown, fd_t, fd,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_fchown), group) {
#ifdef __ARCH_WANT_SYSCALL_FCHOWN32
	return sys_fchown32(fd,
	                    (__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32))owner,
	                    (__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32))group);
#else /* __ARCH_WANT_SYSCALL_FCHOWN32 */
	REF struct inode *node;
	node = handle_get_inode((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chown(node,
		            (uid_t)owner,
		            (gid_t)group);
	}
	return -EOK;
#endif /* !__ARCH_WANT_SYSCALL_FCHOWN32 */
}
#endif /* __ARCH_WANT_SYSCALL_FCHOWN */

#ifdef __ARCH_WANT_SYSCALL_LCHOWN32
DEFINE_SYSCALL3(errno_t, lchown32,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_lchown32), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_lchown32), group) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         false,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chown(node,
		            (uid_t)owner,
		            (gid_t)group);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_LCHOWN32 */

#ifdef __ARCH_WANT_SYSCALL_LCHOWN
DEFINE_SYSCALL3(errno_t, lchown,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_lchown), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_lchown), group) {
#ifdef __ARCH_WANT_SYSCALL_LCHOWN32
	return sys_lchown32(filename,
	                    (__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32))owner,
	                    (__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32))group);
#else /* __ARCH_WANT_SYSCALL_LCHOWN32 */
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         false,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chown(node,
		            (uid_t)owner,
		            (gid_t)group);
	}
	return -EOK;
#endif /* !__ARCH_WANT_SYSCALL_LCHOWN32 */
}
#endif /* __ARCH_WANT_SYSCALL_LCHOWN */

#ifdef __ARCH_WANT_SYSCALL_CHOWN32
DEFINE_SYSCALL3(errno_t, chown32,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_chown32), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_chown32), group) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chown(node,
		            (uid_t)owner,
		            (gid_t)group);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_CHOWN32 */

#ifdef __ARCH_WANT_SYSCALL_CHOWN
DEFINE_SYSCALL3(errno_t, chown,
                USER UNCHECKED char const *, filename,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_chown), owner,
                __PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT2_chown), group) {
#ifdef __ARCH_WANT_SYSCALL_CHOWN32
	return sys_chown32(filename,
	                   (__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32))owner,
	                   (__PRIVATE_SYSCALL_GET_ESCAPED_TYPE(__NRAT1_fchown32))group);
#else /* __ARCH_WANT_SYSCALL_CHOWN32 */
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chown(node,
		            (uid_t)owner,
		            (gid_t)group);
	}
	return -EOK;
#endif /* !__ARCH_WANT_SYSCALL_CHOWN32 */
}
#endif /* __ARCH_WANT_SYSCALL_CHOWN */





/************************************************************************/
/* umask()                                                              */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_UMASK
DEFINE_SYSCALL1(mode_t, umask, mode_t, mode) {
	struct fs *f = THIS_FS;
	return ATOMIC_XCH(f->f_umask, mode & 0777);
}
#endif /* __ARCH_WANT_SYSCALL_UMASK */





/************************************************************************/
/* fsmode()                                                             */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FSMODE
DEFINE_SYSCALL1(uint64_t, fsmode, uint64_t, mode) {
	struct fs *f = THIS_FS;
	fs_mask_t new_mode;
	new_mode.f_mode = mode;
	new_mode.f_atmask &= ~FS_MODE_FALWAYS0MASK;
	new_mode.f_atmask |= FS_MODE_FALWAYS1MASK;
	new_mode.f_atflag &= ~FS_MODE_FALWAYS0FLAG;
	new_mode.f_atflag |= FS_MODE_FALWAYS1FLAG;
	return atomic64_xch(&f->f_mode.f_atom, new_mode.f_mode);
}
#endif /* __ARCH_WANT_SYSCALL_FSMODE */





/************************************************************************/
/* sync(), syncfs()                                                     */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_SYNC
DEFINE_SYSCALL0(errno_t, sync) {
	TRY {
		superblock_syncall();
	} EXCEPT {
		error_printf("sync()");
		RETHROW();
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SYNC */

#ifdef __ARCH_WANT_SYSCALL_SYNCFS
DEFINE_SYSCALL1(errno_t, syncfs, fd_t, fd) {
	REF struct superblock *super;
	super = handle_get_superblock_relaxed((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_sync(super,
		                true);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_SYNCFS */





/************************************************************************/
/* openat(), open(), creat()                                            */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_OPENAT
DEFINE_SYSCALL4(fd_t, openat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                oflag_t, oflags, mode_t, mode) {
	unsigned int result;
	struct fs *filesystem = THIS_FS;
	fsmode_t fsmode;
	REF struct handle result_handle;
	assert(!task_wasconnected());
	validate_readable(filename, 1);
	if (oflags & O_CREAT) {
		if (has_personality(KP_OPEN_CREAT_CHECK_MODE)) {
			if unlikely(mode & ~07777) {
				THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
				      E_INVALID_ARGUMENT_CONTEXT_OPEN_MODE,
				      mode, ~07777 /*, 0*/);
			}
		}
		/* Unconditionally mask mode flags. */
		mode &= 07777;
	}
	fsmode = (fsmode_t)0;
	if (oflags & (O_NOFOLLOW | O_SYMLINK))
		fsmode |= (fsmode_t)AT_SYMLINK_NOFOLLOW;
	if (oflags & O_DOSPATH)
		fsmode |= (fsmode_t)AT_DOSPATH;
	fsmode = fs_getmode_for(filesystem, (atflag_t)fsmode);
#ifdef __O_ACCMODE_INVALID
	if ((oflags & O_ACCMODE) == __O_ACCMODE_INVALID) {
		THROW(E_INVALID_ARGUMENT_BAD_FLAG_COMBINATION,
		      E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG,
		      oflags, O_ACCMODE, __O_ACCMODE_INVALID);
	}
#endif /* __O_ACCMODE_INVALID */
	if (oflags & O_PATH) {
		/* Only need to lookup the resulting path object. */
		if (oflags & ~(O_ACCMODE | O_APPEND | O_NONBLOCK | O_SYNC |
		               O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
		               O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC |
		               O_CLOFORK | O_PATH | O_SYMLINK | O_DOSPATH)) {
			THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
			      E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG,
			      oflags,
			      ~(O_ACCMODE | O_APPEND | O_NONBLOCK | O_SYNC |
			        O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
			        O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC |
			        O_CLOFORK | O_PATH | O_SYMLINK | O_DOSPATH),
			      O_PATH | (oflags & O_DIRECTORY));
		}
	} else {
		if (oflags & O_DIRECTORY) {
			if (oflags & ~(O_ACCMODE | O_NOCTTY | O_TRUNC | O_APPEND | O_NONBLOCK |
			               O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
			               O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC |
			               O_CLOFORK | O_PATH | O_TMPFILE | O_SYMLINK | O_DOSPATH)) {
				THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
				      E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG,
				      oflags,
				      ~(O_ACCMODE | O_APPEND | O_NONBLOCK | O_SYNC | O_DSYNC |
				        O_ASYNC | O_DIRECT | O_LARGEFILE | O_DIRECTORY | O_NOFOLLOW |
				        O_NOATIME | O_CLOEXEC | O_CLOFORK | O_PATH | O_SYMLINK | O_DOSPATH),
				      O_DIRECTORY);
			}
		} else {
			VALIDATE_FLAGSET(oflags,
			                 O_ACCMODE | O_CREAT | O_EXCL | O_NOCTTY | O_TRUNC | O_APPEND |
			                 O_NONBLOCK | O_SYNC | O_DSYNC | O_ASYNC | O_DIRECT | O_LARGEFILE |
			                 O_DIRECTORY | O_NOFOLLOW | O_NOATIME | O_CLOEXEC | O_CLOFORK |
			                 O_PATH | O_TMPFILE | O_SYMLINK | O_DOSPATH,
			                 E_INVALID_ARGUMENT_CONTEXT_OPEN_OFLAG);
		}
	}
	{
		REF struct path *root, *cwd;
		/* Load base directory paths. */
		sync_read(&filesystem->f_pathlock);
		root = incref(filesystem->f_root);
		if ((unsigned int)dirfd == HANDLE_SYMBOLIC_FDCWD) {
			cwd = incref(filesystem->f_cwd);
			sync_endread(&filesystem->f_pathlock);
		} else if ((unsigned int)dirfd == HANDLE_SYMBOLIC_FDROOT) {
			cwd = incref(root);
			sync_endread(&filesystem->f_pathlock);
		} else {
			sync_endread(&filesystem->f_pathlock);
			TRY {
				cwd = handle_get_path((unsigned int)dirfd);
			} EXCEPT {
				decref(root);
				RETHROW();
			}
		}
		FINALLY_DECREF_UNLIKELY(root);
		FINALLY_DECREF_UNLIKELY(cwd);
		/* Open the underlying file. */
		result_handle = fs_open_ex(/* filesystem: */ filesystem,
		                           /* cwd:        */ cwd,
		                           /* root:       */ root,
		                           /* upath:      */ filename,
		                           /* oflags:     */ oflags,
		                           /* mode:       */ mode,
		                           /* fsmode:     */ fsmode);
	}
	/* Set the I/O mode, and install the resulting object handle. */
	STATIC_ASSERT(IO_FROM_OPENFLAG(O_CLOFORK) == IO_CLOFORK);
	STATIC_ASSERT(IO_FROM_OPENFLAG(O_CLOEXEC) == IO_CLOEXEC);
	STATIC_ASSERT(IO_FROM_OPENFLAG(O_CLOFORK | O_CLOEXEC) == (IO_CLOFORK | IO_CLOEXEC));
	result_handle.h_mode = IO_FROM_OPENFLAG(oflags);
	TRY {
		result = handle_install(THIS_HANDLE_MANAGER, result_handle);
	} EXCEPT {
		decref(result_handle);
		RETHROW();
	}
	decref(result_handle);
	assert(!task_wasconnected());
	return (fd_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_OPENAT */

#ifdef __ARCH_WANT_SYSCALL_OPEN
DEFINE_SYSCALL3(fd_t, open,
                USER UNCHECKED char const *, filename,
                oflag_t, oflags, mode_t, mode) {
	return sys_openat(AT_FDCWD,
	                  filename,
	                  oflags,
	                  mode);
}
#endif /* __ARCH_WANT_SYSCALL_OPEN */

#ifdef __ARCH_WANT_SYSCALL_CREAT
DEFINE_SYSCALL2(fd_t, creat,
                USER UNCHECKED char const *, filename,
                mode_t, mode) {
	return sys_openat(AT_FDCWD,
	                  filename,
	                  O_CREAT | O_WRONLY | O_TRUNC,
	                  mode);
}
#endif /* __ARCH_WANT_SYSCALL_CREAT */





/************************************************************************/
/* frealpath4(), frealpathat()                                          */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_FREALPATH4
DEFINE_SYSCALL4(ssize_t, frealpath4,
                fd_t, fd, USER UNCHECKED char *, buf,
                size_t, buflen, atflag_t, flags) {
	struct handle hnd;
	size_t result;
	fsmode_t fsmode;
	unsigned int print_mode = PATH_PRINT_MODE_NORMAL;
	struct fs *f            = THIS_FS;
	REF struct path *root;
	validate_writable(buf, buflen);
	VALIDATE_FLAGSET(flags,
	                 AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS);
	fsmode = fs_getmode_for(f, flags);
	if (flags & AT_ALTPATH)
		fsmode ^= AT_DOSPATH;
	if (fsmode & AT_DOSPATH)
		print_mode |= PATH_PRINT_MODE_DOSPATH;
	sync_read(&f->f_pathlock);
	root = incref(f->f_root);
	if (fd == AT_FDCWD) {
		hnd.h_type = HANDLE_TYPE_PATH;
		hnd.h_data = incref(f->f_cwd);
		sync_endread(&f->f_pathlock);
	} else if (fd == AT_FDROOT) {
		sync_endread(&f->f_pathlock);
		hnd.h_type = HANDLE_TYPE_PATH;
		hnd.h_data = incref(root);
	} else {
		sync_endread(&f->f_pathlock);
		TRY {
			hnd = handle_lookup((unsigned int)fd);
		} EXCEPT {
			decref(root);
			RETHROW();
		}
	}
	TRY {
		switch (hnd.h_type) {

		case HANDLE_TYPE_CHARACTERDEVICE:
		case HANDLE_TYPE_BLOCKDEVICE: {
			/* Figure out where (if at all) devfs is mounted. */
			REF struct path *mount;
			char const *devname;
			if (hnd.h_type == HANDLE_TYPE_CHARACTERDEVICE) {
				struct character_device *me;
				me      = (struct character_device *)hnd.h_data;
				devname = me->cd_name;
			} else {
				struct block_device *me;
				me      = (struct block_device *)hnd.h_data;
				devname = me->bd_name;
			}
			mount = superblock_getmountloc(&devfs, THIS_VFS);
			if unlikely(!mount)
				goto bad_handle_type; /* devfs isn't mounted... */
			FINALLY_DECREF_UNLIKELY(mount);
			result = path_sprintentex(buf,
			                          buflen,
			                          mount,
			                          devname,
			                          strlen(devname),
			                          print_mode,
			                          root);
		}	break;

		case HANDLE_TYPE_FILE:
		case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
			struct file *me;
			me = (struct file *)hnd.h_data;
			if unlikely(!me->f_path)
				goto bad_handle_type;
			if unlikely(!me->f_dirent)
				goto bad_handle_type;
			result = path_sprintentex(buf,
			                          buflen,
			                          me->f_path,
			                          me->f_dirent->de_name,
			                          me->f_dirent->de_namelen,
			                          print_mode,
			                          root);
		}	break;

		case HANDLE_TYPE_PATH:
			result = path_sprintex(buf,
			                       buflen,
			                       (struct path *)hnd.h_data,
			                       print_mode,
			                       root);
			break;

		case HANDLE_TYPE_FS: {
			REF struct path *pwd;
			struct fs *me;
			me = (struct fs *)hnd.h_data;
			sync_read(&me->f_pathlock);
			pwd = incref(me->f_cwd);
			sync_endread(&me->f_pathlock);
			{
				FINALLY_DECREF_UNLIKELY(pwd);
				result = path_sprintex(buf,
				                       buflen,
				                       pwd,
				                       print_mode,
				                       root);
			}
		}	break;

		case HANDLE_TYPE_FIFO_USER: {
			struct fifo_user *me;
			me = (struct fifo_user *)hnd.h_data;
			if unlikely(!me->fu_path)
				goto bad_handle_type;
			if unlikely(!me->fu_dirent)
				goto bad_handle_type;
			result = path_sprintentex(buf,
			                          buflen,
			                          me->fu_path,
			                          me->fu_dirent->de_name,
			                          me->fu_dirent->de_namelen,
			                          print_mode,
			                          root);
		}	break;

		default:
bad_handle_type:
			THROW(E_INVALID_HANDLE_FILETYPE,
			      (unsigned int)fd, /* Filled in by the caller */
			      HANDLE_TYPE_PATH,
			      hnd.h_type,
			      HANDLE_TYPEKIND_PATH_GENERIC,
			      handle_typekind(&hnd));
			break;
		}
	} EXCEPT {
		decref(root);
		decref(hnd);
		RETHROW();
	}
	decref(root);
	decref(hnd);
	/* Throw a buffer error if the caller doesn't want the required size */
	if (result > buflen && !(flags & AT_READLINK_REQSIZE))
		THROW(E_BUFFER_TOO_SMALL, result, buflen);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_FREALPATH4 */

#ifdef __ARCH_WANT_SYSCALL_FREALPATHAT
DEFINE_SYSCALL5(ssize_t, frealpathat,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                USER UNCHECKED char *, buf, size_t, buflen, atflag_t, flags) {
	size_t result;
	fsmode_t fsmode;
	struct fs *f            = THIS_FS;
	unsigned int print_mode = PATH_PRINT_MODE_NORMAL;
	REF struct path *cwd, *root;
	REF struct path *containing_path;
	REF struct directory_entry *containing_dentry;
	validate_writable(buf, buflen);
	VALIDATE_FLAGSET(flags,
	                 AT_SYMLINK_NOFOLLOW | AT_ALTPATH | AT_READLINK_REQSIZE | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FREALPATH4_FLAGS);
	fsmode = fs_getmode_for(f, flags);
	if ((fsmode & AT_DOSPATH) != (flags & AT_ALTPATH))
		print_mode |= PATH_PRINT_MODE_DOSPATH;
	sync_read(&f->f_pathlock);
	root = incref(f->f_root);
	if (dirfd == AT_FDCWD) {
		cwd = incref(f->f_cwd);
		sync_endread(&f->f_pathlock);
	} else if (dirfd == AT_FDROOT) {
		cwd = incref(root);
		sync_endread(&f->f_pathlock);
	} else {
		sync_endread(&f->f_pathlock);
		TRY {
			cwd = handle_get_path((unsigned int)dirfd);
		} EXCEPT {
			decref(root);
			RETHROW();
		}
	}
	{
		REF struct inode *node;
		FINALLY_DECREF_UNLIKELY(root);
		FINALLY_DECREF_UNLIKELY(cwd);
		node = path_traversefull_ex(f,
		                            cwd,
		                            root,
		                            filename,
		                            !(flags & AT_SYMLINK_NOFOLLOW),
		                            fsmode,
		                            NULL,
		                            &containing_path,
		                            NULL,
		                            &containing_dentry);
		decref(node);
		{
			FINALLY_DECREF_UNLIKELY(containing_path);
			FINALLY_DECREF_UNLIKELY(containing_dentry);
			result = path_sprintentex(buf,
			                          buflen,
			                          containing_path,
			                          containing_dentry->de_name,
			                          containing_dentry->de_namelen,
			                          print_mode,
			                          root);
		}
	}
	/* Throw a buffer error if the caller doesn't want the required size */
	if (result > buflen && !(flags & AT_READLINK_REQSIZE))
		THROW(E_BUFFER_TOO_SMALL, result, buflen);
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_FREALPATHAT */






/************************************************************************/
/* Base implementation of all stat() functions                          */
/************************************************************************/
LOCAL void KCALL
system_fstatat(fd_t dirfd,
               USER UNCHECKED char const *filename,
               USER CHECKED struct stat *statbuf,
               atflag_t flags) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	VALIDATE_FLAGSET(flags,
	                 AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_KFSTATAT_FLAGS);
	node = path_traversefull_at(f,
	                            (unsigned int)dirfd,
	                            filename,
	                            !(flags & AT_SYMLINK_NOFOLLOW),
	                            fs_getmode_for(f, flags),
	                            NULL,
	                            NULL,
	                            NULL,
	                            NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, statbuf);
	}
}

LOCAL void KCALL
system_fstat(fd_t fd, USER CHECKED struct stat *statbuf) {
	struct handle hnd;
	hnd = handle_lookup((unsigned int)fd);
	TRY {
		handle_stat(hnd, statbuf);
	} EXCEPT {
		decref(hnd);
		RETHROW();
	}
	decref(hnd);
}

LOCAL void KCALL
system_lstat(USER UNCHECKED char const *filename,
             USER CHECKED struct stat *statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         false,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, statbuf);
	}
}

LOCAL void KCALL
system_stat(USER UNCHECKED char const *filename,
            USER CHECKED struct stat *statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_mode.f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, statbuf);
	}
}







/************************************************************************/
/* kfstatat(), kfstat(), klstat(), kstat()                              */
/************************************************************************/
#if (defined(__ARCH_WANT_SYSCALL_KFSTATAT) || \
     defined(__ARCH_WANT_SYSCALL_KFSTAT) ||   \
     defined(__ARCH_WANT_SYSCALL_KLSTAT) ||   \
     defined(__ARCH_WANT_SYSCALL_KSTAT))
#define WANT_KSTAT_NATIVE 1
#endif /* kstat... */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_KFSTATAT) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_KFSTAT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_KLSTAT) ||   \
     defined(__ARCH_WANT_COMPAT_SYSCALL_KSTAT))
#define WANT_KSTAT_COMPAT 1
#endif /* kstat... (compat) */

#if defined(WANT_KSTAT_NATIVE) || defined(WANT_KSTAT_COMPAT)
#define WANT_KSTAT 1
#endif /* kstat... */

#ifdef WANT_KSTAT_NATIVE
#if __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__
#define complete_kstat(statbuf) (void)0
#else /* __SIZEOF_TIME32_T__ == __SIZEOF_TIME64_T__ */
LOCAL void KCALL
complete_kstat(USER CHECKED struct stat *statbuf) {
	COMPILER_BARRIER();
	statbuf->__st_atimespec32.tv_sec  = statbuf->st_atime;
	statbuf->__st_atimespec32.tv_nsec = statbuf->st_atimensec;
	statbuf->__st_mtimespec32.tv_sec  = statbuf->st_mtime;
	statbuf->__st_mtimespec32.tv_nsec = statbuf->st_mtimensec;
	statbuf->__st_ctimespec32.tv_sec  = statbuf->st_ctime;
	statbuf->__st_ctimespec32.tv_nsec = statbuf->st_ctimensec;
	COMPILER_BARRIER();
}
#endif /* __SIZEOF_TIME32_T__ != __SIZEOF_TIME64_T__ */
#endif /* WANT_KSTAT_NATIVE */

#ifdef __ARCH_WANT_SYSCALL_KFSTATAT
DEFINE_SYSCALL4(errno_t, kfstatat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct stat *, statbuf,
                atflag_t, flags) {
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, statbuf, flags);
	complete_kstat(statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_KFSTATAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_KFSTATAT
DEFINE_COMPAT_SYSCALL4(errno_t, kfstatat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_stat *, statbuf,
                       atflag_t, flags) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, flags);
	stat_to_compat_stat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_KFSTATAT */

#ifdef __ARCH_WANT_SYSCALL_KFSTAT
DEFINE_SYSCALL2(errno_t, kfstat, fd_t, fd,
                USER UNCHECKED struct stat *, statbuf) {
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstat(fd, statbuf);
	complete_kstat(statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_KFSTAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_KFSTAT
DEFINE_COMPAT_SYSCALL2(errno_t, kfstat, fd_t, fd,
                       USER UNCHECKED struct compat_stat *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstat(fd, &st);
	stat_to_compat_stat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_KFSTAT */

#ifdef __ARCH_WANT_SYSCALL_KLSTAT
DEFINE_SYSCALL2(errno_t, klstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct stat *, statbuf) {
	validate_writable(statbuf, sizeof(*statbuf));
	system_lstat(filename, statbuf);
	complete_kstat(statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_KLSTAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_KLSTAT
DEFINE_COMPAT_SYSCALL2(errno_t, klstat,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_stat *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_lstat(filename, &st);
	stat_to_compat_stat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_KLSTAT */

#ifdef __ARCH_WANT_SYSCALL_KSTAT
DEFINE_SYSCALL2(errno_t, kstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct stat *, statbuf) {
	validate_writable(statbuf, sizeof(*statbuf));
	system_stat(filename, statbuf);
	complete_kstat(statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_KSTAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_KSTAT
DEFINE_COMPAT_SYSCALL2(errno_t, kstat,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_stat *, statbuf) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_stat(filename, &st);
	stat_to_compat_stat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_KSTAT */





/************************************************************************/
/* oldfstatat(), oldfstat(), oldlstat(), oldstat() */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_OLDFSTATAT
DEFINE_SYSCALL4(errno_t, oldfstatat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_oldstat *, statbuf,
                atflag_t, flags) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, flags);
	stat_to_linux_oldstat(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_OLDFSTATAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_OLDFSTATAT
DEFINE_COMPAT_SYSCALL4(errno_t, oldfstatat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct linux_oldstat *, statbuf,
                       atflag_t, flags) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, flags);
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
                atflag_t, flags) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, flags);
	stat_to_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSTATAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FSTATAT
DEFINE_COMPAT_SYSCALL4(errno_t, fstatat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_linux_stat32 *, statbuf,
                       atflag_t, flags) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, flags);
	stat_to_compat_linux_stat32(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTATAT */

#ifdef __ARCH_WANT_SYSCALL_FSTATAT64
DEFINE_SYSCALL4(errno_t, fstatat64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat64 *, statbuf,
                atflag_t, flags) {
	struct stat st;
	validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, flags);
	stat_to_linux_stat64(&st, statbuf);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FSTATAT64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FSTATAT64
DEFINE_COMPAT_SYSCALL4(errno_t, fstatat64, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_linux_stat64 *, statbuf,
                       atflag_t, flags) {
	struct stat st;
	compat_validate_writable(statbuf, sizeof(*statbuf));
	system_fstatat(dirfd, filename, &st, flags);
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
#ifdef __ARCH_WANT_SYSCALL_FREADLINKAT
DEFINE_SYSCALL5(ssize_t, freadlinkat,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                USER UNCHECKED char *, buf, size_t, buflen, atflag_t, flags) {
	size_t result;
	struct fs *f = THIS_FS;
	REF struct symlink_node *link_node;
	validate_readable(filename, 1);
	validate_writable(buf, buflen);
	VALIDATE_FLAGSET(flags,
	                 AT_READLINK_REQSIZE | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_FREADLINKAT_FLAGS);
	link_node = (REF struct symlink_node *)path_traversefull_at(f,
	                                                            (unsigned int)dirfd,
	                                                            filename,
	                                                            false, /* follow_final_link */
	                                                            fs_getmode_for(f, flags),
	                                                            NULL,
	                                                            NULL,
	                                                            NULL,
	                                                            NULL);
	{
		FINALLY_DECREF_UNLIKELY((struct inode *)link_node);
		/* Check that the named INode is actually a symbolic link. */
		if (!INODE_ISLNK((struct inode *)link_node))
			THROW(E_FSERROR_NOT_A_SYMBOLIC_LINK,
			      E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_READLINK);
		/* Read the contents of the symbolic link. */
		result = symlink_node_readlink(link_node,
		                               buf,
		                               buflen);
	}
	if (flags & AT_READLINK_REQSIZE) {
		/* Append a trailing NUL-character */
		if (result < buflen)
			buf[result] = '\0';
		++result;
	} else if (result >= buflen) {
		/* From `man':
		 *  ... It will (silently) truncate the contents (to a length
		 *      of bufsiz characters), in case the buffer is too small
		 *      to hold all of the contents
		 * In other words, it's $h1t, which is why KOS offers the extension
		 * of using `AT_READLINK_REQSIZE'. */
		result = buflen;
	}
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_FREADLINKAT */

#ifdef __ARCH_WANT_SYSCALL_READLINKAT
DEFINE_SYSCALL4(ssize_t, readlinkat,
                fd_t, dirfd, USER UNCHECKED char const *, filename,
                USER UNCHECKED char *, buf, size_t, buflen) {
	size_t result;
	struct fs *f = THIS_FS;
	REF struct symlink_node *link_node;
	validate_readable(filename, 1);
	validate_writable(buf, buflen);
	link_node = (REF struct symlink_node *)path_traversefull_at(f,
	                                                            (unsigned int)dirfd,
	                                                            filename,
	                                                            false,
	                                                            ATOMIC_READ(f->f_mode.f_atflag),
	                                                            NULL,
	                                                            NULL,
	                                                            NULL,
	                                                            NULL);
	{
		FINALLY_DECREF_UNLIKELY((struct inode *)link_node);
		/* Check that the named INode is actually a symbolic link. */
		if (!INODE_ISLNK((struct inode *)link_node))
			THROW(E_FSERROR_NOT_A_SYMBOLIC_LINK,
			      E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_READLINK);
		/* Read the contents of the symbolic link. */
		result = symlink_node_readlink(link_node,
		                               buf,
		                               buflen);
	}
	if (result >= buflen)
		result = buflen;
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_READLINKAT */

#ifdef __ARCH_WANT_SYSCALL_READLINK
DEFINE_SYSCALL3(ssize_t, readlink,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED char *, buf, size_t, buflen) {
	size_t result;
	struct fs *f = THIS_FS;
	REF struct symlink_node *link_node;
	validate_readable(filename, 1);
	validate_writable(buf, buflen);
	link_node = (REF struct symlink_node *)path_traversefull(f,
	                                                         filename,
	                                                         false,
	                                                         ATOMIC_READ(f->f_mode.f_atflag),
	                                                         NULL,
	                                                         NULL,
	                                                         NULL,
	                                                         NULL);
	{
		FINALLY_DECREF_UNLIKELY((struct inode *)link_node);
		/* Check that the named INode is actually a symbolic link. */
		if (!INODE_ISLNK((struct inode *)link_node))
			THROW(E_FSERROR_NOT_A_SYMBOLIC_LINK,
			      E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_READLINK);
		/* Read the contents of the symbolic link. */
		result = symlink_node_readlink(link_node,
		                               buf,
		                               buflen);
	}
	if (result >= buflen)
		result = buflen;
	return (ssize_t)result;
}
#endif /* __ARCH_WANT_SYSCALL_READLINK */


#ifdef CONFIG_USE_NEW_VM
typedef void(KCALL *kernel_permman_onexec_t)(void);
INTDEF kernel_permman_onexec_t __kernel_permman_onexec_start[];
INTDEF kernel_permman_onexec_t __kernel_permman_onexec_end[];

LOCAL void KCALL run_permman_onexec(void) {
	kernel_permman_onexec_t *iter;
	for (iter = __kernel_permman_onexec_start;
	     iter < __kernel_permman_onexec_end; ++iter)
		(**iter)();
	/* Invoke dynamic callbacks. */
	mman_onexec_callbacks();
}
#else /* CONFIG_USE_NEW_VM */
typedef void(KCALL *kernel_pervm_onexec_t)(void);
INTDEF kernel_pervm_onexec_t __kernel_pervm_onexec_start[];
INTDEF kernel_pervm_onexec_t __kernel_pervm_onexec_end[];

LOCAL void KCALL run_permman_onexec(void) {
	kernel_pervm_onexec_t *iter;
	for (iter = __kernel_pervm_onexec_start;
	     iter < __kernel_pervm_onexec_end; ++iter)
		(**iter)();
	/* Invoke dynamic callbacks. */
	vm_onexec_callbacks();
}
#endif /* !CONFIG_USE_NEW_VM */



PRIVATE void KCALL
kernel_do_execveat_impl(/*in|out*/ struct execargs *__restrict args) {
	uintptr_t thread_flags;
	thread_flags = PERTASK_GET(this_task.t_flags);
#ifdef CONFIG_HAVE_USERPROCMASK
	/* If the calling thread uses userprocmask, we must copy
	 * their final process mask into kernel-space before we do
	 * the exec. Note that the `TASK_FUSERPROCMASK' flag itself
	 * is later unset by `reset_user_except_handler()' */
	if (thread_flags & TASK_FUSERPROCMASK) {
		struct kernel_sigmask *mymask;
		USER CHECKED struct userprocmask *um;
		USER UNCHECKED sigset_t *um_sigset;
		um        = PERTASK_GET(this_userprocmask_address);
		um_sigset = ATOMIC_READ(um->pm_sigmask);
		validate_readable(um_sigset, sizeof(sigset_t));

		/* Copy the final user-space signal mask into kernel-space.
		 * If the exec() ends up succeeding, then this will be the
		 * signal mask that the new program will start execution
		 * under. */
		mymask = sigmask_kernel_getwr();
		memcpy(&mymask->sm_mask, um_sigset, sizeof(sigset_t));
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
		/* ==== Point of no return: This is where we
		 *      indicate success to our parent process. */
#ifdef CONFIG_HAVE_USERPROCMASK
		{
			uintptr_t old_flags;
			old_flags = ATOMIC_FETCHAND(THIS_TASK->t_flags,
			                            ~(TASK_FVFORK | TASK_FUSERPROCMASK |
			                              TASK_FUSERPROCMASK_AFTER_VFORK));
			/* Special case: If userprocmask was enabled after vfork(), then
			 *               we must write-back a NULL to its `pm_sigmask' field
			 *               in order to indicate to the parent process that
			 *               their userprocmask hasn't been enabled, yet. */
			if (old_flags & TASK_FUSERPROCMASK_AFTER_VFORK) {
				USER CHECKED struct userprocmask *um;
				um = PERTASK_GET(this_userprocmask_address);
				printk(KERN_DEBUG "[userprocmask:%p] Uninstall during exec after vfork\n", um);
				TRY {
					ATOMIC_WRITE(um->pm_sigmask, NULL);
				} EXCEPT {
					error_class_t cls = error_class();
					if (ERRORCLASS_ISRTLPRIORITY(cls))
						RETHROW();
					error_printf("Handling TASK_FUSERPROCMASK_AFTER_VFORK");
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
		 * since this also means that our thread's user-visible signal
		 * mask has once again come into effect.
		 * XXX: Use `sigmask_check_s()' (after all: we _do_ have `state') */
		sigmask_check();
	} else {
		args->ea_mman = THIS_MMAN;
		mman_exec(args);
#ifdef CONFIG_HAVE_USERPROCMASK
		/* If the previous process used to have a userprocmask, and didn't make proper
		 * use of calling `sys_sigmask_check()', we check for pending signals in the
		 * context of the new process, just so it gets to start out with a clean slate.
		 *
		 * Note though that assuming the original program used the userprocmask API
		 * correctly, there shouldn't be any unmasked, pending signals from before
		 * the call to exec() at this point (of course, there could always be some
		 * from during the call...) */
		if (thread_flags & TASK_FUSERPROCMASK)
			sigmask_check();
#endif /* CONFIG_HAVE_USERPROCMASK */
	}
	/* Upon success, run onexec callbacks (which will clear all CLOEXEC handles). */
	run_permman_onexec();
#ifndef CONFIG_EVERYONE_IS_ROOT
	cred_onexec(args->ea_xnode);
#endif /* !CONFIG_EVERYONE_IS_ROOT */
}

PRIVATE void KCALL
kernel_do_execveat(/*in|out*/ struct execargs *__restrict args) {
	if (kernel_debugtrap_enabled()) {
		/* Trigger an EXEC debug trap. */
		char *buf, *dst;
		size_t reglen;
		reglen = (size_t)path_printent(args->ea_xpath,
		                               args->ea_xdentry->de_name,
		                               args->ea_xdentry->de_namelen,
		                               &format_length,
		                               NULL);
		/* Allocate the register buffer beforehand, so this
		 * allocation failing can still be handled by user-space.
		 * NOTE: We always allocate this buffer on the heap, since file paths can get quite long,
		 *       an being as far to the bottom of the kernel stack as we are, it could be a bit
		 *       risky to allocate a huge stack-based structure when we still have to call `mman_exec()',
		 *       even when using `malloca()' (but maybe I'm just overlay cautios...) */
		buf = (char *)kmalloc((reglen + 1) * sizeof(char), GFP_NORMAL);
		TRY {
			dst = buf;
			/* FIXME: If the process uses chroot() between this and the previous
			 *        printent() call, then we may write past the end of the buffer!
			 * Solution: Use `path_printentex()' and pass the same pre-loaded root-path
			 *           during every invocation! */
			path_printent(args->ea_xpath,
			              args->ea_xdentry->de_name,
			              args->ea_xdentry->de_namelen,
			              &format_sprintf_printer,
			              &dst);
			*dst = '\0';
			assert(dst == buf + reglen);
			*dst = 0;
			/* Execute the specified program. */
			kernel_do_execveat_impl(args);
			{
				struct debugtrap_reason r;
				r.dtr_signo  = SIGTRAP;
				r.dtr_reason = DEBUGTRAP_REASON_EXEC;
				r.dtr_strarg = buf;
				args->ea_state = kernel_debugtrap_r(args->ea_state, &r);
			}
		} EXCEPT {
			kfree(buf);
			RETHROW();
		}
		kfree(buf);
	} else {
		/* Execute the specified program. */
		kernel_do_execveat_impl(args);
	}
}


struct kernel_exec_rpc_data {
	struct execargs       er_args;   /* Exec args. */
	struct exception_data er_except; /* Information about the exception that caused exec() to fail. */
	struct sig            er_error;  /* Signal broadcast upon error. */
};


PRIVATE struct icpustate *FCALL
kernel_exec_rpc_func(void *arg, struct icpustate *__restrict state,
                     unsigned int reason,
                     struct rpc_syscall_info const *UNUSED(sc_info)) {
	struct kernel_exec_rpc_data *data;
	struct exception_info old_exception_info;
	struct exception_info *tls_info;
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	data = (struct kernel_exec_rpc_data *)arg;
	tls_info = error_info();
	memcpy(&old_exception_info, tls_info, sizeof(old_exception_info));
	tls_info->ei_code = ERROR_CODEOF(E_OK);
	tls_info->ei_flags &= ~EXCEPT_FINCATCH;
	TRY {
		/* Check for race condition: Our RPC only got executed because the
		 * main thread is currently being terminated. - In this case it wouldn't
		 * make any sense to try and load a new binary into the VM, so just indicate
		 * to the receiving thread that we've been terminated by propagating an
		 * E_EXIT_THREAD exception to them. */
		if unlikely(reason == TASK_RPC_REASON_SHUTDOWN) {
			assert(THIS_TASKPID);
			bzero(&data->er_except.e_args, sizeof(data->er_except.e_args));
			data->er_except.e_code                            = ERROR_CODEOF(E_EXIT_THREAD);
			data->er_except.e_args.e_exit_thread.et_exit_code = (uintptr_t)(unsigned int)THIS_TASKPID->tp_status.w_status;
			goto done_signal_exception;
		}
		/* Actually map the specified file into memory!
		 * NOTE: For this purpose, we simply re-direct the given user-space
		 *       CPU state to which the RPC would have normally returned! */
		data->er_args.ea_state = state;
		kernel_do_execveat(&data->er_args);
		state = data->er_args.ea_state;
	} EXCEPT {
		execargs_fini(&data->er_args);
		memcpy(&data->er_except,
		       &THIS_EXCEPTION_INFO,
		       sizeof(data->er_except));
		goto restore_exception;
	}
	memcpy(tls_info, &old_exception_info, sizeof(old_exception_info));
	/* Success! -> In this case _we_ must inherit the given RPC data packet,
	 *             since the sending thread will terminate (or has already
	 *             terminated) by having its `task_waitfor()' function return
	 *             by throwing an E_EXIT_THREAD exception that got caused by
	 *            `vmb_apply()' terminating all threads except for the calling
	 *             one (us) within the current process. */
	execargs_fini(&data->er_args);
	kfree(data);
	return state;
restore_exception:
	memcpy(tls_info, &old_exception_info, sizeof(old_exception_info));
done_signal_exception:
	if (sig_broadcast(&data->er_error) == 0) {
		/* Can't deliver the error to the original caller of `exec()', since
		 * they must have died in the mean time. - With that in mind, the
		 * error that caused the problem must go unnoticed, and we are
		 * responsible for the cleanup of `data'. */
		kfree(data);
	}
	return state;
}

/* Implementation of the execv() system call. */
INTERN struct icpustate *KCALL
kernel_execveat(fd_t dirfd,
                USER UNCHECKED char const *pathname,
#ifdef __ARCH_HAVE_COMPAT
                USER UNCHECKED void const *argv,
                USER UNCHECKED void const *envp,
#else /* __ARCH_HAVE_COMPAT */
                USER UNCHECKED char const *USER UNCHECKED const *argv,
                USER UNCHECKED char const *USER UNCHECKED const *envp,
#endif /* !__ARCH_HAVE_COMPAT */
                atflag_t flags,
#ifdef __ARCH_HAVE_COMPAT
                bool argv_is_compat,
#endif /* __ARCH_HAVE_COMPAT */
                struct icpustate *__restrict state) {
	struct fs *f = THIS_FS;
	struct task *caller = THIS_TASK;
	struct execargs args;
#ifdef __ARCH_HAVE_COMPAT
	validate_readable_opt(argv, 1);
	validate_readable_opt(envp, 1);
#else /* __ARCH_HAVE_COMPAT */
	validate_readable_opt(argv, sizeof(*argv));
	validate_readable_opt(envp, sizeof(*envp));
#endif /* !__ARCH_HAVE_COMPAT */
	VALIDATE_FLAGSET(flags,
	                 AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_EXECVEAT_FLAGS);
	memset(&args, 0, sizeof(args));
	args.ea_xnode = (REF struct regular_node *)path_traversefull_at(f,
	                                                                (unsigned int)dirfd,
	                                                                pathname,
	                                                                !(flags & AT_SYMLINK_NOFOLLOW),
	                                                                fs_getmode_for(f, flags),
	                                                                NULL,
	                                                                &args.ea_xpath,
	                                                                NULL,
	                                                                &args.ea_xdentry);
	TRY {
		/* Assert that the specified node is a regular file. */
#ifndef CONFIG_USE_NEW_VM /* TODO */
		vm_exec_assert_regular(args.ea_xnode);
#endif /* !CONFIG_USE_NEW_VM */

		/* Check for execute permissions? */
		inode_access(args.ea_xnode, R_OK | X_OK);

		/* Fill in exec arguments. */
		args.ea_argv = argv;
		args.ea_envp = envp;
#ifdef __ARCH_HAVE_COMPAT
		args.ea_argv_is_compat = argv_is_compat;
#endif /* __ARCH_HAVE_COMPAT */

		if (caller == task_getprocess_of(caller)) {
			args.ea_state = state;
			kernel_do_execveat(&args);
			state = args.ea_state;
		} else {
			struct kernel_exec_rpc_data *data;
			struct task *proc = task_getprocess_of(caller);
			/* Since the new process is meant to override our's as a whole, the actual
			 * exec() must be performed by the main thread of our own process. - For this
			 * purpose, we must use an RPC to load the new binary from the main thread. */
			data = (struct kernel_exec_rpc_data *)kmalloc(sizeof(struct kernel_exec_rpc_data),
			                                              GFP_LOCKED);
			/* Initialize RPC information. */
			memcpy(&data->er_args, &args, sizeof(struct execargs));
			sig_init(&data->er_error);
			/* Create references for `data->er_args' */
			incref(args.ea_xdentry);
			incref(args.ea_xpath);
			incref(args.ea_xnode);
			TRY {
				assert(!task_wasconnected());
				task_connect(&data->er_error);
				if (!task_schedule_synchronous_rpc(proc,
				                                   &kernel_exec_rpc_func,
				                                   data,
				                                   TASK_RPC_FHIGHPRIO,
				                                   GFP_NORMAL)) {
					/* The main thread was already terminated. - Propagate its
					 * termination signal manually (since we may not have received
					 * it before in case our thread had been detached). */
					union wait status;
					status = FORTASK(caller, this_taskpid)->tp_status;
					THROW(E_EXIT_THREAD, status.w_status);
				}
			} EXCEPT {
				task_disconnectall();
				assert(data->er_args.ea_xdentry == args.ea_xdentry);
				assert(data->er_args.ea_xpath == args.ea_xpath);
				assert(data->er_args.ea_xnode == args.ea_xnode);
				/* NoKill, because we still got 1 more reference to each, which will be
				 * dropped after `RETHROW()' by the `FINALLY_DECREF_UNLIKELY()' above. */
				decref_nokill(args.ea_xdentry);
				decref_nokill(args.ea_xpath);
				decref_nokill(args.ea_xnode);
				kfree(data);
				RETHROW();
			}
			/* With the RPC now scheduled, 1 of a couple of things will happen:
			 *  #1: The main thread succeeds and is able to load+execute the binary.
			 *      In this case, it will signal all threads except for itself to
			 *      terminate, which is that case means us receiving a synchronous
			 *      RPC that simply causes an `E_EXIT_THREAD' exception to be thrown,
			 *      and thus `task_waitfor()' to propagate that exception.
			 *  #2: The main thread fails to load the binary.
			 *      In this case, the main thread will have used `sig_broadcast()' to wake
			 *      us up via the `&data->er_error' signal. (The signal runtime guaranties
			 *      that a non-zero return value of `sig_broadcast()' means that `wait_waitfor()'
			 *      will always return in the receiving thread, meaning that in this case we
			 *      are guarantied to be allowed to continue execution, without having to be
			 *      afraid of being terminated before we're able to clean up `data'.
			 *  #3: The RPC was executed only because the main thread has terminated.
			 *      In this case, the RPC function will have forwarded the exit status
			 *      as an E_EXIT_THREAD exception that will be handled the same way any
			 *      other exception caused by case #2 would have been.
			 */
#ifdef NDEBUG
			task_waitfor();
#else /* NDEBUG */
			{
				struct sig *recv;
				recv = task_waitfor();
				assert(recv == &data->er_error);
			}
#endif /* !NDEBUG */
			/* We only get here if the exec() failed, in which case the reason will have
			 * been stored in `data->er_except'. */
			memcpy(&THIS_EXCEPTION_DATA,
			       &data->er_except,
			       sizeof(data->er_except));
			/* On error, we re-inherit the arguments structure, however the
			 * references within are always inherited by the RPC callback! */
			kfree(data);
			/* (Re-)throw the exception that caused the exec() to fail. */
			error_throw_current();
		}
	} EXCEPT {
		execargs_fini(&args);
		RETHROW();
	}
	execargs_fini(&args);
	return state;
}


/************************************************************************/
/* execveat(), execve()                                                 */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_EXECVEAT
PRIVATE struct icpustate *FCALL
syscall_execveat_rpc(void *UNUSED(arg),
                     struct icpustate *__restrict state,
                     unsigned int reason,
                     struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		/* Actually service the exec() system call. */
		state = kernel_execveat((fd_t)sc_info->rsi_regs[0],
		                        (USER UNCHECKED char const *)sc_info->rsi_regs[1],
#ifdef __ARCH_HAVE_COMPAT
		                        (USER UNCHECKED void const *)sc_info->rsi_regs[2],
		                        (USER UNCHECKED void const *)sc_info->rsi_regs[3],
#else /* __ARCH_HAVE_COMPAT */
		                        (USER UNCHECKED char const *USER UNCHECKED const *)sc_info->rsi_regs[2],
		                        (USER UNCHECKED char const *USER UNCHECKED const *)sc_info->rsi_regs[3],
#endif /* !__ARCH_HAVE_COMPAT */
		                        (atflag_t)sc_info->rsi_regs[4],
#ifdef __ARCH_HAVE_COMPAT
		                        false,
#endif /* __ARCH_HAVE_COMPAT */
		                        state);
	}
	return state;
}

DEFINE_SYSCALL5(errno_t, execveat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED char const *USER UNCHECKED const *, argv,
                USER UNCHECKED char const *USER UNCHECKED const *, envp,
                atflag_t, flags) {
	(void)dirfd;
	(void)filename;
	(void)argv;
	(void)envp;
	(void)flags;
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &syscall_execveat_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_EXECVEAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_EXECVEAT
PRIVATE struct icpustate *FCALL
compat_syscall_execveat_rpc(void *UNUSED(arg),
                            struct icpustate *__restrict state,
                            unsigned int reason,
                            struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		/* Actually service the exec() system call. */
		state = kernel_execveat((fd_t)sc_info->rsi_regs[0],
		                        (USER UNCHECKED char const *)sc_info->rsi_regs[1],
		                        (USER UNCHECKED void const *)sc_info->rsi_regs[2],
		                        (USER UNCHECKED void const *)sc_info->rsi_regs[3],
		                        (atflag_t)sc_info->rsi_regs[4],
		                        true,
		                        state);
	}
	return state;
}

DEFINE_COMPAT_SYSCALL5(errno_t, execveat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED compat_ptr(char const) USER UNCHECKED const *, argv,
                       USER UNCHECKED compat_ptr(char const) USER UNCHECKED const *, envp,
                       atflag_t, flags) {
	(void)dirfd;
	(void)filename;
	(void)argv;
	(void)envp;
	(void)flags;
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &compat_syscall_execveat_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_EXECVEAT */

#ifdef __ARCH_WANT_SYSCALL_EXECVE
PRIVATE struct icpustate *FCALL
syscall_execve_rpc(void *UNUSED(arg),
                   struct icpustate *__restrict state,
                   unsigned int reason,
                   struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		/* Actually service the exec() system call. */
		state = kernel_execveat(AT_FDCWD,
		                        (USER UNCHECKED char const *)sc_info->rsi_regs[0],
#ifdef __ARCH_HAVE_COMPAT
		                        (USER UNCHECKED void const *)sc_info->rsi_regs[1],
		                        (USER UNCHECKED void const *)sc_info->rsi_regs[2],
#else /* __ARCH_HAVE_COMPAT */
		                        (USER UNCHECKED char const *USER UNCHECKED const *)sc_info->rsi_regs[1],
		                        (USER UNCHECKED char const *USER UNCHECKED const *)sc_info->rsi_regs[2],
#endif /* !__ARCH_HAVE_COMPAT */
		                        0,
#ifdef __ARCH_HAVE_COMPAT
		                        false,
#endif /* __ARCH_HAVE_COMPAT */
		                        state);
	}
	return state;
}

DEFINE_SYSCALL3(errno_t, execve,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED char const *USER UNCHECKED const *, argv,
                USER UNCHECKED char const *USER UNCHECKED const *, envp) {
	(void)filename;
	(void)argv;
	(void)envp;
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &syscall_execve_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_EXECVE */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_EXECVE
PRIVATE struct icpustate *FCALL
compat_syscall_execve_rpc(void *UNUSED(arg),
                          struct icpustate *__restrict state,
                          unsigned int reason,
                          struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		/* Actually service the exec() system call. */
		state = kernel_execveat(AT_FDCWD,
		                        (USER UNCHECKED char const *)sc_info->rsi_regs[0],
		                        (USER UNCHECKED void const *)sc_info->rsi_regs[1],
		                        (USER UNCHECKED void const *)sc_info->rsi_regs[2],
		                        0,
		                        true,
		                        state);
	}
	return state;
}

DEFINE_COMPAT_SYSCALL3(errno_t, execve,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED compat_ptr(char const) USER UNCHECKED const *, argv,
                       USER UNCHECKED compat_ptr(char const) USER UNCHECKED const *, envp) {
	(void)filename;
	(void)argv;
	(void)envp;
	/* Send an RPC to ourself, so we can gain access to the user-space register state. */
	task_schedule_user_rpc(THIS_TASK,
	                       &compat_syscall_execve_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_EXECVE */




/************************************************************************/
/* getdrives()                                                          */
/************************************************************************/
#ifdef __ARCH_WANT_SYSCALL_GETDRIVES
DEFINE_SYSCALL0(syscall_slong_t, getdrives) {
	unsigned int i;
	syscall_ulong_t mask, result = 0;
	struct vfs *v = THIS_FS->f_vfs;
	for (i = 0, mask = 1; i < VFS_DRIVECOUNT; ++i, mask <<= 1) {
		if (ATOMIC_READ(v->v_drives[i]) != NULL)
			result |= mask;
	}
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
	REF struct superblock *super;
#ifndef _STATFS_MATCHES_STATFS64
	struct statfs data;
#endif /* !_STATFS_MATCHES_STATFS64 */
	validate_writable(result, sizeof(*result));
	super = handle_get_superblock_relaxed((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
#ifdef _STATFS_MATCHES_STATFS64
		superblock_statfs(super, result);
#else /* _STATFS_MATCHES_STATFS64 */
		superblock_statfs(super, &data);
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
	REF struct superblock *super;
	struct statfs data;
	validate_writable(result, sizeof(*result));
	super = handle_get_superblock_relaxed((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_statfs(super, &data);
	}
	COMPILER_WRITE_BARRIER();
	statfs_to_compat_statfs32(&data, result);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTATFS */

#ifdef __ARCH_WANT_SYSCALL_FSTATFS64
DEFINE_SYSCALL2(errno_t, fstatfs64, fd_t, fd,
                USER UNCHECKED struct_statfs64 *, result) {
	REF struct superblock *super;
	validate_writable(result, sizeof(*result));
	super = handle_get_superblock_relaxed((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
#ifdef __USE_FILE_OFFSET64
		superblock_statfs(super, result);
#else /* __USE_FILE_OFFSET64 */
		{
			struct statfs data;
			superblock_statfs(super, &data);
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
	REF struct superblock *super;
	struct statfs data;
	validate_writable(result, sizeof(*result));
	super = handle_get_superblock_relaxed((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_statfs(super, &data);
	}
	COMPILER_WRITE_BARRIER();
	statfs_to_compat_statfs64(&data, result);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_FSTATFS64 */

PRIVATE REF struct superblock *KCALL
get_superblock_from_path(USER CHECKED char const *filename) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	REF struct superblock *result;
	/* Traverse the given path in its entirety. */
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         /* Ignore trailing slashes to allow stat() with dir-like paths. */
	                         f->f_mode.f_atflag | FS_MODE_FIGNORE_TRAILING_SLASHES,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	result = (REF struct superblock *)incref(node->i_super);
	decref_unlikely(node);
	return result;
}

#ifdef __ARCH_WANT_SYSCALL_STATFS
DEFINE_SYSCALL2(errno_t, statfs,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct_statfs32 *, result) {
	REF struct superblock *super;
#ifndef _STATFS_MATCHES_STATFS64
	struct statfs data;
#endif /* !_STATFS_MATCHES_STATFS64 */
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_superblock_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
#ifdef _STATFS_MATCHES_STATFS64
		superblock_statfs(super, result);
#else /* _STATFS_MATCHES_STATFS64 */
		superblock_statfs(super, &data);
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
	REF struct superblock *super;
	struct statfs data;
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_superblock_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_statfs(super, &data);
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
	REF struct superblock *super;
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_superblock_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_statfs(super, result);
	}
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_STATFS64 */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_STATFS64
DEFINE_COMPAT_SYSCALL2(errno_t, statfs64,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_statfs64 *, result) {
	struct statfs st;
	REF struct superblock *super;
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_superblock_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_statfs(super, &st);
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
/* Verify that the calling thread is allowed to assign arbitrary
 * timestamp to the given `node's last-accessed and last-modified
 * fields. */
PRIVATE NONNULL((1)) void KCALL
inode_request_arbitrary_timestamps(struct inode *__restrict node) {
	/* Caller must be owner, or have `CAP_FOWNER' */
	inode_loadattr(node);
	if (node->i_fileuid != cred_getfsuid())
		require(CAP_FOWNER); /* FIXME: This fails with EACCES, but POSIX wants EPERM... */
}

PRIVATE NONNULL((1)) void KCALL
inode_request_current_timestamps(struct inode *__restrict node) {
	/* Caller must be owner, or have `CAP_DAC_OVERRIDE' or `CAP_FOWNER' */
	if (!inode_tryaccess(node, W_OK) && !capable(CAP_DAC_OVERRIDE))
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
	struct fs *f = THIS_FS;
	struct timespec atm, mtm;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         f->f_mode.f_atflag,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, sizeof(*times));
		atm.tv_sec  = (time_t)times->actime;
		atm.tv_nsec = 0;
		mtm.tv_sec  = (time_t)times->modtime;
		mtm.tv_nsec = 0;
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIME */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIME
DEFINE_COMPAT_SYSCALL2(errno_t, utime,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_utimbuf32 const *, times) {
	struct fs *f = THIS_FS;
	struct timespec atm, mtm;
	REF struct inode *node;
	compat_validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         f->f_mode.f_atflag,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, sizeof(*times));
		atm.tv_sec  = (time_t)times->actime;
		atm.tv_nsec = 0;
		mtm.tv_sec  = (time_t)times->modtime;
		mtm.tv_nsec = 0;
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		if (!capable(CAP_DAC_OVERRIDE))
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
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
	struct fs *f = THIS_FS;
	struct timespec atm, mtm;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         f->f_mode.f_atflag,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, sizeof(*times));
		atm.tv_sec  = (time_t)times->actime;
		atm.tv_nsec = 0;
		mtm.tv_sec  = (time_t)times->modtime;
		mtm.tv_nsec = 0;
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIME64 || __ARCH_WANT_SYSCALL_UTIME_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_UTIME64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIME_TIME64))
DEFINE_COMPAT_SYSCALL2(errno_t, utime64,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_utimbuf64 const *, times) {
	struct fs *f = THIS_FS;
	struct timespec atm, mtm;
	REF struct inode *node;
	compat_validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         f->f_mode.f_atflag,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, sizeof(*times));
		atm.tv_sec  = (time_t)times->actime;
		atm.tv_nsec = 0;
		mtm.tv_sec  = (time_t)times->modtime;
		mtm.tv_nsec = 0;
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
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
	struct fs *f = THIS_FS;
	struct timespec atm, mtm;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         f->f_mode.f_atflag,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIMES */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIMES
DEFINE_COMPAT_SYSCALL2(errno_t, utimes,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timeval32 const *, times) {
	struct fs *f = THIS_FS;
	struct timespec atm, mtm;
	REF struct inode *node;
	compat_validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         f->f_mode.f_atflag,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
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
	struct fs *f = THIS_FS;
	struct timespec atm, mtm;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         f->f_mode.f_atflag,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
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
	struct fs *f = THIS_FS;
	struct timespec atm, mtm;
	REF struct inode *node;
	compat_validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         f->f_mode.f_atflag,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
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
PRIVATE ATTR_RETNONNULL WUNUSED REF struct inode *KCALL
lookup_inode_for_futimesat(fd_t dirfd, USER UNCHECKED char const *filename) {
	REF struct inode *result;
	if (filename) {
		struct fs *f = THIS_FS;
		validate_readable(filename, 1);
		result = path_traversefull_at(f,
		                              (unsigned int)dirfd,
		                              filename,
		                              true,
		                              f->f_mode.f_atflag,
		                              NULL,
		                              NULL,
		                              NULL,
		                              NULL);
	} else {
		result = handle_get_inode((unsigned int)dirfd);
	}
	return result;
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_FUTIMESAT
DEFINE_SYSCALL3(errno_t, futimesat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timeval32 const *, times) {
	struct timespec atm, mtm;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = lookup_inode_for_futimesat(dirfd, filename);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_FUTIMESAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_FUTIMESAT
DEFINE_COMPAT_SYSCALL3(errno_t, futimesat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timeval32 const *, times) {
	struct timespec atm, mtm;
	REF struct inode *node;
	node = lookup_inode_for_futimesat(dirfd, filename);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
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
	REF struct inode *node;
	node = lookup_inode_for_futimesat(dirfd, filename);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
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
	REF struct inode *node;
	node = lookup_inode_for_futimesat(dirfd, filename);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		TIMEVAL_TO_TIMESPEC(&times[0], &atm);
		TIMEVAL_TO_TIMESPEC(&times[1], &mtm);
		COMPILER_READ_BARRIER();
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
	}
	inode_chtime(node, &atm, &mtm, NULL);
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
PRIVATE ATTR_RETNONNULL WUNUSED REF struct inode *KCALL
lookup_inode_for_utimensat(fd_t dirfd, USER UNCHECKED char const *filename,
                           atflag_t flags) {
	REF struct inode *result;
	if (filename) {
		struct fs *f = THIS_FS;
		VALIDATE_FLAGSET(flags,
		                 AT_SYMLINK_NOFOLLOW | AT_CHANGE_CTIME | AT_DOSPATH,
		                 E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS);
		validate_readable(filename, 1);
		result = path_traversefull_at(f,
		                              (unsigned int)dirfd,
		                              filename,
		                              !(flags & AT_SYMLINK_NOFOLLOW),
		                              fs_getmode_for(f, flags),
		                              NULL,
		                              NULL,
		                              NULL,
		                              NULL);
	} else {
		VALIDATE_FLAGSET(flags,
		                 AT_CHANGE_CTIME,
		                 E_INVALID_ARGUMENT_CONTEXT_UTIMENSAT_FLAGS_NOFILENAME);
		result = handle_get_inode((unsigned int)dirfd);
	}
	return result;
}
#endif /* ... */

#ifdef __ARCH_WANT_SYSCALL_UTIMENSAT
DEFINE_SYSCALL4(errno_t, utimensat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timespec32 const *, times,
                atflag_t, flags) {
	struct timespec atm, mtm, ctm;
	struct timespec *patm, *pmtm;
	struct timespec *pctm = NULL;
	REF struct inode *node;
	node = lookup_inode_for_utimensat(dirfd, filename, flags);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		atm.tv_sec  = (time_t)times[0].tv_sec;
		atm.tv_nsec = (syscall_ulong_t)times[0].tv_nsec;
		mtm.tv_sec  = (time_t)times[1].tv_sec;
		mtm.tv_nsec = (syscall_ulong_t)times[1].tv_nsec;
		if unlikely(flags & AT_CHANGE_CTIME) {
			ctm.tv_sec  = (time_t)times[2].tv_sec;
			ctm.tv_nsec = (syscall_ulong_t)times[2].tv_nsec;
			/* Specify CTMIE as OMIT is the same as not passing `AT_CHANGE_CTIME'! */
			if (ctm.tv_nsec != UTIME_OMIT) {
				require(CAP_AT_CHANGE_CTIME);
				pctm = &ctm;
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
		    (pctm && pctm->tv_nsec == UTIME_NOW)) {
			struct timespec now;
			/* Special case: Less permissions are needed to do a touch! */
			if (atm.tv_nsec == UTIME_NOW &&
			    mtm.tv_nsec == UTIME_NOW && !pctm)
				goto do_touch;
			now = realtime();
			if (atm.tv_nsec == UTIME_NOW)
				atm = now;
			if (mtm.tv_nsec == UTIME_NOW)
				mtm = now;
			if (pctm && pctm->tv_nsec == UTIME_NOW)
				*pctm = now;
		}
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
do_touch:
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
		patm = &atm;
		pmtm = &mtm;
	}
	inode_chtime(node, patm, pmtm, pctm);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIMENSAT */

#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT
DEFINE_COMPAT_SYSCALL4(errno_t, utimensat, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timespec32 const *, times,
                       atflag_t, flags) {
	struct timespec atm, mtm, ctm;
	struct timespec *patm, *pmtm;
	struct timespec *pctm = NULL;
	REF struct inode *node;
	node = lookup_inode_for_utimensat(dirfd, filename, flags);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		atm.tv_sec  = (time_t)times[0].tv_sec;
		atm.tv_nsec = (syscall_ulong_t)times[0].tv_nsec;
		mtm.tv_sec  = (time_t)times[1].tv_sec;
		mtm.tv_nsec = (syscall_ulong_t)times[1].tv_nsec;
		if unlikely(flags & AT_CHANGE_CTIME) {
			ctm.tv_sec  = (time_t)times[2].tv_sec;
			ctm.tv_nsec = (syscall_ulong_t)times[2].tv_nsec;
			/* Specify CTMIE as OMIT is the same as not passing `AT_CHANGE_CTIME'! */
			if (ctm.tv_nsec != UTIME_OMIT) {
				require(CAP_AT_CHANGE_CTIME);
				pctm = &ctm;
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
		    (pctm && pctm->tv_nsec == UTIME_NOW)) {
			struct timespec now;
			/* Special case: Less permissions are needed to do a touch! */
			if (atm.tv_nsec == UTIME_NOW &&
			    mtm.tv_nsec == UTIME_NOW && !pctm)
				goto do_touch;
			now = realtime();
			if (atm.tv_nsec == UTIME_NOW)
				atm = now;
			if (mtm.tv_nsec == UTIME_NOW)
				mtm = now;
			if (pctm && pctm->tv_nsec == UTIME_NOW)
				*pctm = now;
		}
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
do_touch:
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
		patm = &atm;
		pmtm = &mtm;
	}
	inode_chtime(node, patm, pmtm, pctm);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT */

#if (defined(__ARCH_WANT_SYSCALL_UTIMENSAT64) || \
     defined(__ARCH_WANT_SYSCALL_UTIMENSAT_TIME64))
#ifdef __ARCH_WANT_SYSCALL_UTIMENSAT64
DEFINE_SYSCALL4(errno_t, utimensat64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timespec64 const *, times,
                atflag_t, flags)
#else /* __ARCH_WANT_SYSCALL_UTIMENSAT64 */
DEFINE_SYSCALL4(errno_t, utimensat_time64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct timespec64 const *, times,
                atflag_t, flags)
#endif /* !__ARCH_WANT_SYSCALL_UTIMENSAT64 */
{
	struct timespec atm, mtm, ctm;
	struct timespec *patm, *pmtm;
	struct timespec *pctm = NULL;
	REF struct inode *node;
	node = lookup_inode_for_utimensat(dirfd, filename, flags);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		validate_readable(times, 2 * sizeof(*times));
		atm.tv_sec  = (time_t)times[0].tv_sec;
		atm.tv_nsec = (syscall_ulong_t)times[0].tv_nsec;
		mtm.tv_sec  = (time_t)times[1].tv_sec;
		mtm.tv_nsec = (syscall_ulong_t)times[1].tv_nsec;
		if unlikely(flags & AT_CHANGE_CTIME) {
			ctm.tv_sec  = (time_t)times[2].tv_sec;
			ctm.tv_nsec = (syscall_ulong_t)times[2].tv_nsec;
			/* Specify CTMIE as OMIT is the same as not passing `AT_CHANGE_CTIME'! */
			if (ctm.tv_nsec != UTIME_OMIT) {
				require(CAP_AT_CHANGE_CTIME);
				pctm = &ctm;
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
		    (pctm && pctm->tv_nsec == UTIME_NOW)) {
			struct timespec now;
			/* Special case: Less permissions are needed to do a touch! */
			if (atm.tv_nsec == UTIME_NOW &&
			    mtm.tv_nsec == UTIME_NOW && !pctm)
				goto do_touch;
			now = realtime();
			if (atm.tv_nsec == UTIME_NOW)
				atm = now;
			if (mtm.tv_nsec == UTIME_NOW)
				mtm = now;
			if (pctm && pctm->tv_nsec == UTIME_NOW)
				*pctm = now;
		}
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
do_touch:
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
		patm = &atm;
		pmtm = &mtm;
	}
	inode_chtime(node, patm, pmtm, pctm);
	return -EOK;
}
#endif /* __ARCH_WANT_SYSCALL_UTIMENSAT64 || __ARCH_WANT_SYSCALL_UTIMENSAT_TIME64 */

#if (defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64) || \
     defined(__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT_TIME64))
#ifdef __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64
DEFINE_COMPAT_SYSCALL4(errno_t, utimensat64, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timespec64 const *, times,
                       atflag_t, flags)
#else /* __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64 */
DEFINE_COMPAT_SYSCALL4(errno_t, utimensat_time64, fd_t, dirfd,
                       USER UNCHECKED char const *, filename,
                       USER UNCHECKED struct compat_timespec64 const *, times,
                       atflag_t, flags)
#endif /* !__ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64 */
{
	struct timespec atm, mtm, ctm;
	struct timespec *patm, *pmtm;
	struct timespec *pctm = NULL;
	REF struct inode *node;
	node = lookup_inode_for_utimensat(dirfd, filename, flags);
	FINALLY_DECREF_UNLIKELY(node);
	if (times) {
		compat_validate_readable(times, 2 * sizeof(*times));
		atm.tv_sec  = (time_t)times[0].tv_sec;
		atm.tv_nsec = (syscall_ulong_t)times[0].tv_nsec;
		mtm.tv_sec  = (time_t)times[1].tv_sec;
		mtm.tv_nsec = (syscall_ulong_t)times[1].tv_nsec;
		if unlikely(flags & AT_CHANGE_CTIME) {
			ctm.tv_sec  = (time_t)times[2].tv_sec;
			ctm.tv_nsec = (syscall_ulong_t)times[2].tv_nsec;
			/* Specify CTMIE as OMIT is the same as not passing `AT_CHANGE_CTIME'! */
			if (ctm.tv_nsec != UTIME_OMIT) {
				require(CAP_AT_CHANGE_CTIME);
				pctm = &ctm;
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
		    (pctm && pctm->tv_nsec == UTIME_NOW)) {
			struct timespec now;
			/* Special case: Less permissions are needed to do a touch! */
			if (atm.tv_nsec == UTIME_NOW &&
			    mtm.tv_nsec == UTIME_NOW && !pctm)
				goto do_touch;
			now = realtime();
			if (atm.tv_nsec == UTIME_NOW)
				atm = now;
			if (mtm.tv_nsec == UTIME_NOW)
				mtm = now;
			if (pctm && pctm->tv_nsec == UTIME_NOW)
				*pctm = now;
		}
		inode_request_arbitrary_timestamps(node);
	} else {
		/* Caller must be able to write to `node' */
do_touch:
		inode_request_current_timestamps(node);
		atm = mtm = realtime();
		patm = &atm;
		pmtm = &mtm;
	}
	inode_chtime(node, patm, pmtm, pctm);
	return -EOK;
}
#endif /* __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT64 || __ARCH_WANT_COMPAT_SYSCALL_UTIMENSAT_TIME64 */


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_SYSCALLS_C */
