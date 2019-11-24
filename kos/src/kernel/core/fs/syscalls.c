/* Copyright (c) 2019 Griefer@Work                                            *
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
 *    in a product, an acknowledgement in the product documentation would be  *
 *    appreciated but is not required.                                        *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FS_SYSCALLS_C
#define GUARD_KERNEL_CORE_FS_SYSCALLS_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1
#define _LARGEFILE64_SOURCE 1

#include <kernel/compiler.h>

#include <dev/block.h>
#include <dev/char.h>
#include <dev/ttybase.h>
#include <fs/file.h>
#include <fs/node.h>
#include <fs/vfs.h>
#include <kernel/debugtrap.h>
#include <kernel/personality.h>
#include <kernel/except.h>
#include <kernel/handle.h>
#include <kernel/printk.h>
#include <kernel/syscall.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/pid.h>
#include <sched/rpc.h>

#include <hybrid/atomic.h>
#include <hybrid/minmax.h>

#include <kos/compat/linux-stat.h>
#include <kos/debugtrap.h>
#include <kos/except-inval.h>
#include <kos/kernel/handle.h>
#include <sys/mount.h>
#include <sys/statfs.h>

#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <format-printer.h>
#include <malloca.h>
#include <signal.h>
#include <stddef.h>
#include <string.h>

#include <librpc/rpc.h>


DECL_BEGIN

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


#ifdef __NR_access
DEFINE_SYSCALL2(errno_t, access,
                USER UNCHECKED char const *, filename,
                syscall_ulong_t, type) {
	return sys_faccessat(AT_FDCWD, filename, type, 0);
}
#endif /* __NR_access */

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
	mode |= ATOMIC_READ(f->f_atflag) & PATH_PRINT_MODE_DOSPATH;
#else
	if (ATOMIC_READ(f->f_atflag) & FS_MODE_FDOSPATH)
		mode |= PATH_PRINT_MODE_DOSPATH;
#endif
	{
		FINALLY_DECREF_UNLIKELY(cwd);
		FINALLY_DECREF_UNLIKELY(root);
		reqlen = path_sprintex(buf, bufsize, cwd, mode, root);
	}
	if unlikely(reqlen > bufsize) /* return -ERANGE; */
		THROW(E_BUFFER_TOO_SMALL, reqlen, bufsize);
	return reqlen;
}


DEFINE_SYSCALL5(errno_t, fmknodat, fd_t, dirfd,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, dev_t, dev, atflag_t, flags) {
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
	VALIDATE_FLAGSET(mode, 07777 | S_IFMT,
	                 E_INVALID_ARGUMENT_CONTEXT_MKNOD_MODE);
	if ((mode & S_IFMT) != S_IFREG &&
	    (mode & S_IFMT) != S_IFCHR &&
	    (mode & S_IFMT) != S_IFBLK) {
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
		                              dev,
		                              fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKNOD_FNOCASE
		                                                        : DIRECTORY_MKNOD_FNORMAL,
		                              NULL);
	}
	decref(result_node);
	return -EOK;
}

DEFINE_SYSCALL4(errno_t, mknodat, fd_t, dirfd,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, dev_t, dev) {
	return sys_fmknodat(dirfd, nodename, mode, (__dev_t)dev, 0);
}

DEFINE_SYSCALL3(errno_t, mknod,
                USER UNCHECKED char const *, nodename,
                mode_t, mode, dev_t, dev) {
	return sys_fmknodat(AT_FDCWD, nodename, mode, (__dev_t)dev, 0);
}


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
	VALIDATE_FLAGSET(mode, 07777,
	                 E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE);
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
		                             mode & ~ATOMIC_READ(f->f_umask),
		                             fs_getuid(f),
		                             fs_getgid(f),
		                             fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKDIR_FNOCASE
		                                                       : DIRECTORY_MKDIR_FNORMAL,
		                             NULL);
	}
	decref(result_dir);
	return -EOK;
}

DEFINE_SYSCALL3(errno_t, mkdirat, fd_t, dirfd,
                USER UNCHECKED char const *, pathname, mode_t, mode) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir, *result_dir;
	fsmode_t fsmode = ATOMIC_READ(f->f_atflag);
	validate_readable(pathname, 1);
	VALIDATE_FLAGSET(mode, 07777,
	                 E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE);
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
		                             mode & ~ATOMIC_READ(f->f_umask),
		                             fs_getuid(f),
		                             fs_getgid(f),
		                             fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKDIR_FNOCASE
		                                                       : DIRECTORY_MKDIR_FNORMAL,
		                             NULL);
	}
	decref(result_dir);
	return -EOK;
}

DEFINE_SYSCALL2(errno_t, mkdir,
                USER UNCHECKED char const *, pathname, mode_t, mode) {
	char const *last_seg;
	u16 last_seglen;
	struct fs *f = THIS_FS;
	REF struct path *p;
	REF struct directory_node *dir, *result_dir;
	fsmode_t fsmode = ATOMIC_READ(f->f_atflag);
	validate_readable(pathname, 1);
	VALIDATE_FLAGSET(mode, 07777,
	                 E_INVALID_ARGUMENT_CONTEXT_MKDIR_MODE);
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
		                             mode & ~ATOMIC_READ(f->f_umask),
		                             fs_getuid(f),
		                             fs_getgid(f),
		                             fsmode & FS_MODE_FDOSPATH ? DIRECTORY_MKDIR_FNOCASE
		                                                       : DIRECTORY_MKDIR_FNORMAL,
		                             NULL);
	}
	decref(result_dir);
	return -EOK;
}


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
	fsmode      = ATOMIC_READ(f->f_atflag);
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
	fsmode      = ATOMIC_READ(f->f_atflag) | FS_MODE_FIGNORE_TRAILING_SLASHES;
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
	fsmode = ATOMIC_READ(f->f_atflag);
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
	fsmode = ATOMIC_READ(f->f_atflag);
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



DEFINE_SYSCALL2(errno_t, link,
                USER UNCHECKED char const *, oldpath,
                USER UNCHECKED char const *, newpath) {
	return sys_linkat(AT_FDCWD, oldpath,
	                  AT_FDCWD, newpath,
	                  0);
}
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

DEFINE_SYSCALL2(errno_t, rename,
                USER UNCHECKED char const *, oldpath,
                USER UNCHECKED char const *, newpath) {
	return sys_frenameat(AT_FDCWD, oldpath,
	                     AT_FDCWD, newpath, 0);
}
DEFINE_SYSCALL4(errno_t, renameat,
                fd_t, olddirfd, USER UNCHECKED char const *, oldpath,
                fd_t, newdirfd, USER UNCHECKED char const *, newpath) {
	return sys_frenameat(olddirfd, oldpath,
	                     newdirfd, newpath, 0);
}
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

DEFINE_SYSCALL2(errno_t, umount2,
                USER UNCHECKED char const *, target,
                syscall_ulong_t, flags) {
	struct path *p;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
	/* Require mounting rights. */
	cred_require_mount();

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
		path_umount(p);
	}
	return -EOK;
}

#ifdef __NR_umount
DEFINE_SYSCALL1(errno_t, umount,
                USER UNCHECKED char const *, special_file) {
	return sys_umount2(special_file, 0);
}
#endif /* __NR_umount */

DEFINE_SYSCALL5(errno_t, mount,
                USER UNCHECKED char const *, source,
                USER UNCHECKED char const *, target,
                USER UNCHECKED char const *, filesystemtype,
                syscall_ulong_t, mountflags,
                USER UNCHECKED void const *, data) {
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
	/* Require mounting rights. */
	cred_require_mount();
	fsmode = ATOMIC_READ(f->f_atflag) | FS_MODE_FIGNORE_TRAILING_SLASHES;
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
		decref(super);
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




#ifdef __NR_truncate64
DEFINE_SYSCALL2(errno_t, truncate64,
                USER UNCHECKED char const *, pathname,
                uint64_t, length)
#else /* __NR_truncate64 */
DEFINE_SYSCALL2(errno_t, truncate,
                USER UNCHECKED char const *, pathname,
                syscall_ulong_t, length)
#endif /* !__NR_truncate64 */
{
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(pathname, 1);
	node = path_traversefull(f,
	                         pathname,
	                         true,
	                         ATOMIC_READ(f->f_atflag),
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


#ifdef __NR_truncate64
DEFINE_SYSCALL2(errno_t, truncate,
                USER UNCHECKED char const *, pathname,
                syscall_ulong_t, length) {
	return sys_truncate64(pathname, length);
}
#endif /* __NR_truncate64 */


DEFINE_SYSCALL1(errno_t, chdir,
                USER UNCHECKED char const *, pathname) {
	REF struct path *old_cwd;
	REF struct path *new_cwd;
	REF struct path *root;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
again:
	sync_read(&f->f_pathlock);
	fsmode  = ATOMIC_READ(f->f_atflag);
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

DEFINE_SYSCALL1(errno_t, chroot,
                USER UNCHECKED char const *, pathname) {
	REF struct path *cwd;
	REF struct path *new_root;
	REF struct path *old_root;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
again:
	fsmode = ATOMIC_READ(f->f_atflag);
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

DEFINE_SYSCALL2(errno_t, fchmod, fd_t, fd, mode_t, mode) {
	REF struct inode *node;
	VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE);
	node = handle_get_inode((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chmod(node,
		            07777,
		            mode);
	}
	return -EOK;
}

DEFINE_SYSCALL2(errno_t, chmod, USER CHECKED char const *, filename, mode_t, mode) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	VALIDATE_FLAGSET(mode, 07777, E_INVALID_ARGUMENT_CONTEXT_CHMOD_MODE);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_chmod(node,
		            07777,
		            mode);
	}
	return -EOK;
}

DEFINE_SYSCALL4(errno_t, fchmodat, fd_t, dirfd,
                USER CHECKED char const *, filename,
                mode_t, mode, atflag_t, flags) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
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
		inode_chmod(node,
		            07777,
		            mode);
	}
	return -EOK;
}

#ifdef __NR_fchown32
DEFINE_SYSCALL3(errno_t, fchown32,
                fd_t, fd, uint32_t, owner, uint32_t, group)
#else /* __NR_fchown32 */
DEFINE_SYSCALL3(errno_t, fchown,
                fd_t, fd, uint32_t, owner, uint32_t, group)
#endif /* !__NR_fchown32 */
{
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

#ifdef __NR_fchown32
DEFINE_SYSCALL3(errno_t, fchown, fd_t, fd, uint16_t, owner, uint16_t, group) {
	return sys_fchown32(fd, owner, group);
}
#endif /* __NR_fchown32 */

#ifdef __NR_lchown32
DEFINE_SYSCALL3(errno_t, lchown32,
                USER UNCHECKED char const *, filename,
                uint32_t, owner, uint32_t, group)
#else /* __NR_lchown32 */
DEFINE_SYSCALL3(errno_t, lchown,
                USER UNCHECKED char const *, filename,
                uint32_t, owner, uint32_t, group)
#endif /* !__NR_lchown32 */
{
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         false,
	                         ATOMIC_READ(f->f_atflag),
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

#ifdef __NR_lchown32
DEFINE_SYSCALL3(errno_t, chown32,
                USER UNCHECKED char const *, filename,
                uint32_t, owner, uint32_t, group)
#else
DEFINE_SYSCALL3(errno_t, chown,
                USER UNCHECKED char const *, filename,
                uint32_t, owner, uint32_t, group)
#endif
{
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_atflag),
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
DEFINE_SYSCALL5(errno_t, fchownat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                uint32_t, owner, uint32_t, group,
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


#ifdef __NR_lchown32
DEFINE_SYSCALL3(errno_t, lchown,
                USER UNCHECKED char const *, filename,
                uint16_t, owner, uint16_t, group) {
	return sys_lchown32(filename, owner, group);
}
#endif /* __NR_lchown32 */

#ifdef __NR_chown32
DEFINE_SYSCALL3(errno_t, chown,
                USER UNCHECKED char const *, filename,
                uint16_t, owner, uint16_t, group) {
	return sys_chown32(filename, owner, group);
}
#endif /* __NR_chown32 */


DEFINE_SYSCALL1(mode_t, umask, mode_t, mode) {
	struct fs *f = THIS_FS;
	return ATOMIC_XCH(f->f_umask, mode & 0777);
}

DEFINE_SYSCALL1(uint64_t, fsmode, uint64_t, mode) {
	struct fs *f = THIS_FS;
	union {
		struct ATTR_PACKED {
			u32 f_atmask;
			u32 f_atflag;
		};
		u64 f_mode;
	} new_mode;
	new_mode.f_mode = mode;
	new_mode.f_atmask &= ~FS_MODE_FALWAYS0MASK;
	new_mode.f_atmask |= FS_MODE_FALWAYS1MASK;
	new_mode.f_atflag &= ~FS_MODE_FALWAYS0FLAG;
	new_mode.f_atflag |= FS_MODE_FALWAYS1FLAG;
	return ATOMIC_XCH(f->f_mode, new_mode.f_mode);
}

DEFINE_SYSCALL0(errno_t, sync) {
	TRY {
		superblock_syncall();
	} EXCEPT {
		error_printf("sync()");
		RETHROW();
	}
	return -EOK;
}

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

DEFINE_SYSCALL3(fd_t, open,
                USER UNCHECKED char const *, filename,
                oflag_t, oflags, mode_t, mode) {
	return sys_openat(AT_FDCWD,
	                  filename,
	                  oflags,
	                  mode);
}

DEFINE_SYSCALL2(fd_t, creat,
                USER UNCHECKED char const *, filename,
                mode_t, mode) {
	return sys_openat(AT_FDCWD,
	                  filename,
	                  O_CREAT | O_WRONLY | O_TRUNC,
	                  mode);
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2, 4, 7, 8, 9, 10, 11, 12, 13)) bool KCALL
openat_create_follow_symlink_dynamic_impl(struct fs *__restrict f,
                                          struct path *__restrict root,
                                          fsmode_t fsmode,
                                          /*in|out*/ u32 *__restrict pmax_remaining_links,
                                          oflag_t oflags, mode_t mode,
                                          struct symlink_node *__restrict sl_node,
                                          /*in|out*/ REF struct path **__restrict presult_containing_path,
                                          /*in|out*/ REF struct directory_node **__restrict presult_containing_directory,
                                          /*in|out*/ REF struct directory_entry **__restrict presult_containing_dirent,
                                          /*in|out*/ REF struct inode **__restrict presult_inode,
                                          /*out*/ bool *__restrict pwas_newly_created,
                                          /*in|out*/ size_t *__restrict pbufsize) {
	char const *last_seg;
	u16 last_seglen;
	REF struct inode *new_result_inode;
	REF struct path *new_result_containing_path;
	REF struct directory_node *new_result_containing_directory;
	REF struct directory_entry *new_result_containing_dirent;
	size_t bufsize = *pbufsize;
	char *buf;
	buf = (char *)malloca(bufsize);
	TRY {
		size_t reqsize;
		assert(sl_node->i_type->it_symlink.sl_readlink_dynamic);
		reqsize = (*sl_node->i_type->it_symlink.sl_readlink_dynamic)(sl_node,
		                                                             buf,
		                                                             bufsize);
		if unlikely(reqsize > bufsize) {
			/* Must try again with a larger buffer size. */
			*pbufsize = reqsize;
			freea(buf);
			return false;
		}
		/* Traverse the symlink text. */
		new_result_containing_path = path_traversen_ex(f,
		                                               *presult_containing_path,
		                                               root,
		                                               buf,
		                                               reqsize,
		                                               &last_seg,
		                                               &last_seglen,
		                                               fsmode,
		                                               pmax_remaining_links);
		decref(*presult_containing_path);
		*presult_containing_path = new_result_containing_path;

		sync_read(*presult_containing_path);
		new_result_containing_directory = (REF struct directory_node *)
		incref((*presult_containing_path)->p_inode);
		sync_endread(*presult_containing_path);
		decref(*presult_containing_directory);
		*presult_containing_directory = new_result_containing_directory;

		/* Repeat the create() function with the symlink's dereferenced text. */
		new_result_inode = directory_creatfile(new_result_containing_directory,
		                                       last_seg,
		                                       last_seglen,
		                                       oflags & (O_CREAT | /*O_EXCL|*/ O_DOSPATH),
		                                       fs_getuid(f),
		                                       fs_getgid(f),
		                                       mode,
		                                       &new_result_containing_dirent,
		                                       pwas_newly_created);
		decref(*presult_containing_dirent);
		*presult_containing_dirent = new_result_containing_dirent;
		decref(*presult_inode);
		*presult_inode = new_result_inode;
	} EXCEPT {
		freea(buf);
		RETHROW();
	}
	freea(buf);
	return true;
}

PRIVATE ATTR_NOINLINE NONNULL((1, 2, 4, 7, 8, 9, 10, 11, 12)) void KCALL
openat_create_follow_symlink_dynamic(struct fs *__restrict f,
                                     struct path *__restrict root,
                                     fsmode_t fsmode,
                                     /*in|out*/ u32 *__restrict pmax_remaining_links,
                                     oflag_t oflags, mode_t mode,
                                     struct symlink_node *__restrict sl_node,
                                     /*in|out*/ REF struct path **__restrict presult_containing_path,
                                     /*in|out*/ REF struct directory_node **__restrict presult_containing_directory,
                                     /*in|out*/ REF struct directory_entry **__restrict presult_containing_dirent,
                                     /*in|out*/ REF struct inode **__restrict presult_inode,
                                     /*out*/ bool *__restrict pwas_newly_created) {
	size_t bufsize = 128;
	for (;;) {
		bool ok;
		ok = openat_create_follow_symlink_dynamic_impl(f,
		                                               root,
		                                               fsmode,
		                                               pmax_remaining_links,
		                                               oflags,
		                                               mode,
		                                               sl_node,
		                                               presult_containing_path,
		                                               presult_containing_directory,
		                                               presult_containing_dirent,
		                                               presult_inode,
		                                               pwas_newly_created,
		                                               &bufsize);
		if (ok)
			break;
	}
}


DEFINE_SYSCALL4(fd_t, openat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                oflag_t, oflags, mode_t, mode) {
	unsigned int result;
	struct fs *f = THIS_FS;
	fsmode_t fsmode;
	REF struct handle result_handle;
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
	fsmode = fs_getmode_for(f, (atflag_t)fsmode);
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
		result_handle.h_type = HANDLE_TYPE_PATH;
		result_handle.h_data = path_traverse_at_recent(f,
		                                               (unsigned int)dirfd,
		                                               filename,
		                                               NULL,
		                                               NULL,
		                                               fsmode,
		                                               NULL);
	} else {
		REF struct inode *result_inode;
		REF struct path *result_containing_path;
		REF struct directory_node *result_containing_directory;
		REF struct directory_entry *result_containing_dirent;
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
		if (!(oflags & O_CREAT)) {
			/* Simple case: open an existing file. */
			result_inode = path_traversefull_at(f,
			                                    (unsigned int)dirfd,
			                                    filename,
			                                    !(oflags & (O_NOFOLLOW | O_SYMLINK)),
			                                    fsmode,
			                                    NULL,
			                                    &result_containing_path,
			                                    &result_containing_directory,
			                                    &result_containing_dirent);
			/* Clear the file if O_TRUNC was given. */
			if ((oflags & O_TRUNC) && (oflags & O_ACCMODE) != O_RDONLY) {
				TRY {
					inode_truncate(result_inode, 0);
				} EXCEPT {
					decref(result_inode);
					decref(result_containing_path);
					decref(result_containing_directory);
					decref(result_containing_dirent);
					RETHROW();
				}
			}
		} else {
			/* (Potentially) create a new file. */
			char const *last_seg;
			u16 last_seglen;
			u32 max_remaining_links = ATOMIC_READ(f->f_lnkmax);
			REF struct path *cwd, *root;
			sync_read(&f->f_pathlock);
			root = incref(f->f_root);
			if ((unsigned int)dirfd == HANDLE_SYMBOLIC_FDCWD) {
				cwd = incref(f->f_cwd);
				sync_endread(&f->f_pathlock);
			} else if ((unsigned int)dirfd == HANDLE_SYMBOLIC_FDROOT) {
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
				FINALLY_DECREF_UNLIKELY(root);
				{
					FINALLY_DECREF_UNLIKELY(cwd);
					result_containing_path = path_traverse_ex(f,
					                                          cwd,
					                                          root,
					                                          filename,
					                                          &last_seg,
					                                          &last_seglen,
					                                          fsmode,
					                                          &max_remaining_links);
				}
				TRY {
					sync_read(result_containing_path);
					result_containing_directory = (REF struct directory_node *)incref(result_containing_path->p_inode);
					sync_endread(result_containing_path);
					TRY {
						bool was_newly_created;
						/* Create/open an existing INode within the associated directory. */
						result_inode = directory_creatfile(result_containing_directory,
						                                   last_seg,
						                                   last_seglen,
						                                   oflags & (O_CREAT | /*O_EXCL|*/ O_DOSPATH),
						                                   fs_getuid(f),
						                                   fs_getgid(f),
						                                   mode,
						                                   &result_containing_dirent,
						                                   &was_newly_created);
						TRY {
check_result_inode_for_symlink:
							if (INODE_ISLNK(result_inode) && !(oflags & (O_NOFOLLOW | O_SYMLINK))) {
								/* No new file was created, and the accessed file turned out to be a symbolic
								 * link. - In this case, we must continue following that file's link for at
								 * most `max_remaining_links' additional links and open/create the file at its
								 * target location. */
								struct symlink_node *sl_node;
								sl_node = (struct symlink_node *)result_inode;

								if (symlink_node_load(sl_node)) {
									REF struct inode *new_result_inode;
									REF struct path *new_result_containing_path;
									REF struct directory_node *new_result_containing_directory;
									REF struct directory_entry *new_result_containing_dirent;
									/* Traverse the symlink text. */
									new_result_containing_path = path_traverse_ex(f,
									                                              result_containing_path,
									                                              root,
									                                              sl_node->sl_text,
									                                              &last_seg,
									                                              &last_seglen,
									                                              fsmode,
									                                              &max_remaining_links);
									decref(result_containing_path);
									result_containing_path = new_result_containing_path;

									sync_read(result_containing_path);
									new_result_containing_directory = (REF struct directory_node *)
									incref(result_containing_path->p_inode);
									sync_endread(result_containing_path);
									decref(result_containing_directory);
									result_containing_directory = new_result_containing_directory;

									/* Repeat the create() function with the symlink's dereferenced text. */
									new_result_inode = directory_creatfile(result_containing_directory,
									                                       last_seg,
									                                       last_seglen,
									                                       oflags & (O_CREAT | /*O_EXCL|*/ O_DOSPATH),
									                                       fs_getuid(f),
									                                       fs_getgid(f),
									                                       mode,
									                                       &new_result_containing_dirent,
									                                       &was_newly_created);
									decref(result_containing_dirent);
									result_containing_dirent = new_result_containing_dirent;
									decref(result_inode);
									result_inode = new_result_inode;
								} else {
									/* Use the dynamic interface! */
									openat_create_follow_symlink_dynamic(f,
									                                     root,
									                                     fsmode,
									                                     &max_remaining_links,
									                                     oflags,
									                                     mode,
									                                     sl_node,
									                                     &result_containing_path,
									                                     &result_containing_directory,
									                                     &result_containing_dirent,
									                                     &result_inode,
									                                     &was_newly_created);
								}
								goto check_result_inode_for_symlink;
							}
							if (!was_newly_created) {
								/* If the O_EXCL flag was given, make sure that the file was newly created.
								 * Otherwise, throw an exception.
								 * NOTE: Even though `directory_creatfile()' has builtin support for this type
								 *       of check when passed the O_EXCL flag, we don't use that functionality,
								 *       as it wouldn't allow for the special handling of SMYLINK+!O_NOFOLLOW
								 *       which we do above (which allows open() to create/open files pointed to
								 *       by symbolic links directly) */
								if (oflags & O_EXCL)
									THROW(E_FSERROR_FILE_ALREADY_EXISTS);
								/* Clear the file if O_TRUNC was given. */
								if ((oflags & O_TRUNC) &&
								    (oflags & O_ACCMODE) != O_RDONLY &&
								    INODE_ISREG(result_inode))
									inode_truncate(result_inode, 0);
							}
						} EXCEPT {
							decref(result_containing_dirent);
							decref(result_inode);
							RETHROW();
						}
					} EXCEPT {
						decref(result_containing_directory);
						RETHROW();
					}
				} EXCEPT {
					decref(result_containing_path);
					RETHROW();
				}
			} /* FINALLY {
				decref(root);
			}*/
		}
		TRY {
			if (INODE_ISLNK(result_inode)) {
				/* The resulting INode is a symbolic link.
				 * -> This is where KOS's `O_SYMLINK' extension comes into play:
				 *   - When `O_SYMLINK' is given, then the symbolic link is opened
				 *     as a regular file.
				 *   - When `O_SYMLINK' isn't given, throw an `E_FSERROR_IS_A_SYMBOLIC_LINK'
				 *     exception with `E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN' context. */
				if (!(oflags & O_SYMLINK)) {
					THROW(E_FSERROR_IS_A_SYMBOLIC_LINK,
					      E_FILESYSTEM_IS_A_SYMBOLIC_LINK_OPEN);
				}
			} else {
				if ((oflags & (O_CREAT | O_SYMLINK | O_EXCL)) == (O_SYMLINK | O_EXCL))
					THROW(E_FSERROR_NOT_A_SYMBOLIC_LINK,
					      E_FILESYSTEM_NOT_A_SYMBOLIC_LINK_OPEN);
			}

			/* Implement support for the `O_DIRECTORY' flag by throwing
			 * an error if the accessed file isn't a directory. */
			if (!INODE_ISDIR(result_inode) && (oflags & O_DIRECTORY))
				THROW(E_FSERROR_NOT_A_DIRECTORY, E_FILESYSTEM_NOT_A_DIRECTORY_OPEN);

			/* Create a file handle from all of the gathered object pointers. */
			switch (result_inode->i_filemode & S_IFMT) {

			case S_IFBLK: {
				/* Open the associated block-device. */
				dev_t devno;
				inode_loadattr(result_inode);
				COMPILER_READ_BARRIER();
				devno = result_inode->i_filerdev;
				COMPILER_READ_BARRIER();
				result_handle.h_data = block_device_lookup(devno);
				if (!result_handle.h_data)
					THROW(E_NO_DEVICE, E_NO_DEVICE_KIND_BLOCK_DEVICE, devno);
				result_handle.h_type = HANDLE_TYPE_BLOCKDEVICE;
				decref(result_inode);
				decref(result_containing_path);
				decref(result_containing_directory);
				decref(result_containing_dirent);
			}	break;

			case S_IFCHR: {
				/* Open the associated character-device. */
				dev_t devno;
				REF struct character_device *cdev;
				inode_loadattr(result_inode);
				COMPILER_READ_BARRIER();
				devno = result_inode->i_filerdev;
				COMPILER_READ_BARRIER();
				cdev = character_device_lookup(devno);
				if (!cdev)
					THROW(E_NO_DEVICE, E_NO_DEVICE_KIND_CHARACTER_DEVICE, devno);
				/* Assign a controlling terminal to the calling process. */
				if (!(oflags & O_NOCTTY) && character_device_isattybase(cdev) &&
				    ((struct ttybase_device *)cdev)->t_cproc.m_pointer == NULL)
					ttybase_device_setctty((struct ttybase_device *)cdev);
				result_handle.h_data = cdev;
				result_handle.h_type = HANDLE_TYPE_CHARACTERDEVICE;
				decref(result_inode);
				decref(result_containing_path);
				decref(result_containing_directory);
				decref(result_containing_dirent);
			}	break;

			//TODO:Filesystem pipes:case S_IFIFO:
			//TODO:Filesystem pipes: These will require a new inode-subtype `struct fifo_node'
			//                      (similar to `directory_node' or `symlink_node')

			case S_IFDIR:
				if (!result_inode->i_type->it_directory.d_readdir) {
					REF struct oneshot_directory_file *result_file;
					/* Need to return a one-shot-directory-file object. */
					result_file = (REF struct oneshot_directory_file *)kmalloc(sizeof(REF struct oneshot_directory_file),
					                                                           GFP_PREFLT);
					result_file->d_refcnt = 1;
					result_file->d_node   = (REF struct directory_node *)result_inode; /* Inherit reference */
					result_file->d_path   = result_containing_path;                    /* Inherit reference */
					result_file->d_dir    = result_containing_directory;               /* Inherit reference */
					result_file->d_dirent = result_containing_dirent;                  /* Inherit reference */
					result_file->d_offset = 0;
					atomic_rwlock_init(&result_file->d_curlck);
					result_file->d_curidx = 0;
					result_file->d_curent = NULL;
					result_file->d_curbuf = NULL;
					result_file->d_buf    = NULL;
					result_handle.h_type  = HANDLE_TYPE_ONESHOT_DIRECTORY_FILE;
					result_handle.h_data  = result_file;
					break;
				}
				ATTR_FALLTHROUGH
			default: {
				REF struct file *result_file;
				/* Simply need to return a regular file object for the given INode. */
				result_file           = (REF struct file *)kmalloc(sizeof(REF struct file), GFP_PREFLT);
				result_file->f_refcnt = 1;
				result_file->f_node   = result_inode;                /* Inherit reference */
				result_file->f_path   = result_containing_path;      /* Inherit reference */
				result_file->f_dir    = result_containing_directory; /* Inherit reference */
				result_file->f_dirent = result_containing_dirent;    /* Inherit reference */
				result_file->f_offset = 0;
				atomic_rwlock_init(&result_file->f_curlck);
				result_file->f_curidx = 0;
				result_file->f_curent = NULL;
				result_handle.h_type  = HANDLE_TYPE_FILE;
				result_handle.h_data  = result_file;
			}	break;

			}
		} EXCEPT {
			decref(result_inode);
			decref(result_containing_path);
			decref(result_containing_directory);
			decref(result_containing_dirent);
			RETHROW();
		}
	}

	{
		/* Set the I/O mode, and install the resulting object handle. */
		STATIC_ASSERT(IO_FROM_OPENFLAG(O_CLOFORK) == IO_CLOFORK);
		STATIC_ASSERT(IO_FROM_OPENFLAG(O_CLOEXEC) == IO_CLOEXEC);
		STATIC_ASSERT(IO_FROM_OPENFLAG(O_CLOFORK | O_CLOEXEC) == (IO_CLOFORK | IO_CLOEXEC));
		result_handle.h_mode = IO_FROM_OPENFLAG(oflags);
	}
	TRY {
		result = handle_install(THIS_HANDLE_MANAGER, result_handle);
	} EXCEPT {
		decref(result_handle);
		RETHROW();
	}
	decref(result_handle);
	return (fd_t)result;
}




STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_refcnt) == offsetof(struct file, f_refcnt));
STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_node) == offsetof(struct file, f_node));
STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_path) == offsetof(struct file, f_path));
STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_dir) == offsetof(struct file, f_dir));
STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_dirent) == offsetof(struct file, f_dirent));
STATIC_ASSERT(offsetof(struct oneshot_directory_file, d_offset) == offsetof(struct file, f_offset));


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

		case HANDLE_TYPE_FILE:
		case HANDLE_TYPE_ONESHOT_DIRECTORY_FILE: {
			struct file *fp;
			fp     = (struct file *)hnd.h_data;
			result = path_sprintentex(buf,
			                          buflen,
			                          fp->f_path,
			                          fp->f_dirent,
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
			sync_read(&((struct fs *)hnd.h_data)->f_pathlock);
			pwd = incref(((struct fs *)hnd.h_data)->f_cwd);
			sync_endread(&((struct fs *)hnd.h_data)->f_pathlock);
			{
				FINALLY_DECREF_UNLIKELY(pwd);
				result = path_sprintex(buf,
				                       buflen,
				                       pwd,
				                       print_mode,
				                       root);
			}
		}	break;

		default:
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
			                          containing_dentry,
			                          print_mode,
			                          root);
		}
	}
	/* Throw a buffer error if the caller doesn't want the required size */
	if (result > buflen && !(flags & AT_READLINK_REQSIZE))
		THROW(E_BUFFER_TOO_SMALL, result, buflen);
	return (ssize_t)result;
}






DEFINE_SYSCALL2(errno_t, kstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct stat *, statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, statbuf);
	}
	return -EOK;
}
DEFINE_SYSCALL2(errno_t, klstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct stat *, statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
	node = path_traversefull(f,
	                         filename,
	                         false,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, statbuf);
	}
	return -EOK;
}
DEFINE_SYSCALL2(errno_t, kfstat, fd_t, fd,
                USER UNCHECKED struct stat *, statbuf) {
	struct handle hnd;
	validate_writable(statbuf, sizeof(*statbuf));
	hnd = handle_lookup((unsigned int)fd);
	TRY {
		handle_stat(hnd, statbuf);
	} EXCEPT {
		decref(hnd);
		RETHROW();
	}
	decref(hnd);
	return -EOK;
}

DEFINE_SYSCALL4(errno_t, kfstatat, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct stat *, statbuf,
                atflag_t, flags) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
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
	return -EOK;
}



/* Compatibility with the linux kernel. */

#if defined(__NR_linux_oldstat) || defined(__NR_linux_oldlstat) || defined(__NR_linux_oldfstat)
PRIVATE void KCALL
convert_kos2linold(USER CHECKED struct linux_oldstat *__restrict dst,
                   KERNEL struct stat const *__restrict src)
		THROWS(E_SEGFAULT) {
	dst->st_dev   = (__uint16_t)src->st_dev;
	dst->st_ino   = (__uint16_t)src->st_ino32;
	dst->st_mode  = (__uint16_t)src->st_mode;
	dst->st_nlink = (__uint16_t)src->st_nlink;
	dst->st_uid   = (__uint16_t)src->st_uid;
	dst->st_gid   = (__uint16_t)src->st_gid;
	dst->st_rdev  = (__uint16_t)src->st_rdev;
	dst->st_size  = (__uint32_t)src->st_size32;
	dst->st_atime = (__uint32_t)src->st_atime32;
	dst->st_mtime = (__uint32_t)src->st_mtime32;
	dst->st_ctime = (__uint32_t)src->st_ctime32;
}
#endif /* __NR_linux_oldstat || __NR_linux_oldlstat || __NR_linux_oldfstat */

#ifdef __NR_linux_oldstat
DEFINE_SYSCALL2(errno_t, linux_oldstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	struct stat kbuf;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, &kbuf);
	}
	convert_kos2linold(statbuf, &kbuf);
	return -EOK;
}
#endif /* __NR_linux_oldstat */

#ifdef __NR_linux_oldlstat
DEFINE_SYSCALL2(errno_t, linux_oldlstat,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	struct stat kbuf;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
	node = path_traversefull(f,
	                         filename,
	                         false,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, &kbuf);
	}
	convert_kos2linold(statbuf, &kbuf);
	return -EOK;
}
#endif /* __NR_linux_oldlstat */

#ifdef __NR_linux_oldfstat
DEFINE_SYSCALL2(errno_t, linux_oldfstat, fd_t, fd,
                USER UNCHECKED struct linux_oldstat *, statbuf) {
	struct handle hnd;
	struct stat kbuf;
	validate_writable(statbuf, sizeof(*statbuf));
	hnd = handle_lookup((unsigned int)fd);
	TRY {
		handle_stat(hnd, &kbuf);
	} EXCEPT {
		decref(hnd);
		RETHROW();
	}
	decref(hnd);
	convert_kos2linold(statbuf, &kbuf);
	return -EOK;
}
#endif /* __NR_linux_oldfstat */


#if defined(__NR_linux_stat32) || defined(__NR_linux_lstat32) || \
    defined(__NR_linux_fstatat32) || defined(__NR_linux_fstat32)
PRIVATE void KCALL
convert_kos2lin32(USER CHECKED struct linux_stat32 *__restrict dst,
                  KERNEL struct stat const *__restrict src)
		THROWS(E_SEGFAULT) {
	dst->st_dev        = (__uint32_t)src->st_dev;
	dst->st_ino        = (__uint32_t)src->st_ino32;
	dst->st_mode       = (__uint16_t)src->st_mode;
	dst->st_nlink      = (__uint16_t)src->st_nlink;
	dst->st_uid        = (__uint16_t)src->st_uid;
	dst->st_gid        = (__uint16_t)src->st_gid;
	dst->st_rdev       = (__uint32_t)src->st_rdev;
	dst->st_size       = (__uint32_t)src->st_size;
	dst->st_blksize    = (__uint32_t)src->st_blksize;
	dst->st_blocks     = (__uint32_t)src->st_blocks32;
	dst->st_atime      = (__uint32_t)src->st_atime32;
	dst->st_atime_nsec = (__uint32_t)src->st_atimensec;
	dst->st_mtime      = (__uint32_t)src->st_mtime32;
	dst->st_mtime_nsec = (__uint32_t)src->st_mtimensec;
	dst->st_ctime      = (__uint32_t)src->st_ctime32;
	dst->st_ctime_nsec = (__uint32_t)src->st_ctimensec;
}
#endif /* __NR_linux_stat32 || __NR_linux_lstat32 || __NR_linux_fstatat32 || __NR_linux_fstat32 */

#ifdef __NR_linux_stat32
DEFINE_SYSCALL2(errno_t, linux_stat32,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat32 *, statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	struct stat kbuf;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, &kbuf);
	}
	convert_kos2lin32(statbuf, &kbuf);
	return -EOK;
}
#endif /* __NR_linux_stat32 */

#ifdef __NR_linux_lstat32
DEFINE_SYSCALL2(errno_t, linux_lstat32,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat32 *, statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	struct stat kbuf;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
	node = path_traversefull(f,
	                         filename,
	                         false,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, &kbuf);
	}
	convert_kos2lin32(statbuf, &kbuf);
	return -EOK;
}
#endif /* __NR_linux_lstat32 */

#ifdef __NR_linux_fstatat32
DEFINE_SYSCALL4(errno_t, linux_fstatat32, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat32 *, statbuf,
                atflag_t, flags) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	struct stat kbuf;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
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
		inode_stat(node, &kbuf);
	}
	convert_kos2lin32(statbuf, &kbuf);
	return -EOK;
}
#endif

#ifdef __NR_linux_fstat32
DEFINE_SYSCALL2(errno_t, linux_fstat32, fd_t, fd,
                USER UNCHECKED struct linux_stat32 *, statbuf) {
	struct handle hnd;
	struct stat kbuf;
	validate_writable(statbuf, sizeof(*statbuf));
	hnd = handle_lookup((unsigned int)fd);
	TRY {
		handle_stat(hnd, &kbuf);
	} EXCEPT {
		decref(hnd);
		RETHROW();
	}
	decref(hnd);
	convert_kos2lin32(statbuf, &kbuf);
	return -EOK;
}
#endif /* __NR_linux_fstat32 */


PRIVATE void KCALL
convert_kos2lin64(USER CHECKED struct linux_stat64 *__restrict dst,
                  KERNEL struct stat const *__restrict src)
		THROWS(E_SEGFAULT) {
	dst->st_dev        = (__uint64_t)src->st_dev;
	dst->__st_ino      = (__uint32_t)src->st_ino32;
	dst->st_mode       = (__uint32_t)src->st_mode;
	dst->st_nlink      = (__uint32_t)src->st_nlink;
	dst->st_uid        = (__uint32_t)src->st_uid;
	dst->st_gid        = (__uint32_t)src->st_gid;
	dst->st_rdev       = (__uint64_t)src->st_rdev;
	dst->st_size       = (__int64_t)src->st_size64;
	dst->st_blksize    = (__uint32_t)src->st_blksize;
	dst->st_blocks     = (__uint64_t)src->st_blocks64;
	dst->st_atime      = (__uint32_t)src->st_atime32;
	dst->st_atime_nsec = (__uint32_t)src->st_atimensec;
	dst->st_mtime      = (__uint32_t)src->st_mtime32;
	dst->st_mtime_nsec = (__uint32_t)src->st_mtimensec;
	dst->st_ctime      = (__uint32_t)src->st_ctime32;
	dst->st_ctime_nsec = (__uint32_t)src->st_ctimensec;
	dst->st_ino        = (__uint64_t)src->st_ino64;
}


DEFINE_SYSCALL2(errno_t, linux_stat64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat64 *, statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	struct stat kbuf;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
	node = path_traversefull(f,
	                         filename,
	                         true,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, &kbuf);
	}
	convert_kos2lin64(statbuf, &kbuf);
	return -EOK;
}

DEFINE_SYSCALL2(errno_t, linux_lstat64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat64 *, statbuf) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	struct stat kbuf;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
	node = path_traversefull(f,
	                         filename,
	                         false,
	                         ATOMIC_READ(f->f_atflag),
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	{
		FINALLY_DECREF_UNLIKELY(node);
		inode_stat(node, &kbuf);
	}
	convert_kos2lin64(statbuf, &kbuf);
	return -EOK;
}

DEFINE_SYSCALL2(errno_t, linux_fstat64, fd_t, fd,
                USER UNCHECKED struct linux_stat64 *, statbuf) {
	__NR_linux_fstat64;
	struct handle hnd;
	struct stat kbuf;
	validate_writable(statbuf, sizeof(*statbuf));
	hnd = handle_lookup((unsigned int)fd);
	TRY {
		handle_stat(hnd, &kbuf);
	} EXCEPT {
		decref(hnd);
		RETHROW();
	}
	decref(hnd);
	convert_kos2lin64(statbuf, &kbuf);
	return -EOK;
}

#ifdef __NR_linux_fstatat64
DEFINE_SYSCALL4(errno_t, linux_fstatat64, fd_t, dirfd,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct linux_stat64 *, statbuf,
                atflag_t, flags) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	struct stat kbuf;
	validate_readable(filename, 1);
	validate_writable(statbuf, sizeof(*statbuf));
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
		inode_stat(node, &kbuf);
	}
	convert_kos2lin64(statbuf, &kbuf);
	return -EOK;
}
#endif /* __NR_linux_fstatat64 */


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
	                                                         ATOMIC_READ(f->f_atflag),
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
	                                                            ATOMIC_READ(f->f_atflag),
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


typedef void(KCALL *kernel_pervm_onexec_t)(void);
INTDEF kernel_pervm_onexec_t __kernel_pervm_onexec_start[];
INTDEF kernel_pervm_onexec_t __kernel_pervm_onexec_end[];
LOCAL void KCALL run_pertask_onexec(void) {
	kernel_pervm_onexec_t *iter;
	for (iter = __kernel_pervm_onexec_start;
	     iter < __kernel_pervm_onexec_end; ++iter)
		(**iter)();
	/* Invoke dynamic callbacks. */
	vm_onexec_callbacks();
}




PRIVATE struct icpustate *KCALL
kernel_do_execveat(struct icpustate *__restrict state,
                   REF struct regular_node *__restrict exec_node,
                   REF struct path *__restrict containing_path,
                   REF struct directory_entry *__restrict containing_dentry,
                   USER UNCHECKED char const *USER CHECKED const *argv,
                   USER UNCHECKED char const *USER CHECKED const *envp) {
	if (kernel_debugtrap_enabled()) {
		/* Trigger an EXEC debug trap. */
		char *buf, *dst;
		size_t reglen;
		reglen = (size_t)path_printent(containing_path, containing_dentry, &format_length, NULL);
		/* Allocate the register buffer beforehand, so this
		 * allocation failing can still be handled by user-space.
		 * NOTE: We always allocate this buffer on the heap, since file paths can get quite long,
		 *       an being as far to the bottom of the kernel stack as we are, it could be a bit
		 *       risky to allocate a huge stack-based structure when we still have to call `vm_exec()',
		 *       even when using `malloca()' (but maybe I'm just overlay cautios...) */
		buf = (char *)kmalloc((reglen + 1) * sizeof(char), GFP_NORMAL);
		TRY {
			dst = buf;
			path_printent(containing_path, containing_dentry, &format_sprintf_printer, &dst);
			*dst = '\0';
			assert(dst == buf + reglen);
			*dst = 0;
			/* Actually map the specified file into memory! */
			state = vm_exec(THIS_VM,
			                state,
			                containing_path,
			                containing_dentry,
			                exec_node,
			                0,
			                NULL,
			                argv,
			                envp);
			/* Upon success, run onexec callbacks (which will clear all CLOEXEC handles). */
			run_pertask_onexec();
			{
				struct debugtrap_reason r;
				r.dtr_signo  = SIGTRAP;
				r.dtr_reason = DEBUGTRAP_REASON_EXEC;
				r.dtr_strarg = buf;
				state = kernel_debugtrap_r(state, &r);
			}
		} EXCEPT {
			kfree(buf);
			RETHROW();
		}
		kfree(buf);
	} else {
		/* Actually map the specified file into memory! */
		state = vm_exec(THIS_VM,
		                state,
		                containing_path,
		                containing_dentry,
		                exec_node,
		                0,
		                NULL,
		                argv,
		                envp);
		/* Upon success, run onexec callbacks (which will clear all CLOEXEC handles). */
		run_pertask_onexec();
	}
	return state;
}


struct kernel_exec_rpc_data {
	REF struct regular_node                       *er_node;   /* [1..1] The INode that should be executed. */
	REF struct path                               *er_path;   /* [1..1] The containing path for `er_node' */
	REF struct directory_entry                    *er_dentry; /* [1..1] The directory entry for `er_node' */
	USER UNCHECKED char const *USER CHECKED const *er_argv;   /* [?..?][1..1] Vector user-supplied arguments to-be passed to the targeted executable. */
	USER UNCHECKED char const *USER CHECKED const *er_envp;   /* [?..?][1..1] Vector user-supplied environment variables to-be passed to the targeted executable. */
	struct exception_data                          er_except; /* Information about the exception that caused exec() to fail. */
	struct sig                                     er_error;  /* Signal broadcast upon error. */
};


PRIVATE struct icpustate *FCALL
kernel_exec_rpc_func(void *arg, struct icpustate *__restrict state,
                     unsigned int reason,
                     struct rpc_syscall_info const *UNUSED(sc_info)) {
	struct kernel_exec_rpc_data *data;
	struct exception_info old_exception_info;
	assert(reason == TASK_RPC_REASON_ASYNCUSER ||
	       reason == TASK_RPC_REASON_SYSCALL ||
	       reason == TASK_RPC_REASON_SHUTDOWN);
	data = (struct kernel_exec_rpc_data *)arg;
	memcpy(&old_exception_info, &THIS_EXCEPTION_INFO, sizeof(old_exception_info));
	TRY {
		FINALLY_DECREF_UNLIKELY(data->er_node);
		FINALLY_DECREF_UNLIKELY(data->er_path);
		FINALLY_DECREF_UNLIKELY(data->er_dentry);
		/* Check for race condition: Our RPC only got executed because the
		 * main thread is currently being terminated. - In this case it wouldn't
		 * make any sense to try and load a new binary into the VM, so just indicate
		 * to the receiving thread that we've been terminated by propagating an
		 * E_EXIT_THREAD exception to them. */
		if unlikely(reason == TASK_RPC_REASON_SHUTDOWN) {
			assert(THIS_TASKPID);
			data->er_except.e_code        = ERROR_CODEOF(E_EXIT_THREAD);
			data->er_except.e_pointers[0] = (uintptr_t)(unsigned int)THIS_TASKPID->tp_status.w_status;
			memset(&data->er_except.e_pointers[1], 0,
			       (EXCEPTION_DATA_POINTERS - 1) * sizeof(void *));
			goto done_signal_exception;
		}
		/* Actually map the specified file into memory!
		 * NOTE: For this purpose, we simply re-direct the given user-space
		 *       CPU state to which the RPC would have normally returned! */
		state = kernel_do_execveat(state,
		                           data->er_node,
		                           data->er_path,
		                           data->er_dentry,
		                           data->er_argv,
		                           data->er_envp);
	} EXCEPT {
		memcpy(&data->er_except,
		       &THIS_EXCEPTION_INFO,
		       sizeof(data->er_except));
		goto restore_exception;
	}
	/* Success! -> In this case _we_ must inherit the given RPC data packet,
	 *             since the sending thread will terminate (or has already
	 *             terminated) by having its `task_waitfor()' function return
	 *             by throwing an E_EXIT_THREAD exception that got caused by
	 *            `vmb_apply()' terminating all threads except for the calling
	 *             one (us) within the current process. */
	kfree(data);
	return state;
restore_exception:
	memcpy(&THIS_EXCEPTION_INFO,
	       &old_exception_info,
	       sizeof(old_exception_info));
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
kernel_execveat(struct icpustate *__restrict state,
                fd_t dirfd,
                USER UNCHECKED char const *pathname,
                USER UNCHECKED char const *USER UNCHECKED const *argv,
                USER UNCHECKED char const *USER UNCHECKED const *envp,
                atflag_t flags) {
	struct fs *f = THIS_FS;
	REF struct inode *node;
	REF struct path *containing_path;
	REF struct directory_entry *containing_dentry;
	struct task *caller = THIS_TASK;
	validate_readable_opt(argv, sizeof(*argv));
	validate_readable_opt(envp, sizeof(*envp));
	VALIDATE_FLAGSET(flags,
	                 AT_EMPTY_PATH | AT_SYMLINK_NOFOLLOW | AT_DOSPATH,
	                 E_INVALID_ARGUMENT_CONTEXT_EXECVEAT_FLAGS);
	node = path_traversefull_at(f,
	                            (unsigned int)dirfd,
	                            pathname,
	                            !(flags & AT_SYMLINK_NOFOLLOW),
	                            fs_getmode_for(f, flags),
	                            NULL,
	                            &containing_path,
	                            NULL,
	                            &containing_dentry);
	{
		FINALLY_DECREF_UNLIKELY(containing_path);
		FINALLY_DECREF_UNLIKELY(containing_dentry);
		FINALLY_DECREF_UNLIKELY(node);
		/* Assert that the specified node is a regular file. */
		vm_exec_assert_regular(node);
		{
			inode_loadattr(node);
			/* TODO: Check for execute permissions? */
		}
		if (caller == task_getprocess_of(caller)) {
			state = kernel_do_execveat(state,
			                           (struct regular_node *)node,
			                           containing_path,
			                           containing_dentry,
			                           argv,
			                           envp);
		} else {
			struct kernel_exec_rpc_data *data;
			struct task *proc = task_getprocess_of(caller);
			/* Since the new process is meant to override our's as a whole, the actual
			 * exec() must be performed by the main thread of our own process. - For this
			 * purpose, we must use an RPC to load the new binary from the main thread. */
			data = (struct kernel_exec_rpc_data *)kmalloc(sizeof(struct kernel_exec_rpc_data),
			                                              GFP_LOCKED);
			/* Initialize RPC information. */
			data->er_node   = (REF struct regular_node *)incref(node);
			data->er_path   = incref(containing_path);
			data->er_dentry = incref(containing_dentry);
			data->er_argv   = argv;
			data->er_envp   = envp;
			sig_init(&data->er_error);
			TRY {
				task_connect(&data->er_error);
				if (!task_schedule_synchronous_rpc(proc,
				                                   &kernel_exec_rpc_func,
				                                   data,
				                                   TASK_RPC_FHIGHPRIO,
				                                   NULL,
				                                   GFP_NORMAL)) {
					/* The main thread was already terminated. - Propagate its
					 * termination signal manually (since we may not have received
					 * it before in case our thread had been detached). */
					union wait status;
					status = FORTASK(caller, this_taskpid)->tp_status;
					THROW(E_EXIT_THREAD, status.w_status);
				}
			} EXCEPT {
				assert(data->er_dentry == containing_dentry);
				assert(data->er_path == containing_path);
				assert(data->er_node == node);
				/* NoKill, because we still got 1 more reference to each, which will be
				 * dropped after `RETHROW()' by the `FINALLY_DECREF_UNLIKELY()' above. */
				decref_nokill(containing_dentry);
				decref_nokill(containing_path);
				decref_nokill(node);
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
			task_waitfor(NULL);
#else
			{
				struct sig *recv;
				recv = task_waitfor(NULL);
				assert(recv == &data->er_error);
			}
#endif
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
	}
	return state;
}


PRIVATE struct icpustate *FCALL
syscall_execvat_rpc(void *UNUSED(arg),
                    struct icpustate *__restrict state,
                    unsigned int reason,
                    struct rpc_syscall_info const *sc_info) {
	if (reason == TASK_RPC_REASON_SYSCALL) {
		/* Actually service the exec() system call. */
		state = kernel_execveat(state,
		                        (fd_t)sc_info->rsi_args[0],
		                        (USER UNCHECKED char const *)sc_info->rsi_args[1],
		                        (USER UNCHECKED char const *USER UNCHECKED const *)sc_info->rsi_args[2],
		                        (USER UNCHECKED char const *USER UNCHECKED const *)sc_info->rsi_args[3],
		                        (atflag_t)sc_info->rsi_args[4]);
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
	                       &syscall_execvat_rpc,
	                       NULL,
	                       TASK_RPC_FHIGHPRIO |
	                       TASK_USER_RPC_FINTR,
	                       NULL,
	                       GFP_NORMAL);
	/* Shouldn't get here... */
	return -EOK;
}

DEFINE_SYSCALL3(errno_t, execve,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED char const *USER UNCHECKED const *, argv,
                USER UNCHECKED char const *USER UNCHECKED const *, envp) {
	return sys_execveat(AT_FDCWD, filename, argv, envp, 0);
}

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

LOCAL void KCALL
statfs64_to_statfs32(USER CHECKED struct __statfs32 *dst,
                     struct statfs const *__restrict src) {
	dst->f_type    = src->f_type;
	dst->f_bsize   = src->f_bsize;
	dst->f_blocks  = (__fsblkcnt32_t)src->f_blocks;
	dst->f_bfree   = (__fsblkcnt32_t)src->f_bfree;
	dst->f_bavail  = (__fsblkcnt32_t)src->f_bavail;
	dst->f_files   = (__fsfilcnt32_t)src->f_files;
	dst->f_ffree   = (__fsfilcnt32_t)src->f_ffree;
	dst->f_fsid    = src->f_fsid;
	dst->f_namelen = src->f_namelen;
	dst->f_frsize  = src->f_frsize;
	dst->f_flags   = src->f_flags;
	memcpy(dst->f_spare, src->f_spare, sizeof(src->f_spare));
}

DEFINE_SYSCALL2(errno_t, fstatfs, fd_t, fd,
                USER UNCHECKED struct __statfs32 *, result) {
	REF struct superblock *super;
	struct statfs data;
	validate_writable(result, sizeof(*result));
	super = handle_get_superblock_relaxed((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_statfs(super, &data);
	}
	COMPILER_WRITE_BARRIER();
	statfs64_to_statfs32(result, &data);
	return -EOK;
}

#ifdef __NR_fstatfs64
DEFINE_SYSCALL2(errno_t, fstatfs64, fd_t, fd,
                USER UNCHECKED struct statfs64 *, result) {
	REF struct superblock *super;
	validate_writable(result, sizeof(*result));
	super = handle_get_superblock_relaxed((unsigned int)fd);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_statfs(super, (struct statfs *)result);
	}
	return -EOK;
}
#endif /* __NR_fstatfs64 */

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
	                         f->f_atflag | FS_MODE_FIGNORE_TRAILING_SLASHES,
	                         NULL,
	                         NULL,
	                         NULL,
	                         NULL);
	result = (REF struct superblock *)incref(node->i_super);
	decref_unlikely(node);
	return result;
}


DEFINE_SYSCALL2(errno_t, statfs,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct __statfs32 *, result) {
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
	statfs64_to_statfs32(result, &data);
	return -EOK;
}

#ifdef __NR_statfs64
DEFINE_SYSCALL2(errno_t, statfs64,
                USER UNCHECKED char const *, filename,
                USER UNCHECKED struct statfs64 *, result) {
	REF struct superblock *super;
	validate_readable(filename, 1);
	validate_writable(result, sizeof(*result));
	super = get_superblock_from_path(filename);
	{
		FINALLY_DECREF_UNLIKELY(super);
		superblock_statfs(super, (struct statfs *)result);
	}
	return -EOK;
}
#endif /* __NR_statfs64 */






/* TODO: Missing system calls: */
//#define SYS_faccessat       __NR_faccessat       /* errno_t faccessat(fd_t dirfd, char const *pathname, syscall_ulong_t mode, atflag_t flags) */
//#define __NR_utimensat                  320        /* errno_t utimensat(fd_t dirfd, char const *filename, [2-3]struct __timespec32 const *times, atflag_t flags) */
//#define __NR_utimensat64                0x80000140 /* errno_t utimensat64(fd_t dirfd, char const *filename, [2-3]struct timespec64 const *times, atflag_t flags) */
//#define __NR_fallocate                  324        /* errno_t fallocate(fd_t fd, syscall_ulong_t mode, uint32_t offset, uint32_t length) */
//#define __NR_fallocate64                0x80000144 /* errno_t fallocate64(fd_t fd, syscall_ulong_t mode, uint64_t offset, uint64_t length) */


DECL_END

#endif /* !GUARD_KERNEL_CORE_FS_SYSCALLS_C */
