/* Copyright (c) 2019-2020 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2020 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_DEV_KEYBOARD_H
#define GUARD_KERNEL_INCLUDE_DEV_KEYBOARD_H 1

#include <kernel/compiler.h>

#include <debugger/config.h> /* CONFIG_HAVE_DEBUGGER */
#include <dev/char.h>
#include <kernel/types.h>
#include <sched/mutex.h>
#include <sched/signal.h>

#include <kos/keyboard.h>

#include <stdbool.h>

#include <libkeymap/keymap.h>

#ifndef CONFIG_NO_SMP
#include <hybrid/sync/atomic-rwlock.h>
#endif /* !CONFIG_NO_SMP */

DECL_BEGIN

#ifndef CONFIG_KEYBOARD_BUFFER_SIZE
#define CONFIG_KEYBOARD_BUFFER_SIZE 128
#endif /* !CONFIG_KEYBOARD_BUFFER_SIZE */


#ifdef __CC__

union keyboard_buffer_state {
	WEAK uintptr_t bs_word; /* Atomic control word. */
	struct {
		uintptr_half_t s_start; /* Offset to the first used key */
		uintptr_half_t s_used;  /* Number of used keys. */
	} bs_state;
};
struct keyboard_buffer {
	union keyboard_buffer_state kb_bufstate; /* Buffer state */
	WEAK u16                    kb_buffer[CONFIG_KEYBOARD_BUFFER_SIZE]; /* Buffer of unread keyboard inputs. */
	struct sig                  kb_avail;    /* Signal broadcast when the buffer becomes non-empty. */
};



#define KEYBOARD_DEVICE_FLAG_NORMAL  0x0000 /* Normal keyboard device flags. */
#define KEYBOARD_DEVICE_FLAG_RDKEYS  0x0001 /* Using `read(2)' on the keyboard will yield `struct keyboard_key_packet',
                                             * rather than the pre-translated ASCII characters. */
#ifndef CONFIG_NO_DEBUGGER
#define KEYBOARD_DEVICE_FLAG_DBGF12  0x0002 /* Pressing F12 4 times in a row on this keyboard will invoke `dbg()' */
#define KEYBOARD_DEVICE_FLAG_DBGF12_ONCE   0x4000 /* F12 was pressed once */
#define KEYBOARD_DEVICE_FLAG_DBGF12_TWICE  0x8000 /* F12 was pressed twice */
#define KEYBOARD_DEVICE_FLAG_DBGF12_THRICE 0xc000 /* F12 was pressed thrice */
#define KEYBOARD_DEVICE_FLAG_DBGF12_MASK   0xc000 /* Mask for the number of times F12 was pressed */
#endif /* !CONFIG_NO_DEBUGGER */


struct keyboard_device;
struct keyboard_device_ops {
	/* [0..1] Set which leds are currently lit.
	 * @param: new_leds: Set of `KEYBOARD_LED_*'
	 * NOTE: The keyboard driver itself shouldn't update the LED state
	 *       when it notices the user pressing one of the locking keys.
	 *       Instead, this operator is called once a locking key is read,
	 *       thus ensuring that what the OS sees as the active key modifiers
	 *       is in sync with the LEDs visible on the keyboard, even at times
	 *       of some major lag. */
	void (KCALL *ko_setleds)(struct keyboard_device *__restrict self, uintptr_t new_leds);
	/* XXX: Operators for configuring key repeat */
};

struct keyboard_device
#ifdef __cplusplus
	: character_device
#endif /* __cplusplus */
{
#ifndef __cplusplus
	struct character_device    kd_dev;          /* The underlying character device. */
#endif /* !__cplusplus */
	struct keyboard_device_ops kd_ops;          /* [const] Keyboard device operators. */
	struct keyboard_buffer     kd_buf;          /* Keyboard input buffer. */
	WEAK uintptr_t             kd_flags;        /* Keyboard operation flags (set of `KEYBOARD_DEVICE_FLAG_*').
	                                             * NOTE: When changed, you must broadcast `kd_buf.kb_avail' */
	struct atomic_rwlock       kd_map_lock;     /* Lock for `kd_map' */
	struct keymap              kd_map;          /* [lock(kd_maplock)][owned(kfree(.km_ext))] Keyboard key translation map. */
	size_t                     kd_map_extsiz;   /* [lock(kd_maplock)] Size (in bytes) of `kd_map::km_ext' */
	/*utf-8*/ char              kd_map_pend[32]; /* [lock(kd_maplock)] List of pending utf-8 characters (terminated by a NUL-character; empty if `kd_map_pend[0] == NUL') */
	uintptr_t                  kd_mods;         /* [lock(kd_maplock)] Currently active keyboard modifiers (Set of `KEYMOD_*'). */
	struct mutex               kd_leds_lock;    /* Lock for updating `kd_leds' */
	uintptr_t                  kd_leds;         /* [lock(kd_leds)] Set of currently lit LEDs (when modified, `ko_setled' must be called). */
};
DEFINE_REFCOUNT_TYPE_SUBCLASS(keyboard_device, character_device);


#define character_device_isakeyboard(self)                    \
	((self)->cd_heapsize >= sizeof(struct keyboard_device) && \
	 (self)->cd_type.ct_read == &keyboard_device_read)

/* Keyboard character device operators */
FUNDEF NONNULL((1)) size_t KCALL keyboard_device_read(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) syscall_slong_t KCALL keyboard_device_ioctl(struct character_device *__restrict self, syscall_ulong_t cmd, USER UNCHECKED void *arg, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) void KCALL keyboard_device_stat(struct character_device *__restrict self, USER CHECKED struct stat *result) THROWS(...);
FUNDEF NONNULL((1)) poll_mode_t KCALL keyboard_device_poll(struct character_device *__restrict self, poll_mode_t what);
/* Key-mode/character-mode read callbacks. */
FUNDEF NONNULL((1)) size_t KCALL keyboard_device_readkeys(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);
FUNDEF NONNULL((1)) size_t KCALL keyboard_device_readchars(struct character_device *__restrict self, USER CHECKED void *dst, size_t num_bytes, iomode_t mode) THROWS(...);

/* Initialize/finalize the given keyboard device.
 * NOTE: Drivers that override the `ct_fini' operator of a given keyboard
 *       must ensure that `keyboard_device_fini()' is still invoked by their
 *       override.
 * NOTE: The following operators are intrinsically provided by keyboard,
 *       get initialized by `keyboard_device_init()', and should not be
 *       overwritten:
 *         - ct_read
 *         - ct_ioctl
 *         - ct_stat
 *         - ct_poll */
FUNDEF NOBLOCK void NOTHROW(KCALL keyboard_device_init)(struct keyboard_device *__restrict self,
                                                        struct keyboard_device_ops const *__restrict ops);
FUNDEF NOBLOCK void NOTHROW(KCALL keyboard_device_fini)(struct keyboard_device *__restrict self);

/* Add a given key to the keyboard user-input buffer.
 * NOTE: The caller must not pass `KEY_NONE' for `key'
 * @return: true:  Successfully added the key.
 * @return: false: The buffer is already full and the key was not added. */
FUNDEF NOBLOCK bool NOTHROW(KCALL keyboard_buffer_putkey)(struct keyboard_buffer *__restrict self, u16 key);
FUNDEF NOBLOCK bool NOTHROW(KCALL keyboard_buffer_putkey_nopr)(struct keyboard_buffer *__restrict self, u16 key);
#ifdef CONFIG_HAVE_DEBUGGER
FUNDEF NOBLOCK bool NOTHROW(KCALL keyboard_device_putkey)(struct keyboard_device *__restrict self, u16 key);
FUNDEF NOBLOCK bool NOTHROW(KCALL keyboard_device_putkey_nopr)(struct keyboard_device *__restrict self, u16 key);
#else /* CONFIG_HAVE_DEBUGGER */
#define keyboard_device_putkey(self, key) keyboard_buffer_putkey(&(self)->kd_buf, key)
#define keyboard_device_putkey_nopr(self, key) keyboard_buffer_putkey_nopr(&(self)->kd_buf, key)
#endif /* !CONFIG_HAVE_DEBUGGER */


/* Try to read a key stroke from the given keyboard buffer.
 * @return: KEY_NONE: The buffer is empty. */
FUNDEF NOBLOCK u16 NOTHROW(KCALL keyboard_buffer_trygetkey)(struct keyboard_buffer *__restrict self);
FUNDEF u16 KCALL keyboard_buffer_getkey(struct keyboard_buffer *__restrict self) THROWS(E_WOULDBLOCK);

/* Try to read a key stroke from the given keyboard.
 * @return: { KEY_NONE, ? }: The buffer is empty. */
FUNDEF struct keyboard_key_packet KCALL keyboard_device_trygetkey(struct keyboard_device *__restrict self) THROWS(E_IOERROR, ...);
FUNDEF struct keyboard_key_packet KCALL keyboard_device_getkey(struct keyboard_device *__restrict self) THROWS(E_WOULDBLOCK, E_IOERROR, ...);

/* Try to read a character from the given keyboard.
 * @return: -1: The buffer is empty. */
FUNDEF /*utf-8*/ int KCALL keyboard_device_trygetchar(struct keyboard_device *__restrict self) THROWS(E_IOERROR, ...);
FUNDEF /*utf-8*/ char KCALL keyboard_device_getchar(struct keyboard_device *__restrict self) THROWS(E_WOULDBLOCK, E_IOERROR, ...);


#endif /* __CC__ */

DECL_END

#endif /* !GUARD_KERNEL_INCLUDE_DEV_KEYBOARD_H */
