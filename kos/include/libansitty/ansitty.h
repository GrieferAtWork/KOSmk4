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
#ifndef _LIBANSITTY_ANSITTY_H
#define _LIBANSITTY_ANSITTY_H 1

#include "api.h"
#include <hybrid/__byteorder.h>
#include <bits/types.h>

/* s.a.
 *  - https://en.wikipedia.org/wiki/ANSI_escape_code
 *  - http://ascii-table.com/documents/vt100/chapter3.php#S3.3.3
 *  - http://ascii-table.com/ansi-escape-sequences-vt-100.php
 *  - http://www.termsys.demon.co.uk/vtansi.htm
 *  - https://vt100.net/docs/vt100-ug/chapter3.html
 *  - https://vt100.net/docs/vt100-ug/table3-9.html
 *  - http://www.ecma-international.org/publications/files/ECMA-ST/Ecma-048.pdf
 *  - https://espterm.github.io/docs/VT100%20escape%20codes.html
 *  - https://www.climagic.org/mirrors/VT100_Escape_Codes.html
 *  - http://real-world-systems.com/docs/ANSIcode.html
 *  - http://man7.org/linux/man-pages/man1/screen.1.html
 */


#define ANSITTY_COLORS       16
#define ANSITTY_CL_BLACK     0
#define ANSITTY_CL_RED       1
#define ANSITTY_CL_GREEN     2
#define ANSITTY_CL_YELLOW    3
#define ANSITTY_CL_BLUE      4
#define ANSITTY_CL_MAGENTA   5
#define ANSITTY_CL_CYAN      6
#define ANSITTY_CL_WHITE     7
#define ANSITTY_IFSTRONG     0x8 /*< Intensify a given ANSI color. */
#define ANSITTY_ISSTRONG(x) ((x)&ANSITTY_IFSTRONG)
#define ANSITTY_TOSTRONG(x) ((x)|ANSITTY_IFSTRONG)

#define ANSITTY_PALETTE_INDEX(fg, bg)  (((bg) << 4)|(fg))
#define ANSITTY_PALETTE_INDEX_FG(idx)  ((idx) & 0xf)
#define ANSITTY_PALETTE_INDEX_BG(idx)  ((idx) >> 4)
#define ANSITTY_CL_DEFAULT     ANSITTY_PALETTE_INDEX(ANSITTY_CL_WHITE, ANSITTY_CL_BLACK)

/* Sequence that can be printed at any time to reset the ANSI driver to its default
 * state, where it accepts regular text input for immediate display, with all attributes
 * and special coloration disabled.
 * Explanation:
 *   - `\077\\' -- String terminator (ends any possible dangling model-mode)
 *   - `\077c'  -- Reset TTY (resets colors, display-attributes, tty-flags and tty-mode)
 */
#define ANSITTY_RESET_SEQUENCE  "\077\\\077c"


#define ANSITTY_CLS_AFTER    0 /* Clear everything after the cursor (including the cursor itself). */
#define ANSITTY_CLS_BEFORE   1 /* Clear everything before the cursor (excluding the cursor itself). */
#define ANSITTY_CLS_ALL      2 /* Clear everything. */
#define ANSITTY_CLS_ALLPAGES 3 /* Clear everything including the scroll-back buffers. */

#define ANSITTY_EL_AFTER  0 /* Erase the line after the cursor (including the cursor itself). */
#define ANSITTY_EL_BEFORE 1 /* Erase the line before the cursor (excluding the cursor itself). */
#define ANSITTY_EL_ALL    2 /* Erase the line. */


/* TTY mode flags */
#define ANSITTY_MODE_DEFAULT            0x0000 /* Default TTY mode */
#define ANSITTY_MODE_MOUSEON_NO         0x0000 /* Don't report mouse data */
#define ANSITTY_MODE_MOUSEON_YES        0x0001 /* Report mouse position */
#define ANSITTY_MODE_MOUSEON_WITHMOTION 0x0002 /* Report motion of pressed buttons. */
#define ANSITTY_MODE_MOUSEON_MASK       0x0003 /* Mask for the MOUSEON mode. */
#define ANSITTY_MODE_NOLINEWRAP         0x0004 /* FLAG: Writing past the end of a line will not wrap to the next line.
                                                *       When set, characters written past line-endings are discarded. */
#define ANSITTY_MODE_HIDECURSOR         0x0008 /* FLAG: Don't show the cursor. */
#define ANSITTY_MODE_NEWLINE_CLRFREE    0x0010 /* FLAG: CR and LF should fill trailing cells with space characters. */


/* Display flags (text attributes) */
#define ANSITTY_ATTRIB_DEFAULT   0x0000 /* Default attributes */
#define ANSITTY_ATTRIB_UNDERLINE 0x0001 /* FLAG: Print a line below the character */
#define ANSITTY_ATTRIB_OVERLINE  0x0002 /* FLAG: Print a line above the character */
#define ANSITTY_ATTRIB_ITALIC    0x0004 /* FLAG: Print the character in cursive */
#define ANSITTY_ATTRIB_BLINK     0x0008 /* FLAG: Cause text to blink (don't use this one; please...) */
#define ANSITTY_ATTRIB_CROSS     0x0010 /* FLAG: Cross-out written text. */
#define ANSITTY_ATTRIB_FRAMED    0x0020 /* FLAG: Surround text with a frame. */
#define ANSITTY_ATTRIB_CIRCLED   0x0040 /* FLAG: Surround text with a frame (with rounded corners).
                                         * NOTE: This flag always appears in conjunction with `ANSITTY_ATTRIB_FRAMED' */
#define ANSITTY_ATTRIB_LET_SWSH  0x0000 /* Letter mode: Single-Width, Single-Height */
#define ANSITTY_ATTRIB_LET_DWSH  0x0100 /* Letter mode: Double-Width, Single-Height */
#define ANSITTY_ATTRIB_LET_DHTP  0x0200 /* Letter mode: Single-Width, Double-Height (top-half) */
#define ANSITTY_ATTRIB_LET_DHBP  0x0300 /* Letter mode: Single-Width, Double-Height (bottom-half) */
#define ANSITTY_ATTRIB_LET_MASK  0x0300 /* Mask for letter mode. */
#define ANSITTY_ATTRIB_FONTMASK  0xf000 /* MASK: Alternate font selection */
#define ANSITTY_ATTRIB_FONTSHFT      24 /* SHFT: Alternate font selection */


#ifdef __CC__
__DECL_BEGIN

typedef __uint32_t ansitty_coord_t;
typedef __int32_t ansitty_offset_t;

struct ansitty;
struct termios;

struct ansitty_operators {
	/* [1..1] Output a single unicode character.
	 * This also includes the control control characters `BEL,LF,CR,TAB,BS'
	 * Note that LF should be interpreted as next-line + carriage-return */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_putc)(struct ansitty *__restrict self,
	                               __CHAR32_TYPE__ ch);
	/* [0..1] Set the current text color.
	 * Called whenever a different color is selected.
	 * @param: color: ==  */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_setcolor)(struct ansitty *__restrict self,
	                                   __uint8_t color);
	/* [0..1] Set the current text attributes.
	 * Called whenever a text attribute change.
	 * @param: new_attrib: == self->at_attrib */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_setattrib)(struct ansitty *__restrict self,
	                                    __uint16_t new_attrib);
	/* [0..1] Set the current tty mode.
	 * Called whenever the tty mode changes.
	 * @param: new_ttymode: == self->at_ttymode */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_setttymode)(struct ansitty *__restrict self,
	                                     __uint16_t new_ttymode);
	/* [0..1] Set the position of the cursor.
	 * NOTE: The given `x' and `y' must be clamped to COLUMNS-1/ROWS-1, meaning
	 *       that `(*ato_setcursor)(tty, (ansitty_coord_t)-1, (ansitty_coord_t)-1)'
	 *       places the cursor at its greatest possible position in both X and Y. */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_setcursor)(struct ansitty *__restrict self,
	                                    ansitty_coord_t x, ansitty_coord_t y);
	/* [0..1] Returns the position of the cursor.
	 * @param: ppos[0]: Store X-position here.
	 * @param: ppos[1]: Store Y-position here. */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_getcursor)(struct ansitty *__restrict self,
	                                    ansitty_coord_t ppos[2]);
	/* [0..1] Clear text from the screen.
	 * @param: mode: One of `ANSITTY_CLS_*' */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_cls)(struct ansitty *__restrict self, unsigned int mode);
	/* [0..1] Clear text from the current line.
	 * @param: mode: One of `ANSITTY_EL_*' */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_el)(struct ansitty *__restrict self, unsigned int mode);
	/* [0..1] Shift terminal lines by offset, where a negative value shifts
	 *        lines downwards/left, and a positive value shifts them up/right.
	 * E.g.: When the end of the terminal is reached, the driver may
	 *       implement this as `(*to_scroll)(...,1);' */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_scroll)(struct ansitty *__restrict self,
	                                 ansitty_offset_t hoffset,
	                                 ansitty_offset_t voffset);
	/* [0..1] Set the window title of the terminal. */
	__ATTR_NONNULL((1, 2))
	void (LIBANSITTY_CC *ato_settitle)(struct ansitty *__restrict self,
	                                   /*utf-8*/char const *__restrict text);
	/* [0..1] Output `text' to the slave process (`write(amaster, text, textlen)'; amaster from <pty.h>:openpty) */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_output)(struct ansitty *__restrict self,
	                                 void const *data, __size_t datalen);
	/* [0..1] Set the scroll region */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_scrollregion)(struct ansitty *__restrict self,
	                                       ansitty_coord_t start_line,
	                                       ansitty_coord_t start_column,
	                                       ansitty_coord_t end_line,
	                                       ansitty_coord_t end_column);
	/* [0..1] Turn LEDs on/off, such that NEW_LEDS = (OLD_LEDS & mask) | flag.
	 * For this purpose, both mask and flag are bitsets of LEDs enumerated
	 * from 0 to 3 (yes: that's 4 leds, and I don't know what that 4'th led
	 * is all about...)
	 * However, linux defines them like this:
	 *   0x01: KEYBOARD_LED_SCROLLLOCK
	 *   0x02: KEYBOARD_LED_NUMLOCK
	 *   0x04: KEYBOARD_LED_CAPSLOCK
	 *   0x08: Undefined (ignore if it wouldn't have any meaning) */
	__ATTR_NONNULL((1))
	void (LIBANSITTY_CC *ato_setled)(struct ansitty *__restrict self,
	                                 __uint8_t mask, __uint8_t flag);
	/* [0..1] Try to get/set the terminal IOS descriptor of the associated terminal.
	 * This function can be used in 2 different modes:
	 *  - newios == NULL:
	 *      Copy the current IOS state into `oldios'.
	 *      The return value for this case doesn't matter and is ignored.
	 *  - newios != NULL:
	 *      Compare the current IOS state with `oldios'
	 *      If they differ, leave `oldios' undefined, and return `false'
	 *      If they match, set `newios' as the new IOS state and return `true'
	 */
	__ATTR_NONNULL((1, 2))
	__BOOL (LIBANSITTY_CC *ato_termios)(struct ansitty *__restrict self,
	                                    struct termios *__restrict oldios,
	                                    struct termios const *newios);
};

struct ansitty {
	struct ansitty_operators  at_ops;         /* [const] ANSI TTY operators. */
	__uint8_t                 at_color;       /* Selected color index (0xf0: bg; 0x0f: fg). */
	__uint8_t                 at_defcolor;    /* Default color index (usually `ANSITTY_CL_DEFAULT').
	                                           * This index is used when `\ec' is encountered */
	__uint16_t                at_ttyflag;     /* Internal TTY mode flags. */
	__uint16_t                at_ttymode;     /* TTY mode (Set of `ANSITTY_MODE_*') */
	__uint16_t                at_attrib;      /* Text mode attributes (set of `ANSITTY_ATTRIB_*'). */
	ansitty_coord_t           at_savecur[2];  /* Saved cursor position */
	ansitty_coord_t           at_scroll_sl;   /* Scroll region starting line */
	ansitty_coord_t           at_scroll_sc;   /* Scroll region starting column */
	ansitty_coord_t           at_scroll_el;   /* Scroll region end line */
	ansitty_coord_t           at_scroll_ec;   /* Scroll region end column */
	__uintptr_t               at_state;       /* Current state-machine state. (not exposed) */
	union {
		__UINTPTR_TYPE__      at_esclen;      /* Number of written, escaped bytes. */
		__UINTPTR_HALF_TYPE__ at_escwrd[2];   /* Double-word status (used by some values for `at_state') */
	};
	__byte_t                  at_escape[256]; /* Escape text buffer (also used for unicode translation). */
	__byte_t                  at_zero;        /* [const] Always ZERO. */
};


/* Initialize the given ANSI TTY */
typedef __ATTR_NONNULL((1, 2)) void
(LIBANSITTY_CC *PANSITTY_INIT)(struct ansitty *__restrict self,
                               struct ansitty_operators const *__restrict ops);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __ATTR_NONNULL((1, 2)) void LIBANSITTY_CC
ansitty_init(struct ansitty *__restrict self,
             struct ansitty_operators const *__restrict ops);
#endif /* LIBANSITTY_WANT_PROTOTYPES */

/* Output a single utf-8 character to the given TTY */
typedef __ATTR_NONNULL((1)) void
(LIBANSITTY_CC *PANSITTY_PUTC)(struct ansitty *__restrict self, /*utf-8*/char ch);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __ATTR_NONNULL((1)) void LIBANSITTY_CC
ansitty_putc(struct ansitty *__restrict self, /*utf-8*/char ch);
#endif /* LIBANSITTY_WANT_PROTOTYPES */

/* Output a single unicode character to the given TTY */
typedef __ATTR_NONNULL((1)) void
(LIBANSITTY_CC *PANSITTY_PUTUNI)(struct ansitty *__restrict self, __CHAR32_TYPE__ ch);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __ATTR_NONNULL((1)) void LIBANSITTY_CC
ansitty_putuni(struct ansitty *__restrict self, __CHAR32_TYPE__ ch);
#endif /* LIBANSITTY_WANT_PROTOTYPES */

/* pformatprinter-compatible prototype for printing to an ANSI TTY
 * @param: arg: The `struct ansitty *' to which to print.
 * @return: * : Always re-return `(ssize_t)datalen' */
typedef __ATTR_NONNULL((1)) __ssize_t
(__LIBCCALL *PANSITTY_PRINTER)(void *arg, char const *data, __size_t datalen);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __ATTR_NONNULL((1)) __ssize_t __LIBCCALL
ansitty_printer(void *arg, char const *data, __size_t datalen);
#endif /* LIBANSITTY_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBANSITTY_ANSITTY_H */
