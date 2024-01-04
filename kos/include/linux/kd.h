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
/* (#) Portability: Linux     (/usr/include/linux/kd.h) */
/* (#) Portability: diet libc (/include/linux/kd.h) */
#ifndef _LINUX_KD_H
#define _LINUX_KD_H 1

/* DISCLAIMER: _STRONGLY_ Based on '/usr/include/linux/kd.h' */
/* TODO: Support this stuff within the kernel */

#include <__stdinc.h>
#include <bits/types.h>
#include <asm/ioctl.h>

/* 0x4b is 'K', to avoid collision with termios and vt */

#define GIO_FONT  _IO('K', 0x60) /* gets font in expanded form */
#define PIO_FONT  _IO('K', 0x61) /* use font in expanded form */
#define GIO_FONTX _IO('K', 0x6b) /* get font using struct consolefontdesc */
#define PIO_FONTX _IO('K', 0x6c) /* set font using struct consolefontdesc */
#ifdef __CC__
struct consolefontdesc {
	__uint16_t charcount;  /* characters in font (256 or 512) */
	__uint16_t charheight; /* scan lines per character (1-32) */
	char      *chardata;   /* font data in expanded form */
};
#endif /* __CC__ */

#define PIO_FONTRESET _IO('K', 0x6d) /* reset to default font */
#define GIO_CMAP      _IO('K', 0x70) /* gets colour palette on VGA+ */
#define PIO_CMAP      _IO('K', 0x71) /* sets colour palette on VGA+ */
#define KIOCSOUND     _IO('K', 0x2f) /* start sound generation (0 for off) */
#define KDMKTONE      _IO('K', 0x30) /* generate tone */

#define KDGETLED _IO('K', 0x31) /* return current led state */
#define KDSETLED _IO('K', 0x32) /* set led state [lights, not flags] */
#define    LED_SCR 0x01 /* scroll lock led */
#define    LED_NUM 0x02 /* num lock led */
#define    LED_CAP 0x04 /* caps lock led */

#define KDGKBTYPE _IO('K', 0x33) /* get keyboard type */
#define    KB_84    0x01
#define    KB_101   0x02 /* this is what we always answer */
#define    KB_OTHER 0x03

#define KDADDIO   _IO('K', 0x34) /* add i/o port as valid */
#define KDDELIO   _IO('K', 0x35) /* del i/o port as valid */
#define KDENABIO  _IO('K', 0x36) /* enable i/o to video board */
#define KDDISABIO _IO('K', 0x37) /* disable i/o to video board */

#define KDSETMODE         _IO('K', 0x3a) /* set text/graphics mode */
#define    KD_TEXT        0x00
#define    KD_GRAPHICS    0x01
#define    KD_TEXT0       0x02 /* obsolete */
#define    KD_TEXT1       0x03 /* obsolete */
#define    KD_TRANSPARENT 0x04

#define KDGETMODE   _IO('K', 0x3b) /* get current mode */
#define KDMAPDISP   _IO('K', 0x3c) /* map display into address space */
#define KDUNMAPDISP _IO('K', 0x3d) /* unmap display from address space */

#ifdef __CC__
typedef char scrnmap_t;
#endif /* __CC__ */
#define E_TABSZ 256
#define GIO_SCRNMAP    _IO('K', 0x40) /* get screen mapping from kernel */
#define PIO_SCRNMAP    _IO('K', 0x41) /* put screen mapping table in kernel */
#define GIO_UNISCRNMAP _IO('K', 0x69) /* get full Unicode screen mapping */
#define PIO_UNISCRNMAP _IO('K', 0x6a) /* set full Unicode screen mapping */

#define GIO_UNIMAP _IO('K', 0x66) /* get unicode-to-font mapping from kernel */
#ifdef __CC__
struct unipair {
	__uint16_t unicode;
	__uint16_t fontpos;
};
struct unimapdesc {
	__uint16_t      entry_ct;
	struct unipair *entries;
};
#endif /* __CC__ */

#define PIO_UNIMAP    _IO('K', 0x67) /* put unicode-to-font mapping in kernel */
#define PIO_UNIMAPCLR _IO('K', 0x68) /* clear table, possibly advise hash algorithm */
#ifdef __CC__
struct unimapinit {
	__uint16_t advised_hashsize;  /* 0 if no opinion */
	__uint16_t advised_hashstep;  /* 0 if no opinion */
	__uint16_t advised_hashlevel; /* 0 if no opinion */
};
#endif /* __CC__ */

#define UNI_DIRECT_BASE 0xF000 /* start of Direct Font Region */
#define UNI_DIRECT_MASK 0x01FF /* Direct Font Region bitmask */

/* Keyboard modes (configure what is read(2) from a keyboard):
 *
 *  - K_RAW:       Produce raw AT-style scancodes (same as a PS/2 keyboard with scanset #1)
 *                 s.a. `ps2_keyboard_ss1' and `ps2_keyboard_ss1_e0' from
 *                      `/kos/src/kernel/modps2/keyboard-scansets.c'
 *
 *  - K_XLATE:     The *normal* (but  deprecated) mode,  where actual text  is read  from
 *                 the  keyboard.  Characters encoded  via  `keymap_translate_buf()' must
 *                 fall into the ascii range. If they don't, they are silently discarded.
 *
 *  - K_MEDIUMRAW: Produce keycodes (as found in <kos/keyboard.h>) that are encoded as:
 *                 >> if (keycode < 128) {
 *                 >>     putchar(keycode | (down ? 0 : 0x80));
 *                 >> } else {
 *                 >>     putchar(down ? 0 : 0x80);
 *                 >>     putchar((keycode >> 7) | 0x80);
 *                 >>     putchar((keycode & 0x7f) | 0x80);
 *                 >> }
 *
 *  - K_UNICODE:   The actual default mode. Behaves the same as `K_XLATE', except that
 *                 characters  from  outside the  ascii  range are  encoded  as utf-8.
 *
 *  - K_OFF:       Keyboard input isn't being generated. (But internal control sequences,
 *                 including   the   4xF12=dbg()    behavior   continue   to    function)
 */
#define KDGKBMODE _IO('K', 0x44) /* gets current keyboard mode */
#define KDSKBMODE _IO('K', 0x45) /* sets current keyboard mode */
#define    K_RAW       0x00
#define    K_XLATE     0x01
#define    K_MEDIUMRAW 0x02
#define    K_UNICODE   0x03
#define    K_OFF       0x04


#define KDGKBMETA _IO('K', 0x62) /* gets meta key handling mode */
#define KDSKBMETA _IO('K', 0x63) /* sets meta key handling mode */
#define    K_METABIT   0x03
#define    K_ESCPREFIX 0x04

#define KDGKBLED _IO('K', 0x64) /* get led flags (not lights) */
#define KDSKBLED _IO('K', 0x65) /* set led flags (not lights) */
#define    K_SCROLLLOCK 0x01
#define    K_NUMLOCK    0x02
#define    K_CAPSLOCK   0x04

#ifdef __CC__
struct kbentry {
	__UINT8_TYPE__  kb_table;
	__UINT8_TYPE__  kb_index;
	__UINT16_TYPE__ kb_value;
};
#endif /* __CC__ */

#define KDGKBENT _IO('K', 0x46) /* gets one entry in translation table */
#define KDSKBENT _IO('K', 0x47) /* sets one entry in translation table */
#define    K_NORMTAB     0x00
#define    K_SHIFTTAB    0x01
#define    K_ALTTAB      0x02
#define    K_ALTSHIFTTAB 0x03

#ifdef __CC__
struct kbsentry {
	unsigned char kb_func;
	unsigned char kb_string[512];
};
#endif /* __CC__ */
#define KDGKBSENT _IO('K', 0x48) /* gets one function key string entry */
#define KDSKBSENT _IO('K', 0x49) /* sets one function key string entry */

#ifdef __CC__
struct kbdiacr {
	unsigned char diacr;
	unsigned char base;
	unsigned char result;
};
struct kbdiacrs {
	__UINT32_TYPE__ kb_cnt;       /* number of entries in following array */
	struct kbdiacr  kbdiacr[256]; /* MAX_DIACR from keyboard.h */
};
#endif /* __CC__ */
#define KDGKBDIACR _IO('K', 0x4a) /* read kernel accent table */
#define KDSKBDIACR _IO('K', 0x4b) /* write kernel accent table */

#ifdef __CC__
struct kbdiacruc {
	__UINT32_TYPE__ diacr;
	__UINT32_TYPE__ base;
	__UINT32_TYPE__ result;
};
struct kbdiacrsuc {
	__UINT32_TYPE__  kb_cnt;         /* number of entries in following array */
	struct kbdiacruc kbdiacruc[256]; /* MAX_DIACR from keyboard.h */
};
#endif /* __CC__ */
#define KDGKBDIACRUC _IO('K', 0xfa) /* read kernel accent table - UCS */
#define KDSKBDIACRUC _IO('K', 0xfb) /* write kernel accent table - UCS */

#ifdef __CC__
struct kbkeycode {
	__UINT32_TYPE__ scancode;
	__UINT32_TYPE__ keycode;
};
#endif /* __CC__ */
#define KDGETKEYCODE _IO('K', 0x4c) /* read kernel keycode table entry */
#define KDSETKEYCODE _IO('K', 0x4d) /* write kernel keycode table entry */

#define KDSIGACCEPT _IO('K', 0x4e) /* accept kbd generated signals */

#ifdef __CC__
struct kbd_repeat {
	__INT32_TYPE__ delay;  /* in msec; <= 0: don't change */
	__INT32_TYPE__ period; /* in msec; <= 0: don't change
	                        * earlier this field was misnamed "rate" */
};
#endif /* __CC__ */

#define KDKBDREP _IO('K', 0x52) /* set keyboard delay/repeat rate; actually used values are returned */
#define KDFONTOP _IO('K', 0x72) /* font operations */

#ifdef __CC__
struct console_font_op {
	__UINT32_TYPE__ op;        /* operation code KD_FONT_OP_* */
	__UINT32_TYPE__ flags;     /* KD_FONT_FLAG_* */
	__UINT32_TYPE__ width;     /* font size */
	__UINT32_TYPE__ height;    /* font size */
	__UINT32_TYPE__ charcount; /* ... */
	unsigned char  *data;      /* font data with height fixed to 32 */
};
struct console_font {
	__UINT32_TYPE__ width;     /* font size */
	__UINT32_TYPE__ height;    /* font size */
	__UINT32_TYPE__ charcount; /* ... */
	unsigned char  *data;      /* font data with height fixed to 32 */
};
#endif /* __CC__ */

#define KD_FONT_OP_SET         0 /* Set font */
#define KD_FONT_OP_GET         1 /* Get font */
#define KD_FONT_OP_SET_DEFAULT 2 /* Set font to default, data points to name / NULL */
#define KD_FONT_OP_COPY        3 /* Copy from another console */

#define KD_FONT_FLAG_DONT_RECALC 1 /* Don't recalculate hw charcell size [compat] */

/* note: 0x4B00-0x4B4E all have had a value at some time;
   don't reuse for the time being */
/* note: 0x4B60-0x4B6D, 0x4B70-0x4B72 used above */


#endif /* !_LINUX_KD_H */
