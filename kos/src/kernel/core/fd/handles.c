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
#ifndef GUARD_KERNEL_SRC_FD_HANDLES_C
#define GUARD_KERNEL_SRC_FD_HANDLES_C 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <dev/tty.h>
#include <kernel/except.h>
#include <kernel/execabi.h>
#include <kernel/fs/dirent.h>
#include <kernel/fs/fs.h>
#include <kernel/fs/node.h>
#include <kernel/fs/path.h>
#include <kernel/fs/super.h>
#include <kernel/fs/vfs.h>
#include <kernel/handle.h>
#include <kernel/handman.h>
#include <kernel/mman/mfile.h>
#include <kernel/mman/ramfile.h>
#include <kernel/user.h>
#include <sched/cred.h>
#include <sched/group.h>
#include <sched/pid.h>
#include <sched/task.h>

#include <hybrid/atomic.h>

#include <compat/config.h>
#include <kos/except.h>
#include <kos/except/reason/inval.h>
#include <kos/ioctl/_openfd.h>

#include <fcntl.h>
#include <stddef.h>
#include <string.h>

#ifdef __ARCH_HAVE_COMPAT
#include <kernel/compat.h>
#endif /* __ARCH_HAVE_COMPAT */

/************************************************************************/
/* HIGH-LEVEL HANDLE OPERATIONS (FOR THE CALLING THREAD)                */
/************************************************************************/

DECL_BEGIN

/* Special handling for symbolic handles. */
PRIVATE ATTR_NOINLINE NONNULL((2)) REF struct handle *FCALL
handles_close_symbolic(fd_t fd, /*out*/ REF struct handle *__restrict ohand) {
	switch (fd) {

	case (AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)): {
		REF struct path *oldpath;
		struct fs *myfs   = THIS_FS;
		struct vfs *myvfs = myfs->fs_vfs;
		require(CAP_MOUNT_DRIVES);
		vfs_driveslock_write(myvfs);
		oldpath = myvfs->vf_drives[fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)]; /* Inherit reference */
		myvfs->vf_drives[fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)] = NULL;
		if (oldpath) {
			/* Check if `oldpath' is still a drive root. */
			bool isdrive = false;
			unsigned int id;
			for (id = 0; id < lengthof(myvfs->vf_drives); ++id) {
				if (myvfs->vf_drives[id] == oldpath) {
					isdrive = true;
					break;
				}
			}
			if (!isdrive)
				ATOMIC_AND(oldpath->p_flags, ~PATH_F_ISDRIVE);
		}
		vfs_driveslock_endwrite(myvfs);
		ohand->h_mode = IO_RDONLY;
		ohand->h_type = HANDLE_TYPE_PATH;
		ohand->h_data = oldpath;
		if (ohand->h_data == NULL)
			ohand->h_type = HANDLE_TYPE_UNDEFINED;
	}	break;

	default:
		/* Unknown symbolic handle. */
		return NULL;
	}
	return ohand;
}

PRIVATE ATTR_NOINLINE NONNULL((2)) REF struct handle *FCALL
handles_lookup_symbolic(fd_t fd, /*out*/ REF struct handle *__restrict hand) {
	switch (fd) {

	case AT_FDCWD: {
		struct fs *myfs = THIS_FS;
		fs_pathlock_read(myfs);
		hand->h_data = incref(myfs->fs_cwd);
		fs_pathlock_endread(myfs);
	}
do_return_path:
		hand->h_mode = IO_RDONLY;
		hand->h_type = HANDLE_TYPE_PATH;
		return hand;

	case AT_FDROOT: {
		struct fs *myfs = THIS_FS;
		fs_pathlock_read(myfs);
		hand->h_data = incref(myfs->fs_root);
		fs_pathlock_endread(myfs);
		goto do_return_path;
	}	break;

	case (AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX)): {
		struct fs *myfs = THIS_FS;
		fs_pathlock_read(myfs);
		hand->h_data = xincref(myfs->fs_dcwd[fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN)]);
		fs_pathlock_endread(myfs);
		if (hand->h_data == NULL) {
			struct vfs *myvfs;
			myvfs = myfs->fs_vfs;
			vfs_driveslock_read(myvfs);
			hand->h_data = xincref(myvfs->vf_drives[fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN)]);
			vfs_driveslock_endread(myvfs);
			if (hand->h_data == NULL)
				return NULL;
		}
		goto do_return_path;
	}	break;

	case (AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)): {
		struct fs *myfs = THIS_FS;
		struct vfs *myvfs = myfs->fs_vfs;
		vfs_driveslock_read(myvfs);
		hand->h_data = xincref(myvfs->vf_drives[fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)]);
		vfs_driveslock_endread(myvfs);
		if (hand->h_data == NULL)
			return NULL;
		goto do_return_path;
	}	break;

	case AT_FDTHRD:
		hand->h_data = incref(task_gettaskpid());
		goto do_return_pidfd;
	case AT_FDPROC:
		hand->h_data = incref(task_getprocpid());
		goto do_return_pidfd;
	case AT_FDPARPROC:
		/* no incref(), because `task_getparentprocesspid()' already returns a reference! */
		hand->h_data = task_getparentprocesspid();
do_return_pidfd:
		hand->h_mode = IO_RDONLY;
		hand->h_type = HANDLE_TYPE_PIDFD;
		return hand;

	case AT_FDCTTY:
		hand->h_data = task_getctty();
		if unlikely(!hand->h_data)
			break; /* No CTTY */
		TRY {
			fnode_access((REF struct ttydev *)hand->h_data, R_OK | W_OK);
		} EXCEPT {
			decref_unlikely((REF struct ttydev *)hand->h_data);
			RETHROW();
		}
		hand->h_mode = IO_RDWR;
		hand->h_type = HANDLE_TYPE_MFILE;
		return hand;

	case AT_FDSYSRTLD:
		hand->h_data = &execabi_system_rtld_file.mrf_file;
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat())
			hand->h_data = &compat_execabi_system_rtld_file.mrf_file;
#endif /* __ARCH_HAVE_COMPAT */
		incref((struct mfile *)hand->h_data);
		hand->h_mode = IO_RDONLY;
		hand->h_type = HANDLE_TYPE_MFILE;
		return hand;

	default:
		/* Unknown symbolic handle. */
		break;
	}
	return NULL;
}

#ifndef __OPTIMIZE_SIZE__
PRIVATE ATTR_NOINLINE REF void *FCALL
handles_lookupobj_symbolic(fd_t fd, uintptr_half_t wanted_type) {
	switch (fd) {

	case AT_FDCWD:
	case AT_FDROOT:
	case (AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX)):
	case (AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)): {
		REF struct path *result;
		struct fs *myfs = THIS_FS;
		if (wanted_type != HANDLE_TYPE_PATH &&
		    wanted_type != HANDLE_TYPE_MFILE &&
		    wanted_type != HANDLE_TYPE_DIRENT) {
			THROW(E_INVALID_HANDLE_FILETYPE,
			      /* fd:                 */ (syscall_slong_t)fd,
			      /* needed_handle_type: */ wanted_type,
			      /* actual_handle_type: */ HANDLE_TYPE_PATH,
			      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
			      /* actual_handle_kind: */ HANDLE_TYPEKIND_GENERIC);
		}
		switch (fd) {

		case (AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)): {
			struct vfs *myvfs = myfs->fs_vfs;
			vfs_driveslock_read(myvfs);
			result = xincref(myvfs->vf_drives[fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)]);
			vfs_driveslock_endread(myvfs);
		}	break;

		case (AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX)): {
			fs_pathlock_read(myfs);
			result = xincref(myfs->fs_dcwd[fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN)]);
			fs_pathlock_endread(myfs);
			if (result == NULL) {
				struct vfs *myvfs = myfs->fs_vfs;
				vfs_driveslock_read(myvfs);
				result = xincref(myvfs->vf_drives[fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN)]);
				vfs_driveslock_endread(myvfs);
			}
		}	break;

		case AT_FDCWD:
			fs_pathlock_read(myfs);
			result = incref(myfs->fs_cwd);
			fs_pathlock_endread(myfs);
			break;

		case AT_FDROOT:
			fs_pathlock_read(myfs);
			result = incref(myfs->fs_root);
			fs_pathlock_endread(myfs);
			break;

		default: __builtin_unreachable();
		}

		/* Return the relevant element of `result' */
		switch (wanted_type) {
		case HANDLE_TYPE_PATH:
			return result;
		case HANDLE_TYPE_MFILE: {
			REF struct mfile *r;
			r = incref(result->p_dir);
			decref_unlikely(result);
			return r;
		}	break;
		case HANDLE_TYPE_DIRENT: {
			REF struct fdirent *r;
			r = incref(result->p_name);
			decref_unlikely(result);
			return r;
		}	break;
		default: __builtin_unreachable();
		}
		__builtin_unreachable();
	}	break;

	case AT_FDTHRD:
	case AT_FDPROC:
	case AT_FDPARPROC:
		if (wanted_type != HANDLE_TYPE_PIDFD) {
			THROW(E_INVALID_HANDLE_FILETYPE,
			      /* fd:                 */ (syscall_slong_t)fd,
			      /* needed_handle_type: */ wanted_type,
			      /* actual_handle_type: */ HANDLE_TYPE_PIDFD,
			      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
			      /* actual_handle_kind: */ HANDLE_TYPEKIND_GENERIC);
		}
		switch (fd) {
		case AT_FDTHRD:
			return incref(task_gettaskpid());
		case AT_FDPROC:
			return incref(task_getprocpid());
		case AT_FDPARPROC:
			/* no incref(), because `task_getparentprocesspid()' already returns a reference! */
			return task_getparentprocesspid();
		default: __builtin_unreachable();
		}
		break;

	case AT_FDCTTY: {
		REF struct ttydev *tty;
		REF void *result;
		tty = task_getctty();
		if unlikely(!tty)
			break; /* No CTTY */
		TRY {
			fnode_access((REF struct ttydev *)tty, R_OK | W_OK);
		} EXCEPT {
			decref_unlikely((REF struct ttydev *)tty);
			RETHROW();
		}
		if likely(wanted_type == HANDLE_TYPE_MFILE)
			return tty;
		TRY {
			result = mfile_utryas(tty, wanted_type);
		} EXCEPT {
			decref_unlikely(tty);
			RETHROW();
		}
		if unlikely(!result) {
			uintptr_t kind;
			kind = mfile_typekind(tty);
			decref_unlikely(tty);
			THROW(E_INVALID_HANDLE_FILETYPE,
			      /* fd:                 */ (syscall_slong_t)fd,
			      /* needed_handle_type: */ wanted_type,
			      /* actual_handle_type: */ HANDLE_TYPE_MFILE,
			      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
			      /* actual_handle_kind: */ kind);
		}
		decref_unlikely(tty);
		return result;
	}	break;

	case AT_FDSYSRTLD:
		if (wanted_type != HANDLE_TYPE_MFILE) {
			THROW(E_INVALID_HANDLE_FILETYPE,
			      /* fd:                 */ (syscall_slong_t)fd,
			      /* needed_handle_type: */ wanted_type,
			      /* actual_handle_type: */ HANDLE_TYPE_MFILE,
			      /* needed_handle_kind: */ HANDLE_TYPEKIND_GENERIC,
			      /* actual_handle_kind: */ HANDLE_TYPEKIND_GENERIC);
		}
#ifdef __ARCH_HAVE_COMPAT
		if (syscall_iscompat())
			return incref(&compat_execabi_system_rtld_file.mrf_file);
#endif /* __ARCH_HAVE_COMPAT */
		return incref(&execabi_system_rtld_file.mrf_file);

	default:
		/* Unknown symbolic handle. */
		break;
	}
	return NULL;
}
#endif /* !__OPTIMIZE_SIZE__ */


PRIVATE ATTR_NOINLINE NONNULL((2, 3)) bool FCALL
handles_install_symbolic(fd_t fd, struct handle const *__restrict nhand,
                         /*out*/ REF struct handle *__restrict ohand) {
	switch (fd) {

	case AT_FDCWD:
	case AT_FDROOT:
	case (AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX)):
	case (AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)): {
		REF struct path *newpath;
		struct fs *myfs = THIS_FS;
		if unlikely(!IO_CANREAD(nhand->h_mode)) {
			THROW(E_INVALID_HANDLE_OPERATION, -1,
			      E_INVALID_HANDLE_OPERATION_READ,
			      nhand->h_mode);
		}
		ohand->h_mode = IO_RDONLY;
		ohand->h_type = HANDLE_TYPE_PATH;
		newpath       = (REF struct path *)handle_as_noinherit(nhand, HANDLE_TYPE_PATH);
		TRY {
			/* Require EXEC(traverse) and READ permissions for FS path  hooks.
			 * For reference, this same check is also performed in `fchdir(2)' */
			fnode_access(newpath->p_dir, X_OK | R_OK);

			/* Bind the path to the specified `fd' */
			switch (fd) {

			case (AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_ROOT(AT_DOS_DRIVEMAX)): {
				REF struct path *oldpath;
				struct vfs *myvfs = myfs->fs_vfs;
				require(CAP_MOUNT_DRIVES);
				ATOMIC_OR(newpath->p_flags, PATH_F_ISDRIVE);
				vfs_driveslock_write(myvfs);
				oldpath = myvfs->vf_drives[fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)]; /* Inherit reference */
				myvfs->vf_drives[fd - AT_FDDRIVE_ROOT(AT_DOS_DRIVEMIN)] = newpath; /* Inherit reference */
				if (oldpath) {
					/* Check if `oldpath' is still a drive root. */
					bool isdrive = false;
					unsigned int id;
					for (id = 0; id < lengthof(myvfs->vf_drives); ++id) {
						if (myvfs->vf_drives[id] == oldpath) {
							isdrive = true;
							break;
						}
					}
					if (!isdrive)
						ATOMIC_AND(oldpath->p_flags, ~PATH_F_ISDRIVE);
				}
				vfs_driveslock_endwrite(myvfs);
				ohand->h_data = oldpath;
				if (ohand->h_data == NULL)
					ohand->h_type = HANDLE_TYPE_UNDEFINED;
			}	break;

			case (AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN))...(AT_FDDRIVE_CWD(AT_DOS_DRIVEMAX)): {
again_acquire_pathlock_for_drive_cwd:
				fs_pathlock_write(myfs);
				ohand->h_data = myfs->fs_dcwd[fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN)]; /* Inherit reference */
				if (!ohand->h_data) {
					/* In order to be able to bind a DRIVE-CWD path, the drive itself must be mounted. */
					struct vfs *myvfs = myfs->fs_vfs;
					if (!vfs_driveslock_tryread(myvfs)) {
						fs_pathlock_endwrite(myfs);
						vfs_driveslock_waitread(myvfs);
						goto again_acquire_pathlock_for_drive_cwd;
					}
					/* The old effective handle value was the drive root. */
					ohand->h_data = myvfs->vf_drives[fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN)];
					if (!ohand->h_data) {
						/* Unbound drive --> mustn't recognize this symbolic FD. */
						_vfs_driveslock_endread(myvfs);
						_fs_pathlock_endwrite(myfs);
						vfs_driveslock_reap(myvfs);
						fs_pathlock_reap(myfs);
						decref_unlikely(newpath);
						return false;
					}
					incref((struct path *)ohand->h_data);
					vfs_driveslock_endread(myvfs);
				}
				/* TODO: Check that `newpath' is a sub-directory of the drive root.
				 *       -> If it isn't, must throw `E_FSERROR_CROSS_DEVICE_LINK' */
				myfs->fs_dcwd[fd - AT_FDDRIVE_CWD(AT_DOS_DRIVEMIN)] = newpath; /* Inherit reference */
				fs_pathlock_endwrite(myfs);
			}	break;

			case AT_FDCWD:
				fs_pathlock_write(myfs);
				ohand->h_data = myfs->fs_cwd; /* Inherit reference */
				myfs->fs_cwd  = newpath;      /* Inherit reference */
				fs_pathlock_endwrite(myfs);
				break;

			case AT_FDROOT:
				fs_pathlock_write(myfs);
				ohand->h_data = myfs->fs_root; /* Inherit reference */
				myfs->fs_root = newpath;       /* Inherit reference */
				fs_pathlock_endwrite(myfs);
				break;

			default: __builtin_unreachable();
			}
		} EXCEPT {
			decref_unlikely(newpath);
			RETHROW();
		}
		return true;
	}	break;

	default:
		/* Unknown symbolic handle. */
		return false;
	}
	return true;
}

/* Same as `handman_close()', but also accept symbolic
 * handles, and  use `THIS_HANDMAN'  for normal  ones. */
PUBLIC ATTR_RETNONNULL NONNULL((2)) REF struct handle *FCALL
handles_close(fd_t fd, /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	REF struct handle *result;
	if (fd < 0) {
		/* Special handling for symbolic handles. */
		result = handles_close_symbolic(fd, ohand);
		if (result != NULL)
			return result;
	}
	return handman_close(THIS_HANDMAN, fd, ohand);
}

/* Same as `handman_lookup()', but also accept symbolic
 * handles,  and  use `THIS_HANDMAN'  for  normal ones. */
PUBLIC ATTR_RETNONNULL NONNULL((2)) REF struct handle *FCALL
handles_lookup(fd_t fd, /*out*/ REF struct handle *__restrict hand)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE) {
	REF struct handle *result;
	if (fd < 0) {
		/* Special handling for symbolic handles. */
		result = handles_lookup_symbolic(fd, hand);
		if (result != NULL)
			return result;
	}
	return handman_lookup(THIS_HANDMAN, fd, hand);
}


/* Same as `handles_lookup()', but require a specific handle type,
 * and return a reference to  the handle's `h_data' field,  rather
 * than the handle itself (attempts to cast miss-matching  types). */
PUBLIC ATTR_RETNONNULL WUNUSED REF void *FCALL
handles_lookupobj(fd_t fd, uintptr_half_t wanted_type)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	struct handle buf;
	REF struct handle *hand;
	REF void *result;
#ifdef __OPTIMIZE_SIZE__
	hand = handles_lookup(fd, &buf);
#else /* __OPTIMIZE_SIZE__ */
	if (fd < 0) {
		/* Special handling for symbolic handles. */
		result = handles_lookupobj_symbolic(fd, wanted_type);
		if (result != NULL)
			return result;
	}
	hand = handman_lookup(THIS_HANDMAN, fd, &buf);
#endif /* !__OPTIMIZE_SIZE__ */
	if (hand->h_type == wanted_type)
		return hand->h_data; /* Inherit reference */
	TRY {
		result = _handle_tryas(*hand, wanted_type);
	} EXCEPT {
		decref(*hand);
		if (was_thrown(E_INVALID_HANDLE_FILETYPE)) {
			if (!PERTASK_TEST(this_exception_args.e_invalid_handle.ih_fd))
				PERTASK_SET(this_exception_args.e_invalid_handle.ih_fd, (syscall_slong_t)fd);
		}
		RETHROW();
	}
	decref(*hand);
	return result;
}


/* Special wrappers for retrieving specific objects from handles. */
PUBLIC ATTR_RETNONNULL WUNUSED REF struct fnode *FCALL
handles_lookupfnode(fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	REF struct mfile *mf;
	mf = handles_lookupmfile(fd);
	if (!mfile_isnode(mf)) {
		uintptr_half_t kind = mfile_typekind(mf);
		decref_unlikely(mf);
		THROW(E_INVALID_HANDLE_FILETYPE,
		      /* fd:                 */ (syscall_slong_t)fd,
		      /* needed_handle_type: */ HANDLE_TYPE_MFILE,
		      /* actual_handle_type: */ HANDLE_TYPE_MFILE,
		      /* needed_handle_kind: */ HANDLE_TYPEKIND_MFILE_FNODE,
		      /* actual_handle_kind: */ kind);
	}
	return mfile_asnode(mf);
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct fsuper *FCALL
handles_lookupfsuper_relaxed(fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE, E_INVALID_HANDLE_FILETYPE) {
	REF struct fsuper *result;
	REF struct fnode *fn;
	fn     = handles_lookupfnode(fd);
	result = incref(fn->fn_super);
	decref_unlikely(fn);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED REF struct task *FCALL
handles_lookuptask(fd_t fd)
		THROWS(E_WOULDBLOCK, E_INVALID_HANDLE_FILE,
		       E_INVALID_HANDLE_FILETYPE, E_PROCESS_EXITED) {
	REF struct task *result;
	REF struct taskpid *pid;
	if (fd < 0) {
		switch (fd) {

#ifndef __OPTIMIZE_SIZE__
		case AT_FDTHRD:
			return incref(THIS_TASK);

		case AT_FDPROC: {
			REF struct task *proc;
			while unlikely((proc = task_getproc()) == NULL) {
				/* Sleep  without first connecting --> wait indefinitely
				 * until we receive the termination-propagation RPC from
				 * our  process leader, since  our process has obviously
				 * been killed if the leader is `NULL'. */
				task_waitfor();
			}
			return proc;
		}	break;
#endif /* !__OPTIMIZE_SIZE__ */

		case AT_FDPARPROC:
			/* NOTE: This case right here is actually required for ABI  compliance.
			 * Because  the parent process  might change, there  is always a chance
			 * that doing taskpid_gettask(task_getparentprocesspid()) fails, simply
			 * because the parent changed and died between loading its PID and then
			 * loading its task.
			 *
			 * As such, we'd either have to  keep on re-trying loading the  parent
			 * in that case, or simply _always_ skip the PID step (even when built
			 * for __OPTIMIZE_SIZE__). */
			return task_getparentprocess();

		default:
			break;
		}
	}
	/* Lookup a PIDFD */
	pid = handles_lookuppidfd(fd);
	FINALLY_DECREF_UNLIKELY(pid);
	result = taskpid_gettask_srch(pid);
	return result;
}

/* Same as `handman_install_into()',  but also  accept
 * symbolic handles, and use `THIS_HANDMAN' otherwise. */
PUBLIC BLOCKING NONNULL((2, 3)) fd_t FCALL
handles_install_into(fd_t fd, struct handle const *__restrict nhand,
                     /*out*/ REF struct handle *__restrict ohand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK) {
	if (fd < 0) {
		/* Special handling for symbolic handles. */
		if (handles_install_symbolic(fd, nhand, ohand))
			return fd;
	}
	return handman_install_into(THIS_HANDMAN, fd, nhand, ohand);
}

PUBLIC BLOCKING NONNULL((2)) fd_t FCALL
handles_install_into_simple(fd_t fd, struct handle const *__restrict nhand)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK) {
	fd_t result;
	REF struct handle ohand;
	result = handles_install_into(fd, nhand, &ohand);
	handle_decref(ohand); /* No-op if `HANDLE_TYPE_UNDEFINED' */
	return result;
}



/* Install a handle according to user-space openfd instructions.
 * @return: * : The file descriptor slot into which `hand' was installed. */
PUBLIC BLOCKING NONNULL((1)) fd_t FCALL
handles_install_openfd(struct handle const *__restrict hand,
                       USER UNCHECKED struct openfd *data)
		THROWS(E_BADALLOC_INSUFFICIENT_HEAP_MEMORY,
		       E_BADALLOC_INSUFFICIENT_HANDLE_NUMBERS,
		       E_INVALID_HANDLE_FILE, E_WOULDBLOCK,
		       E_SEGFAULT) {
	u16 mode, flags;
	fd_t result, hint;
	struct handle used_hnd;
	validate_readwrite(data, sizeof(*data));
	COMPILER_READ_BARRIER();
	mode  = data->of_mode;
	flags = data->of_flags;
	hint  = data->of_hint;
	COMPILER_READ_BARRIER();
	if (flags & ~(IO_CLOEXEC | IO_CLOFORK)) {
		THROW(E_INVALID_ARGUMENT_UNKNOWN_FLAG,
		      E_INVALID_ARGUMENT_CONTEXT_OPENFD_FLAGS,
		      flags, ~(IO_CLOEXEC | IO_CLOFORK), 0);
	}
	memcpy(&used_hnd, hand, sizeof(struct handle));
	used_hnd.h_mode |= flags;
	switch (mode) {

	case OPENFD_MODE_AUTO:
		hint = 0;
		ATTR_FALLTHROUGH
	case OPENFD_MODE_HINT:
		/* Do a normal handle install */
		result = handles_install(&used_hnd, hint);
		break;

	case OPENFD_MODE_INTO:
		/* Allow for symbolic handle assignments. */
		result = handles_install_into(hint, &used_hnd);
		break;

	case OPENFD_MODE_INTO_EXACT:
		/* Don't allow for symbolic handle assignments. */
		result = handman_install_into(THIS_HANDMAN, hint, &used_hnd);
		break;

	default:
		THROW(E_INVALID_ARGUMENT_UNKNOWN_COMMAND,
		      E_INVALID_ARGUMENT_CONTEXT_OPENFD_MODE,
		      mode);
		break;
	}
	COMPILER_WRITE_BARRIER();
	data->of_hint = result;
	COMPILER_WRITE_BARRIER();
	return result;
}


DECL_END

#endif /* !GUARD_KERNEL_SRC_FD_HANDLES_C */
