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
#ifndef GUARD_KERNEL_INCLUDE_DEV_TTY_H
#define GUARD_KERNEL_INCLUDE_DEV_TTY_H 1

#include <kernel/compiler.h>

#include <kernel/fs/chrdev.h>
#include <kernel/types.h>
#include <sched/group.h>


#include <libterm/termio.h>

DECL_BEGIN

/* The base type for PTY and TTY devices */
#ifdef __CC__
struct taskpid;
struct stat;

#ifndef __procgrp_awref_defined
#define __procgrp_awref_defined
struct procgrp;
AWREF(procgrp_awref, procgrp);
#endif /* !__procgrp_awref_defined */

struct ttydev_ops {
	struct chrdev_ops to_cdev; /* Character device operators. */
};

struct ttydev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : chrdev                      /* The underling character-device */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct chrdev        t_cdev;  /* The underling character-device */
#define _ttydev_aschr(x) &(x)->t_cdev
#define _ttydev_chr_     t_cdev.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _ttydev_aschr(x) x
#define _ttydev_chr_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct terminal      t_term;  /* The associated terminal driver controller. */
	struct procgrp_awref t_cproc; /* [0..1] Session controlled by this tty. */
	struct procgrp_awref t_fproc; /* [0..1] Foreground process group. */
};


/* Kernel-level implementations for terminal system operators. */
FUNDEF NONNULL((1)) ssize_t LIBTERM_CC __ttydev_v_chk_sigttou(struct terminal *__restrict self) ASMNAME("ttydev_v_chk_sigttou");
FUNDEF NONNULL((1)) ssize_t LIBTERM_CC __ttydev_v_raise(struct terminal *__restrict self, signo_t signo) ASMNAME("ttydev_v_raise");


/* Operator access */
#define ttydev_getops(self) \
	((struct ttydev_ops const *)__COMPILER_REQTYPE(struct ttydev const *, self)->_ttydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#ifdef NDEBUG
#define _ttydev_only_assert_ops_(ops) /* nothing */
#else /* NDEBUG */
#define _ttydev_only_assert_ops_(ops)                                                                        \
	__hybrid_assert((ops)->to_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream),                             \
	__hybrid_assert((ops)->to_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream->mso_read == &ttydev_v_read), \
	__hybrid_assert((ops)->to_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream->mso_write == &ttydev_v_write),
#endif /* !NDEBUG */
#define _ttydev_assert_ops_(ops) _chrdev_assert_ops_(&(ops)->to_cdev) _ttydev_only_assert_ops_(ops)

/* Helper macros */
#define mfile_istty(self)   ((self)->mf_ops->mo_stream && (self)->mf_ops->mo_stream->mso_read == &ttydev_v_read)
#define mfile_astty(self)   ((struct ttydev *)(self))
#define fnode_istty(self)   mfile_istty(_fnode_asfile(self))
#define fnode_astty(self)   mfile_astty(_fnode_asfile(self))
#define devnode_istty(self) fnode_istty(_fdevnode_asnode(self))
#define devnode_astty(self) fnode_astty(_fdevnode_asnode(self))
#define device_istty(self)  devnode_istty(_device_asdevnode(self))
#define device_astty(self)  devnode_astty(_device_asdevnode(self))
#define chrdev_istty(self)  device_istty(_chrdev_asdev(self))
#define chrdev_astty(self)  device_astty(_chrdev_asdev(self))

/* Default tty operators. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL ttydev_v_destroy)(struct mfile *__restrict self);
FUNDEF BLOCKING NONNULL((1, 2)) void KCALL /* Implements handling for `O_NOCTTY' */
ttydev_v_open(struct mfile *__restrict self,
              /*in|out*/ REF struct handle *__restrict hand,
              struct path *access_path,
              struct fdirent *access_dent,
              oflag_t oflags);
#define ttydev_v_changed chrdev_v_changed
#define ttydev_v_wrattr  chrdev_v_wrattr
#define ttydev_v_tryas   chrdev_v_tryas
FUNDEF NONNULL((1)) size_t KCALL /* NOTE: This read operator is _MANDATORY_ and may NOT be overwritten by sub-classes! */
ttydev_v_read(struct mfile *__restrict self, USER CHECKED void *dst,
              size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) size_t KCALL /* NOTE: This write operator is _MANDATORY_ and may NOT be overwritten by sub-classes! */
ttydev_v_write(struct mfile *__restrict self, USER CHECKED void const *src,
               size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL
ttydev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) void KCALL
ttydev_v_stat(struct mfile *__restrict self,
              USER CHECKED struct stat *result) THROWS(...);
FUNDEF NONNULL((1)) void KCALL
ttydev_v_pollconnect(struct mfile *__restrict self,
                     poll_mode_t what) THROWS(...);
FUNDEF NONNULL((1)) poll_mode_t KCALL
ttydev_v_polltest(struct mfile *__restrict self,
                  poll_mode_t what) THROWS(...);

/* @return: -EINVAL: Unsupported `cmd' */
FUNDEF NONNULL((1)) syscall_slong_t KCALL
_ttydev_tryioctl(struct mfile *__restrict self, ioctl_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_ttydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;  # s.a. `device_registerf()'
 *  - self->_ttydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes;  # s.a. `device_registerf()'
 *  - self->_ttydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent;    # s.a. `device_registerf()'
 *  - self->_ttydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino;       # s.a. `device_registerf()'
 *  - self->_ttydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode;      # Something or'd with S_IFCHR
 *  - self->_ttydev_chr_ _chrdev_dev_ _device_devnode_ dn_devno;                     # s.a. `device_registerf()'
 *  - self->_ttydev_chr_ _chrdev_dev_ dv_driver;                                     # As `incref(drv_self)'
 *  - self->_ttydev_chr_ _chrdev_dev_ dv_dirent;                                     # s.a. `device_registerf()'
 *  - self->_ttydev_chr_ _chrdev_dev_ dv_byname_node;                                # s.a. `device_registerf()'
 * @param: struct ttydev       *self:     TTY to initialize.
 * @param: struct ttydev_ops   *ops:      TTY operators.
 * @param: pterminal_oprinter_t oprinter: [1..1] Terminal output printer. */
#define _ttydev_init(self, ops, oprinter)                \
	(_ttydev_only_assert_ops_(ops)                       \
	 _chrdev_init(_ttydev_aschr(self), &(ops)->to_cdev), \
	 terminal_init(&(self)->t_term, oprinter,            \
	               &__ttydev_v_raise,                    \
	               &__ttydev_v_chk_sigttou),             \
	 awref_init(&(self)->t_cproc, __NULLPTR),            \
	 awref_init(&(self)->t_fproc, __NULLPTR))
#define _ttydev_cinit(self, ops)                          \
	(_ttydev_only_assert_ops_(ops)                        \
	 _chrdev_cinit(_ttydev_aschr(self), &(ops)->to_cdev), \
	 terminal_init(&(self)->t_term, oprinter,             \
	               &__ttydev_v_raise,                     \
	               &__ttydev_v_chk_sigttou),              \
	 awref_cinit(&(self)->t_cproc, __NULLPTR),            \
	 awref_cinit(&(self)->t_fproc, __NULLPTR))
/* Finalize a partially initialized `struct ttydev' (as initialized by `_ttydev_init()') */
#define _ttydev_fini(self) _chrdev_fini(_ttydev_aschr(self))



/* Returns a reference to the controlling- or foreground process
 * group, or  NULL  if  the specified  field  hasn't  been  set. */
#define ttydev_getcproc(self) awref_get(&(self)->t_cproc)
#define ttydev_getfproc(self) awref_get(&(self)->t_fproc)

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_TTY_H */
