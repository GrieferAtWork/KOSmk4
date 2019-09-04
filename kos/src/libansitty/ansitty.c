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
#ifndef GUARD_LIBANSITTY_ANSITTY_C
#define GUARD_LIBANSITTY_ANSITTY_C 1
#define _KOS_SOURCE 1

#include "api.h"
/**/

#include <hybrid/compiler.h>

#include <assert.h>
#include <string.h>
#include <unicode.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include <libansitty/ansitty.h>
#include <termios.h>

#include "ansitty.h"

#ifdef __KERNEL__
#include <kernel/printk.h>
#else /* __KERNEL__ */
#include <sys/syslog.h>
#endif /* !__KERNEL__ */


DECL_BEGIN

#define CAN  '\030' /* Cancel */
#define BEL  '\7'
#define ESC  '\033' /* '\e' */
#define SESC "\033" /* "\e" */

#if 0
#define TRACE_OPERATION DOTRACE
#else
#define TRACE_OPERATION TRACE
#endif

#ifdef __KERNEL__
#define UNKNOWN_SEQUENCE_WARN(...) printk(KERN_WARNING __VA_ARGS__)
#else /* __KERNEL__ */
#define UNKNOWN_SEQUENCE_WARN(...) syslog(LOG_WARNING, __VA_ARGS__)
#endif /* !__KERNEL__ */
#define WARN_UNKNOWN_SEQUENCE1(firstch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q\"\n", firstch)
#define WARN_UNKNOWN_SEQUENCE2(firstch, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#Q\"\n", firstch, lastch)
#define WARN_UNKNOWN_SEQUENCE3C(firstch, secondch, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#Q%#Q\"\n", firstch, secondch, lastch)
#define WARN_UNKNOWN_SEQUENCE3(firstch, ptr, len, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#$q%#Q\"\n", firstch, (size_t)(len), ptr, lastch)
#define WARN_UNKNOWN_SEQUENCE4C(firstch, secondch, thirdch, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#Q%#Q%#Q\"\n", firstch, secondch, thirdch, lastch)
#define WARN_UNKNOWN_SEQUENCE4(firstch, ptr, len, before_lastch, lastch) \
	UNKNOWN_SEQUENCE_WARN("[ansitty] Unrecognized escape sequence \"\\e%#Q%#$q%#Q%#Q\"\n", firstch, (size_t)(len), ptr, before_lastch, lastch)

#define PUTUNI(uni)                 (*self->at_ops.ato_putc)(self, uni)
#define GETCURSOR(pxy)              ((*self->at_ops.ato_getcursor)(self, pxy), TRACE_OPERATION("getcur:{%u,%u}\n", (pxy)[0], (pxy)[1]))
#define SETCURSOR(x, y)             (TRACE_OPERATION("setcur(%u,%u)\n", x, y), (*self->at_ops.ato_setcursor)(self, x, y))
#define SETCOLOR(color)             (TRACE_OPERATION("setcolor(%#x)\n", color), (*self->at_ops.ato_setcolor)(self, color))
#define SETTTYMODE(ttymode)         (TRACE_OPERATION("setttymode(%#x)\n", ttymode), self->at_ops.ato_setttymode ? (*self->at_ops.ato_setttymode)(self, ttymode) : (void)0)
#define SETATTRIB(attrib)           (TRACE_OPERATION("setattrib(%#x)\n", attrib), self->at_ops.ato_setattrib ? (*self->at_ops.ato_setattrib)(self, attrib) : (void)0)
#define SETTITLE(title)             (TRACE_OPERATION("settitle(%q)\n", title), (self->at_ops.ato_settitle ? (*self->at_ops.ato_settitle)(self, title) : (void)0))
#define DOOUTPUT(text, len)         (TRACE_OPERATION("output(%$q)\n", len, text), (*self->at_ops.ato_output)(self, text, len))
#define OUTPUT(text)                (TRACE_OPERATION("output(%q)\n", text), self->at_ops.ato_output ? (*self->at_ops.ato_output)(self, text, COMPILER_STRLEN(text)) : (void)0)
#define SCROLL(offset)              (TRACE_OPERATION("scroll(%d)\n", (int)(offset)), (*self->at_ops.ato_scroll)(self, offset))
#define COPYCELL(dst_offset, count) (TRACE_OPERATION("copycell(%d,%u)\n", (int)(dst_offset), (unsigned int)(count)), (*self->at_ops.ato_copycell)(self, dst_offset, count))
#define CLS(mode)                   (TRACE_OPERATION("cls(%u)\n", mode), (*self->at_ops.ato_cls)(self, mode))
#define EL(mode)                    (TRACE_OPERATION("el(%u)\n", mode), (*self->at_ops.ato_el)(self, mode))
#define SETLED(mask, flag)          (TRACE_OPERATION("setled(%#x,%#x)\n", mask, flag), self->at_ops.ato_setled ? (*self->at_ops.ato_setled)(self, mask, flag) : (void)0)
#define SCROLLREGION(sl, el)                           \
	(TRACE_OPERATION("scrollregion(%u,%u)\n", sl, el), \
	 self->at_ops.ato_scrollregion                     \
	 ? (*self->at_ops.ato_scrollregion)(self, sl, el)  \
	 : (void)0)

#define MAXCOORD        ((ansitty_coord_t)-1)

/* Values for `at_ttyflag' */
#define ANSITTY_FLAG_NORMAL       0x0000 /* Normal flags */
#define ANSITTY_FLAG_CONCEIL      0x0001 /* FLAG: Use background color as foreground */
#define ANSITTY_FLAG_BOXMODE      0x0002 /* FLAG: Box mode enabled. */
#define ANSITTY_FLAG_VT52         0x0004 /* FLAG: VT52 compatibility mode. */
#define ANSITTY_FLAG_NOLFCR       0x0008 /* FLAG: \n characters should not imply CR. */
#define ANSITTY_FLAG_HEDIT        0x0010 /* FLAG: Horizontal Editing mode (ICH/DCH/IRM go backwards). */
#define ANSITTY_FLAG_INSERT       0x0020 /* FLAG: Enable insertion mode. */
#define ANSITTY_FLAG_INSDEL_LINE  0x0040 /* FLAG: Insert/Delete only affects the current line. */
#define ANSITTY_FLAG_RENDERMASK  (ANSITTY_FLAG_CONCEIL) /* Mask for flags that affect rendering */


/* TTY states */
#define STATE_TEXT        0 /* Default state: at the start of the next character. */
#define STATE_MBS         1 /* Inside of a multi-byte-character-string (same as `STATE_TEXT', \
                             * but `at_esclen' is non-NULL and refers to the number of UTF-8  \
                             * characters already present within `at_escape') */
#define STATE_ESC         2 /* State set immediately after a `\e' character was encountered */
#define STATE_CSI         3 /* Process escape arguments. */
#define STATE_OSC         4 /* Operating System Command reception mode. */
#define STATE_DCS         5 /* Device control string reception mode. */
#define STATE_SOS         6 /* Start of String reception mode. */
#define STATE_PM          7 /* Privacy Message reception mode. */
#define STATE_APC         8 /* Application Program Command reception mode. */
#define STATE_OSC_ESC     9 /* `STATE_OSC', followed by ESC */
#define STATE_DCS_ESC    10 /* `STATE_DCS', followed by ESC */
#define STATE_SOS_ESC    11 /* `STATE_SOS', followed by ESC */
#define STATE_PM_ESC     12 /* `STATE_PM', followed by ESC */
#define STATE_APC_ESC    13 /* `STATE_APC', followed by ESC */
#define STATE_LPAREN     14 /* After `ESC(' */
#define STATE_BOX        15 /* Box rendering mode. */
#define STATE_BOX_MBS    16 /* Box rendering mode (multi-byte string). */
#define STATE_ESC_5      17 /* After `ESC5' */
#define STATE_ESC_6      18 /* After `ESC6' */
#define STATE_ESC_POUND  19 /* After `ESC#' */
#define STATE_REPEAT     20 /* Repeat the next character `STATE_REPEAT_COUNT(self)' times */
#define STATE_REPEAT_MBS 21 /* Repeat the next character `STATE_REPEAT_COUNT(self)' times (character is incomplete) */
#define STATE_REPEAT_COUNT(self) (*(unsigned int *)(COMPILER_ENDOF((self)->at_escape) - sizeof(unsigned int)))
#define STATE_INSERT     22 /* Insertion-mode */
#define STATE_INSERT_MBS 23 /* Insertion-mode with pending multi-byte character */
#define STATE_ESC_Y1     24 /* After `ESCY' */
#define STATE_ESC_Y1_VAL(self) (*(uint8_t *)(COMPILER_ENDOF((self)->at_escape) - sizeof(uint8_t)))
#define STATE_ESC_Y2     25 /* After `ESCY<ORD>' */

#define STATE_OSC_ADD_ESC(x) ((x)+5)
#define STATE_OSC_DEL_ESC(x) ((x)-5)


/* Anything in this range (should) exit escape mode. */
#define ANSI_LOW       'A'
#define ANSI_HIGH      'z'





PRIVATE NONNULL((1)) void CC
stub_setcolor(struct ansitty *__restrict UNUSED(self),
              uint8_t UNUSED(color)) {
	/* no-op */
}

PRIVATE NONNULL((1)) void CC
stub_setcursor(struct ansitty *__restrict UNUSED(self),
               ansitty_coord_t UNUSED(x),
               ansitty_coord_t UNUSED(y)) {
	/* no-op */
}

PRIVATE NONNULL((1)) void CC
stub_getcursor(struct ansitty *__restrict UNUSED(self),
               ansitty_coord_t ppos[2]) {
	ppos[0] = ppos[1] = 0;
}

PRIVATE NONNULL((1)) void CC
stub_cls(struct ansitty *__restrict self,
         unsigned int mode) {
	ansitty_coord_t sxsy[2], xy[2];
	ansitty_coord_t &sx = sxsy[0];
	ansitty_coord_t &sy = sxsy[1];
	ansitty_coord_t &x = xy[0];
	ansitty_coord_t &y = xy[1];
	size_t i;
	GETCURSOR(xy);
	switch (mode) {

	case ANSITTY_CLS_AFTER:
		SETCURSOR(MAXCOORD, MAXCOORD);
		GETCURSOR(sxsy);
		SETCURSOR(x, y);
		i = (((sy + 1) - y) * (sx + 1)) - x;
		break;

	case ANSITTY_CLS_BEFORE:
		SETCURSOR(MAXCOORD, MAXCOORD);
		GETCURSOR(sxsy);
		SETCURSOR(0, 0);
		i = (y * (sx + 1)) + x;
		break;

	default:
		SETCURSOR(MAXCOORD, MAXCOORD);
		GETCURSOR(sxsy);
		SETCURSOR(0, 0);
		i = (sx + 1) * (sy + 1);
		break;
	}
	while (i--)
		PUTUNI(' ');
	SETCURSOR(xy[0], xy[1]);
}

PRIVATE NONNULL((1)) void CC
stub_el(struct ansitty *__restrict self,
        unsigned int mode) {
	ansitty_coord_t xy[2];
	ansitty_coord_t sxy[2];
	ansitty_coord_t &x = xy[0];
	ansitty_coord_t &y = xy[1];
	ansitty_coord_t &sx = sxy[0];
	size_t i;
	GETCURSOR(xy);
	SETCURSOR(MAXCOORD, y);
	GETCURSOR(sxy);
	y = sxy[1];
	switch (mode) {

	case ANSITTY_EL_AFTER:
		SETCURSOR(x, y);
		i = (sx + 1) - x;
		break;

	case ANSITTY_EL_BEFORE:
		SETCURSOR(0, y);
		i = x;
		break;

	default:
		SETCURSOR(0, y);
		i = sx + 1;
		break;
	}
	while (i--)
		PUTUNI(' ');
	if (mode != ANSITTY_EL_BEFORE)
		SETCURSOR(xy[0], xy[1]);
}

PRIVATE NONNULL((1)) void CC
stub_copycell(struct ansitty *__restrict UNUSED(self),
              ansitty_offset_t UNUSED(dst_offset),
              ansitty_coord_t UNUSED(count)) {
	/* Cannot be emulated. */
}

PRIVATE NONNULL((1)) void CC
stub_scroll_with_copycell(struct ansitty *__restrict self,
                          ansitty_offset_t offset) {
	ansitty_coord_t xy[2];
	ansitty_coord_t sxy[2];
	ansitty_coord_t y, y_start, y_end, y_size;
	if unlikely(!offset)
		return;
	y_start = self->at_scroll_sl;
	y_end   = self->at_scroll_el;
	if unlikely(y_start >= y_end)
		return;
	GETCURSOR(xy);
	SETCURSOR(MAXCOORD, MAXCOORD);
	GETCURSOR(sxy);
	++sxy[0];
	++sxy[1];
	if (y_end > sxy[1]) {
		y_end = sxy[1];
		if unlikely(y_start >= y_end)
			goto done;
	}
	y_size = y_end - y_start;
	if unlikely(y_size == 1)
		return;
	--y_size;
	assert(y_size != 0);
	if (offset < 0) {
		offset = -offset;
		if ((ansitty_coord_t)offset >= y_size)
			goto done;
		/* Move terminal contents upwards */
		for (y = y_start + 1; y < y_end; ++y) {
			SETCURSOR(0, y);
			COPYCELL(-(ansitty_offset_t)sxy[0], sxy[0]);
		}
	} else {
		if ((ansitty_coord_t)offset >= y_size)
			goto done;
		/* Move terminal contents downwards */
		y = y_end - 1;
		while (y >= y_start) {
			SETCURSOR(0, y);
			COPYCELL((ansitty_offset_t)sxy[0], sxy[0]);
			--y;
		}
	}
done:
	SETCURSOR(xy[0], xy[1]);
}


PRIVATE NONNULL((1)) void CC
stub_scroll(struct ansitty *__restrict self,
            ansitty_offset_t offset) {
	ansitty_coord_t xy[2];
	if (offset >= 0)
		return;
	GETCURSOR(xy);
	SETCURSOR(MAXCOORD, MAXCOORD);
	while (offset++)
		PUTUNI('\n');
	SETCURSOR(xy[0], xy[1]);
}



/* Initialize the given ANSI TTY
 * After calling this function, the caller is still responsible
 * to initialize at the very least `self->at_ops.ato_putc'. */
INTERN NONNULL((1)) void CC
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
	/* copycell cannot be emulated, but still replace it with a no-op */
	if (!self->at_ops.ato_copycell)
		self->at_ops.ato_copycell = &stub_copycell;
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
	self->at_scroll_ec  = MAXCOORD;
	self->at_state      = 0;
	self->at_zero       = 0;
}


LOCAL void CC
setcolor(struct ansitty *__restrict self,
         uint8_t color) {
	if (self->at_color == color)
		return; /* Unchanged. */
	self->at_color = color;
	if (self->at_ttyflag & ANSITTY_FLAG_CONCEIL)
		color = ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_BG(color),
		                              ANSITTY_PALETTE_INDEX_BG(color));
	SETCOLOR(color);
}

LOCAL void CC
setttymode(struct ansitty *__restrict self, uint16_t new_ttymode) {
	if (self->at_ttymode == new_ttymode)
		return;
	self->at_ttymode = new_ttymode;
	SETTTYMODE(new_ttymode);
}

LOCAL void CC
setattrib(struct ansitty *__restrict self, uint16_t new_attrib) {
	if (self->at_attrib == new_attrib)
		return;
	self->at_attrib = new_attrib;
	SETATTRIB(new_attrib);
}

LOCAL void CC
setflags(struct ansitty *__restrict self, uint16_t new_flags) {
	if (self->at_ttyflag == new_flags)
		return;
	if ((new_flags & ANSITTY_FLAG_CONCEIL) != (self->at_ttyflag & ANSITTY_FLAG_CONCEIL)) {
		uint8_t used_color = self->at_color;
		if (new_flags & ANSITTY_FLAG_CONCEIL)
			used_color = ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_BG(used_color),
			                                   ANSITTY_PALETTE_INDEX_BG(used_color));
		SETCOLOR(used_color);
	}
	self->at_ttyflag = new_flags;
}



/* Ansi box character set (translate to their unicode character equivalents) */
#define BOX_CHARS_START '_'
PRIVATE char16_t const box_chars[] = {
	/* s.a.: https://vt100.net/docs/vt100-ug/table3-9.html */
#ifdef __INTELLISENSE__
#define CHR(x) [x - BOX_CHARS_START] =
#else
#define CHR(x) /* nothing */
#endif
	CHR('_') ' ',    /* Blank */
	CHR('`') 0x22c4, /* Diamond */
	CHR('a') 0x2593, /* Checkerboard */
	CHR('b') 0x0009, /* Horizontal tab */
	CHR('c') 0x000c, /* Form Feed */
	CHR('d') '\r',   /* Carriage return */
	CHR('e') '\n',   /* Line feed */
	CHR('f') 0x00b0, /* ° Degree symbol */
	CHR('g') 0x00b1, /* ± Plus/minus */
	CHR('h') '\n',   /* New line */
	CHR('i') 0x000b, /* Vertical tab */
	CHR('j') 0x2518, /* Lower-right corner */
	CHR('k') 0x2510, /* Upper-right corner */
	CHR('l') 0x250c, /* Upper-left corner*/
	CHR('m') 0x2514, /* Lower-left corner */
	CHR('n') 0x253c, /* Crossing lines */
	CHR('o') 0x2500, /* Horizontal line - Scan 1 */
	CHR('p') 0x2500, /* Horizontal line - Scan 3 */
	CHR('q') 0x2500, /* Horizontal line - Scan 5 */
	CHR('r') 0x2500, /* Horizontal line - Scan 7 */
	CHR('s') 0x2500, /* Horizontal line - Scan 9 */
	CHR('t') 0x251c, /* Left "T" */
	CHR('u') 0x2524, /* Right "T" */
	CHR('v') 0x2534, /* Bottom "T" */
	CHR('w') 0x252c, /* Top "T" */
	CHR('x') 0x2502, /* | Vertical bar */
	CHR('y') 0x2264, /* Less than or equal to */
	CHR('z') 0x2265, /* Greater than or equal to */
	CHR('{') 0x03a0, /* Pi */
	CHR('|') 0x2260, /* Not equal to */
	CHR('}') 0x00a3, /* UK pound sign */
	CHR('~') 0x2219, /* Centered dot */
#undef CHR
};


PRIVATE void CC
ansitty_putbox(struct ansitty *__restrict self, char32_t boxch) {
	/* Translate box characters. */
	if (boxch >= BOX_CHARS_START &&
	    boxch < (BOX_CHARS_START + COMPILER_LENOF(box_chars)))
		boxch = (box_chars[boxch - BOX_CHARS_START]);
	PUTUNI(boxch);
}

PRIVATE size_t CC
ansitty_printutf8(struct ansitty *__restrict self,
                  /*utf-8*/ char const *__restrict text, size_t textlen) {
	char const *end, *reader;
	end = (reader = text) + textlen;
	while (reader < end) {
		char32_t ch;
		if ((reader + unicode_utf8seqlen[(unsigned char)*reader]) > end)
			return (size_t)(end - reader);
		ch = unicode_readutf8_n(&reader, end);
		PUTUNI(ch);
	}
	return 0;
}

PRIVATE size_t CC
ansitty_printutf8_box(struct ansitty *__restrict self,
                      /*utf-8*/ char const *__restrict text, size_t textlen) {
	char const *end, *reader;
	end = (reader = text) + textlen;
	while (reader < end) {
		char32_t ch;
		if ((reader + unicode_utf8seqlen[(unsigned char)*reader]) > end)
			return (size_t)(end - reader);
		ch = unicode_readutf8_n(&reader, end);
		ansitty_putbox(self, ch);
	}
	return 0;
}

PRIVATE void CC savecursor(struct ansitty *__restrict self) {
	GETCURSOR(self->at_savecur);
}
PRIVATE void CC loadcursor(struct ansitty *__restrict self) {
	SETCURSOR(self->at_savecur[0],
	          self->at_savecur[1]);
}

PRIVATE void CC setscrollregion(struct ansitty *__restrict self,
                                ansitty_coord_t sl, ansitty_coord_t el) {
	if (sl == self->at_scroll_sl &&
	    el == self->at_scroll_el)
		return;
	self->at_scroll_sl = sl;
	self->at_scroll_el = el;
	SCROLLREGION(sl, el);
}

PRIVATE void CC setscrollmargin(struct ansitty *__restrict self,
                                ansitty_coord_t sc, ansitty_coord_t ec) {
	self->at_scroll_sc = sc;
	self->at_scroll_ec = ec;
}



/* ==================================================================================== */
/* Escape command implementation                                                        */
/* ==================================================================================== */


/* "\e]{arg[arglen]:%s}\e[" */
PRIVATE bool CC
ansi_OSC(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen) {
	char *pos;
	unsigned int code;
	code = (unsigned int)strtoul(arg, &pos, 10);
	if (*pos == ';') {
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
PRIVATE bool CC
ansi_DCS(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen) {
	/* TODO */
	return false;
}

/* "\eX{arg[arglen]:%s}\e[" */
PRIVATE bool CC
ansi_SOS(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen) {
	/* TODO */
	return false;
}

/* "\e^{arg[arglen]:%s}\e[" */
PRIVATE bool CC
ansi_PM(struct ansitty *__restrict self,
        char *__restrict arg, size_t arglen) {
	/* TODO */
	return false;
}

/* "\e_{arg[arglen]:%s}\e[" */
PRIVATE bool CC
ansi_APC(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen) {
	/* TODO */
	return false;
}



struct rgb_color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};

struct ansi_palette {
	struct rgb_color pal[16];
};

PRIVATE struct ansi_palette const vga_pal = {
	{
		{ 0, 0, 0 },       { 170, 0, 0 },     { 0, 170, 0 },     { 170, 85, 0 },
		{ 0, 0, 170 },     { 170, 0, 170 },   { 0, 170, 170 },   { 170, 170, 170 },
		{ 85, 85, 85 },    { 255, 85, 85 },   { 85, 255, 85 },   { 255, 255, 85 },
		{ 85, 85, 255 },   { 255, 85, 255 },  { 85, 255, 255 },  { 255, 255, 255 }
	}
};


PRIVATE size_t CC
color_distance(uint8_t ra, uint8_t ga, uint8_t ba,
               uint8_t rb, uint8_t gb, uint8_t bb) {
	unsigned int dist_r = (unsigned int)abs((int)ra - (int)rb);
	unsigned int dist_g = (unsigned int)abs((int)ga - (int)gb);
	unsigned int dist_b = (unsigned int)abs((int)ba - (int)bb);
	/* Crude, hacky way of favoring colors best seen by the human eye. */
	return (dist_r) +
	       (dist_g * 2) +
	       (dist_b / 2);
}

PRIVATE unsigned int CC
get_index_for_color(uint8_t r, uint8_t g, uint8_t b) {
	unsigned int i, winner_index = 0;
	size_t winner_distance = (size_t)-1;
	for (i = 0; i < COMPILER_LENOF(vga_pal.pal); ++i) {
		size_t distance;
		distance = color_distance(r, g, b,
		                          vga_pal.pal[i].r,
		                          vga_pal.pal[i].g,
		                          vga_pal.pal[i].b);
		if (distance < winner_distance) {
			winner_distance = distance;
			winner_index    = i;
		}
	}
	return winner_index;
}


PRIVATE void CC
do_ident_DA(struct ansitty *__restrict self) {
	/* Do what linux does: Report `\e[6c` */
	OUTPUT(SESC "[6c");
}


#define ARGUMENT_CODE_SWITCH_BEGIN()                                  \
	{                                                                 \
		unsigned int code;                                            \
		char *_args_iter, *_args_end;                                 \
		_args_iter = arg;                                             \
		for (;;) {                                                    \
			code = (unsigned int)strtoul(_args_iter, &_args_end, 10); \
			if (*_args_end != ';' && _args_end != arg + arglen)       \
				goto nope;                                            \
			switch (code) {
#define ARGUMENT_CODE_SWITCH_END()         \
			default: goto nope;            \
			}                              \
			if (_args_end == arg + arglen) \
				break;                     \
			_args_iter = _args_end + 1;    \
		}                                  \
	}

#define ARGUMENT_CODE_QSWITCH_BEGIN()                                     \
	{                                                                     \
		unsigned int code;                                                \
		char *_args_iter, *_args_end;                                     \
		_args_iter = arg;                                                 \
		for (;;) {                                                        \
			if (*_args_iter == '?') {                                     \
				++_args_iter;                                             \
				code = (unsigned int)strtoul(_args_iter, &_args_end, 10); \
				if (*_args_end != ';' && _args_end != arg + arglen)       \
					goto nope;                                            \
				switch (code) {
#define ARGUMENT_CODE_QSWITCH_ELSE()                                      \
				default: goto nope;                                       \
				}                                                         \
			} else {                                                      \
				code = (unsigned int)strtoul(_args_iter, &_args_end, 10); \
				if (*_args_end != ';' && _args_end != arg + arglen)       \
					goto nope;                                            \
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


PRIVATE void CC
ansitty_do_hscroll(struct ansitty *__restrict self, int offset) {
	ansitty_coord_t xy[2];
	ansitty_coord_t y, x_size;
	ansitty_coord_t y_start, y_end;
	ansitty_coord_t x_start, x_end;
	x_start = self->at_scroll_sc;
	x_end   = self->at_scroll_ec;
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
			SETCURSOR(x_start, y);
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
			SETCURSOR(x, y);
			COPYCELL(-offset, cells_per_row);
		}
	}
	SETCURSOR(xy[0], xy[1]);
}

/* "\e[{arg[arglen]:%s}{lastch}" */
PRIVATE bool CC
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
				n = (int)strtol(arg, &end, 10);
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
				n = (int)strtol(arg, &end, 10);
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
			n = (int)strtol(arg, &end, 10);
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
			SETCURSOR(xy[0], (ansitty_coord_t)n);
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
			SETCURSOR((ansitty_coord_t)n, xy[1]);
		}	break;

		case 'd': /* VPA -- Vertical Position Absolute */
		{
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			if (n < 0)
				n = 0;
			SETCURSOR(xy[0], (ansitty_coord_t)n);
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
			SETCURSOR(0, (ansitty_coord_t)n);
		}	break;

		case 'G': /* ANSI: CHA */
		case '`': /* HPA -- Horizontal Position Absolute */
		{
			ansitty_coord_t xy[2];
			if (n < 0)
				n = 0;
			if (n)
				--n;
			GETCURSOR(xy);
			SETCURSOR((ansitty_coord_t)n, xy[1]);
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
			                            ANSITTY_FLAG_INSDEL_LINE)) {

			case 0:
				/* 123456789      123456789
				 * ABCDEFGHI  --> ABCD...EF
				 * abcdefghi      GHIabcdef */
				COPYCELL(n, MAXCOORD);
				break;

			case ANSITTY_FLAG_INSDEL_LINE: {
				/* 123456789      123456789
				 * ABCDEFGHI  --> ABCD...EF
				 * abcdefghi      abcdefghi */
				ansitty_coord_t xy[2];
				ansitty_coord_t sxy[2];
				ansitty_coord_t cells_in_line;
				GETCURSOR(xy);
				SETCURSOR(MAXCOORD, MAXCOORD);
				GETCURSOR(sxy);
				SETCURSOR(xy[0], xy[1]);
				++sxy[0];
				if unlikely(xy[0] >= sxy[0])
					break;
				cells_in_line = sxy[0] - xy[0];
				if ((unsigned int)n >= cells_in_line)
					break;
				COPYCELL(n, cells_in_line - (unsigned int)n);
			}	break;

			case ANSITTY_FLAG_HEDIT: {
				ansitty_coord_t xy[2];
				ansitty_coord_t xy2[2];
				unsigned int copy_count;
				/* 123456789      456789ABC
				 * ABCDEFGHI  --> D...EFGHI
				 * abcdefghi      abcdefghi */
				GETCURSOR(xy);
				if (xy[1] == 0) {
					if (xy[0] < (unsigned int)n)
						break;
					copy_count = xy[0];
					SETCURSOR((unsigned int)n, 0);
				} else {
					SETCURSOR((unsigned int)n, 0);
					GETCURSOR(xy2);
					if (xy2[0] < (unsigned int)n) {
						/* n >= SCREEN_SIZE.X, where xy2[0] == SCREEN_SIZE.X - 1 */
						ansitty_coord_t column, row;
						++xy2[0];
						column = n % xy2[0];
						row    = n / xy2[0];
						if (row > xy[1] ||
						    (row == xy[1] && column > xy[0])) {
							SETCURSOR(xy[0], xy[1]);
							break; /* Full area shift */
						}
						SETCURSOR(column, row);
					} else {
						/* We still need to know the display width */
						SETCURSOR(MAXCOORD, 0);
						GETCURSOR(xy2);
						SETCURSOR((unsigned int)n, 0);
						++xy2[0];
					}
					copy_count = xy[0] + xy[1] * xy2[0];
				}
				COPYCELL(-n, copy_count);
				SETCURSOR(xy[0], xy[1]);
			}	break;

			case ANSITTY_FLAG_HEDIT | ANSITTY_FLAG_INSDEL_LINE: {
				ansitty_coord_t xy[2];
				/* 123456789      123456789
				 * ABCDEFGHI  --> D...EFGHI
				 * abcdefghi      abcdefghi */
				GETCURSOR(xy);
				if ((unsigned int)n >= xy[0])
					break; /* Full area shift */
				SETCURSOR((ansitty_coord_t)n, xy[1]);
				COPYCELL(-n, xy[0] - (unsigned int)n);
				SETCURSOR(xy[0], xy[1]);
			}	break;

			default: __builtin_unreachable();
			}
			break;

		case 'P':
			/* DCH -- Delete Character, from current position to end of field */
			if (n <= 0)
				break;
			switch (self->at_ttyflag & (ANSITTY_FLAG_HEDIT |
			                            ANSITTY_FLAG_INSDEL_LINE)) {

			case 0: {
				/* 123456789      123456789
				 * ABCDEFGHI  --> ABCDHIabc
				 * abcdefghi      defghi... */
				ansitty_coord_t xy[2];
				ansitty_coord_t xy2[2];
				ansitty_coord_t new_x;
				GETCURSOR(xy);
				new_x = xy[0] + (unsigned int)n;
				SETCURSOR(new_x, xy[1]);
				GETCURSOR(xy2);
				if (xy2[0] < new_x) {
					ansitty_coord_t new_y;
					++xy2[0];
					new_y = xy[1] + (unsigned int)n / xy2[0];
					new_x = xy[0] + (unsigned int)n % xy2[0];
					SETCURSOR(new_x, new_y);
				}
				COPYCELL(-n, MAXCOORD);
				SETCURSOR(xy[0], xy[1]);
			}	break;

			case ANSITTY_FLAG_INSDEL_LINE: {
				/* 123456789      123456789
				 * ABCDEFGHI  --> ABCDHI...
				 * abcdefghi      abcdefghi */
				ansitty_coord_t xy[2];
				ansitty_coord_t sxy[2];
				ansitty_coord_t cells_in_line;
				GETCURSOR(xy);
				SETCURSOR(MAXCOORD, MAXCOORD);
				GETCURSOR(sxy);
				++sxy[0];
				if unlikely(xy[0] >= sxy[0]) {
					SETCURSOR(xy[0], xy[1]);
					break;
				}
				cells_in_line = sxy[0] - xy[0];
				if ((unsigned int)n >= cells_in_line) {
					SETCURSOR(xy[0], xy[1]);
					break;
				}
				cells_in_line -= (unsigned int)n;
				SETCURSOR(xy[0] + cells_in_line, xy[1]);
				COPYCELL(-n, cells_in_line);
				SETCURSOR(xy[0], xy[1]);
			}	break;

			case ANSITTY_FLAG_HEDIT: {
				ansitty_coord_t xy[2];
				unsigned int copy_count;
				/* 123456789      ...123456
				 * ABCDEFGHI  --> 789AEFGHI
				 * abcdefghi      abcdefghi */
				GETCURSOR(xy);
				copy_count = xy[0];
				if (xy[1] != 0) {
					ansitty_coord_t sxy[2];
					SETCURSOR(MAXCOORD, 0);
					GETCURSOR(sxy);
					++sxy[0];
					copy_count += xy[1] * sxy[0];
				}
				SETCURSOR(0, 0);
				COPYCELL(n, copy_count);
				SETCURSOR(xy[0], xy[1]);
			}	break;

			case ANSITTY_FLAG_HEDIT | ANSITTY_FLAG_INSDEL_LINE: {
				ansitty_coord_t xy[2];
				/* 123456789      123456789
				 * ABCDEFGHI  --> ...AEFGHI
				 * abcdefghi      abcdefghi */
				GETCURSOR(xy);
				if ((unsigned int)n >= xy[0])
					break; /* Full area shift */
				SETCURSOR(0, xy[1]);
				COPYCELL(n, xy[0] - (unsigned int)n);
				SETCURSOR(xy[0], xy[1]);
			}	break;

			default: __builtin_unreachable();
			}
			break;

		case 'M': /* DL -- \e[2M   Delete 2 lines if currently in scrolling region */
			n = -n;
			ATTR_FALLTHROUGH
		case 'L': /* IL -- \e[3L   Insert 3 lines if currently in scrolling region */
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
			 * I implement this one as repeat-the-next-character. */
			if (n <= 0)
				break;
			STATE_REPEAT_COUNT(self) = (unsigned int)n;
			self->at_state = STATE_REPEAT;
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
		int x, y;
		if (!arglen)
			x = y = 1; /* \e[f */
		else {
			char *end;
			if (arg[0] == ';') {
				x = 1; /* \e[;10f  --or-- \e[;f */
				y = (int)strtol(arg + 1, &end, 10);
			} else {
				x = (int)strtol(arg, &end, 10);
				if (end >= arg + arglen) {
					y = 1; /* \e[10f */
				} else {
					if (end[0] != ';')
						goto nope;  /* \e[10;20f --or-- \e[10;f */
					y = (int)strtol(end + 1, &end, 10);
				}
				if unlikely(x < 1)
					x = 1;
			}
			if unlikely(end != arg + arglen)
				goto nope;
			if unlikely(y < 1)
				y = 1;
		}
		SETCURSOR((ansitty_coord_t)(x - 1),
		          (ansitty_coord_t)(y - 1));
	}	break;

	/* TODO: case 'I': Horizontal tab emulation */


	case 'J': /* ANSI/VT100: ED */
		if (!arglen)
			CLS(ANSITTY_CLS_AFTER);
		else {
			ARGUMENT_CODE_SWITCH_BEGIN()

			case ANSITTY_CLS_AFTER:
			case ANSITTY_CLS_BEFORE:
			case ANSITTY_CLS_ALL:
			case ANSITTY_CLS_ALLPAGES:
				CLS(code);
				break;

			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'K': /* ANSI/VT100: EL */
		if (!arglen)
			EL(ANSITTY_EL_AFTER);
		else {
			ARGUMENT_CODE_SWITCH_BEGIN()

			case ANSITTY_EL_AFTER:
			case ANSITTY_EL_BEFORE:
			case ANSITTY_EL_ALL:
				EL(code);
				break;

			ARGUMENT_CODE_SWITCH_END()
		}
		break;


	case 'Q': /* SEM Set Editing extent Mode (limits ICH & DCH) */
		if (!arglen)
			self->at_ttyflag &= ~(ANSITTY_FLAG_INSDEL_LINE);
		else {
			ARGUMENT_CODE_SWITCH_BEGIN()

			case 0: /* \e[0Q   [Q = Insert/delete character affects rest of display */
				self->at_ttyflag &= ~(ANSITTY_FLAG_INSDEL_LINE);
				break;

			case 1: /* \e[1Q   ICH/DCH affect the current line only */
				self->at_ttyflag |= ANSITTY_FLAG_INSDEL_LINE;
				break;
			/* TODO: \e[2Q   ICH/DCH affect current field (between tab stops) only */
			/* TODO: \e[3Q   ICH/DCH affect qualified area (between protected fields) */

			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'c':
		if (!arglen) {
			do_ident_DA(self);
		} else {
			ARGUMENT_CODE_SWITCH_BEGIN()
			case 0:
				do_ident_DA(self);
				break;
			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'h':
	case 'l':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_QSWITCH_BEGIN()

			case 0:
				/* Must be ignored. */
				break;

//			case 1:  /* \e[?1h    DECCKM   Cursor Keys Mode, send ESC O A for cursor up */
//			         /* \e[?1l             Cursor keys send ANSI cursor position commands DECCKM */

			case 2:  /* \e[?2h    DECANM   ANSI Mode, use ESC < to switch VT52 to ANSI */
			         /* \e[?2l             Use VT52 emulation instead of ANSI mode DECANM */
				if (lastch == 'h') {
					/* \e[?2h -- Set ANSI (versus VT52) */
					self->at_ttyflag &= ~ANSITTY_FLAG_VT52;
				} else {
					/* \e[?2l -- Set VT52 (versus ANSI) */
					self->at_ttyflag |= ANSITTY_FLAG_VT52;
				}
				break;

//			case 3:  /* \e[?3h    DECCOLM  COLumn mode, 132 characters per line */
//			         /* \e[?3l             80 characters per line (erases screen) DECCOLM */
//			case 4:  /* \e[?4h    DECSCLM  SCrolL Mode, smooth scrolling */
//			         /* \e[?4l             Jump scrolling DECSCLM */
//			case 5:  /* \e[?5h    DECSCNM  SCreeN Mode,  white on black background */
//			         /* \e[?5l             black on white background) DEC SCNM */
//			case 6:  /* \e[?6h    DECOM    Origin Mode, line 1 is relative to scroll region */
//			         /* \e[?6l             Line numbers are independent of scrolling region DECOM */

			case 7:  /* \e[?7h    DECAWM   AutoWrap Mode, start newline after column 80 */
			         /* \e[?7l             Cursor remains at end of line after column 80 DECAWM */
				setattrib(self, (self->at_attrib & ~ANSITTY_MODE_NOLINEWRAP) |
				                (lastch == 'l' ? ANSITTY_MODE_NOLINEWRAP : 0));
				break;

//			case 8:  /* \e[?8h    DECARM   Auto Repeat Mode, key will autorepeat */
//			         /* \e[?8l             Keys do not repeat when held down DECARM */
//			case 9:  /* \e[?9h    DECINLM  INterLace Mode, interlaced for taking photos */
//			         /* \e[?9l             Display is not interlaced to avoid flicker DECINLM */
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
//			case 1004: /* \e[?1004h focus notify enable (causes mac os terminal to "alert" when  gaining/loosing focus) */
//			           /* \e[?1004l focus notify disable */

			case 1049:
				if (lastch == 'h') {
					CLS(ANSITTY_CLS_ALL);
					SETCURSOR(0, 0);
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

			ARGUMENT_CODE_QSWITCH_ELSE()

			case 0:
				/* Must be ignored. */
				break;

//			case 1:  /* \e[1h   GATM  Guarded Area Transmit Mode, send all (VT132) */
//			         /* \e[1l         Transmit only unprotected characters (VT132) GATM */
//			case 2:  /* \e[2h   KAM   Keyboard Action Mode, disable keyboard input */
//			         /* \e[2l         Enable input from keyboard KAM */
//			case 3:  /* \e[3h   CRM   Control Representation Mode, show all control chars */
//			         /* \e[3l         Control characters are not displayable characters CRM */

			case 4:  /* \e[4h   IRM   Insertion/Replacement Mode, set insert mode (VT102) */
			         /* \e[4l         Reset to replacement mode (VT102) IRM */
				if (lastch == 'h') {
					self->at_ttyflag |= ANSITTY_FLAG_INSERT;
					self->at_state = STATE_INSERT;
				} else {
					self->at_ttyflag &= ~ANSITTY_FLAG_INSERT;
					self->at_state = STATE_TEXT;
					if (self->at_ttyflag & ANSITTY_FLAG_BOXMODE)
						self->at_state = STATE_BOX;
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

			case 20: /* \e[20h   LNM  Linefeed Newline Mode, LF interpreted as CR LF */
			         /* \e[20l        Linefeed does not change horizontal position LNM */
				if (lastch == 'h') {
					/* LF == CRLF (default) */
					self->at_ttyflag &= ~ANSITTY_FLAG_NOLFCR;
				} else {
					/* LF == LF */
					self->at_ttyflag |= ANSITTY_FLAG_NOLFCR;
				}
				break;

			ARGUMENT_CODE_QSWITCH_END()
		}
		break;

#if 0
	case 'i':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_QSWITCH_BEGIN()

			case 0: /* \e[?0i Graphics screen dump goes to graphics printer VT125,VT240 */
			case 1: /* \e[?1i Print cursor line, terminated by CR LF */
			case 2: /* \e[?2i Graphics screen dump goes to host computer VT125,VT240 */
			case 3: /* \e[?4i Disable auto print */
			case 4: /* \e[?5i Auto print, send a line at a time when linefeed received */

			ARGUMENT_CODE_QSWITCH_ELSE()

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
			ARGUMENT_CODE_QSWITCH_BEGIN()

			case 20: /* \e[?20j Portrait    Extended N. American letter Yes */
			case 21: /* \e[?21j Landscape   Extended N. American letter Yes */
			case 22: /* \e[?22j Portrait    Extended A4 Yes */
			case 23: /* \e[?23j Landscape   Extended A4 Yes */
			case 24: /* \e[?24j Portrait    Extended Legal Yes */
			case 25: /* \e[?25j Landscape   Extended Legal Yes */
			case 26: /* \e[?26j Portrait    Extended B Yes */
			case 27: /* \e[?27j Landscape   Extended B Yes */

			ARGUMENT_CODE_QSWITCH_ELSE()

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
			ARGUMENT_CODE_SWITCH_BEGIN()

			case 0: /* Reset colors and text attributes */
				setcolor(self, self->at_defcolor);
				setattrib(self, ANSITTY_ATTRIB_DEFAULT);
				setflags(self, self->at_ttyflag & ~ANSITTY_FLAG_RENDERMASK);
				break;

			case 1: /* Brighten foreground output color */
				setcolor(self, self->at_color | ANSITTY_IFSTRONG);
				break;

			case 2: /* Darken foreground output color */
				setcolor(self, self->at_color & ~ANSITTY_IFSTRONG);
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
				setattrib(self, self->at_attrib | ANSITTY_ATTRIB_CROSS);
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
				setcolor(self, (self->at_color & ~ANSITTY_IFSTRONG) |
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
				setattrib(self, self->at_attrib & ~ANSITTY_ATTRIB_CROSS);
				break;

			case 30 ... 37:
				setcolor(self, ANSITTY_PALETTE_INDEX(code - 30,
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
					r = (unsigned int)strtoul(_args_end, &_args_end, 10);
					if (*_args_end != ';')
						goto nope;
					++_args_end;
					g = (unsigned int)strtoul(_args_end, &_args_end, 10);
					if (*_args_end != ';')
						goto nope;
					++_args_end;
					b = (unsigned int)strtoul(_args_end, &_args_end, 10);
					if (*_args_end != ';' && _args_end != arg + arglen)
						goto nope;
					++_args_end;
					if unlikely(r > 0xff)
						r = 0xff;
					if unlikely(g > 0xff)
						g = 0xff;
					if unlikely(b > 0xff)
						b = 0xff;
					used_color_index = get_index_for_color((uint8_t)r,
					                                       (uint8_t)g,
					                                       (uint8_t)b);
				} else {
					assert(color_mode == 5);
					used_color_index = (unsigned int)strtoul(_args_end, &_args_end, 10);
					if (*_args_end != ';' && _args_end != arg + arglen)
						goto nope;
				}
				setcolor(self, code == 38
				               ? ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(used_color_index),
				                                       ANSITTY_PALETTE_INDEX_BG(self->at_color))
				               : ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(self->at_color),
				                                       ANSITTY_PALETTE_INDEX_BG(used_color_index)));
			}	break;

			case 51:
				setattrib(self, self->at_attrib | ANSITTY_ATTRIB_FRAMED);
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
				setcolor(self, ANSITTY_PALETTE_INDEX(ANSITTY_IFSTRONG + (code - 90),
				                                     ANSITTY_PALETTE_INDEX_BG(self->at_color)));
				break;

			case 100 ... 107:
				setcolor(self, ANSITTY_PALETTE_INDEX(ANSITTY_PALETTE_INDEX_FG(self->at_color),
				                                     ANSITTY_IFSTRONG + (code - 100)));
				break;

			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'n':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_QSWITCH_BEGIN()

			case 15:
				/* Command to terminal requesting printer status
				 * Return values:
				 *     \e[?10n = OK,
				 *     \e[?11n = not OK,
				 *     \e[?13n = no printer. */
				OUTPUT(SESC "[?13n"); /* no printer */
				break;

			ARGUMENT_CODE_QSWITCH_ELSE()

			case 5:
				/* Query Device Status
				 *     \e[0n = Terminal is ready, no malfunctions detected
				 *     \e[1n = Terminal is busy, retry later
				 *     \e[2n = Terminal is busy, it will send DSR when ready
				 *     \e[3n = Malfunction, please try again
				 *     \e[4n = Malfunction, terminal will send DSR when ready */
				OUTPUT(SESC "[0n"); /* We are always ready! */
				break;

			case 6:
				/* DSR */
				if (self->at_ops.ato_output) {
					char buf[32];
					size_t len;
					ansitty_coord_t xy[2];
					GETCURSOR(xy);
					len = sprintf(buf, SESC "[%u;%uR",
					              (unsigned int)(xy[0] + 1),
					              (unsigned int)(xy[1] + 1));
					DOOUTPUT(buf, len);
				}
				break;

			ARGUMENT_CODE_QSWITCH_END()
		}
		break;

	case 'y':
		if (!arglen) {
			/* Undefined */
			goto nope;
		} else {
			ARGUMENT_CODE_SWITCH_BEGIN()

				/* 2;1:  Confidence power up test (no-op) */
				/* 2;2:  Confidence loopback test (no-op) */
				/* 2;9:  Repeat power up test (no-op) */
				/* 2;10: Repeat loopback test (no-op) */
			case 1:
			case 2:
			case 9:
			case 10:
				break;

			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 'q':
		if (arglen == 0) {
			/* ledsoff DECLL0 */
			SETLED(~0xf, 0x0);
		} else {
			ARGUMENT_CODE_SWITCH_BEGIN()

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

			ARGUMENT_CODE_SWITCH_END()
		}
		break;

	case 's': /* DECSTRM */
		if (arglen == 0) {
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
				startcolumn = (ansitty_coord_t)strtoul(arg, &end, 10);
				if (*end != ';')
					goto nope;
				++end;
				if (end == arg + arglen)
					endcolumn = MAXCOORD;
				else {
					endcolumn = (ansitty_coord_t)strtoul(end, &end, 10);
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
		/* Set top and bottom line#s of a window */
		ansitty_coord_t startline;
		ansitty_coord_t endline;
		if (!arglen) {
			startline = 0;
			endline   = MAXCOORD;
		} else {
			char *end;
			startline = (ansitty_coord_t)strtoul(arg, &end, 10);
			if (*end != ';')
				goto nope;
			++end;
			if (end == arg + arglen)
				endline = MAXCOORD;
			else {
				endline = (ansitty_coord_t)strtoul(end, &end, 10);
				if (end != arg + arglen)
					goto nope;
			}
			if (startline)
				--startline;
			if (endline)
				--endline;
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


PRIVATE void CC
ansitty_setstate_text(struct ansitty *__restrict self) {
	if (self->at_ttyflag & ANSITTY_FLAG_INSERT)
		self->at_state = STATE_INSERT;
	else if (self->at_ttyflag & ANSITTY_FLAG_BOXMODE)
		self->at_state = STATE_BOX;
	else {
		self->at_state = STATE_TEXT;
	}
}

PRIVATE void CC
ansitty_setstate_mbs(struct ansitty *__restrict self) {
	if (self->at_ttyflag & ANSITTY_FLAG_INSERT)
		self->at_state = STATE_INSERT_MBS;
	else if (self->at_ttyflag & ANSITTY_FLAG_BOXMODE)
		self->at_state = STATE_BOX_MBS;
	else {
		self->at_state = STATE_MBS;
	}
}

PRIVATE void CC
ansitty_print_escape(struct ansitty *__restrict self) {
	size_t unused;
	assert(self->at_esclen <= COMPILER_LENOF(self->at_escape));
	unused = self->at_ttyflag & ANSITTY_FLAG_BOXMODE
	         ? ansitty_printutf8_box(self, (char *)self->at_escape, self->at_esclen)
	         : ansitty_printutf8(self, (char *)self->at_escape, self->at_esclen);
	if likely(unused == 0) {
		ansitty_setstate_text(self);
	} else {
		ansitty_setstate_mbs(self);
		memmove(self->at_escape,
		        self->at_escape + self->at_esclen - unused,
		        unused * sizeof(char));
		self->at_escwrd[0] = unicode_utf8seqlen[(byte_t)self->at_escape[0]];
		self->at_escwrd[1] = (__UINTPTR_HALF_TYPE__)unused;
		assert(self->at_escwrd[0] != 0);
		assert(self->at_escwrd[0] != 1);
		assert(self->at_escwrd[1] < self->at_escwrd[0]);
	}
}

LOCAL void CC
ansitty_do_insert_nobox(struct ansitty *__restrict self, char32_t ch) {
	switch (self->at_ttyflag & (ANSITTY_FLAG_HEDIT |
	                            ANSITTY_FLAG_INSDEL_LINE)) {

	case 0:
		/* 123456789      123456789
		 * ABCDEFGHI  --> ABCD...EF
		 * abcdefghi      GHIabcdef */
		COPYCELL(1, MAXCOORD);
		PUTUNI(ch);
		break;

	case ANSITTY_FLAG_INSDEL_LINE: {
		/* 123456789      123456789
		 * ABCDEFGHI  --> ABCD...EF
		 * abcdefghi      abcdefghi */
		ansitty_coord_t xy[2];
		ansitty_coord_t sxy[2];
		ansitty_coord_t cells_in_line;
		GETCURSOR(xy);
		SETCURSOR(MAXCOORD, MAXCOORD);
		GETCURSOR(sxy);
		SETCURSOR(xy[0], xy[1]);
		++sxy[0];
		if unlikely(xy[0] >= sxy[0])
			break;
		cells_in_line = sxy[0] - xy[0];
		if (1 >= cells_in_line)
			break;
		COPYCELL(1, cells_in_line - 1);
		PUTUNI(ch);
	}	break;

	case ANSITTY_FLAG_HEDIT: {
		ansitty_coord_t xy[2];
		ansitty_coord_t xy2[2];
		unsigned int copy_count;
		/* 123456789      456789ABC
		 * ABCDEFGHI  --> D...EFGHI
		 * abcdefghi      abcdefghi */
		GETCURSOR(xy);
		if (xy[1] == 0) {
			if (xy[0] <= 1) {
				if (xy[0] == 0)
					break;
				SETCURSOR(0, 0);
				PUTUNI(ch);
				break;
			}
			copy_count = xy[0];
		} else {
			SETCURSOR(MAXCOORD, 0);
			GETCURSOR(xy2);
			copy_count = xy[0] + xy[1] * (xy2[0] + 1);
		}
		SETCURSOR(1, 0);
		COPYCELL(-1, copy_count);
		if (!xy[0]) {
			--xy[1];
			xy[0] = MAXCOORD;
		} else {
			--xy[0];
		}
		SETCURSOR(xy[0], xy[1]);
		PUTUNI(ch);
	}	break;

	case ANSITTY_FLAG_HEDIT | ANSITTY_FLAG_INSDEL_LINE: {
		ansitty_coord_t xy[2];
		/* 123456789      123456789
		 * ABCDEFGHI  --> D...EFGHI
		 * abcdefghi      abcdefghi */
		GETCURSOR(xy);
		if (xy[0] <= 1) {
			/* Full area shift */
			if (xy[0] == 0)
				break;
			SETCURSOR(0, xy[1]);
			PUTUNI(ch);
			break;
		}
		SETCURSOR(1, xy[1]);
		COPYCELL(-1, xy[0] - 1);
		SETCURSOR(xy[0] - 1, xy[1]);
		PUTUNI(ch);
	}	break;

	default: __builtin_unreachable();
	}
}

LOCAL void CC
ansitty_do_insert(struct ansitty *__restrict self, char32_t ch) {
	if (self->at_ttyflag & ANSITTY_FLAG_BOXMODE) {
		if (ch >= BOX_CHARS_START &&
		    ch < (BOX_CHARS_START + COMPILER_LENOF(box_chars)))
			ch = box_chars[ch - BOX_CHARS_START];
	}
	ansitty_do_insert_nobox(self, ch);
}


LOCAL void CC
ansitty_do_repeat(struct ansitty *__restrict self, char32_t ch) {
	unsigned int count;
	count = STATE_REPEAT_COUNT(self);
	/* Translate box characters. */
	if (self->at_ttyflag & ANSITTY_FLAG_BOXMODE) {
		if (ch >= BOX_CHARS_START &&
		    ch < (BOX_CHARS_START + COMPILER_LENOF(box_chars)))
			ch = box_chars[ch - BOX_CHARS_START];
	}
	if (self->at_ttyflag & ANSITTY_FLAG_INSERT) {
		while (count--) {
			ansitty_do_insert_nobox(self, ch);
		}
	} else {
		while (count--) {
			PUTUNI((char32_t)(uint8_t)ch);
		}
	}
}


LOCAL void CC
ansitty_putmbs(struct ansitty *__restrict self, char ch) {
	assert(self->at_state == STATE_MBS ||
	       self->at_state == STATE_BOX_MBS ||
	       self->at_state == STATE_REPEAT_MBS);
	assert(self->at_escwrd[1] < self->at_escwrd[0]);
	self->at_escape[self->at_escwrd[1]++] = (byte_t)ch;
	if (self->at_escwrd[1] >= self->at_escwrd[0]) {
		/* Unicode sequence has been completed. */
		char const *text;
		char32_t unich;
		assert(self->at_escwrd[1] == self->at_escwrd[0]);
		text  = (char *)self->at_escape;
		unich = unicode_readutf8(&text);
		assert(text == ((char *)self->at_escape + self->at_escwrd[0]));
		/* Check for the escape character */
		if unlikely(unich == ESC) {
			self->at_state = STATE_ESC;
		} else if unlikely(unich == CAN) {
			ansitty_setstate_text(self);
		} else if (self->at_state == STATE_BOX_MBS) {
			ansitty_putbox(self, unich);
			self->at_state = STATE_BOX;
		} else if (self->at_state == STATE_REPEAT_MBS) {
			ansitty_do_repeat(self, unich);
			ansitty_setstate_text(self);
		} else if (self->at_state == STATE_INSERT_MBS) {
			ansitty_do_insert(self, unich);
			self->at_state = STATE_INSERT;
		} else {
			PUTUNI(unich);
			self->at_state = STATE_TEXT;
		}
	}
}


PRIVATE bool CC ansitty_invoke_string_command(struct ansitty *__restrict self) {
	bool result;
	self->at_escape[self->at_esclen] = 0;
	switch (self->at_state) {

	case STATE_OSC:
	case STATE_OSC_ESC:
		result = ansi_OSC(self, (char *)self->at_escape, self->at_esclen);
		break;

	case STATE_DCS:
	case STATE_DCS_ESC:
		result = ansi_DCS(self, (char *)self->at_escape, self->at_esclen);
		break;

	case STATE_SOS:
	case STATE_SOS_ESC:
		result = ansi_SOS(self, (char *)self->at_escape, self->at_esclen);
		break;

	case STATE_PM:
	case STATE_PM_ESC:
		result = ansi_PM(self, (char *)self->at_escape, self->at_esclen);
		break;

	case STATE_APC:
	case STATE_APC_ESC:
		result = ansi_APC(self, (char *)self->at_escape, self->at_esclen);
		break;

	default: __builtin_unreachable();
	}
	return result;
}

PRIVATE char CC
get_string_command_start_character(uintptr_t state) {
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

	default: __builtin_unreachable();
	}
	return result;
}

PRIVATE void CC
do_print_string_command_control_character(struct ansitty *__restrict self) {
	PUTUNI(get_string_command_start_character(self->at_state));
}


/* Output a single utf-8 character to the given TTY */
INTERN NONNULL((1)) void CC
libansitty_putc(struct ansitty *__restrict self, /*utf-8*/ char ch) {
again:
	switch (self->at_state) {

	case STATE_TEXT:
		/* Check for the escape character */
		switch ((uint8_t)ch) {

		case ESC:
set_esc_state:
			self->at_state = STATE_ESC;
			break;

		case CAN:
			break; /* Ignore... */

		case 0x80 ... 0xff:
			/* Begin a new multi-byte character sequence. */
			self->at_escwrd[0] = unicode_utf8seqlen[(byte_t)ch];
			if unlikely(!self->at_escwrd[0])
				goto do_putuni; /* Invalid utf-8 byte... (simply re-output, thus ignoring the error) */
			assert(self->at_escwrd[0] != 1);
			self->at_escwrd[1] = 1;
			self->at_escape[0] = (byte_t)ch;
			self->at_state     = STATE_MBS;
			break;

		case '\n':
			if (self->at_ttyflag & ANSITTY_FLAG_NOLFCR) {
				/* LF shouldn't set COLUMN=0 */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				if (xy[0] != 0) {
					/* Current column is non-zero, so we must take special
					 * action to ensure that the cursor is placed correctly. */
					PUTUNI('\n');
					/* Reset the cursor position to the middle of the following line.
					 * Note that in the case of the previous line being the bottom-most one,
					 * SETCURSOR() will clamp that coord into the valid display range. */
					SETCURSOR(xy[0], xy[1] + 1);
					break;
				}
			}
			ATTR_FALLTHROUGH
		default:
			/* Output a regular, old ASCII character. */
do_putuni:
			PUTUNI((char32_t)(uint8_t)ch);
			break;
		}
		break;

	case STATE_BOX:
		/* Check for the escape character */
		if ((uint8_t)ch == ESC)
			goto set_esc_state;
		if ((uint8_t)ch <= 0x7f) {
			/* Output a regular, old ASCII character. */
do_putuni_box:
			ansitty_putbox(self, (char32_t)(uint8_t)ch);
			return;
		}
		/* Begin a new multi-byte character sequence. */
		self->at_escwrd[0] = unicode_utf8seqlen[(byte_t)ch];
		if unlikely(!self->at_escwrd[0])
			goto do_putuni_box; /* Invalid utf-8 byte... (simply re-output, thus ignoring the error) */
		assert(self->at_escwrd[0] != 1);
		self->at_escwrd[1] = 1;
		self->at_escape[0] = (byte_t)ch;
		self->at_state     = STATE_BOX_MBS;
		break;

	case STATE_REPEAT:
		/* Check for the escape character */
		if ((uint8_t)ch == ESC)
			goto set_esc_state;
		if ((uint8_t)ch == CAN)
			goto set_text_and_done; /* Cancel the repeat. */
		if ((uint8_t)ch <= 0x7f) {
			/* Output a regular, old ASCII character. */
do_repuni:
			ansitty_do_repeat(self, (char32_t)(uint8_t)ch);
			goto set_text_and_done;
		}
		/* Begin a new multi-byte character sequence. */
		self->at_escwrd[0] = unicode_utf8seqlen[(byte_t)ch];
		if unlikely(!self->at_escwrd[0])
			goto do_repuni; /* Invalid utf-8 byte... (simply re-output, thus ignoring the error) */
		assert(self->at_escwrd[0] != 1);
		self->at_escwrd[1] = 1;
		self->at_escape[0] = (byte_t)ch;
		self->at_state     = STATE_REPEAT_MBS;
		break;

	case STATE_INSERT:
		/* Check for the escape character */
		if ((uint8_t)ch == ESC)
			goto set_esc_state;
		if ((uint8_t)ch == CAN)
			break; /* Ignore */
		if ((uint8_t)ch <= 0x7f) {
			/* Output a regular, old ASCII character. */
do_insuni:
			ansitty_do_insert(self, (char32_t)(uint8_t)ch);
			goto set_text_and_done;
		}
		/* Begin a new multi-byte character sequence. */
		self->at_escwrd[0] = unicode_utf8seqlen[(byte_t)ch];
		if unlikely(!self->at_escwrd[0])
			goto do_insuni; /* Invalid utf-8 byte... (simply re-output, thus ignoring the error) */
		assert(self->at_escwrd[0] != 1);
		self->at_escwrd[1] = 1;
		self->at_escape[0] = (byte_t)ch;
		self->at_state     = STATE_INSERT_MBS;
		break;

	case STATE_MBS:
	case STATE_BOX_MBS:
	case STATE_REPEAT_MBS:
	case STATE_INSERT_MBS:
		ansitty_putmbs(self, ch);
		break;

	case STATE_ESC:
		switch (ch) {

		case 'A':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursorup */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				if (xy[1] != 0)
					SETCURSOR(xy[0], xy[1] - 1);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'B':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursordn */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				SETCURSOR(xy[0], xy[1] + 1);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'C':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursorrt */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				SETCURSOR(xy[0] + 1, xy[1]);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'D':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursorlf */
				ansitty_coord_t xy[2];
				GETCURSOR(xy);
				if (xy[0] != 0)
					SETCURSOR(xy[0] - 1, xy[1]);
				goto set_text_and_done;
			} else {
				/* IND */
				/* Move/scroll window up one line */
				SCROLL(-1);
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
				goto disable_box_mode;
			}
			goto unknown_character_after_esc;

		case 'H':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: cursorhome */
				SETCURSOR(0, 0);
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'I':
			if (self->at_ttyflag & ANSITTY_FLAG_VT52) {
				/* VT52: revindex */
				/* Generate a reverse line-feed (XXX: Is this correct?) */
				SCROLL(1);
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
				OUTPUT(SESC "/Z");
				goto set_text_and_done;
			}
			goto unknown_character_after_esc;

		case 'M': /* RI */
			/* Move/scroll window down one line */
			SCROLL(1);
			goto set_text_and_done;

		case 'E': /* NEL */
			/* Move to next line */
			PUTUNI('\n');
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
			PUTUNI(BEL);
			goto set_text_and_done;

		case 'Y':
			self->at_state = STATE_ESC_Y1;
			break;

		case 'c':
			/* Reset graphics, tabs, font and color. */
			setflags(self, ANSITTY_FLAG_NORMAL);
			setattrib(self, ANSITTY_ATTRIB_DEFAULT);
			setttymode(self, ANSITTY_MODE_DEFAULT);
			setcolor(self, self->at_defcolor);
			setscrollregion(self, 0, MAXCOORD);
			self->at_scroll_sc = 0;
			self->at_scroll_ec = MAXCOORD;
			goto set_text_and_done;

		case '[':
			self->at_esclen = 0;
			self->at_state  = STATE_CSI;
			break;

		case CAN: /* Cancel */
set_text_and_done:
			ansitty_setstate_text(self);
			break;

		default:
unknown_character_after_esc:
			WARN_UNKNOWN_SEQUENCE1(ch);
			PUTUNI(ESC);
			goto reset_state;
		}
		break;

	case STATE_LPAREN:
		switch (ch) {

		case '0':
		case '1': /* ??? */
		case '2': /* ??? */
			/* Enable BOX mode. */
enable_box_mode:
			self->at_ttyflag |= ANSITTY_FLAG_BOXMODE;
			self->at_state = STATE_BOX;
			break;

		case 'A': /* ??? */
		case 'B':
			/* Disable BOX mode. */
disable_box_mode:
			self->at_ttyflag &= ~ANSITTY_FLAG_BOXMODE;
			self->at_state = STATE_TEXT;
			if (self->at_ttyflag & ANSITTY_FLAG_INSERT)
				self->at_state = STATE_INSERT;
			break;

		case CAN: /* Cancel */
			goto set_text_and_done;

		default:
			WARN_UNKNOWN_SEQUENCE2('(', ch);
			PUTUNI(ESC);
			PUTUNI('(');
			goto reset_state;
		}
		break;

	case STATE_CSI:
		assert(self->at_esclen < COMPILER_LENOF(self->at_escape));
		if (ch >= ANSI_LOW && ch <= ANSI_HIGH) {
			/* Process escape argument. */
do_process_csi:
			self->at_escape[self->at_esclen] = 0;
			ansitty_setstate_text(self);
			if (!ansi_CSI(self, (char *)self->at_escape, self->at_esclen, ch)) {
				WARN_UNKNOWN_SEQUENCE3('[', self->at_esclen, self->at_escape, ch);
				PUTUNI(ESC);
				PUTUNI('[');
print_escape_and_reset_state:
				ansitty_print_escape(self);
				goto reset_state;
			}
			break;
		}
		if (ch == CAN) /* Cancel */
			goto set_text_and_done;
		self->at_escape[self->at_esclen] = (byte_t)ch;
		++self->at_esclen;
		if unlikely(self->at_esclen >= COMPILER_LENOF(self->at_escape)) {
			assert(self->at_esclen == COMPILER_LENOF(self->at_escape));
			goto do_process_csi;
		}
		break;

	case STATE_OSC_ESC:
	case STATE_DCS_ESC:
	case STATE_SOS_ESC:
	case STATE_PM_ESC:
	case STATE_APC_ESC:
		assert(self->at_esclen < COMPILER_LENOF(self->at_escape));
		if ((byte_t)ch == '\\') {
			if (!ansitty_invoke_string_command(self)) {
				WARN_UNKNOWN_SEQUENCE4(get_string_command_start_character(self->at_state),
				                       self->at_esclen, self->at_escape, ESC, ch);
				PUTUNI(ESC);
				do_print_string_command_control_character(self);
				ansitty_print_escape(self);
				if (self->at_state == STATE_TEXT ||
				    self->at_state == STATE_BOX ||
				    self->at_state == STATE_INSERT)
					self->at_state = STATE_ESC;
				else {
					ansitty_putmbs(self, ESC);
				}
				goto reset_state;
			}
			goto set_text_and_done;
		} else if (ch == CAN) { /* Cancel */
			goto set_text_and_done;
		}
		self->at_escape[self->at_esclen] = ESC;
		++self->at_esclen;
		if unlikely(self->at_esclen >= COMPILER_LENOF(self->at_escape))
			goto do_process_string_command;
		self->at_escape[self->at_esclen] = (byte_t)ch;
		++self->at_esclen;
		if unlikely(self->at_esclen >= COMPILER_LENOF(self->at_escape))
			goto do_process_string_command;
		self->at_state = STATE_OSC_DEL_ESC(self->at_state);
		break;

	case STATE_OSC:
	case STATE_DCS:
	case STATE_SOS:
	case STATE_PM:
	case STATE_APC:
		assert(self->at_esclen < COMPILER_LENOF(self->at_escape));
		if ((byte_t)ch == BEL) {
do_process_string_command:
			if (!ansitty_invoke_string_command(self)) {
				WARN_UNKNOWN_SEQUENCE3(get_string_command_start_character(self->at_state),
				                       self->at_esclen, self->at_escape, BEL);
				PUTUNI(ESC);
				do_print_string_command_control_character(self);
				ansitty_setstate_text(self);
				goto print_escape_and_reset_state;
			}
			goto set_text_and_done;
		} else if ((byte_t)ch == ESC) {
			self->at_state = STATE_OSC_ADD_ESC(self->at_state);
			break;
		} else if (ch == CAN) { /* Cancel */
			goto set_text_and_done;
		}
		self->at_escape[self->at_esclen] = (byte_t)ch;
		++self->at_esclen;
		if unlikely(self->at_esclen >= COMPILER_LENOF(self->at_escape)) {
			assert(self->at_esclen == COMPILER_LENOF(self->at_escape));
			goto do_process_string_command;
		}
		break;

	case STATE_ESC_5:
		if (ch == 'n') {
			/* VT100: devstat DSR */
			/* termok DSR  --- Response: terminal is OK */
			OUTPUT(SESC "0n");
			goto set_text_and_done;
		} else if (ch == CAN) {
			goto set_text_and_done;
		}
		WARN_UNKNOWN_SEQUENCE3C(ESC, '5', ch);
		PUTUNI(ESC);
		PUTUNI('5');
		goto reset_state;

	case STATE_ESC_6:
		if (ch == 'n') {
			char buf[32];
			ansitty_coord_t xy[2];
			size_t len;
			/* VT100: getcursor DSR */
			/* Response: cursor is at v,h */
			GETCURSOR(xy);
			len = sprintf(buf, SESC "%u;%uR",
			              (unsigned int)(xy[0] + 1),
			              (unsigned int)(xy[1] + 1));
			DOOUTPUT(buf, len);
			goto set_text_and_done;
		} else if (ch == CAN) {
			goto set_text_and_done;
		}
		WARN_UNKNOWN_SEQUENCE3C(ESC, '6', ch);
		PUTUNI(ESC);
		PUTUNI('6');
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
			/* Screen alignment display (whatever it is. - Ignore it...) */
			/* TODO: screen(1) documents this one as:
			 *     ESC # 8               (V)  Fill Screen with E's
			 * So I guess that's a simple enough explanation, although I'm not
			 * entirely sure if there's some kind of joke I'm missing, or if
			 * this one's _literally_ supposed?? to fill the entire screen with
			 * all E's (I mean: don't get me wrong. How often didn't I want a
			 * screen full of E's, wishing there was an easier way of getting
			 * them all...)
			 */
			goto set_text_and_done;

		case CAN:
			goto set_text_and_done;

		default:
			break;
		}
		WARN_UNKNOWN_SEQUENCE3C(ESC, '#', ch);
		PUTUNI(ESC);
		PUTUNI('#');
		goto reset_state;

	case STATE_ESC_Y1:
		if ((byte_t)ch < 32) {
			if (ch == CAN)
				goto set_text_and_done;
			WARN_UNKNOWN_SEQUENCE3C(ESC, 'Y', ch);
			PUTUNI(ESC);
			PUTUNI('Y');
			goto reset_state;
		}
		STATE_ESC_Y1_VAL(self) = (uint8_t)ch - 32;
		self->at_state = STATE_ESC_Y2;
		break;

	case STATE_ESC_Y2:
		/* ESC Y Ps Ps    Move the cursor to given row and column.
		 * Parameters for cursor movement are at the end of the ESC Y  escape
		 * sequence.  Each ordinate is encoded in a single character as value+32.
		 * For example, !  is 1.  The screen coordinate system is 0-based. */
		if ((byte_t)ch < 32) {
			if (ch == CAN)
				goto set_text_and_done;
			WARN_UNKNOWN_SEQUENCE4C(ESC, 'Y', 32 + STATE_ESC_Y1_VAL(self), ch);
			PUTUNI(ESC);
			PUTUNI('Y');
			PUTUNI(32 + STATE_ESC_Y1_VAL(self));
			goto reset_state;
		}
		/* Set the cursor position. */
		SETCURSOR((byte_t)ch - 32, STATE_ESC_Y1_VAL(self));
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
	char utf8_seq[UNICODE_UTF8_MAXLEN];
	size_t i, utf8_len;
	/* Simple case: Default state and non-escaping character */
	if (self->at_state == STATE_TEXT) {
		if unlikely(ch == ESC) {
			self->at_state = STATE_ESC;
		} else {
			PUTUNI(ch);
		}
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
INTERN NONNULL((1)) ssize_t __LIBCCALL
libansitty_printer(void *arg, char const *data, size_t datalen) {
	size_t i;
	struct ansitty *self;
	self = (struct ansitty *)arg;
	for (i = 0; i < datalen; ++i) {
		libansitty_putc(self, data[i]);
	}
	return (ssize_t)datalen;
}


DEFINE_PUBLIC_ALIAS(ansitty_init, libansitty_init);
DEFINE_PUBLIC_ALIAS(ansitty_putc, libansitty_putc);
DEFINE_PUBLIC_ALIAS(ansitty_putuni, libansitty_putuni);
DEFINE_PUBLIC_ALIAS(ansitty_printer, libansitty_printer);


DECL_END

#endif /* !GUARD_LIBANSITTY_ANSITTY_C */
