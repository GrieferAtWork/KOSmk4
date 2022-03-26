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
#ifndef GUARD_KERNEL_INCLUDE_DEV_MOUSE_H
#define GUARD_KERNEL_INCLUDE_DEV_MOUSE_H 1

#include <kernel/compiler.h>

#include <kernel/fs/chrdev.h>
#include <kernel/types.h>
#include <sched/sig.h>

#include <hybrid/sync/atomic-rwlock.h>

#include <kos/ioctl/mouse.h>

#include <stdbool.h>

DECL_BEGIN

#ifndef CONFIG_MOUSE_BUFFER_SIZE
#define CONFIG_MOUSE_BUFFER_SIZE 256
#endif /* !CONFIG_MOUSE_BUFFER_SIZE */


#ifdef __CC__

union mousebuf_state {
	WEAK uintptr_t bs_word; /* Atomic control word. */
	struct {
		uintptr_half_t s_start; /* Offset to the first used packet */
		uintptr_half_t s_used;  /* Number of used packets. */
	} bs_state;
};

struct mousebuf {
	union mousebuf_state mb_bufstate;                         /* Buffer state */
	WEAK mouse_packet_t  mb_buffer[CONFIG_MOUSE_BUFFER_SIZE]; /* Buffer of unread mouse inputs. */
	struct sig           mb_avail;                            /* Signal send for every packet added to the buffer. */
};

#define mousebuf_init(self)           \
	((self)->mb_bufstate.bs_word = 0, \
	 sig_init(&(self)->mb_avail))
#define mousebuf_cinit(self)                            \
	(__hybrid_assert((self)->mb_bufstate.bs_word == 0), \
	 sig_cinit(&(self)->mb_avail))


struct mouse_state {
	s32 ms_abs_x;   /* Absolute position in X. */
	s32 ms_abs_y;   /* Absolute position in Y. */
	u32 ms_buttons; /* Currently held buttons. */
};

#define MOUSE_DEVICE_FLAG_NORMAL 0x0000 /* Normal mouse device flags. */
#define MOUSE_DEVICE_FLAG_GENABS 0x0001 /* Generate absolute mouse packets. */

struct mousedev_ops {
	struct chrdev_ops mo_cdev; /* Character device operators. */
};

struct mousedev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : chrdev
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct chrdev        md_dev;   /* The underlying character device. */
#define _mousedev_aschr(x) &(x)->md_dev
#define _mousedev_chr_     md_dev.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _mousedev_aschr(x) x
#define _mousedev_chr_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct mousebuf    md_buf;   /* [lock(md_lock)] Mouse input buffer. */
	struct mouse_state md_state; /* [lock(md_lock)] Current mouse state at the head of the buffer of pending inputs. */
	struct mouse_rect  md_rect;  /* [lock(md_lock)] Clip rectangle for absolute mouse positions. */
#ifndef CONFIG_NO_SMP
	struct atomic_lock md_lock;  /* Preemption-lock for writing to `md_buf', `md_state' and `md_rect' */
#endif /* !CONFIG_NO_SMP */
	WEAK uintptr_t     md_flags; /* Mouse device flags (Set of `MOUSE_DEVICE_FLAG_*') */
};

/* Operator access */
#define mousedev_getops(self) \
	((struct mousedev_ops const *)__COMPILER_REQTYPE(struct mousedev const *, self)->_mousedev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#ifdef NDEBUG
#define ___mousedev_assert_ops_(ops) /* nothing */
#else /* NDEBUG */
#define ___mousedev_assert_ops_(ops)                                             \
	__hybrid_assert((ops)->mo_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream), \
	__hybrid_assert((ops)->mo_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream->mso_read == &mousedev_v_read),
#endif /* !NDEBUG */
#define _mousedev_assert_ops_(ops) _chrdev_assert_ops_(&(ops)->mo_cdev) ___mousedev_assert_ops_(ops)

/* Helper macros */
#define mfile_ismouse(self)   ((self)->mf_ops->mo_stream && (self)->mf_ops->mo_stream->mso_read == &mousedev_v_read)
#define mfile_asmouse(self)   ((struct mousedev *)(self))
#define fnode_ismouse(self)   mfile_ismouse(_fnode_asfile(self))
#define fnode_asmouse(self)   mfile_asmouse(_fnode_asfile(self))
#define devnode_ismouse(self) fnode_ismouse(_fdevnode_asnode(self))
#define devnode_asmouse(self) fnode_asmouse(_fdevnode_asnode(self))
#define device_ismouse(self)  devnode_ismouse(_device_asdevnode(self))
#define device_asmouse(self)  devnode_asmouse(_device_asdevnode(self))
#define chrdev_ismouse(self)  device_ismouse(_chrdev_asdev(self))
#define chrdev_asmouse(self)  device_asmouse(_chrdev_asdev(self))

/* Default mouse operators. */
#define mousedev_v_destroy chrdev_v_destroy
#define mousedev_v_changed chrdev_v_changed
#define mousedev_v_wrattr  chrdev_v_wrattr
#define mousedev_v_tryas   chrdev_v_tryas
FUNDEF NONNULL((1)) size_t KCALL /* NOTE: This read operator is _MANDATORY_ and may not be overwritten by sub-classes! */
mousedev_v_read(struct mfile *__restrict self, USER CHECKED void *dst,
                size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL
mousedev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
                 USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) void KCALL
mousedev_v_stat(struct mfile *__restrict self,
                USER CHECKED struct stat *result) THROWS(...);
FUNDEF NONNULL((1)) void KCALL
mousedev_v_pollconnect(struct mfile *__restrict self,
                       poll_mode_t what) THROWS(...);
FUNDEF NONNULL((1)) poll_mode_t KCALL
mousedev_v_polltest(struct mfile *__restrict self,
                    poll_mode_t what) THROWS(...);

#ifndef CONFIG_NO_SMP
#define mousedev_smplock_tryacquire(self)   atomic_lock_tryacquire(&(self)->md_lock)
#define mousedev_smplock_acquire_nopr(self) atomic_lock_acquire_nopr(&(self)->md_lock)
#define mousedev_smplock_release_nopr(self) atomic_lock_release_nopr(&(self)->md_lock)
#define __mousedev_init_md_lock_(self)      atomic_lock_init(&(self)->md_lock),
#define __mousedev_cinit_md_lock_(self)     atomic_lock_cinit(&(self)->md_lock),
#else /* !CONFIG_NO_SMP */
#define mousedev_smplock_tryacquire(self)   1
#define mousedev_smplock_acquire_nopr(self) (void)0
#define mousedev_smplock_release_nopr(self) (void)0
#define __mousedev_init_md_lock_(self)      /* nothing */
#define __mousedev_cinit_md_lock_(self)     /* nothing */
#endif /* CONFIG_NO_SMP */

/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_mousedev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;  # s.a. `device_registerf()'
 *  - self->_mousedev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes;  # s.a. `device_registerf()'
 *  - self->_mousedev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent;    # s.a. `device_registerf()'
 *  - self->_mousedev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino;       # s.a. `device_registerf()'
 *  - self->_mousedev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode;      # Something or'd with S_IFCHR
 *  - self->_mousedev_chr_ _chrdev_dev_ _device_devnode_ dn_devno;                     # s.a. `device_registerf()'
 *  - self->_mousedev_chr_ _chrdev_dev_ dv_driver;                                     # As `incref(drv_self)'
 *  - self->_mousedev_chr_ _chrdev_dev_ dv_dirent;                                     # s.a. `device_registerf()'
 *  - self->_mousedev_chr_ _chrdev_dev_ dv_byname_node;                                # s.a. `device_registerf()'
 *  - self->md_rect
 * @param: struct mousedev     *self: Mouse to initialize.
 * @param: struct mousedev_ops *ops:  Mouse operators. */
#define _mousedev_init(self, ops)                          \
	(___mousedev_assert_ops_(ops)                          \
	 _chrdev_init(_mousedev_aschr(self), &(ops)->mo_cdev), \
	 mousebuf_init(&(self)->md_buf),                       \
	 (self)->md_state.ms_abs_x   = 0,                      \
	 (self)->md_state.ms_abs_y   = 0,                      \
	 (self)->md_state.ms_buttons = 0,                      \
	 __mousedev_init_md_lock_(self)                        \
	 (self)->md_flags = MOUSE_DEVICE_FLAG_NORMAL)
#define _mousedev_cinit(self, ops)                          \
	(___mousedev_assert_ops_(ops)                           \
	 _chrdev_cinit(_mousedev_aschr(self), &(ops)->mo_cdev), \
	 mousebuf_cinit(&(self)->md_buf),                       \
	 __hybrid_assert((self)->md_state.ms_abs_x == 0),       \
	 __hybrid_assert((self)->md_state.ms_abs_y == 0),       \
	 __hybrid_assert((self)->md_state.ms_buttons == 0),     \
	 __mousedev_cinit_md_lock_(self)                        \
	 __hybrid_assert((self)->md_flags == MOUSE_DEVICE_FLAG_NORMAL))
/* Finalize a partially initialized `struct mousedev' (as initialized by `_mousedev_init()') */
#define _mousedev_fini(self) _chrdev_fini(_mousedev_aschr(self))





/************************************************************************/
/* Mouse API Functions                                                  */
/************************************************************************/

/* Read packets from a given mouse device buffer. */
FUNDEF NOBLOCK NONNULL((1)) mouse_packet_t NOTHROW(KCALL mousebuf_trygetpacket)(struct mousebuf *__restrict self);
FUNDEF NONNULL((1)) mouse_packet_t KCALL mousebuf_getpacket(struct mousebuf *__restrict self) THROWS(E_WOULDBLOCK);

/* Generate mouse input packets
 * Note  that when generating event packets, the motion
 * packets should always be created before other events */
FUNDEF NONNULL((1)) __BOOL KCALL mousedev_motion(struct mousedev *__restrict self, s32 relx, s32 rely);
FUNDEF NONNULL((1)) __BOOL KCALL mousedev_moveto(struct mousedev *__restrict self, s32 absx, s32 absy);
FUNDEF NONNULL((1)) __BOOL KCALL mousedev_button(struct mousedev *__restrict self, u32 mask, u32 flag);
FUNDEF NONNULL((1)) __BOOL KCALL mousedev_vwheel(struct mousedev *__restrict self, s32 lines);
FUNDEF NONNULL((1)) __BOOL KCALL mousedev_hwheel(struct mousedev *__restrict self, s32 rows);
FUNDEF NONNULL((1)) __BOOL KCALL mousedev_button_ex(struct mousedev *__restrict self, u32 mask, u32 flag, u32 xflg, u32 *__restrict pold_buttons, u32 *__restrict pnew_buttons);
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(KCALL mousedev_motion_nopr)(struct mousedev *__restrict self, s32 relx, s32 rely);
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(KCALL mousedev_moveto_nopr)(struct mousedev *__restrict self, s32 absx, s32 absy);
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(KCALL mousedev_button_nopr)(struct mousedev *__restrict self, u32 mask, u32 flag);
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(KCALL mousedev_vwheel_nopr)(struct mousedev *__restrict self, s32 lines);
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(KCALL mousedev_hwheel_nopr)(struct mousedev *__restrict self, s32 rows);
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(KCALL mousedev_button_ex_nopr)(struct mousedev *__restrict self, u32 mask, u32 flag, u32 xflg, u32 *__restrict pold_buttons, u32 *__restrict pnew_buttons);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_MOUSE_H */
