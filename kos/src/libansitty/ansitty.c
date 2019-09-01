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

#include "ansitty.h"

DECL_BEGIN

#define BEL  '\7'
#define ESC  '\033' /* '\e' */
#define SESC "\033" /* "\e" */

#if 0
#define TRACE_OPERATION DOTRACE
#else
#define TRACE_OPERATION TRACE
#endif

#define PUTUNI(uni)         (*self->at_ops.ato_putc)(self, uni)
#define GETCURSOR(pxy)      ((*self->at_ops.ato_getcursor)(self, pxy), TRACE_OPERATION("getcur:{%u,%u}\n", (pxy)[0], (pxy)[1]))
#define SETCURSOR(x, y)     (TRACE_OPERATION("setcur(%u,%u)\n", x, y), (*self->at_ops.ato_setcursor)(self, x, y))
#define SETCOLOR(color)     (TRACE_OPERATION("setcolor(%#x)\n", color), (*self->at_ops.ato_setcolor)(self, color))
#define SETTTYMODE(ttymode) (TRACE_OPERATION("setttymode(%#x)\n", ttymode), self->at_ops.ato_setttymode ? (*self->at_ops.ato_setttymode)(self, ttymode) : (void)0)
#define SETATTRIB(attrib)   (TRACE_OPERATION("setattrib(%#x)\n", attrib), self->at_ops.ato_setattrib ? (*self->at_ops.ato_setattrib)(self, attrib) : (void)0)
#define SETTITLE(title)     (TRACE_OPERATION("settitle(%q)\n", title), (self->at_ops.ato_settitle ? (*self->at_ops.ato_settitle)(self, title) : (void)0))
#define DOOUTPUT(text, len) (TRACE_OPERATION("output(%$q)\n", len, text), (*self->at_ops.ato_output)(self, text, len))
#define OUTPUT(text)        (TRACE_OPERATION("output(%q)\n", text), self->at_ops.ato_output ? (*self->at_ops.ato_output)(self, text, COMPILER_STRLEN(text)) : (void)0)
#define SCROLL(offset)      (TRACE_OPERATION("scroll(%d)\n", (int)(offset)), (*self->at_ops.ato_scroll)(self, offset))
#define CLS(mode)           (TRACE_OPERATION("cls(%u)\n", mode), (*self->at_ops.ato_cls)(self, mode))
#define EL(mode)            (TRACE_OPERATION("el(%u)\n", mode), (*self->at_ops.ato_el)(self, mode))
#define SCROLLREGION(start_line, end_line)                           \
	(TRACE_OPERATION("scrollregion(%u,%u)\n", start_line, end_line), \
	 self->at_ops.ato_scrollregion                                   \
	 ? (*self->at_ops.ato_scrollregion)(self, start_line, end_line)  \
	 : (void)0)

#define MAXCOORD        ((ansitty_coord_t)-1)

/* Values for `at_ttyflag' */
#define ANSITTY_FLAG_NORMAL       0x0000 /* Normal flags */
#define ANSITTY_FLAG_CONCEIL      0x0001 /* FLAG: Use background color as foreground */
#define ANSITTY_FLAG_BOXMODE      0x0002 /* FLAG: Box mode enabled. */
#define ANSITTY_FLAG_RENDERMASK  (ANSITTY_FLAG_CONCEIL) /* Mask for flags that affect rendering */


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
	switch (mode) {

	case ANSITTY_CLS_AFTER:
		GETCURSOR(xy);
		SETCURSOR(MAXCOORD, MAXCOORD);
		GETCURSOR(sxsy);
		SETCURSOR(x, y);
		i = (((sy + 1) - y) * (sx + 1)) - x;
		break;

	case ANSITTY_CLS_BEFORE:
		GETCURSOR(xy);
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
}

PRIVATE NONNULL((1)) void CC
stub_scroll(struct ansitty *__restrict self,
            ansitty_offset_t offset) {
	if (offset <= 0)
		return;
	while (offset--) {
		SETCURSOR(MAXCOORD, MAXCOORD);
		PUTUNI('\n');
	}
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
	if (!self->at_ops.ato_scroll)
		self->at_ops.ato_scroll = &stub_scroll;
	self->at_color      = ANSITTY_CL_DEFAULT;
	self->at_defcolor   = ANSITTY_CL_DEFAULT;
	self->at_ttyflag    = ANSITTY_FLAG_NORMAL;
	self->at_ttymode    = ANSITTY_MODE_DEFAULT;
	self->at_attrib     = ANSITTY_ATTRIB_DEFAULT;
	self->at_savecur[0] = 0;
	self->at_savecur[0] = 0;
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
	if (*pos == ';' && code == 1) {
		SETTITLE(pos + 1);
		return true;
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



/* "\e[{arg[arglen]:%s}{lastch}" */
PRIVATE bool CC
ansi_CSI(struct ansitty *__restrict self,
         char *__restrict arg, size_t arglen,
         char lastch) {
	switch (lastch) {

	case 'A':   /* CUU */
	case 'B':   /* CUD */
	case 'C':   /* CUF */
	case 'D':   /* CUB */
	case 'E':   /* CNL */
	case 'F':   /* CPL */
	case 'G':   /* CHA */
	case 'S':   /* SU */
	case 'T': { /* SD */
		int n;
		if (!arglen)
			n = 1;
		else {
			char *end;
			n = (int)strtol(arg, &end, 10);
			if unlikely(end != arg + arglen)
				goto nope;
		}
		switch (lastch) {

		case 'A': /* CUU */
			n = -n;
			ATTR_FALLTHROUGH
		case 'B': { /* CUD */
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			n += xy[1];
			if (n < 0)
				n = 0;
			SETCURSOR(xy[0], (ansitty_coord_t)n);
		}	break;

		case 'D': /* CUB */
			n = -n;
			ATTR_FALLTHROUGH
		case 'C': { /* CUF */
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			n += xy[0];
			if (n < 0)
				n = 0;
			SETCURSOR((ansitty_coord_t)n, xy[1]);
		}	break;

		case 'F': /* CPL */
			n = -n;
			ATTR_FALLTHROUGH
		case 'E': { /* CNL */
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			n += xy[1];
			if (n < 0)
				n = 0;
			SETCURSOR(0, (ansitty_coord_t)n);
		}	break;

		case 'G': { /* CHA */
			ansitty_coord_t xy[2];
			if (n < 0)
				n = 0;
			if (n)
				--n;
			GETCURSOR(xy);
			SETCURSOR((ansitty_coord_t)n, xy[1]);
		}	break;

		case 'S': /* SU */
			n = -n;
			ATTR_FALLTHROUGH
		case 'T': /* SD */
			SCROLL((ansitty_offset_t)n);
			break;

		default: __builtin_unreachable();
		}
	}	break;

	case 'H':   /* CUP */
	case 'f': { /* HVP */
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

	case 'J': /* ED */
	case 'K': /* EL */
	{
		unsigned int mode;
		if (!arglen)
			mode = 0;
		else {
			char *end;
			mode = (unsigned int)strtoul(arg, &end, 10);
			if unlikely(end != arg + arglen)
				goto nope;
		}
		if (lastch == 'J') {
			if unlikely(mode > ANSITTY_CLS_ALLPAGES)
				mode = ANSITTY_CLS_ALLPAGES;
			CLS(mode);
		} else {
			if unlikely(mode > ANSITTY_EL_ALL)
				mode = ANSITTY_EL_ALL;
			EL(mode);
		}
	}	break;

	case 'i':
		if (arglen == 1) {
			if (arg[0] == '4') {
				setttymode(self, self->at_ttymode & ~ANSITTY_MODE_AUXPORT);
			} else if (arg[0] == '5') {
				setttymode(self, self->at_ttymode | ANSITTY_MODE_AUXPORT);
			} else {
				goto nope;
			}
		} else {
			goto nope;
		}
		break;

	case 's':
		if (arglen != 0)
			goto nope;
		savecursor(self);
		break;

	case 'u':
		if (arglen != 0)
			goto nope;
		loadcursor(self);
		break;

	case 'c':
		if (arglen != 0)
			goto nope;
		/* Query Device Code
		 * NOTE: Aparently we can return some {code} before the 0c,
		 *       but I don't know what kind of code that would be... */
		OUTPUT(SESC "[0c");
		break;

	case 'n':
		if (arglen == 1) {
			if (arg[0] == '6') {
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
			} else if (arg[0] == '5') {
				/* Query Device Status */
				OUTPUT(SESC "[0n");
			} else {
				goto nope;
			}
		} else {
			goto nope;
		}
		break;

	case 'h':
	case 'l': {
		unsigned int code;
		char *end;
		if (arg[0] == '?') {
			code = (unsigned int)strtoul(arg + 1, &end, 10);
			if (end == arg + 1 || end != arg + arglen)
				goto nope;
			switch (code) {

			case 0:
				/* Must be ignored. */
				break;

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

			case 25:
				setttymode(self, (self->at_ttymode & ~ANSITTY_MODE_HIDECURSOR) |
				                 (lastch == 'h' ? 0 : ANSITTY_MODE_HIDECURSOR));
				break;

			default:
				goto nope;
			}
			break;
		} else {
			code = (unsigned int)strtoul(arg, &end, 10);
			if (end == arg || end != arg + arglen)
				goto nope;
			switch (code) {

			case 0:
				/* Must be ignored. */
				break;

			case 6:
				setattrib(self, (self->at_attrib & ~ANSITTY_MODE_NOLINEWRAP) |
				                (lastch == 'h' ? ANSITTY_MODE_NOLINEWRAP : 0));
				break;

			case 20:
				/* new-line / line-feed mode??? */
				break;

			default:
				goto nope;
			}
		}
	}	break;

	case 'r': {
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
		SCROLLREGION(startline, endline);
	}	break;

	case 'm': {
		unsigned int code;
		char *iter, *end;
		/* SGR */
		if (!arglen) {
			setcolor(self, self->at_defcolor);
			setattrib(self, ANSITTY_ATTRIB_DEFAULT);
			setflags(self, self->at_ttyflag & ~ANSITTY_FLAG_RENDERMASK);
			break;
		}
		iter = arg;
again_sgr:
		code = strtoul(iter, &end, 10);
		if (*end != ';' && end != arg + arglen)
			goto nope;
		switch (code) {

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
			if (*end != ';')
				goto nope;
			++end;
			if (*end != '5' && *end != '2')
				goto nope;
			color_mode = *end - '0';
			++end;
			if (*end != ';')
				goto nope;
			++end;
			if (color_mode == 2) {
				unsigned int r, g, b;
				r = (unsigned int)strtoul(end, &end, 10);
				if (*end != ';')
					goto nope;
				++end;
				g = (unsigned int)strtoul(end, &end, 10);
				if (*end != ';')
					goto nope;
				++end;
				b = (unsigned int)strtoul(end, &end, 10);
				if (*end != ';' && end != arg + arglen)
					goto nope;
				++end;
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
				used_color_index = (unsigned int)strtoul(end, &end, 10);
				if (*end != ';' && end != arg + arglen)
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

		default:
			goto nope;
		}
		if (end != arg + arglen) {
			iter = end + 1;
			goto again_sgr;
		}
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


/* TTY states */
#define STATE_TEXT     0 /* Default state: at the start of the next character. */
#define STATE_MBS      1 /* Inside of a multi-byte-character-string (same as `STATE_TEXT', \
                          * but `at_esclen' is non-NULL and refers to the number of UTF-8  \
                          * characters already present within `at_escape') */
#define STATE_ESC      2 /* State set immediately after a `\e' character was encountered */
#define STATE_CSI      3 /* Process escape arguments. */
#define STATE_OSC      4 /* Operating System Command reception mode. */
#define STATE_DCS      5 /* Device control string reception mode. */
#define STATE_SOS      6 /* Start of String reception mode. */
#define STATE_PM       7 /* Privacy Message reception mode. */
#define STATE_APC      8 /* Application Program Command reception mode. */
#define STATE_OSC_ESC  9 /* `STATE_OSC', followed by ESC */
#define STATE_DCS_ESC 10 /* `STATE_DCS', followed by ESC */
#define STATE_SOS_ESC 11 /* `STATE_SOS', followed by ESC */
#define STATE_PM_ESC  12 /* `STATE_PM', followed by ESC */
#define STATE_APC_ESC 13 /* `STATE_APC', followed by ESC */
#define STATE_LPAREN  14 /* After `ESC(' */
#define STATE_BOX     15 /* Box rendering mode. */
#define STATE_BOX_MBS 16 /* Box rendering mode (multi-byte string). */

#define STATE_OSC_ADD_ESC(x) ((x)+5)
#define STATE_OSC_DEL_ESC(x) ((x)-5)


/* Anything in this range (should) exit escape mode. */
#define ANSI_LOW       'A'
#define ANSI_HIGH      'z'


PRIVATE void CC
ansitty_setstate_text(struct ansitty *__restrict self) {
	self->at_state = STATE_TEXT;
	if (self->at_ttyflag & ANSITTY_FLAG_BOXMODE)
		self->at_state = STATE_BOX;
}

PRIVATE void CC
ansitty_setstate_mbs(struct ansitty *__restrict self) {
	self->at_state = STATE_MBS;
	if (self->at_ttyflag & ANSITTY_FLAG_BOXMODE)
		self->at_state = STATE_BOX_MBS;
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
ansitty_putmbs(struct ansitty *__restrict self, char ch) {
	assert(self->at_state == STATE_MBS ||
	       self->at_state == STATE_BOX_MBS);
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
		} else if (self->at_state == STATE_BOX_MBS) {
			ansitty_putbox(self, unich);
			self->at_state = STATE_BOX;
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

PRIVATE void CC
do_print_string_command_control_character(struct ansitty *__restrict self) {
	switch (self->at_state) {
	case STATE_OSC:
	case STATE_OSC_ESC:
		PUTUNI(']');
		break;
	case STATE_DCS:
	case STATE_DCS_ESC:
		PUTUNI('P');
		break;
	case STATE_SOS:
	case STATE_SOS_ESC:
		PUTUNI('X');
		break;
	case STATE_PM:
	case STATE_PM_ESC:
		PUTUNI('^');
		break;
	case STATE_APC:
	case STATE_APC_ESC:
		PUTUNI('_');
		break;
	default: __builtin_unreachable();
	}
}


/* Output a single utf-8 character to the given TTY */
INTERN NONNULL((1)) void CC
libansitty_putc(struct ansitty *__restrict self, /*utf-8*/ char ch) {
again:
	switch (self->at_state) {

	case STATE_TEXT:
		/* Check for the escape character */
		if ((uint8_t)ch == ESC) {
set_esc_state:
			self->at_state = STATE_ESC;
			break;
		}
		if ((uint8_t)ch <= 0x7f) {
			/* Output a regular, old ASCII character. */
do_putuni:
			PUTUNI((char32_t)(uint8_t)ch);
			return;
		}
		/* Begin a new multi-byte character sequence. */
		self->at_escwrd[0] = unicode_utf8seqlen[(byte_t)ch];
		if unlikely(!self->at_escwrd[0])
			goto do_putuni; /* Invalid utf-8 byte... (simply re-output, thus ignoring the error) */
		assert(self->at_escwrd[0] != 1);
		self->at_escwrd[1] = 1;
		self->at_escape[0] = (byte_t)ch;
		self->at_state     = STATE_MBS;
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

	case STATE_MBS:
	case STATE_BOX_MBS:
		ansitty_putmbs(self, ch);
		break;

	case STATE_ESC:
		switch (ch) {

		case 'A': {
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			if (xy[1] != 0)
				SETCURSOR(xy[0], xy[1] - 1);
		}	break;

		case 'B': {
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			SETCURSOR(xy[0], xy[1] + 1);
		}	break;

		case 'C': {
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			SETCURSOR(xy[0] + 1, xy[1]);
		}	break;

		case 'D': {
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			if (xy[0] != 0)
				SETCURSOR(xy[0] - 1, xy[1]);
		}	break;

		case 'H': {
			ansitty_coord_t xy[2];
			GETCURSOR(xy);
			SETCURSOR(0, xy[1]);
		}	break;

		case '(':
			self->at_state = STATE_LPAREN;
			break;

		case '7':
			savecursor(self);
			ansitty_setstate_text(self);
			break;

		case '8':
			loadcursor(self);
			ansitty_setstate_text(self);
			break;

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

		case '\\': /* String terminator. */
			ansitty_setstate_text(self);
			break;

		case 'c':
			/* Reset graphics, tabs, font and color. */
			setflags(self, ANSITTY_FLAG_NORMAL);
			setattrib(self, ANSITTY_ATTRIB_DEFAULT);
			setttymode(self, ANSITTY_MODE_DEFAULT);
			setcolor(self, self->at_defcolor);
			SCROLLREGION(0, MAXCOORD);
			ansitty_setstate_text(self);
			break;

		case '[':
			self->at_esclen = 0;
			self->at_state  = STATE_CSI;
			break;

		default:
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
			self->at_ttyflag |= ANSITTY_FLAG_BOXMODE;
			self->at_state = STATE_BOX;
			break;

		case 'A': /* ??? */
		case 'B':
			/* Disable BOX mode. */
			self->at_ttyflag &= ~ANSITTY_FLAG_BOXMODE;
			self->at_state = STATE_TEXT;
			break;

		default:
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
			if (!ansi_CSI(self, (char *)self->at_escape, self->at_esclen, ch)) {
				PUTUNI(ESC);
				PUTUNI('[');
print_escape_and_reset_state:
				ansitty_print_escape(self);
				goto again;
			}
			ansitty_setstate_text(self);
			break;
		}
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
				PUTUNI(ESC);
				do_print_string_command_control_character(self);
				ansitty_print_escape(self);
				if (self->at_state == STATE_TEXT || self->at_state == STATE_BOX)
					self->at_state = STATE_ESC;
				else {
					ansitty_putmbs(self, ESC);
				}
				goto again;
			}
			ansitty_setstate_text(self);
			break;
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
				PUTUNI(ESC);
				do_print_string_command_control_character(self);
				ansitty_setstate_text(self);
				goto print_escape_and_reset_state;
			}
			ansitty_setstate_text(self);
			break;
		} else if ((byte_t)ch == ESC) {
			self->at_state = STATE_OSC_ADD_ESC(self->at_state);
			break;
		}
		self->at_escape[self->at_esclen] = (byte_t)ch;
		++self->at_esclen;
		if unlikely(self->at_esclen >= COMPILER_LENOF(self->at_escape)) {
			assert(self->at_esclen == COMPILER_LENOF(self->at_escape));
			goto do_process_string_command;
		}
		break;

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
