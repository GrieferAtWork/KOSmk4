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
#ifndef GUARD_LIBANSITTY_ANSITTY_C
#define GUARD_LIBANSITTY_ANSITTY_C 1
#define LIBANSITTY_EXPOSE_INTERNALS 1
#define _KOS_SOURCE 1

/* NOTE: References  used  during the  implementation of  this ansitty
 *       processor can be found in `/kos/include/libansitty/ansitty.h' */

/* TODO: The unicode C1 area contains characters that act as aliases
 *       for  \e[  and  other  sequences.  --  Support  them   here! */

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <hybrid/atomic.h>

#include <kos/anno.h>
#include <kos/keyboard.h>

#include <assert.h>
#include <format-printer.h> /* FORMATPRINTER_CC */
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unicode.h>

#include <libansitty/ansitty.h>

#include "ansitty.h"
#include "cp.h"

#ifdef __KERNEL__
#include <kernel/printk.h>
#else /* __KERNEL__ */
#include <sys/syslog.h>
#endif /* !__KERNEL__ */

/* String to integer helper functions */
#undef strtoi
#undef strtoui
#if __SIZEOF_INT__ == 4
#define strtoi  strto32
#define strtoui strtou32
#elif __SIZEOF_INT__ == 8
#define strtoi  strto64
#define strtoui strtou64
#else /* __SIZEOF_INT__ == ... */
#define strtoi  (int)strtol
#define strtoui (unsigned int)strtoul
#endif /* __SIZEOF_INT__ != ... */

#undef CONFIG_HIDE_CURSOR_DURING_NAVIGATION
/* Hide the  terminal cursor  while  navigating to  gather  information
 * about the terminal, or moving it to perform some specific operation. */
#define CONFIG_HIDE_CURSOR_DURING_NAVIGATION 1

DECL_BEGIN

/* CC = ControlCharacter */
#define CC_NUL    0x00
#define CC_ENQ    0x05
#define CC_BEL    0x07
#define CC_BS     0x08
#define CC_TAB    0x09
#define CC_LF     0x0a /* '\n' */
#define CC_VT     0x0b
#define CC_FF     0x0c
#define CC_CR     0x0d /* '\r' */
#define CC_SO     0x0e
#define CC_SI     0x0f
#define CC_CAN    0x18 /* Cancel */
#define CC_ESC    0x1b /* '\e' */
#define CC_SPC    ' '
#define CC_SESC "\033" /* "\e" */

#if 0
#define TRACE_OPERATION DOTRACE
#else
#define TRACE_OPERATION TRACE
#endif

#ifdef __KERNEL__
#define LOG_SYSTEM_WARNING(...) printk(KERN_WARNING __VA_ARGS__)
#else /* __KERNEL__ */
#define LOG_SYSTEM_WARNING(...) syslog(LOG_WARNING, __VA_ARGS__)
#endif /* !__KERNEL__ */
#define UNKNOWN_SEQUENCE_WARN LOG_SYSTEM_WARNING
#define WARN_UNKNOWN_SEQUENCE1(firstch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q\"\n", firstch)
#define WARN_UNKNOWN_SEQUENCE2(firstch, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#Q\"\n", firstch, lastch)
#define WARN_UNKNOWN_SEQUENCE3C(firstch, secondch, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#Q%#Q\"\n", firstch, secondch, lastch)
#define WARN_UNKNOWN_SEQUENCE3(firstch, len, ptr, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#$q%#Q\"\n", firstch, (size_t)(len), ptr, lastch)
#define WARN_UNKNOWN_SEQUENCE4(firstch, len, ptr, before_lastch, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#$q%#Q%#Q\"\n", firstch, (size_t)(len), ptr, before_lastch, lastch)


#if 1
#define RACE(err)                                                                    \
	do {                                                                             \
		LOG_SYSTEM_WARNING("[ansitty] race detected (%s:%d)\n", __FILE__, __LINE__); \
		goto err;                                                                    \
	}	__WHILE0
#else
#define RACE(err) goto err
#endif


/* When this bit is set in `at_scroll_ec', then the horizontal margin is disabled. */
#define HORIZONTAL_MARGIN_DISABLE_BIT \
	((ansitty_coord_t)1 << ((sizeof(ansitty_coord_t) * 8) - 1))


#define PUTUNI(uni)                 (*self->at_ops.ato_putc)(self, uni)
#define PUTUNILAST(uni)             (PUTUNI(uni), self->at_lastch = (uni))
#define GETCURSOR(pxy)              ((*self->at_ops.ato_getcursor)(self, pxy), TRACE_OPERATION("getcur:{%u,%u}\n", (pxy)[0], (pxy)[1]))
#define GETSIZE(pxy)                ((*self->at_ops.ato_getsize)(self, pxy), TRACE_OPERATION("getsiz:{%u,%u}\n", (pxy)[0], (pxy)[1]))
#define SETCURSOR(x, y, uhwc)       (TRACE_OPERATION("setcur(%u,%u,%s)\n", x, y, (uhwc) ? "true" : "false"), (*self->at_ops.ato_setcursor)(self, x, y, uhwc))
#define NOTIFY_SETCOLOR()           (TRACE_OPERATION("setcolor(%#x)\n", self->at_color), (*self->at_ops.ato_setcolor)(self))
#define NOTIFY_SETTTYMODE()         (TRACE_OPERATION("setttymode(%#x)\n", self->at_ttymode), self->at_ops.ato_setttymode ? (*self->at_ops.ato_setttymode)(self) : (void)0)
#define NOTIFY_SETATTRIB()          (TRACE_OPERATION("setattrib(%#x)\n", self->at_attrib), self->at_ops.ato_setattrib ? (*self->at_ops.ato_setattrib)(self) : (void)0)
#define SETTITLE(title)             (TRACE_OPERATION("settitle(%q)\n", title), (self->at_ops.ato_settitle ? (*self->at_ops.ato_settitle)(self, title) : (void)0))
#define DOOUTPUT(text, len)         (TRACE_OPERATION("output(%$q)\n", len, text), (*self->at_ops.ato_output)(self, text, len))
#define OUTPUT(text)                (TRACE_OPERATION("output(%q)\n", text), self->at_ops.ato_output ? (*self->at_ops.ato_output)(self, text, COMPILER_STRLEN(text)) : (void)0)
#define SCROLL(offset)              (TRACE_OPERATION("scroll(%d)\n", (int)(offset)), (*self->at_ops.ato_scroll)(self, offset))
#define COPYCELL(dst_offset, count) (TRACE_OPERATION("copycell(%d,%u)\n", (int)(dst_offset), (unsigned int)(count)), (*self->at_ops.ato_copycell)(self, dst_offset, count))
#define FILLCELL(ch, count)         (TRACE_OPERATION("fillcell(%I32Q,%u)\n", (uint32_t)(ch), (unsigned int)(count)), (*self->at_ops.ato_fillcell)(self, ch, count))
#define CLS(mode)                   (TRACE_OPERATION("cls(%u)\n", mode), (*self->at_ops.ato_cls)(self, mode))
#define EL(mode)                    (TRACE_OPERATION("el(%u)\n", mode), (*self->at_ops.ato_el)(self, mode))
#define SETLED(mask, flag)          (TRACE_OPERATION("setled(%#x,%#x)\n", mask, flag), self->at_ops.ato_setled ? (*self->at_ops.ato_setled)(self, mask, flag) : (void)0)
#define NOTIFY_SCROLLREGION()                 \
	(TRACE_OPERATION("scrollregion(%u,%u)\n", \
	                 self->at_scroll_sl,      \
	                 self->at_scroll_el),     \
	 self->at_ops.ato_scrollregion            \
	 ? (*self->at_ops.ato_scrollregion)(self) \
	 : (void)0)

#define MAXCOORD        ((ansitty_coord_t)-1)

/* Values for `at_ttyflag' */
#define ANSITTY_FLAG_NORMAL            0x0000 /* Normal flags */
#define ANSITTY_FLAG_CONCEIL           0x0001 /* FLAG: Use background color as foreground */
#define ANSITTY_FLAG_VT52              0x0002 /* FLAG: VT52 compatibility mode. */
#define ANSITTY_FLAG_HEDIT             0x0004 /* FLAG: Horizontal Editing mode (ICH/DCH/IRM go backwards). */
#define ANSITTY_FLAG_INSERT            0x0008 /* FLAG: Enable insertion mode. */
#define ANSITTY_FLAG_INSDEL_SCRN       0x0010 /* FLAG: Insert/Delete affect the entire screen. */
#define ANSITTY_FLAG_CRM               0x0020 /* FLAG: Control representation mode (https://en.wikipedia.org/wiki/Unicode_control_characters#Control_pictures) */
#define ANSITTY_FLAG_ENABLE_APP_CURSOR 0x0040 /* FLAG: Enable application cursor keys */
#define ANSITTY_FLAG_ENABLE_APP_KEYPAD 0x0080 /* FLAG: Enable application keypad keys */
#define ANSITTY_FLAG_BACKSPACE_REVERSE 0x0100 /* FLAG: 0: BS=8,CTRL+BS=127; 1: BS=127,CTRL+BS=8 */
#define ANSITTY_FLAG_COLORBOLD         0x0200 /* FLAG: \e[1m (brighten foreground color) is active. (affects \e[30m ... \e[37m) */
#define ANSITTY_FLAG_RENDERMASK        (ANSITTY_FLAG_CONCEIL | ANSITTY_FLAG_CRM | ANSITTY_FLAG_COLORBOLD) /* Mask for flags that affect rendering */

#if (ANSITTY_FLAG_COLORBOLD >> 6) == ANSITTY_IFSTRONG
#define ANSITTY_FLAG_GETCOLORSTRONG(x) (((x) & ANSITTY_FLAG_COLORBOLD) >> 6)
#else /* (ANSITTY_FLAG_COLORBOLD >> 6) == ANSITTY_IFSTRONG */
#define ANSITTY_FLAG_GETCOLORSTRONG(x) ((x) & ANSITTY_FLAG_COLORBOLD ? ANSITTY_IFSTRONG : 0)
#endif /* (ANSITTY_FLAG_COLORBOLD >> 6) != ANSITTY_IFSTRONG */


/* TTY states */
#define STATE_TEXT_UTF8        0 /* Default state: at the start of the next character. */
#define STATE_TEXT_UTF8_MBS    1 /* Inside of a multi-byte-character-string (same as `STATE_TEXT_UTF8', \
                                  * but  `at_esclen'  is non-NULL  and refers  to  the number  of UTF-8 \
                                  * characters already present within `at_escape') */
#define STATE_ESC              2 /* State set immediately after a `\e' character was encountered */
#define STATE_CSI              3 /* Process escape arguments. */
#define STATE_OSC              4 /* Operating System Command reception mode. */
#define STATE_DCS              5 /* Device control string reception mode. */
#define STATE_SOS              6 /* Start of String reception mode. */
#define STATE_PM               7 /* Privacy Message reception mode. */
#define STATE_APC              8 /* Application Program Command reception mode. */
#define STATE_OSC_ESC          9 /* `STATE_OSC', followed by "\e" */
#define STATE_DCS_ESC         10 /* `STATE_DCS', followed by "\e" */
#define STATE_SOS_ESC         11 /* `STATE_SOS', followed by "\e" */
#define STATE_PM_ESC          12 /* `STATE_PM', followed by "\e" */
#define STATE_APC_ESC         13 /* `STATE_APC', followed by "\e" */
#define STATE_LPAREN          14 /* After "\e(" */
#define STATE_ESC_5           15 /* After "\e5" */
#define STATE_ESC_6           16 /* After "\e6" */
#define STATE_ESC_POUND       17 /* After "\e#" */
#define STATE_INSERT          18 /* Insertion-mode */
#define STATE_INSERT_UTF8     19 /* Insertion-mode (in UTF-8 mode) */
#define STATE_INSERT_UTF8_MBS 20 /* Insertion-mode (in UTF-8 mode, with pending multi-byte character) */
#define STATE_ESC_Y1          21 /* After "\eY" */
#define STATE_ESC_Y1_VAL(self) (*(uint8_t *)(COMPILER_ENDOF((self)->at_escape) - sizeof(uint8_t)))
#define STATE_ESC_Y2          22 /* After "\eY<ORD>" */
#define STATE_LPAREN_PERCENT  23 /* After "\e(%" */
#define STATE_TEXT            24 /* Non-utf8 character set */

#define STATE_OSC_ADD_ESC(x) ((x) + 5)
#define STATE_OSC_DEL_ESC(x) ((x) - 5)


/* Code page codes. */
#define SET_CP(id) \
	(self->at_codepage = (id), self->at_state = STATE_TEXT)
#define CP_UTF8             0 /* \e(B               -- UTF-8 (well, actually it's ASCII, but we extend it as utf-8) */
#define CP_LDM              1 /* \e(0               -- DEC Special Character and Line Drawing Set, VT100. */
#define CP_LATIN1           2 /* \e(A               -- United Kingdom (UK), VT100. */
#define CP_DUTCH            3 /* \e(4               -- Dutch, VT200. */
#define CP_FINNISH          4 /* \e(5  \e(C         -- Finnish, VT200. */
#define CP_FRENCH           5 /* \e(f  \e(R         -- French, VT200. */
#define CP_FRENCH_CANADIAN  6 /* \e(9  \e(Q         -- French Canadian, VT200. */
#define CP_GERMAN           7 /* \e(K               -- German, VT200. */
#define CP_ITALIAN          8 /* \e(Y               -- Italian, VT200. */
#define CP_NORWEGIAN        9 /* \e(`  \e(E  \e(6   -- Norwegian, VT200. */
#define CP_PORTUGUESE      10 /* \e(%6              -- Portuguese, VT300. */
#define CP_SPANISH         11 /* \e(T               -- Spanish, VT200. */
#define CP_SWEDISH         12 /* \e(7  \e(H         -- Swedish, VT200. */
#define CP_SWISS           13 /* \e(=               -- Swiss, VT200. */

STATIC_ASSERT_MSG(CP_UTF8 == 0,
                  "CP=0 meaning UTF-8 appears in documentation "
                  "and is therefor part of the API/ABI");


/* Anything in this range (should) exit escape mode. */
#define ANSI_LOW       'A'
#define ANSI_HIGH      'z'



#ifdef __INTELLISENSE__
#define HIDECURSOR_BEGIN() do
#define HIDECURSOR_END()   __WHILE0
#elif defined(CONFIG_HIDE_CURSOR_DURING_NAVIGATION)
#define HIDECURSOR_BEGIN()                                                   \
	do {                                                                     \
		uint16_t _old_ttymode = self->at_ttymode;                            \
		if (!(_old_ttymode & ANSITTY_MODE_HIDECURSOR)) {                     \
			uint16_t _new_ttymode = _old_ttymode & ~ANSITTY_MODE_HIDECURSOR; \
			self->at_ttymode      = _new_ttymode;                            \
			NOTIFY_SETTTYMODE();                                             \
		}                                                                    \
		do
#define HIDECURSOR_END()                                 \
		__WHILE0;                                        \
		if (!(_old_ttymode & ANSITTY_MODE_HIDECURSOR)) { \
			self->at_ttymode = _old_ttymode;             \
			NOTIFY_SETTTYMODE();                         \
		}                                                \
	}	__WHILE0
#else /* CONFIG_HIDE_CURSOR_DURING_NAVIGATION */
#define HIDECURSOR_BEGIN() do
#define HIDECURSOR_END()   __WHILE0
#endif /* !CONFIG_HIDE_CURSOR_DURING_NAVIGATION */




PRIVATE NONNULL((1)) void CC
stub_setcolor(struct ansitty *__restrict UNUSED(self)) {
	/* no-op */
}

PRIVATE NONNULL((1)) void CC
stub_setcursor(struct ansitty *__restrict UNUSED(self),
               ansitty_coord_t UNUSED(x),
               ansitty_coord_t UNUSED(y),
               bool UNUSED(update_hw_cursor)) {
	/* no-op */
}

PRIVATE NONNULL((1)) void CC
stub_getsize_from_cursor(struct ansitty *__restrict self,
                         ansitty_coord_t psize[2]) {
	ansitty_coord_t xy[2];
	GETCURSOR(xy);
	SETCURSOR(MAXCOORD, MAXCOORD, false);
	GETCURSOR(psize);
	SETCURSOR(xy[0], xy[1], false);
	++psize[0];
	++psize[1];
}

PRIVATE NONNULL((1)) void CC
stub_getsize(struct ansitty *__restrict UNUSED(self),
             ansitty_coord_t ppos[2]) {
	ppos[0] = 80;
	ppos[1] = 25;
}

PRIVATE NONNULL((1)) void CC
stub_getcursor(struct ansitty *__restrict UNUSED(self),
               ansitty_coord_t ppos[2]) {
	ppos[0] = ppos[1] = 0;
}

PRIVATE NONNULL((1)) void CC
stub_cls(struct ansitty *__restrict self,
         unsigned int mode) {
	ansitty_coord_t sxsy[2];
	ansitty_coord_t xy[2];
	size_t count;
	GETCURSOR(xy);
	switch (mode) {

	case ANSITTY_CLS_AFTER:
		GETSIZE(sxsy);
		count = ((size_t)(sxsy[1] - xy[1]) * sxsy[0]) - xy[0];
		break;

	case ANSITTY_CLS_BEFORE:
		GETSIZE(sxsy);
		SETCURSOR(0, 0, false);
		count = ((size_t)xy[1] * sxsy[0]) + xy[0];
		break;

	default:
		SETCURSOR(0, 0, false);
		count = (size_t)-1;
		break;
	}
	FILLCELL(CC_SPC, count);
	SETCURSOR(xy[0], xy[1], false);
}

PRIVATE NONNULL((1)) void CC
stub_el(struct ansitty *__restrict self,
        unsigned int mode) {
	ansitty_coord_t xy[2];
	ansitty_coord_t sxy[2];
	ansitty_coord_t count;
	GETCURSOR(xy);
	switch (mode) {

	case ANSITTY_EL_AFTER:
		GETSIZE(sxy);
		count = sxy[0] - xy[0];
		break;

	case ANSITTY_EL_BEFORE:
		SETCURSOR(0, xy[1], false);
		count = xy[0];
		break;

	default:
		SETCURSOR(0, xy[1], false);
		GETSIZE(sxy);
		count = sxy[0];
		break;
	}
	FILLCELL(CC_SPC, count);
	SETCURSOR(xy[0], xy[1], false);
}

PRIVATE NONNULL((1)) void CC
stub_copycell(struct ansitty *__restrict UNUSED(self),
              ansitty_offset_t UNUSED(dst_offset),
              ansitty_coord_t UNUSED(count)) {
	/* Cannot be emulated. */
}

PRIVATE NONNULL((1)) void CC
stub_fillcell(struct ansitty *__restrict self,
              char32_t ch, ansitty_coord_t count) {
	ansitty_coord_t xy[2];
	ansitty_coord_t sxy[2];
	HIDECURSOR_BEGIN() {
		ansitty_coord_t maxcount, offset;
		GETCURSOR(xy);
		GETSIZE(sxy);
		maxcount = sxy[1] * sxy[0];
		offset   = xy[0] + (xy[1] * sxy[0]);
		if likely(maxcount > offset) {
			maxcount -= offset;
			if (count > maxcount)
				count = maxcount;
			while (count--)
				PUTUNI(ch);
			SETCURSOR(xy[0], xy[1], false);
		}
	}
	HIDECURSOR_END();

}


PRIVATE NONNULL((1)) void CC
stub_scroll_with_copycell(struct ansitty *__restrict self,
                          ansitty_offset_t offset) {
	ansitty_coord_t xy[2];
	ansitty_coord_t sxy[2];
	ansitty_coord_t y_start, y_end, y_size;
	if unlikely(!offset)
		return;
	y_start = self->at_scroll_sl;
	y_end   = self->at_scroll_el;
	if unlikely(y_start >= y_end)
		return;
	GETCURSOR(xy);
	GETSIZE(sxy);
	if (y_end > sxy[1]) {
		y_end = sxy[1];
		if unlikely(y_start >= y_end)
			goto done;
	}
	y_size = y_end - y_start;
	if (offset < 0) {
		offset = -offset;
		if ((ansitty_coord_t)offset >= y_size)
			goto clearall;
		/* Move terminal contents downwards */
		SETCURSOR(0, y_start, false);
		COPYCELL((ansitty_offset_t)sxy[0] * offset, (y_size - offset) * sxy[0]);
	} else {
		if ((ansitty_coord_t)offset >= y_size)
			goto clearall;
		/* Move terminal contents upwards */
		SETCURSOR(0, y_start + offset, false);
		COPYCELL(-(ansitty_offset_t)sxy[0] * offset, (y_size - offset) * sxy[0]);
		SETCURSOR(0, y_end - offset, false);
	}
	FILLCELL(CC_SPC, (ansitty_offset_t)sxy[0] * offset);
	SETCURSOR(xy[0], xy[1], false);
done:
	return;
clearall:
	/* Only clear cells within the scroll region! */
	if (y_start == 0 && y_end >= sxy[1]) {
		CLS(ANSITTY_CLS_ALL);
	} else {
		SETCURSOR(0, xy[1], false);
		FILLCELL(' ', y_size * xy[0]);
		SETCURSOR(xy[0], xy[1], false);
	}
}


PRIVATE NONNULL((1)) void CC
stub_scroll(struct ansitty *__restrict self,
            ansitty_offset_t offset) {
	ansitty_coord_t xy[2];
	if (offset <= 0)
		return;
	GETCURSOR(xy);
	SETCURSOR(MAXCOORD, MAXCOORD, false);
	while (offset--)
		PUTUNI(CC_LF);
	SETCURSOR(xy[0], xy[1], false);
}



/* Initialize the given ANSI TTY */
INTERN NONNULL((1, 2)) void CC
libansitty_init(struct ansitty *__restrict self,
                struct ansitty_operators const *__restrict ops) {
	memcpy(&self->at_ops, ops, sizeof(*ops));
	assertf(self->at_ops.ato_putc != NULL,
	        "Mandatory operator `ato_putc' not implemented");
	/* Substitute unimplemented operators. */
	if (!self->at_ops.ato_setcolor)
		self->at_ops.ato_setcolor = &stub_setcolor;
	if (!self->at_ops.ato_setcursor)
		self->at_ops.ato_setcursor = &stub_setcursor;
	if (!self->at_ops.ato_getcursor)
		self->at_ops.ato_getcursor = &stub_getcursor;
	if (!self->at_ops.ato_cls)
		self->at_ops.ato_cls = &stub_cls;
	if (!self->at_ops.ato_el)
		self->at_ops.ato_el = &stub_el;
	if (!self->at_ops.ato_scroll) {
		self->at_ops.ato_scroll = &stub_scroll;
		/* With copycell(), we can do 100% accurate emulation of scroll() */
		if (self->at_ops.ato_copycell)
			self->at_ops.ato_scroll = &stub_scroll_with_copycell;
	}
	if (!self->at_ops.ato_getsize)
		self->at_ops.ato_getsize = self->at_ops.ato_getcursor ? &stub_getsize_from_cursor : &stub_getsize;
	/* copycell cannot be emulated, but still replace it with a no-op */
	if (!self->at_ops.ato_copycell)
		self->at_ops.ato_copycell = &stub_copycell;
	if (!self->at_ops.ato_fillcell)
		self->at_ops.ato_fillcell = &stub_fillcell;
	self->at_color      = ANSITTY_CL_DEFAULT;
	self->at_defcolor   = ANSITTY_CL_DEFAULT;
	self->at_ttyflag    = ANSITTY_FLAG_NORMAL;
	self->at_ttymode    = ANSITTY_MODE_DEFAULT;
	self->at_attrib     = ANSITTY_ATTRIB_DEFAULT;
	self->at_savecur[0] = 0;
	self->at_savecur[0] = 0;
	self->at_scroll_sl  = 0;
	self->at_scroll_sc  = 0;
	self->at_scroll_el  = MAXCOORD;
	self->at_scroll_ec  = MAXCOORD & ~HORIZONTAL_MARGIN_DISABLE_BIT;
	self->at_state      = STATE_TEXT_UTF8;
	self->at_codepage   = CP_UTF8;
	self->at_zero       = 0;
	self->at_lastch     = ' ';
}

PRIVATE uint8_t const ansipal[16][3] = {
#define RGB(r, g, b) { r, g, b }
	/* [0x0] = */ RGB(0x00, 0x00, 0x00),
	/* [0x1] = */ RGB(0xaa, 0x00, 0x00),
	/* [0x2] = */ RGB(0x00, 0xaa, 0x00),
	/* [0x3] = */ RGB(0xaa, 0x55, 0x00),
	/* [0x4] = */ RGB(0x00, 0x00, 0xaa),
	/* [0x5] = */ RGB(0xaa, 0x00, 0xaa),
	/* [0x6] = */ RGB(0x00, 0xaa, 0xaa),
	/* [0x7] = */ RGB(0xaa, 0xaa, 0xaa),
	/* [0x8] = */ RGB(0x55, 0x55, 0x55),
	/* [0x9] = */ RGB(0xff, 0x55, 0x55),
	/* [0xa] = */ RGB(0x55, 0xff, 0x55),
	/* [0xb] = */ RGB(0xff, 0xff, 0x55),
	/* [0xc] = */ RGB(0x55, 0x55, 0xff),
	/* [0xd] = */ RGB(0xff, 0x55, 0xff),
	/* [0xe] = */ RGB(0x55, 0xff, 0xff),
	/* [0xf] = */ RGB(0xff, 0xff, 0xff),
#undef RGB
};


PRIVATE NOBLOCK ATTR_CONST WUNUSED uint16_t
NOTHROW(CC color_distance)(uint8_t ra, uint8_t ga, uint8_t ba,
                           uint8_t rb, uint8_t gb, uint8_t bb) {
	uint16_t dist_r = (unsigned int)abs((int)ra - (int)rb);
	uint16_t dist_g = (unsigned int)abs((int)ga - (int)gb);
	uint16_t dist_b = (unsigned int)abs((int)ba - (int)bb);
	/* Crude, hacky way of favoring colors best seen by the human eye. */
	return (dist_r) +
	       (dist_g * 2) +
	       (dist_b / 2);
}

PRIVATE NOBLOCK ATTR_CONST WUNUSED uint8_t
NOTHROW(CC colorindex)(uint8_t r, uint8_t g, uint8_t b) {
	uint8_t i, winner_index = 0;
	uint16_t winner_distance = (uint16_t)-1;
	for (i = 0; i < COMPILER_LENOF(ansipal); ++i) {
		uint16_t distance;
		distance = color_distance(r, g, b,
		                          ansipal[i][0],
		                          ansipal[i][1],
		                          ansipal[i][2]);
		if (distance < winner_distance) {
			winner_distance = distance;
			winner_index    = i;
		}
	}
	return winner_index;
}


PRIVATE NONNULL((1)) void CC
setcolor_rgb_fg(struct ansitty *__restrict self,
                uint8_t r, uint8_t g, uint8_t b) {
	if unlikely(self->at_ttyflag & ANSITTY_FLAG_CONCEIL) {
		r = self->at_tcolorbg[0];
		g = self->at_tcolorbg[1];
		b = self->at_tcolorbg[2];
	}
	if (self->at_tcolorfg[0] == r &&
	    self->at_tcolorfg[1] == g &&
	    self->at_tcolorfg[2] == b)
		return; /* Unchanged. */

	/* Load new color index. */
	self->at_color = ANSITTY_PALETTE_INDEX(colorindex(r, g, b),
	                                       ANSITTY_PALETTE_INDEX_BG(self->at_color));

	/* Set color values. */
	self->at_tcolorfg[0] = r;
	self->at_tcolorfg[1] = g;
	self->at_tcolorfg[2] = b;
	NOTIFY_SETCOLOR();
}

PRIVATE NONNULL((1)) void CC
setcolor_rgb_bg(struct ansitty *__restrict self,
                uint8_t r, uint8_t g, uint8_t b) {
	uint8_t color;
	if (self->at_tcolorbg[0] == r &&
	    self->at_tcolorbg[1] == g &&
	    self->at_tcolorbg[2] == b)
		return; /* Unchanged. */
	color = ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(self->at_color),
	                              colorindex(r, g, b));
	if unlikely(self->at_ttyflag & ANSITTY_FLAG_CONCEIL) {
		self->at_tcolorfg[0] = r;
		self->at_tcolorfg[1] = g;
		self->at_tcolorfg[2] = b;
		color = ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_BG(color),
		                              ANSITTY_PALETTE_INDEX_BG(color));
	}
	self->at_color       = color;
	self->at_tcolorbg[0] = r;
	self->at_tcolorbg[1] = g;
	self->at_tcolorbg[2] = b;
	NOTIFY_SETCOLOR();
}


PRIVATE NONNULL((1)) void CC
setcolor(struct ansitty *__restrict self,
         uint8_t color) {
	if unlikely(self->at_ttyflag & ANSITTY_FLAG_CONCEIL) {
		color = ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_BG(color),
		                              ANSITTY_PALETTE_INDEX_BG(color));
	}
	if (self->at_color == color)
		return; /* Unchanged. */
	self->at_color = color;
	memcpy(self->at_tcolorfg, ansipal[ANSITTY_PALETTE_INDEX_FG(color)], sizeof(self->at_tcolorfg));
	memcpy(self->at_tcolorbg, ansipal[ANSITTY_PALETTE_INDEX_BG(color)], sizeof(self->at_tcolorbg));
	NOTIFY_SETCOLOR();
}

PRIVATE NONNULL((1)) void CC
setttymode(struct ansitty *__restrict self, uint16_t new_ttymode) {
	if (self->at_ttymode == new_ttymode)
		return;
	self->at_ttymode = new_ttymode;
	NOTIFY_SETTTYMODE();
}

PRIVATE NONNULL((1)) void CC
setattrib(struct ansitty *__restrict self, uint16_t new_attrib) {
	if (self->at_attrib == new_attrib)
		return;
	self->at_attrib = new_attrib;
	NOTIFY_SETATTRIB();
}

PRIVATE NONNULL((1)) void CC
setflags(struct ansitty *__restrict self, uint16_t new_flags) {
	if (self->at_ttyflag == new_flags)
		return;
	if ((new_flags & ANSITTY_FLAG_CONCEIL) != (self->at_ttyflag & ANSITTY_FLAG_CONCEIL)) {
		if (new_flags & ANSITTY_FLAG_CONCEIL) {
			uint8_t used_color;
			used_color = self->at_color;
			used_color = ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_BG(used_color),
			                                   ANSITTY_PALETTE_INDEX_BG(used_color));
			setcolor(self, used_color);
		}
	}
	self->at_ttyflag = new_flags;
}




PRIVATE NONNULL((1)) void CC
savecursor(struct ansitty *__restrict self) {
	GETCURSOR(self->at_savecur);
}

PRIVATE NONNULL((1)) void CC
loadcursor(struct ansitty *__restrict self) {
	SETCURSOR(self->at_savecur[0],
	          self->at_savecur[1],
	          true);
}

PRIVATE NONNULL((1)) void CC
setscrollregion(struct ansitty *__restrict self,
                ansitty_coord_t sl,
                ansitty_coord_t el) {
	if (sl == self->at_scroll_sl &&
	    el == self->at_scroll_el)
		return;
	self->at_scroll_sl = sl;
	self->at_scroll_el = el;
	NOTIFY_SCROLLREGION();
}

PRIVATE NONNULL((1)) void CC
setscrollmargin(struct ansitty *__restrict self,
                ansitty_coord_t sc,
                ansitty_coord_t ec) {
	self->at_scroll_sc = sc;
	self->at_scroll_ec = ec & ~HORIZONTAL_MARGIN_DISABLE_BIT;
}


PRIVATE NONNULL((1)) void CC
resetterminal(struct ansitty *__restrict self,
              bool soft_reset) {
	(void)soft_reset;
	/* Reset graphics, tabs, font and color. */
	setflags(self, ANSITTY_FLAG_NORMAL);
	setattrib(self, ANSITTY_ATTRIB_DEFAULT);
	setttymode(self, ANSITTY_MODE_DEFAULT);
	setcolor(self, self->at_defcolor);
	setscrollregion(self, 0, MAXCOORD);
	self->at_scroll_sc = 0;
	self->at_scroll_ec = MAXCOORD & ~HORIZONTAL_MARGIN_DISABLE_BIT;
	if (self->at_ops.ato_termios) {
		struct termios oldios, newios;
		for (;;) {
			(*self->at_ops.ato_termios)(self, &oldios, NULL);
			memcpy(&newios, &oldios, sizeof(struct termios));
			newios.c_oflag |= ONLCR;
			/* After  a reset (or  power-on), a terminal is  supposed to clear the
			 * XOFF flag in order to indicate that it has once again gained power.
			 * We  emulate this behavior  by clearing the  XOFF status flag within
			 * the IOS structure.
			 * s.a. `https://vt100.net/docs/vt102-ug/chapter5.html#S5.5.2.27' */
			newios.c_iflag &= ~IXOFF;
			if (newios.c_iflag == oldios.c_iflag &&
			    newios.c_oflag == oldios.c_oflag)
				break;
			if ((*self->at_ops.ato_termios)(self, &oldios, &newios))
				break;
		}
	}
}







/* ==================================================================================== */
/* Low-level character output helpers                                                   */
/* ==================================================================================== */

PRIVATE NONNULL((1)) void CC
ansitty_setstate_text(struct ansitty *__restrict self) {
	self->at_state = (self->at_ttyflag & ANSITTY_FLAG_INSERT)
	                 ? (self->at_codepage == CP_UTF8 ? STATE_INSERT_UTF8 : STATE_INSERT)
	                 : (self->at_codepage == CP_UTF8 ? STATE_TEXT_UTF8 : STATE_TEXT);
}

PRIVATE ATTR_PURE WUNUSED NONNULL((2)) char32_t FCALL
cp_decode(uint8_t ch, struct ansitty *__restrict self) {
	char32_t result;
	switch (self->at_codepage) {

	case CP_LDM:
		result = libansitty_decode_cp_ldm(ch);
		break;

	case CP_DUTCH:
		result = libansitty_decode_cp_dutch(ch);
		break;

	case CP_FINNISH:
		result = libansitty_decode_cp_finnish(ch);
		break;

	case CP_FRENCH:
		result = libansitty_decode_cp_french(ch);
		break;

	case CP_FRENCH_CANADIAN:
		result = libansitty_decode_cp_french_canadian(ch);
		break;

	case CP_GERMAN:
		result = libansitty_decode_cp_german(ch);
		break;

	case CP_ITALIAN:
		result = libansitty_decode_cp_italian(ch);
		break;

	case CP_NORWEGIAN:
		result = libansitty_decode_cp_norwegian(ch);
		break;

	case CP_PORTUGUESE:
		result = libansitty_decode_cp_portuguese(ch);
		break;

	case CP_SPANISH:
		result = libansitty_decode_cp_spanish(ch);
		break;

	case CP_SWEDISH:
		result = libansitty_decode_cp_swedish(ch);
		break;

	case CP_SWISS:
		result = libansitty_decode_cp_swiss(ch);
		break;

	case CP_LATIN1:
	default:
		result = (char32_t)ch;
		break;
	}
	return result;
}

PRIVATE NONNULL((1)) bool CC
handle_control_character(struct ansitty *__restrict self, char32_t ch) {
	switch (ch) {

	case CC_NUL:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM)
			PUTUNILAST(0x2400);
		/* NUL should be ignored by ansi ttys in all situations. */
		goto done;

	case CC_ENQ:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM)
			PUTUNILAST(0x2405);
		/* Return Terminal Status (which defaults to an empty string) */
		goto done;

	case CC_BS:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM) {
			PUTUNI(CC_BS);
			PUTUNILAST(0x2408);
		}
		break;

	case CC_BEL:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM)
			PUTUNILAST(0x2400 + (uint8_t)ch);
		break;

	case CC_TAB:
	case CC_CR:
	case CC_LF:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM) {
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			PUTUNILAST(0x2400 + (uint8_t)ch);
			SETCURSOR(xy[0], xy[1], false);
		}
		break;

	case CC_VT:
	case CC_FF:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM) {
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			PUTUNILAST(0x2400 + (uint8_t)ch);
			SETCURSOR(xy[0], xy[1], false);
		}
		ch = CC_LF;
		break;

	case CC_SO:
	case CC_SI:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM)
			PUTUNILAST(0x2400 + (uint8_t)ch);
		/* Standard/Alternate character set??? */
		goto done;

	case CC_CAN:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM)
			PUTUNILAST(0x2418);
		ansitty_setstate_text(self);
		goto done;

	case CC_ESC:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM)
			PUTUNILAST(0x241b);
		self->at_state = STATE_ESC;
		goto done;

	case 0x01: case 0x02: case 0x03: case 0x04:
	case 0x06: case 0x11: case 0x12: case 0x13:
	case 0x14: case 0x15: case 0x16: case 0x17:
	case 0x19: case 0x1a: case 0x1c: case 0x1d:
	case 0x1e: case 0x1f:
		/* Misc. control characters */
		if (self->at_ttyflag & ANSITTY_FLAG_CRM)
			PUTUNILAST(0x2400 + (uint8_t)ch);
		break;

	case 0x7f: /* DEL */
		if (self->at_ttyflag & ANSITTY_FLAG_CRM)
			PUTUNILAST(0x2421);
		break;

	case CC_SPC:
		if (self->at_ttyflag & ANSITTY_FLAG_CRM) {
			PUTUNILAST(0x2420);
			goto done;
		}
		break;

	default:
		return false;
	}
	PUTUNI(ch);
done:
	return true;
}

PRIVATE NONNULL((1)) void CC
ansitty_do_insert_unicode(struct ansitty *__restrict self, char32_t ch) {
	switch (self->at_ttyflag & (ANSITTY_FLAG_HEDIT |
	                            ANSITTY_FLAG_INSDEL_SCRN)) {

	case 0: {
		/* >> 123456789       123456789
		 * >> ABCDEFGHI  -->  ABCD...EF
		 * >> abcdefghi       abcdefghi */
		ansitty_coord_t xy[2];
		ansitty_coord_t sxy[2];
		ansitty_coord_t cells_in_line;
		GETCURSOR(xy);
		GETSIZE(sxy);
		if unlikely(xy[0] >= sxy[0])
			break;
		cells_in_line = sxy[0] - xy[0];
		if (1 >= cells_in_line)
			break;
		COPYCELL(1, cells_in_line - 1);
	}	goto do_putuni_and_break;

	case ANSITTY_FLAG_INSDEL_SCRN:
		/* >> 123456789       123456789
		 * >> ABCDEFGHI  -->  ABCD...EF
		 * >> abcdefghi       GHIabcdef */
		COPYCELL(1, MAXCOORD);
do_putuni_and_break:
		PUTUNILAST(ch);
		break;

	case ANSITTY_FLAG_HEDIT: {
		ansitty_coord_t xy[2];
		/* >> 123456789       123456789
		 * >> ABCDEFGHI  -->  D...EFGHI
		 * >> abcdefghi       abcdefghi */
		GETCURSOR(xy);
		if (xy[0] <= 1) {
			/* Full area shift */
			if (xy[0] == 0)
				break;
			SETCURSOR(0, xy[1], false);
			goto do_putuni_and_break;
		}
		SETCURSOR(1, xy[1], false);
		COPYCELL(-1, xy[0] - 1);
		SETCURSOR(xy[0] - 1, xy[1], false);
	}	goto do_putuni_and_break;

	case ANSITTY_FLAG_HEDIT | ANSITTY_FLAG_INSDEL_SCRN: {
		ansitty_coord_t xy[2];
		unsigned int copy_count;
		/* >> 123456789       456789ABC
		 * >> ABCDEFGHI  -->  D...EFGHI
		 * >> abcdefghi       abcdefghi */
		GETCURSOR(xy);
		if (xy[1] == 0) {
			if (xy[0] <= 1) {
				if (xy[0] == 0)
					break;
				SETCURSOR(0, 0, false);
				goto do_putuni_and_break;
			}
			copy_count = xy[0];
		} else {
			ansitty_coord_t xy2[2];
			GETSIZE(xy2);
			copy_count = xy[0] + xy[1] * xy2[0];
		}
		SETCURSOR(1, 0, false);
		COPYCELL(-1, copy_count);
		if (!xy[0]) {
			--xy[1];
			xy[0] = MAXCOORD;
		} else {
			--xy[0];
		}
		SETCURSOR(xy[0], xy[1], false);
	}	goto do_putuni_and_break;

	default: __builtin_unreachable();
	}
}

PRIVATE NONNULL((1)) void CC
ansitty_do_repeat_unicode(struct ansitty *__restrict self,
                          char32_t ch, unsigned int count) {
	assert(count != 0);
	if (handle_control_character(self, ch)) {
		while (--count)
			handle_control_character(self, ch);
	} else if (self->at_ttyflag & ANSITTY_FLAG_INSERT) {
		do {
			ansitty_do_insert_unicode(self, ch);
		} while (--count);
	} else {
		do {
			PUTUNI(ch);
		} while (--count);
	}
}

PRIVATE NONNULL((1)) void CC
ansitty_pututf8_mbs(struct ansitty *__restrict self,
                    uintptr_half_t state, char ch) {
	char32_t unich;
	uintptr_half_t count, limit;
	if (((byte_t)ch & 0xc0) != 0x80) {
do_handle_this_ch:
		unich = (char32_t)ch;
		goto do_handle_unich;
	}
	do {
		count = ATOMIC_READ(self->at_escwrd[1]);
		limit = ATOMIC_READ(self->at_escwrd[0]);
		if unlikely(count >= limit)
			RACE(do_handle_this_ch); /* Shouldn't happen (race condition guard) */
		self->at_escape[count] = (byte_t)ch;
		if (count + 1 >= limit) {
			/* Unicode sequence has been completed. */
			char const *text;
			text  = (char *)self->at_escape;
			unich = unicode_readutf8(&text);
do_handle_unich:
			/* Check for the escape character */
			if (!handle_control_character(self, unich)) {
				if (state == STATE_INSERT_UTF8_MBS) {
					ansitty_do_insert_unicode(self, unich);
					self->at_state = STATE_INSERT_UTF8;
				} else {
					PUTUNILAST(unich);
					self->at_state = STATE_TEXT_UTF8;
				}
			}
			return;
		}
	} while (!ATOMIC_CMPXCH_WEAK(self->at_escwrd[1], count, count + 1));
}







/* ==================================================================================== */
/* Escape command implementation                                                        */
/* ==================================================================================== */


/* "\e]{arg[arglen]:%s}\e[" */
PRIVATE NONNULL((1, 2)) bool CC
ansi_OSC(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen) {
	char *pos;
	unsigned int code;
	code = strtoui(arg, &pos, 10);
	if (*pos == ';' && pos + 1 < arg + arglen) {
		switch (code) {

		case 0: /* Set icon name and window title */
		case 2: /* Set window title */
			SETTITLE(pos + 1);
			return true;
		case 1: /* Set icon name */
			return true;

		default:
			break;
		}
	}
	return false;
}

/* "\eP{arg[arglen]:%s}\e[" */
PRIVATE NONNULL((1, 2)) bool CC
ansi_DCS(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen) {
	/* ??? */
	(void)self;
	(void)arg;
	(void)arglen;
	return false;
}

/* "\eX{arg[arglen]:%s}\e[" */
PRIVATE NONNULL((1, 2)) bool CC
ansi_SOS(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen) {
	/* ??? */
	(void)self;
	(void)arg;
	(void)arglen;
	return false;
}

/* "\e^{arg[arglen]:%s}\e[" */
PRIVATE NONNULL((1, 2)) bool CC
ansi_PM(struct ansitty *__restrict self,
        char *__restrict arg, size_t arglen) {
	/* ??? */
	(void)self;
	(void)arg;
	(void)arglen;
	return false;
}

/* "\e_{arg[arglen]:%s}\e[" */
PRIVATE NONNULL((1, 2)) bool CC
ansi_APC(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen) {
	/* ??? */
	(void)self;
	(void)arg;
	(void)arglen;
	return false;
}



PRIVATE NONNULL((1)) void CC
do_ident_DA(struct ansitty *__restrict self) {
	/* Do what linux does: Report `\e[?6c` */
	OUTPUT(CC_SESC "[?6c"); /* VT102 */
}


#define ARGUMENT_CODE_SWITCH_BEGIN()                            \
	{                                                           \
		unsigned int code;                                      \
		char *_args_iter, *_args_end;                           \
		_args_iter = arg;                                       \
		for (;;) {                                              \
			code = strtoui(_args_iter, &_args_end, 10);         \
			if (*_args_end != ';' && _args_end != arg + arglen) \
				goto nope;                                      \
			switch (code) {
#define ARGUMENT_CODE_SWITCH_END()         \
			default: goto nope;            \
			}                              \
			if (_args_end == arg + arglen) \
				break;                     \
			_args_iter = _args_end + 1;    \
		}                                  \
	}

#define ARGUMENT_CODE_QSWITCH_BEGIN()                               \
	{                                                               \
		unsigned int code;                                          \
		char *_args_iter, *_args_end;                               \
		_args_iter = arg;                                           \
		for (;;) {                                                  \
			if (*_args_iter == '?') {                               \
				++_args_iter;                                       \
				code = strtoui(_args_iter, &_args_end, 10);         \
				if (*_args_end != ';' && _args_end != arg + arglen) \
					goto nope;                                      \
				switch (code) {
#define ARGUMENT_CODE_QSWITCH_ELSE()                                \
				default: goto nope;                                 \
				}                                                   \
			} else {                                                \
				code = strtoui(_args_iter, &_args_end, 10);         \
				if (*_args_end != ';' && _args_end != arg + arglen) \
					goto nope;                                      \
				switch (code) {
#define ARGUMENT_CODE_QSWITCH_END()        \
				default: goto nope;        \
				}                          \
			}                              \
			if (_args_end == arg + arglen) \
				break;                     \
			_args_iter = _args_end + 1;    \
		}                                  \
	}


PRIVATE NONNULL((1)) void CC
ansitty_do_hscroll(struct ansitty *__restrict self, int offset) {
	ansitty_coord_t xy[2];
	ansitty_coord_t y, x_size;
	ansitty_coord_t y_start, y_end;
	ansitty_coord_t x_start, x_end;
	x_start = self->at_scroll_sc;
	x_end   = self->at_scroll_ec;
	if (x_end & HORIZONTAL_MARGIN_DISABLE_BIT) {
		x_start = 0;
		x_end   = MAXCOORD;
	}
	y_start = self->at_scroll_sl;
	y_end   = self->at_scroll_el;
	if (x_start >= x_end)
		return;
	if (y_start >= y_end)
		return;
	x_size = x_end - x_start;
	if (offset >= 0) {
		unsigned int cells_per_row;
		if ((unsigned int)offset >= x_size)
			return;
		GETCURSOR(xy);
		cells_per_row = x_size - (unsigned int)offset;
		/* Copy cells to the right */
		for (y = y_start; y < y_end; ++y) {
			SETCURSOR(x_start, y, false);
			COPYCELL(offset, cells_per_row);
		}
	} else {
		ansitty_coord_t x;
		unsigned int cells_per_row;
		/* Copy cells to the left */
		offset = -offset;
		if ((unsigned int)offset >= x_size)
			return;
		GETCURSOR(xy);
		x = x_start + (unsigned int)offset;
		cells_per_row = x_size - (unsigned int)offset;
		for (y = y_start; y < y_end; ++y) {
			SETCURSOR(x, y, false);
			COPYCELL(-offset, cells_per_row);
		}
	}
	SETCURSOR(xy[0], xy[1], false);
}


/* "\e[{arg[arglen]:%s}{lastch}" */
PRIVATE NONNULL((1, 2)) bool CC
ansi_CSI(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen,
         char lastch) {
	switch (lastch) {

	case '@': /* ICH -- [10@  Make room for 10 characters at current position */
		if (arglen >= 1 && arg[arglen - 1] == ' ') {
			/* SL - Scroll Left   \e[4 @   move everything over 4 columns, 4 new columns at right */
			int n;
			if (arglen == 1)
				n = 1;
			else {
				char *end;
				n = strtoi(arg, &end, 10);
				if unlikely(end != arg + arglen - 1)
					goto nope;
			}
			ansitty_do_hscroll(self, n);
			break;
		}
		goto do_single_argument_case;

	case 'A': /* ANSI/VT100: CUU */
		if (arglen >= 1 && arg[arglen - 1] == ' ') {
			/* SR  - Scroll Right   \e[2 A   move everything over 2 columns, 2 new columns at left */
			int n;
			if (arglen == 1)
				n = 1;
			else {
				char *end;
				n = strtoi(arg, &end, 10);
				if unlikely(end != arg + arglen - 1)
					goto nope;
			}
			ansitty_do_hscroll(self, -n);
			break;
		}
		goto do_single_argument_case;

	case 'B': /* ANSI/VT100: CUD */
	case 'C': /* ANSI/VT100: CUF */
	case 'a': /* HPR */
	case 'D': /* ANSI/VT100: CUB */
	case 'd': /* VPA */
	case 'E': /* ANSI: CNL */
	case 'e': /* VPR */
	case 'F': /* ANSI: CPL */
	case 'G': /* ANSI: CHA */
	case '`': /* HPA */
	case 'S': /* ANSI: SU */
	case 'T': /* ANSI: SD */
	case 'L': /* IL -- \e[3L   Insert 3 lines if currently in scrolling region */
	case 'M': /* DL -- \e[2M   Delete 2 lines if currently in scrolling region */
	case 'b': /* REP -- \e[80b   Repeat character 80 times */
	case '|': /* DECTTC -- Transmit Termination Character */
	case 'P': /* DCH -- Delete Character, from current position to end of field */
	{
		int n;
do_single_argument_case:
		if (!arglen)
			n = 1;
		else {
			char *end;
			n = strtoi(arg, &end, 10);
			if unlikely(end != arg + arglen)
				goto nope;
		}
		switch (lastch) {

		case 'A': /* ANSI/VT100: CUU */
			n = -n;
			ATTR_FALLTHROUGH
		case 'B': /* ANSI/VT100: CUD */
		case 'e': /* VPR -- Vertical Position Relative */
		{
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			n += xy[1];
			if (n < 0)
				n = 0;
			SETCURSOR(xy[0], (ansitty_coord_t)n, true);
		}	break;

		case 'D': /* ANSI/VT100: CUB */
			n = -n;
			ATTR_FALLTHROUGH
		case 'C': /* ANSI/VT100: CUF */
		case 'a': /* HPR -- Horizontal Position Relative */
		{
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			n += xy[0];
			if (n < 0)
				n = 0;
			SETCURSOR((ansitty_coord_t)n, xy[1], true);
		}	break;

		case 'd': /* VPA -- Vertical Position Absolute */
		{
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			if (n < 1)
				n = 1;
			SETCURSOR(xy[0], (ansitty_coord_t)n - 1, true);
		}	break;

		case 'F': /* ANSI: CPL */
			n = -n;
			ATTR_FALLTHROUGH
		case 'E': { /* ANSI: CNL */
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			n += xy[1];
			if (n < 0)
				n = 0;
			SETCURSOR(0, (ansitty_coord_t)n, true);
		}	break;

		case 'G': /* ANSI: CHA */
		case '`': /* HPA -- Horizontal Position Absolute */
		{
			ansitty_coord_t xy[2];
			if (n < 1)
				n = 1;
			GETCURSOR(xy);
			SETCURSOR((ansitty_coord_t)n - 1, xy[1], true);
		}	break;

		case 'T': /* ANSI: SD */
			n = -n;
			ATTR_FALLTHROUGH
		case 'S': /* ANSI: SU */
			SCROLL((ansitty_offset_t)n);
			break;

		case '@':
			/* ICH -- [10@  Make room for 10 characters at current position */
			if (n <= 0)
				break;
			switch (self->at_ttyflag & (ANSITTY_FLAG_HEDIT |
			                            ANSITTY_FLAG_INSDEL_SCRN)) {

			case 0: {
				/* >> 123456789       123456789
				 * >> ABCDEFGHI  -->  ABCD...EF
				 * >> abcdefghi       abcdefghi */
				ansitty_coord_t xy[2];
				ansitty_coord_t sxy[2];
				ansitty_coord_t cells_in_line;
				GETCURSOR(xy);
				GETSIZE(sxy);
				if unlikely(xy[0] >= sxy[0])
					break;
				cells_in_line = sxy[0] - xy[0];
				if ((unsigned int)n >= cells_in_line)
					break;
				COPYCELL(n, cells_in_line - (unsigned int)n);
			}	break;

			case ANSITTY_FLAG_INSDEL_SCRN:
				/* >> 123456789       123456789
				 * >> ABCDEFGHI  -->  ABCD...EF
				 * >> abcdefghi       GHIabcdef */
				COPYCELL(n, MAXCOORD);
				break;

			case ANSITTY_FLAG_HEDIT: {
				ansitty_coord_t xy[2];
				/* >> 123456789       123456789
				 * >> ABCDEFGHI  -->  D...EFGHI
				 * >> abcdefghi       abcdefghi */
				GETCURSOR(xy);
				if ((unsigned int)n >= xy[0]) {
					/* Full area shift */
				} else {
					SETCURSOR((ansitty_coord_t)n, xy[1], false);
					COPYCELL(-n, xy[0] - (unsigned int)n);
					SETCURSOR(xy[0], xy[1], false);
				}
			}	break;

			case ANSITTY_FLAG_HEDIT | ANSITTY_FLAG_INSDEL_SCRN: {
				ansitty_coord_t xy[2];
				ansitty_coord_t xy2[2];
				unsigned int copy_count;
				/* >> 123456789       456789ABC
				 * >> ABCDEFGHI  -->  D...EFGHI
				 * >> abcdefghi       abcdefghi */
				GETCURSOR(xy);
				if (xy[1] == 0) {
					if (xy[0] < (unsigned int)n)
						break;
					copy_count = xy[0];
					SETCURSOR((unsigned int)n, 0, false);
				} else {
					SETCURSOR((unsigned int)n, 0, false);
					GETCURSOR(xy2);
					if (xy2[0] < (unsigned int)n) {
						/* n >= SCREEN_SIZE.X, where xy2[0] == SCREEN_SIZE.X - 1 */
						ansitty_coord_t column, row;
						++xy2[0];
						column = n % xy2[0];
						row    = n / xy2[0];
						if (row > xy[1] ||
							(row == xy[1] && column > xy[0])) {
							SETCURSOR(xy[0], xy[1], false);
							goto done_insert_ansitty_flag_hedit; /* Full area shift */
						}
						SETCURSOR(column, row, false);
					} else {
						/* We still need to know the display width */
						GETSIZE(xy2);
					}
					copy_count = xy[0] + xy[1] * xy2[0];
				}
				COPYCELL(-n, copy_count);
				SETCURSOR(xy[0], xy[1], false);
done_insert_ansitty_flag_hedit:
				;
			}	break;

			default: __builtin_unreachable();
			}
			break;

		case 'P':
			/* DCH -- Delete Character, from current position to end of field */
			if (n <= 0)
				break;
			switch (self->at_ttyflag & (ANSITTY_FLAG_HEDIT |
			                            ANSITTY_FLAG_INSDEL_SCRN)) {

			case 0: {
				/* >> 123456789       123456789
				 * >> ABCDEFGHI  -->  ABCDHI...
				 * >> abcdefghi       abcdefghi */
				/* TODO: Need to account for the right margin here! */
				ansitty_coord_t xy[2];
				ansitty_coord_t sxy[2];
				GETCURSOR(xy);
				GETSIZE(sxy);
				if unlikely(xy[0] >= sxy[0]) {
					/* Full area shift */
				} else {
					ansitty_coord_t cells_in_line;
					cells_in_line = sxy[0] - xy[0];
					if ((unsigned int)n >= cells_in_line) {
						/* Full area shift */
					} else {
						SETCURSOR(xy[0] + (unsigned int)n, xy[1], false);
						COPYCELL(-n, cells_in_line - (unsigned int)n);
						SETCURSOR(xy[0], xy[1], false);
					}
				}
			}	break;

			case ANSITTY_FLAG_INSDEL_SCRN: {
				/* >> 123456789       123456789
				 * >> ABCDEFGHI  -->  ABCDHIabc
				 * >> abcdefghi       defghi... */
				ansitty_coord_t xy[2];
				ansitty_coord_t xy2[2];
				ansitty_coord_t new_x;
				GETCURSOR(xy);
				new_x = xy[0] + (unsigned int)n;
				SETCURSOR(new_x, xy[1], false);
				GETCURSOR(xy2);
				if (xy2[0] < new_x) {
					ansitty_coord_t new_y;
					++xy2[0];
					new_y = xy[1] + (unsigned int)n / xy2[0];
					new_x = xy[0] + (unsigned int)n % xy2[0];
					SETCURSOR(new_x, new_y, false);
				}
				COPYCELL(-n, MAXCOORD);
				SETCURSOR(xy[0], xy[1], false);
			}	break;

			case ANSITTY_FLAG_HEDIT: {
				ansitty_coord_t xy[2];
				/* >> 123456789       123456789
				 * >> ABCDEFGHI  -->  ...AEFGHI
				 * >> abcdefghi       abcdefghi */
				GETCURSOR(xy);
				if ((unsigned int)n >= xy[0]) {
					/* Full area shift */
				} else {
					if (xy[0] != 0)
						SETCURSOR(0, xy[1], false);
					COPYCELL(n, xy[0] - (unsigned int)n);
					SETCURSOR(xy[0], xy[1], false);
				}
			}	break;

			case ANSITTY_FLAG_HEDIT | ANSITTY_FLAG_INSDEL_SCRN: {
				ansitty_coord_t xy[2];
				unsigned int copy_count;
				/* >> 123456789       ...123456
				 * >> ABCDEFGHI  -->  789AEFGHI
				 * >> abcdefghi       abcdefghi */
				GETCURSOR(xy);
				copy_count = xy[0];
				if (xy[1] != 0) {
					ansitty_coord_t sxy[2];
					GETSIZE(sxy);
					copy_count += xy[1] * sxy[0];
				}
				SETCURSOR(0, 0, false);
				COPYCELL(n, copy_count);
				SETCURSOR(xy[0], xy[1], false);
			}	break;

			default: __builtin_unreachable();
			}
			break;

		case 'L': /* IL -- \e[3L   Insert 3 lines if currently in scrolling region */
			n = -n;
			ATTR_FALLTHROUGH
		case 'M': /* DL -- \e[2M   Delete 2 lines if currently in scrolling region */
		{
			ansitty_coord_t xy[2];
			ansitty_coord_t old_sl, old_el;
			old_sl = self->at_scroll_sl;
			old_el = self->at_scroll_el;
			GETCURSOR(xy);
			if (xy[1] >= old_sl && xy[1] < old_el) {
				/* Scroll if inside of scroll region */
				if (n < 0) {
					setscrollregion(self, old_sl, xy[1]);
				} else {
					setscrollregion(self, xy[1], old_el);
				}
				SCROLL(n);
				setscrollregion(self, old_sl, old_el);
			}
		}	break;

		case 'b': /* REP -- \e[80b   Repeat character 80 times */
			/* Note while the specs don't say which character should be repeated,
			 * I    implement    this    one    as     repeat-the-next-character. */
			if (n <= 0)
				break;
			ansitty_do_repeat_unicode(self,
			                          self->at_lastch,
			                          (unsigned int)n);
			break;

		case '|': { /* DECTTC -- Transmit Termination Character */
			if (n == 1)
				PUTUNI(0xc); /* form-feed */
			else {
				if (n != 0)
					goto nope;
			}
			PUTUNI(0x03); /* End-of-text */
			PUTUNI(0x17); /* End-of-transmission-block */
			PUTUNI(0x04); /* End-of-transmission */
			PUTUNI(0x00); /* null */
		}	break;

		default: __builtin_unreachable();
		}
	}	break;

	case 'H':   /* ANSI/VT100: CUP */
	case 'f': { /* ANSI/VT100: HVP */
		int y, x;
		if (!arglen)
			y = x = 1; /* \e[f */
		else {
			char *end;
			if (arg[0] == ';') {
				y = 1; /* \e[;10f  --or-- \e[;f */
				if (arglen == 1)
					x = 1;
				else {
					x = strtoi(arg + 1, &end, 10);
					if unlikely(end != arg + arglen)
						goto nope;
				}
			} else {
				y = strtoi(arg, &end, 10);
				if (end >= arg + arglen) {
					x = 1; /* \e[10f */
				} else {
					if (end[0] != ';')
						goto nope;  /* \e[10;20f --or-- \e[10;f */
					x = strtoi(end + 1, &end, 10);
				}
				if unlikely(end != arg + arglen)
					goto nope;
				if unlikely(y < 1)
					y = 1;
			}
			if unlikely(x < 1)
				x = 1;
		}
		SETCURSOR((ansitty_coord_t)(x - 1),
		          (ansitty_coord_t)(y - 1),
		          true);
	}	break;

	/* TODO: case 'I': Horizontal tab emulation */


	case 'J': /* ANSI/VT100: ED */
		if (!arglen)
			CLS(ANSITTY_CLS_AFTER);
		else {
			ARGUMENT_CODE_SWITCH_BEGIN() {

			case ANSITTY_CLS_AFTER:
			case ANSITTY_CLS_BEFORE:
			case ANSITTY_CLS_ALL:
			case ANSITTY_CLS_ALLPAGES:
				CLS(code);
				break;

			}
			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'K': /* ANSI/VT100: EL */
		if (!arglen)
			EL(ANSITTY_EL_AFTER);
		else {
			ARGUMENT_CODE_SWITCH_BEGIN() {

			case ANSITTY_EL_AFTER:
			case ANSITTY_EL_BEFORE:
			case ANSITTY_EL_ALL:
				EL(code);
				break;

			}
			ARGUMENT_CODE_SWITCH_END()
		}
		break;


	case 'Q': /* SEM Set Editing extent Mode (limits ICH & DCH) */
		if (!arglen)
			self->at_ttyflag |= ANSITTY_FLAG_INSDEL_SCRN;
		else {
			ARGUMENT_CODE_SWITCH_BEGIN() {

			case 0: /* \e[0Q   [Q = Insert/delete character affects rest of display */
				self->at_ttyflag |= ANSITTY_FLAG_INSDEL_SCRN;
				break;

			case 1: /* \e[1Q   ICH/DCH affect the current line only */
				self->at_ttyflag &= ~(ANSITTY_FLAG_INSDEL_SCRN);
				break;
			/* TODO: \e[2Q   ICH/DCH affect current field (between tab stops) only */
			/* TODO: \e[3Q   ICH/DCH affect qualified area (between protected fields) */

			}
			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'c':
		if (!arglen) {
			do_ident_DA(self);
		} else {
			ARGUMENT_CODE_SWITCH_BEGIN() {

			case 0:
				do_ident_DA(self);
				break;

			}
			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'h':
	case 'l':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_QSWITCH_BEGIN() {

			case 0:
				/* Must be ignored. */
				break;

			case 1: /* \e[?1h    DECCKM   Cursor Keys Mode, send ESC O A for cursor up */
			        /* \e[?1l             Cursor keys send ANSI cursor position commands DECCKM */
				if (lastch == 'h') {
					self->at_ttyflag |= ANSITTY_FLAG_ENABLE_APP_CURSOR;
				} else {
					self->at_ttyflag &= ~ANSITTY_FLAG_ENABLE_APP_CURSOR;
				}
				break;

			case 2: /* \e[?2h    DECANM   ANSI Mode, use ESC < to switch VT52 to ANSI */
			        /* \e[?2l             Use VT52 emulation instead of ANSI mode DECANM */
				if (lastch == 'h') {
					/* \e[?2h -- Set ANSI (versus VT52) */
					self->at_ttyflag &= ~ANSITTY_FLAG_VT52;
				} else {
					/* \e[?2l -- Set VT52 (versus ANSI) */
					self->at_ttyflag |= ANSITTY_FLAG_VT52;
				}
				break;

//			case 3: /* \e[?3h    DECCOLM  COLumn mode, 132 characters per line */
//			        /* \e[?3l             80 characters per line (erases screen) DECCOLM */
//			case 4: /* \e[?4h    DECSCLM  SCrolL Mode, smooth scrolling */
//			        /* \e[?4l             Jump scrolling DECSCLM */
//			case 5: /* \e[?5h    DECSCNM  SCreeN Mode,  white on black background */
//			        /* \e[?5l             black on white background) DEC SCNM */
//			case 6: /* \e[?6h    DECOM    Origin Mode, line 1 is relative to scroll region */
//			        /* \e[?6l             Line numbers are independent of scrolling region DECOM */

			case 7: /* \e[?7h    DECAWM   AutoWrap Mode, start newline after column 80 */
			        /* \e[?7l             Cursor remains at end of line after column 80 DECAWM */
				setttymode(self, (self->at_ttymode & ~ANSITTY_MODE_NOLINEWRAP) |
				                 (lastch == 'l' ? ANSITTY_MODE_NOLINEWRAP : 0));
				break;

//			case 8: /* \e[?8h    DECARM   Auto Repeat Mode, key will autorepeat */
//			        /* \e[?8l             Keys do not repeat when held down DECARM */
//			case 9: /* \e[?9h    DECINLM  INterLace Mode, interlaced for taking photos */
//			        /* \e[?9l             Display is not interlaced to avoid flicker DECINLM */
//			case 10: /* \e[?10h   DECEDM   Edit Mode, VT132 is in EDIT mode */
//			         /* \e[?10l            VT132 transmits all key presses DECEDM */
//			case 11: /* \e[?11h   DECLTM   Line Transmit Mode, ignore TTM, send line */
//			         /* \e[?11l            Send page or partial page depending on TTM DECLTM */
//			case 13: /* \e[?13h   DECSCFDM Space Compression/Field Delimiting on, */
//			         /* \e[?13l            Don't suppress trailing spaces on transmit DECSCFDN */
//			case 14: /* \e[?14h   DECTEM   Transmit Execution Mode, transmit on ENTER */
//			         /* \e[?14l            ENTER sends ESC S (STS) a request to send DECTEM */
//			case 16: /* \e[?16h   DECEKEM  Edit Key Execution Mode, EDIT key is local */
//			         /* \e[?16l            EDIT key transmits either $[10h or $[10l DECEKEM */
//			case 18: /* \e[?18h   DECPFF   Print FormFeed mode, send FF after printscreen */
//			         /* \e[?18l            Don't send a formfeed after printing screen DECPFF */
//			case 19: /* \e[?19h   DECPEXT  Print Extent mode, print entire screen */
//			         /* \e[?19l            Print only the lines within the scroll region DECPEXT */
//			case 20: /* \e[?20h   OV1   Overstrike, overlay characters on GIGI */
//			         /* \e[?20l   OV0   Space is destructive, replace not overstrike, GIGI OV0 */
//			case 21: /* \e[?21h   BA1   Local BASIC, GIGI to keyboard and screen */
//			         /* \e[?21l   BA0   No BASIC, GIGI is On-Line or Local BA0 */
//			case 22: /* \e[?22h   BA2   Host BASIC, GIGI to host computer */
//			         /* \e[?22l   BA0   No BASIC, GIGI is On-Line or Local BA0 */
//			case 23: /* \e[?23h   PK1   GIGI numeric keypad sends reprogrammable sequences */
//			         /* \e[?23l   PK0   Ignore reprogramming on GIGI keypad and cursor PK0rs */

			case 24: /* \e[?24h   AH1   Autohardcopy before erasing or rolling GIGI screen */
			         /* \e[?24l   AH0   No auto-hardcopy when GIGI screen erased AH0 */
				if (self->at_ops.ato_termios) {
					struct termios oldios, newios;
					for (;;) {
						(*self->at_ops.ato_termios)(self, &oldios, NULL);
						memcpy(&newios, &oldios, sizeof(struct termios));
						if (lastch == 'h') {
							/* Enable ECHOPRT */
							if (newios.c_lflag & ECHOPRT)
								break;
							newios.c_lflag |= ECHOPRT;
						} else {
							/* Disable ECHOPRT */
							if (!(newios.c_lflag & ECHOPRT))
								break;
							newios.c_lflag &= ~ECHOPRT;
						}
						if ((*self->at_ops.ato_termios)(self, &oldios, &newios))
							break;
					}
				}
				break;

			case 25: /* \e[?25h   show cursor */
			         /* \e[?25l   hide cursor */
				setttymode(self, (self->at_ttymode & ~ANSITTY_MODE_HIDECURSOR) |
				                 (lastch == 'h' ? 0 : ANSITTY_MODE_HIDECURSOR));
				break;

//			case 29: /* \e[?29h   Use only the proper pitch for the LA100 font */
//			         /* \e[?29l   Allow all character pitches on the LA100 */

//			case 38: /* \e[?38h   DECTEK  TEKtronix mode graphics */
//			         /* \e[?38l           Ignore TEKtronix graphics commands */

			case 66: /* \e[?66h   Application keypad (DECNKM), VT320. */
			         /* \e[?66l   Numeric keypad (DECNKM), VT320. */
				if (lastch == 'h') {
					self->at_ttyflag |= ANSITTY_FLAG_ENABLE_APP_KEYPAD;
				} else {
					self->at_ttyflag &= ~ANSITTY_FLAG_ENABLE_APP_KEYPAD;
				}
				break;

			case 67: /* \e[?67h   Backarrow key sends backspace (DECBKM), VT340, VT420. */
			         /* \e[?67l   Backarrow key sends delete (DECBKM), VT340, VT420 */
				if (lastch == 'h') {
					self->at_ttyflag &= ~ANSITTY_FLAG_BACKSPACE_REVERSE;
				} else {
					self->at_ttyflag |= ANSITTY_FLAG_BACKSPACE_REVERSE;
				}
				break;

			case 69: /* \e[?69h   Enable left and right margin mode (DECLRMM), VT420 and up. */
			         /* \e[?69l   Disable left and right margin mode (DECLRMM), VT420 and up. */
				if (lastch == 'h') {
					self->at_scroll_ec &= ~HORIZONTAL_MARGIN_DISABLE_BIT;
				} else {
					self->at_scroll_ec |= HORIZONTAL_MARGIN_DISABLE_BIT;
				}
				break;

			case 1000:
				setttymode(self, (self->at_ttymode & ~ANSITTY_MODE_MOUSEON_MASK) |
				                 (lastch == 'h' ? ANSITTY_MODE_MOUSEON_YES
				                                : ANSITTY_MODE_MOUSEON_NO));
				break;

			case 1002:
				setttymode(self, (self->at_ttymode & ~ANSITTY_MODE_MOUSEON_MASK) |
				                 (lastch == 'h' ? ANSITTY_MODE_MOUSEON_WITHMOTION
				                                : ANSITTY_MODE_MOUSEON_NO));
				break;

//			case 1004: /* \e[?1004h focus notify enable (causes mac os terminal to "alert" when  gaining/loosing focus) */
//			           /* \e[?1004l focus notify disable */

			case 1049:
				if (lastch == 'h') {
					CLS(ANSITTY_CLS_ALL);
					SETCURSOR(0, 0, true);
				}
				break;

			} ARGUMENT_CODE_QSWITCH_ELSE() {

			case 0:
				/* Must be ignored. */
				break;

//			case 1:  /* \e[1h   GATM  Guarded Area Transmit Mode, send all (VT132) */
//			         /* \e[1l         Transmit only unprotected characters (VT132) GATM */

			case 2:  /* \e[2h   KAM   Keyboard Action Mode, disable keyboard input */
			         /* \e[2l         Enable input from keyboard KAM */
				if (self->at_ops.ato_termios) {
					struct termios oldios, newios;
					for (;;) {
						(*self->at_ops.ato_termios)(self, &oldios, NULL);
						memcpy(&newios, &oldios, sizeof(struct termios));
						if (lastch == 'h') {
							/* Disable __IIOFF */
							if (!(newios.c_iflag & __IIOFF))
								break;
							newios.c_iflag &= ~__IIOFF;
						} else {
							/* Enable __IIOFF */
							if (newios.c_iflag & __IIOFF)
								break;
							newios.c_iflag |= __IIOFF;
						}
						if ((*self->at_ops.ato_termios)(self, &oldios, &newios))
							break;
					}
				}
				break;

			case 3:  /* \e[3h   CRM   Control Representation Mode, show all control chars */
			         /* \e[3l         Control characters are not displayable characters CRM */
				if (lastch == 'h') {
					self->at_ttyflag |= ANSITTY_FLAG_CRM;
				} else {
					self->at_ttyflag &= ~ANSITTY_FLAG_CRM;
				}
				self->at_state = self->at_codepage == CP_UTF8
				                 ? STATE_TEXT_UTF8
				                 : STATE_TEXT;
				break;

			case 4:  /* \e[4h   IRM   Insertion/Replacement Mode, set insert mode (VT102) */
			         /* \e[4l         Reset to replacement mode (VT102) IRM */
				if (lastch == 'h') {
					self->at_ttyflag |= ANSITTY_FLAG_INSERT;
					self->at_state = STATE_INSERT_UTF8;
				} else {
					self->at_ttyflag &= ~ANSITTY_FLAG_INSERT;
					self->at_state = self->at_codepage == CP_UTF8
					                 ? STATE_TEXT_UTF8
					                 : STATE_TEXT;
				}
				break;

//			case 5:  /* \e[5h   SRTM  Status Report Transfer Mode, report after DCS */
//			         /* \e[5l         Report only on command (DSR) SRTM */
//			case 6:  /* \e[6h   ERM   ERasure Mode, erase protected and unprotected */
//			         /* \e[6l         erase only unprotected fields ERM */
//			case 7:  /* \e[7h   VEM   Vertical Editing Mode, IL/DL affect previous lines */
//			         /* \e[7l         IL/DL affect lines after current line VEM */

			case 10: /* \e[10h   HEM  Horizontal Editing mode, ICH/DCH/IRM go backwards */
			         /* \e[10l        ICH and IRM shove characters forward, DCH pulls HEM */
				if (lastch == 'h') {
					self->at_ttyflag |= ANSITTY_FLAG_HEDIT;
				} else {
					self->at_ttyflag &= ~ANSITTY_FLAG_HEDIT;
				}
				break;

			case 11: /* \e[11h   PUM  Positioning Unit Mode, use decipoints for HVP/etc */
			         /* \e[11l        Use character positions for HPA/HPR/VPA/VPR/HVP PUM */
				if (lastch != 'l')
					goto nope;
				break;

			case 12: /* \e[12h   SRM  Send Receive Mode, transmit without local echo */
			         /* \e[12l        Local echo - input from keyboard sent to screen SRM */
				if (self->at_ops.ato_termios) {
					struct termios oldios, newios;
					for (;;) {
						(*self->at_ops.ato_termios)(self, &oldios, NULL);
						memcpy(&newios, &oldios, sizeof(struct termios));
						if (lastch == 'h') {
							/* Disable ECHO */
							if (!(newios.c_lflag & ECHO))
								break;
							newios.c_lflag &= ~ECHO;
						} else {
							/* Enable ECHO */
							if (newios.c_lflag & ECHO)
								break;
							newios.c_lflag |= ECHO;
						}
						if ((*self->at_ops.ato_termios)(self, &oldios, &newios))
							break;
					}
				}
				break;

//			case 13: /* \e[13h   FEAM Format Effector Action Mode, FE's are stored */
//			         /* \e[13l        HPA/VPA/SGR/etc are acted upon when received FEAM */
//			case 14: /* \e[14h   FETM Format Effector Transfer Mode, send only if stored */
//			         /* \e[14l        Format Effectors are sent to the printer FETM */
//			case 15: /* \e[15h   MATM Multiple Area Transfer Mode, send all areas */
//			         /* \e[15l        Send only current area if SATM is reset MATM */
//			case 16: /* \e[16h   TTM  Transmit Termination Mode, send scrolling region */
//			         /* \e[16l        Transmit partial page, up to cursor position TTM */
//			case 17: /* \e[17h   SATM Send Area Transmit Mode, send entire buffer */
//			         /* \e[17l        Transmit areas bounded by SSA/ESA/DAQ SATM */
//			case 18: /* \e[18h   TSM  Tabulation Stop Mode, lines are independent */
//			         /* \e[18l        Setting a tab stop on one line affects all lines TSM */
//			case 19: /* \e[19h   EBM  Editing Boundry Mode, all of memory affected */
//			         /* \e[19l        Insert does not overflow to next page EBM */

			case 20: /* \e[20h   LNM  Linefeed newline mode (sets the `ONLCR' bit, and clear `ONLRET') */
			         /* \e[20l        Linefeed normal mode (clear the `ONLCR' bit) */
				if (self->at_ops.ato_termios) {
					struct termios oldios, newios;
					for (;;) {
						(*self->at_ops.ato_termios)(self, &oldios, NULL);
						memcpy(&newios, &oldios, sizeof(struct termios));
						if (lastch == 'h') {
							newios.c_oflag |= ONLCR;
							newios.c_oflag &= ~ONLRET;
						} else {
							newios.c_oflag &= ~ONLCR;
						}
						if (newios.c_oflag == oldios.c_oflag)
							break;
						if ((*self->at_ops.ato_termios)(self, &oldios, &newios))
							break;
					}
				}
				break;

			}
			ARGUMENT_CODE_QSWITCH_END()
		}
		break;

#if 0
	case 'i':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_QSWITCH_BEGIN() {

			case 0: /* \e[?0i Graphics screen dump goes to graphics printer VT125,VT240 */
			case 1: /* \e[?1i Print cursor line, terminated by CR LF */
			case 2: /* \e[?2i Graphics screen dump goes to host computer VT125,VT240 */
			case 3: /* \e[?4i Disable auto print */
			case 4: /* \e[?5i Auto print, send a line at a time when linefeed received */

			} ARGUMENT_CODE_QSWITCH_ELSE() {

			case 0: /* \e[0i  Send contents of text screen to printer */
			case 1: /* \e[1i  Fill screen from auxiliary input (printer's keyboard) */
			case 2: /* \e[2i  Send screen to secondary output device */
			case 3: /* \e[3i  Fill screen from secondary input device */

			case 4: /* \e[4i  Turn on copying received data to primary output (VT125) */
			        /* \e[4i  Received data goes to VT102 screen, not to its printer */
			case 5: /* \e[5i  Turn off copying received data to primary output (VT125) */
			        /* \e[5i  Received data goes to VT102's printer, not its screen */
			case 6: /* \e[6i  Turn off copying received data to secondary output (VT125) */
			case 7: /* \e[7i  Turn on copying received data to secondary output (VT125) */

			}
			ARGUMENT_CODE_QSWITCH_END()
		}
		break;
#endif

#if 0
	case 'j':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_QSWITCH_BEGIN() {

			case 20: /* \e[?20j Portrait    Extended N. American letter Yes */
			case 21: /* \e[?21j Landscape   Extended N. American letter Yes */
			case 22: /* \e[?22j Portrait    Extended A4 Yes */
			case 23: /* \e[?23j Landscape   Extended A4 Yes */
			case 24: /* \e[?24j Portrait    Extended Legal Yes */
			case 25: /* \e[?25j Landscape   Extended Legal Yes */
			case 26: /* \e[?26j Portrait    Extended B Yes */
			case 27: /* \e[?27j Landscape   Extended B Yes */

			} ARGUMENT_CODE_QSWITCH_ELSE() {

			case 0:  /* \e[0j   Portrait    Normal text N. American letter No */
			case 1:  /* \e[1j   Landscape   Normal text N. American letter No */
			case 2:  /* \e[2j   Portrait    Normal A4 No */
			case 3:  /* \e[3j   Landscape   Normal A4 No */
			case 4:  /* \e[4j   Portrait    Normal N. American letter No */
			case 5:  /* \e[5j   Landscape   Normal N. American letter No */
			case 6:  /* \e[6j   Portrait    Extended A4 No */
			case 7:  /* \e[7j   Landscape   Extended A4 No */
			case 8:  /* \e[8j   Portrait    Extended Legal No */
			case 9:  /* \e[9j   Landscape   Extended Legal No */

			}
			ARGUMENT_CODE_QSWITCH_END()
		}
		break;
#endif

	case 'm':
		if (!arglen) {
			setcolor(self, self->at_defcolor);
			setattrib(self, ANSITTY_ATTRIB_DEFAULT);
			setflags(self, self->at_ttyflag & ~ANSITTY_FLAG_RENDERMASK);
		} else {
			ARGUMENT_CODE_SWITCH_BEGIN() {

			case 0: /* Reset colors and text attributes */
				setcolor(self, self->at_defcolor);
				setattrib(self, ANSITTY_ATTRIB_DEFAULT);
				setflags(self, self->at_ttyflag & ~ANSITTY_FLAG_RENDERMASK);
				break;

			case 1: /* Brighten foreground output color */
				setcolor(self, self->at_color | ANSITTY_IFSTRONG);
				self->at_ttyflag |= ANSITTY_FLAG_COLORBOLD;
				break;

			case 2: /* Darken foreground output color */
				setcolor(self, self->at_color & ~ANSITTY_IFSTRONG);
				self->at_ttyflag &= ~ANSITTY_FLAG_COLORBOLD;
				break;

			case 3:
				setattrib(self, self->at_attrib | ANSITTY_ATTRIB_ITALIC);
				break;

			case 4:
				setattrib(self, self->at_attrib | ANSITTY_ATTRIB_UNDERLINE);
				break;

			case 5:
			case 6:
				setattrib(self, self->at_attrib | ANSITTY_ATTRIB_BLINK);
				break;

			case 7:
			case 27:
				setcolor(self,
				         ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_BG(self->at_color),
				                               ANSITTY_PALETTE_INDEX_FG(self->at_color)));
				break;

			case 8:
				setflags(self, self->at_ttyflag | ANSITTY_FLAG_CONCEIL);
				break;

			case 9:
				setattrib(self, self->at_attrib | ANSITTY_ATTRIB_STRIKETHROUGH);
				break;

			case 10 ... 19:
				/* Alternate font selection */
				setattrib(self, (self->at_attrib & ~ANSITTY_ATTRIB_FONTMASK) |
				                (uint16_t)(code - 10) << ANSITTY_ATTRIB_FONTSHFT);
				break;

			case 20:
				/* Fracture (ignored) */
				break;

			case 21:
			case 22:
				setcolor(self,
				         (self->at_color & ~ANSITTY_IFSTRONG) |
				         (self->at_defcolor & ANSITTY_IFSTRONG));
				break;

			case 23:
				setattrib(self, self->at_attrib & ~ANSITTY_ATTRIB_ITALIC);
				break;

			case 24:
				setattrib(self, self->at_attrib & ~ANSITTY_ATTRIB_UNDERLINE);
				break;

			case 25:
			case 26:
				setattrib(self, self->at_attrib & ~ANSITTY_ATTRIB_BLINK);
				break;

			case 28:
				setflags(self, self->at_ttyflag & ~ANSITTY_FLAG_CONCEIL);
				break;

			case 29:
				setattrib(self, self->at_attrib & ~ANSITTY_ATTRIB_STRIKETHROUGH);
				break;

			case 30 ... 37:
				setcolor(self, ANSITTY_PALETTE_INDEX((code - 30) + ANSITTY_FLAG_GETCOLORSTRONG(self->at_ttyflag),
				                                     ANSITTY_PALETTE_INDEX_BG(self->at_color)));
				break;

			case 40 ... 47:
				setcolor(self, ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(self->at_color),
				                                     code - 40));
				break;

			case 39:
				setcolor(self, ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(self->at_defcolor),
				                                     ANSITTY_PALETTE_INDEX_BG(self->at_color)));
				break;

			case 49:
				setcolor(self, ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(self->at_color),
				                                     ANSITTY_PALETTE_INDEX_BG(self->at_defcolor)));
				break;

			case 38:
			case 48: {
				unsigned int color_mode;
				unsigned int used_color_index;
				if (*_args_end != ';')
					goto nope;
				++_args_end;
				if (*_args_end != '5' && *_args_end != '2')
					goto nope;
				color_mode = *_args_end - '0';
				++_args_end;
				if (*_args_end != ';')
					goto nope;
				++_args_end;
				if (color_mode == 2) {
					unsigned int r, g, b;
					r = strtoui(_args_end, &_args_end, 10);
					if (*_args_end != ';')
						goto nope;
					++_args_end;
					g = strtoui(_args_end, &_args_end, 10);
					if (*_args_end != ';')
						goto nope;
					++_args_end;
					b = strtoui(_args_end, &_args_end, 10);
					if (*_args_end != ';' && _args_end != arg + arglen)
						goto nope;
					++_args_end;
					if unlikely(r > 0xff)
						r = 0xff;
					if unlikely(g > 0xff)
						g = 0xff;
					if unlikely(b > 0xff)
						b = 0xff;
					/* True color support (if provided by drivers) */
					if (code == 38) {
						setcolor_rgb_fg(self, (uint8_t)r, (uint8_t)g, (uint8_t)b);
					} else {
						setcolor_rgb_bg(self, (uint8_t)r, (uint8_t)g, (uint8_t)b);
					}
					break;
				} else {
					/*assert(color_mode == 5);*/
					used_color_index = strtoui(_args_end, &_args_end, 10);
					if (*_args_end != ';' && _args_end != arg + arglen)
						goto nope;
				}
				setcolor(self,
				         code == 38
				         ? ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(used_color_index),
				                                 ANSITTY_PALETTE_INDEX_BG(self->at_color))
				         : ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(self->at_color),
				                                 ANSITTY_PALETTE_INDEX_BG(used_color_index)));
			}	break;

			case 51:
				setattrib(self, (self->at_attrib & ~ANSITTY_ATTRIB_CIRCLED) |
				                /*               */ ANSITTY_ATTRIB_FRAMED);
				break;

			case 52:
				setattrib(self, self->at_attrib | (ANSITTY_ATTRIB_FRAMED |
				                                   ANSITTY_ATTRIB_CIRCLED));
				break;

			case 53:
				setattrib(self, self->at_attrib | ANSITTY_ATTRIB_OVERLINE);
				break;

			case 54:
				setattrib(self, self->at_attrib & ~(ANSITTY_ATTRIB_FRAMED |
				                                    ANSITTY_ATTRIB_CIRCLED));
				break;

			case 55:
				setattrib(self, self->at_attrib & ~ANSITTY_ATTRIB_OVERLINE);
				break;

			case 60 ... 65:
				break; /* Ignored... */

			case 90 ... 97:
				setcolor(self,
				         ANSITTY_PALETTE_INDEX((code - 90) + ANSITTY_IFSTRONG -
				                               ANSITTY_FLAG_GETCOLORSTRONG(self->at_ttyflag),
				                               ANSITTY_PALETTE_INDEX_BG(self->at_color)));
				break;

			case 100 ... 107:
				setcolor(self,
				         ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(self->at_color),
				                               (code - 100) + ANSITTY_IFSTRONG));
				break;

			}
			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'n':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_QSWITCH_BEGIN() {

			case 15:
				/* Command to terminal requesting printer status
				 * Return values:
				 *     \e[?10n = OK,
				 *     \e[?11n = not OK,
				 *     \e[?13n = no printer. */
				OUTPUT(CC_SESC "[?13n"); /* no printer */
				break;

			} ARGUMENT_CODE_QSWITCH_ELSE() {

			case 5:
				/* Query Device Status
				 *     \e[0n = Terminal is ready, no malfunctions detected
				 *     \e[1n = Terminal is busy, retry later
				 *     \e[2n = Terminal is busy, it will send DSR when ready
				 *     \e[3n = Malfunction, please try again
				 *     \e[4n = Malfunction, terminal will send DSR when ready */
				OUTPUT(CC_SESC "[0n"); /* We are always ready! */
				break;

			case 6:
				/* DSR */
				if (self->at_ops.ato_output) {
					char buf[COMPILER_LENOF(CC_SESC "[" PRIMAXu ";" PRIMAXu "R")];
					size_t len;
					ansitty_coord_t xy[2];
					GETCURSOR(xy);
					len = sprintf(buf, CC_SESC "[%u;%uR",
					              (unsigned int)(xy[1] + 1),
					              (unsigned int)(xy[0] + 1));
					DOOUTPUT(buf, len);
				}
				break;

			}
			ARGUMENT_CODE_QSWITCH_END()
		}
		break;

	case 'p':
		/* TODO: `CSI > Ps p'      Select if/when the mouse pointer should be hidden */
		/* TODO: `CSI Pl ; Pc " p' DECSCL: Set conformance level */
		if (arglen == 1 && arg[0] == '!') {
			/* `CSI ! p'     DECSTR: Soft terminal reset */
			resetterminal(self, true);
			break;
		}
		if (arglen >= 2 && arg[arglen - 1] == '$') {
			/* `CSI Ps $ p'      DECRQM: Request ANSI mode */
			unsigned int name;
			char *end;
			name = strtoui(arg, &end, 10);
			if (end == arg + arglen - 1) {
				/* reply DECRPM: `CSI Ps; Pm$ y'
				 * PS = ECHO `name'
				 * PM = 0 - not recognized
				 * PM = 1 - set
				 * PM = 2 - reset
				 * PM = 3  - permanently  set
				 * PM = 4 - permanently reset
				 * NOTE: `PS' is the same as in `\e[<PS>h' and `\e[<PS>l' */
				unsigned int result;
				switch (name) {

				case 2:  /* KAM */
					result = 4;
					if (self->at_ops.ato_termios) {
						struct termios ios;
						(*self->at_ops.ato_termios)(self, &ios, NULL);
						result = ios.c_lflag & __IIOFF ? 1 : 2;
					}
					break;

				case 3:  /* CRM */
					result = self->at_ttyflag & ANSITTY_FLAG_CRM ? 1 : 2;
					break;

				case 4:  /* IRM */
					result = self->at_ttyflag & ANSITTY_FLAG_INSERT ? 1 : 2;
					break;

				case 1:  /* GATM */
				case 5:  /* SRTM */
				case 6:  /* ERM */
				case 7:  /* VEM */
				case 11: /* PUM */
				case 13: /* FEAM */
				case 14: /* FETM */
				case 15: /* MATM */
				case 16: /* TTM */
				case 17: /* SATM */
				case 18: /* TSM */
				case 19: /* EBM */
					result = 4; /* Always disabled */
					break;

				case 10: /* HEM */
					result = self->at_ttyflag & ANSITTY_FLAG_HEDIT ? 1 : 2;
					break;

				case 12: /* SRM */
					result = 4;
					if (self->at_ops.ato_termios) {
						struct termios ios;
						(*self->at_ops.ato_termios)(self, &ios, NULL);
						result = ios.c_lflag & ECHO ? 1 : 2;
					}
					break;

				case 20: /* \e[20h   LNM  Linefeed newline mode (sets the `ONLCR' bit, and clear `ONLRET') */
				         /* \e[20l        Linefeed normal mode (clear the `ONLCR' bit) */
					result = 3;
					if (self->at_ops.ato_termios) {
						struct termios ios;
						(*self->at_ops.ato_termios)(self, &ios, NULL);
						result = ios.c_oflag & ONLCR ? 1 : 2;
					}
					break;

				default:
					result = 0;
					break;
				}
				{
					char buf[COMPILER_LENOF(CC_SESC "[" PRIMAXu ";" PRIMAXu "$y")];
					size_t len = sprintf(buf, CC_SESC "[%u;%u$y", name, result);
					DOOUTPUT(buf, len);
				}
			}
		}


		break;

	case 'y':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_SWITCH_BEGIN() {

				/* 2;1:  Confidence power up test (no-op) */
				/* 2;2:  Confidence loopback test (no-op) */
				/* 2;9:  Repeat power up test (no-op) */
				/* 2;10: Repeat loopback test (no-op) */
			case 1:
			case 2:
			case 9:
			case 10:
				break;

			}
			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'q':
		if (arglen == 0) {
			/* ledsoff DECLL0 */
			SETLED(~0xf, 0x0);
		} else {
			ARGUMENT_CODE_SWITCH_BEGIN() {

			case 0:
				/* ledsoff DECLL0 */
				SETLED(~0xf, 0x0);
				break;

			case 1: /* led1 DECLL1 */
			case 2: /* led2 DECLL2 */
			case 3: /* led3 DECLL3 */
			case 4: /* led4 DECLL4 */
				SETLED(~0, 0x01 << (code - 1));
				break;

			case 21: /* led1 DECLL1 */
			case 22: /* led2 DECLL2 */
			case 23: /* led3 DECLL3 */
			case 24: /* led4 DECLL4 */
				SETLED(~(0x01 << (code - 21)), 0);
				break;

			}
			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 's':
		/* DECSLRM */
		if (self->at_scroll_ec & HORIZONTAL_MARGIN_DISABLE_BIT) {
			if (arglen != 0)
				goto nope;
			/* ANSI/VT100: Save Cursor */
			savecursor(self);
		} else {
			/* Set left and right columns of the scroll region */
			ansitty_coord_t startcolumn;
			ansitty_coord_t endcolumn;
			if (!arglen) {
				startcolumn = 0;
				endcolumn   = MAXCOORD;
			} else {
				char *end;
				startcolumn = (ansitty_coord_t)strtou32(arg, &end, 10);
				if (*end != ';')
					goto nope;
				++end;
				if (end == arg + arglen)
					endcolumn = MAXCOORD;
				else {
					endcolumn = (ansitty_coord_t)strtou32(end, &end, 10);
					if (end != arg + arglen)
						goto nope;
				}
				if (startcolumn)
					--startcolumn;
				if (endcolumn)
					--endcolumn;
				if (endcolumn < startcolumn) {
					ansitty_coord_t temp;
					temp = startcolumn;
					startcolumn = endcolumn;
					endcolumn = temp;
				}
			}
			setscrollmargin(self,
			                startcolumn,
			                endcolumn);
		}
		break;

	case 'u': /* ANSI/VT100: Unsave Cursor */
		if (arglen != 0)
			goto nope;
		loadcursor(self);
		break;


	case 'r': { /* VT100: setwin DECSTBM */
		/* Set top and bottom (inclusive) line#s of a window */
		ansitty_coord_t startline;
		ansitty_coord_t endline;
		if (!arglen) {
			startline = 0;
			endline   = MAXCOORD;
		} else {
			char *end;
			startline = (ansitty_coord_t)strtou32(arg, &end, 10);
			if (*end != ';')
				goto nope;
			++end;
			if (end == arg + arglen)
				endline = MAXCOORD;
			else {
				endline = (ansitty_coord_t)strtou32(end, &end, 10);
				if (end != arg + arglen)
					goto nope;
#if 0 /* The bottom-line  is actually  the  index of  the  last
       * line  to-be   included  within   the  scroll   region.
       * As such, we'd have to add +1 onto it later, so we skip
       * that step by never subtracting  1 in the first  place! */
				if (endline)
					--endline;
#endif
			}
			if (startline)
				--startline;
			if (endline < startline) {
				ansitty_coord_t temp;
				temp = startline;
				startline = endline;
				endline = temp;
			}
		}
		setscrollregion(self,
		                startline,
		                endline);
	}	break;

	case 'X': {
		/* CSI Ps X  Erase Ps Character(s) (default = 1) (ECH). */
		unsigned int count, maxerase;
		ansitty_coord_t xy[2];
		ansitty_coord_t sxy[2];
		if (!arglen)
			count = 1;
		else {
			char *end;
			count = strtoui(arg, &end, 10);
			if (end != arg + arglen)
				goto nope;
		}
		/* Erase the next `count' characters within the current line, */
		GETCURSOR(xy);
		GETSIZE(sxy);
		maxerase = (unsigned int)(sxy[0] - xy[0]);
		if (count > maxerase)
			count = maxerase;
		FILLCELL(' ', count);
	}	break;

	default:
		goto nope;
	}
	return true;
nope:
	return false;
}




/* ==================================================================================== */
/* ANSI escape gather parser implementation                                             */
/* ==================================================================================== */

PRIVATE NONNULL((1)) bool CC
ansitty_invoke_string_command(struct ansitty *__restrict self,
                              uintptr_half_t state, size_t len) {
	bool result;
	self->at_escape[len] = 0;
	switch (state) {

	case STATE_OSC:
	case STATE_OSC_ESC:
		result = ansi_OSC(self, (char *)self->at_escape, len);
		break;

	case STATE_DCS:
	case STATE_DCS_ESC:
		result = ansi_DCS(self, (char *)self->at_escape, len);
		break;

	case STATE_SOS:
	case STATE_SOS_ESC:
		result = ansi_SOS(self, (char *)self->at_escape, len);
		break;

	case STATE_PM:
	case STATE_PM_ESC:
		result = ansi_PM(self, (char *)self->at_escape, len);
		break;

	case STATE_APC:
	case STATE_APC_ESC:
		result = ansi_APC(self, (char *)self->at_escape, len);
		break;

	default:
		__builtin_unreachable();
	}
	return result;
}

PRIVATE NOBLOCK ATTR_CONST char
NOTHROW(CC get_string_command_start_character)(uintptr_t state) {
	char result;
	switch (state) {

	case STATE_OSC:
	case STATE_OSC_ESC:
		result = ']';
		break;

	case STATE_DCS:
	case STATE_DCS_ESC:
		result = 'P';
		break;

	case STATE_SOS:
	case STATE_SOS_ESC:
		result = 'X';
		break;

	case STATE_PM:
	case STATE_PM_ESC:
		result = '^';
		break;

	case STATE_APC:
	case STATE_APC_ESC:
		result = '_';
		break;

	default:
		__builtin_unreachable();
	}
	return result;
}


/* Output a single utf-8 character to the given TTY */
INTERN NONNULL((1)) void CC
libansitty_putc(struct ansitty *__restrict self, /*utf-8*/ char ch) {
	uintptr_half_t state;
again:
	state = ATOMIC_READ(self->at_state);
	switch (__builtin_expect(state, STATE_TEXT_UTF8)) {

	case STATE_TEXT_UTF8:
		/* Check for the escape character */
		switch ((uint8_t)ch) {

		case CC_NUL:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM)
				PUTUNILAST(0x2400);
			/* NUL should be ignored by ansi ttys in all situations. */
			break;

		case CC_ESC:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM)
				PUTUNILAST(0x241b);
			self->at_state = STATE_ESC;
			break;

		case CC_ENQ:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM)
				PUTUNILAST(0x2405);
			/* Return Terminal Status (which defaults to an empty string) */
			break;

		case CC_SO:
		case CC_SI:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM)
				PUTUNILAST(0x2400 + (uint8_t)ch);
			/* Standard/Alternate character set??? */
			break;

		case CC_CAN:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM)
				PUTUNILAST(0x2418);
			break; /* Ignore... */

		case 0x80 ... 0xff: {
			uint8_t len;
			/* Begin a new multi-byte character sequence. */
			len = unicode_utf8seqlen[(byte_t)ch];
			if unlikely(!len)
				goto do_putuni; /* Invalid utf-8 byte... (simply re-output, thus ignoring the error) */
			assert(len != 1);
			self->at_escwrd[0] = len;
			self->at_escwrd[1] = 1;
			self->at_escape[0] = (byte_t)ch;
			self->at_state     = STATE_TEXT_UTF8_MBS;
		}	break;

		case CC_VT:
		case CC_FF:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM) {
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				PUTUNILAST(0x2400 + (uint8_t)ch);
				SETCURSOR(xy[0], xy[1], false);
			}
			PUTUNI(CC_LF);
			break;

		case CC_BS:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM) {
				PUTUNI(CC_BS);
				PUTUNILAST(0x2408);
			}
			PUTUNI(CC_BS);
			break;

		case CC_BEL:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM)
				PUTUNILAST(0x2400 + (uint8_t)ch);
			PUTUNI(CC_BEL);
			break;

		case CC_TAB:
		case CC_CR:
		case CC_LF:
			if unlikely(self->at_ttyflag & ANSITTY_FLAG_CRM) {
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				PUTUNILAST(0x2400 + (uint8_t)ch);
				SETCURSOR(xy[0], xy[1], false);
			}
			PUTUNI((char32_t)(uint8_t)ch);
			break;

		case 0x01: case 0x02: case 0x03: case 0x04:
		case 0x06: case 0x11: case 0x12: case 0x13:
		case 0x14: case 0x15: case 0x16: case 0x17:
		case 0x19: case 0x1a: case 0x1c: case 0x1d:
		case 0x1e: case 0x1f:
			/* Misc. control characters */
			if (self->at_ttyflag & ANSITTY_FLAG_CRM)
				PUTUNILAST(0x2400 + (uint8_t)ch);
			break;

		case 0x7f: /* DEL */
			if (self->at_ttyflag & ANSITTY_FLAG_CRM)
				PUTUNILAST(0x2421);
			break;

		case CC_SPC:
			if (self->at_ttyflag & ANSITTY_FLAG_CRM) {
				PUTUNILAST(0x2420);
				break;
			}
			ATTR_FALLTHROUGH
		default:
			/* Output a regular, old ASCII character. */
do_putuni:
			PUTUNILAST((char32_t)(uint8_t)ch);
			break;
		}
		break;

	case STATE_INSERT_UTF8: {
		uint8_t len;
		/* Check for the escape character */
		if (handle_control_character(self, (uint8_t)ch))
			break;
		if ((uint8_t)ch <= 0x7f) {
			/* Output a regular, old ASCII character. */
do_insuni:
			ansitty_do_insert_unicode(self, (char32_t)(uint8_t)ch);
			break;
		}
		/* Begin a new multi-byte character sequence. */
		len = unicode_utf8seqlen[(byte_t)ch];
		if unlikely(!len)
			goto do_insuni; /* Invalid utf-8 byte... (simply re-output, thus ignoring the error) */
		assert(len != 1);
		self->at_escwrd[0] = len;
		self->at_escwrd[1] = 1;
		self->at_escape[0] = (byte_t)ch;
		self->at_state     = STATE_INSERT_UTF8_MBS;
	}	break;

	case STATE_TEXT_UTF8_MBS:
	case STATE_INSERT_UTF8_MBS:
		ansitty_pututf8_mbs(self, state, ch);
		break;

	case STATE_INSERT: {
		char32_t uni = cp_decode((uint8_t)ch, self);
		if (handle_control_character(self, uni))
			break;
		ansitty_do_insert_unicode(self, uni);
	}	break;

	case STATE_TEXT: {
		char32_t uni = cp_decode((uint8_t)ch, self);
		if (handle_control_character(self, uni))
			break;
		PUTUNILAST(uni);
	}	break;

	case STATE_ESC:
		switch (ch) {

		case 'A':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursorup */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				if (xy[1] != 0)
					SETCURSOR(xy[0], xy[1] - 1, true);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'B':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursordn */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				SETCURSOR(xy[0], xy[1] + 1, true);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'C':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursorrt */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				SETCURSOR(xy[0] + 1, xy[1], true);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'D':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursorlf */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				if (xy[0] != 0)
					SETCURSOR(xy[0] - 1, xy[1], true);
				goto set_text_and_done;
			} else {
				/* IND */
				/* Move/scroll window up one line */
				SCROLL(1);
				ansitty_setstate_text(self);
			}
			goto unknown_character_after_esc;

		case '<':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: setansi */
				self->at_ttyflag &= ~ANSITTY_FLAG_VT52;
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'F':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: setgr */
				/* Use special graphics character set (XXX: Is this correct?) */
				goto enable_box_mode;
			}
			goto unknown_character_after_esc;

		case 'G':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: resetgr */
				/* Use normal US/UK character set (XXX: Is this correct?) */
				goto setcp_USASCII;
			}
			goto unknown_character_after_esc;

		case 'H':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursorhome */
				SETCURSOR(0, 0, true);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'I':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: revindex */
				/* Generate a reverse line-feed (XXX: Is this correct?) */
				SCROLL(-1);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'K':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cleareol */
				EL(ANSITTY_EL_AFTER);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'J':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cleareos */
				CLS(ANSITTY_CLS_AFTER);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'Z':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				do_ident_DA(self);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case '=':
			/* Application Keypad (DECKPAM). */
			self->at_ttyflag |= ANSITTY_FLAG_ENABLE_APP_KEYPAD;
			goto set_text_and_done;

		case '>':
			/* Normal Keypad (DECKPNM) */
			self->at_ttyflag &= ~ANSITTY_FLAG_ENABLE_APP_KEYPAD;
			goto set_text_and_done;

		case 'M': /* RI */
			/* Move/scroll window down one line */
			SCROLL(-1);
			goto set_text_and_done;

		case 'E': /* NEL */
			/* Move to next line */
			PUTUNI(CC_LF);
			goto set_text_and_done;

		case '(':
			self->at_state = STATE_LPAREN;
			break;

		case '7':
			savecursor(self);
			goto set_text_and_done;

		case '8':
			loadcursor(self);
			goto set_text_and_done;

		case ']': /* OSC */
			self->at_state  = STATE_OSC;
			self->at_esclen = 0;
			break;

		case 'P': /* DCS */
			self->at_state  = STATE_DCS;
			self->at_esclen = 0;
			break;

		case 'X': /* SOS */
			self->at_state  = STATE_SOS;
			self->at_esclen = 0;
			break;

		case '^': /* PM */
			self->at_state  = STATE_PM;
			self->at_esclen = 0;
			break;

		case '_': /* APC */
			self->at_state  = STATE_APC;
			self->at_esclen = 0;
			break;

		case '5':
			self->at_state = STATE_ESC_5;
			break;

		case '6':
			self->at_state = STATE_ESC_6;
			break;

		case '#':
			self->at_state = STATE_ESC_POUND;
			break;

		case '\\': /* String terminator. */
			goto set_text_and_done;

		case 'g': /* screen(1): Visual Bell */
			PUTUNI(CC_BEL);
			goto set_text_and_done;

		case 'Y':
			self->at_state = STATE_ESC_Y1;
			break;

		case 'c':
			/* RIS: Reset graphics, tabs, font and color. */
			resetterminal(self, false);
			goto set_text_and_done;

		case '[':
			self->at_esclen = 0;
			self->at_state  = STATE_CSI;
			break;

		case CC_NUL:
			/* NUL should be ignored by ansi ttys in all situations. */
			break;

		case CC_CAN: /* Cancel */
set_text_and_done:
			ansitty_setstate_text(self);
			break;

		default:
unknown_character_after_esc:
			WARN_UNKNOWN_SEQUENCE1(ch);
			goto reset_state;
		}
		break;

	case STATE_LPAREN:
		switch (ch) {

		case '0': /* DEC Special Character and Line Drawing Set, VT100. */
enable_box_mode:
			SET_CP(CP_LDM);
			break;

		case 'A': /* United Kingdom (UK), VT100. */
			SET_CP(CP_LATIN1);
			break;

		case 'B': /* United States (USASCII), VT100. */
setcp_USASCII:
			self->at_codepage = CP_UTF8;
			self->at_state    = STATE_TEXT_UTF8;
			if (self->at_ttyflag & ANSITTY_FLAG_INSERT)
				self->at_state = STATE_INSERT_UTF8;
			break;

		case '4': /* Dutch, VT200. */
			SET_CP(CP_DUTCH);
			break;

		case 'C': /* Finnish, VT200. */
		case '5': /* Finnish, VT200. */
			SET_CP(CP_FINNISH);
			break;

		case 'R': /* French, VT200. */
		case 'f': /* French, VT200. */
			SET_CP(CP_FRENCH);
			break;

		case 'Q': /* French Canadian, VT200. */
		case '9': /* French Canadian, VT200. */
			SET_CP(CP_FRENCH_CANADIAN);
			break;

		case 'K': /* German, VT200. */
			SET_CP(CP_GERMAN);
			break;

		case 'Y': /* Italian, VT200. */
			SET_CP(CP_ITALIAN);
			break;

		case '`': /* Norwegian, VT200. */
		case 'E': /* Norwegian, VT200. */
		case '6': /* Norwegian, VT200. */
			SET_CP(CP_NORWEGIAN);
			break;

		case 'T': /* Spanish, VT200. */
			SET_CP(CP_SPANISH);
			break;

		case 'H': /* Swedish, VT200. */
		case '7': /* Swedish, VT200. */
			SET_CP(CP_SWEDISH);
			break;

		case '=': /* Swiss, VT200. */
			SET_CP(CP_SWISS);
			break;

		case '%':
			self->at_state = STATE_LPAREN_PERCENT;
			break;

		case CC_NUL:
			/* NUL should be ignored by ansi ttys in all situations. */
			break;

		case CC_CAN: /* Cancel */
			goto set_text_and_done;

		default:
			WARN_UNKNOWN_SEQUENCE2('(', ch);
			goto reset_state;
		}
		break;

	case STATE_LPAREN_PERCENT:
		switch (ch) {

		case '6': /* Portuguese, VT300. */
			SET_CP(CP_PORTUGUESE);
			break;

		case 'G':
			/* UTF-8 (referenced here: https://man7.org/linux/man-pages/man7/utf-8.7.html) */
			SET_CP(CP_UTF8);
			break;

//		case '@':
//			/* ISO-2022-* (referenced here: https://man7.org/linux/man-pages/man7/utf-8.7.html) */
//			SET_CP(???);
//			break;

		case CC_NUL:
			/* NUL should be ignored by ansi ttys in all situations. */
			break;

		case CC_CAN: /* Cancel */
			goto set_text_and_done;

		default:
			WARN_UNKNOWN_SEQUENCE3C('(', '%', ch);
			goto reset_state;
		}
		break;


	case STATE_CSI: {
		size_t len;
		len = self->at_esclen;
		if unlikely(len >= COMPILER_LENOF(self->at_escape))
			RACE(set_text_and_done);
		if (ch >= ANSI_LOW && ch <= ANSI_HIGH) {
			/* Process escape argument. */
do_process_csi:
			self->at_escape[len] = 0;
			ansitty_setstate_text(self);
			if (!ansi_CSI(self, (char *)self->at_escape, len, ch)) {
				WARN_UNKNOWN_SEQUENCE3('[', len, self->at_escape, ch);
				goto set_text_and_done;
			}
			break;
		}
		if (ch == CC_CAN) /* Cancel */
			goto set_text_and_done;
		if (ch == CC_NUL) /* Ignored */
			break;
		self->at_escape[len++] = (byte_t)ch;
		self->at_esclen = len;
		if unlikely(len >= COMPILER_LENOF(self->at_escape)) {
			assert(len == COMPILER_LENOF(self->at_escape));
			goto do_process_csi;
		}
	}	break;

	case STATE_OSC_ESC:
	case STATE_DCS_ESC:
	case STATE_SOS_ESC:
	case STATE_PM_ESC:
	case STATE_APC_ESC: {
		size_t len;
		len = self->at_esclen;
		if unlikely(len >= COMPILER_LENOF(self->at_escape))
			RACE(set_text_and_done);
		if ((byte_t)ch == '\\') {
			if (!ansitty_invoke_string_command(self, state, len)) {
				WARN_UNKNOWN_SEQUENCE4(get_string_command_start_character(state),
				                       len, self->at_escape, CC_ESC, ch);
			}
			goto set_text_and_done;
		} else if (ch == CC_CAN) { /* Cancel */
			goto set_text_and_done;
		} else if (ch == CC_NUL) { /* Ignored */
			break;
		}
		self->at_escape[len++] = CC_ESC;
		self->at_esclen = len;
		if unlikely(len >= COMPILER_LENOF(self->at_escape))
			goto do_process_string_command;
		self->at_escape[len++] = (byte_t)ch;
		self->at_esclen = len;
		if unlikely(len >= COMPILER_LENOF(self->at_escape))
			goto do_process_string_command;
		self->at_state = STATE_OSC_DEL_ESC(state);
		break;

	case STATE_OSC:
	case STATE_DCS:
	case STATE_SOS:
	case STATE_PM:
	case STATE_APC:
		len = self->at_esclen;
		if unlikely(len >= COMPILER_LENOF(self->at_escape))
			RACE(set_text_and_done);
		if ((byte_t)ch == CC_BEL) {
do_process_string_command:
			if (!ansitty_invoke_string_command(self, state, len)) {
				WARN_UNKNOWN_SEQUENCE3(get_string_command_start_character(state),
				                       len, self->at_escape, CC_BEL);
			}
			goto set_text_and_done;
		} else if ((byte_t)ch == CC_ESC) {
			self->at_state = STATE_OSC_ADD_ESC(state);
			break;
		} else if (ch == CC_CAN) { /* Cancel */
			goto set_text_and_done;
		} else if (ch == CC_NUL) { /* Ignored */
			break;
		}
		self->at_escape[len++] = (byte_t)ch;
		self->at_esclen = len;
		if unlikely(len >= COMPILER_LENOF(self->at_escape)) {
			assert(len == COMPILER_LENOF(self->at_escape));
			goto do_process_string_command;
		}
	}	break;

	case STATE_ESC_5:
		if (ch == 'n') {
			/* VT100: devstat DSR */
			/* termok DSR  --- Response: terminal is OK */
			OUTPUT(CC_SESC "0n");
			goto set_text_and_done;
		} else if (ch == CC_CAN) {
			goto set_text_and_done;
		} else if (ch == CC_NUL) { /* Ignored */
			break;
		}
		WARN_UNKNOWN_SEQUENCE2('5', ch);
		goto reset_state;

	case STATE_ESC_6:
		if (ch == 'n') {
			char buf[COMPILER_LENOF(CC_SESC PRIMAXu ";" PRIMAXu "R")];
			ansitty_coord_t xy[2];
			size_t len;
			/* VT100: getcursor DSR */
			/* Response: cursor is at v,h */
			GETCURSOR(xy);
			len = sprintf(buf, CC_SESC "%u;%uR",
			              (unsigned int)(xy[1] + 1),
			              (unsigned int)(xy[0] + 1));
			DOOUTPUT(buf, len);
			goto set_text_and_done;
		} else if (ch == CC_CAN) {
			goto set_text_and_done;
		} else if (ch == CC_NUL) { /* Ignored */
			break;
		}
		WARN_UNKNOWN_SEQUENCE2('6', ch);
		goto reset_state;

	case STATE_ESC_POUND:
		switch (ch) {

		case '3':
			/* VT100: dhtop DECDHL (Double-height letters, top half) */
			setattrib(self, (self->at_attrib & ~ANSITTY_ATTRIB_LET_MASK) | ANSITTY_ATTRIB_LET_DHTP);
			goto set_text_and_done;

		case '4':
			/* VT100: dhbot DECDHL (Double-height letters, bottom half) */
			setattrib(self, (self->at_attrib & ~ANSITTY_ATTRIB_LET_MASK) | ANSITTY_ATTRIB_LET_DHBP);
			goto set_text_and_done;

		case '5':
			/* VT100: swsh DECSWL  (Single width, single height letters) */
			setattrib(self, (self->at_attrib & ~ANSITTY_ATTRIB_LET_MASK) | ANSITTY_ATTRIB_LET_SWSH);
			goto set_text_and_done;

		case '6':
			/* VT100: dwsh DECDWL  (Double width, single height letters) */
			setattrib(self, (self->at_attrib & ~ANSITTY_ATTRIB_LET_MASK) | ANSITTY_ATTRIB_LET_DWSH);
			goto set_text_and_done;

		case '8':
			/* VT100: align DECALN */
			/* Screen alignment display (whatever that is) */
			/* screen(1) documents this one as:
			 *     ESC # 8               (V)  Fill Screen with E's
			 * So  I guess that's a simple enough explanation, although I'm not
			 * entirely  sure if there's  some kind of joke  I'm missing, or if
			 * this one's _literally_ supposed?? to fill the entire screen with
			 * all E's (I mean: don't get me  wrong. How often didn't I want  a
			 * screen full of E's, wishing there  was an easier way of  getting
			 * them all...)
			 * -> I've just checked with putty, and yes: It literally fills
			 *    the  tty  with  all  E's.  As  dumb  as  that   sounds... */
			{
				ansitty_coord_t xy[2];
				ansitty_coord_t sxy[2];
				GETCURSOR(xy);
				GETSIZE(sxy);
				SETCURSOR(0, 0, false);
				FILLCELL('E', sxy[0] * sxy[1]);
				SETCURSOR(xy[0], xy[1], false);
			}
			goto set_text_and_done;

		case CC_NUL:
			/* NUL should be ignored by ansi ttys in all situations. */
			break;

		case CC_CAN:
			goto reset_state;

		default:
			break;
		}
		WARN_UNKNOWN_SEQUENCE2('#', ch);
		goto set_text_and_done;

	case STATE_ESC_Y1:
		if ((byte_t)ch < 32) {
			if (ch == CC_CAN)
				goto set_text_and_done;
			if (ch == CC_NUL) /* Ignored */
				break;
			WARN_UNKNOWN_SEQUENCE2('Y', ch);
			goto reset_state;
		}
		STATE_ESC_Y1_VAL(self) = (uint8_t)ch - 32;
		self->at_state = STATE_ESC_Y2;
		break;

	case STATE_ESC_Y2:
		/* ESC Y Ps Ps    Move the cursor to given row and column.
		 * Parameters for cursor  movement are at  the end of  the ESC Y  escape
		 * sequence. Each ordinate is encoded in a single character as value+32.
		 * For example, ! is 1. The screen coordinate system is 0-based. */
		if ((byte_t)ch < 32) {
			if (ch == CC_CAN)
				goto set_text_and_done;
			if (ch == CC_NUL) /* Ignored */
				break;
			WARN_UNKNOWN_SEQUENCE3C('Y', 32 + STATE_ESC_Y1_VAL(self), ch);
			goto reset_state;
		}

		/* Set the cursor position. */
		SETCURSOR((byte_t)ch - 32, STATE_ESC_Y1_VAL(self), true);
		goto set_text_and_done;


	default:
reset_state:
		ansitty_setstate_text(self);
		goto again;
	}
}

/* Output a single unicode character to the given TTY */
INTERN NONNULL((1)) void CC
libansitty_putuni(struct ansitty *__restrict self, char32_t ch) {
	char utf8_seq[UNICODE_UTF8_CURLEN];
	size_t i, utf8_len;

	/* Simple case: Default state and non-escaping character */
	if (self->at_state == STATE_TEXT_UTF8) {
		if (!handle_control_character(self, ch))
			PUTUNILAST(ch);
		return;
	}

	/* Encode as utf-8 and use `libansitty_putc()'. */
	utf8_len = (size_t)(unicode_writeutf8(utf8_seq, ch) - utf8_seq);
	for (i = 0; i < utf8_len; ++i)
		libansitty_putc(self, utf8_seq[i]);
}

/* pformatprinter-compatible prototype for printing to an ANSI TTY
 * @param: arg: The `struct ansitty *' to which to print.
 * @return: * : Always re-return `(ssize_t)datalen' */
INTERN NONNULL((1)) ssize_t FORMATPRINTER_CC
libansitty_printer(void *arg, char const *data, size_t datalen) {
	size_t i;
	struct ansitty *self;
	self = (struct ansitty *)arg;
	for (i = 0; i < datalen; ++i) {
		libansitty_putc(self, data[i]);
	}
	return (ssize_t)datalen;
}



/* Translate a given unicode input character `ch' (which should originate form
 * the  keyboard) into the sequence of bytes mandated by the code page that is
 * currently being used by the ansitty.
 * @return: * : The number of produced bytes (<= ANSITTY_TRANSLATE_BUFSIZE)
 * @return: 0 : The character cannot be represented in the current CP, and
 *              should be discarded. */
INTERN NOBLOCK NONNULL((1, 2)) size_t
NOTHROW_NCX(CC libansitty_translate)(struct ansitty *__restrict self,
                                     char buf[ANSITTY_TRANSLATE_BUFSIZE],
                                     char32_t ch) {
	size_t result;
	if likely(self->at_codepage == CP_UTF8) {
do_encode_utf8:
		/* Default: Encode a utf-8 character. */
		result = (size_t)(unicode_writeutf8(buf, ch) - buf);
	} else {
		uint8_t cp_byte;
		switch (self->at_codepage) {

		case CP_DUTCH:
			cp_byte = libansitty_encode_cp_dutch(ch);
			break;

		case CP_FINNISH:
			cp_byte = libansitty_encode_cp_finnish(ch);
			break;

		case CP_FRENCH:
			cp_byte = libansitty_encode_cp_french(ch);
			break;

		case CP_FRENCH_CANADIAN:
			cp_byte = libansitty_encode_cp_french_canadian(ch);
			break;

		case CP_GERMAN:
			cp_byte = libansitty_encode_cp_german(ch);
			break;

		case CP_ITALIAN:
			cp_byte = libansitty_encode_cp_italian(ch);
			break;

		case CP_NORWEGIAN:
			cp_byte = libansitty_encode_cp_norwegian(ch);
			break;

		case CP_PORTUGUESE:
			cp_byte = libansitty_encode_cp_portuguese(ch);
			break;

		case CP_SPANISH:
			cp_byte = libansitty_encode_cp_spanish(ch);
			break;

		case CP_SWEDISH:
			cp_byte = libansitty_encode_cp_swedish(ch);
			break;

		case CP_SWISS:
			cp_byte = libansitty_encode_cp_swiss(ch);
			break;

		default:
			goto do_encode_utf8;
		}
		if (!cp_byte)
			return 0;
		buf[0] = (char)cp_byte;
		result = 1;
	}
	return result;
}

/* NOTE: Meta=Gui
 *            Normal  Shft      Ctrl      Shft+Ctrl Meta      Meta+Shft  Meta+Ctrl  Meta+Ctrl+Shft
 *  KEY_F1    \eOP    \e[1;2P~  \e[1;5P~  \e[1;6P~  \e[1;9P~  \e[1;10P~  \e[1;13P~  \e[1;14P~
 *  KEY_F2    \eOQ    \e[1;2Q~  \e[1;5Q~  \e[1;6Q~  \e[1;9Q~  \e[1;10Q~  \e[1;13Q~  \e[1;14Q~
 *  KEY_F3    \eOR    \e[1;2R~  \e[1;5R~  \e[1;6R~  \e[1;9R~  \e[1;10R~  \e[1;13R~  \e[1;14R~
 *  KEY_F4    \eOS    \e[1;2S~  \e[1;5S~  \e[1;6S~  \e[1;9S~  \e[1;10S~  \e[1;13S~  \e[1;14S~
 *  KEY_F5    \e[15~  \e[15;2~  \e[15;5~  \e[15;6~  \e[15;9~  \e[15;10~  \e[15;13~  \e[15;14~
 *  KEY_F6    \e[17~  \e[17;2~  \e[17;5~  \e[17;6~  \e[17;9~  \e[17;10~  \e[17;13~  \e[17;14~
 *  KEY_F7    \e[18~  \e[18;2~  \e[18;5~  \e[18;6~  \e[18;9~  \e[18;10~  \e[18;13~  \e[18;14~
 *  KEY_F8    \e[19~  \e[19;2~  \e[19;5~  \e[19;6~  \e[19;9~  \e[19;10~  \e[19;13~  \e[19;14~
 *  KEY_F9    \e[20~  \e[20;2~  \e[20;5~  \e[20;6~  \e[20;9~  \e[20;10~  \e[20;13~  \e[20;14~
 *  KEY_F10   \e[21~  \e[21;2~  \e[21;5~  \e[21;6~  \e[21;9~  \e[21;10~  \e[21;13~  \e[21;14~
 *  KEY_F11   \e[23~  \e[23;2~  \e[23;5~  \e[23;6~  \e[23;9~  \e[23;10~  \e[23;13~  \e[23;14~
 *  KEY_F12   \e[24~  \e[24;2~  \e[24;5~  \e[24;6~  \e[24;9~  \e[24;10~  \e[24;13~  \e[24;14~
 * NOTE: KEY_F{13-24} are the same as KEY_F{1-12} with inverted shift-modifiers
 * @param: fn: Function key ID (0-based; aka. for KEY_F1, pass `0')
 */
PRIVATE NONNULL((1)) size_t
NOTHROW_NCX(CC encode_function_key)(char *__restrict buf, uint8_t fn, uint16_t mod) {
	size_t result;
	unsigned int keycode;
	unsigned int modcode;
	char endch;
	bool has_shift;
	has_shift = KEYMOD_HASSHIFT(mod);
	if (fn >= 12) {
		/* Extended function keys */
		fn -= 12;
		has_shift = !has_shift;
	}
	if (has_shift) {
		if (KEYMOD_HASGUI(mod)) {
			if (KEYMOD_HASCTRL(mod)) {
				modcode = 14; /* Meta + Ctrl + Shift */
			} else {
				modcode = 10; /* Meta + Shift */
			}
		} else if (KEYMOD_HASCTRL(mod)) {
			modcode = 6; /* Shift + Control */
		} else {
			modcode = 2; /* Shift */
		}
	} else {
		if (KEYMOD_HASGUI(mod)) {
			if (KEYMOD_HASCTRL(mod)) {
				modcode = 13; /* Meta + Ctrl */
			} else {
				modcode = 9; /* Meta */
			}
		} else if (KEYMOD_HASCTRL(mod)) {
			modcode = 5; /* Control */
		} else {
			modcode = 0;
		}
	}
	if (fn < 4) {
		/* F1...F4 */
		endch   = 'P' + fn;
		keycode = 1;
	} else {
		endch = '~';
		if (fn == (5 - 1)) {
			keycode = 15; /* F5 */
		} else if (fn <= (10 - 1)) {
			keycode = 17 + fn - (6 - 1); /* F6...F10 */
		} else {
			keycode = 23 + fn - (11 - 1); /* F11...F12 */
		}
	}
	/* Encode the function key code. */
	if (modcode != 0) {
		result = sprintf(buf, CC_SESC "[%u;%u%c", keycode, modcode, endch);
	} else if (keycode != 1) {
		result = sprintf(buf, CC_SESC "[%u%c", keycode, endch);
	} else {
		result = sprintf(buf, CC_SESC "O%c", endch);
	}
	return result;
}



/* Encode the representation of a misc. keyboard key `key' with `mod',
 * and finalize encoding of certain keyboard characters after  already
 * having been translated through the keymap.
 * @param: self: The ANSITTY to use (or `NULL' to use default settings)
 * @param: key:  The keyboard key (one of `KEY_*' from <kos/keyboard.h>; e.g. `KEY_UP')
 * @param: mod:  Keyboard modifiers (set of `KEYMOD_*' from <kos/keyboard.h>)
 * @param: len:  The # of bytes from `buf' that were previously encoded by the keymap.
 * @return: * :  The number of produced bytes (<= ANSITTY_TRANSLATE_BUFSIZE)
 * @return: 0 :  The key cannot be represented and should be discarded. */
INTERN NOBLOCK NONNULL((2)) size_t
NOTHROW_NCX(CC libansitty_translate_misc)(struct ansitty *self,
                                          char buf[ANSITTY_TRANSLATE_BUFSIZE],
                                          size_t len, uint16_t key, uint16_t mod) {
#define IS_VT52()           (self && (self->at_ttyflag & ANSITTY_FLAG_VT52) != 0)
#define ENABLE_APP_CURSOR() (!!KEYMOD_HASCTRL(mod) ^ !!(self && (self->at_ttyflag & ANSITTY_FLAG_ENABLE_APP_CURSOR) != 0))
#define ENABLE_APP_KEYPAD() (self && (self->at_ttyflag & ANSITTY_FLAG_ENABLE_APP_KEYPAD) != 0)
	size_t result;
	size_t addend;
	if (len != 0) {
		/* Only override keymap settings in certain cases.
		 * Also: In some cases, re-use certain bits of information from the keymap! */
		switch (key) {

		case KEY_KPCOMMA:
		case KEY_KPDOT:
			if (len == 1) {
				/* Deal with internationalization */
				if (buf[0] == '.')
					key = KEY_KPDOT;
				else if (buf[0] == ',') {
					key = KEY_KPCOMMA;
				}
			}
			ATTR_FALLTHROUGH
#ifdef KEY_KPSPACE
		case KEY_KPSPACE:
#endif /* KEY_KPSPACE */
#ifdef KEY_KPTAB
		case KEY_KPTAB:
#endif /* KEY_KPTAB */
		case KEY_KPENTER:
		case KEY_KPASTERISK:
		case KEY_KPPLUS:
		case KEY_KPMINUS:
		case KEY_KPSLASH:
		case KEY_KP0: case KEY_KP1: case KEY_KP2: case KEY_KP3: case KEY_KP4:
		case KEY_KP5: case KEY_KP6: case KEY_KP7: case KEY_KP8: case KEY_KP9:
		case KEY_KPEQUAL:
			if (ENABLE_APP_KEYPAD()) {
				addend = 0;
				/* Prefix with 0x1b (ESC; aka. `\e') */
				if (KEYMOD_HASALT(mod)) {
					*buf++ = CC_ESC;
					addend = 1;
				}
				goto handle_app_keypad;
			}
			break;

		case KEY_ENTER:
		case KEY_SPACE:
		case KEY_TAB:
			/* Force special encoding for these keys under certain conditions */
			if (KEYMOD_HASSHIFT(mod) || KEYMOD_HASCTRL(mod) ||
			    KEYMOD_HASALT(mod) || ENABLE_APP_KEYPAD())
				goto do_handle_key;
			break;

		default:
			break;
		}
		return len;
	}
do_handle_key:
	addend = 0;
	/* Prefix with 0x1b (ESC; aka. `\e') */
	if (KEYMOD_HASALT(mod)) {
		*buf++ = CC_ESC;
		addend = 1;
	}
	switch (key) {

	case KEY_ENTER:
		if (ENABLE_APP_KEYPAD()) {
			buf[2] = 'M';
			if (IS_VT52()) {
				/* ESC ? M */
set_buf_escape_qmark_3:
				buf[1] = '?';
set_buf_escape_3:
				result = 3;
				goto set_buf_escape;
			}
			goto set_buf_escape_O_3; /* ESC O M */
		}
		buf[0] = '\r';
		goto set_result_1;

	case KEY_SPACE:
#if 0 /* Although documented in xterm, nurses doesn't understand this,
       * and terminfo contains no entry (or even definition) for this! */
		if (ENABLE_APP_KEYPAD()) {
			buf[2] = ' ';
			if (IS_VT52())
				goto set_buf_escape_qmark_3; /* ESC ? SP */
			goto set_buf_escape_O_3; /* ESC O SP */
		}
#endif
		buf[0] = ' ';
		goto set_result_1;

	case KEY_TAB:
		if (ENABLE_APP_KEYPAD()) {
			buf[2] = 'I';
			if (IS_VT52())
				goto set_buf_escape_qmark_3; /* ESC ? I */
			/* ESC O I */
set_buf_escape_O_3:
			buf[1] = 'O';
			goto set_buf_escape_3;
		}
		if (KEYMOD_HASSHIFT(mod)) {
			/* Cursor Backward Tabulation */
			buf[2] = 'Z';
			goto set_buf_escape_lbracket_3;
		}
		buf[0] = '\t';
set_result_1:
		result = 1;
		break;

	case KEY_BACKSPACE:
		if (!!KEYMOD_HASCTRL(mod) ^
		    !!(self && (self->at_ttyflag & ANSITTY_FLAG_BACKSPACE_REVERSE) != 0)) {
			buf[0] = 127;
		} else {
			buf[0] = 8;
		}
		result = 1;
		break;

		/* Keypad keys. */
#ifdef KEY_KPSPACE
	case KEY_KPSPACE:     buf[0] = ' '; goto check_app_keypad;
#endif /* KEY_KPSPACE */
#ifdef KEY_KPTAB
	case KEY_KPTAB:       buf[0] = '\t'; goto check_app_keypad;
#endif /* KEY_KPTAB */
	case KEY_KPCOMMA:     buf[0] = ','; goto check_app_keypad;
	case KEY_KPDOT:       buf[0] = '.'; goto check_app_keypad;
	case KEY_KPENTER:     buf[0] = '\r'; goto check_app_keypad;
	case KEY_KPASTERISK:  buf[0] = '*'; goto check_app_keypad;
	case KEY_KPPLUS:      buf[0] = '+'; goto check_app_keypad;
	case KEY_KPMINUS:     buf[0] = '-'; goto check_app_keypad;
	case KEY_KPSLASH:     buf[0] = '/'; goto check_app_keypad;
	case KEY_KP0:         buf[0] = '0'; goto check_app_keypad;
	case KEY_KP1:         buf[0] = '1'; goto check_app_keypad;
	case KEY_KP2:         buf[0] = '2'; goto check_app_keypad;
	case KEY_KP3:         buf[0] = '3'; goto check_app_keypad;
	case KEY_KP4:         buf[0] = '4'; goto check_app_keypad;
	case KEY_KP5:         buf[0] = '5'; goto check_app_keypad;
	case KEY_KP6:         buf[0] = '6'; goto check_app_keypad;
	case KEY_KP7:         buf[0] = '7'; goto check_app_keypad;
	case KEY_KP8:         buf[0] = '8'; goto check_app_keypad;
	case KEY_KP9:         buf[0] = '9'; goto check_app_keypad;
	case KEY_KPEQUAL:     buf[0] = '='; goto check_app_keypad;
check_app_keypad:
		result = 1;
		if (ENABLE_APP_KEYPAD()) {
handle_app_keypad:
			switch (key) {
#ifdef KEY_KPSPACE
			case KEY_KPSPACE:     buf[2] = ' '; break;
#endif /* KEY_KPSPACE */
#ifdef KEY_KPTAB
			case KEY_KPTAB:       buf[2] = 'I'; break;
#endif /* KEY_KPTAB */
			case KEY_KPCOMMA:     buf[2] = 'l'; break;
			case KEY_KPDOT:       buf[2] = 'n'; break;
			case KEY_KPENTER:     buf[2] = 'M'; break;
			case KEY_KPASTERISK:  buf[2] = 'j'; break;
			case KEY_KPPLUS:      buf[2] = 'k'; break;
			case KEY_KPMINUS:     buf[2] = 'm'; break;
			case KEY_KPSLASH:     buf[2] = 'o'; break;
			case KEY_KP0:         buf[2] = 'p'; break;
			case KEY_KP1:         buf[2] = 'q'; break;
			case KEY_KP2:         buf[2] = 'r'; break;
			case KEY_KP3:         buf[2] = 's'; break;
			case KEY_KP4:         buf[2] = 't'; break;
			case KEY_KP5:         buf[2] = 'E'; break; /* 'u'? */
			case KEY_KP6:         buf[2] = 'v'; break;
			case KEY_KP7:         buf[2] = 'w'; break;
			case KEY_KP8:         buf[2] = 'x'; break;
			case KEY_KP9:         buf[2] = 'y'; break;
			case KEY_KPEQUAL:     buf[2] = 'X'; break;
			default: __builtin_unreachable();
			}
			if (IS_VT52()) {
				buf[1] = '?';
/*set_buf_escape_3:*/
				result = 3;
				goto set_buf_escape;
			}
			goto set_buf_escape_O_3;
		}
		if (KEYMOD_HASCTRL(mod)) {
			/* Deal with control characters.
			 * s.a. /kos/src/kernel/core/dev/keyboard.c:get_control_key() */
			switch (buf[0]) {
			case '2': buf[0] = 0x00; break;
			case '3': buf[0] = 0x1b; break;
			case '4': buf[0] = 0x1c; break;
			case '5': buf[0] = 0x1d; break;
			case '6': buf[0] = 0x1e; break;
			case '-':
			case '7': buf[0] = 0x1f; break;
			case '8': buf[0] = 0x7f; break;
			default: break;
			}
		}
		break;

#if 0 /* ??? */
	case KEY_PF1 ... KEY_PF4:
		if (IS_VT52()) {
			buf[1] = 'P' + (key - KEY_PF1);
			goto set_buf_escape_2;
		}
		buf[2] = 'P' + (key - KEY_PF1);
		goto set_buf_escape_O_3;
#endif



	case KEY_F1 ... KEY_F10:
		result = encode_function_key(buf, key - KEY_F1, mod);
		break;
	case KEY_F11 ... KEY_F12:
		result = encode_function_key(buf, key - KEY_F11 + (11 - 1), mod);
		break;

	case KEY_F13 ... KEY_F24:
		result = encode_function_key(buf, key - KEY_F13 + (13 - 1), mod);
		break;

	case KEY_HOME:
	case KEY_FIND:
		buf[2] = 'H';
		/* With modifiers, HOME/END are encoded as:
		 * \e[1;<mod>(H|F) */
set_buf_escape_O_3_or_lbracket_1_semicolon_mod_buf2:
		if (KEYMOD_HASSHIFT(mod)) {
			buf[5] = buf[2];
			buf[2] = '1';
			buf[3] = ';';
			if (KEYMOD_HASGUI(mod)) {
				buf[4] = '1';
				buf[6] = buf[2];
				if (KEYMOD_HASCTRL(mod)) {
					buf[5] = '4'; /* Meta + Ctrl + Shift */
set_buf_escape_lbracket_7:
					result = 7;
					goto set_buf_escape_lbracket;
				}
				buf[5] = '0'; /* Meta + Shift */
				goto set_buf_escape_lbracket_7;
			} else if (KEYMOD_HASCTRL(mod)) {
				buf[4] = '6'; /* Shift + Control */
set_buf_escape_lbracket_6:
				result = 6;
				goto set_buf_escape_lbracket;
			}
			buf[4] = '2'; /* Shift */
			goto set_buf_escape_lbracket_6;
		} else {
			if (KEYMOD_HASGUI(mod)) {
				buf[5] = buf[2];
				buf[2] = '1';
				buf[3] = ';';
				if (KEYMOD_HASCTRL(mod)) {
					buf[6] = buf[5];
					buf[4] = '1';
					buf[5] = '3'; /* Meta + Ctrl */
					goto set_buf_escape_lbracket_7;
				}
				buf[4] = '9'; /* Meta */
				goto set_buf_escape_lbracket_6;
			} else if (KEYMOD_HASCTRL(mod)) {
				buf[5] = buf[2];
				buf[2] = '1';
				buf[3] = ';';
				buf[4] = '5'; /* Control */
				goto set_buf_escape_lbracket_6;
			}
		}
		goto set_buf_escape_O_3;

	case KEY_SELECT:
	case KEY_END:
		buf[2] = 'F'; /* PC-Style */
		goto set_buf_escape_O_3_or_lbracket_1_semicolon_mod_buf2;

	case KEY_INSERT:
		key = 2;
		goto do_1char_tilde_code;

	case KEY_DELETE:
		key = 3;
		goto do_1char_tilde_code;

	case KEY_PREVIOUS:
	case KEY_PAGEUP:
		key = 5;
		goto do_1char_tilde_code;

	case KEY_NEXT:
	case KEY_PAGEDOWN:
		key = 6;
do_1char_tilde_code:
		buf[2] = itoa_decimal(key);
		if (KEYMOD_HASSHIFT(mod)) {
			buf[3] = ';';
			if (KEYMOD_HASGUI(mod)) {
				buf[4] = '1';
				if (KEYMOD_HASCTRL(mod)) {
					buf[5] = '4'; /* Meta + Ctrl + Shift */
set_buf_escape_lbracket_7_tilde_6:
					buf[6] = '~';
					goto set_buf_escape_lbracket_7;
				}
				buf[5] = '0'; /* Meta + Shift */
				goto set_buf_escape_lbracket_7_tilde_6;
			} else if (KEYMOD_HASCTRL(mod)) {
				buf[4] = '6'; /* Shift + Control */
set_buf_escape_lbracket_6_tilde_5:
				buf[5] = '~';
				goto set_buf_escape_lbracket_6;
			}
			buf[4] = '2'; /* Shift */
			goto set_buf_escape_lbracket_6_tilde_5;
		} else {
			if (KEYMOD_HASGUI(mod)) {
				buf[3] = ';';
				if (KEYMOD_HASCTRL(mod)) {
					buf[4] = '1';
					buf[5] = '3'; /* Meta + Ctrl */
					buf[6] = '~';
					goto set_buf_escape_lbracket_7;
				}
				buf[4] = '9'; /* Meta */
				goto set_buf_escape_lbracket_6_tilde_5;
			} else if (KEYMOD_HASCTRL(mod)) {
				buf[3] = ';';
				buf[4] = '5'; /* Control */
				goto set_buf_escape_lbracket_6_tilde_5;
			}
		}
/*set_buf_escape_lbracket_4_tilde_3:*/
		buf[3] = '~';
/*set_buf_escape_lbracket_4:*/
		result = 4;
		goto set_buf_escape_lbracket;


	case KEY_MACRO:
		buf[2] = 'M';
		goto set_buf_escape_lbracket_3;

	case KEY_PAUSE:
		buf[2] = 'P';
set_buf_escape_lbracket_3:
		result = 3;
		goto set_buf_escape_lbracket;

	case KEY_ESC:
/*set_buf_escape_1:*/
		result = 1;
		goto set_buf_escape;

	case KEY_UP:
		buf[2] = 'A';
		goto handle_cursor_key;

	case KEY_DOWN:
		buf[2] = 'B';
		goto handle_cursor_key;

	case KEY_RIGHT:
		buf[2] = 'C';
		goto handle_cursor_key;

	case KEY_LEFT:
		buf[2] = 'D';
handle_cursor_key:
		if (IS_VT52()) {
			/* VT52-specific cursor key encoding */
			buf[1] = buf[2];
/*set_buf_escape_2:*/
			result = 2;
			goto set_buf_escape;
		} else if (ENABLE_APP_CURSOR()) {
			/* Application cursor key mode.
			 * NOTE: When modifiers are present, then  the
			 *       key is encoded as \e[1;<mod>(A|B|C|D) */
			goto set_buf_escape_O_3_or_lbracket_1_semicolon_mod_buf2;
		}
		result = 3;
set_buf_escape_lbracket:
		buf[1] = '[';
set_buf_escape:
		buf[0] = CC_ESC;
		break;

	default:
		/* Key cannot be encoded! */
		return 0;
	}
	return addend + result;
}



DEFINE_PUBLIC_ALIAS(ansitty_init, libansitty_init);
DEFINE_PUBLIC_ALIAS(ansitty_putc, libansitty_putc);
DEFINE_PUBLIC_ALIAS(ansitty_putuni, libansitty_putuni);
DEFINE_PUBLIC_ALIAS(ansitty_printer, libansitty_printer);
DEFINE_PUBLIC_ALIAS(ansitty_translate, libansitty_translate);
DEFINE_PUBLIC_ALIAS(ansitty_translate_misc, libansitty_translate_misc);

DECL_END

#endif /* !GUARD_LIBANSITTY_ANSITTY_C */
