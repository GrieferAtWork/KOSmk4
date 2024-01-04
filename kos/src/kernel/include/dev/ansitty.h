/* Copyright (c) 2019-2024 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2024 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_DEV_ANSITTY_H
#define GUARD_KERNEL_INCLUDE_DEV_ANSITTY_H 1

#include <kernel/compiler.h>

#include <dev/mktty.h>

#include <libansitty/ansitty.h>

DECL_BEGIN

#ifdef __CC__

#ifndef __mkttydev_awref_defined
#define __mkttydev_awref_defined
AWREF(mkttydev_awref, mkttydev);
#endif /* !__mkttydev_awref_defined */

struct ansittydev_ops {
	struct chrdev_ops ato_cdev; /* Character device operators. */
};

struct ansittydev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : chrdev                       /* The underling character-device */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct chrdev         at_cdev; /* The underling character-device */
#define _ansittydev_aschr(x) &(x)->at_cdev
#define _ansittydev_chr_     at_cdev.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _ansittydev_aschr(x) x
#define _ansittydev_chr_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct ansitty        at_ansi; /* Ansi TTY support. */
	struct mkttydev_awref at_tty;  /* [0..1] Weak reference to a connected TTY (used for injecting keyboard input) */
};


/* Operator access */
#define ansittydev_getops(self) \
	((struct ansittydev_ops const *)__COMPILER_REQTYPE(struct ansittydev const *, self)->_ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#ifdef NDEBUG
#define _ansittydev_only_assert_ops_(ops) /* nothing */
#else /* NDEBUG */
#define _ansittydev_only_assert_ops_(ops)                                         \
	__hybrid_assert((ops)->ato_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream), \
	__hybrid_assert((ops)->ato_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream->mso_write == &ansittydev_v_write),
#endif /* !NDEBUG */
#define _ansittydev_assert_ops_(ops) _chrdev_assert_ops_(&(ops)->ato_cdev) _ansittydev_only_assert_ops_(ops)

/* Helper macros */
#define mfile_isansitty(self)   ((self)->mf_ops->mo_stream && (self)->mf_ops->mo_stream->mso_write == &ansittydev_v_write)
#define mfile_asansitty(self)   ((struct ansittydev *)(self))
#define fnode_isansitty(self)   mfile_isansitty(_fnode_asfile(self))
#define fnode_asansitty(self)   mfile_asansitty(_fnode_asfile(self))
#define devnode_isansitty(self) fnode_isansitty(_fdevnode_asnode(self))
#define devnode_asansitty(self) fnode_asansitty(_fdevnode_asnode(self))
#define device_isansitty(self)  devnode_isansitty(_device_asdevnode(self))
#define device_asansitty(self)  devnode_asansitty(_device_asdevnode(self))
#define chrdev_isansitty(self)  device_isansitty(_chrdev_asdev(self))
#define chrdev_asansitty(self)  device_asansitty(_chrdev_asdev(self))

/* Default ansitty operators. */
#define ansittydev_v_destroy chrdev_v_destroy
#define ansittydev_v_changed chrdev_v_changed
#define ansittydev_v_wrattr  chrdev_v_wrattr
#define ansittydev_v_tryas   chrdev_v_tryas
FUNDEF NONNULL((1)) size_t KCALL /* NOTE: This read operator is _MANDATORY_ and may not be overwritten by sub-classes! */
ansittydev_v_write(struct mfile *__restrict self,
                   NCX void const *src,
                   size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL
ansittydev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                   NCX UNCHECKED void *arg, iomode_t mode) THROWS(...);

/* Mandatory TTY operators for ansitty objects. (automatically installed) */
FUNDEF NONNULL((1)) void LIBANSITTY_CC __ansittydev_v_output(struct ansitty *__restrict self, void const *data, size_t datalen) ASMNAME("ansittydev_v_output");
FUNDEF NONNULL((1)) void LIBANSITTY_CC __ansittydev_v_setled(struct ansitty *__restrict self, uint8_t mask, uint8_t flag) ASMNAME("ansittydev_v_setled");
FUNDEF NONNULL((1, 2)) __BOOL LIBANSITTY_CC __ansittydev_v_termios(struct ansitty *__restrict self, struct termios *__restrict oldios, struct termios const *newios) ASMNAME("ansittydev_v_termios");

/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;  # s.a. `device_registerf()'
 *  - self->_ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes;  # s.a. `device_registerf()'
 *  - self->_ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent;    # s.a. `device_registerf()'
 *  - self->_ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino;       # s.a. `device_registerf()'
 *  - self->_ansittydev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode;      # Something or'd with S_IFCHR
 *  - self->_ansittydev_chr_ _chrdev_dev_ _device_devnode_ dn_devno;                     # s.a. `device_registerf()'
 *  - self->_ansittydev_chr_ _chrdev_dev_ dv_driver;                                     # As `incref(drv_self)'
 *  - self->_ansittydev_chr_ _chrdev_dev_ dv_dirent;                                     # s.a. `device_registerf()'
 *  - self->_ansittydev_chr_ _chrdev_dev_ dv_byname_node;                                # s.a. `device_registerf()'
 * @param: struct ansittydev              *self:    Ansitty to initialize.
 * @param: struct ansittydev_ops const    *ops:     Ansitty operators.
 * @param: struct ansitty_operators const *tty_ops: TTY operators. NOTE: `ato_output', `ato_setled' and `ato_termios' must _NOT_
 *                                                  be implemented; these operators are provided by the internal implementation! */
#define _ansittydev_init(self, ops, tty_ops)                       \
	(_ansittydev_only_assert_ops_(ops)                             \
	 __hybrid_assert((tty_ops)->ato_output == __NULLPTR),          \
	 __hybrid_assert((tty_ops)->ato_setled == __NULLPTR),          \
	 __hybrid_assert((tty_ops)->ato_termios == __NULLPTR),         \
	 _chrdev_init(_ansittydev_aschr(self), &(ops)->ato_cdev),      \
	 ansitty_init(&(self)->at_ansi, tty_ops),                      \
	 (self)->at_ansi.at_ops.ato_output  = &__ansittydev_v_output,  \
	 (self)->at_ansi.at_ops.ato_setled  = &__ansittydev_v_setled,  \
	 (self)->at_ansi.at_ops.ato_termios = &__ansittydev_v_termios, \
	 awref_init(&(self)->at_tty, __NULLPTR))
#define _ansittydev_cinit(self, ops, tty_ops)                      \
	(_ansittydev_only_assert_ops_(ops)                             \
	 __hybrid_assert((tty_ops)->ato_output == __NULLPTR),          \
	 __hybrid_assert((tty_ops)->ato_setled == __NULLPTR),          \
	 __hybrid_assert((tty_ops)->ato_termios == __NULLPTR),         \
	 _chrdev_cinit(_ansittydev_aschr(self), &(ops)->ato_cdev),     \
	 ansitty_init(&(self)->at_ansi, tty_ops),                      \
	 (self)->at_ansi.at_ops.ato_output  = &__ansittydev_v_output,  \
	 (self)->at_ansi.at_ops.ato_setled  = &__ansittydev_v_setled,  \
	 (self)->at_ansi.at_ops.ato_termios = &__ansittydev_v_termios, \
	 awref_cinit(&(self)->at_tty, __NULLPTR))
/* Finalize a partially initialized `struct ansittydev' (as initialized by `_ansittydev_init()') */
#define _ansittydev_fini(self) _chrdev_fini(_ansittydev_aschr(self))

#endif /* __CC__ */


DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_ANSITTY_H */
