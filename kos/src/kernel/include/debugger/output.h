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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_OUTPUT_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_OUTPUT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/types.h>

#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__

/* I/O within the debugger. */
FUNDEF void NOTHROW(KCALL dbg_bell)(void);
FUNDEF void NOTHROW(KCALL dbg_putc)(/*utf-8*/ char ch);
FUNDEF void NOTHROW(KCALL dbg_putuni)(/*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(KCALL dbg_fillscreen)(/*utf-32*/ char32_t ch); /* Fill the entire screen with `ch' */
FUNDEF NONNULL((1)) size_t KCALL dbg_print(/*utf-8*/ char const *__restrict str);
FUNDEF NONNULL((1)) size_t VCALL dbg_printf(/*utf-8*/ char const *__restrict format, ...);
FUNDEF NONNULL((1)) size_t KCALL dbg_vprintf(/*utf-8*/ char const *__restrict format, __builtin_va_list args);
FUNDEF NONNULL((2)) ssize_t KCALL dbg_printer(void *ignored, /*utf-8*/ char const *__restrict data, size_t datalen);

/* Display a rectangle (frame) or box (filled) on-screen. */
FUNDEF void NOTHROW(KCALL dbg_fillbox)(int x, int y, unsigned int size_x,
                                       unsigned int size_y, /*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(KCALL dbg_fillrect)(int x, int y, unsigned int size_x,
                                        unsigned int size_y, /*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(KCALL dbg_fillrect2)(int x, int y, unsigned int size_x, unsigned int size_y,
                                         /*utf-32*/ char32_t tl, /*utf-32*/ char32_t t, /*utf-32*/ char32_t tr,
                                         /*utf-32*/ char32_t l,                         /*utf-32*/ char32_t r,
                                         /*utf-32*/ char32_t bl, /*utf-32*/ char32_t b, /*utf-32*/ char32_t br);
FUNDEF void NOTHROW(KCALL dbg_hline)(int x, int y, unsigned int size_x, /*utf-32*/ char32_t ch);
FUNDEF void NOTHROW(KCALL dbg_vline)(int x, int y, unsigned int size_y, /*utf-32*/ char32_t ch);

/* Fill a rectangle with single-stroke or double-stroke outline */
#define dbg_fillrect_singlestroke(x, y, size_x, size_y) \
	dbg_fillrect2(x, y, size_x, size_y,                 \
	              0x250C, 0x2500, 0x2510, 0x2502,       \
	              0x2502, 0x2514, 0x2500, 0x2518)
#define dbg_fillrect_doublestroke(x, y, size_x, size_y) \
	dbg_fillrect2(x, y, size_x, size_y,                 \
	              0x2554, 0x2550, 0x2557, 0x2551,       \
	              0x2551, 0x255A, 0x2550, 0x255D)

/* Print text to the given coords. */
FUNDEF void NOTHROW(KCALL dbg_pputuni)(int x, int y, /*utf-32*/ char32_t ch);
FUNDEF size_t KCALL dbg_pprint(int x, int y, /*utf-8*/ char const *__restrict str);
FUNDEF size_t VCALL dbg_pprintf(int x, int y, /*utf-8*/ char const *__restrict format, ...);
FUNDEF size_t KCALL dbg_vpprintf(int x, int y, /*utf-8*/ char const *__restrict format, __builtin_va_list args);
FUNDEF ssize_t KCALL dbg_pprinter(/*dbg_pprinter_arg_t*/ void *arg, /*utf-8*/ char const *__restrict data, size_t datalen);
typedef struct {
	int p_printx;  /* X-coord of the next character */
	int p_printy;  /* Y-coord of the next character */
	u8  p_utf8[8]; /* Pending UTF-8 characters */
} dbg_pprinter_arg_t;
#define DBG_PPRINTER_ARG_INIT(x, y) { x, y, { 0, 0, 0, 0, 0, 0, 0, 0  } }




/* Scroll the DBG output display to the given position.
 * Scroll positions increment upwards, meaning that `pos=0'
 * scrolls to the active display, while any other number will
 * display content that has been visible before then.
 * NOTE: When `pos' > `dbg_scroll_max(line|page)', it will
 *       be clamped to that value before being applied.
 * @param: cmd: The command to perform (One of `DBG_SCROLL_CMD_*')
 * @param: pos: The position to which to scroll.
 * @return: * : The position that has been set. */
FUNDEF unsigned int NOTHROW(KCALL dbg_scroll)(unsigned int cmd, unsigned int pos);
#define DBG_SCROLL_CMD_GET 0 /* Get scroll position. */
#define DBG_SCROLL_CMD_SET 1 /* Set scroll position. */
DATDEF unsigned int const dbg_scroll_maxline;  /* The max line to which scrolling it possible. */

/* Debug TTY dimensions. */
DATDEF unsigned int const dbg_screen_width;    /* Debug TTY width (in characters) */
DATDEF unsigned int const dbg_screen_height;   /* Debug TTY height (in characters) */
DATDEF unsigned int const dbg_screen_cellsize; /* Debug TTY cell size (in bytes) */

/* Alignment of TAB characters (default: `4') */
DATDEF unsigned int dbg_tabsize;
#define DBG_TABSIZE_DEFAULT      4 /* Default TAB size */

/* Cursor X-position assign after a line-feed */
DATDEF unsigned int dbg_indent;

DATDEF unsigned int dbg_newline_mode; /* Debugger new-line mode */
#define DBG_NEWLINE_MODE_NORMAL  0 /* Normal new-line mode */
#define DBG_NEWLINE_MODE_CLRFREE 1 /* Override all unused positions of the old line with space characters.
                                    * NOTE: This also affects `\r', which will erase unwritten spaces before
                                    *       jumping back to the start of the line.
                                    * HINT: This mode is useful for progress indicators, as well as well as
                                    *       self-updating menus. */
#define DBG_NEWLINE_MODE_NOWRAP  2 /* Don't automatically wrap to the next line when writing past the end
                                    * of the current line. */


/* Get/Set debug TTY screen data
 * NOTE: Reading Out-of-bound cells are read as the same value as a space-character
 *       cell when written using `dbg_putc(' ')' as the current cursor position.
 * NOTE: Writing Out-of-bound cells is a no-op.
 * NOTE: These functions will read/write the SCROLL-TOP screen data, and
 *      `dbg_setscreendata()' will apply `dbg_scroll(DBG_SCROLL_CMD_SET,0)'
 *       before actually copying cells.
 * @param: buf: A buffer capable of holding `size_x * size_y * dbg_screen_cellsize' bytes of data. */
FUNDEF NONNULL((5)) void KCALL dbg_getscreendata(int x, int y, unsigned int size_x, unsigned int size_y, void *__restrict buf);
FUNDEF NONNULL((5)) void KCALL dbg_setscreendata(int x, int y, unsigned int size_x, unsigned int size_y, void const *__restrict buf);


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

/* TTY show-screen support (display the contents of the monitor before the debugger was enabled) */
FUNDEF void NOTHROW(KCALL dbg_beginshowscreen)(void);
FUNDEF void NOTHROW(KCALL dbg_endshowscreen)(void);



/* Get/Set the current on-screen cursor position.
 * NOTE: Out-of-bounds coords are clamped to their valid ranges. */
FUNDEF u32 NOTHROW(KCALL dbg_setcur)(int x, int y);
FUNDEF WUNUSED ATTR_PURE u32 NOTHROW(KCALL dbg_getcur)(void);
#define DBG_GETCUR_X(val) ((unsigned int)((val)&0xffff))
#define DBG_GETCUR_Y(val) ((unsigned int)((val) >> 16))
#define DBG_MAKECUR(x, y) ((u32)(x) | ((u32)(y) << 16))
LOCAL WUNUSED ATTR_PURE unsigned int NOTHROW(KCALL dbg_getcur_x)(void) { return DBG_GETCUR_X(dbg_getcur()); }
LOCAL WUNUSED ATTR_PURE unsigned int NOTHROW(KCALL dbg_getcur_y)(void) { return DBG_GETCUR_Y(dbg_getcur()); }


/* TTY color codes. */
#define DBG_COLOR_BLACK   0x0 /* RGB(0x00, 0x00, 0x00) */
#define DBG_COLOR_MAROON  0x1 /* RGB(0xaa, 0x00, 0x00) */
#define DBG_COLOR_GREEN   0x2 /* RGB(0x00, 0xaa, 0x00) */
#define DBG_COLOR_OLIVE   0x3 /* RGB(0xaa, 0x55, 0x00) */
#define DBG_COLOR_NAVY    0x4 /* RGB(0x00, 0x00, 0xaa) */
#define DBG_COLOR_PURPLE  0x5 /* RGB(0xaa, 0x00, 0xaa) */
#define DBG_COLOR_TEAL    0x6 /* RGB(0x00, 0xaa, 0xaa) */
#define DBG_COLOR_SILVER  0x7 /* RGB(0xaa, 0xaa, 0xaa) */
#define DBG_COLOR_GREY    0x8 /* RGB(0x55, 0x55, 0x55) */
#define DBG_COLOR_RED     0x9 /* RGB(0xff, 0x55, 0x55) */
#define DBG_COLOR_LIME    0xa /* RGB(0x55, 0xff, 0x55) */
#define DBG_COLOR_YELLOW  0xb /* RGB(0xff, 0xff, 0x55) */
#define DBG_COLOR_BLUE    0xc /* RGB(0x55, 0x55, 0xff) */
#define DBG_COLOR_FUCHSIA 0xd /* RGB(0xff, 0x55, 0xff) */
#define DBG_COLOR_AQUA    0xe /* RGB(0x55, 0xff, 0xff) */
#define DBG_COLOR_WHITE   0xf /* RGB(0xff, 0xff, 0xff) */
#define DBG_COLOR_LIGHT_GRAY    DBG_COLOR_SILVER
#define DBG_COLOR_DARK_GRAY     DBG_COLOR_GREY

#define _DBG_PRIVATE_COLORFMT_FG_0x0 "30"  /* DBG_COLOR_BLACK  : RGB(0x00, 0x00, 0x00) */
#define _DBG_PRIVATE_COLORFMT_FG_0x1 "31"  /* DBG_COLOR_MAROON : RGB(0x00, 0x00, 0xaa) */
#define _DBG_PRIVATE_COLORFMT_FG_0x2 "32"  /* DBG_COLOR_GREEN  : RGB(0x00, 0xaa, 0x00) */
#define _DBG_PRIVATE_COLORFMT_FG_0x3 "33"  /* DBG_COLOR_OLIVE  : RGB(0x00, 0xaa, 0xaa) */
#define _DBG_PRIVATE_COLORFMT_FG_0x4 "34"  /* DBG_COLOR_NAVY   : RGB(0xaa, 0x00, 0x00) */
#define _DBG_PRIVATE_COLORFMT_FG_0x5 "35"  /* DBG_COLOR_PURPLE : RGB(0xaa, 0x00, 0xaa) */
#define _DBG_PRIVATE_COLORFMT_FG_0x6 "36"  /* DBG_COLOR_TEAL   : RGB(0xaa, 0x55, 0x00) */
#define _DBG_PRIVATE_COLORFMT_FG_0x7 "37"  /* DBG_COLOR_SILVER : RGB(0xaa, 0xaa, 0xaa) */
#define _DBG_PRIVATE_COLORFMT_FG_0x8 "90"  /* DBG_COLOR_GREY   : RGB(0x55, 0x55, 0x55) */
#define _DBG_PRIVATE_COLORFMT_FG_0x9 "91"  /* DBG_COLOR_RED    : RGB(0x55, 0x55, 0xff) */
#define _DBG_PRIVATE_COLORFMT_FG_0xa "92"  /* DBG_COLOR_LIME   : RGB(0x55, 0xff, 0x55) */
#define _DBG_PRIVATE_COLORFMT_FG_0xb "93"  /* DBG_COLOR_YELLOW : RGB(0x55, 0xff, 0xff) */
#define _DBG_PRIVATE_COLORFMT_FG_0xc "94"  /* DBG_COLOR_BLUE   : RGB(0xff, 0x55, 0x55) */
#define _DBG_PRIVATE_COLORFMT_FG_0xd "95"  /* DBG_COLOR_FUCHSIA: RGB(0xff, 0x55, 0xff) */
#define _DBG_PRIVATE_COLORFMT_FG_0xe "96"  /* DBG_COLOR_AQUA   : RGB(0xff, 0xff, 0x55) */
#define _DBG_PRIVATE_COLORFMT_FG_0xf "97"  /* DBG_COLOR_WHITE  : RGB(0xff, 0xff, 0xff) */
#define _DBG_PRIVATE_COLORFMT_BG_0x0 "40"  /* DBG_COLOR_BLACK  : RGB(0x00, 0x00, 0x00) */
#define _DBG_PRIVATE_COLORFMT_BG_0x1 "41"  /* DBG_COLOR_MAROON : RGB(0x00, 0x00, 0xaa) */
#define _DBG_PRIVATE_COLORFMT_BG_0x2 "42"  /* DBG_COLOR_GREEN  : RGB(0x00, 0xaa, 0x00) */
#define _DBG_PRIVATE_COLORFMT_BG_0x3 "43"  /* DBG_COLOR_OLIVE  : RGB(0x00, 0xaa, 0xaa) */
#define _DBG_PRIVATE_COLORFMT_BG_0x4 "44"  /* DBG_COLOR_NAVY   : RGB(0xaa, 0x00, 0x00) */
#define _DBG_PRIVATE_COLORFMT_BG_0x5 "45"  /* DBG_COLOR_PURPLE : RGB(0xaa, 0x00, 0xaa) */
#define _DBG_PRIVATE_COLORFMT_BG_0x6 "46"  /* DBG_COLOR_TEAL   : RGB(0xaa, 0x55, 0x00) */
#define _DBG_PRIVATE_COLORFMT_BG_0x7 "47"  /* DBG_COLOR_SILVER : RGB(0xaa, 0xaa, 0xaa) */
#define _DBG_PRIVATE_COLORFMT_BG_0x8 "100" /* DBG_COLOR_GREY   : RGB(0x55, 0x55, 0x55) */
#define _DBG_PRIVATE_COLORFMT_BG_0x9 "101" /* DBG_COLOR_RED    : RGB(0x55, 0x55, 0xff) */
#define _DBG_PRIVATE_COLORFMT_BG_0xa "102" /* DBG_COLOR_LIME   : RGB(0x55, 0xff, 0x55) */
#define _DBG_PRIVATE_COLORFMT_BG_0xb "103" /* DBG_COLOR_YELLOW : RGB(0x55, 0xff, 0xff) */
#define _DBG_PRIVATE_COLORFMT_BG_0xc "104" /* DBG_COLOR_BLUE   : RGB(0xff, 0x55, 0x55) */
#define _DBG_PRIVATE_COLORFMT_BG_0xd "105" /* DBG_COLOR_FUCHSIA: RGB(0xff, 0x55, 0xff) */
#define _DBG_PRIVATE_COLORFMT_BG_0xe "106" /* DBG_COLOR_AQUA   : RGB(0xff, 0xff, 0x55) */
#define _DBG_PRIVATE_COLORFMT_BG_0xf "107" /* DBG_COLOR_WHITE  : RGB(0xff, 0xff, 0xff) */


#define _DBG_PRIVATE_FMT_SETCOLOR(fg, bg) "\033[" _DBG_PRIVATE_COLORFMT_FG_##fg ";" _DBG_PRIVATE_COLORFMT_BG_##bg "m"
#define _DBG_PRIVATE_FMT_SETFGCOLOR(fg)   "\033[" _DBG_PRIVATE_COLORFMT_FG_##fg "m"
#define _DBG_PRIVATE_FMT_SETBGCOLOR(bg)   "\033[" _DBG_PRIVATE_COLORFMT_BG_##bg "m"

/* Color escape codes for debug TTY output. */
#define DF_SETCOLOR(fg, bg)   _DBG_PRIVATE_FMT_SETCOLOR(fg, bg)
#define DF_SETFGCOLOR(fg)     _DBG_PRIVATE_FMT_SETFGCOLOR(fg)
#define DF_SETBGCOLOR(bg)     _DBG_PRIVATE_FMT_SETBGCOLOR(bg)
#define DF_DEFFGCOLOR         "\033[39m"    /* Reset foreground color */
#define DF_DEFBGCOLOR         "\033[49m"    /* Reset background color */
#define DF_DEFCOLOR           "\033[39;49m" /* Reset colors */
#define DF_RESETATTR          "\033[m"      /* Reset all graphics attributes */
#define DF_SETMAROON          DF_SETFGCOLOR(DBG_COLOR_MAROON)
#define DF_SETWHITE           DF_SETFGCOLOR(DBG_COLOR_WHITE)
#define DF_SETBLUE            DF_SETFGCOLOR(DBG_COLOR_BLUE)
#define DF_COLOR(fg, bg, text) DF_SETCOLOR(fg, bg) text DF_RESETATTR
#define DF_FGCOLOR(fg, text)   DF_SETFGCOLOR(fg) text DF_RESETATTR
#define DF_BGCOLOR(bg, text)   DF_SETBGCOLOR(bg) text DF_RESETATTR
#define DF_WHITE(text)         DF_SETWHITE text DF_RESETATTR
#define DF_BLUE(text)          DF_SETBLUE text DF_RESETATTR


#define DBG_COLOR_ATTR(fg, bg) ((dbg_attr_t)(fg)<<8|(dbg_attr_t)(bg)<<12)
#define DBG_COLOR_FG(attr)     ((u8)(((attr) >> 8)&0xf))
#define DBG_COLOR_BG(attr)     ((u8)(((attr) >> 12)&0xf))
typedef u16 dbg_attr_t;

/* Get/Set TTY text attributes. */
DATDEF dbg_attr_t dbg_attr;
DATDEF dbg_attr_t dbg_default_attr; /* Attributes restored by `DF_RESETATTR' */

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
