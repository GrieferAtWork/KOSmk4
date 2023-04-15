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
#ifndef GUARD_KERNEL_INCLUDE_DEV_KEYBOARD_H
#define GUARD_KERNEL_INCLUDE_DEV_KEYBOARD_H 1

#include <kernel/compiler.h>

#include <debugger/config.h> /* CONFIG_HAVE_KERNEL_DEBUGGER */
#include <dev/mktty.h>
#include <kernel/types.h>
#include <sched/sig.h>

#include <kos/aref.h>
#include <kos/keyboard.h>
#include <kos/sched/shared-lock.h>
#include <linux/kd.h> /* Needed to emulate the linux keyboard interface */

#include <stdbool.h>

#include <libansitty/ansitty.h>
#include <libkeymap/keymap.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sched/atomic-rwlock.h>
#endif /* !CONFIG_NO_SMP */

DECL_BEGIN

/*[[[config CONFIG_KERNEL_KEYBOARD_BUFFER_SIZE! = 128]]]*/
#ifndef CONFIG_KERNEL_KEYBOARD_BUFFER_SIZE
#define CONFIG_KERNEL_KEYBOARD_BUFFER_SIZE 128
#endif /* !CONFIG_KERNEL_KEYBOARD_BUFFER_SIZE */
/*[[[end]]]*/


#ifdef __CC__
union kbdbuf_state {
	WEAK uintptr_t bs_word; /* Atomic control word. */
	struct {
		uintptr_half_t s_start; /* Offset to the first used key */
		uintptr_half_t s_used;  /* Number of used keys. */
	} bs_state;
};

struct kbdbuf {
	union kbdbuf_state kb_bufstate; /* Buffer state */
	WEAK u16           kb_buffer[CONFIG_KERNEL_KEYBOARD_BUFFER_SIZE]; /* Buffer of unread keyboard inputs. */
	struct sig         kb_avail;    /* Signal send for every key added to the buffer. */
};
#define kbdbuf_init(self) \
	((self)->kb_bufstate.bs_word = 0, sig_init(&(self)->kb_avail))
#define kbdbuf_cinit(self) \
	(__hybrid_assert((self)->kb_bufstate.bs_word == 0), sig_cinit(&(self)->kb_avail))




#define KEYBOARD_DEVICE_FLAG_NORMAL  0x0000 /* Normal keyboard device flags. */
#define KEYBOARD_DEVICE_FLAG_RDMODE  0x0007 /* Mask for the effective read-mode (one of `K_*' from <linux/kd.h>) */
#ifndef CONFIG_NO_KERNEL_DEBUGGER
#define KEYBOARD_DEVICE_FLAG_DBGF12  0x2000 /* Pressing F12 4 times in a row on this keyboard will invoke `dbg()' */
#define KEYBOARD_DEVICE_FLAG_DBGF12_ONCE   0x4000 /* F12 was pressed once */
#define KEYBOARD_DEVICE_FLAG_DBGF12_TWICE  0x8000 /* F12 was pressed twice */
#define KEYBOARD_DEVICE_FLAG_DBGF12_THRICE 0xc000 /* F12 was pressed thrice */
#define KEYBOARD_DEVICE_FLAG_DBGF12_MASK   0xc000 /* Mask for the number of times F12 was pressed */
#endif /* !CONFIG_NO_KERNEL_DEBUGGER */


struct kbddev;
struct kbddev_ops {
	struct chrdev_ops ko_cdev; /* Character device operators. */

	/* [0..1] Set which leds are currently lit.
	 * @param: new_leds: Set of `KEYBOARD_LED_*'
	 * NOTE: The keyboard  driver  itself  shouldn't update  the  LED  state
	 *       when it  notices the  user pressing  one of  the locking  keys.
	 *       Instead,  this operator is  called once a  locking key is read,
	 *       thus ensuring that what the OS sees as the active key modifiers
	 *       is in sync with the LEDs visible on the keyboard, even at times
	 *       of some major lag. */
	void (KCALL *ko_setleds)(struct kbddev *__restrict self, uintptr_t new_leds);
	/* XXX: Operators for configuring key repeat */
};

#ifndef __mkttydev_awref_defined
#define __mkttydev_awref_defined
AWREF(mkttydev_awref, mkttydev);
#endif /* !__mkttydev_awref_defined */

struct kbddev
#ifndef __WANT_FS_INLINE_STRUCTURES
    : chrdev                             /* The underlying character device. */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
{
#ifdef __WANT_FS_INLINE_STRUCTURES
	struct chrdev         kd_dev;        /* The underlying character device. */
#define _kbddev_aschr(x) &(x)->kd_dev
#define _kbddev_chr_     kd_dev.
#else /* __WANT_FS_INLINE_STRUCTURES */
#define _kbddev_aschr(x) x
#define _kbddev_chr_     /* nothing */
#endif /* !__WANT_FS_INLINE_STRUCTURES */
	struct kbdbuf         kd_buf;        /* Keyboard input buffer. */
	WEAK uintptr_t        kd_flags;      /* Keyboard operation flags (set of `KEYBOARD_DEVICE_FLAG_*').
	                                      * NOTE: When  changed, you  must broadcast  `kd_buf.kb_avail' */
	struct atomic_rwlock  kd_map_lock;   /* Lock for `kd_map' */
	struct keymap         kd_map;        /* [lock(kd_map_lock)][owned(kfree(.km_ext))] Keyboard key translation map. */
	size_t                kd_map_extsiz; /* [lock(kd_map_lock)] Size (in bytes) of `kd_map::km_ext' */
	uintptr_t             kd_mods;       /* [lock(kd_map_lock)] Currently active keyboard modifiers (Set of `KEYMOD_*'). */
	byte_t                kd_pend[32];   /* [0..kd_pendsz][lock(kd_map_lock)] Pending data to-be returned by `kbddev_v_read()' */
	size_t                kd_pendsz;     /* [lock(kd_map_lock)] # of pending bytes in `kd_pendsz' */
	struct shared_lock    kd_leds_lock;  /* Lock for updating `kd_leds' */
	uintptr_t             kd_leds;       /* [lock(kd_leds)] Set of currently lit LEDs (when modified, `ko_setled' must be called). */
	struct mkttydev_awref kd_tty;        /* [0..1] Weak reference to a connected TTY (used for encoding keyboard
	                                      * input  with  `ansitty_translate()',  when an  ansitty  is connected) */
};

/* Helper macros for `struct kbddev::kd_map_lock' */
#define kbddev_map_mustreap(self)     0
#define kbddev_map_reap(self)         (void)0
#define _kbddev_map_reap(self)        (void)0
#define kbddev_map_write(self)        atomic_rwlock_write(&(self)->kd_map_lock)
#define kbddev_map_write_nx(self)     atomic_rwlock_write_nx(&(self)->kd_map_lock)
#define kbddev_map_trywrite(self)     atomic_rwlock_trywrite(&(self)->kd_map_lock)
#define kbddev_map_endwrite(self)     (atomic_rwlock_endwrite(&(self)->kd_map_lock), kbddev_map_reap(self))
#define _kbddev_map_endwrite(self)    atomic_rwlock_endwrite(&(self)->kd_map_lock)
#define kbddev_map_read(self)         atomic_rwlock_read(&(self)->kd_map_lock)
#define kbddev_map_read_nx(self)      atomic_rwlock_read_nx(&(self)->kd_map_lock)
#define kbddev_map_tryread(self)      atomic_rwlock_tryread(&(self)->kd_map_lock)
#define _kbddev_map_endread(self)     atomic_rwlock_endread(&(self)->kd_map_lock)
#define kbddev_map_endread(self)      (void)(atomic_rwlock_endread_ex(&(self)->kd_map_lock) && (kbddev_map_reap(self), 0))
#define _kbddev_map_end(self)         atomic_rwlock_end(&(self)->kd_map_lock)
#define kbddev_map_end(self)          (void)(atomic_rwlock_end_ex(&(self)->kd_map_lock) && (kbddev_map_reap(self), 0))
#define kbddev_map_upgrade(self)      atomic_rwlock_upgrade(&(self)->kd_map_lock)
#define kbddev_map_upgrade_nx(self)   atomic_rwlock_upgrade_nx(&(self)->kd_map_lock)
#define kbddev_map_tryupgrade(self)   atomic_rwlock_tryupgrade(&(self)->kd_map_lock)
#define kbddev_map_downgrade(self)    atomic_rwlock_downgrade(&(self)->kd_map_lock)
#define kbddev_map_reading(self)      atomic_rwlock_reading(&(self)->kd_map_lock)
#define kbddev_map_writing(self)      atomic_rwlock_writing(&(self)->kd_map_lock)
#define kbddev_map_canread(self)      atomic_rwlock_canread(&(self)->kd_map_lock)
#define kbddev_map_canwrite(self)     atomic_rwlock_canwrite(&(self)->kd_map_lock)
#define kbddev_map_waitread(self)     atomic_rwlock_waitread(&(self)->kd_map_lock)
#define kbddev_map_waitwrite(self)    atomic_rwlock_waitwrite(&(self)->kd_map_lock)
#define kbddev_map_waitread_nx(self)  atomic_rwlock_waitread_nx(&(self)->kd_map_lock)
#define kbddev_map_waitwrite_nx(self) atomic_rwlock_waitwrite_nx(&(self)->kd_map_lock)


/* Helper macros for `struct kbddev::kd_leds_lock' */
#define _kbddev_leds_reap(self)      (void)0
#define kbddev_leds_reap(self)       (void)0
#define kbddev_leds_mustreap(self)   0
#define kbddev_leds_tryacquire(self) shared_lock_tryacquire(&(self)->kd_leds_lock)
#define kbddev_leds_acquire(self)    shared_lock_acquire(&(self)->kd_leds_lock)
#define kbddev_leds_acquire_nx(self) shared_lock_acquire_nx(&(self)->kd_leds_lock)
#define _kbddev_leds_release(self)   shared_lock_release(&(self)->kd_leds_lock)
#define kbddev_leds_release(self)    (shared_lock_release(&(self)->kd_leds_lock), kbddev_leds_reap(self))
#define kbddev_leds_acquired(self)   shared_lock_acquired(&(self)->kd_leds_lock)
#define kbddev_leds_available(self)  shared_lock_available(&(self)->kd_leds_lock)


/* Operator access */
#define kbddev_getops(self) \
	((struct kbddev_ops const *)__COMPILER_REQTYPE(struct kbddev const *, self)->_kbddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_ops)
#ifdef NDEBUG
#define _kbddev_only_assert_ops_(ops) /* nothing */
#else /* NDEBUG */
#define _kbddev_only_assert_ops_(ops)                                            \
	__hybrid_assert((ops)->ko_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream), \
	__hybrid_assert((ops)->ko_cdev.cdo_dev.do_node.dvno_node.no_file.mo_stream->mso_read == &kbddev_v_read),
#endif /* !NDEBUG */
#define _kbddev_assert_ops_(ops) _chrdev_assert_ops_(&(ops)->ko_cdev) _kbddev_only_assert_ops_(ops)

/* Helper macros */
#define mfile_iskbd(self)   ((self)->mf_ops->mo_stream && (self)->mf_ops->mo_stream->mso_read == &kbddev_v_read)
#define mfile_askbd(self)   ((struct kbddev *)(self))
#define fnode_iskbd(self)   mfile_iskbd(_fnode_asfile(self))
#define fnode_askbd(self)   mfile_askbd(_fnode_asfile(self))
#define devnode_iskbd(self) fnode_iskbd(_fdevnode_asnode(self))
#define devnode_askbd(self) fnode_askbd(_fdevnode_asnode(self))
#define device_iskbd(self)  devnode_iskbd(_device_asdevnode(self))
#define device_askbd(self)  devnode_askbd(_device_asdevnode(self))
#define chrdev_iskbd(self)  device_iskbd(_chrdev_asdev(self))
#define chrdev_askbd(self)  device_askbd(_chrdev_asdev(self))

/* Default keyboard operators. */
FUNDEF NOBLOCK NONNULL((1)) void
NOTHROW(KCALL kbddev_v_destroy)(struct mfile *__restrict self);
#define kbddev_v_changed chrdev_v_changed
#define kbddev_v_wrattr  chrdev_v_wrattr
#define kbddev_v_tryas   chrdev_v_tryas
FUNDEF NONNULL((1)) size_t KCALL /* NOTE: This read operator is _MANDATORY_ and may not be overwritten by sub-classes! */
kbddev_v_read(struct mfile *__restrict self, USER CHECKED void *dst,
              size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL
kbddev_v_ioctl(struct mfile *__restrict self, ioctl_t cmd,
               USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) void KCALL
kbddev_v_stat(struct mfile *__restrict self,
              USER CHECKED struct stat *result) THROWS(...);
FUNDEF NONNULL((1)) void KCALL
kbddev_v_pollconnect(struct mfile *__restrict self,
                     poll_mode_t what) THROWS(...);
FUNDEF NONNULL((1)) poll_mode_t KCALL
kbddev_v_polltest(struct mfile *__restrict self,
                  poll_mode_t what) THROWS(...);
/* Default set of stream operators for keyboard devices (s.a.: the operators above) */
DATDEF struct mfile_stream_ops const kbddev_v_stream_ops;


#if !defined(CONFIG_NO_KERNEL_DEBUGGER) && defined(KEYBOARD_DEVICE_FLAG_DBGF12)
#define _kbddev_init_flags(self) (self)->kd_flags = K_UNICODE | KEYBOARD_DEVICE_FLAG_DBGF12
#else /* !CONFIG_NO_KERNEL_DEBUGGER && KEYBOARD_DEVICE_FLAG_DBGF12 */
#define _kbddev_init_flags(self) (self)->kd_flags = K_UNICODE | KEYBOARD_DEVICE_FLAG_NORMAL
#endif /* CONFIG_NO_KERNEL_DEBUGGER || !KEYBOARD_DEVICE_FLAG_DBGF12 */
#define _kbddev_cinit_flags _kbddev_init_flags


/* Initialize common+basic fields. The caller must still initialize:
 *  - self->_kbddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ _fnode_file_ mf_flags |= MFILE_FN_GLOBAL_REF;  # s.a. `device_registerf()'
 *  - self->_kbddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_allnodes;  # s.a. `device_registerf()'
 *  - self->_kbddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_supent;    # s.a. `device_registerf()'
 *  - self->_kbddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_ino;       # s.a. `device_registerf()'
 *  - self->_kbddev_chr_ _chrdev_dev_ _device_devnode_ _fdevnode_node_ fn_mode;      # Something or'd with S_IFCHR
 *  - self->_kbddev_chr_ _chrdev_dev_ _device_devnode_ dn_devno;                     # s.a. `device_registerf()'
 *  - self->_kbddev_chr_ _chrdev_dev_ dv_driver;                                     # As `incref(drv_self)'
 *  - self->_kbddev_chr_ _chrdev_dev_ dv_dirent;                                     # s.a. `device_registerf()'
 *  - self->_kbddev_chr_ _chrdev_dev_ dv_byname_node;                                # s.a. `device_registerf()'
 * @param: struct kbddev     *self: Keyboard to initialize.
 * @param: struct kbddev_ops *ops:  Keyboard operators. */
#define _kbddev_init(self, ops)                          \
	(_kbddev_only_assert_ops_(ops)                       \
	 _chrdev_init(_kbddev_aschr(self), &(ops)->ko_cdev), \
	 kbdbuf_init(&(self)->kd_buf),                       \
	 _kbddev_init_flags(self),                           \
	 atomic_rwlock_init(&(self)->kd_map_lock),           \
	 keymap_init_en_US(&(self)->kd_map),                 \
	 (self)->kd_map_extsiz = 0,                          \
	 (self)->kd_mods       = 0,                          \
	 (self)->kd_pendsz     = 0,                          \
	 shared_lock_init(&(self)->kd_leds_lock),            \
	 (self)->kd_leds = 0,                                \
	 awref_init(&(self)->kd_tty, __NULLPTR))
#define _kbddev_cinit(self, ops)                          \
	(_kbddev_only_assert_ops_(ops)                        \
	 _chrdev_cinit(_kbddev_aschr(self), &(ops)->ko_cdev), \
	 kbdbuf_cinit(&(self)->kd_buf),                       \
	 _kbddev_cinit_flags(self),                           \
	 atomic_rwlock_cinit(&(self)->kd_map_lock),           \
	 keymap_init_en_US(&(self)->kd_map),                  \
	 __hybrid_assert((self)->kd_map_extsiz == 0),         \
	 __hybrid_assert((self)->kd_mods == 0),               \
	 __hybrid_assert((self)->kd_pendsz == 0),             \
	 shared_lock_cinit(&(self)->kd_leds_lock),            \
	 __hybrid_assert((self)->kd_leds == 0),               \
	 awref_cinit(&(self)->kd_tty, __NULLPTR))
/* Finalize a partially initialized `struct kbddev' (as initialized by `_kbddev_init()') */
#define _kbddev_fini(self) _chrdev_fini(_kbddev_aschr(self))




/************************************************************************/
/* Keyboard API functions                                               */
/************************************************************************/

/* Add a given key to the keyboard user-input  buffer.
 * NOTE: The caller must not pass `KEY_NONE' for `key'
 * @return: true:  Successfully added the key.
 * @return: false: The buffer is already full and the key was not added. */
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL kbdbuf_putkey)(struct kbdbuf *__restrict self, u16 key);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) __BOOL NOTHROW(FCALL kbdbuf_putkey_nopr)(struct kbdbuf *__restrict self, u16 key);
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
FUNDEF NOBLOCK NONNULL((1)) __BOOL NOTHROW(FCALL kbddev_putkey)(struct kbddev *__restrict self, u16 key);
FUNDEF NOBLOCK NOPREEMPT NONNULL((1)) __BOOL NOTHROW(FCALL kbddev_putkey_nopr)(struct kbddev *__restrict self, u16 key);
#else /* CONFIG_HAVE_KERNEL_DEBUGGER */
#define kbddev_putkey(self, key)      kbdbuf_putkey(&(self)->kd_buf, key)
#define kbddev_putkey_nopr(self, key) kbdbuf_putkey_nopr(&(self)->kd_buf, key)
#endif /* !CONFIG_HAVE_KERNEL_DEBUGGER */


/* Try to read a key stroke from the given keyboard buffer.
 * @return: KEY_NONE: The buffer is empty. */
FUNDEF NOBLOCK NONNULL((1)) u16 NOTHROW(KCALL kbdbuf_trygetkey)(struct kbdbuf *__restrict self);
FUNDEF NONNULL((1)) u16 KCALL kbdbuf_getkey(struct kbdbuf *__restrict self) THROWS(E_WOULDBLOCK);

/* Try to read a key stroke from the given keyboard.
 * @return: { KEY_NONE, ? }: The buffer is empty. */
FUNDEF NONNULL((1)) struct kbd_packet KCALL kbddev_trygetkey(struct kbddev *__restrict self) THROWS(E_IOERROR, ...);
FUNDEF NONNULL((1)) struct kbd_packet KCALL kbddev_getkey(struct kbddev *__restrict self) THROWS(E_WOULDBLOCK, E_IOERROR, ...);

/* Try to read a single byte from the keyboard data stream.
 * Same as `kbddev_v_read()'.
 * @return: -1: No data is available at the moment. */
FUNDEF NONNULL((1)) int KCALL kbddev_trygetc(struct kbddev *__restrict self) THROWS(E_IOERROR, ...);
FUNDEF NONNULL((1)) byte_t KCALL kbddev_getc(struct kbddev *__restrict self) THROWS(E_WOULDBLOCK, E_IOERROR, ...);

#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_KEYBOARD_H */
