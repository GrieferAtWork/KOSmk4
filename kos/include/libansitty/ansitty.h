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
#ifndef _LIBANSITTY_ANSITTY_H
#define _LIBANSITTY_ANSITTY_H 1

#include "api.h"

#include <hybrid/byteorder.h>

#include <bits/crt/format-printer.h>
#include <bits/types.h>
#include <kos/anno.h>

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
 *  - https://real-world-systems.com/docs/ANSIcode.html
 *  - http://man7.org/linux/man-pages/man1/screen.1.html
 *  - https://vt100.net/docs/vt102-ug/chapter5.html
 *  - https://invisible-island.net/xterm/ctlseqs/ctlseqs.html
 */

/* CR (\r) and LF (\n) behavior throughout the keyboard->termios->ansitty->display chain of sub-systems:
 * keyboard:
 *   - The keyboard always sends \r
 *   - There doesn't seem to be a way to change this besides using custom key maps.
 *     This behavior can also be observed on linux by analyzing keyboard data  sent
 *     after putting a terminal into cfmakeraw()-mode
 * termios:
 *   - '\r' (from keyboard):
 *     - IGNCR: Ignore '\r' characters  (Cleared by ansitty:"\ec", "\e[20h" and "\e[20l")
 *     - ICRNL: Convert into '\n'       (Default; Set by ansitty:"\ec" and "\e[20h")
 *     - 0:     Forward '\r' characters unchanged (s.a. `cfmakeraw()')
 *   - '\n' (from keyboard):
 *     - INLCR: Convert into '\r'  (Cleared by ansitty:"\ec" and "\e[20l"; Set by ansitty:"\e[20h")
 *       - I  don't really know why this flag exists, since it seems like it would imply
 *         there may be some keyboard/tty combinations where the return-key sends a '\n'
 *         character, however even despite this,  using CTRL+J will always trigger  this
 *         flag, since that key combination will also send a '\n' character
 *       - Note that it was this flag which always confused me into thinking that '\n'
 *         may  be what a keyboard should send, but this causes problems with at least
 *         a hand full of programs:
 *          - The <Enter-File-Name> dialog of `nano' doesn't accept '\n' as confirmation
 *            input  and instead responds with a BELL,  indicating that the input is not
 *            accepted.
 *          - However other programs (like the `busybox' commandline) will work just fine
 *            regardless of the keyboard sending '\r' or '\n' (although it may also  just
 *            be using either `INLCR' or `ICRNL' to unify input for either behavior)
 *   - '\r' (from application / for ansitty):
 *     - ONLRET:      Ignore '\r' characters
 *     - ONOCR:       Ignore '\r' characters at column 0 (ignored on KOS)
 *     - OCRNL:       Convert into '\n'
 *     - OCRNL|ONLCR: Convert into '\r\n'
 *   - '\n' (from application / for ansitty):
 *     - ONLCR:       Convert into '\r\n'
 * ansitty:
 *   - '\r' (from termios / for display):
 *     - Always forwarded as unchanged
 *   - '\n' (from termios / for display):
 *     - Always forwarded as unchanged
 * display:
 *   - '\r' (from ansitty):
 *     >> SET_COLUMN(0);
 *   - '\n' (from ansitty):
 *     >> if (AT_END_OF_SCROLL_REGION()) {
 *     >>     SCROLL();
 *     >>     SET_ROW(DISPLAY_HEIGHT - 1);
 *     >> } else {
 *     >>     SET_ROW(GET_ROW() + 1);
 *     >> }
 *     >> SET_COLUMN(GET_COLUMN()); // Keep the old column index
 */


#define ANSITTY_COLORS       16
#ifndef ANSITTY_CL_BLACK
#define ANSITTY_CL_BLACK     0x0 /* RGB(0x00, 0x00, 0x00) */
#define ANSITTY_CL_MAROON    0x1 /* RGB(0xaa, 0x00, 0x00) */
#define ANSITTY_CL_GREEN     0x2 /* RGB(0x00, 0xaa, 0x00) */
#define ANSITTY_CL_OLIVE     0x3 /* RGB(0xaa, 0x55, 0x00) */
#define ANSITTY_CL_NAVY      0x4 /* RGB(0x00, 0x00, 0xaa) */
#define ANSITTY_CL_PURPLE    0x5 /* RGB(0xaa, 0x00, 0xaa) */
#define ANSITTY_CL_TEAL      0x6 /* RGB(0x00, 0xaa, 0xaa) */
#define ANSITTY_CL_SILVER    0x7 /* RGB(0xaa, 0xaa, 0xaa) */
#define ANSITTY_CL_GREY      0x8 /* RGB(0x55, 0x55, 0x55) */
#define ANSITTY_CL_RED       0x9 /* RGB(0xff, 0x55, 0x55) */
#define ANSITTY_CL_LIME      0xa /* RGB(0x55, 0xff, 0x55) */
#define ANSITTY_CL_YELLOW    0xb /* RGB(0xff, 0xff, 0x55) */
#define ANSITTY_CL_BLUE      0xc /* RGB(0x55, 0x55, 0xff) */
#define ANSITTY_CL_FUCHSIA   0xd /* RGB(0xff, 0x55, 0xff) */
#define ANSITTY_CL_AQUA      0xe /* RGB(0x55, 0xff, 0xff) */
#define ANSITTY_CL_WHITE     0xf /* RGB(0xff, 0xff, 0xff) */
#endif /* !ANSITTY_CL_BLACK */

#define ANSITTY_IFSTRONG     0x8 /* Intensify a given ANSI color. */
#define ANSITTY_ISSTRONG(x) ((x) & ANSITTY_IFSTRONG)
#define ANSITTY_TOSTRONG(x) ((x) | ANSITTY_IFSTRONG)

/* Color name aliases */
#ifndef ANSITTY_CL_LIGHT_GRAY
#define ANSITTY_CL_LIGHT_GRAY   ANSITTY_CL_SILVER
#define ANSITTY_CL_DARK_GRAY    ANSITTY_CL_GREY
#define ANSITTY_CL_MAGENTA      ANSITTY_CL_PURPLE
#define ANSITTY_CL_CYAN         ANSITTY_CL_TEAL
#define ANSITTY_CL_LIGHT_GREEN  ANSITTY_CL_LIME
#define ANSITTY_CL_BRIGHT_GREEN ANSITTY_CL_LIME
#define ANSITTY_CL_DARK_BLUE    ANSITTY_CL_NAVY
#endif /* !ANSITTY_CL_LIGHT_GRAY */

#define ANSITTY_PALETTE_INDEX(fg, bg) (((bg) << 4) | (fg))
#define ANSITTY_PALETTE_INDEX_FG(idx) ((idx) & 0xf)
#define ANSITTY_PALETTE_INDEX_BG(idx) ((idx) >> 4)
#define ANSITTY_CL_DEFAULT \
	ANSITTY_PALETTE_INDEX(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_BLACK)

/* Sequence that can  be printed at  any time to  reset the ANSI  driver to its  default
 * state, where it accepts regular text input for immediate display, with all attributes
 * and special coloration disabled.
 * Explanation:
 *   - `\030'  -- AC_CAN: Cancel (forces the state machine to abort any in-progress sequence and
 *                                reset itself to accept text or the start of an escape sequence)
 *   - `\033c' -- AC_RIS: Reset  TTY (resets colors, display-attributes, tty-flags and tty-mode)
 *                        However, this will not clear the screen, or reset the cursor  position
 *                        (though it will make the cursor visible). If wanted, the cursor can be
 *                        reset with `AC_CUP0', and the screen be cleared with `AC_ED("")'
 */
#define ANSITTY_RESET_SEQUENCE "\030\033c" /* == AC_CAN AC_RIS */


/* Values for `struct ansitty_operators::ato_cls::mode' */
#define ANSITTY_CLS_AFTER    0 /* Clear everything after the cursor (including the cursor itself). */
#define ANSITTY_CLS_BEFORE   1 /* Clear everything before the cursor (excluding the cursor itself). */
#define ANSITTY_CLS_ALL      2 /* Clear everything. */
#define ANSITTY_CLS_ALLPAGES 3 /* Clear everything including the scroll-back buffers. */


/* Values for `struct ansitty_operators::ato_el::mode' */
#define ANSITTY_EL_AFTER  0 /* Erase the line after the cursor (including the cursor itself). */
#define ANSITTY_EL_BEFORE 1 /* Erase the line before the cursor (excluding the cursor itself). */
#define ANSITTY_EL_ALL    2 /* Erase the line. */


/* TTY mode flags (for `struct ansitty::at_ttymode') */
#define ANSITTY_MODE_DEFAULT            0x0000 /* Default TTY mode */
#define ANSITTY_MODE_MOUSEON_NO         0x0000 /* Don't report mouse data */
#define ANSITTY_MODE_MOUSEON_YES        0x0001 /* Report mouse position */
#define ANSITTY_MODE_MOUSEON_WITHMOTION 0x0002 /* Report motion of pressed buttons. */
#define ANSITTY_MODE_MOUSEON_MASK       0x0003 /* Mask for the MOUSEON mode. */
#define ANSITTY_MODE_NOLINEWRAP         0x0004 /* FLAG: Writing past the end of a line will not wrap to the next line.
                                                *       When  set, characters written past line-endings are discarded. */
#define ANSITTY_MODE_HIDECURSOR         0x0008 /* FLAG: Don't show the cursor. */
#define ANSITTY_MODE_NEWLINE_CLRFREE    0x0010 /* FLAG: CR and LF should fill trailing cells with space characters. */


/* Display flags (text attributes) (for `struct ansitty::at_attrib') */
#define ANSITTY_ATTRIB_DEFAULT       0x0000 /* Default attributes */
#define ANSITTY_ATTRIB_UNDERLINE     0x0001 /* FLAG: Print a line below the character */
#define ANSITTY_ATTRIB_OVERLINE      0x0002 /* FLAG: Print a line above the character */
#define ANSITTY_ATTRIB_ITALIC        0x0004 /* FLAG: Print the character in cursive */
#define ANSITTY_ATTRIB_BLINK         0x0008 /* FLAG: Cause text to blink (don't use this one; please...) */
#define ANSITTY_ATTRIB_STRIKETHROUGH 0x0010 /* FLAG: Strike-through text. */
#define ANSITTY_ATTRIB_FRAMED        0x0020 /* FLAG: Surround text with a frame. */
#define ANSITTY_ATTRIB_CIRCLED       0x0040 /* FLAG: Surround text with a frame (with rounded corners).
                                             * NOTE: This flag always appears in conjunction with `ANSITTY_ATTRIB_FRAMED' */
#define ANSITTY_ATTRIB_LET_SWSH      0x0000 /* Letter mode: Single-Width, Single-Height */
#define ANSITTY_ATTRIB_LET_DWSH      0x0100 /* Letter mode: Double-Width, Single-Height */
#define ANSITTY_ATTRIB_LET_DHTP      0x0200 /* Letter mode: Single-Width, Double-Height (top-half) */
#define ANSITTY_ATTRIB_LET_DHBP      0x0300 /* Letter mode: Single-Width, Double-Height (bottom-half) */
#define ANSITTY_ATTRIB_LET_MASK      0x0300 /* Mask for letter mode. */
#define ANSITTY_ATTRIB_FONTMASK      0xf000 /* MASK: Alternate font selection */
#define ANSITTY_ATTRIB_FONTSHFT          12 /* SHFT: Alternate font selection */


#ifdef __CC__
__DECL_BEGIN

typedef __uint32_t ansitty_coord_t;
typedef __int32_t ansitty_offset_t;

struct ansitty;
struct termios;

struct ansitty_operators {
	/* [1..1] Output a single unicode character.
	 * This  also includes the control control characters `BEL,LF,CR,TAB,BS'
	 * Note that LF should be interpreted as next-line w/o  carriage-return,
	 * as  the LF=CRLF  behavior should  be implemented  using `ONLCR'. Note
	 * however  that  LF  not resetting  the  carriage is  not  mandatory in
	 * controlled situations. libansitty won't care as to what is the actual
	 * behavior, however  some user-space  programs using  the terminal  may
	 * depend  on  LF not  resetting the  carriage when  the terminal  is in
	 * `cfmakeraw()' mode (such as busybox:hexedit)
	 *
	 * In practice, this means:
	 *  - Ansitty drivers should implement LF as not resetting CURSOR.X,
	 *    and so should any other  component that feeds input through  a
	 *    configurable `libtermios' layer.
	 *  - However, the kernel's builtin debugger implements LF as implying
	 *    CURSOR.X=0, mainly since this is  the expected behavior in  most
	 *    cases, and also because `dbg_printf()' doesn't feed through  the
	 *    libtermios layer that would normally translate LF->CRLF.
	 */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_putc)(struct ansitty *__restrict self,
	                          __CHAR32_TYPE__ ch);

	/* [0..1] Set the position of the cursor.
	 * NOTE: The given `x'  and `y'  must be clamped  to COLUMNS-1/ROWS-1,  meaning
	 *       that `(*ato_setcursor)(tty, (ansitty_coord_t)-1, (ansitty_coord_t)-1)'
	 *       places  the cursor at its greatest possible  position in both X and Y.
	 * @param: update_hw_cursor: When true,  also update  the hardware  cursor.
	 *                           Otherwise, the position of the hardware cursor
	 *                           should be left unchanged. */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_setcursor)(struct ansitty *__restrict self,
	                               ansitty_coord_t x, ansitty_coord_t y,
	                               __BOOL update_hw_cursor);

	/* [0..1] Returns the position of the cursor.
	 * @param: ppos[0]: Store X-position here.
	 * @param: ppos[1]: Store Y-position here. */
	__ATTR_NONNULL((1, 2)) void
	(LIBANSITTY_CC *ato_getcursor)(struct ansitty *__restrict self,
	                               ansitty_coord_t ppos[2]);

	/* [0..1] Returns the size of the terminal.
	 * NOTE: When implementing this function, you are _required_ never to fill
	 *       in  either psize[0] or psize[1] with ZERO(0). Doing so will cause
	 *       undefined behavior (such  as `DIVIDE_BY_ZERO')  errors in  places
	 *       where it may be impossible to handle them.
	 * @param: psize[0]: Number of cells in X (width/columns).
	 * @param: psize[1]: Number of cells in Y (height/rows). */
	__ATTR_NONNULL((1, 2)) void
	(LIBANSITTY_CC *ato_getsize)(struct ansitty *__restrict self,
	                             ansitty_coord_t psize[2]);

	/* [0..1] Copy the contents of cells starting at CURSOR into cells at
	 *        CURSOR+dst_offset (added together  such that values  beyond
	 *        the left/right border of the screen will wrap around to the
	 *        end/start of the prev/next line).
	 *        The  number of  cells to-be  copied is  given by `count'
	 *        When `count' would overflow past the end of the display,
	 *        it must be clamped before being used. */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_copycell)(struct ansitty *__restrict self,
	                              ansitty_offset_t dst_offset,
	                              ansitty_coord_t count);

	/* [0..1] Print the given character `ch' (which is always a graphical
	 *        character, rather than a control character) up to `count'
	 *        times, without ever scrolling, and stopping if the end of
	 *        the display is reached.
	 *        The actual cursor position remains unchanged. */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_fillcell)(struct ansitty *__restrict self,
	                              __CHAR32_TYPE__ ch,
	                              ansitty_coord_t count);

	/* [0..1] Shift terminal lines by offset, where a positive value shifts
	 *        lines up (like a \n at the bottom of the screen would), and a
	 *        negative value shifts them downwards.
	 *        New cells exposed by this operation should be filled with space
	 *        characters.
	 * E.g.: When the end of the terminal is reached, the driver may
	 *       implement this as `(*to_scroll)(..., 1);' */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_scroll)(struct ansitty *__restrict self,
	                            ansitty_offset_t offset);

	/* [0..1] Clear text from the screen.
	 * @param: mode: One of `ANSITTY_CLS_*' */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_cls)(struct ansitty *__restrict self,
	                         unsigned int mode);

	/* [0..1] Clear text from the current line.
	 * @param: mode: One of `ANSITTY_EL_*' */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_el)(struct ansitty *__restrict self,
	                        unsigned int mode);

	/* [0..1] Set the current text color.
	 * Called whenever a different color is selected; iow: one of ... changed:
	 *  - self->at_color
	 *  - self->at_tcolorfg
	 *  - self->at_tcolorbg
	 * NOTE: If the driver has support for more than the standard 16 ANSI colors,
	 *       this can be exposed by using `self->at_tcolor{fg|bg}' instead of the
	 *       the normal `self->at_color'. */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_setcolor)(struct ansitty *__restrict self);

	/* [0..1] Set the current text attributes.
	 * Called whenever text attributes change; iow: `self->at_attrib' changed. */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_setattrib)(struct ansitty *__restrict self);

	/* [0..1] Set the current tty mode.
	 * Called whenever the tty mode changes; iow: `self->at_ttymode' changed. */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_setttymode)(struct ansitty *__restrict self);

	/* [0..1] Set the scroll region (s.a. `ato_scroll()')
	 * Called whenever the scroll region changes; iow: one of ... changed:
	 * - self->at_scroll_sl
	 * - self->at_scroll_el */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_scrollregion)(struct ansitty *__restrict self);

	/* [0..1] Set the window title of the terminal. */
	__ATTR_NONNULL((1, 2)) void
	(LIBANSITTY_CC *ato_settitle)(struct ansitty *__restrict self,
	                              /*utf-8*/ char const *__restrict text);

	/* [0..1] Output `data' to the slave process (`write(amaster, data, datalen)';
	 *        amaster from <pty.h>:openpty, or alternatively identical to keyboard
	 *        input).
	 *        Certain control  sequences produce  response strings  that are  then
	 *        passed to string function in order to become readable by the issuing
	 *        process. */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_output)(struct ansitty *__restrict self,
	                            void const *data, __size_t datalen);

	/* [0..1] Turn LEDs on/off, such that NEW_LEDS = (OLD_LEDS & mask) | flag.
	 * For  this purpose,  both mask and  flag are bitsets  of LEDs enumerated
	 * from 0 to 3 (yes:  that's 4 leds, and I  don't know what that 4'th  led
	 * is all about...)
	 * However, linux defines them like this:
	 *   0x01: KEYBOARD_LED_SCROLLLOCK
	 *   0x02: KEYBOARD_LED_NUMLOCK
	 *   0x04: KEYBOARD_LED_CAPSLOCK
	 *   0x08: Undefined (ignore if it wouldn't have any meaning) */
	__ATTR_NONNULL((1)) void
	(LIBANSITTY_CC *ato_setled)(struct ansitty *__restrict self,
	                            __uint8_t mask, __uint8_t flag);

	/* [0..1] Try to get/set the terminal IOS descriptor of the associated terminal.
	 * This function can be used in 2 different modes:
	 *  - newios == NULL:
	 *      Copy the current IOS state into `oldios'.
	 *      The return value for this case doesn't matter and is ignored.
	 *  - newios != NULL:
	 *      Compare the current IOS state with `oldios'
	 *      If they  differ,  leave  `oldios' undefined,  and  return  `false'
	 *      If they match, set `newios' as the new IOS state and return `true'
	 */
	__ATTR_NONNULL((1, 2)) __BOOL
	(LIBANSITTY_CC *ato_termios)(struct ansitty *__restrict self,
	                             struct termios *__restrict oldios,
	                             struct termios const *newios);
};

#ifdef LIBANSITTY_EXPOSE_INTERNALS
#define ANSITTY_INTERNAL(x) x
#else /* LIBANSITTY_EXPOSE_INTERNALS */
#define ANSITTY_INTERNAL(x) _##x
#endif /* !LIBANSITTY_EXPOSE_INTERNALS */

struct ansitty {
	struct ansitty_operators  at_ops;         /* [const] ANSI TTY operators. */
	__uint8_t                 at_color;       /* Selected color index (0xf0: bg; 0x0f: fg). */
	__uint8_t                 at_defcolor;    /* Default color index (usually `ANSITTY_CL_DEFAULT').
	                                           * This  index  is  used  when  `\ec'  is  encountered */
	__uint8_t                 at_tcolorfg[3]; /* RGB for foreground color (`at_color & 0x0f' is the closest ANSI color) */
	__uint8_t                 at_tcolorbg[3]; /* RGB for background color (`at_color & 0xf0' is the closest ANSI color) */
	__uint16_t                ANSITTY_INTERNAL(at_ttyflag); /* Internal TTY mode flags. */
	__uint16_t                at_ttymode;     /* TTY mode (Set of `ANSITTY_MODE_*') */
	__uint16_t                at_attrib;      /* Text mode attributes (set of `ANSITTY_ATTRIB_*'). */
	ansitty_coord_t           at_savecur[2];  /* Saved cursor position */
	ansitty_coord_t           at_scroll_sl;   /* Scroll region starting line */
	ansitty_coord_t           at_scroll_el;   /* Scroll region end line */
	ansitty_coord_t           ANSITTY_INTERNAL(at_scroll_sc);   /* Scroll region starting column (only used internally!) */
	ansitty_coord_t           ANSITTY_INTERNAL(at_scroll_ec);   /* Scroll region end column (only used internally!) */
	__UINTPTR_HALF_TYPE__     ANSITTY_INTERNAL(at_state);       /* Current state-machine state. (not exposed) */
	__UINTPTR_HALF_TYPE__     at_codepage;    /* Current code-page state. (not exposed, but 0 means UTF-8) */
	union {
		__UINTPTR_TYPE__      ANSITTY_INTERNAL(at_esclen);      /* Number of written, escaped bytes. */
		__UINTPTR_HALF_TYPE__ ANSITTY_INTERNAL(at_escwrd)[2];   /* Double-word status (used by some values for `at_state') */
	};
	__byte_t                  ANSITTY_INTERNAL(at_escape)[256]; /* Escape text buffer (also used for unicode translation). */
	__byte_t                  ANSITTY_INTERNAL(at_zero);        /* [const] Always ZERO. */
	__CHAR32_TYPE__           at_lastch;      /* The last successfully printed character (used for `\e[<n>b', aka. `AC_REP()'). */
};

#undef ANSITTY_INTERNAL


/* Initialize the given ANSI TTY */
typedef __ATTR_NONNULL_T((1, 2)) void
(LIBANSITTY_CC *PANSITTY_INIT)(struct ansitty *__restrict self,
                               struct ansitty_operators const *__restrict ops);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __ATTR_NONNULL((1, 2)) void LIBANSITTY_CC
ansitty_init(struct ansitty *__restrict self,
             struct ansitty_operators const *__restrict ops);
#endif /* LIBANSITTY_WANT_PROTOTYPES */

/* Output a single utf-8 character to the given TTY */
typedef __ATTR_NONNULL_T((1)) void
(LIBANSITTY_CC *PANSITTY_PUTC)(struct ansitty *__restrict self, /*utf-8*/ char ch);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __ATTR_NONNULL((1)) void LIBANSITTY_CC
ansitty_putc(struct ansitty *__restrict self, /*utf-8*/ char ch);
#endif /* LIBANSITTY_WANT_PROTOTYPES */

/* Output a single unicode character to the given TTY */
typedef __ATTR_NONNULL_T((1)) void
(LIBANSITTY_CC *PANSITTY_PUTUNI)(struct ansitty *__restrict self, __CHAR32_TYPE__ ch);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __ATTR_NONNULL((1)) void LIBANSITTY_CC
ansitty_putuni(struct ansitty *__restrict self, __CHAR32_TYPE__ ch);
#endif /* LIBANSITTY_WANT_PROTOTYPES */

/* pformatprinter-compatible prototype for printing to an ANSI TTY
 * @param: arg: The `struct ansitty *' to which to print.
 * @return: * : Always re-return `(ssize_t)datalen' */
typedef __ATTR_NONNULL_T((1)) __ssize_t
(__FORMATPRINTER_CC *PANSITTY_PRINTER)(void *arg, char const *data, __size_t datalen);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __ATTR_NONNULL((1)) __ssize_t __FORMATPRINTER_CC
ansitty_printer(void *arg, char const *data, __size_t datalen);
#endif /* LIBANSITTY_WANT_PROTOTYPES */


/* Max number of bytes ever produced by `ansitty_translate' */
#define ANSITTY_TRANSLATE_BUFSIZE 8

/* Translate a given unicode input character `ch' (which should originate form
 * the  keyboard) into the sequence of bytes mandated by the code page that is
 * currently being used by the ansitty.
 * @return: * : The number of produced bytes (<= ANSITTY_TRANSLATE_BUFSIZE)
 * @return: 0 : The character cannot be represented in the current CP, and
 *              should be discarded. */
typedef __NOBLOCK __ATTR_NONNULL((1, 2)) __size_t
__NOTHROW_NCX_T(LIBANSITTY_CC *PANSITTY_TRANSLATE)(struct ansitty *__restrict self,
                                                   char buf[ANSITTY_TRANSLATE_BUFSIZE],
                                                   __CHAR32_TYPE__ ch);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __NOBLOCK __ATTR_NONNULL((1, 2)) __size_t
__NOTHROW_NCX(LIBANSITTY_CC ansitty_translate)(struct ansitty *__restrict self,
                                               char buf[ANSITTY_TRANSLATE_BUFSIZE],
                                               __CHAR32_TYPE__ ch);
#endif /* LIBANSITTY_WANT_PROTOTYPES */


/* Encode the representation of a misc. keyboard key `key' with `mod',
 * and finalize encoding of certain keyboard characters after  already
 * having been translated through the keymap.
 * @param: self: The ANSITTY to use (or `NULL' to use default settings)
 * @param: key:  The keyboard key (one of `KEY_*' from <kos/keyboard.h>; e.g. `KEY_UP')
 * @param: mod:  Keyboard modifiers (set of `KEYMOD_*' from <kos/keyboard.h>)
 * @param: len:  The # of bytes from `buf' that were previously encoded by the keymap.
 * @return: * :  The number of produced bytes (<= ANSITTY_TRANSLATE_BUFSIZE)
 * @return: 0 :  The key cannot be represented and should be discarded. */
typedef __NOBLOCK __ATTR_NONNULL((2)) __size_t
__NOTHROW_NCX_T(LIBANSITTY_CC *PANSITTY_TRANSLATE_MISC)(struct ansitty *self,
                                                        char buf[ANSITTY_TRANSLATE_BUFSIZE], __size_t len,
                                                        __UINT16_TYPE__ key, __UINT16_TYPE__ mod);
#ifdef LIBANSITTY_WANT_PROTOTYPES
LIBANSITTY_DECL __NOBLOCK __ATTR_NONNULL((2)) __size_t
__NOTHROW_NCX(LIBANSITTY_CC ansitty_translate_misc)(struct ansitty *self,
                                                    char buf[ANSITTY_TRANSLATE_BUFSIZE], __size_t len,
                                                    __UINT16_TYPE__ key, __UINT16_TYPE__ mod);
#endif /* LIBANSITTY_WANT_PROTOTYPES */



__DECL_END
#endif /* __CC__ */

#endif /* !_LIBANSITTY_ANSITTY_H */
