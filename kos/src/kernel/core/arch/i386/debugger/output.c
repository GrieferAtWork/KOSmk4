/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
/* Copyright (c) 2019-2021 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2021 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C
#define GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#ifdef CONFIG_USE_UNIFIED_OUTPUT
#include <debugger/hook.h>
#include <debugger/io.h>

DECL_BEGIN


/* Arch-specific, fallback functions  for acquiring a  terminal.
 * These work the same as `vdo_enterdbg' / `vdo_leavedbg' when a
 * proper  video adapter has been configured in `viddev_default' */
INTERN ATTR_RETNONNULL WUNUSED struct vidttyaccess *
NOTHROW(FCALL dbg_fallback_acquiretty)(void) {
	/* TODO */
}

INTERN void NOTHROW(FCALL dbg_fallback_releasetty)(void) {
	/* TODO */
}


DECL_END
#else /* CONFIG_USE_UNIFIED_OUTPUT */
#include <debugger/hook.h>
#include <debugger/io.h>
#include <kernel/arch/syslog.h>
#include <kernel/paging.h>
#include <kernel/panic.h>
#include <kernel/printk.h>
#include <kernel/rand.h>

#include <hybrid/byteorder.h>
#include <hybrid/minmax.h>
#include <hybrid/overflow.h>

#include <hw/video/vga.h>
#include <sys/io.h>

#include <assert.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

#include <libansitty/ansitty.h>
#include <libvgastate/vga.h>

DECL_BEGIN

#define VGA_VRAM_BASE  0xa0000
#define VGA_VRAM_TEXT  0xb8000
#define VGA_VRAM_SIZE  0x01000


/* macro  for  composing an  8-bit  VGA register
 * index and value into a single 16-bit quantity */
#define VGA_OUT16VAL(v, r) (((v) << 8) | (r))

/* decide whether we should enable the faster 16-bit VGA register writes */
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
#define VGA_OUTW_WRITE 1
#endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */



/* generic VGA port read/write */
FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_DBGTEXT u8
NOTHROW(KCALL vga_r)(port_t port) {
	return inb_p(port);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_DBGTEXT void
NOTHROW(KCALL vga_w)(port_t port, u8 val) {
	outb_p(port, val);
}

FORCELOCAL NOBLOCK ATTR_ARTIFICIAL ATTR_DBGTEXT void
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
PUBLIC ATTR_DBGBSS unsigned int dbg_tabsize = 0;

/* Cursor X-position assigned after a line-feed */
PUBLIC ATTR_DBGBSS unsigned int dbg_indent = 0;

/* The logecho-enabled state for debugger output.
 * When enabled (default), debugger output is echoed via some
 * architecture-specific mechanism onto  an external  logging
 * sink which then allows external programs to inspect/record
 * debugger output. */
PUBLIC ATTR_DBGBSS bool dbg_logecho_enabled = false;

/* The ANSI TTY used for printing screen-output within the builtin debugger */
PUBLIC ATTR_DBGBSS struct ansitty dbg_tty = {};

PRIVATE ATTR_DBGBSS u32  vga_vram_offset         = 0;     /* [const] Current VRAM offset */
PRIVATE ATTR_DBGBSS u16 *vga_real_terminal_start = NULL;  /* [const] Real terminal display start */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_start      = NULL;  /* Terminal display start */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_end        = NULL;  /* Terminal display end */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_cur        = NULL;  /* Terminal display cursor */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_2ndln      = NULL;  /* Start of the second line within the terminal display. */
PRIVATE ATTR_DBGBSS u16 *vga_terminal_lastln     = NULL;  /* Start of the last line within the terminal display. */
PRIVATE ATTR_DBGBSS bool vga_terminal_showcur    = false; /* True if the current cursor position should be shown. */

#define VGA_SETCUR(x, y) (vga_terminal_cur = vga_terminal_start + (y) * VGA_WIDTH + (x))
#define VGA_GETCUR_X()   ((unsigned int)(vga_terminal_cur - vga_terminal_start) % VGA_WIDTH)
#define VGA_GETCUR_Y()   ((unsigned int)(vga_terminal_cur - vga_terminal_start) / VGA_WIDTH)
#define VGA_CHR(ch)      ((u16)(u8)(ch) | ((u16)dbg_tty.at_color << 8))
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
			         vga_rcrt(VGA_CRTC_CURSOR_START) &
			         ~(VGA_CRA_FCURSOR_DISABLE));
		}
		vga_cursor_is_shown = true;
	}
}

LOCAL ATTR_DBGTEXT void
NOTHROW(FCALL vga_disable_cursor)(void) {
	if (vga_cursor_is_shown) {
		if (vga_suppress_update == 0) {
			vga_wcrt(VGA_CRTC_CURSOR_START,
			         vga_rcrt(VGA_CRTC_CURSOR_START) |
			         VGA_CRA_FCURSOR_DISABLE);
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
		vga_wcrt(VGA_CRTC_CURSOR_HI, (u8)(pos >> 8));
		vga_wcrt(VGA_CRTC_CURSOR_LO, (u8)(pos));
		vga_enable_cursor();
	}
}


PRIVATE ATTR_DBGBSS u16 vga_backlog_screen[VGA_WIDTH * VGA_HEIGHT] = { 0 };
PRIVATE ATTR_DBGBSS unsigned int vga_backlog_scrollpos = 0;
#define vga_backlog_scrollmax                             \
	(vga_terminal_backlog_full                            \
	 ? (VGA_BACKLOG_NUMSCREENS * VGA_HEIGHT)              \
	 : (unsigned int)((size_t)(vga_terminal_backlog_cur - \
	                           vga_terminal_backlog) /    \
	                  VGA_WIDTH))



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
		        (size_t)(VGA_HEIGHT - pos) * VGA_WIDTH);
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
			assertf(num_trailing < COMPILER_LENOF(vga_terminal_backlog), "num_trailing = %" PRIuSIZ, num_trailing);
			assertf(num_leading < COMPILER_LENOF(vga_terminal_backlog), "num_leading = %" PRIuSIZ, num_leading);
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
			dest[i] = (u16)(u8)buf[i] |
			          ((u16)ANSITTY_PALETTE_INDEX(ANSITTY_CL_LIGHT_GRAY,
			                                      ANSITTY_CL_DARK_GRAY) << 8);
		}
	}
#endif
}



PUBLIC ATTR_PURE WUNUSED unsigned int
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
 * but instead draw to a separate  buffer, thus preventing flickering in  the
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

PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED u32
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
		         (size_t)(VGA_HEIGHT - 1) * VGA_WIDTH);
		memsetw(vga_terminal_lastln + 1, VGA_EMPTY, VGA_WIDTH - 1);
		vga_terminal_cur = vga_terminal_lastln + dbg_indent;
	}
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
	if (dbg_logecho_enabled) {
		char buf[UNICODE_UTF8_CURLEN];
		size_t buflen = (size_t)(unicode_writeutf8(buf, ch) - buf);
		x86_syslog_write(buf, buflen);
	}

	/* Scroll to bottom before printing a character. */
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	cp_ch = vga_state_encode(ch);
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
			    vga_state_encode(dbg_last_character) != 0 && cury)
				--cury;
			VGA_SETCUR(dbg_indent, cury);
		}	break;

		case '\n':
			if (VGA_GETCUR_X() <= dbg_indent &&
			    vga_state_encode(dbg_last_character) != 0) {
				/* Special case: The previous line was filled entirely, and the cursor had to be  wrapped
				 *               to the next line,  however the first character  then printed was also  a
				 *               linefeed. - In this case, don't wrap the line, as the linefeed requested
				 *               by the caller already happened implicitly, thus not creating an entirely
				 *               empty line and wasting what little screen space we have. */
			} else {
				/* Clear the remainder of the old line */
				if (dbg_tty.at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE)
					memsetw(vga_terminal_cur, VGA_EMPTY, VGA_WIDTH - VGA_GETCUR_X());
				if (vga_terminal_cur >= vga_terminal_lastln) {
					/* Scroll down */
					if (!vga_suppress_update)
						VGA_TERMINAL_BACKLOG_ADDLINE(vga_terminal_start);
					memmovew(vga_terminal_start, vga_terminal_2ndln,
					         (size_t)(VGA_HEIGHT - 1) * VGA_WIDTH);
					memsetw(vga_terminal_lastln, VGA_EMPTY, VGA_WIDTH);
					vga_terminal_cur = vga_terminal_lastln + dbg_indent;
				} else {
					VGA_SETCUR(dbg_indent, VGA_GETCUR_Y() + 1);
				}
				vga_last_chr_caused_linewrap = false;
			}
			break;

		default:
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
	ansitty_coord_t used_count, max_count;
	byte_t cpch;
	u16 cell;
	cpch = vga_state_encode((u32)ch);
	cell = VGA_CHR(cpch);
	max_count = (size_t)(vga_terminal_end - vga_terminal_cur);
	used_count = count;
	if (used_count > max_count)
		used_count = max_count;
	memsetw(vga_terminal_cur, cell, used_count);
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
	.ato_setcolor     = NULL,
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
	cp_ch = vga_state_encode(ch);
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
				    printer->p_printy >= 0 && printer->p_printy < VGA_HEIGHT) {
					memsetw(&vga_terminal_start[printer->p_printx + printer->p_printy * VGA_WIDTH],
					        VGA_EMPTY, VGA_WIDTH - (unsigned int)printer->p_printx);
				}
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

PUBLIC ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL dbg_pprinter_putuni)(dbg_pprinter_arg_t *__restrict printer, /*utf-32*/ char32_t ch) {
	if (dbg_tty._at_state != 0 || ch == (unsigned char)'\033') {
		ansitty_putuni(&dbg_tty, ch);
	} else {
		/* Output a regular, old character. */
		vga_pprinter_do_putuni(printer, ch);
	}
}

LOCAL NOBLOCK ATTR_DBGTEXT ATTR_PURE NONNULL((1)) char32_t
NOTHROW(FCALL dbg_pprinter_pending_ch32)(dbg_pprinter_arg_t const *__restrict printer) {
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

PUBLIC ATTR_DBGTEXT NONNULL((1)) void
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
	    pagedir_translate(vga_real_terminal_start) == (physaddr_t)VGA_VRAM_TEXT) {
		vga_oldmapping_did_prepare = false;
		return;
	}
	/* We might get here so early during booting that the page frame  allocator
	 * has yet to be initialized, at which point prepare would fail. - However,
	 * at that point we'd still have access to the physical identity map, so we
	 * should  instead also support  its use instead of  only hacking around to
	 * place a temporary mapping of the VGA display just before the kernel. */
	vga_oldmapping_did_prepare = pagedir_prepare((void *)((uintptr_t)vga_real_terminal_start & ~PAGEMASK),
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
			                              (physaddr_t)VGA_VRAM_TEXT + i * PAGESIZE,
			                              PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
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
			    pagedir_translate(result) == (physaddr_t)(VGA_VRAM_BASE + vram_offset)) {
				vga_vram_offset = vram_offset;
				return result + offset;
			}
			printk(DBGSTR(KERN_CRIT "[dbg] Video memory not prepared, and not "
			                        "identity-mapped. This will probably go wrong...\n"));
		}
#endif /* ARCH_PAGEDIR_NEED_PERPARE_FOR_KERNELSPACE */
		addr = (byte_t *)((uintptr_t)vga_real_terminal_start & ~PAGEMASK);
		pagedir_map(addr, PAGESIZE,
		            (physaddr_t)VGA_VRAM_BASE + vram_offset,
		            PAGEDIR_PROT_READ | PAGEDIR_PROT_WRITE);
		pagedir_syncone(addr);
		vga_vram_offset = vram_offset;
	}
	return (byte_t *)vga_real_terminal_start + offset;
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


PRIVATE ATTR_DBGBSS struct vga_state vga_oldstate = {};
PRIVATE ATTR_DBGBSS bool vga_showscreen_enabled = false;
PRIVATE ATTR_DBGBSS struct vga_cursor_regs vga_showscreen_oldcursor = {};


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
		vga_state_load(&vga_oldstate);
		vga_showscreen_enabled = true;
	}
}

PUBLIC void NOTHROW(FCALL dbg_endshowscreen)(void) {
	if (vga_showscreen_enabled) {
		vga_state_text();
		vga_vram(VGA_VRAM_TEXT - VGA_VRAM_BASE);
		memcpyw(vga_real_terminal_start, vga_backlog_screen, VGA_WIDTH * VGA_HEIGHT);
		vga_showscreen_enabled = false;
		VGA_SetCursor(&vga_showscreen_oldcursor);
	}
}


INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_initialize_tty)(void) {
	vga_map();                     /* Map a portion of VRAM into memory. */
	vga_state_save(&vga_oldstate); /* Save the old VGA mode. */
	vga_vram(VGA_VRAM_TEXT - VGA_VRAM_BASE);
}

INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_finalize_tty)(void) {
	/* Make sure we're not in show-screen mode. */
	dbg_endshowscreen();
	vga_state_load(&vga_oldstate);
	vga_state_fini(&vga_oldstate);
	/* Unmap video memory. */
	vga_unmap();
}

INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_reset_tty)(void) {
	/* Make sure we're not in show-screen mode from before. */
	dbg_endshowscreen();
	vga_state_text(); /* Ensure that we're in text-mode */
	vga_vram_offset = 0;
	vga_vram(VGA_VRAM_TEXT - VGA_VRAM_BASE);
	ansitty_init(&dbg_tty, &vga_tty_operators);
	vga_showscreen_enabled       = false;
	vga_terminal_backlog_cur     = vga_terminal_backlog;
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
	dbg_logecho_enabled          = true;
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
	byte_t cp_ch;
	if (vga_backlog_scrollpos && !vga_suppress_update)
		vga_backlog_setscrollpos(0);
	cp_ch = vga_state_encode(ch);
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

PUBLIC ATTR_DBGTEXT ssize_t FORMATPRINTER_CC
dbg_printer(void *UNUSED(ignored),
            /*utf-8*/ char const *__restrict data,
            size_t datalen) {
	return ansitty_printer(&dbg_tty, data, datalen);
}


/* Get/Set debug TTY screen data
 * NOTE: Out-of-bound cells  are read  as the  same value  as a  space-character
 *       cell when written using `dbg_putc(' ')' at the current cursor position.
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
		memsetw((u16 *)buf, VGA_EMPTY, (size_t)size_x * size_y);
		return;
	}
	if (y < 0) {
		memsetw((u16 *)buf, VGA_EMPTY, (size_t)size_x * (unsigned int)-y);
		size_y += y;
		y = 0;
	}
	if ((unsigned int)y_end > VGA_HEIGHT) {
		memsetw((u16 *)buf + VGA_HEIGHT * size_x, VGA_EMPTY,
		        (size_t)((unsigned int)y_end - VGA_HEIGHT) * size_x);
		y_end  = VGA_HEIGHT;
		size_y = VGA_HEIGHT - y;
	}
	screen = vga_backlog_scrollpos
	         ? vga_backlog_screen
	         : vga_terminal_start;
	screen += y * VGA_WIDTH;
	if (x == 0 && size_x == VGA_WIDTH) {
		memcpyw(buf, screen, (size_t)size_y * VGA_WIDTH);
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
			buf = mempsetw(buf, VGA_EMPTY, (size_t)xhead);
			buf = mempcpyw(buf, screen, (size_t)xcopy);
			buf = mempsetw(buf, VGA_EMPTY, (size_t)xtail);
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
		memcpyw(screen, buf, (size_t)size_y * VGA_WIDTH);
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
			mempcpyw(screen, buf, (size_t)xcopy);
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
	byte_t cp_ch;
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
	cp_ch = vga_state_encode(ch);
	memsetw(vga_terminal_start +
	        (unsigned int)x +
	        (unsigned int)y * VGA_WIDTH,
	        VGA_CHR(cp_ch),
	        (size_t)size_x);
done:
	;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_vline)(int x, int y, unsigned int size_y, /*utf-32*/ char32_t ch) {
	byte_t cp_ch;
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
	cp_ch = vga_state_encode(ch);
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
	byte_t cp_ch;
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
	cp_ch = vga_state_encode(ch);
	if (x == 0 && size_x == VGA_WIDTH) {
		memsetw(screen, VGA_CHR(cp_ch), (size_t)size_y * VGA_WIDTH);
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
#endif /* !CONFIG_USE_UNIFIED_OUTPUT */
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_CORE_ARCH_I386_DEBUGGER_OUTPUT_C */
