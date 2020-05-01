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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_OUTPUT_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_OUTPUT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/types.h>

#include <stdbool.h>

#include <libansitty/ansitty.h>
#include <libansitty/ctl.h>
#include <libc/string.h>

DECL_BEGIN

#ifdef __CC__

/* I/O within the debugger. */
FUNDEF void NOTHROW(FCALL dbg_bell)(void);
FUNDEF void NOTHROW(FCALL dbg_putc)(/*utf-8*/ char ch);
FUNDEF void NOTHROW(FCALL dbg_putuni)(/*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(FCALL dbg_fillscreen)(/*utf-32*/ char32_t ch); /* Fill the entire screen with `ch' */
FUNDEF NONNULL((1)) size_t FCALL dbg_print(/*utf-8*/ char const *__restrict str);
FUNDEF NONNULL((1)) size_t VCALL dbg_printf(/*utf-8*/ char const *__restrict format, ...);
FUNDEF NONNULL((1)) size_t FCALL dbg_vprintf(/*utf-8*/ char const *__restrict format, __builtin_va_list args);
FUNDEF NONNULL((2)) ssize_t KCALL dbg_printer(void *ignored, /*utf-8*/ char const *__restrict data, size_t datalen);

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
FUNDEF void NOTHROW(FCALL dbg_pputuni)(int x, int y, /*utf-32*/ char32_t ch);
FUNDEF size_t FCALL dbg_pprint(int x, int y, /*utf-8*/ char const *__restrict str);
FUNDEF size_t VCALL dbg_pprintf(int x, int y, /*utf-8*/ char const *__restrict format, ...);
FUNDEF size_t FCALL dbg_vpprintf(int x, int y, /*utf-8*/ char const *__restrict format, __builtin_va_list args);
FUNDEF ssize_t KCALL dbg_pprinter(/*dbg_pprinter_arg_t*/ void *arg, /*utf-8*/ char const *__restrict data, size_t datalen);

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




/* Get/set the scroll position the DBG output display.
 * Scroll positions increment upwards, meaning that `pos=0'
 * scrolls to the active display, while any other number will
 * display content that has been visible before then.
 * NOTE: When `pos' > `dbg_scroll_maxline', it will
 *       be clamped to that value before being applied.
 * @param: pos: The position to which to scroll.
 * @return: * : The position that has been set. */
FUNDEF unsigned int NOTHROW(FCALL dbg_getscroll)(void);
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

/* Cursor X-position assign after a line-feed */
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
 * NOTE: Reading Out-of-bound cells are read as the same value as a space-character
 *       cell when written using `dbg_putc(' ')' as the current cursor position.
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
 * but instead draw to a separate buffer, thus preventing flickering in the
 * case of whole screen redraw operations.
 * NOTE: Also affects updates made to the cursor position
 * @param: force: When true, force updates to stop. */
FUNDEF void NOTHROW(FCALL dbg_beginupdate)(void);
FUNDEF void NOTHROW(FCALL dbg_endupdate)(bool force DFL(false));

/* TTY show-screen support (display the contents of the monitor before the debugger was enabled)
 * WARNING: `dbg_beginshowscreen()' also implies the behavior of `dbg_endupdate(true)'
 * NOTE: This functionality of these functions is also available through the `screen' command */
FUNDEF void NOTHROW(FCALL dbg_beginshowscreen)(void);
FUNDEF void NOTHROW(FCALL dbg_endshowscreen)(void);



/* Get/Set the current on-screen cursor position.
 * NOTE: Out-of-bounds coords are clamped to their valid ranges. */
FUNDEF u32 NOTHROW(FCALL dbg_setcur)(int x, int y);
FUNDEF WUNUSED ATTR_PURE u32 NOTHROW(FCALL dbg_getcur)(void);
#define DBG_GETCUR_X(val) ((unsigned int)((val)&0xffff))
#define DBG_GETCUR_Y(val) ((unsigned int)((val) >> 16))
#define DBG_MAKECUR(x, y) ((u32)(x) | ((u32)(y) << 16))
LOCAL WUNUSED ATTR_PURE unsigned int NOTHROW(FCALL dbg_getcur_x)(void) { return DBG_GETCUR_X(dbg_getcur()); }
LOCAL WUNUSED ATTR_PURE unsigned int NOTHROW(FCALL dbg_getcur_y)(void) { return DBG_GETCUR_Y(dbg_getcur()); }
LOCAL u32 NOTHROW(FCALL dbg_setcur_x)(int x) { return dbg_setcur(x, dbg_getcur_y()); }
LOCAL u32 NOTHROW(FCALL dbg_setcur_y)(int y) { return dbg_setcur(dbg_getcur_x(), y); }


/* TTY color codes. */
/* TODO: Get rid of this stuff and use the control codes from <libansitty/ctl.h> */
#define DBG_COLOR_BLACK         ANSITTY_CL_BLACK   /* RGB(0x00, 0x00, 0x00) */
#define DBG_COLOR_MAROON        ANSITTY_CL_MAROON  /* RGB(0xaa, 0x00, 0x00) */
#define DBG_COLOR_GREEN         ANSITTY_CL_GREEN   /* RGB(0x00, 0xaa, 0x00) */
#define DBG_COLOR_OLIVE         ANSITTY_CL_OLIVE   /* RGB(0xaa, 0x55, 0x00) */
#define DBG_COLOR_NAVY          ANSITTY_CL_NAVY    /* RGB(0x00, 0x00, 0xaa) */
#define DBG_COLOR_PURPLE        ANSITTY_CL_PURPLE  /* RGB(0xaa, 0x00, 0xaa) */
#define DBG_COLOR_TEAL          ANSITTY_CL_TEAL    /* RGB(0x00, 0xaa, 0xaa) */
#define DBG_COLOR_SILVER        ANSITTY_CL_SILVER  /* RGB(0xaa, 0xaa, 0xaa) */
#define DBG_COLOR_GREY          ANSITTY_CL_GREY    /* RGB(0x55, 0x55, 0x55) */
#define DBG_COLOR_RED           ANSITTY_CL_RED     /* RGB(0xff, 0x55, 0x55) */
#define DBG_COLOR_LIME          ANSITTY_CL_LIME    /* RGB(0x55, 0xff, 0x55) */
#define DBG_COLOR_YELLOW        ANSITTY_CL_YELLOW  /* RGB(0xff, 0xff, 0x55) */
#define DBG_COLOR_BLUE          ANSITTY_CL_BLUE    /* RGB(0x55, 0x55, 0xff) */
#define DBG_COLOR_FUCHSIA       ANSITTY_CL_FUCHSIA /* RGB(0xff, 0x55, 0xff) */
#define DBG_COLOR_AQUA          ANSITTY_CL_AQUA    /* RGB(0x55, 0xff, 0xff) */
#define DBG_COLOR_WHITE         ANSITTY_CL_WHITE   /* RGB(0xff, 0xff, 0xff) */
#define DBG_COLOR_LIGHT_GRAY    ANSITTY_CL_LIGHT_GRAY
#define DBG_COLOR_DARK_GRAY     ANSITTY_CL_DARK_GRAY
#define DBG_COLOR_MAGENTA       ANSITTY_CL_MAGENTA
#define DBG_COLOR_CYAN          ANSITTY_CL_CYAN
#define DBG_COLOR_LIGHT_GREEN   ANSITTY_CL_LIGHT_GREEN
#define DBG_COLOR_BRIGHT_GREEN  ANSITTY_CL_BRIGHT_GREEN
#define DBG_COLOR_DARK_BLUE     ANSITTY_CL_DARK_BLUE

/* Color escape codes for debug TTY output. */
#define DF_SETCOLOR(fg, bg)    AC_COLOR(fg, bg)
#define DF_SETFGCOLOR(fg)      AC_FG(fg)
#define DF_SETBGCOLOR(bg)      AC_BG(bg)
#define DF_DEFFGCOLOR          AC_FGDEF    /* Reset foreground color */
#define DF_DEFBGCOLOR          AC_BGDEF    /* Reset background color */
#define DF_DEFCOLOR            AC_DEFCOLOR /* Reset colors */
#define DF_RESETATTR           AC_DEFATTR  /* Reset all graphics attributes */
#define DF_SETMAROON           DF_SETFGCOLOR(DBG_COLOR_MAROON)
#define DF_SETWHITE            DF_SETFGCOLOR(DBG_COLOR_WHITE)
#define DF_SETBLUE             DF_SETFGCOLOR(DBG_COLOR_BLUE)
#define DF_COLOR(fg, bg, text) DF_SETCOLOR(fg, bg) text DF_RESETATTR
#define DF_FGCOLOR(fg, text)   DF_SETFGCOLOR(fg) text DF_RESETATTR
#define DF_BGCOLOR(bg, text)   DF_SETBGCOLOR(bg) text DF_RESETATTR
#define DF_WHITE(text)         DF_SETWHITE text DF_RESETATTR
#define DF_BLUE(text)          DF_SETBLUE text DF_RESETATTR


#define DBG_COLOR_ATTR(fg, bg) ((dbg_attr_t)(fg) << 8 | (dbg_attr_t)(bg) << 12)
#define DBG_COLOR_FG(attr)     ((u8)(((attr) >> 8) & 0xf))
#define DBG_COLOR_BG(attr)     ((u8)(((attr) >> 12) & 0xf))
typedef u16 dbg_attr_t;

/* Get/Set TTY text attributes. */
DATDEF dbg_attr_t dbg_attr;         /* TODO: Get rid of me (use dbg_tty.at_color instead) */
DATDEF dbg_attr_t dbg_default_attr; /* TODO: Get rid of me (use dbg_tty.at_defcolor instead) */ /* Attributes restored by `DF_RESETATTR' */

/* Get/Set TTY colors. */
LOCAL void NOTHROW(KCALL dbg_setcolor)(u8 fg, u8 bg) { dbg_attr = DBG_COLOR_ATTR(fg, bg); }
LOCAL u8 NOTHROW(KCALL dbg_getfgcolor)(void) { return DBG_COLOR_FG(dbg_attr); }
LOCAL u8 NOTHROW(KCALL dbg_getbgcolor)(void) { return DBG_COLOR_BG(dbg_attr); }
LOCAL void NOTHROW(KCALL dbg_setfgcolor)(u8 fg) { dbg_attr = DBG_COLOR_ATTR(fg, dbg_getbgcolor()); }
LOCAL void NOTHROW(KCALL dbg_setbgcolor)(u8 bg) { dbg_attr = DBG_COLOR_ATTR(dbg_getfgcolor(), bg); }


#endif /* __CC__ */

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_OUTPUT_H */
