/*[[[magic
local gcc_opt = options.setdefault("GCC.options", []);
if (gcc_opt.removeif([](x) -> x.startswith("-O")))
	gcc_opt.append("-Os");
]]]*/
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
#ifndef GUARD_KERNEL_SRC_DEBUGGER_OUTPUT_C
#define GUARD_KERNEL_SRC_DEBUGGER_OUTPUT_C 1
#define DISABLE_BRANCH_PROFILING
#define _KOS_SOURCE 1
#define _GNU_SOURCE 1

#include <kernel/compiler.h>

#include <debugger/config.h>
#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <debugger/output.h>
#include <debugger/hook.h>
#include <debugger/io.h>
#include <dev/video.h>

#include <hybrid/host.h>
#include <hybrid/overflow.h>

#include <alloca.h>
#include <format-printer.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unicode.h>

#undef DBG_LOGECHO
#if defined(__i386__) || defined(__x86_64__)
#include <kernel/arch/syslog.h>
#define DBG_LOGECHO(buf, buflen) x86_syslog_write(buf, buflen)
#endif /* ... */

DECL_BEGIN

DATDEF unsigned int dbg_scroll_maxline_ ASMNAME("dbg_scroll_maxline");
DATDEF unsigned int dbg_screen_width_ ASMNAME("dbg_screen_width");
DATDEF unsigned int dbg_screen_height_ ASMNAME("dbg_screen_height");
DATDEF unsigned int dbg_screen_cellsize_ ASMNAME("dbg_screen_cellsize");
#undef dbg_scroll_maxline
#undef dbg_screen_width
#undef dbg_screen_height
#undef dbg_screen_cellsize
#define dbg_scroll_maxline  dbg_scroll_maxline_
#define dbg_screen_width    dbg_screen_width_
#define dbg_screen_height   dbg_screen_height_
#define dbg_screen_cellsize dbg_screen_cellsize_

/* The logecho-enabled state for debugger output.
 * When enabled (default), debugger output is echoed via some
 * architecture-specific mechanism onto  an external  logging
 * sink which then allows external programs to inspect/record
 * debugger output. */
PUBLIC ATTR_DBGBSS bool dbg_logecho_enabled = false;

/* The ANSI TTY used for printing screen-output within the builtin debugger */
PUBLIC ATTR_DBGBSS struct ansitty dbg_tty = {};

/* [1..1] The video terminal attached to the debugger. */
PRIVATE ATTR_DBGBSS struct vidttyaccess *dbg_vtty = NULL;

/* [0..1] The real video terminal currently being used (set to `NULL' while "screen" is active) */
PRIVATE ATTR_DBGBSS struct vidttyaccess *dbg_real_vtty = NULL;

/* [0..1] The video device used to drive the debugger
 *        (or NULL to use `dbg_fallback_acquiretty()'). */
PRIVATE ATTR_DBGBSS struct viddev *dbg_vdev = NULL;

/* Arch-specific, fallback functions  for acquiring a  terminal.
 * These work the same as `vdo_enterdbg' / `vdo_leavedbg' when a
 * proper  video adapter has been configured in `viddev_default' */
INTDEF ATTR_RETNONNULL WUNUSED struct vidttyaccess *
NOTHROW(FCALL dbg_fallback_acquiretty)(void);
INTDEF void NOTHROW(FCALL dbg_fallback_releasetty)(void);


/* Recursion counter for `dbg_beginupdate()' / `dbg_endupdate()' */
PRIVATE ATTR_DBGBSS unsigned int dbg_update_recursion = 0;

/* TTY configuration */
PUBLIC ATTR_DBGBSS unsigned int dbg_tabsize         = 0; /* Alignment of TAB characters (default: `DBG_TABSIZE_DEFAULT') */
PUBLIC ATTR_DBGBSS unsigned int dbg_indent          = 0; /* Cursor X-position assigned after a line-feed */
PUBLIC ATTR_DBGBSS unsigned int dbg_scroll_maxline  = 0; /* [const] == Max # of lines in `dbgtty_backlog' (== DBG_TTY_BACKLOG_SIZE / dbgtty_linesize)  */
PUBLIC ATTR_DBGBSS unsigned int dbg_screen_width    = 0; /* [const] == dbg_vtty->vta_resx */
PUBLIC ATTR_DBGBSS unsigned int dbg_screen_height   = 0; /* [const] == dbg_vtty->vta_resy */
PUBLIC ATTR_DBGBSS unsigned int dbg_screen_cellsize = 0; /* [const] == dbg_vtty->vta_cellsize */

#define DBG_TTY_BACKLOG_SIZE ((uint16_t)sizeof(dbgtty_backlog))
PRIVATE ATTR_DBGBSS byte_t dbgtty_backlog[0x8000]; /* Display scroll-back buffer. (wraps around) */
PRIVATE ATTR_DBGBSS uint16_t dbgtty_backend   = 0; /* Offset into `dbgtty_backlog' for where to store the next line. */
PRIVATE ATTR_DBGBSS uint16_t dbgtty_linesize  = 0; /* Size of a single line of text in `dbgtty_backlog' */
PRIVATE ATTR_DBGBSS uint16_t dbgtty_scrollpos = 0; /* [<= dbgtty_scrolllen] Scroll position in lines (0 means not scrolling) */
PRIVATE ATTR_DBGBSS uint16_t dbgtty_scrolllen = 0; /* [<= dbgtty_scrollmax] # of lines stored in `dbgtty_backlog' */
#define dbgtty_scrollmax dbg_scroll_maxline        /* [const] Max # of lines in `dbgtty_backlog' (== DBG_TTY_BACKLOG_SIZE / dbgtty_linesize) */

/* # of characters used for rendering the current scroll position */
PRIVATE ATTR_DBGBSS uint8_t dbgtty_scrollpos_tlen = 0;

PRIVATE ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL dbgtty_init4tty)(struct vidttyaccess *__restrict tty) {
	/* Set terminal. */
	dbg_real_vtty = tty;
	dbg_vtty      = tty;

	/* Load terminal properties. */
	dbg_screen_width    = tty->vta_resx;
	dbg_screen_height   = tty->vta_resy;
	dbg_screen_cellsize = tty->vta_cellsize;
	dbgtty_linesize     = dbg_screen_cellsize * dbg_screen_width;
	dbg_scroll_maxline  = DBG_TTY_BACKLOG_SIZE / dbgtty_linesize;

	/* Clear backlog */
	dbgtty_backend        = 0;
	dbgtty_scrollpos      = 0;
	dbgtty_scrolllen      = 0;
	dbgtty_scrollpos_tlen = 0;
}

/* Return the offset into `dbgtty_backlog' for where to find data
 * for the bottom  off-screen line when  `dbgtty_scrollpos != 0'. */
#define dbgtty_scroll_offsetof_botline() \
	((uint16_t)(dbgtty_backend - (dbgtty_scrollpos * dbgtty_linesize)) % DBG_TTY_BACKLOG_SIZE)

/* Return  the offset into `dbgtty_backlog' for where to find data for
 * the top off-screen line when `dbgtty_scrollpos < dbgtty_scrolllen'. */
#define dbgtty_scroll_offsetof_topline() \
	((uint16_t)(dbgtty_backend - ((dbgtty_scrollpos + 1) * dbgtty_linesize)) % DBG_TTY_BACKLOG_SIZE)

/* Read data from the backlog buffer. */
PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL dbgtty_rdbacklog)(uint16_t offset, byte_t buf[], uint16_t size) {
	while (size) {
		uint16_t avail;
		offset %= DBG_TTY_BACKLOG_SIZE;
		avail = DBG_TTY_BACKLOG_SIZE - offset;
		if (avail > size)
			avail = size;
		buf = (byte_t *)mempcpy(buf, dbgtty_backlog + offset, avail);
		size -= avail;
		offset += avail;
	}
}

/* Write data to the backlog buffer. */
PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL dbgtty_wrbacklog)(uint16_t offset, byte_t const buf[], uint16_t size) {
	while (size) {
		uint16_t avail;
		offset %= DBG_TTY_BACKLOG_SIZE;
		avail = DBG_TTY_BACKLOG_SIZE - offset;
		if (avail > size)
			avail = size;
		buf = (byte_t *)mempcpy(dbgtty_backlog + offset, buf, avail);
		size -= avail;
		offset += avail;
	}
}

/* TTY show-screen support (display the contents of the monitor before the debugger was enabled)
 * WARNING: `dbg_beginshowscreen()' also implies the behavior of `dbg_endupdate(true)'
 * NOTE: This functionality of these functions is also available through the `screen' command */
PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_beginshowscreen)(void) {
	if (dbg_real_vtty == NULL)
		return; /* Already in "screen"-mode */
	dbg_endupdate(true);
	if (dbg_vdev) {
		(*viddev_getops(dbg_vdev)->vdo_leavedbg)(dbg_vdev);
	} else {
		dbg_fallback_releasetty();
	}
	dbg_real_vtty = NULL;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_endshowscreen)(void) {
	if (dbg_real_vtty != NULL)
		return; /* Not in "screen"-mode */
	if (dbg_vdev) {
		dbg_real_vtty = (*viddev_getops(dbg_vdev)->vdo_enterdbg)(dbg_vdev);
	} else {
		dbg_real_vtty = dbg_fallback_acquiretty();
	}
	if unlikely(dbg_real_vtty != dbg_vtty) {
		/* Shouldn't happen, but can be handled like this: */
		dbgtty_init4tty(dbg_real_vtty);
	}
}





/* Raw scroll on-screen cells up once (doesn't append to the backlog)
 * Also doesn't fill newly exposed cells! */
#define dbgtty_scrollup_screen() \
	(*dbg_vtty->vta_copycell)(dbg_vtty, dbg_vtty->_vta_scrl1_to, dbg_vtty->_vta_scrl1_from, dbg_vtty->_vta_scrl1_cnt);
#define dbgtty_scrolldown_screen() \
	(*dbg_vtty->vta_copycell)(dbg_vtty, dbg_vtty->_vta_scrl1_from, dbg_vtty->_vta_scrl1_to, dbg_vtty->_vta_scrl1_cnt);

PRIVATE ATTR_DBGTEXT NONNULL((2)) void
NOTHROW(FCALL dbgtty_getcells)(uintptr_t addr, byte_t buf[], uintptr_half_t num_cells) {
	while (num_cells--) {
		(*dbg_vtty->vta_getcelldata)(dbg_vtty, addr, buf);
		buf += dbg_screen_cellsize;
		++addr;
	}
}

PRIVATE ATTR_DBGTEXT NONNULL((2)) void
NOTHROW(FCALL dbgtty_setcells)(uintptr_t addr, byte_t const buf[], uintptr_half_t num_cells) {
	while (num_cells--) {
		(*dbg_vtty->vta_setcelldata)(dbg_vtty, addr, buf);
		buf += dbg_screen_cellsize;
		++addr;
	}
}

#define dbgtty_getlinecells(y, buf) dbgtty_getcells((y) * dbg_vtty->vta_scan, buf, dbg_screen_width);
#define dbgtty_setlinecells(y, buf) dbgtty_setcells((y) * dbg_vtty->vta_scan, buf, dbg_screen_width);

/* Screen data backup area for scroll position display. */
PRIVATE ATTR_DBGBSS byte_t dbgtty_scrollpos_backup[8 * 32];
#define dbgtty_scrollpos_dispaddr(textlen) \
	(dbg_screen_height * dbg_vtty->vta_scan - (textlen))

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL dbgtty_hidescrollpos)(void) {
	uintptr_t txtaddr;
	if (!dbgtty_scrollpos_tlen)
		return;
	/* Restore cells used for the scroll position display. */
	txtaddr = dbgtty_scrollpos_dispaddr(dbgtty_scrollpos_tlen);
	dbgtty_setcells(txtaddr, dbgtty_scrollpos_backup, dbgtty_scrollpos_tlen);
	dbgtty_scrollpos_tlen = 0;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(FCALL dbgtty_showscrollpos)(void) {
	size_t textlen;
	uintptr_t i, txtaddr;
	uint8_t saved_color;
	char text[COMPILER_LENOF(PRIMAXu16 "/" PRIMAXu16)];
	textlen = sprintf(text, "%" PRIu16 "/%" PRIu16,
	                  dbgtty_scrolllen - dbgtty_scrollpos,
	                  dbgtty_scrolllen);
	/* Check if our backup area is large enough. */
	if (textlen * dbg_screen_cellsize > sizeof(dbgtty_scrollpos_backup))
		return; /* Can't render this :( */
	txtaddr = dbgtty_scrollpos_dispaddr(textlen);
	dbgtty_getcells(txtaddr, dbgtty_scrollpos_backup, textlen);
	saved_color      = dbg_tty.at_color;
	dbg_tty.at_color = ANSITTY_PALETTE_INDEX(ANSITTY_CL_LIGHT_GRAY, ANSITTY_CL_DARK_GRAY);
	for (i = 0; i < textlen; ++i)
		(*dbg_vtty->vta_setcell)(dbg_vtty, &dbg_tty, txtaddr + i, text[i]);
	dbg_tty.at_color      = saved_color;
	dbgtty_scrollpos_tlen = textlen;
}


/* For backlog: scroll up once (moving on-screen content down)
 * >> caller must ensure `dbgtty_scrollpos < dbgtty_scrolllen' */
PRIVATE ATTR_NOINLINE ATTR_DBGTEXT void
NOTHROW(FCALL dbgtty_scrollup)(void) {
	uint16_t offset;
	byte_t *topline, *botline;
	dbgtty_hidescrollpos();
	offset  = dbgtty_scroll_offsetof_topline();
	topline = (byte_t *)alloca(dbgtty_linesize);
	botline = (byte_t *)alloca(dbgtty_linesize);
	dbgtty_getlinecells(dbg_screen_height - 1, botline);
	dbgtty_rdbacklog(offset, topline, dbgtty_linesize);
	dbgtty_scrolldown_screen(); /* Scroll screen. */
	dbgtty_setlinecells(0, topline);
	dbgtty_wrbacklog(offset, botline, dbgtty_linesize);
	dbgtty_scrollpos += 1;
	dbgtty_showscrollpos();
	if (dbgtty_scrollpos == 1) {
		/* Try to hide the cursor. */
		if ((dbg_vtty->vta_flags & VIDTTYACCESS_F_ACTIVE) &&
		    !(dbg_tty.at_ttymode & ANSITTY_MODE_HIDECURSOR))
			(*dbg_vtty->vta_hidecursor)(dbg_vtty);
	}
}

/* For backlog: scroll down once (moving on-screen content up)
 * >> caller must ensure `dbgtty_scrollpos != 0' */
PRIVATE ATTR_NOINLINE ATTR_DBGTEXT void
NOTHROW(FCALL dbgtty_scrolldown)(void) {
	uint16_t offset;
	byte_t *topline, *botline;
	dbgtty_hidescrollpos();
	offset  = dbgtty_scroll_offsetof_botline();
	topline = (byte_t *)alloca(dbgtty_linesize);
	botline = (byte_t *)alloca(dbgtty_linesize);
	dbgtty_getlinecells(0, topline);
	dbgtty_rdbacklog(offset, botline, dbgtty_linesize);
	dbgtty_scrollup_screen(); /* Scroll screen. */
	dbgtty_setlinecells(dbg_screen_height - 1, botline);
	dbgtty_wrbacklog(offset, topline, dbgtty_linesize);
	dbgtty_scrollpos -= 1;
	if (dbgtty_scrollpos != 0) {
		dbgtty_showscrollpos();
	} else {
		/* Try to show the cursor. */
		if ((dbg_vtty->vta_flags & VIDTTYACCESS_F_ACTIVE) &&
		    !(dbg_tty.at_ttymode & ANSITTY_MODE_HIDECURSOR))
			(*dbg_vtty->vta_showcursor)(dbg_vtty);
	}
}

PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED unsigned int
NOTHROW(FCALL dbg_getscroll)(void) {
	return dbgtty_scrollpos;
}

PUBLIC ATTR_DBGTEXT unsigned int
NOTHROW(FCALL dbg_setscroll)(unsigned int pos) {
	if (pos > dbgtty_scrolllen)
		pos = dbgtty_scrolllen;
	while (pos != dbgtty_scrollpos) {
		if (pos < dbgtty_scrollpos) {
			dbgtty_scrolldown();
		} else {
			dbgtty_scrollup();
		}
	}
	return pos;
}


/* Hints towards the screen driver to temporarily stop drawing to the screen,
 * but instead draw to a separate  buffer, thus preventing flickering in  the
 * case of whole screen redraw operations.
 * NOTE: Also affects updates made to the cursor position
 * @param: force: When true, force updates to stop. */
PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_beginupdate)(void) {
	if (dbg_update_recursion++ == 0)
		dbg_vtty->vta_flags &= ~VIDTTYACCESS_F_ACTIVE;
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_endupdate)(bool force) {
	if (dbg_update_recursion == 0)
		return; /* Already active. */
	--dbg_update_recursion;

	/* When force is true, always re-activate. */
	if (force)
		dbg_update_recursion = 0;

	/* When we hit `0', re-activate the tty. */
	if (dbg_update_recursion == 0) {
		dbg_vtty->vta_flags |= VIDTTYACCESS_F_ACTIVE;
		(*dbg_vtty->vta_activate)(dbg_vtty);
	}
}

PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED u32
NOTHROW(FCALL dbg_getcur)(void) {
	return DBG_MAKECUR(dbg_vtty->vta_cursor.vtc_cellx,
	                   dbg_vtty->vta_cursor.vtc_celly);
}

PUBLIC ATTR_DBGTEXT u32
NOTHROW(FCALL dbg_setcur)(int x, int y) {
	if (x < 0)
		x = 0;
	if ((unsigned int)x >= dbg_screen_width)
		x = dbg_screen_width - 1;
	if (y < 0)
		y = 0;
	if ((unsigned int)y >= dbg_screen_height)
		y = dbg_screen_height - 1;
	dbg_vtty->vta_cursor.vtc_cellx = (uintptr_half_t)x;
	dbg_vtty->vta_cursor.vtc_celly = (uintptr_half_t)y;

	/* Update on-screen cursor if necessary. */
	if ((dbg_vtty->vta_flags & VIDTTYACCESS_F_ACTIVE) &&
	    !(dbg_tty.at_ttymode & ANSITTY_MODE_HIDECURSOR))
		(*dbg_vtty->vta_showcursor)(dbg_vtty);
	return DBG_MAKECUR(x, y);
}


PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_bell)(void) {
	/* Not implemented */
	COMPILER_IMPURE();
}

PUBLIC ATTR_DBGTEXT NONNULL((1)) void
NOTHROW(FCALL dbg_pprinter_putuni)(dbg_pprinter_arg_t *__restrict printer,
                                   /*utf-32*/ char32_t ch) {
	/* Deal with escape characters. */
	if (dbg_tty._at_state != 0 || ch == (unsigned char)'\033') {
		ansitty_putuni(&dbg_tty, ch);
		return;
	}

	/* Output a regular, old character. */
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
		max_space = dbg_screen_width - cur_x;
		if (num_space > max_space)
			num_space = max_space;
		/* Output space characters. */
		if (printer->p_printx >= 0 && (unsigned int)printer->p_printx < dbg_screen_width &&
		    printer->p_printy >= 0 && (unsigned int)printer->p_printy < dbg_screen_height) {
			(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty,
			                           (unsigned int)printer->p_printx +
			                           (unsigned int)printer->p_printy *
			                           dbg_vtty->vta_scan,
			                           ' ',
			                           num_space);
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
			if (printer->p_printx >= 0 && (unsigned int)printer->p_printx < dbg_screen_width &&
			    printer->p_printy >= 0 && (unsigned int)printer->p_printy < dbg_screen_height) {
				(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty,
				                           (unsigned int)printer->p_printx +
				                           (unsigned int)printer->p_printy *
				                           dbg_vtty->vta_scan,
				                           ' ',
				                           dbg_screen_width -
				                           (unsigned int)printer->p_printx);
			}
		}
		printer->p_printx = dbg_indent;
		if (ch == '\n')
			++printer->p_printy;
		break;

	default:
		/* Output a normal character */
		if (printer->p_printx >= 0 && (unsigned int)printer->p_printx < dbg_screen_width &&
		    printer->p_printy >= 0 && (unsigned int)printer->p_printy < dbg_screen_height) {
			(*dbg_vtty->vta_setcell)(dbg_vtty, &dbg_tty,
			                         (unsigned int)printer->p_printx +
			                         (unsigned int)printer->p_printy *
			                         dbg_vtty->vta_scan,
			                         ch);
		}
		++printer->p_printx;
		break;
	}

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
	int x_end, y_end;
	unsigned int xi, yi;
	dbg_setscroll(0);
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(x_end < 0)
		return;
	if unlikely(y_end < 0)
		return;
	if unlikely((unsigned int)x >= dbg_screen_width)
		return;
	if unlikely((unsigned int)y >= dbg_screen_height)
		return;
	if (y < 0) {
		size_y += y;
		y = 0;
	}
	if (x < 0) {
		size_x += x;
		x = 0;
	}
	if ((unsigned int)y_end > dbg_screen_height) {
		y_end  = dbg_screen_height;
		size_y = dbg_screen_height - y;
	}
	if ((unsigned int)x_end > dbg_screen_width) {
		x_end  = dbg_screen_width;
		size_x = dbg_screen_width - x;
	}

	/* Actually extract cell data. */
	for (yi = (unsigned int)y; yi < (unsigned int)y_end; ++yi) {
		for (xi = (unsigned int)x; xi < (unsigned int)x_end; ++xi) {
			uintptr_t addr = xi + yi * dbg_vtty->vta_scan;
			(*dbg_vtty->vta_getcelldata)(dbg_vtty, addr, (byte_t *)buf);
			buf = (byte_t *)buf + dbg_screen_cellsize;
		}
	}
}

PUBLIC ATTR_DBGTEXT NONNULL((5)) void FCALL
dbg_setscreendata(int x, int y,
                  unsigned int size_x,
                  unsigned int size_y,
                  void const *__restrict buf) {
	int x_end, y_end;
	unsigned int xi, yi;
	dbg_setscroll(0);
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(x_end < 0)
		return;
	if unlikely(y_end < 0)
		return;
	if unlikely((unsigned int)x >= dbg_screen_width)
		return;
	if unlikely((unsigned int)y >= dbg_screen_height)
		return;
	if (y < 0) {
		size_y += y;
		y = 0;
	}
	if (x < 0) {
		size_x += x;
		x = 0;
	}
	if ((unsigned int)y_end > dbg_screen_height) {
		y_end  = dbg_screen_height;
		size_y = dbg_screen_height - y;
	}
	if ((unsigned int)x_end > dbg_screen_width) {
		x_end  = dbg_screen_width;
		size_x = dbg_screen_width - x;
	}

	/* Actually set cell data. */
	for (yi = (unsigned int)y; yi < (unsigned int)y_end; ++yi) {
		for (xi = (unsigned int)x; xi < (unsigned int)x_end; ++xi) {
			uintptr_t addr = xi + yi * dbg_vtty->vta_scan;
			(*dbg_vtty->vta_setcelldata)(dbg_vtty, addr, (byte_t const *)buf);
			buf = (byte_t const *)buf + dbg_screen_cellsize;
		}
	}
}


PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fillbox)(int x, int y,
                           unsigned int size_x,
                           unsigned int size_y,
                           /*utf-32*/ char32_t ch) {
	int x_end, y_end;
	unsigned int yi;
	dbg_setscroll(0);
	x_end = x + size_x;
	y_end = y + size_y;
	if unlikely(x_end < 0)
		return;
	if unlikely(y_end < 0)
		return;
	if unlikely((unsigned int)x >= dbg_screen_width)
		return;
	if unlikely((unsigned int)y >= dbg_screen_height)
		return;
	if (y < 0) {
		size_y += y;
		y = 0;
	}
	if (x < 0) {
		size_x += x;
		x = 0;
	}
	if ((unsigned int)y_end > dbg_screen_height) {
		y_end  = dbg_screen_height;
		size_y = dbg_screen_height - y;
	}
	if ((unsigned int)x_end > dbg_screen_width) {
		x_end  = dbg_screen_width;
		size_x = dbg_screen_width - x;
	}

	/* Fill cells. */
	for (yi = (unsigned int)y; yi < (unsigned int)y_end; ++yi) {
		uintptr_t addr = (unsigned int)x + yi * dbg_vtty->vta_scan;
		(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty, addr, ch, size_x);
	}
}






/************************************************************************/
/* ANSI TTY Operators                                                   */
/************************************************************************/
PRIVATE ATTR_NOINLINE ATTR_DBGTEXT void
NOTHROW(FCALL dbgtty_scrollone)(void) {
	/* Copy cell data into backlog buffer. */
	if (dbgtty_scrollmax != 0) {
		uint16_t offset;
		byte_t *topline;
		offset  = dbgtty_scroll_offsetof_botline();
		topline = (byte_t *)alloca(dbgtty_linesize);
		dbgtty_getlinecells(0, topline);
		dbgtty_wrbacklog(offset, topline, dbgtty_linesize);
		if (dbgtty_scrolllen < dbgtty_scrollmax)
			dbgtty_scrolllen += 1;
		dbgtty_backend += dbgtty_linesize;
		dbgtty_backend %= DBG_TTY_BACKLOG_SIZE;
	}

	/* Scroll screen. */
	dbgtty_scrollup_screen();

	/* fill cells at bottom of screen with spaces. */
	(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty,
	                           dbg_vtty->_vta_scrl1_fil,
	                           ' ', dbg_screen_width);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC dbgtty_putc)(struct ansitty *__restrict UNUSED(self),
                                   char32_t ch) {
#ifdef DBG_LOGECHO
	if (dbg_logecho_enabled) {
		char buf[UNICODE_UTF8_CURLEN];
		size_t buflen = (size_t)(unicode_writeutf8(buf, ch) - buf);
		DBG_LOGECHO(buf, buflen);
	}
#endif /* DBG_LOGECHO */

	/* Scroll to bottom before printing a character. */
	dbg_setscroll(0);
	switch (ch) {

	case 7: /* BEL */
		dbg_bell();
		break;

	case '\t': {
		uintptr_half_t advance;
		/* Check if we need to scroll. */
		if (dbg_vtty->vta_cursor.vtc_celly >= dbg_vtty->vta_scroll_yend) {
			dbg_vtty->vta_cursor.vtc_celly = dbg_vtty->_vta_scrl_ymax;
			dbgtty_scrollone();
		}
		advance = dbg_tabsize - (dbg_vtty->vta_cursor.vtc_cellx % dbg_tabsize);
		if ((dbg_vtty->vta_cursor.vtc_cellx + advance) > dbg_screen_width)
			advance = dbg_screen_width - dbg_vtty->vta_cursor.vtc_cellx;
		(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty,
		                           dbg_vtty->vta_cursor.vtc_cellx +
		                           dbg_vtty->vta_cursor.vtc_celly *
		                           dbg_vtty->vta_scan,
		                           ' ', advance);
		dbg_vtty->vta_cursor.vtc_cellx += advance;
		if (dbg_vtty->vta_cursor.vtc_cellx >= dbg_screen_width) {
			if (dbg_indent >= dbg_screen_width)
				dbg_indent = dbg_screen_width - 1;
			dbg_vtty->vta_cursor.vtc_cellx = dbg_indent;
			++dbg_vtty->vta_cursor.vtc_celly;

			/* Set the EOL flag after an implicit line-feed */
			dbg_vtty->vta_flags |= VIDTTYACCESS_F_EOL;
			goto maybe_hide_cursor_after_eol;
		}
	}	break;

	case '\b':
		if (OVERFLOW_USUB(dbg_vtty->vta_cursor.vtc_cellx, 1, &dbg_vtty->vta_cursor.vtc_cellx)) {
			dbg_vtty->vta_cursor.vtc_cellx = dbg_screen_width - 1;
			if (OVERFLOW_USUB(dbg_vtty->vta_cursor.vtc_celly, 1, &dbg_vtty->vta_cursor.vtc_celly)) {
				/* Stay in the top-left. */
				dbg_vtty->vta_cursor.vtc_cellx = 0;
				dbg_vtty->vta_cursor.vtc_celly = 0;
			}
		}
		/* Check if we need to scroll. */
		if (dbg_vtty->vta_cursor.vtc_celly >= dbg_vtty->vta_scroll_yend) {
			dbg_vtty->vta_cursor.vtc_celly = dbg_vtty->_vta_scrl_ymax;
			dbgtty_scrollone();
		}
		break;

	case '\r':
		if (dbg_indent >= dbg_screen_width)
			dbg_indent = dbg_screen_width - 1;
		if (dbg_vtty->vta_flags & VIDTTYACCESS_F_EOL) {
			/* Go to the original line after a line-wrap. */
			dbg_vtty->vta_cursor.vtc_cellx = dbg_indent;
			--dbg_vtty->vta_cursor.vtc_celly;
			break;
		}
		if (dbg_tty.at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE) {
			/* Clear trailing spaces */
			(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty,
			                           dbg_vtty->vta_cursor.vtc_cellx +
			                           dbg_vtty->vta_cursor.vtc_celly *
			                           dbg_vtty->vta_scan,
			                           ' ',
			                           dbg_screen_width - dbg_vtty->vta_cursor.vtc_cellx);
		}
		dbg_vtty->vta_cursor.vtc_cellx = dbg_indent;
		break;

	case '\n':
		/* Ignore '\n' after an implicit line-wrap. */
		if (!(dbg_vtty->vta_flags & VIDTTYACCESS_F_EOL)) {
			if (dbg_tty.at_ttymode & ANSITTY_MODE_NEWLINE_CLRFREE) {
				/* Clear trailing spaces */
				(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty,
				                           dbg_vtty->vta_cursor.vtc_cellx +
				                           dbg_vtty->vta_cursor.vtc_celly *
				                           dbg_vtty->vta_scan,
				                           ' ',
				                           dbg_screen_width - dbg_vtty->vta_cursor.vtc_cellx);
			}
			++dbg_vtty->vta_cursor.vtc_celly;
		}
		if (dbg_vtty->vta_cursor.vtc_celly >= dbg_vtty->vta_scroll_yend) {
			dbg_vtty->vta_cursor.vtc_celly = dbg_vtty->_vta_scrl_ymax;
			dbgtty_scrollone();
		}
		if (dbg_indent >= dbg_screen_width)
			dbg_indent = dbg_screen_width - 1;
		dbg_vtty->vta_cursor.vtc_cellx = dbg_indent;
		break;

	default: {
		/* Check if we need to scroll. */
		if (dbg_vtty->vta_cursor.vtc_celly >= dbg_vtty->vta_scroll_yend) {
			dbg_vtty->vta_cursor.vtc_celly = dbg_vtty->_vta_scrl_ymax;
			dbgtty_scrollone();
		}

		/* Print the character to the screen. */
		(*dbg_vtty->vta_setcell)(dbg_vtty, &dbg_tty,
		                         dbg_vtty->vta_cursor.vtc_cellx +
		                         dbg_vtty->vta_cursor.vtc_celly *
		                         dbg_vtty->vta_scan,
		                         ch);

		/* Advance the cursor. */
		++dbg_vtty->vta_cursor.vtc_cellx;

		/* Check for line overflow. */
		if (dbg_vtty->vta_cursor.vtc_cellx >= dbg_screen_width) {
			if (dbg_indent >= dbg_screen_width)
				dbg_indent = dbg_screen_width - 1;
			dbg_vtty->vta_cursor.vtc_cellx = dbg_indent;
			++dbg_vtty->vta_cursor.vtc_celly;

			/* Set the EOL flag after an implicit line-feed */
			dbg_vtty->vta_flags |= VIDTTYACCESS_F_EOL;
maybe_hide_cursor_after_eol:
			if (dbg_vtty->vta_cursor.vtc_celly >= dbg_screen_height) {
				/* Hide the hardware cursor (if it was visible before) */
				if (!(dbg_tty.at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
				    (dbg_vtty->vta_flags & VIDTTYACCESS_F_ACTIVE))
					(*dbg_vtty->vta_hidecursor)(dbg_vtty);
				goto after_clear_eol_nocursor;
			}
			goto after_clear_eol;
		}
	}	break;

	}

	/* Clear the EOL flag. */
	dbg_vtty->vta_flags &= ~VIDTTYACCESS_F_EOL;
after_clear_eol:
	if (!(dbg_tty.at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
	    (dbg_vtty->vta_flags & VIDTTYACCESS_F_ACTIVE))
		(*dbg_vtty->vta_showcursor)(dbg_vtty); /* Update hardware cursor. */
after_clear_eol_nocursor:
	;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC dbgtty_setcursor)(struct ansitty *__restrict UNUSED(self),
                                        ansitty_coord_t x,
                                        ansitty_coord_t y,
                                        bool update_hw_cursor) {
	if (x < 0)
		x = 0;
	if (x >= dbg_screen_width)
		x = dbg_screen_width - 1;
	if (y < 0)
		y = 0;
	if (y >= dbg_screen_height)
		y = dbg_screen_height - 1;
	dbg_vtty->vta_cursor.vtc_cellx = (uintptr_half_t)x;
	dbg_vtty->vta_cursor.vtc_celly = (uintptr_half_t)y;

	/* Update on-screen cursor if necessary. */
	if ((dbg_vtty->vta_flags & VIDTTYACCESS_F_ACTIVE) &&
	    !(dbg_tty.at_ttymode & ANSITTY_MODE_HIDECURSOR) &&
	    update_hw_cursor)
		(*dbg_vtty->vta_showcursor)(dbg_vtty);
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC dbgtty_getcursor)(struct ansitty *__restrict UNUSED(self),
                                        ansitty_coord_t ppos[2]) {
	ppos[0] = dbg_vtty->vta_cursor.vtc_cellx;
	ppos[1] = dbg_vtty->vta_cursor.vtc_celly;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC dbgtty_getsize)(struct ansitty *__restrict UNUSED(self),
                                      ansitty_coord_t psize[2]) {
	psize[0] = dbg_screen_width;
	psize[1] = dbg_screen_height;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC dbgtty_copycell)(struct ansitty *__restrict UNUSED(self),
                                       ansitty_offset_t dst_offset, ansitty_coord_t count) {
	uintptr_t srcaddr, dstaddr, copyend, dispend;
	srcaddr = dbg_vtty->vta_cursor.vtc_celly;
	/* Yes: vta_resx (and not `vta_scan'); s.a. the documentation of `vta_copycell' */
	srcaddr *= dbg_screen_width;
	srcaddr += dbg_vtty->vta_cursor.vtc_cellx;
	dstaddr = srcaddr + dst_offset;

	/* Limit copy range at the start of destination */
	if ((intptr_t)dstaddr < 0) {
		size_t underflow;
		underflow = (size_t)0 - dstaddr;
		dstaddr   = 0;
		if (OVERFLOW_UADD(srcaddr, underflow, &srcaddr))
			goto done;
	}

	/* Limit copy range at the end of the destination */
	if (OVERFLOW_UADD(dstaddr, count, &copyend)) {
		count   = ((uintptr_t)-1) - dstaddr;
		copyend = ((uintptr_t)-1);
	}
	dispend = dbg_screen_height * dbg_screen_width;
	if (copyend > dispend) {
		size_t overflow = copyend - dbg_screen_height;
		if (OVERFLOW_USUB(count, overflow, &count))
			goto done;
	}

	/* Limit copy range at the end of the source */
	if unlikely(OVERFLOW_UADD(srcaddr, count, &copyend) || copyend > dispend) {
		size_t maxcount, overflow;
		maxcount = dispend - srcaddr;
		overflow = count - maxcount;

		/* Do the actual cell-copy. */
		/*assert(srcaddr <= dispend);*/
		/*assert(dstaddr <= dispend);*/
		/*assert((srcaddr + maxcount) <= dispend);*/
		/*assert((dstaddr + maxcount) <= dispend);*/
		(*dbg_vtty->vta_copycell)(dbg_vtty, dstaddr, srcaddr, maxcount);

		/* Fill `overflow' cells at `dstaddr + maxcount' with ' ' */
		dstaddr += maxcount;
		if (dbg_vtty->vta_scan > dbg_screen_width) {
			size_t delta = dbg_vtty->vta_scan - dbg_screen_width;
			dstaddr += (dstaddr / dbg_screen_width) * delta;
		}
		(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty, dstaddr, ' ', overflow);
	} else {
		/* Do the actual cell-copy. */
		/*assert(srcaddr <= dispend);*/
		/*assert(dstaddr <= dispend);*/
		/*assert((srcaddr + count) <= dispend);*/
		/*assert((dstaddr + count) <= dispend);*/
		(*dbg_vtty->vta_copycell)(dbg_vtty, dstaddr, srcaddr, count);
	}

done:
	;
}

PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC dbgtty_fillcell)(struct ansitty *__restrict UNUSED(self),
                                       char32_t ch, ansitty_coord_t count) {
	uintptr_t dstaddr, fillend, dispend;
	dstaddr = dbg_vtty->vta_cursor.vtc_cellx +
	          dbg_vtty->vta_cursor.vtc_celly *
	          dbg_screen_width;
	dispend = dbg_screen_height * dbg_screen_width;
	/* Limit `count' to what can be put on-screen. */
	if (OVERFLOW_UADD(dstaddr, count, &fillend) || fillend > dispend) {
		if unlikely(OVERFLOW_USUB(dispend, dstaddr, &count))
			goto done;
	}

	/* Adjust `count' for scanlines */
	if (dbg_vtty->vta_scan > dbg_screen_width) {
		size_t aligned_size;
		size_t delta = dbg_vtty->vta_scan - dbg_screen_width;
		dstaddr      = dbg_vtty->vta_cursor.vtc_cellx + dbg_vtty->vta_cursor.vtc_celly * dbg_vtty->vta_scan;
		aligned_size = dstaddr % dbg_vtty->vta_scan; /* # of characters before first line */
		aligned_size += count;                       /* Total number of characters from start of first line */
		aligned_size /= dbg_screen_width;            /* Number of line-feeds included in the fill. */
		count += aligned_size * delta;               /* Include delta induced by line-feeds. */
	}

	/* Do the fill. */
	(*dbg_vtty->vta_fillcells)(dbg_vtty, &dbg_tty, dstaddr, ch, count);
done:
	;
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
dbgtty_setttymode(struct ansitty *__restrict self) {
	if likely(dbg_vtty->vta_flags & VIDTTYACCESS_F_ACTIVE) {
		/* Update the state of the on-screen cursor. */
		if (self->at_ttymode & ANSITTY_MODE_HIDECURSOR) {
			(*dbg_vtty->vta_hidecursor)(dbg_vtty);
		} else if (dbg_vtty->vta_cursor.vtc_celly < dbg_screen_height) {
			(*dbg_vtty->vta_showcursor)(dbg_vtty);
		}
	}
}

PRIVATE NONNULL((1)) void LIBANSITTY_CC
dbgtty_scrollregion(struct ansitty *__restrict self) {
	ansitty_coord_t sl = self->at_scroll_sl;
	ansitty_coord_t el = self->at_scroll_el;
	if (sl < 0)
		sl = 0;
	if (el > dbg_screen_height)
		el = dbg_screen_height;
	if (sl > el)
		sl = el;
	dbg_vtty->vta_scroll_ystart = sl;
	dbg_vtty->vta_scroll_yend   = el;
	_vidttyaccess_update_scrl(dbg_vtty);
}


PRIVATE ATTR_DBGTEXT void
NOTHROW(LIBANSITTY_CC dbgtty_output)(struct ansitty *__restrict UNUSED(self),
                                     void const *data, size_t datalen) {
	while (datalen) {
		byte_t b;
		--datalen;
		b = ((byte_t *)data)[datalen];
		dbg_ungetc((char)b);
	}
}

PRIVATE ATTR_DBGRODATA struct ansitty_operators const dbgtty_operators = {
	.ato_putc         = &dbgtty_putc,
	.ato_setcursor    = &dbgtty_setcursor,
	.ato_getcursor    = &dbgtty_getcursor,
	.ato_getsize      = &dbgtty_getsize,
	.ato_copycell     = &dbgtty_copycell,
	.ato_fillcell     = &dbgtty_fillcell,
	.ato_setttymode   = &dbgtty_setttymode,
	.ato_scrollregion = &dbgtty_scrollregion,
	.ato_output       = &dbgtty_output,
};








/************************************************************************/
/* Initialization / Finalization                                        */
/************************************************************************/

/* Internal initialization (called when entering the debugger) */
INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_initialize_tty)(void) {
	/* Acquire a video terminal. */
	dbg_vdev = axref_ptr(&viddev_default);
	if (dbg_vdev && (!viddev_getops(dbg_vdev)->vdo_enterdbg ||
	                 !viddev_getops(dbg_vdev)->vdo_leavedbg))
		dbg_vdev = NULL;
	if (dbg_vdev) {
		dbg_vtty = (*viddev_getops(dbg_vdev)->vdo_enterdbg)(dbg_vdev);
	} else {
		dbg_vtty = dbg_fallback_acquiretty();
	}
	dbg_real_vtty = dbg_vtty;
}

/* Internal finalization (called when exiting the debugger) */
INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_finalize_tty)(void) {
	if unlikely(!dbg_vtty)
		return; /* Shouldn't happen... */
	dbg_endshowscreen(); /* Make sure we're not in show-screen mode. */
	if (dbg_vdev) {
		(*viddev_getops(dbg_vdev)->vdo_leavedbg)(dbg_vdev);
	} else {
		dbg_fallback_releasetty();
	}
	dbg_real_vtty = NULL;
	dbg_vdev      = NULL;
	dbg_vtty      = NULL;
}

/* Internal reset (called when resetting the debugger) */
INTERN ATTR_DBGTEXT void
NOTHROW(KCALL dbg_reset_tty)(void) {
	uintptr_half_t x, y;

	/* Make sure we're not in show-screen mode from before. */
	dbg_endshowscreen();
	ansitty_init(&dbg_tty, &dbgtty_operators);
	dbg_logecho_enabled  = true;
	dbg_tabsize          = DBG_TABSIZE_DEFAULT;
	dbg_indent           = 0;
	dbg_update_recursion = 0;

	/* Reset tty config. */
	dbg_vtty->vta_scroll_ystart   = 0;
	dbg_vtty->vta_scroll_yend     = dbg_vtty->vta_resy;
	dbg_vtty->vta_cursor.vtc_word = 0;
	_vidttyaccess_update_scrl(dbg_vtty);

	/* Load the tty. */
	dbgtty_init4tty(dbg_vtty);

	/* Clear display buffer. */
	for (y = 0; y < dbg_vtty->vta_resy; ++y) {
		for (x = 0; x < dbg_vtty->vta_resx; ++x) {
			uintptr_t addr = x + y * dbg_vtty->vta_scan;
			(*dbg_vtty->vta_setcell)(dbg_vtty, &dbg_tty, addr, ' ');
		}
	}
}






/************************************************************************/
/* Functions implemented in terms of others                             */
/************************************************************************/

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
NOTHROW(FCALL dbg_pprinter_putc)(dbg_pprinter_arg_t *__restrict printer,
                                 /*utf-8*/ char ch) {
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
			bzero(printer->p_utf8 + 1,
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


PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_putc)(/*utf-8*/ char ch) {
	ansitty_putc(&dbg_tty, ch);
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_putuni)(/*utf-32*/ char32_t ch) {
	ansitty_putuni(&dbg_tty, ch);
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

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fillscreen)(/*utf-32*/ char32_t ch) {
	dbg_fillbox(0, 0, dbg_screen_width, dbg_screen_height, ch);
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_hline)(int x, int y, unsigned int size_x, /*utf-32*/ char32_t ch) {
	dbg_fillbox(x, y, size_x, 1, ch);
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_vline)(int x, int y, unsigned int size_y, /*utf-32*/ char32_t ch) {
	dbg_fillbox(x, y, 1, size_y, ch);
}

PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fillrect)(int x, int y, unsigned int size_x,
                            unsigned int size_y, /*utf-32*/ char32_t ch) {
	dbg_hline(x, y, size_x, ch);
	if (size_y > 1)
		dbg_hline(x, y + size_y - 1, size_x, ch);
	if (size_y > 2) {
		dbg_vline(x, y + 1, size_y - 2, ch);
		if (size_x > 1)
			dbg_vline(x + size_x - 1, y + 1, size_y - 2, ch);
	}
}

PUBLIC ATTR_DBGTEXT ATTR_PURE WUNUSED bool
NOTHROW(FCALL dbg_getcur_visible)(void) {
	return !(dbg_tty.at_ttymode & ANSITTY_MODE_HIDECURSOR);
}

PUBLIC ATTR_DBGTEXT bool
NOTHROW(FCALL dbg_setcur_visible)(bool visible) {
	bool result;
	result = !(dbg_tty.at_ttymode & ANSITTY_MODE_HIDECURSOR);
	if (visible != result) {
		dbg_tty.at_ttymode &= ~ANSITTY_MODE_HIDECURSOR;
		if (!visible)
			dbg_tty.at_ttymode |= ANSITTY_MODE_HIDECURSOR;
		dbgtty_setttymode(&dbg_tty);
	}
	return result;
}


PUBLIC ATTR_DBGTEXT void
NOTHROW(FCALL dbg_fillrect2)(int x, int y, unsigned int size_x, unsigned int size_y,
                             /*utf-32*/ char32_t tl, /*utf-32*/ char32_t t, /*utf-32*/ char32_t tr,
                             /*utf-32*/ char32_t l,                         /*utf-32*/ char32_t r,
                             /*utf-32*/ char32_t bl, /*utf-32*/ char32_t b, /*utf-32*/ char32_t br) {
	if (!size_x || !size_y) {
		dbg_setscroll(0);
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


DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_SRC_DEBUGGER_OUTPUT_C */
