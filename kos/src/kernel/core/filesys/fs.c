/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_FILESYS_FS_C
#define GUARD_KERNEL_CORE_FILESYS_FS_C 1
#define _GNU_SOURCE 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <kernel/fs/fs.h>
#include <kernel/fs/path.h>
#include <kernel/fs/vfs.h>
#include <kernel/malloc.h>
#include <sched/task.h>

#include <kos/except.h>

#include <assert.h>
#include <atomic.h>
#include <limits.h>
#include <sched.h>
#include <stddef.h>

DECL_BEGIN

/* Destroy the given FS controller. */
PUBLIC NOBLOCK NONNULL((1)) void
NOTHROW(FCALL fs_destroy)(struct fs *__restrict self) {
	unsigned int i;
	for (i = 0; i < lengthof(self->fs_dcwd); ++i)
		xdecref_unlikely(self->fs_dcwd[i]);
	decref_unlikely(self->fs_cwd);
	decref_unlikely(self->fs_root);
	decref_unlikely(self->fs_vfs);
	kfree(self);
}


/* Default kernel and /bin/init FS controller. */
PUBLIC struct fs fs_kernel = {
	.fs_refcnt   = 3, /* +1: fs_kernel, +1: this_fs@boottask, +1: this_fs@bootidle */
	.fs_vfs      = &vfs_kernel,
	.fs_pathlock = ATOMIC_RWLOCK_INIT,
	.fs_root     = NULL, /* Initialized once rootfs gets mounted */
	.fs_cwd      = NULL, /* Initialized once rootfs gets mounted */
	.fs_dcwd     = { NULL, },
	.fs_umask    = FS_DEFAULT_UMASK,
	.fs_lnkmax   = SYMLOOP_MAX,
	.fs_mode     = {{
		/*.f_atmask = */ (uint32_t)~0,
		/*.f_atflag = */ (uint32_t)0,
	}},
};

/* [1..1][lock(PRIVATE(THIS_TASK))] Filesystem controller for the current thread.
 * Even  though this pointer can be modified by the thread itself, it must not be
 * altered from within any kind of RPC. Lots of filesystem functionality  assumes
 * that this pointer cannot changed over  the course of some operation.  However,
 * it  is OK for this pointer to change  outside the context of any FS operation,
 * such as a top-level system call.
 *
 * NOTE: Initialize changed to `NULL' in `kernel_initialize_scheduler_after_smp()' */
PUBLIC ATTR_PERTASK ATTR_ALIGN(REF struct fs *) this_fs = &fs_kernel;

DEFINE_PERTASK_FINI(fini_this_fs);
INTERN NOBLOCK NONNULL((1)) void
NOTHROW(KCALL fini_this_fs)(struct task *__restrict self) {
	xdecref(FORTASK(self, this_fs));
}



/* Lock for accessing any remote thread's this_fs field */
#ifndef CONFIG_NO_SMP
PRIVATE struct atomic_lock this_fs_smplock = ATOMIC_LOCK_INIT;
#endif /* !CONFIG_NO_SMP */
#define this_fs_smplock_acquire() atomic_lock_acquire_smp(&this_fs_smplock)
#define this_fs_smplock_release() atomic_lock_release_smp(&this_fs_smplock)



/* Return the handle manager of the given thread. */
PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fs *
NOTHROW(FCALL task_getfs)(struct task *__restrict thread) {
	REF struct fs *result;
	this_fs_smplock_acquire();
	result = incref(FORTASK(thread, this_fs));
	this_fs_smplock_release();
	return result;
}

PUBLIC NOBLOCK ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct vfs *
NOTHROW(FCALL task_getvfs)(struct task *__restrict thread) {
	REF struct vfs *result;
	this_fs_smplock_acquire();
	result = incref(FORTASK(thread, this_fs)->fs_vfs);
	this_fs_smplock_release();
	return result;
}

/* Exchange the handle manager of the calling thread. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fs *
NOTHROW(FCALL task_setfs_inherit)(/*inherit(always)*/ REF struct fs *__restrict newfs) {
	REF struct fs *result;
	this_fs_smplock_acquire();
	result = PERTASK_GET(this_fs); /* Inherit reference */
	PERTASK_SET(this_fs, newfs);   /* Inherit reference */
	this_fs_smplock_release();
	return result;
}



/* Clone the given FS
 * @param: clone_vfs: When true, also clone the VFS, else share the same one. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct fs *KCALL
fs_clone(struct fs *__restrict self, bool clone_vfs) THROWS(E_BADALLOC) {
	REF struct fs *result;
	unsigned int i;
	if (clone_vfs)
		THROW(E_NOT_IMPLEMENTED_TODO); /* TODO */
	result = (REF struct fs *)kmalloc(sizeof(struct fs), GFP_NORMAL);
	TRY {
		fs_pathlock_read(self);
	} EXCEPT {
		kfree(result);
		RETHROW();
	}
	/* Duplicate path references. */
	result->fs_root = incref(self->fs_root);
	result->fs_cwd  = incref(self->fs_cwd);
	for (i = 0; i < lengthof(self->fs_dcwd); ++i)
		result->fs_dcwd[i] = xincref(self->fs_dcwd[i]);
	fs_pathlock_endread(self);
	result->fs_vfs    = incref(self->fs_vfs);
	result->fs_refcnt = 1;
	atomic_rwlock_init(&result->fs_pathlock);
	result->fs_umask  = atomic_read_relaxed(&self->fs_umask);
	result->fs_lnkmax = atomic_read_relaxed(&self->fs_lnkmax);
	atomic64_init(&result->fs_mode.f_atom, atomic64_read(&self->fs_mode.f_atom));
	return result;
}


/* Return currently set CWD/ROOT of the given filesystem. */
PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *FCALL
fs_getcwd(struct fs *__restrict self) THROWS(E_WOULDBLOCK) {
	REF struct path *result;
	fs_pathlock_read(self);
	result = incref(self->fs_cwd);
	fs_pathlock_endread(self);
	return result;
}

PUBLIC ATTR_RETNONNULL WUNUSED NONNULL((1)) REF struct path *FCALL
fs_getroot(struct fs *__restrict self) THROWS(E_WOULDBLOCK) {
	REF struct path *result;
	fs_pathlock_read(self);
	result = incref(self->fs_root);
	fs_pathlock_endread(self);
	return result;
}


PUBLIC ATTR_PURE WUNUSED atflag_t
NOTHROW(FCALL fs_atflags)(atflag_t atflags) {
	fs_mask_t mask;
	mask.f_mode = atomic64_read(&THIS_FS->fs_mode.f_atom);
	return (atflags & mask.f_atmask) | mask.f_atflag;
}

DECL_END

#endif /* !GUARD_KERNEL_CORE_FILESYS_FS_C */
