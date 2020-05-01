/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.remove("-O3"))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C 1
#define DISABLE_BRANCH_PROFILING 1
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <debugger/function.h>
#include <debugger/io.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rand.h>
#include <kernel/vm.h>

#include <hybrid/byteorder.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <kos/io/vga.h>
#include <sys/io.h>

#include <assert.h>
#include <format-printer.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

#include <libansitty/ansitty.h>

DECL_BEGIN

#define VGA_VRAM_BASE  0xa0000
#define VGA_VRAM_TEXT  0xb8000
#define VGA_VRAM_SIZE  0x01000


/* macro for composing an 8-bit VGA register
 * index and value into a single 16-bit quantity */
#define VGA_OUT16VAL(v,r)    (((v) << 8)|(r))

/* decide whether we should enable the faster 16-bit VGA register writes */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VGA_OUTW_WRITE 1
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */



/* generic VGA port read/write */
FORCELOCAL NOBLOCK ATTR_DBGTEXT u8 
NOTHROW(KCALL vga_r)(port_t port) {
	return inb_p(port);
}

FORCELOCAL NOBLOCK ATTR_DBGTEXT void
NOTHROW(KCALL vga_w)(port_t port, u8 val) {
	outb_p(port, val);
}

FORCELOCAL NOBLOCK ATTR_DBGTEXT void
NOTHROW(KCALL vga_w_fast)(port_t port, u8 reg, u8 val) {
	outw(port, VGA_OUT16VAL(val, reg));
}

#ifdef VGA_OUTW_WRITE
#if 1
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val)           func##_fast(port_i, reg, val)
#else
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val)          ((port_i+1 == port_d) ? func##_fast(port_i, reg, val) : (func(port_i, reg), func(port_d, val)))
#endif
#else /* VGA_OUTW_WRITE */
#define __VGA_OUTW_SELECTOR(func, port_i, port_d, reg, val)          (func(port_i, reg),func(port_d, val))
#endif /* !VGA_OUTW_WRITE */

/* VGA CRTC register read/write */
LOCAL NOBLOCK ATTR_DBGTEXT u8
NOTHROW(KCALL vga_rcrt)(u8 reg) {
	vga_w(VGA_CRT_IC, reg);
	return vga_r(VGA_CRT_DC);
}

LOCAL NOBLOCK ATTR_DBGTEXT void
NOTHROW(KCALL vga_wcrt)(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_CRT_IC, VGA_CRT_DC, reg, val);
}

/* VGA sequencer register read/write */
LOCAL NOBLOCK ATTR_DBGTEXT u8
NOTHROW(KCALL vga_rseq)(u8 reg) {
	vga_w(VGA_SEQ_I, reg);
	return vga_r(VGA_SEQ_D);
}

LOCAL NOBLOCK ATTR_DBGTEXT void
NOTHROW(KCALL vga_wseq)(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_SEQ_I, VGA_SEQ_D, reg, val);
}

/* VGA graphics controller register read/write */
LOCAL NOBLOCK ATTR_DBGTEXT u8
NOTHROW(KCALL vga_rgfx)(u8 reg) {
	vga_w(VGA_GFX_I, reg);
	return vga_r(VGA_GFX_D);
}

LOCAL NOBLOCK ATTR_DBGTEXT void
NOTHROW(KCALL vga_wgfx)(u8 reg, u8 val) {
	__VGA_OUTW_SELECTOR(vga_w, VGA_GFX_I, VGA_GFX_D, reg, val);
}

/* VGA attribute controller register read/write */
LOCAL NOBLOCK ATTR_DBGTEXT u8
NOTHROW(KCALL vga_rattr)(u8 reg) {
	vga_w(VGA_ATT_IW, reg);
	return vga_r(VGA_ATT_R);
}

LOCAL NOBLOCK ATTR_DBGTEXT void
NOTHROW(KCALL vga_wattr)(u8 reg, u8 val) {
	vga_w(VGA_ATT_IW, reg);
	vga_w(VGA_ATT_W, val);
}



#define VGA_WIDTH  80
#define VGA_HEIGHT 25

/* # of screens stored in the VGA backlog. */
#ifndef VGA_BACKLOG_NUMSCREENS
#define VGA_BACKLOG_NUMSCREENS 8
#endif /* !VGA_BACKLOG_NUMSCREENS */

PUBLIC_CONST ATTR_DBGRODATA unsigned int const dbg_scroll_maxline  = VGA_BACKLOG_NUMSCREENS * VGA_HEIGHT;
PUBLIC_CONST ATTR_DBGRODATA unsigned int const dbg_screen_width    = VGA_WIDTH;
PUBLIC_CONST ATTR_DBGRODATA unsigned int const dbg_screen_height   = VGA_HEIGHT;
PUBLIC_CONST ATTR_DBGRODATA unsigned int const dbg_screen_cellsize = 2;

/* Alignment of TAB characters (default: `DBG_TABSIZE_DEFAULT') */
PUBLIC ATTR_DBGDATA unsigned int dbg_tabsize = 0;

/* Cursor X-position assign after a line-feed */
PUBLIC ATTR_DBGDATA unsigned int dbg_indent = 0;

/* The ANSI TTY used for printing screen-output within the builtin debugger */
PUBLIC ATTR_DBGBSS struct ansitty dbg_tty = {};

PUBLIC ATTR_DBGBSS u16 dbg_attr         = 0; /* Color attributes. */
PUBLIC ATTR_DBGBSS u16 dbg_default_attr = 0; /* Color attributes. */

PRIVATE ATTR_DBGBSS u32  vga_vram_offset         = 0;     /* [const] Current VRAM offset */
PRIVATE ATTR_DBGBSS u16 *vga_real_terminal_start = NULL;  /* [const] Real terminal display start */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_start      = NULL;  /* Terminal display start */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_end        = NULL;  /* Terminal display end */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_cur        = NULL;  /* Terminal display cursor */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_2ndln      = NULL;  /* Start of the second line within the terminal display. */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_lastln     = NULL;  /* Start of the last line within the terminal display. */
PRIVATE ATTR_DBGBSS bool vga_terminal_showcur    = false; /* True if the current cursor position should be shown. */

#define VGA_SETCUR(x, y) (vga_terminal_cur = vga_terminal_start + (y)*VGA_WIDTH + (x))
#define VGA_GETCUR_X()   ((unsigned int)(vga_terminal_cur - vga_terminal_start) % VGA_WIDTH)
#define VGA_GETCUR_Y()   ((unsigned int)(vga_terminal_cur - vga_terminal_start) / VGA_WIDTH)
#define VGA_CHR(ch)      ((u16)(u8)(ch) | dbg_attr)
#define VGA_EMPTY        VGA_CHR(' ')

/* Terminal display backlog */
PRIVATE ATTR_DBGBSS u16 vga_terminal_backlog[VGA_BACKLOG_NUMSCREENS * VGA_WIDTH * VGA_HEIGHT];
#define vga_terminal_backlog_end COMPILER_ENDOF(vga_terminal_backlog)

/* [>= vga_terminal_backlog][< ENDOF(vga_terminal_backlog)]
 * Pointer to the next character to write.
 * NOTE: Always aligned to the start of a line. */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_backlog_cur = NULL;
/* Set to true once old data starts being overwritten. */
PRIVATE ATTR_DBGBSS bool vga_terminal_backlog_full = false;

/* Append a given line to the backlog */
#define VGA_TERMINAL_BACKLOG_ADDLINE(src)                       \
	(memcpyw(vga_terminal_backlog_cur, src, VGA_WIDTH),         \
	 vga_terminal_backlog_cur += VGA_WIDTH,                     \
	 vga_terminal_backlog_cur < vga_terminal_backlog_end        \
	 ? (void)0                                                  \
	 : (void)(vga_terminal_backlog_cur  = vga_terminal_backlog, \
	          vga_terminal_backlog_full = true))

/* Non-zero if display updates should be suppressed. */
PRIVATE ATTR_DBGBSS unsigned int vga_suppress_update = 0;

/* Terminal off-screen buffer (used when `vga_suppress_update' is non-zero) */
PRIVATE ATTR_DBGBSS u16 vga_offscreen_buffer[VGA_WIDTH * VGA_HEIGHT] = { 0 };


PRIVATE ATTR_DBGBSS bool vga_cursor_is_shown = false;
LOCAL ATTR_DBGTEXT void
NOTHROW(FCALL vga_enable_cursor)(void) {
	if (!vga_cursor_is_shown) {
		if (vga_suppress_update == 0) {
			vga_wcrt(VGA_CRTC_CURSOR_START,
			         vga_rcrt(VGA_CRTC_CURSOR_START) & ~(VGA_CRA_FCURSOR_DISABLE));
		}
		vga_cursor_is_shown = true;
	}
}

LOCAL ATTR_DBGTEXT void
NOTHROW(FCALL vga_disable_cursor)(void) {
	if (vga_cursor_is_shown) {
		if (vga_suppress_update == 0) {
			vga_wcrt(VGA_CRTC_CURSOR_START,
			         vga_rcrt(VGA_CRTC_CURSOR_START) | VGA_CRA_FCURSOR_DISABLE);
		}
		vga_cursor_is_shown = false;
	}
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL vga_update_cursor_pos)(void) {
	if (vga_terminal_cur >= vga_terminal_end) {
		vga_disable_cursor();
	} else {
		unsigned int pos;
		pos = (unsigned int)(vga_terminal_cur - vga_terminal_start);
		vga_wcrt(VGA_CRTC_CURSOR_HI, (pos >> 8));
		vga_wcrt(VGA_CRTC_CURSOR_LO, (u8)pos);
		vga_enable_cursor();
	}
}


PRIVATE ATTR_DBGBSS u16 vga_backlog_screen[VGA_WIDTH * VGA_HEIGHT] = { 0 };
PRIVATE ATTR_DBGBSS unsigned int vga_backlog_scrollpos = 0;
#define vga_backlog_scrollmax  \
   (vga_terminal_backlog_full ? (VGA_BACKLOG_NUMSCREENS * VGA_HEIGHT) : \
   (unsigned int)((size_t)(vga_terminal_backlog_cur - vga_terminal_backlog) / VGA_WIDTH))



PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL vga_backlog_setscrollpos)(unsigned int pos) {
	size_t backlog_offset;
	if (!pos) {
		/* Scroll to the bottom. */
		memcpyw(vga_terminal_start,
		        vga_backlog_screen,
		        VGA_WIDTH * VGA_HEIGHT);
		vga_backlog_scrollpos = 0;
		return;
	}
	/* Start scrolling */
	if (!vga_backlog_scrollpos) {
		memcpyw(vga_backlog_screen,
		        vga_terminal_start,
		        VGA_WIDTH * VGA_HEIGHT);
	}
	/* Copy the relevant section on-screen. */
	backlog_offset = (size_t)pos * VGA_WIDTH;
	if (pos < VGA_HEIGHT) {
		u16 *backlog_src;
		/* Part of the active screen is still visible */
		memcpyw(vga_terminal_start + backlog_offset,
		        vga_backlog_screen,
		        (VGA_HEIGHT - pos) * VGA_WIDTH);
		backlog_src = vga_terminal_backlog_cur - backlog_offset;
		if (backlog_src >= vga_terminal_backlog) {
			memcpyw(vga_terminal_start,
			        backlog_src,
			        backlog_offset);
		} else {
			size_t num_leading, num_trailing;
			num_leading  = (size_t)(vga_terminal_backlog_cur - vga_terminal_backlog);
			num_trailing = (size_t)(backlog_offset - num_leading);
			memcpyw(vga_terminal_start, vga_terminal_backlog_end - num_trailing, num_trailing);
			memcpyw(vga_terminal_start + num_trailing, vga_terminal_backlog, num_leading);
		}
	} else {
		/* Only the backlog is visible. */
		u16 *visible_start, *visible_end;
		visible_start = vga_terminal_backlog_cur - backlog_offset;
		visible_end   = visible_start + (VGA_WIDTH * VGA_HEIGHT);
		if (visible_end < vga_terminal_backlog) {
			visible_start += VGA_BACKLOG_NUMSCREENS * VGA_WIDTH * VGA_HEIGHT;
			visible_end += VGA_BACKLOG_NUMSCREENS * VGA_WIDTH * VGA_HEIGHT;
		}
		assert(visible_end >= vga_terminal_backlog);
		if (visible_start >= vga_terminal_backlog) {
			memcpyw(vga_terminal_start, visible_start, VGA_WIDTH * VGA_HEIGHT);
		} else {
			size_t num_leading, num_trailing;
			num_leading  = (size_t)(visible_end - vga_terminal_backlog);
			num_trailing = (size_t)(vga_terminal_backlog - visible_start);
			assertf(num_trailing < COMPILER_LENOF(vga_terminal_backlog), "num_trailing = %Iu\n", num_trailing);
			assertf(num_leading < COMPILER_LENOF(vga_terminal_backlog), "num_leading = %Iu\n", num_leading);
			memcpyw(vga_terminal_start, vga_terminal_backlog_end - num_trailing, num_trailing);
			memcpyw(vga_terminal_start + num_trailing, vga_terminal_backlog, num_leading);
		}
	}
	vga_backlog_scrollpos = pos;
#if 1
	{
		/* Display the current scroll position in the bottom-right corner. */
		char buf[64];
		u16 *dest;
		unsigned int i, len;
		unsigned int maxpos = vga_backlog_scrollmax;
		len = (unsigned int)sprintf(buf, "%u/%u",
		                            maxpos - pos,
		                            maxpos);
		dest = vga_terminal_end - len;
		for (i = 0; i < len; ++i) {
			dest[i] = (u16)(u8)buf[i] | DBG_COLOR_ATTR(DBG_COLOR_LIGHT_GRAY,
			                                           DBG_COLOR_DARK_GRAY);
		}
	}
#endif
}



PUBLIC unsigned int
NOTHROW(FCALL dbg_getscroll)(void) {
	return vga_backlog_scrollpos;
}

PUBLIC unsigned int
NOTHROW(FCALL dbg_setscroll)(unsigned int pos) {
	unsigned int maxpos;
	if (!pos) {
set_pos_0:
		if (vga_backlog_scrollpos) {
			vga_backlog_setscrollpos(0);
			if (vga_terminal_showcur)
				vga_update_cursor_pos();
		}
		goto done;
	}
	maxpos = vga_backlog_scrollmax;
	if (pos > maxpos) {
		pos = maxpos;
		if (!pos)
			goto set_pos_0;
	}
	if (pos != vga_backlog_scrollpos) {
		if (!vga_backlog_scrollpos && vga_terminal_showcur)
			vga_disable_cursor();
		vga_backlog_setscrollpos(pos);
	}
done:
	return pos;
}


PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED bool
NOTHROW(FCALL dbg_getcur_visible)(void) {
	return vga_terminal_showcur;
}
PUBLIC ATTR_DBGTEXT bool
NOTHROW(FCALL dbg_setcur_visible)(bool visible) {
	bool result;
	result = vga_terminal_showcur;
	if (result != visible) {
		if (!vga_backlog_scrollpos && !vga_suppress_update) {
			if (visible)
				vga_update_cursor_pos();
			else {
				vga_disable_cursor();
			}
		}
		vga_terminal_showcur = visible;
	}
	return vga_terminal_showcur;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL vga_enable_offscreen_buffer)(void) {
	if (vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
	memcpyw(vga_offscreen_buffer, vga_real_terminal_start, VGA_WIDTH * VGA_HEIGHT);
	vga_terminal_cur     = vga_offscreen_buffer + (vga_terminal_cur - vga_terminal_start);
	vga_terminal_start   = vga_offscreen_buffer;
	vga_terminal_end     = vga_offscreen_buffer + VGA_WIDTH * VGA_HEIGHT;
	vga_terminal_2ndln   = vga_offscreen_buffer + VGA_WIDTH;
	vga_terminal_lastln  = vga_offscreen_buffer + VGA_WIDTH * (VGA_HEIGHT - 1);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL vga_disable_offscreen_buffer)(void) {
	if (vga_backlog_scrollpos)
		vga_backlog_setscrollpos(0);
	memcpyw(vga_real_terminal_start, vga_offscreen_buffer, VGA_WIDTH * VGA_HEIGHT);
	vga_terminal_cur     = vga_real_terminal_start + (vga_terminal_cur - vga_terminal_start);
	vga_terminal_start   = vga_real_terminal_start;
	vga_terminal_end     = vga_real_terminal_start + VGA_WIDTH * VGA_HEIGHT;
	vga_terminal_2ndln   = vga_real_terminal_start + VGA_WIDTH;
	vga_terminal_lastln  = vga_real_terminal_start + VGA_WIDTH * (VGA_HEIGHT - 1);
	if (vga_terminal_showcur)
		vga_update_cursor_pos();
}


/* Hints towards the screen driver to temporarily stop drawing to the screen,
 * but instead draw to a separate buffer, thus preventing flickering in the
 * case of whole screen redraw operations.
 * NOTE: Also affects updates made to the cursor position
 * @param: force: When true, force updates to stop. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_beginupdate)(void) {
	++vga_suppress_update;
	if (vga_suppress_update == 1)
		vga_enable_offscreen_buffer();
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_endupdate)(bool force) {
	if (vga_suppress_update == 0)
		return; /* Missing `dbg_beginupdate()' */
	if (force) {
		vga_suppress_update = 0;
	} else {
		--vga_suppress_update;
		if (vga_suppress_update != 0)
			return; /* Recursive `dbg_beginupdate()' */
	}
	vga_disable_offscreen_buffer();
}

PUBLIC ATTR_DBGTEXT WUNUSED ATTR_PURE u32
NOTHROW(FCALL dbg_getcur)(void) {
	unsigned int pos;
	pos = (unsigned int)(vga_terminal_cur -
	                     vga_terminal_start);
	return DBG_MAKECUR(pos % VGA_WIDTH,
	                   pos / VGA_WIDTH);
}

PUBLIC ATTR_DBGTEXT u32
NOTHROW(FCALL dbg_setcur)(int x, int y) {
	unsigned int pos;
	if (x < 0)
		x = 0;
	else if (x >= VGA_WIDTH) {
		x = VGA_WIDTH - 1;
	}
	if (y < 0)
		y = 0;
	else if (y >= VGA_WIDTH) {
		y = VGA_WIDTH - 1;
	}
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	pos = (unsigned int)x +
	      (unsigned int)y * VGA_WIDTH;
	vga_terminal_cur = vga_terminal_start + pos;
	if (vga_terminal_showcur && !vga_suppress_update)
		vga_update_cursor_pos();
	return DBG_MAKECUR(pos % VGA_WIDTH,
	                   pos / VGA_WIDTH);
}


LOCAL ATTR_DBGTEXT void
NOTHROW(FCALL scroll_down_if_cur_end)(void) {
	if (vga_terminal_cur >= vga_terminal_end) {
		/* Scroll down */
		if (!vga_suppress_update)
			VGA_TERMINAL_BACKLOG_ADDLINE(vga_terminal_start);
		memmovew(vga_terminal_start, vga_terminal_2ndln,
		         (VGA_HEIGHT - 1) * VGA_WIDTH);
		memsetw(vga_terminal_lastln + 1, VGA_EMPTY, VGA_WIDTH - 1);
		vga_terminal_cur = vga_terminal_lastln + dbg_indent;
	}
}


/* Conversion table: LATIN-1 --> CP437 */
PRIVATE u8 const cp437_from_latin1[256] = {
/*[[[deemon
local l = [0] * 256;
l[0x00] = 0;
l[0x20] = 32;
l[0x21] = 33;
l[0x22] = 34;
l[0x23] = 35;
l[0x24] = 36;
l[0x25] = 37;
l[0x26] = 38;
l[0x27] = 39;
l[0x28] = 40;
l[0x29] = 41;
l[0x2A] = 42;
l[0x2B] = 43;
l[0x2C] = 44;
l[0x2D] = 45;
l[0x2E] = 46;
l[0x2F] = 47;
l[0x30] = 48;
l[0x31] = 49;
l[0x32] = 50;
l[0x33] = 51;
l[0x34] = 52;
l[0x35] = 53;
l[0x36] = 54;
l[0x37] = 55;
l[0x38] = 56;
l[0x39] = 57;
l[0x3A] = 58;
l[0x3B] = 59;
l[0x3C] = 60;
l[0x3D] = 61;
l[0x3E] = 62;
l[0x3F] = 63;
l[0x40] = 64;
l[0x41] = 65;
l[0x42] = 66;
l[0x43] = 67;
l[0x44] = 68;
l[0x45] = 69;
l[0x46] = 70;
l[0x47] = 71;
l[0x48] = 72;
l[0x49] = 73;
l[0x4A] = 74;
l[0x4B] = 75;
l[0x4C] = 76;
l[0x4D] = 77;
l[0x4E] = 78;
l[0x4F] = 79;
l[0x50] = 80;
l[0x51] = 81;
l[0x52] = 82;
l[0x53] = 83;
l[0x54] = 84;
l[0x55] = 85;
l[0x56] = 86;
l[0x57] = 87;
l[0x58] = 88;
l[0x59] = 89;
l[0x5A] = 90;
l[0x5B] = 91;
l[0x5C] = 92;
l[0x5D] = 93;
l[0x5E] = 94;
l[0x5F] = 95;
l[0x60] = 96;
l[0x61] = 97;
l[0x62] = 98;
l[0x63] = 99;
l[0x64] = 100;
l[0x65] = 101;
l[0x66] = 102;
l[0x67] = 103;
l[0x68] = 104;
l[0x69] = 105;
l[0x6A] = 106;
l[0x6B] = 107;
l[0x6C] = 108;
l[0x6D] = 109;
l[0x6E] = 110;
l[0x6F] = 111;
l[0x70] = 112;
l[0x71] = 113;
l[0x72] = 114;
l[0x73] = 115;
l[0x74] = 116;
l[0x75] = 117;
l[0x76] = 118;
l[0x77] = 119;
l[0x78] = 120;
l[0x79] = 121;
l[0x7A] = 122;
l[0x7B] = 123;
l[0x7C] = 124;
l[0x7D] = 125;
l[0x7E] = 126;
l[0xA0] = 255;
l[0xA1] = 173;
l[0xA2] = 155;
l[0xA3] = 156;
l[0xA5] = 157;
l[0xA7] = 21;
l[0xAA] = 166;
l[0xAB] = 174;
l[0xAC] = 170;
l[0xB0] = 248;
l[0xB1] = 241;
l[0xB2] = 253;
l[0xB5] = 230;
l[0xB6] = 20;
l[0xB7] = 250;
l[0xBA] = 167;
l[0xBB] = 175;
l[0xBC] = 172;
l[0xBD] = 171;
l[0xBF] = 168;
l[0xC4] = 142;
l[0xC5] = 143;
l[0xC6] = 146;
l[0xC7] = 128;
l[0xC9] = 144;
l[0xD1] = 165;
l[0xD6] = 153;
l[0xDC] = 154;
l[0xDF] = 225;
l[0xE0] = 133;
l[0xE1] = 160;
l[0xE2] = 131;
l[0xE4] = 132;
l[0xE5] = 134;
l[0xE6] = 145;
l[0xE7] = 135;
l[0xE8] = 138;
l[0xE9] = 130;
l[0xEA] = 136;
l[0xEB] = 137;
l[0xEC] = 141;
l[0xED] = 161;
l[0xEE] = 140;
l[0xEF] = 139;
l[0xF1] = 164;
l[0xF2] = 149;
l[0xF3] = 162;
l[0xF4] = 147;
l[0xF6] = 148;
l[0xF7] = 246;
l[0xF9] = 151;
l[0xFA] = 163;
l[0xFB] = 150;
l[0xFC] = 129;
l[0xFF] = 152;
#include <util>
print "\t",;
for (local i,x: util.enumerate(l)) {
	if (i) {
		print ",",;
		if ((i % 16) == 0) {
			print;
			print "\t",;
		}
	}
	print "0x%.2I8x" % x,;
}
]]]*/
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
	0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
	0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
	0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
	0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
	0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0xff,0xad,0x9b,0x9c,0x00,0x9d,0x00,0x15,0x00,0x00,0xa6,0xae,0xaa,0x00,0x00,0x00,
	0xf8,0xf1,0xfd,0x00,0x00,0xe6,0x14,0xfa,0x00,0x00,0xa7,0xaf,0xac,0xab,0x00,0xa8,
	0x00,0x00,0x00,0x00,0x8e,0x8f,0x92,0x80,0x00,0x90,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0xa5,0x00,0x00,0x00,0x00,0x99,0x00,0x00,0x00,0x00,0x00,0x9a,0x00,0x00,0xe1,
	0x85,0xa0,0x83,0x00,0x84,0x86,0x91,0x87,0x8a,0x82,0x88,0x89,0x8d,0xa1,0x8c,0x8b,
	0x00,0xa4,0x95,0xa2,0x93,0x00,0x94,0xf6,0x00,0x97,0xa3,0x96,0x81,0x00,0x00,0x98
//[[[end]]]
};


/* Encode the given unicode character `ch' using cp437 (the codepage
 * used by VGA) If the character can't be encoded, return 0 instead.
 * s.a.: https://en.wikipedia.org/wiki/Code_page_437  */
LOCAL ATTR_CONST u8
NOTHROW(FCALL cp437_encode)(/*utf-32*/ u32 ch) {
	u8 result;
	if (ch <= 0xff) {
		result = cp437_from_latin1[ch];
		if (result)
			return result;
	} else {
		switch (ch) {
		case 0x0192: result = 159; break;
		case 0x0393: result = 226; break;
		case 0x0398: result = 233; break;
		case 0x03A3: result = 228; break;
		case 0x03A6: result = 232; break;
		case 0x03A9: result = 234; break;
		case 0x03B1: result = 224; break;
		case 0x03B4: result = 235; break;
		case 0x03B5: result = 238; break;
		case 0x03C0: result = 227; break;
		case 0x03C3: result = 229; break;
		case 0x03C4: result = 231; break;
		case 0x03C6: result = 237; break;
		case 0x2022: result = 7; break;
		case 0x203C: result = 19; break;
		case 0x207F: result = 252; break;
		case 0x20A7: result = 158; break;
		case 0x2190: result = 27; break;
		case 0x2191: result = 24; break;
		case 0x2192: result = 26; break;
		case 0x2193: result = 25; break;
		case 0x2194: result = 29; break;
		case 0x2195: result = 18; break;
		case 0x21A8: result = 23; break;
		case 0x2219: result = 249; break;
		case 0x221A: result = 251; break;
		case 0x221E: result = 236; break;
		case 0x221F: result = 28; break;
		case 0x2229: result = 239; break;
		case 0x2248: result = 247; break;
		case 0x2261: result = 240; break;
		case 0x2264: result = 243; break;
		case 0x2265: result = 242; break;
		case 0x2302: result = 127; break;
		case 0x2310: result = 169; break;
		case 0x2320: result = 244; break;
		case 0x2321: result = 245; break;
		case 0x2500: result = 196; break;
		case 0x2502: result = 179; break;
		case 0x250C: result = 218; break;
		case 0x2510: result = 191; break;
		case 0x2514: result = 192; break;
		case 0x2518: result = 217; break;
		case 0x251C: result = 195; break;
		case 0x2524: result = 180; break;
		case 0x252C: result = 194; break;
		case 0x2534: result = 193; break;
		case 0x253C: result = 197; break;
		case 0x2550: result = 205; break;
		case 0x2551: result = 186; break;
		case 0x2552: result = 213; break;
		case 0x2553: result = 214; break;
		case 0x2554: result = 201; break;
		case 0x2555: result = 184; break;
		case 0x2556: result = 183; break;
		case 0x2557: result = 187; break;
		case 0x2558: result = 212; break;
		case 0x2559: result = 211; break;
		case 0x255A: result = 200; break;
		case 0x255B: result = 190; break;
		case 0x255C: result = 189; break;
		case 0x255D: result = 188; break;
		case 0x255E: result = 198; break;
		case 0x255F: result = 199; break;
		case 0x2560: result = 204; break;
		case 0x2561: result = 181; break;
		case 0x2562: result = 182; break;
		case 0x2563: result = 185; break;
		case 0x2564: result = 209; break;
		case 0x2565: result = 210; break;
		case 0x2566: result = 203; break;
		case 0x2567: result = 207; break;
		case 0x2568: result = 208; break;
		case 0x2569: result = 202; break;
		case 0x256A: result = 216; break;
		case 0x256B: result = 215; break;
		case 0x256C: result = 206; break;
		case 0x2580: result = 223; break;
		case 0x2584: result = 220; break;
		case 0x2588: result = 219; break;
		case 0x258C: result = 221; break;
		case 0x2590: result = 222; break;
		case 0x2591: result = 176; break;
		case 0x2592: result = 177; break;
		case 0x2593: result = 178; break;
		case 0x25A0: result = 254; break;
		case 0x25AC: result = 22; break;
		case 0x25B2: result = 30; break;
		case 0x25BA: result = 16; break;
		case 0x25BC: result = 31; break;
		case 0x25C4: result = 17; break;
		case 0x25CB: result = 9; break;
		case 0x25D8: result = 8; break;
		case 0x25D9: result = 10; break;
		case 0x263A: result = 1; break;
		case 0x263B: result = 2; break;
		case 0x263C: result = 15; break;
		case 0x2640: result = 12; break;
		case 0x2642: result = 11; break;
		case 0x2660: result = 6; break;
		case 0x2663: result = 5; break;
		case 0x2665: result = 3; break;
		case 0x2666: result = 4; break;
		case 0x266A: result = 13; break;
		case 0x266B: result = 14; break;
		default: result = 0; break;
		}
	}
	return result;
}



PRIVATE ATTR_DBGBSS bool vga_last_chr_caused_linewrap = false;
LOCAL ATTR_DBGTEXT void
NOTHROW(FCALL dbg_putcp437)(/*cp-437*/ u8 ch) {
	/* VGA terminal output */
	scroll_down_if_cur_end();
	/* When indent-mode is active, wraps to the next line */
	if (dbg_indent != 0 && vga_last_chr_caused_linewrap &&
	    !(dbg_tty.at_ttymode & ANSITTY_MODE_NOLINEWRAP) && VGA_GETCUR_X() == 0)
		vga_terminal_cur += dbg_indent;
	*vga_terminal_cur = VGA_CHR(ch);
	if (dbg_tty.at_ttymode & ANSITTY_MODE_NOLINEWRAP) {
		if (VGA_GETCUR_X() != VGA_WIDTH - 1)
			++vga_terminal_cur;
		vga_last_chr_caused_linewrap = false;
	} else {
		++vga_terminal_cur;
		vga_last_chr_caused_linewrap = VGA_GETCUR_X() == 0;
	}
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_bell)(void) {
	/* TODO */
}

PRIVATE ATTR_DBGBSS char32_t dbg_last_character = 0;
PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC vga_tty_putc)(struct ansitty *__restrict UNUSED(self),
                                    char32_t ch) {
	u8 cp_ch;
#if 1
	{
		INTDEF port_t x86_syslog_port;
		if (x86_syslog_port) {
			char buf[UNICODE_UTF8_CURLEN];
			size_t buflen = (size_t)(unicode_writeutf8(buf, ch) - buf);
			outsb(x86_syslog_port, buf, buflen);
		}
	}
#endif
	/* Scroll to bottom before printing a character. */
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	cp_ch = cp437_encode(ch);
	if (cp_ch) {
do_put_cp_ch:
		dbg_putcp437(cp_ch);
	} else {
		switch (ch) {

		case 7:
			dbg_bell();
			break;

		case '\t': {
			unsigned int cur_x;
			unsigned int num_space;
			unsigned int max_space;
			scroll_down_if_cur_end();
			cur_x     = VGA_GETCUR_X();
			num_space = dbg_tabsize - (cur_x % dbg_tabsize);
			max_space = VGA_WIDTH - cur_x;
			if (num_space > max_space)
				num_space = max_space;
			/* Output space characters. */
			memsetw(vga_terminal_cur, VGA_EMPTY, num_space);
			vga_terminal_cur += num_space;
		}	break;

		case '\b':
			if (vga_terminal_cur > vga_terminal_start) {
				--vga_terminal_cur;
				vga_last_chr_caused_linewrap = false;
			}
			break;

		case '\r': {
			unsigned int cury;
			/* Return to the start of the current line. */
			if (dbg_tty.at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE)
				memsetw(vga_terminal_cur, VGA_EMPTY, VGA_WIDTH - VGA_GETCUR_X());
			cury = VGA_GETCUR_Y();
			if (VGA_GETCUR_X() <= dbg_indent &&
			    cp437_encode(dbg_last_character) != 0 && cury)
				--cury;
			VGA_SETCUR(dbg_indent, cury);
		}	break;

		case '\n':
			if (VGA_GETCUR_X() <= dbg_indent &&
			    cp437_encode(dbg_last_character) != 0) {
				/* Special case: The previous line was filled entirely, and the cursor had to be wrapped
				 *               to the next line, however the first character then printed was also a
				 *               linefeed. - In this case, don't wrap the line, as the linefeed requested
				 *               by the caller already happened implicitly, thus not creating an entirely
				 *               empty line and wasting what little screen space we only have. */
			} else {
				/* Clear the remainder of the old line */
				if (dbg_tty.at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE)
					memsetw(vga_terminal_cur, VGA_EMPTY, VGA_WIDTH - VGA_GETCUR_X());
				if (vga_terminal_cur >= vga_terminal_lastln) {
					/* Scroll down */
					if (!vga_suppress_update)
						VGA_TERMINAL_BACKLOG_ADDLINE(vga_terminal_start);
					memmovew(vga_terminal_start, vga_terminal_2ndln,
					         (VGA_HEIGHT - 1) * VGA_WIDTH);
					memsetw(vga_terminal_lastln, VGA_EMPTY, VGA_WIDTH);
					vga_terminal_cur = vga_terminal_lastln + dbg_indent;
				} else {
					VGA_SETCUR(dbg_indent, VGA_GETCUR_Y() + 1);
				}
				vga_last_chr_caused_linewrap = false;
			}
			break;

		default:
			cp_ch = '?';
			goto do_put_cp_ch;
		}
	}
	if (vga_terminal_showcur && !vga_suppress_update)
		vga_update_cursor_pos();
	dbg_last_character = ch;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC vga_tty_setcursor)(struct ansitty *__restrict UNUSED(self),
                                         ansitty_coord_t x,
                                         ansitty_coord_t y,
                                         bool update_hw_cursor) {
	unsigned int newpos;
	if (x < 0)
		x = 0;
	else if (x >= VGA_WIDTH) {
		x = VGA_WIDTH - 1;
	}
	if (y < 0)
		y = 0;
	else if (y >= VGA_WIDTH) {
		y = VGA_WIDTH - 1;
	}
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	newpos = (unsigned int)x +
	         (unsigned int)y * VGA_WIDTH;
	vga_terminal_cur = vga_terminal_start + newpos;
	if (update_hw_cursor && vga_terminal_showcur && !vga_suppress_update)
		vga_update_cursor_pos();
	dbg_last_character = 0;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC vga_tty_getcursor)(struct ansitty *__restrict UNUSED(self),
                                         ansitty_coord_t ppos[2]) {
	unsigned int pos;
	pos = (unsigned int)(vga_terminal_cur -
	                     vga_terminal_start);
	ppos[0] = pos % VGA_WIDTH;
	ppos[1] = pos / VGA_WIDTH;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC vga_tty_getsize)(struct ansitty *__restrict UNUSED(self),
                                       ansitty_coord_t psize[2]) {
	psize[0] = VGA_WIDTH;
	psize[1] = VGA_HEIGHT;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC vga_tty_copycell)(struct ansitty *__restrict UNUSED(self),
                                        ansitty_offset_t dst_offset, ansitty_coord_t count) {
	u16 *ptr, *copyend;
	ptr = vga_terminal_cur + dst_offset;
	if (ptr < vga_terminal_start) {
		size_t underflow;
		underflow = vga_terminal_start - ptr;
		if (underflow >= count)
			return;
		ptr = vga_terminal_start;
		count -= underflow;
	}
	copyend = ptr + count;
	if (copyend < ptr) {
		count = (size_t)(vga_terminal_end - ptr);
	} else {
		if (copyend > vga_terminal_end)
			count = copyend - ptr;
	}
	copyend = vga_terminal_cur + count;
	if (copyend > vga_terminal_end)
		count = (size_t)(vga_terminal_end - vga_terminal_cur);
	memmovew(ptr, vga_terminal_cur, count);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC vga_tty_fillcell)(struct ansitty *__restrict UNUSED(self),
                                        char32_t ch, ansitty_coord_t count) {
	u16 cell;
	ansitty_coord_t used_count, max_count;
	char cpch = cp437_encode((u32)ch);
	if unlikely(!cpch)
		cpch = '?';
	cell = VGA_CHR(cpch);
	max_count = (size_t)(vga_terminal_end - vga_terminal_cur);
	used_count = count;
	if (used_count > max_count)
		used_count = max_count;
	memsetw(vga_terminal_cur, cell, used_count);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC vga_tty_setcolor)(struct ansitty *__restrict UNUSED(self),
                                        uint8_t color) {
	dbg_attr &= 0x00ff;
	dbg_attr |= color << 8;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC vga_tty_output)(struct ansitty *__restrict UNUSED(self),
                                      void const *data, size_t datalen) {
	while (datalen) {
		byte_t b;
		--datalen;
		b = ((byte_t *)data)[datalen];
		dbg_ungetc((char)b);
	}
}





PRIVATE ATTR_DBGRODATA struct ansitty_operators const vga_tty_operators = {
	.ato_putc         = &vga_tty_putc,
	.ato_setcursor    = &vga_tty_setcursor,
	.ato_getcursor    = &vga_tty_getcursor,
	.ato_getsize      = &vga_tty_getsize,
	.ato_copycell     = &vga_tty_copycell,
	.ato_fillcell     = &vga_tty_fillcell,
	.ato_scroll       = NULL,
	.ato_cls          = NULL,
	.ato_el           = NULL,
	.ato_setcolor     = &vga_tty_setcolor,
	.ato_setattrib    = NULL,
	.ato_setttymode   = NULL,
	.ato_scrollregion = NULL,
	.ato_settitle     = NULL,
	.ato_output       = &vga_tty_output,
	.ato_setled       = NULL,
	.ato_termios      = NULL
};




LOCAL NOBLOCK ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL dbg_pprinter_putcp437)(dbg_pprinter_arg_t *__restrict printer, /*cp-437*/ u8 ch) {
	/* VGA terminal output */
	if (printer->p_printx >= 0 && printer->p_printx < VGA_WIDTH &&
	    printer->p_printy >= 0 && printer->p_printy < VGA_HEIGHT)
		vga_terminal_start[printer->p_printx + printer->p_printy * VGA_WIDTH] = VGA_CHR(ch);
	++printer->p_printx;
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL vga_pprinter_do_putuni)(dbg_pprinter_arg_t *__restrict printer, /*utf-32*/ char32_t ch) {
	u8 cp_ch;
	/* Scroll to bottom before printing a character. */
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	cp_ch = cp437_encode(ch);
	if (cp_ch) {
do_put_cp_ch:
		dbg_pprinter_putcp437(printer, cp_ch);
	} else {
		switch (ch) {

		case 7:
			dbg_bell();
			break;

		case '\t': {
			unsigned int cur_x;
			unsigned int num_space;
			unsigned int max_space;
			cur_x     = (unsigned int)printer->p_printx;
			num_space = dbg_tabsize - (cur_x % dbg_tabsize);
			max_space = VGA_WIDTH - cur_x;
			if (num_space > max_space)
				num_space = max_space;
			/* Output space characters. */
			if (printer->p_printx >= 0 && printer->p_printx < VGA_WIDTH &&
			    printer->p_printy >= 0 && printer->p_printy < VGA_HEIGHT) {
				memsetw(&vga_terminal_start[printer->p_printx + printer->p_printy * VGA_WIDTH],
				        VGA_EMPTY, MIN(num_space, VGA_WIDTH - (unsigned int)printer->p_printx));
			}
			printer->p_printx += num_space;
		}	break;

		case '\b':
			--printer->p_printx;
			break;

		case '\r':
		case '\n':
			/* Return to the start of the current line. */
			if (dbg_tty.at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE) {
				if (printer->p_printx >= 0 && printer->p_printx < VGA_WIDTH &&
				    printer->p_printy >= 0 && printer->p_printy < VGA_HEIGHT)
					memsetw(&vga_terminal_start[printer->p_printx + printer->p_printy * VGA_WIDTH],
					        VGA_EMPTY, VGA_WIDTH - (unsigned int)printer->p_printx);
			}
			printer->p_printx = dbg_indent;
			if (ch == '\n')
				++printer->p_printy;
			break;

		default:
			cp_ch = 4; /* U+2666 */
			goto do_put_cp_ch;
		}
	}
}

PRIVATE NOBLOCK ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL dbg_pprinter_putuni)(dbg_pprinter_arg_t *__restrict printer, /*utf-32*/ char32_t ch) {
	if (dbg_tty._at_state != 0 || ch == (unsigned char)'\033') {
		ansitty_putuni(&dbg_tty, ch);
	} else {
		/* Output a regular, old character. */
		vga_pprinter_do_putuni(printer, ch);
	}
}

LOCAL ATTR_DBGTEXT NONNULL((1)) char32_t
NOTHROW(FCALL dbg_pprinter_pending_ch32)(dbg_pprinter_arg_t *__restrict printer) {
	char32_t result;
	u8 seqlen = unicode_utf8seqlen[printer->p_utf8[0]];
	result = (char32_t)printer->p_utf8[0];
	switch (seqlen) {

	case 0:
	case 1:
		break;

	case 2:
		result  = (result & 0x1f) << 6;
		result |= (printer->p_utf8[1] & 0x3f);
		break;

	case 3:
		result  = (result & 0x0f) << 12;
		result |= (printer->p_utf8[1] & 0x3f) << 6;
		result |= (printer->p_utf8[2] & 0x3f);
		break;

	case 4:
		result  = (result & 0x07) << 18;
		result |= (printer->p_utf8[1] & 0x3f) << 12;
		result |= (printer->p_utf8[2] & 0x3f) << 6;
		result |= (printer->p_utf8[3] & 0x3f);
		break;

	case 5:
		result  = (result & 0x03) << 24;
		result |= (printer->p_utf8[1] & 0x3f) << 18;
		result |= (printer->p_utf8[2] & 0x3f) << 12;
		result |= (printer->p_utf8[3] & 0x3f) << 6;
		result |= (printer->p_utf8[4] & 0x3f);
		break;

	case 6:
		result  = (result & 0x01) << 30;
		result |= (printer->p_utf8[1] & 0x3f) << 24;
		result |= (printer->p_utf8[2] & 0x3f) << 18;
		result |= (printer->p_utf8[3] & 0x3f) << 12;
		result |= (printer->p_utf8[4] & 0x3f) << 6;
		result |= (printer->p_utf8[5] & 0x3f);
		break;

	case 7:
		result  = (printer->p_utf8[1] & 0x03/*0x3f*/) << 30;
		result |= (printer->p_utf8[2] & 0x3f) << 24;
		result |= (printer->p_utf8[3] & 0x3f) << 18;
		result |= (printer->p_utf8[4] & 0x3f) << 12;
		result |= (printer->p_utf8[5] & 0x3f) << 6;
		result |= (printer->p_utf8[6] & 0x3f);
		break;

	case 8:
		/*result = (result & 0x3f) << 36;*/
		result  = (printer->p_utf8[1] & 0x03/*0x3f*/) << 30;
		result |= (printer->p_utf8[2] & 0x3f) << 24;
		result |= (printer->p_utf8[3] & 0x3f) << 18;
		result |= (printer->p_utf8[4] & 0x3f) << 12;
		result |= (printer->p_utf8[5] & 0x3f) << 6;
		result |= (printer->p_utf8[6] & 0x3f);
		break;

	default:
		__builtin_unreachable();
	}
	return result;
}

PRIVATE ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL dbg_pprinter_putc)(dbg_pprinter_arg_t *__restrict printer, /*utf-8*/ char ch) {
	if (printer->p_utf8[0]) {
		/* Continue a utf-8 sequence. */
		u8 reqlen = unicode_utf8seqlen[printer->p_utf8[0]];
		if unlikely(((u8)ch & 0xc0) != 0x80) {
			/* Incomplete utf-8 sequence... */
			dbg_pprinter_putuni(printer, dbg_pprinter_pending_ch32(printer));
			printer->p_utf8[0] = 0;
			goto normal_ch;
		} else {
			unsigned int i;
			for (i = 0;; ++i) {
				if unlikely(i >= COMPILER_LENOF(printer->p_utf8)) {
					dbg_pprinter_putuni(printer, dbg_pprinter_pending_ch32(printer));
					printer->p_utf8[0] = 0;
					goto normal_ch;
				}
				if (!printer->p_utf8[i])
					break;
			}
			printer->p_utf8[i++] = (u8)ch;
			if (i >= reqlen) {
				dbg_pprinter_putuni(printer, dbg_pprinter_pending_ch32(printer));
				printer->p_utf8[0] = 0;
			}
		}
	} else {
normal_ch:
		if ((u8)ch < 0xc0) {
			/* Unicode pass-through character. */
			dbg_pprinter_putuni(printer, (u32)(u8)ch);
		} else {
			/* Start a new utf-8 sequence. */
			printer->p_utf8[0] = (u8)ch;
			memset(printer->p_utf8 + 1, 0,
			       sizeof(printer->p_utf8) -
			       sizeof(*printer->p_utf8));
		}
	}
}

/* Print text to the given coords. */
PUBLIC ATTR_DBGTEXT NONNULL((2)) ssize_t KCALL
dbg_pprinter(/*dbg_pprinter_arg_t **/ void *__restrict arg,
             /*utf-8*/ char const *__restrict data,
             size_t datalen) {
	size_t i;
	dbg_pprinter_arg_t *printer;
	printer = (dbg_pprinter_arg_t *)arg;
	for (i = 0; i < datalen; ++i)
		dbg_pprinter_putc(printer, data[i]);
	return (ssize_t)datalen;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_pputuni)(int x, int y, /*utf-32*/ char32_t ch) {
	dbg_pprinter_arg_t printer = DBG_PPRINTER_ARG_INIT(x, y);
	dbg_pprinter_putuni(&printer, ch);
}

PUBLIC ATTR_DBGTEXT size_t FCALL
dbg_pprint(int x, int y, /*utf-8*/ char const *__restrict str) {
	dbg_pprinter_arg_t printer = DBG_PPRINTER_ARG_INIT(x, y);
	return (size_t)dbg_pprinter(&printer, str, strlen(str));
}

PUBLIC ATTR_DBGTEXT size_t FCALL
dbg_vpprintf(int x, int y, /*utf-8*/ char const *__restrict format, va_list args) {
	dbg_pprinter_arg_t printer = DBG_PPRINTER_ARG_INIT(x, y);
	return (size_t)format_vprintf(&dbg_pprinter, &printer, format, args);
}

PUBLIC ATTR_DBGTEXT size_t VCALL
dbg_pprintf(int x, int y, /*utf-8*/ char const *__restrict format, ...) {
	size_t result;
	va_list args;
	va_start(args, format);
	result = dbg_vpprintf(x, y, format, args);
	va_end(args);
	return result;
}








PRIVATE ATTR_DBGBSS pagedir_pushval_t vga_oldmapping[VGA_VRAM_SIZE / PAGESIZE];
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
PRIVATE ATTR_DBGBSS bool vga_oldmapping_did_prepare = false;
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */


PRIVATE ATTR_DBGTEXT void NOTHROW(FCALL vga_map)(void) {
	unsigned int i;
	if (vga_real_terminal_start != NULL)
		return;
	vga_vram_offset         = VGA_VRAM_TEXT - VGA_VRAM_BASE;
	vga_real_terminal_start = (u16 *)(KERNEL_CORE_BASE + VGA_VRAM_TEXT);
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (pagedir_ismapped(vga_real_terminal_start) &&
	    pagedir_translate(vga_real_terminal_start) == (vm_phys_t)VGA_VRAM_TEXT) {
		vga_oldmapping_did_prepare = false;
		return;
	}
	/* We might get here so early during booting that the page frame allocator
	 * has yet to be initialized, at which point prepare would fail. - However,
	 * at that point we'd still have access to the physical identity map, so we
	 * should instead also support its use instead of only hacking around to
	 * place a temporary mapping of the VGA display just before the kernel. */
	vga_oldmapping_did_prepare = pagedir_prepare_map((void *)((uintptr_t)vga_real_terminal_start & ~PAGEMASK),
	                                                 VGA_VRAM_SIZE);
	if (!vga_oldmapping_did_prepare) {
		printk(DBGSTR(KERN_CRIT "[dbg] Failed to find suitable location to map "
		                        "VGA video memory. - This shouldn't happen\n"));
	} else
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	{
		for (i = 0; i < COMPILER_LENOF(vga_oldmapping); ++i) {
			pagedir_pushval_t oldword;
			byte_t *addr = (byte_t *)((uintptr_t)vga_real_terminal_start & ~PAGEMASK) + i * PAGESIZE;
			oldword = pagedir_push_mapone(addr,
			                              (vm_phys_t)VGA_VRAM_TEXT + i * PAGESIZE,
			                              PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
			vga_oldmapping[i] = oldword;
		}
	}
}

PRIVATE ATTR_DBGTEXT void NOTHROW(FCALL vga_unmap)(void) {
	unsigned int i;
	if (vga_real_terminal_start == NULL)
		return;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
	if (!vga_oldmapping_did_prepare)
		return;
	vga_oldmapping_did_prepare = false;
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
	for (i = 0; i < COMPILER_LENOF(vga_oldmapping); ++i) {
		byte_t *addr = (byte_t *)vga_real_terminal_start + i * PAGESIZE;
		pagedir_pop_mapone(addr, vga_oldmapping[i]);
	}
	vga_real_terminal_start = NULL;
}


PRIVATE NOBLOCK void
NOTHROW(FCALL VGA_SetMode)(struct vga_mode const *__restrict mode) {
	unsigned int i;
	u8 temp, qr1;
	qr1 = vga_rseq(VGA_SEQ_CLOCK_MODE);

	/* Turn off the screen. */
	vga_wseq(VGA_SEQ_RESET, 0x1);
	vga_wseq(VGA_SEQ_CLOCK_MODE, qr1 | VGA_SR01_FSCREEN_OFF);
	vga_wseq(VGA_SEQ_RESET, 0x3);

	/* Enable graphics mode. */
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x00);
	vga_r(VGA_IS1_RC), temp = vga_rattr(VGA_ATC_MODE);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_MODE, (temp & VGA_AT10_FRESERVED) | mode->vm_att_mode);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_OVERSCAN, mode->vm_att_overscan);
	vga_r(VGA_IS1_RC), temp = vga_rattr(VGA_ATC_PLANE_ENABLE);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_PLANE_ENABLE, (temp & VGA_AT12_FRESERVED) | mode->vm_att_plane_enable);
	vga_r(VGA_IS1_RC), temp = vga_rattr(VGA_ATC_PEL);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_PEL, (temp & VGA_AT13_FRESERVED) | mode->vm_att_pel);
	vga_r(VGA_IS1_RC), temp = vga_rattr(VGA_ATC_COLOR_PAGE);
	vga_r(VGA_IS1_RC), vga_wattr(VGA_ATC_COLOR_PAGE, (temp & VGA_AT14_FRESERVED) | mode->vm_att_color_page);
	for (i = 0; i < 16; ++i) {
		vga_r(VGA_IS1_RC);
		temp = vga_rattr(VGA_ATC_PALETTE0 + i);
		vga_r(VGA_IS1_RC);
		vga_wattr(VGA_ATC_PALETTE0 + i,
		          (temp & VGA_ATC_PALETTEn_FRESERVED) |
		          mode->vm_att_pal[i]);
	}
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x20);

	temp = vga_r(VGA_MIS_R);
	vga_w(VGA_MIS_W, (temp & VGA_MIS_FRESERVED) | mode->vm_mis);

	temp = vga_rseq(VGA_SEQ_PLANE_WRITE);
	vga_wseq(VGA_SEQ_PLANE_WRITE, (temp & VGA_SR02_FRESERVED) | mode->vm_seq_plane_write);
	temp = vga_rseq(VGA_SEQ_CHARACTER_MAP);
	vga_wseq(VGA_SEQ_CHARACTER_MAP, (temp & VGA_SR03_FRESERVED) | mode->vm_seq_character_map);
	temp = vga_rseq(VGA_SEQ_MEMORY_MODE);
	vga_wseq(VGA_SEQ_MEMORY_MODE, (temp & VGA_SR04_FRESERVED) | mode->vm_seq_memory_mode);

	temp = vga_rgfx(VGA_GFX_SR_VALUE), vga_wgfx(VGA_GFX_SR_VALUE, (temp & VGA_GR00_FRESERVED) | mode->vm_gfx_sr_value);
	temp = vga_rgfx(VGA_GFX_SR_ENABLE), vga_wgfx(VGA_GFX_SR_ENABLE, (temp & VGA_GR01_FRESERVED) | mode->vm_gfx_sr_enable);
	temp = vga_rgfx(VGA_GFX_COMPARE_VALUE), vga_wgfx(VGA_GFX_COMPARE_VALUE, (temp & VGA_GR02_FRESERVED) | mode->vm_gfx_compare_value);
	temp = vga_rgfx(VGA_GFX_DATA_ROTATE), vga_wgfx(VGA_GFX_DATA_ROTATE, (temp & VGA_GR03_FRESERVED) | mode->vm_gfx_data_rotate);
	temp = vga_rgfx(VGA_GFX_PLANE_READ), vga_wgfx(VGA_GFX_PLANE_READ, (temp & VGA_GR04_FRESERVED) | mode->vm_gfx_plane_read);
	temp = vga_rgfx(VGA_GFX_MODE), vga_wgfx(VGA_GFX_MODE, (temp & VGA_GR05_FRESERVED) | mode->vm_gfx_mode);
	temp = vga_rgfx(VGA_GFX_MISC), vga_wgfx(VGA_GFX_MISC, (temp & VGA_GR06_FRESERVED) | mode->vm_gfx_misc);
	temp = vga_rgfx(VGA_GFX_COMPARE_MASK), vga_wgfx(VGA_GFX_COMPARE_MASK, (temp & VGA_GR07_FRESERVED) | mode->vm_gfx_compare_mask);
	vga_wgfx(VGA_GFX_BIT_MASK, mode->vm_gfx_bit_mask);

	/* Apply new graphics settings. */
	vga_wcrt(VGA_CRTC_H_TOTAL, mode->vm_crt_h_total);
	vga_wcrt(VGA_CRTC_H_DISP, mode->vm_crt_h_disp);
	vga_wcrt(VGA_CRTC_H_BLANK_START, mode->vm_crt_h_blank_start);
	vga_wcrt(VGA_CRTC_H_BLANK_END, mode->vm_crt_h_blank_end);
	vga_wcrt(VGA_CRTC_H_SYNC_START, mode->vm_crt_h_sync_start);
	vga_wcrt(VGA_CRTC_H_SYNC_END, mode->vm_crt_h_sync_end);
	vga_wcrt(VGA_CRTC_V_TOTAL, mode->vm_crt_v_total);
	vga_wcrt(VGA_CRTC_OVERFLOW, mode->vm_crt_overflow);
	temp = vga_rcrt(VGA_CRTC_PRESET_ROW);
	vga_wcrt(VGA_CRTC_PRESET_ROW, (temp & VGA_CR8_FRESERVED) | mode->vm_crt_preset_row);
	vga_wcrt(VGA_CRTC_MAX_SCAN, mode->vm_crt_max_scan);
	vga_wcrt(VGA_CRTC_V_SYNC_START, mode->vm_crt_v_sync_start);
	temp = vga_rcrt(VGA_CRTC_V_SYNC_END);
	vga_wcrt(VGA_CRTC_V_SYNC_END, (temp & VGA_CR11_FRESERVED) | mode->vm_crt_v_sync_end);
	vga_wcrt(VGA_CRTC_V_DISP_END, mode->vm_crt_v_disp_end);
	vga_wcrt(VGA_CRTC_OFFSET, mode->vm_crt_offset);
	vga_wcrt(VGA_CRTC_UNDERLINE, mode->vm_crt_underline);
	vga_wcrt(VGA_CRTC_V_BLANK_START, mode->vm_crt_v_blank_start);
	temp = vga_rcrt(VGA_CRTC_V_BLANK_END);
	vga_wcrt(VGA_CRTC_V_BLANK_END, (temp & VGA_CR16_FRESERVED) | mode->vm_crt_v_blank_end);
	temp = vga_rcrt(VGA_CRTC_MODE);
	vga_wcrt(VGA_CRTC_MODE, (temp & VGA_CR17_FRESERVED) | mode->vm_crt_mode);
	vga_wcrt(VGA_CRTC_LINE_COMPARE, mode->vm_crt_line_compare);

	/* Turn the screen back on. */
	vga_wseq(VGA_SEQ_RESET, 0x1);
	vga_wseq(VGA_SEQ_CLOCK_MODE,
	         (qr1 & VGA_SR01_FRESERVED) |
	         (mode->vm_seq_clock_mode & ~VGA_SR01_FSCREEN_OFF));
	vga_wseq(VGA_SEQ_RESET, 0x3);
}


PRIVATE NOBLOCK void
NOTHROW(FCALL VGA_GetMode)(struct vga_mode *__restrict mode) {
	unsigned int i;
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x00);
	vga_r(VGA_IS1_RC), mode->vm_att_mode         = vga_rattr(VGA_ATC_MODE) & ~VGA_AT10_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_overscan     = vga_rattr(VGA_ATC_OVERSCAN);
	vga_r(VGA_IS1_RC), mode->vm_att_plane_enable = vga_rattr(VGA_ATC_PLANE_ENABLE) & ~VGA_AT12_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_pel          = vga_rattr(VGA_ATC_PEL) & ~VGA_AT13_FRESERVED;
	vga_r(VGA_IS1_RC), mode->vm_att_color_page   = vga_rattr(VGA_ATC_COLOR_PAGE) & ~VGA_AT14_FRESERVED;
	for (i = 0; i < 16; ++i) {
		vga_r(VGA_IS1_RC);
		mode->vm_att_pal[i] = vga_rattr(VGA_ATC_PALETTE0 + i) & ~VGA_ATC_PALETTEn_FRESERVED;
	}
	vga_r(VGA_IS1_RC), vga_w(VGA_ATT_W, 0x20);

	mode->vm_mis               = vga_r(VGA_MIS_R) & ~VGA_MIS_FRESERVED;
	mode->vm_gfx_sr_value      = vga_rgfx(VGA_GFX_SR_VALUE) & ~VGA_GR00_FRESERVED;
	mode->vm_gfx_sr_enable     = vga_rgfx(VGA_GFX_SR_ENABLE) & ~VGA_GR01_FRESERVED;
	mode->vm_gfx_compare_value = vga_rgfx(VGA_GFX_COMPARE_VALUE) & ~VGA_GR02_FRESERVED;
	mode->vm_gfx_data_rotate   = vga_rgfx(VGA_GFX_DATA_ROTATE) & ~VGA_GR03_FRESERVED;
	mode->vm_gfx_plane_read    = vga_rgfx(VGA_GFX_PLANE_READ) & ~VGA_GR04_FRESERVED;
	mode->vm_gfx_mode          = vga_rgfx(VGA_GFX_MODE) & ~VGA_GR05_FRESERVED;
	mode->vm_gfx_misc          = vga_rgfx(VGA_GFX_MISC) & ~VGA_GR06_FRESERVED;
	mode->vm_gfx_compare_mask  = vga_rgfx(VGA_GFX_COMPARE_MASK) & ~VGA_GR07_FRESERVED;
	mode->vm_gfx_bit_mask      = vga_rgfx(VGA_GFX_BIT_MASK);
	mode->vm_crt_h_total       = vga_rcrt(VGA_CRTC_H_TOTAL);
	mode->vm_crt_h_disp        = vga_rcrt(VGA_CRTC_H_DISP);
	mode->vm_crt_h_blank_start = vga_rcrt(VGA_CRTC_H_BLANK_START);
	mode->vm_crt_h_blank_end   = vga_rcrt(VGA_CRTC_H_BLANK_END);
	mode->vm_crt_h_sync_start  = vga_rcrt(VGA_CRTC_H_SYNC_START);
	mode->vm_crt_h_sync_end    = vga_rcrt(VGA_CRTC_H_SYNC_END);
	mode->vm_crt_v_total       = vga_rcrt(VGA_CRTC_V_TOTAL);
	mode->vm_crt_overflow      = vga_rcrt(VGA_CRTC_OVERFLOW);
	mode->vm_crt_preset_row    = vga_rcrt(VGA_CRTC_PRESET_ROW) & ~VGA_CR8_FRESERVED;
	mode->vm_crt_max_scan      = vga_rcrt(VGA_CRTC_MAX_SCAN);
	mode->vm_crt_v_sync_start  = vga_rcrt(VGA_CRTC_V_SYNC_START);
	mode->vm_crt_v_sync_end    = vga_rcrt(VGA_CRTC_V_SYNC_END) & ~VGA_CR11_FRESERVED;
	mode->vm_crt_v_disp_end    = vga_rcrt(VGA_CRTC_V_DISP_END);
	mode->vm_crt_offset        = vga_rcrt(VGA_CRTC_OFFSET);
	mode->vm_crt_underline     = vga_rcrt(VGA_CRTC_UNDERLINE);
	mode->vm_crt_v_blank_start = vga_rcrt(VGA_CRTC_V_BLANK_START);
	mode->vm_crt_v_blank_end   = vga_rcrt(VGA_CRTC_V_BLANK_END) & ~VGA_CR16_FRESERVED;
	mode->vm_crt_mode          = vga_rcrt(VGA_CRTC_MODE) & ~VGA_CR17_FRESERVED;
	mode->vm_crt_line_compare  = vga_rcrt(VGA_CRTC_LINE_COMPARE);
	mode->vm_seq_plane_write   = vga_rseq(VGA_SEQ_PLANE_WRITE) & ~VGA_SR02_FRESERVED;
	mode->vm_seq_character_map = vga_rseq(VGA_SEQ_CHARACTER_MAP) & ~VGA_SR03_FRESERVED;
	mode->vm_seq_memory_mode   = vga_rseq(VGA_SEQ_MEMORY_MODE) & ~VGA_SR04_FRESERVED;
	mode->vm_seq_clock_mode    = vga_rseq(VGA_SEQ_CLOCK_MODE) & ~VGA_SR01_FRESERVED;
}


PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL VGA_SetPalette)(void const *__restrict pal, size_t num_bytes) {
	unsigned int i;
	assert(num_bytes <= 768);
	vga_w(VGA_PEL_MSK, 0xff);
	vga_w(VGA_PEL_IW, 0x00);
	for (i = 0; i < num_bytes; ++i)
		vga_w(VGA_PEL_D, ((u8 *)pal)[i]);
	for (; i < 768; ++i)
		vga_w(VGA_PEL_D, 0);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL VGA_GetPalette)(void *__restrict pal, size_t num_bytes) {
	unsigned int i;
	assert(num_bytes <= 768);
	vga_w(VGA_PEL_MSK, 0xff);
	vga_w(VGA_PEL_IR, 0x00);
	for (i = 0; i < num_bytes; ++i)
		((u8 *)pal)[i] = vga_r(VGA_PEL_D);
	for (; i < 768; ++i)
		vga_r(VGA_PEL_D);
}

PRIVATE ATTR_DBGTEXT byte_t *
NOTHROW(FCALL vga_vram)(u32 vram_offset) {
	u32 offset;
	offset      = vram_offset & PAGEMASK;
	vram_offset = vram_offset & ~PAGEMASK;
	if (vga_vram_offset != vram_offset) {
		byte_t *addr;
#ifdef ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE
		if (!vga_oldmapping_did_prepare) {
			byte_t *result;
			result = (byte_t *)(KERNEL_CORE_BASE + VGA_VRAM_BASE + vram_offset);
			if (pagedir_ismapped(result) &&
			    pagedir_translate(result) == (vm_phys_t)(VGA_VRAM_BASE + vram_offset)) {
				vga_vram_offset = vram_offset;
				return result + offset;
			}
			printk(DBGSTR(KERN_CRIT "[dbg] Video memory not prepared, and not "
			                        "identity-mapped. This will probably go wrong...\n"));
		}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		addr = (byte_t *)((uintptr_t)vga_real_terminal_start & ~PAGEMASK);
		pagedir_map(addr, PAGESIZE,
		            (vm_phys_t)VGA_VRAM_BASE + vram_offset,
		            PAGEDIR_MAP_FREAD | PAGEDIR_MAP_FWRITE);
		pagedir_syncone(addr);
		vga_vram_offset = vram_offset;
	}
	return (byte_t *)vga_real_terminal_start + offset;
}


PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL VGA_SetFont)(struct vga_font const *__restrict font) {
	unsigned int i;
	u32 dst = 0;
	u8 old_seq_plane_write = vga_rseq(VGA_SEQ_PLANE_WRITE);
	u8 old_seq_memory_mode = vga_rseq(VGA_SEQ_MEMORY_MODE);
	u8 old_gfx_plane_read  = vga_rgfx(VGA_GFX_PLANE_READ);
	u8 old_gfx_mode        = vga_rgfx(VGA_GFX_MODE);
	u8 old_gfx_sr_enable   = vga_rgfx(VGA_GFX_SR_ENABLE);
	u8 old_gfx_sr_value    = vga_rgfx(VGA_GFX_SR_VALUE);
	u8 old_gfx_bit_mask    = vga_rgfx(VGA_GFX_BIT_MASK);
	u8 old_gfx_data_rotate = vga_rgfx(VGA_GFX_DATA_ROTATE);
	u8 old_gfx_misc        = vga_rgfx(VGA_GFX_MISC);
	vga_wseq(VGA_SEQ_PLANE_WRITE, (old_seq_plane_write & VGA_SR02_FRESERVED) | VGA_SR02_FPLANE(2));
	vga_wseq(VGA_SEQ_MEMORY_MODE, (old_seq_memory_mode & VGA_SR04_FRESERVED) |
	                              (VGA_SR04_FEXT_MEM | VGA_SR04_FSEQ_MODE));
	vga_wgfx(VGA_GFX_PLANE_READ, (old_gfx_plane_read & VGA_GR04_FRESERVED) | 0x02);
	vga_wgfx(VGA_GFX_MODE, (old_gfx_mode & VGA_GR05_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_SR_ENABLE, (old_gfx_sr_enable & VGA_GR01_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_SR_VALUE, (old_gfx_sr_value & VGA_GR00_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_BIT_MASK, 0xff);
	vga_wgfx(VGA_GFX_DATA_ROTATE, (old_gfx_data_rotate & VGA_GR03_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_MISC, (old_gfx_misc & VGA_GR06_FRESERVED) |
	                       (VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K));
	for (i = 0; i < 256; ++i) {
		memcpy(vga_vram(dst), &font->vf_blob[i], 16);
		dst += 32;
	}
	vga_wseq(VGA_SEQ_PLANE_WRITE, old_seq_plane_write);
	vga_wseq(VGA_SEQ_MEMORY_MODE, old_seq_memory_mode);
	vga_wgfx(VGA_GFX_PLANE_READ, old_gfx_plane_read);
	vga_wgfx(VGA_GFX_MODE, old_gfx_mode);
	vga_wgfx(VGA_GFX_SR_ENABLE, old_gfx_sr_enable);
	vga_wgfx(VGA_GFX_SR_VALUE, old_gfx_sr_value);
	vga_wgfx(VGA_GFX_BIT_MASK, old_gfx_bit_mask);
	vga_wgfx(VGA_GFX_DATA_ROTATE, old_gfx_data_rotate);
	vga_wgfx(VGA_GFX_MISC, old_gfx_misc);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL VGA_GetFont)(struct vga_font *__restrict font) {
	unsigned int i;
	u32 src = 0;
	u8 old_seq_plane_write = vga_rseq(VGA_SEQ_PLANE_WRITE);
	u8 old_seq_memory_mode = vga_rseq(VGA_SEQ_MEMORY_MODE);
	u8 old_gfx_plane_read  = vga_rgfx(VGA_GFX_PLANE_READ);
	u8 old_gfx_mode        = vga_rgfx(VGA_GFX_MODE);
	u8 old_gfx_misc        = vga_rgfx(VGA_GFX_MISC);
	vga_wseq(VGA_SEQ_PLANE_WRITE, (old_seq_plane_write & VGA_SR02_FRESERVED) | VGA_SR02_FPLANE(2));
	vga_wseq(VGA_SEQ_MEMORY_MODE, (old_seq_memory_mode & VGA_SR04_FRESERVED) |
	                              (VGA_SR04_FEXT_MEM | VGA_SR04_FSEQ_MODE));
	vga_wgfx(VGA_GFX_PLANE_READ, (old_gfx_plane_read & VGA_GR04_FRESERVED) | 0x02);
	vga_wgfx(VGA_GFX_MODE, (old_gfx_mode & VGA_GR05_FRESERVED) | 0x00);
	vga_wgfx(VGA_GFX_MISC, (old_gfx_misc & VGA_GR06_FRESERVED) |
	                       (VGA_GR06_FGRAPHICS_MODE | VGA_GR06_FMM_64K));
	for (i = 0; i < 256; ++i) {
		memcpy(&font->vf_blob[i], vga_vram(src), 16);
		src += 32;
	}
	vga_wseq(VGA_SEQ_PLANE_WRITE, old_seq_plane_write);
	vga_wseq(VGA_SEQ_MEMORY_MODE, old_seq_memory_mode);
	vga_wgfx(VGA_GFX_PLANE_READ, old_gfx_plane_read);
	vga_wgfx(VGA_GFX_MODE, old_gfx_mode);
	vga_wgfx(VGA_GFX_MISC, old_gfx_misc);
}


struct vga_cursor_regs {
	u8 crtc_cursor_start;
	u8 crtc_cursor_hi;
	u8 crtc_cursor_lo;
};

PRIVATE NOBLOCK ATTR_FREETEXT void
NOTHROW(FCALL VGA_GetCursor)(struct vga_cursor_regs *__restrict self) {
	self->crtc_cursor_start = vga_rcrt(VGA_CRTC_CURSOR_START);
	self->crtc_cursor_hi    = vga_rcrt(VGA_CRTC_CURSOR_HI);
	self->crtc_cursor_lo    = vga_rcrt(VGA_CRTC_CURSOR_LO);
}

PRIVATE NOBLOCK ATTR_FREETEXT void
NOTHROW(FCALL VGA_SetCursor)(struct vga_cursor_regs const *__restrict self) {
	vga_wcrt(VGA_CRTC_CURSOR_START, self->crtc_cursor_start);
	vga_wcrt(VGA_CRTC_CURSOR_HI, self->crtc_cursor_hi);
	vga_wcrt(VGA_CRTC_CURSOR_LO, self->crtc_cursor_lo);
}


PRIVATE ATTR_DBGRODATA struct vga_palette16 const vga_biospal = VGA_PALETTE_CGA_INIT;
PRIVATE ATTR_DBGRODATA struct vga_mode const vga_textmode = VGA_BIOTEXT80x25_MODE_INIT(VGA_PALINDX_CGA_ANSI_INIT);
PRIVATE ATTR_DBGBSS struct vga_font vga_textfont = {};
PRIVATE ATTR_DBGBSS struct vga_mode vga_oldmode = {};
PRIVATE ATTR_DBGBSS struct vga_cursor_regs vga_oldcursor = {};
PRIVATE ATTR_DBGBSS struct vga_font vga_oldfont = {};
PRIVATE ATTR_DBGBSS struct vga_palette256 vga_oldpal = {};
PRIVATE ATTR_DBGBSS u16 vga_oldtext[VGA_WIDTH * VGA_HEIGHT] = {};

PRIVATE ATTR_DBGBSS bool vga_did_initialized_textfont = false;
PRIVATE ATTR_DBGBSS bool vga_showscreen_enabled = false;
PRIVATE ATTR_DBGBSS struct vga_cursor_regs vga_showscreen_oldcursor = {};

INTERN ATTR_FREETEXT void
NOTHROW(KCALL x86_initialize_debugger_textfont)(void) {
	vga_map();
	VGA_GetFont(&vga_textfont);
	vga_unmap();
	vga_did_initialized_textfont = true;
}


/* TTY show-screen support (display the contents of the monitor before the debugger was enabled)
 * WARNING: `dbg_beginshowscreen()' also implies the behavior of `dbg_endupdate(true)'
 * NOTE: This functionality of these functions is also available through the `screen' command */
PUBLIC void NOTHROW(FCALL dbg_beginshowscreen)(void) {
	dbg_endupdate(true);
	if (!vga_showscreen_enabled) {
		if (vga_backlog_scrollpos)
			vga_backlog_setscrollpos(0);
		VGA_GetCursor(&vga_showscreen_oldcursor);
		vga_vram(VGA_VRAM_TEXT - VGA_VRAM_BASE);
		memcpyw(vga_backlog_screen, vga_real_terminal_start, VGA_WIDTH * VGA_HEIGHT);
		memcpyw(vga_real_terminal_start, vga_oldtext, VGA_WIDTH * VGA_HEIGHT);
		if (vga_did_initialized_textfont)
			VGA_SetFont(&vga_oldfont);
		VGA_SetPalette(&vga_oldpal, sizeof(vga_oldpal));
		VGA_SetMode(&vga_oldmode);
		VGA_SetCursor(&vga_oldcursor);
		vga_showscreen_enabled = true;
	}
}

PUBLIC void NOTHROW(FCALL dbg_endshowscreen)(void) {
	if (vga_showscreen_enabled) {
		VGA_SetMode(&vga_textmode);
		VGA_SetPalette(&vga_biospal, sizeof(vga_biospal));
		if (vga_did_initialized_textfont)
			VGA_SetFont(&vga_textfont);
		vga_vram(VGA_VRAM_TEXT - VGA_VRAM_BASE);
		memcpyw(vga_real_terminal_start, vga_backlog_screen, VGA_WIDTH * VGA_HEIGHT);
		vga_showscreen_enabled = false;
		VGA_SetCursor(&vga_showscreen_oldcursor);
	}
}


INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_initialize_tty)(void) {
	/* Map a portion of VRAM into memory. */
	vga_map();
	/* Save the old VGA mode. */
	VGA_GetCursor(&vga_oldcursor);
	VGA_GetMode(&vga_oldmode);
	/* Save the old VGA palette. */
	VGA_GetPalette(&vga_oldpal, sizeof(vga_oldpal));
	/* Save the old VGA font (or whatever is stored where the font goes). */
	if (vga_did_initialized_textfont)
		VGA_GetFont(&vga_oldfont);
	/* Set 80x25 text mode. */
	VGA_SetMode(&vga_textmode);
	/* Set the expected color palette. */
	VGA_SetPalette(&vga_biospal, sizeof(vga_biospal));
	/* Save the old text display contents. */
	vga_vram(VGA_VRAM_TEXT - VGA_VRAM_BASE);
	memcpyw(vga_oldtext, vga_real_terminal_start, VGA_WIDTH * VGA_HEIGHT);
	/* Set the font originally defined by the BIOS. */
	if (vga_did_initialized_textfont)
		VGA_SetFont(&vga_textfont);
}

INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_finalize_tty)(void) {
	/* Make sure we're not in show-screen mode. */
	dbg_endshowscreen();
	/* Restore font memory. */
	if (vga_did_initialized_textfont)
		VGA_SetFont(&vga_oldfont);
	/* Restore the old text display contents. */
	vga_vram(VGA_VRAM_TEXT - VGA_VRAM_BASE);
	memcpyw(vga_real_terminal_start, vga_oldtext, VGA_WIDTH * VGA_HEIGHT);
	/* Restore the old color palette */
	VGA_SetPalette(&vga_oldpal, sizeof(vga_oldpal));
	/* Restore the old video mode */
	VGA_SetMode(&vga_oldmode);
	VGA_SetCursor(&vga_oldcursor);
	/* Unmap video memory. */
	vga_unmap();
}

INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_reset_tty)(void) {
	/* Make sure we're not in show-screen mode from before. */
	dbg_endshowscreen();
	vga_vram_offset = 0;
	vga_vram(VGA_VRAM_TEXT - VGA_VRAM_BASE);
	ansitty_init(&dbg_tty, &vga_tty_operators);
	vga_showscreen_enabled       = false;
	vga_terminal_backlog_cur     = vga_terminal_backlog;
	dbg_attr                     = DBG_COLOR_ATTR(DBG_COLOR_SILVER, DBG_COLOR_BLACK);
	dbg_default_attr             = DBG_COLOR_ATTR(DBG_COLOR_SILVER, DBG_COLOR_BLACK);
	vga_backlog_scrollpos        = 0;
	vga_terminal_backlog_full    = false;
	vga_terminal_showcur         = false;
	vga_last_chr_caused_linewrap = false;
	vga_terminal_start           = vga_real_terminal_start;
	vga_terminal_cur             = vga_real_terminal_start;
	vga_terminal_2ndln           = vga_real_terminal_start + VGA_WIDTH;
	vga_terminal_end             = vga_real_terminal_start + VGA_WIDTH * VGA_HEIGHT;
	vga_terminal_lastln          = vga_real_terminal_start + VGA_WIDTH * (VGA_HEIGHT - 1);
	dbg_tabsize                  = DBG_TABSIZE_DEFAULT;
	dbg_indent                   = 0;
	vga_suppress_update          = 0;
	dbg_last_character           = 0;
	vga_cursor_is_shown          = false;
	memsetw(vga_real_terminal_start, VGA_EMPTY, VGA_WIDTH * VGA_HEIGHT);
	{
		u8 cursor_start;
		/* Make sure that the text-mode cursor is hidden by default. */
		cursor_start = vga_rcrt(VGA_CRTC_CURSOR_START);
		if (!(cursor_start & VGA_CRA_FCURSOR_DISABLE))
			vga_wcrt(VGA_CRTC_CURSOR_START, cursor_start | VGA_CRA_FCURSOR_DISABLE);
	}
}


PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_putc)(/*utf-8*/ char ch) {
	ansitty_putc(&dbg_tty, ch);
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_putuni)(/*utf-32*/ char32_t ch) {
	ansitty_putuni(&dbg_tty, ch);
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fillscreen)(/*utf-32*/ char32_t ch) {
	u8 cp_ch;
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	cp_ch = cp437_encode(ch);
	if (!cp_ch)
		cp_ch = '?';
	memsetw(vga_terminal_start,
	        VGA_CHR(cp_ch),
	        VGA_WIDTH * VGA_HEIGHT);
	vga_terminal_cur             = vga_terminal_start;
	vga_last_chr_caused_linewrap = false;
}

PUBLIC ATTR_DBGTEXT size_t FCALL
dbg_print(/*utf-8*/ char const *__restrict str) {
	return (size_t)ansitty_printer(&dbg_tty, str, strlen(str));
}

PUBLIC ATTR_DBGTEXT size_t FCALL
dbg_vprintf(/*utf-8*/ char const *__restrict format, va_list args) {
	return (size_t)format_vprintf(&ansitty_printer, &dbg_tty, format, args);
}

PUBLIC ATTR_DBGTEXT size_t VCALL
dbg_printf(/*utf-8*/ char const *__restrict format, ...) {
	size_t result;
	va_list args;
	va_start(args, format);
	result = dbg_vprintf(format, args);
	va_end(args);
	return result;
}

PUBLIC ATTR_DBGTEXT ssize_t KCALL
dbg_printer(void *UNUSED(ignored),
            /*utf-8*/ char const *__restrict data,
            size_t datalen) {
	return ansitty_printer(&dbg_tty, data, datalen);
}


/* Get/Set debug TTY screen data
 * NOTE: Reading Out-of-bound cells are read as the same value as a space-character
 *       cell when written using `dbg_putc(' ')' as the current cursor position.
 * NOTE: Writing Out-of-bound cells is a no-op.
 * NOTE: These functions will read/write the SCROLL-TOP screen data, and
 *      `dbg_setscreendata()' will apply `dbg_setscroll(0)'
 *       before actually copying cells.
 * @param: buf: A buffer capable of holding `size_x * size_y * dbg_screen_cellsize' bytes of data. */
PUBLIC ATTR_DBGTEXT NONNULL((5)) void FCALL
dbg_getscreendata(int x, int y,
                  unsigned int size_x,
                  unsigned int size_y,
                  void *__restrict buf) {
	u16 *screen;
	int x_end, y_end;
	if unlikely(!size_x || !size_y)
		return;
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(y >= VGA_HEIGHT || x >= VGA_WIDTH ||
	            x_end < 0 || y_end < 0) {
		memsetw((u16 *)buf, VGA_EMPTY, size_x * size_y);
		return;
	}
	if (y < 0) {
		memsetw((u16 *)buf, VGA_EMPTY, size_x * (unsigned int)-y);
		size_y += y;
		y = 0;
	}
	if ((unsigned int)y_end > VGA_HEIGHT) {
		memsetw((u16 *)buf + VGA_HEIGHT * size_x, VGA_EMPTY,
		        ((unsigned int)y_end - VGA_HEIGHT) * size_x);
		y_end  = VGA_HEIGHT;
		size_y = VGA_HEIGHT - y;
	}
	screen = vga_backlog_scrollpos
	         ? vga_backlog_screen
	         : vga_terminal_start;
	screen += y * VGA_WIDTH;
	if (x == 0 && size_x == VGA_WIDTH) {
		memcpyw(buf, screen, size_y * VGA_WIDTH);
	} else {
		unsigned int xhead, xcopy, xtail;
		xcopy = size_x;
		xtail = xhead = 0;
		if (x < 0) {
			xhead = (unsigned int)-x;
			xcopy -= xhead;
		} else {
			screen += x;
		}
		if (xcopy > VGA_WIDTH) {
			xtail = VGA_WIDTH - xcopy;
			xcopy = VGA_WIDTH;
		}
		while (size_y--) {
			buf = mempsetw(buf, VGA_EMPTY, xhead);
			buf = mempcpyw(buf, screen, xcopy);
			buf = mempsetw(buf, VGA_EMPTY, xtail);
			screen += VGA_WIDTH;
		}
	}
}

PUBLIC ATTR_DBGTEXT NONNULL((5)) void FCALL
dbg_setscreendata(int x, int y,
                  unsigned int size_x,
                  unsigned int size_y,
                  void const *__restrict buf) {
	u16 *screen;
	int x_end, y_end;
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	if unlikely(!size_x || !size_y)
		goto done;
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(y >= VGA_HEIGHT || x >= VGA_WIDTH ||
	            x_end < 0 || y_end < 0)
		goto done;
	if (y < 0) {
		size_y += y;
		y = 0;
	}
	if ((unsigned int)y_end > VGA_HEIGHT) {
		y_end  = VGA_HEIGHT;
		size_y = VGA_HEIGHT - y;
	}
	screen = vga_backlog_scrollpos
	         ? vga_backlog_screen
	         : vga_terminal_start;
	screen += y * VGA_WIDTH;
	if (x == 0 && size_x == VGA_WIDTH) {
		memcpyw(screen, buf, size_y * VGA_WIDTH);
	} else {
		unsigned int xhead, xcopy, xtail;
		xcopy = size_x;
		xtail = xhead = 0;
		if (x < 0) {
			xhead = (unsigned int)-x;
			xcopy -= xhead;
		} else {
			screen += x;
		}
		if (xcopy > VGA_WIDTH) {
			xtail = VGA_WIDTH - xcopy;
			xcopy = VGA_WIDTH;
		}
		while (size_y--) {
			buf = (u16 *)buf + xhead;
			mempcpyw(screen, buf, xcopy);
			buf = (u16 *)buf + xcopy + xtail;
			screen += VGA_WIDTH;
		}
	}
done:
	;
}


PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fillrect)(int x, int y, unsigned int size_x,
                            unsigned int size_y, /*utf-32*/ char32_t ch) {
	if (!size_x || !size_y) {
		if (vga_backlog_scrollpos && !vga_suppress_update)
			vga_backlog_setscrollpos(0);
		return;
	}
	dbg_hline(x, y, size_x, ch);
	if (size_y > 1)
		dbg_hline(x, y + size_y - 1, size_x, ch);
	if (size_y > 2) {
		dbg_vline(x, y + 1, size_y - 2, ch);
		if (size_x > 1)
			dbg_vline(x + size_x - 1, y + 1, size_y - 2, ch);
	}
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fillrect2)(int x, int y, unsigned int size_x, unsigned int size_y,
                             /*utf-32*/ char32_t tl, /*utf-32*/ char32_t t, /*utf-32*/ char32_t tr,
                             /*utf-32*/ char32_t l,                         /*utf-32*/ char32_t r,
                             /*utf-32*/ char32_t bl, /*utf-32*/ char32_t b, /*utf-32*/ char32_t br) {
	if (!size_x || !size_y) {
		if (vga_backlog_scrollpos && !vga_suppress_update)
			vga_backlog_setscrollpos(0);
		return;
	}
	dbg_pputuni(x, y, tl);
	if (size_x > 1)
		dbg_pputuni(x + size_x - 1, y, tr);
	if (size_y > 1) {
		dbg_pputuni(x, y + size_y - 1, bl);
		if (size_x > 1)
			dbg_pputuni(x + size_x - 1, y + size_y - 1, br);
	}
	if (size_x > 2) {
		dbg_hline(x + 1, y, size_x - 2, t);
		dbg_hline(x + 1, y + size_y - 1, size_x - 2, b);
		if (size_y > 2) {
			dbg_vline(x, y + 1, size_y - 2, l);
			dbg_vline(x + size_x - 1, y + 1, size_y - 2, r);
		}
	}
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_hline)(int x, int y, unsigned int size_x, /*utf-32*/ char32_t ch) {
	u8 cp_ch;
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	if unlikely(!size_x)
		goto done;
	if unlikely(y < 0 || y >= VGA_HEIGHT)
		goto done;
	if unlikely(x >= VGA_WIDTH)
		goto done;
	if (x < 0) {
		x = -x;
		if (size_x <= (unsigned int)x)
			goto done;
		size_x -= (unsigned int)x;
		x = 0;
	}
	cp_ch = cp437_encode(ch);
	if (!cp_ch)
		cp_ch = '?';
	memsetw(vga_terminal_start +
	        (unsigned int)x +
	        (unsigned int)y * VGA_WIDTH,
	        VGA_CHR(cp_ch),
	        size_x);
done:
	;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_vline)(int x, int y, unsigned int size_y, /*utf-32*/ char32_t ch) {
	u8 cp_ch;
	unsigned int i;
	u16 *dst, vga_ch;
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	if unlikely(!size_y)
		goto done;
	if unlikely(y >= VGA_HEIGHT)
		goto done;
	if unlikely(x < 0 || x >= VGA_WIDTH)
		goto done;
	if (y < 0) {
		y = -y;
		if (size_y <= (unsigned int)y)
			goto done;
		size_y -= (unsigned int)y;
		y = 0;
	}
	cp_ch = cp437_encode(ch);
	if (!cp_ch)
		cp_ch = '?';
	vga_ch = VGA_CHR(cp_ch);
	dst    = vga_terminal_start + (unsigned int)x + (unsigned int)y * VGA_WIDTH;
	for (i = 0; i < size_y; ++i) {
		*dst = vga_ch;
		dst += VGA_WIDTH;
	}
done:
	;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fillbox)(int x, int y,
                           unsigned int size_x,
                           unsigned int size_y,
                           /*utf-32*/ char32_t ch) {
	u8 cp_ch;
	int x_end, y_end;
	u16 *screen;
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	if unlikely(!size_x || !size_y)
		goto done;
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(y >= VGA_HEIGHT || x >= VGA_WIDTH ||
	            x_end < 0 || y_end < 0)
		goto done;
	if (y < 0) {
		size_y += y;
		y = 0;
	}
	if ((unsigned int)y_end > VGA_HEIGHT) {
		y_end  = VGA_HEIGHT;
		size_y = VGA_HEIGHT - y;
	}
	screen = vga_terminal_start;
	screen += y * VGA_WIDTH;
	cp_ch = cp437_encode(ch);
	if (!cp_ch)
		cp_ch = '?';
	if (x == 0 && size_x == VGA_WIDTH) {
		memsetw(screen, VGA_CHR(cp_ch), size_y * VGA_WIDTH);
	} else {
		if (x < 0) {
			size_x -= (unsigned int)-x;
		} else {
			screen += x;
		}
		if (size_x > VGA_WIDTH)
			size_x = VGA_WIDTH;
		while (size_y--) {
			mempsetw(screen, VGA_CHR(cp_ch), size_x);
			screen += VGA_WIDTH;
		}
	}
done:
	;
}

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C */
