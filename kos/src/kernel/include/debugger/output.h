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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_OUTPUT_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_OUTPUT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/types.h>

#include <hybrid/pp/__va_nargs.h>

#include <bits/crt/format-printer.h>

#include <stdbool.h>

#include <libansitty/ansitty.h>
#include <libansitty/ctl.h>
#include <libc/string.h>

DECL_BEGIN

#ifdef __CC__

/* The logecho-enabled state for debugger output.
 * When enabled (default), debugger output is echoed via some
 * architecture-specific mechanism onto  an external  logging
 * sink which then allows external programs to inspect/record
 * debugger output. */
DATDEF bool dbg_logecho_enabled;
#define dbg_logecho_push() \
	do {                   \
		bool _dle_old = dbg_logecho_enabled
#define dbg_logecho_pushoff() \
		dbg_logecho_push();   \
		dbg_logecho_enabled = false
#define dbg_logecho_pushon() \
		dbg_logecho_push();  \
		dbg_logecho_enabled = true
#define dbg_logecho_break() \
		(dbg_logecho_enabled = _dle_old)
#define dbg_logecho_pop() \
		dbg_logecho_enabled = _dle_old; \
	}	__WHILE0

/* format-printer compatible function to manually write text
 * to the external debugger logecho sink.
 * NOTE: This function isn't affected by `dbg_logecho_enabled' */
FUNDEF NONNULL((2)) ssize_t __FORMATPRINTER_CC dbg_logecho_printer(void *ignored, /*utf-8*/ char const *__restrict data, size_t datalen);
/* Helper wrappers for `dbg_logecho_printer()' */
FUNDEF NOBLOCK NONNULL((1)) size_t FCALL dbg_logecho(/*utf-8*/ char const *__restrict text);
FUNDEF NOBLOCK NONNULL((1)) size_t VCALL dbg_logechof(/*utf-8*/ char const *__restrict format, ...);
FUNDEF NOBLOCK NONNULL((1)) size_t FCALL dbg_vlogechof(/*utf-8*/ char const *__restrict format, __builtin_va_list args);


/* Basic output functions within the debugger. */
FUNDEF void NOTHROW(FCALL dbg_bell)(void);
FUNDEF void NOTHROW(FCALL dbg_putc)(/*utf-8*/ char ch);
FUNDEF void NOTHROW(FCALL dbg_putuni)(/*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(FCALL dbg_fillscreen)(/*utf-32*/ char32_t ch); /* Fill the entire screen with `ch' */
FUNDEF NONNULL((1)) size_t FCALL dbg_print(/*utf-8*/ char const *__restrict str);
FUNDEF NONNULL((1)) size_t VCALL dbg_printf(/*utf-8*/ char const *__restrict format, ...);
FUNDEF NONNULL((1)) size_t FCALL dbg_vprintf(/*utf-8*/ char const *__restrict format, __builtin_va_list args);
FUNDEF NONNULL((2)) ssize_t __FORMATPRINTER_CC dbg_printer(void *ignored, /*utf-8*/ char const *__restrict data, size_t datalen);

/* Display a rectangle (frame) or box (filled) on-screen. */
FUNDEF void NOTHROW(FCALL dbg_fillbox)(int x, int y, unsigned int size_x,
                                       unsigned int size_y, /*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(FCALL dbg_fillrect)(int x, int y, unsigned int size_x,
                                        unsigned int size_y, /*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(FCALL dbg_fillrect2)(int x, int y, unsigned int size_x, unsigned int size_y,
                                         /*utf-32*/ char32_t tl, /*utf-32*/ char32_t t, /*utf-32*/ char32_t tr,
                                         /*utf-32*/ char32_t l,                         /*utf-32*/ char32_t r,
                                         /*utf-32*/ char32_t bl, /*utf-32*/ char32_t b, /*utf-32*/ char32_t br);
FUNDEF void NOTHROW(FCALL dbg_hline)(int x, int y, unsigned int size_x, /*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(FCALL dbg_vline)(int x, int y, unsigned int size_y, /*utf-32*/ char32_t ch);

/* Fill a rectangle with single-stroke or double-stroke outline */
#define dbg_fillrect_singlestroke(x, y, size_x, size_y) \
	dbg_fillrect2(x, y, size_x, size_y,                 \
	              0x250C, 0x2500, 0x2510, 0x2502,       \
	              0x2502, 0x2514, 0x2500, 0x2518)
#define dbg_fillrect_doublestroke(x, y, size_x, size_y) \
	dbg_fillrect2(x, y, size_x, size_y,                 \
	              0x2554, 0x2550, 0x2557, 0x2551,       \
	              0x2551, 0x255A, 0x2550, 0x255D)

/* Print text to the given coords. (invalid coords are clamped) */
typedef struct {
	int p_printx;  /* X-coord of the next character */
	int p_printy;  /* Y-coord of the next character */
	u8  p_utf8[8]; /* Pending UTF-8 characters */
} dbg_pprinter_arg_t;

#define DBG_PPRINTER_ARG_INIT(x, y) \
	{ x, y, { 0, 0, 0, 0, 0, 0, 0, 0  } }
#define dbg_pprinter_arg_init(self, x, y) \
	((self)->p_printx = (x),              \
	 (self)->p_printy = (y),              \
	 __libc_memset((self)->p_utf8, 0, 8))

FUNDEF void NOTHROW(FCALL dbg_pputuni)(int x, int y, /*utf-32*/ char32_t ch);
FUNDEF size_t FCALL dbg_pprint(int x, int y, /*utf-8*/ char const *__restrict str);
FUNDEF size_t VCALL dbg_pprintf(int x, int y, /*utf-8*/ char const *__restrict format, ...);
FUNDEF size_t FCALL dbg_vpprintf(int x, int y, /*utf-8*/ char const *__restrict format, __builtin_va_list args);
FUNDEF ssize_t KCALL dbg_pprinter(/*dbg_pprinter_arg_t*/ void *arg, /*utf-8*/ char const *__restrict data, size_t datalen);
FUNDEF NONNULL((1)) void NOTHROW(FCALL dbg_pprinter_putc)(dbg_pprinter_arg_t *__restrict printer, /*utf-8*/ char ch);
FUNDEF NONNULL((1)) void NOTHROW(FCALL dbg_pprinter_putuni)(dbg_pprinter_arg_t *__restrict printer, /*utf-32*/ char32_t ch);



/* Get/set  the  scroll  position  the  DBG  output  display.
 * Scroll positions increment  upwards, meaning that  `pos=0'
 * scrolls to the active display, while any other number will
 * display content that has been visible before then.
 * NOTE: When `pos'  >  `dbg_scroll_maxline',  it  will
 *       be clamped to that value before being applied.
 * @param: pos: The position to which to scroll.
 * @return: * : The position that has been set. */
FUNDEF ATTR_PURE WUNUSED unsigned int NOTHROW(FCALL dbg_getscroll)(void);
FUNDEF unsigned int NOTHROW(FCALL dbg_setscroll)(unsigned int pos);

/* The max line to which scrolling it possible. */
DATDEF unsigned int const dbg_scroll_maxline;

/* Debug TTY dimensions. */
DATDEF unsigned int const dbg_screen_width;    /* Debug TTY width (in characters) */
DATDEF unsigned int const dbg_screen_height;   /* Debug TTY height (in characters) */
DATDEF unsigned int const dbg_screen_cellsize; /* Debug TTY cell size (in bytes) */

/* Alignment of TAB characters (default: `DBG_TABSIZE_DEFAULT') */
DATDEF unsigned int dbg_tabsize;
#define DBG_TABSIZE_DEFAULT 4 /* Default TAB size */

/* Cursor X-position assigned after a line-feed */
DATDEF unsigned int dbg_indent;

/* The ANSI TTY used for printing screen-output within the builtin debugger */
DATDEF struct ansitty dbg_tty;

/* Override all unused positions of the old line with space characters.
 * NOTE: This also affects `\r', which will erase unwritten spaces before
 *       jumping back to the start of the line.
 * HINT: This mode is useful for progress indicators, as well as well as
 *       self-updating menus. */
#define dbg_newline_newline_clrfree_enable()  (void)(dbg_tty.at_ttymode |= ANSITTY_MODE_NEWLINE_CLRFREE)
#define dbg_newline_newline_clrfree_disable() (void)(dbg_tty.at_ttymode &= ~ANSITTY_MODE_NEWLINE_CLRFREE)

/* Don't automatically wrap to the next line when writing past the end of the current line. */
#define dbg_newline_nowrap_enable()  (void)(dbg_tty.at_ttymode |= ANSITTY_MODE_NOLINEWRAP)  /* dbg_print(DBGSTR("\033[?7l")) */
#define dbg_newline_nowrap_disable() (void)(dbg_tty.at_ttymode &= ~ANSITTY_MODE_NOLINEWRAP) /* dbg_print(DBGSTR("\033[?7h")) */


/* Get/Set debug TTY screen data
 * NOTE: Out-of-bound cells  are read  as the  same value  as a  space-character
 *       cell when written using `dbg_putc(' ')' at the current cursor position.
 * NOTE: Writing Out-of-bound cells is a no-op.
 * NOTE: These functions will read/write the SCROLL-TOP screen data, and
 *      `dbg_setscreendata()' will apply `dbg_setscroll(0)'
 *       before actually copying cells.
 * @param: buf: A buffer capable of holding `size_x * size_y * dbg_screen_cellsize' bytes of data. */
FUNDEF NONNULL((5)) void FCALL dbg_getscreendata(int x, int y, unsigned int size_x, unsigned int size_y, void *__restrict buf);
FUNDEF NONNULL((5)) void FCALL dbg_setscreendata(int x, int y, unsigned int size_x, unsigned int size_y, void const *__restrict buf);


/* Get/Set if the current cursor position should be visible.
 * @return: * : The cursor-was-visible state prior to the call being made. */
FUNDEF ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_getcur_visible)(void);
FUNDEF bool NOTHROW(FCALL dbg_setcur_visible)(bool visible);

/* Hints towards the screen driver to temporarily stop drawing to the screen,
 * but instead draw to a separate  buffer, thus preventing flickering in  the
 * case of whole screen redraw operations.
 * NOTE: Also affects updates made to the cursor position
 * @param: force: When true, force a switch back to the screen-buffer. */
FUNDEF void NOTHROW(FCALL dbg_beginupdate)(void);
FUNDEF void NOTHROW(FCALL dbg_endupdate)(bool force DFL(false));

/* TTY show-screen support (display the contents of the monitor before the debugger was enabled)
 * WARNING:  `dbg_beginshowscreen()'  also   implies  the   behavior  of   `dbg_endupdate(true)'
 * NOTE: This functionality of  these functions is also  available through the `screen'  command */
FUNDEF void NOTHROW(FCALL dbg_beginshowscreen)(void);
FUNDEF void NOTHROW(FCALL dbg_endshowscreen)(void);

/* Get/Set the current on-screen cursor position.
 * NOTE: Out-of-bounds coords are clamped to their valid ranges. */
FUNDEF u32 NOTHROW(FCALL dbg_setcur)(int x, int y);
FUNDEF ATTR_PURE WUNUSED u32 NOTHROW(FCALL dbg_getcur)(void);
#define DBG_GETCUR_X(val) ((unsigned int)((val)&0xffff))
#define DBG_GETCUR_Y(val) ((unsigned int)((val) >> 16))
#define DBG_MAKECUR(x, y) ((u32)(x) | ((u32)(y) << 16))
#define dbg_getcur_x()    DBG_GETCUR_X(dbg_getcur())
#define dbg_getcur_y()    DBG_GETCUR_Y(dbg_getcur())
#define dbg_setcur_x(x)   dbg_setcur(x, dbg_getcur_y())
#define dbg_setcur_y(y)   dbg_setcur(dbg_getcur_x(), y)

/* Get/Set TTY colors. */
typedef u8 dbg_color_t;
#define dbg_getcolor()         (u8)dbg_tty.at_color
#define _dbg_setcolor1(v)      (void)(dbg_tty.at_color = (v))
#define _dbg_setcolor2(fg, bg) (void)(dbg_tty.at_color = ANSITTY_PALETTE_INDEX(fg, bg))
#define dbg_setcolor(...)      __HYBRID_PP_VA_OVERLOAD(_dbg_setcolor, (__VA_ARGS__))(__VA_ARGS__)
#define dbg_getfgcolor()       ANSITTY_PALETTE_INDEX_FG(dbg_tty.at_color)
#define dbg_getbgcolor()       ANSITTY_PALETTE_INDEX_BG(dbg_tty.at_color)
#define dbg_setfgcolor(fg)     (void)(dbg_tty.at_color = ANSITTY_PALETTE_INDEX(fg, dbg_getbgcolor()))
#define dbg_setbgcolor(bg)     (void)(dbg_tty.at_color = ANSITTY_PALETTE_INDEX(dbg_getfgcolor(), bg))

#define dbg_getdefaultcolor()         (u8)dbg_tty.at_defcolor
#define _dbg_setdefaultcolor1(v)      (void)(dbg_tty.at_defcolor = (v))
#define _dbg_setdefaultcolor2(fg, bg) (void)(dbg_tty.at_defcolor = ANSITTY_PALETTE_INDEX(fg, bg))
#define dbg_setdefaultcolor(...)      __HYBRID_PP_VA_OVERLOAD(_dbg_setdefaultcolor, (__VA_ARGS__))(__VA_ARGS__)
#define dbg_getdefaultfgcolor()       ANSITTY_PALETTE_INDEX_FG(dbg_tty.at_defcolor)
#define dbg_getdefaultbgcolor()       ANSITTY_PALETTE_INDEX_BG(dbg_tty.at_defcolor)
#define dbg_setdefaultfgcolor(fg)     (void)(dbg_tty.at_defcolor = ANSITTY_PALETTE_INDEX(fg, dbg_getbgcolor()))
#define dbg_setdefaultbgcolor(bg)     (void)(dbg_tty.at_defcolor = ANSITTY_PALETTE_INDEX(dbg_getfgcolor(), bg))

#define dbg_savecolor()         \
	do {                        \
		dbg_color_t _old_color; \
		_old_color = dbg_getcolor()
#define dbg_loadcolor()           \
		dbg_setcolor(_old_color); \
	}	__WHILE0

#endif /* __CC__ */

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_OUTPUT_H */
