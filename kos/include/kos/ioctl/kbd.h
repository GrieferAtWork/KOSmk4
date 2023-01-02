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
#ifndef _KOS_IOCTL_KBD_H
#define _KOS_IOCTL_KBD_H 1

/* KOS-specific keyboard-device system interface. */

#include <__stdinc.h>
#include <asm/ioctl.h>
#include <bits/types.h>


#define KEYBOARD_LED_NONE       0x0000
#define KEYBOARD_LED_SCROLLLOCK 0x0100
#define KEYBOARD_LED_NUMLOCK    0x0200
#define KEYBOARD_LED_CAPSLOCK   0x0400

#ifdef __CC__
__DECL_BEGIN

struct kbd_packet {
	__uint16_t  kp_mod; /* Set of `KEYMOD_*' from <kos/keyboard.h> */
	__uint16_t  kp_key; /* The pressed key (one of `KEY_*' from <kos/keyboard.h>) */
};
struct kbd_keymap {
	__byte_t   *km_maptext; /* [0..km_mapsize] Pointer to a key translation program (== `Kmp_Data::d_code') */
	__size_t    km_mapsize; /* Size of the key translation program (in bytes; == `keymap_codesize(Kmp_Data::d_code)') */
	__uint8_t   km_defenc;  /* Default encoding. */
};
struct kbd_ledmask {
	/* Structure used by `KBD_IOC_MASKLED' */
	__uint32_t  lm_mask;   /* [IN] Mask of LEDs to keep unchanged */
	__uint32_t  lm_flag;   /* [IN] Mask of LEDs to turn on */
	__uint32_t  lm_fxor;   /* [IN] Mask of LEDs to toggle */
	__uint32_t  lm_oldled; /* [OUT] Mask of LEDs that were on before */
	__uint32_t  lm_newled; /* [OUT] Mask of LEDs that are on now */
};
struct kbd_string {
	/*utf-8*/ char const *ks_text; /* [0..ks_size] input text */
	__size_t              ks_size; /* Length (in bytes) of the input text */
};

__DECL_END
#endif /* __CC__ */

/* Keyboard device I/O functions. */
#define KBD_IOC_TRYGETKEY     _IOR_KOS('K', 0x00, struct kbd_packet)  /* Try to read a key stroke (returns `-EAGAIN' if no key was available, but doesn't throw an exception) */
#define KBD_IOC_GETKEY        _IOR_KOS('K', 0x01, struct kbd_packet)  /* Read a key stroke (cancellation point) */
#define KBD_IOC_GETLED        _IOR_KOS('K', 0x02, __uint32_t)         /* Get the set of currently lit indicator LEDs (set of `KEYBOARD_LED_*') */
#define KBD_IOC_SETLED        _IOW_KOS('K', 0x02, __uint32_t)         /* Set the set of currently lit indicator LEDs (set of `KEYBOARD_LED_*') */
#define KBD_IOC_MASKLED       _IOR_KOS('K', 0x02, struct kbd_ledmask) /* Mask lit indicator LEDs (new_leds = lm_newled = (((lm_oldled = old_leds) & lm_mask) | lm_flag) ^ lm_fxor); */
#define KBD_IOC_GETKEYMAP     _IOR_KOS('K', 0x03, struct kbd_keymap)  /* Get the key map program of this keyboard.
                                                                       * @param: km_maptext: [IN|OUT] Provided buffer for program data.
                                                                       * @param: km_mapsize: [IN] Available buffer size
                                                                       *                     [OUT] Required buffer size. */
#define KBD_IOC_SETKEYMAP     _IOW_KOS('K', 0x03, struct kbd_keymap)  /* Set the key map program of this keyboard. */
#define KBD_IOC_RESETKEYMAP    _IO_KOS('K', 0x03)                     /* Reset the keymap to en_US. */
#define KBD_IOC_FLUSHPENDING   _IO_KOS('K', 0x04)                     /* Clear the buffer of pending keys */
#define KBD_IOC_PUTCHAR       _IOW_KOS('K', 0x05, /*utf-8*/ char)     /* Schedule a character acting as though it was part of the result of translating a multi-byte key stroke.
                                                                       * Note that unlike `KBD_IOC_PUTKEY', scheduled characters can only be read with `KBD_IOC_SETRDKEY=1', or through use of `KBD_IOC_(TRY)GETCHAR'
                                                                       * Also note that the internal buffer for these character is fixed-length and fairly small.
                                                                       * @return: 0: Failed to schedule the character
                                                                       * @return: 1: Successfully scheduled the character */
#define KBD_IOC_PUTSTR        _IOW_KOS('K', 0x05, struct kbd_string)  /* Same as `KBD_IOC_PUTCHAR', but schedule multiple characters.
                                                                       * @return: 0: Nothing could be scheduled; The buffer is full.
                                                                       * @return: *: The number of bytes from `ks_text' that were scheduled before the buffer became full
                                                                       * @return: ks_size: Successfully scheduled everything. */
#define KBD_IOC_PUTKEY        _IOW_KOS('K', 0x06, __uint16_t)         /* Schedule a key stroke, behaving identical to the user performing that same input (including turning LEDs on/off for locking keys)
                                                                       * @return: == 0: Failed to schedule the key stroke (the keyboard input buffer is full)
                                                                       * @return: >  0: Successfully to scheduled the key stroke */
#define KBD_IOC_GETDBGF12     _IOR_KOS('K', 0x07, int)                /* Get dbgF12-mode (0: disabled; 1: Pressing F12 4 times in a row will enter debug-mode) */
#define KBD_IOC_SETDBGF12     _IOW_KOS('K', 0x07, int)                /* Set dbgF12-mode (0: disabled; 1: Pressing F12 4 times in a row will enter debug-mode) */
#define KBD_IOC_GETMOD        _IOR_KOS('K', 0x08, __uint32_t)         /* Get the set of currently active modifier keys (set of `KEYMOD_*') */
#define KBD_IOC_SETMOD        _IOW_KOS('K', 0x08, __uint32_t)         /* Set the set of currently active modifier keys (set of `KEYMOD_*') */
#define KBD_IOC_MASKMOD       _IOR_KOS('K', 0x08, struct kbd_ledmask) /* Mask active modifier keys (new_mod = lm_newled = (((lm_oldled = old_mod) & lm_mask) | lm_flag) ^ lm_fxor); */

#endif /* !_KOS_IOCTL_KBD_H */
