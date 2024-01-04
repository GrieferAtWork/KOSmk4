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
#ifndef _LIBANSITTY_CTL_H
#define _LIBANSITTY_CTL_H 1

#include "api.h"

/* ANSITTY color codes */
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

/* Color name aliases */
#ifndef ANSITTY_CL_LIGHT_GRAY
#define ANSITTY_CL_LIGHT_GRAY    ANSITTY_CL_SILVER
#define ANSITTY_CL_DARK_GRAY     ANSITTY_CL_GREY
#define ANSITTY_CL_MAGENTA       ANSITTY_CL_PURPLE
#define ANSITTY_CL_CYAN          ANSITTY_CL_TEAL
#define ANSITTY_CL_LIGHT_GREEN   ANSITTY_CL_LIME
#define ANSITTY_CL_BRIGHT_GREEN  ANSITTY_CL_LIME
#define ANSITTY_CL_DARK_BLUE     ANSITTY_CL_NAVY
#endif /* !ANSITTY_CL_LIGHT_GRAY */


/* Helper  macros  for  constructors  ANSITTY  control  sequences
 * All of these strings are pre-fixed by `AC_*' (AnsiControl_xxx)
 * Example:
 * >> printf("a" AC_CUF("%d") "b\n", 7);
 * >> fflush(stdout);
 * Output:   "a       b\n"
 */
/**/

/* Escape prefix */
#define _AC_ESC "\033"

/* <CANCEL> (aborts in-progress escape sequence) */
#define AC_CAN "\030"

/* SET_CURSOR(x: 0, y: GET_CURSOR_Y()); */
#define AC_CR "\r"

/* SET_CURSOR(x: 0, y: GET_CURSOR_Y() + 1); // SCROLL_UP(lines: 1); if necessary */
#define AC_LF "\n"

/* BELL(); */
#define AC_BEL "\07"

/* SET_CURSOR(x: CEIL_ALIGN(GET_CURSOR_X(), <TABSIZE>), y: GET_CURSOR_Y()); */
#define AC_TAB "\t"

/* Application Keypad (DECKPAM). */
#define AC_DECKPAM _AC_ESC "="

/* Normal Keypad (DECKPNM) */
#define AC_DECKPNM _AC_ESC ">"

/* SCROLL_DOWN(lines: 1); */
#define AC_RI _AC_ESC "M"

/* <saved_cursor_pos> = GET_CURSOR(); */
#define AC_SAVECURSOR _AC_ESC "7"

/* SET_CURSOR(<saved_cursor_pos>); */
#define AC_LOADCURSOR _AC_ESC "8"

/* String Terminator */
#define AC_ST _AC_ESC "\\"

/* Full reset */
#define AC_RIS _AC_ESC "c"



/* Enable box-drawing mode (s.a. AC_GR_*) */
#define AC_SETGR _AC_ESC "(0"

#define    AC_GR_SPACE         "_" /*   U+0020 (Blank / Space) */
#define    AC_GR_DIAMOND       "`" /* ⋄ U+22c4 (Diamond) */
#define    AC_GR_CHECKERBOARD  "a" /* ▓ U+2593 (Checkerboard) */
#define    AC_GR_HTAB          "b" /*   U+0009 (Horizontal tab) */
#define    AC_GR_FF            "c" /*   U+000c (Form Feed) */
#define    AC_GR_CR            "d" /*   U+000d (Carriage return) */
#define    AC_GR_LF            "e" /*   U+000a (Line feed) */
#define    AC_GR_DEGREE        "f" /* ° U+00b0 (° Degree symbol) */
#define    AC_GR_PLUSMINUS     "g" /* ± U+00b1 (± Plus/minus) */
#define   _AC_GR_NL            "h" /*   U+000a (New line) */
#define    AC_GR_VT            "i" /*   U+000b (Vertical tab) */
#define    AC_GR_CORNER_DR     "j" /* ┘ U+2518 (Down-right corner) */
#define    AC_GR_CORNER_UR     "k" /* ┐ U+2510 (Upper-right corner) */
#define    AC_GR_CORNER_UL     "l" /* ┌ U+250c (Upper-left corne)r*/
#define    AC_GR_CORNER_DL     "m" /* └ U+2514 (Down-left corner) */
#define    AC_GR_CROSS         "n" /* ┼ U+253c (Crossing lines) */
#define   _AC_GR_HLINE1        "o" /* ─ U+2500 (Horizontal line - Scan 1) */
#define   _AC_GR_HLINE3        "p" /* ─ U+2500 (Horizontal line - Scan 3) */
#define   _AC_GR_HLINE5        "q" /* ─ U+2500 (Horizontal line - Scan 5) */
#define    AC_GR_HLINE         "q" /* ─ U+2500 (Horizontal line) */
#define   _AC_GR_HLINE7        "r" /* ─ U+2500 (Horizontal line - Scan 7) */
#define   _AC_GR_HLINE9        "s" /* ─ U+2500 (Horizontal line - Scan 9) */
#define    AC_GR_VLINE_R       "t" /* ├ U+251c (Left "T") */
#define    AC_GR_VLINE_L       "u" /* ┤ U+2524 (Right "T") */
#define    AC_GR_HLINE_U       "v" /* ┴ U+2534 (Bottom "T") */
#define    AC_GR_HLINE_D       "w" /* ┬ U+252c (Top "T") */
#define    AC_GR_VLINE         "x" /* │ U+2502 (| Vertical bar) */
#define    AC_GR_LESS_EQUAL    "y" /* ≤ U+2264 (Less than or equal to) */
#define    AC_GR_GREATER_EQUAL "z" /* ≥ U+2265 (Greater than or equal to) */
#define    AC_GR_PI            "{" /* π U+03c0 (Pi) */
#define    AC_GR_NOT_EQUAL     "|" /* ≠ U+2260 (Not equal to) */
#define    AC_GR_UK_POUND      "}" /* £ U+00a3 (UK pound sign) */
#define    AC_GR_DOT           "~" /* ∙ U+2219 (Centered dot) */

/* Disable box-drawing mode */
#define AC_RESETGR _AC_ESC "(B"



/* Move everything over <decimal:n=1> columns, <decimal:n=1> new columns at right */
#define AC_SL(n) _AC_ESC "[" n " @"

/* Move everything over <decimal:n=1> columns, <decimal:n=1> new columns at left */
#define AC_SR(n) _AC_ESC "[" n " A"

/* Move cursor up <decimal:n=1> lines */
#define AC_CUU(n) _AC_ESC "[" n "A"

/* Move cursor down <decimal:n=1> lines */
#define AC_CUD(n) _AC_ESC "[" n "B"

/* Move cursor right <decimal:n=1> columns */
#define AC_CUF(n) _AC_ESC "[" n "C"

/* Move cursor left <decimal:n=1> columns */
#define AC_CUB(n) _AC_ESC "[" n "D"

/* Set 1-based cursor line to <decimal:n=1> */
#define AC_VPA(cury) _AC_ESC "[" cury "d"

/* Move cursor up <decimal:n=1> lines and CR(); */
#define AC_CPL(n) _AC_ESC "[" n "F"

/* Move cursor down <decimal:n=1> lines and CR(); */
#define AC_CNL(n) _AC_ESC "[" n "E"

/* Set 1-based cursor column to <decimal:n=1> */
#define AC_CHA(curx) _AC_ESC "[" curx "G"

/* SCROLL_UP(lines: <decimal:lines=1>);   (like "\n"; move existing lines upwards) */
#define AC_SU(lines) _AC_ESC "[" lines "T"

/* SCROLL_DOWN(lines: <decimal:lines=1>); (move existing lines downwards) */
#define AC_SD(lines) _AC_ESC "[" lines "T"

/* Same as `AC_VPA(cury) AC_CHA(curx)' */
#define AC_CUP(cury, curx) _AC_ESC "[" cury ";" curx "H" /* CUrsorPosition */
#define AC_HVP(cury, curx) _AC_ESC "[" cury ";" curx "f" /* HorizontalVerticalPosition (alias for CUP) */

/* Same as `AC_VPA("1") AC_CHA("1")' */
#define AC_CUP0   _AC_ESC "[H"

/* Make room for <decimal:n=1> characters at current position
 * Examples (for `AC_ICH("3")'):
 * [ANSITTY_FLAG_HEDIT=0, ANSITTY_FLAG_INSDEL_SCRN=0]
 * >>     123456789       123456789
 * >>     ABCD𝐄FGHI  -->  ABCD▂  EF
 * >>     abcdefghi       abcdefghi
 * [ANSITTY_FLAG_HEDIT=0, ANSITTY_FLAG_INSDEL_SCRN=1]
 * >>     123456789       123456789
 * >>     ABCD𝐄FGHI  -->  ABCD▂  EF
 * >>     abcdefghi       GHIabcdef
 * [ANSITTY_FLAG_HEDIT=1, ANSITTY_FLAG_INSDEL_SCRN=0]
 * >>     123456789       123456789
 * >>     ABCD𝐄FGHI  -->  D   𝐄FGHI
 * >>     abcdefghi       abcdefghi
 * [ANSITTY_FLAG_HEDIT=1, ANSITTY_FLAG_INSDEL_SCRN=1]
 * >>     123456789       456789ABC
 * >>     ABCD𝐄FGHI  -->  D   𝐄FGHI
 * >>     abcdefghi       abcdefghi
 * NOTE: Cursor is positioned at the 𝐁𝐎𝐋𝐃 character! */
#define AC_ICH(n) _AC_ESC "[" n "@"

/* Delete <decimal:n=1> characters, from current position to end of field
 * Examples (for `AC_DCH("3")'):
 * [ANSITTY_FLAG_HEDIT=0, ANSITTY_FLAG_INSDEL_SCRN=0]
 * >>     123456789       123456789
 * >>     ABCD𝐄FGHI  -->  ABCD𝐇I
 * >>     abcdefghi       abcdefghi
 * [ANSITTY_FLAG_HEDIT=0, ANSITTY_FLAG_INSDEL_SCRN=1]
 * >>     123456789       123456789
 * >>     ABCD𝐄FGHI  -->  ABCD𝐇Iabc
 * >>     abcdefghi       defghi
 * [ANSITTY_FLAG_HEDIT=1, ANSITTY_FLAG_INSDEL_SCRN=0]
 * >>     123456789       123456789
 * >>     ABCD𝐄FGHI  -->     A𝐄FGHI
 * >>     abcdefghi       abcdefghi
 * [ANSITTY_FLAG_HEDIT=1, ANSITTY_FLAG_INSDEL_SCRN=1]
 * >>     123456789          123456
 * >>     ABCD𝐄FGHI  -->  789A𝐄FGHI
 * >>     abcdefghi       abcdefghi
 * NOTE: Cursor is positioned at the 𝐁𝐎𝐋𝐃 character! */
#define AC_DCH(n) _AC_ESC "[" n "P"

/* Insert <decimal:n=1> lines if currently in scrolling region */
#define AC_IL(n) _AC_ESC "[" n "L"

/* Delete <decimal:n=1> lines if currently in scrolling region */
#define AC_DL(n) _AC_ESC "[" n "M"

/* Repeat the preceding character <decimal:n=1> times */
#define AC_REP(n) _AC_ESC "[" n "b"

/* EraseDisplay (with mode <decimal:mode=0>)
 *   `mode = "0"':  ANSITTY_CLS_AFTER
 *   `mode = "1"':  ANSITTY_CLS_BEFORE
 *   `mode = "2"':  ANSITTY_CLS_ALL
 *   `mode = "3"':  ANSITTY_CLS_ALLPAGES */
#define AC_ED(mode) _AC_ESC "[" mode "J"

/* EraseLine (with mode <decimal:mode=0>)
 *   `mode = "0"':  ANSITTY_EL_AFTER
 *   `mode = "1"':  ANSITTY_EL_BEFORE
 *   `mode = "2"':  ANSITTY_EL_ALL */
#define AC_EL(mode) _AC_ESC "[" mode "K"

/* Enable or disable `ANSITTY_FLAG_INSDEL_SCRN' (with mode <decimal:mode=0>)
 *   `mode = "0"':  enable ANSITTY_FLAG_INSDEL_SCRN
 *   `mode = "1"':  disable ANSITTY_FLAG_INSDEL_SCRN */
#define AC_SEM(mode) _AC_ESC "[" mode "Q"


/* Extended control options enable/disable */
#define AC_DECCKM_ON  _AC_ESC "[?1h"  /* Cursor Keys Mode, send ESC O A for cursor up (applicator cursor keys mode) */
#define AC_DECCKM_OFF _AC_ESC "[?1l"  /* Cursor keys send ANSI cursor position commands (normal cursor keys mode) */
#define AC_DECANM_ON  _AC_ESC "[?2h"  /* Disable `VT52' compatibility mode */
#define AC_DECANM_OFF _AC_ESC "[?2l"  /* Enable `VT52' compatibility mode */
#define AC_DECAWM_ON  _AC_ESC "[?7h"  /* Automatic line-feed once right side of terminal is reached */
#define AC_DECAWM_OFF _AC_ESC "[?7l"  /* Cursor remains at end of line after right side of terminal is reached */
#define AC_SHOWCURSOR _AC_ESC "[?25h" /* Show text mode cursor */
#define AC_HIDECURSOR _AC_ESC "[?25l" /* Hide text mode cursor */
#define AC_DECNKM_ON  _AC_ESC "[?66h" /* Application keypad (DECNKM), VT320 */
#define AC_DECNKM_OFF _AC_ESC "[?66l" /* Numeric keypad (DECNKM), VT320 */
#define AC_CRM_ON     _AC_ESC "[3h"   /* Control Representation Mode, show all control chars (use U+2400..U+2426 for display) */
#define AC_CRM_OFF    _AC_ESC "[3l"   /* Control characters are not displayable characters CRM */
#define AC_IRM_ON     _AC_ESC "[4h"   /* Insertion/Replacement Mode, set insert mode (behaves as though any printable character was preceded by `AC_ICH("1")') */
#define AC_IRM_OFF    _AC_ESC "[4l"   /* Insertion/Replacement Mode, set replacement mode */
#define AC_HEM_ON     _AC_ESC "[10h"  /* Horizontal Editing mode, ICH/DCH/IRM go backwards (ANSITTY_FLAG_HEDIT=1) */
#define AC_HEM_OFF    _AC_ESC "[10l"  /* ICH and IRM shove characters forward, DCH pulls (ANSITTY_FLAG_HEDIT=0) */


/* Set (1-based) start/end column indices for scroll margins
 * @param: <decimal:startcolumn=1>
 * @param: <decimal:endcolumn=MAXCOORD> */
#define AC_DECSLRM(startcolumn, endcolumn) _AC_ESC "[" startcolumn ";" endcolumn "s"

/* Set (1-based) start/end line indices for scroll region
 * @param: <decimal:startline=1>
 * @param: <decimal:endline=MAXCOORD> */
#define AC_DECSTBM(startline, endline) _AC_ESC "[" startline ";" endline "r"

/* Fill MIN(<decimal:n=1>, REMAINING_CELLS_IN_CURRENT_LINE) cells with space characters */
#define AC_ECH(n) _AC_ESC "[" n "X"


/* SetGraphicsRendition */
#define _AC_SGR(what) _AC_ESC "[" what "m"

#define AC_DEFATTR            _AC_SGR("")    /* Reset color and text attributes to normal */
#define AC_FGBRIGHT           _AC_SGR("1")   /* Brighten foreground color (fg_color |= ANSITTY_IFSTRONG) */
#define AC_FGDARK             _AC_SGR("2")   /* Darken foreground color (fg_color &= ~ANSITTY_IFSTRONG) */
#define AC_DEFBRIGHT          _AC_SGR("21")  /* Reset color brightness (fg_color = fg_color & ~ANSITTY_IFSTRONG | def_fg_color & ANSITTY_IFSTRONG) */
#define AC_ITALIC_ON          _AC_SGR("3")   /* ANSITTY_ATTRIB_ITALIC=1 */
#define AC_ITALIC_OFF         _AC_SGR("23")  /* ANSITTY_ATTRIB_ITALIC=0 */
#define AC_UNDERLINE_ON       _AC_SGR("4")   /* ANSITTY_ATTRIB_UNDERLINE=1 */
#define AC_UNDERLINE_OFF      _AC_SGR("24")  /* ANSITTY_ATTRIB_UNDERLINE=0 */
#define AC_BLINK_ON           _AC_SGR("5")   /* ANSITTY_ATTRIB_BLINK=1 */
#define AC_BLINK_OFF          _AC_SGR("25")  /* ANSITTY_ATTRIB_BLINK=0 */
#define AC_CONCEIL_ON         _AC_SGR("8")   /* ANSITTY_FLAG_CONCEIL=1 (fg_color = bg_color) */
#define AC_CONCEIL_OFF        _AC_SGR("28")  /* ANSITTY_FLAG_CONCEIL=0 */
#define AC_STRIKETHROUGH_ON   _AC_SGR("9")   /* ANSITTY_ATTRIB_STRIKETHROUGH=1 */
#define AC_STRIKETHROUGH_OFF  _AC_SGR("29")  /* ANSITTY_ATTRIB_STRIKETHROUGH=0 */
#define AC_FRAME_NORMAL       _AC_SGR("51")  /* ANSITTY_ATTRIB_FRAMED=1, ANSITTY_ATTRIB_CIRCLED=0 */
#define AC_FRAME_ROUND        _AC_SGR("52")  /* ANSITTY_ATTRIB_FRAMED=1, ANSITTY_ATTRIB_CIRCLED=1 */
#define AC_FRAME_OFF          _AC_SGR("54")  /* ANSITTY_ATTRIB_FRAMED=0, ANSITTY_ATTRIB_CIRCLED=0 */
#define AC_OVERLINE_ON        _AC_SGR("53")  /* ANSITTY_ATTRIB_OVERLINE=1 */
#define AC_OVERLINE_OFF       _AC_SGR("55")  /* ANSITTY_ATTRIB_OVERLINE=0 */

/* Foreground colors */
#define AC_FGDEF              _AC_SGR("39")  /* fg_color = def_fg_color */
#define AC_FG_BLACK           _AC_SGR("30")  /* fg_color = ANSITTY_CL_BLACK */
#define AC_FG_MAROON          _AC_SGR("31")  /* fg_color = ANSITTY_CL_RED */
#define AC_FG_GREEN           _AC_SGR("32")  /* fg_color = ANSITTY_CL_GREEN */
#define AC_FG_OLIVE           _AC_SGR("33")  /* fg_color = ANSITTY_CL_YELLOW */
#define AC_FG_NAVY            _AC_SGR("34")  /* fg_color = ANSITTY_CL_BLUE */
#define AC_FG_PURPLE          _AC_SGR("35")  /* fg_color = ANSITTY_CL_MAGENTA */
#define AC_FG_TEAL            _AC_SGR("36")  /* fg_color = ANSITTY_CL_CYAN */
#define AC_FG_SILVER          _AC_SGR("37")  /* fg_color = ANSITTY_CL_WHITE */
#define AC_FG_GREY            _AC_SGR("90")  /* fg_color = ANSITTY_IFSTRONG | ANSITTY_CL_BLACK */
#define AC_FG_RED             _AC_SGR("91")  /* fg_color = ANSITTY_IFSTRONG | ANSITTY_CL_RED */
#define AC_FG_LIME            _AC_SGR("92")  /* fg_color = ANSITTY_IFSTRONG | ANSITTY_CL_GREEN */
#define AC_FG_YELLOW          _AC_SGR("93")  /* fg_color = ANSITTY_IFSTRONG | ANSITTY_CL_YELLOW */
#define AC_FG_BLUE            _AC_SGR("94")  /* fg_color = ANSITTY_IFSTRONG | ANSITTY_CL_BLUE */
#define AC_FG_FUCHSIA         _AC_SGR("95")  /* fg_color = ANSITTY_IFSTRONG | ANSITTY_CL_MAGENTA */
#define AC_FG_AQUA            _AC_SGR("96")  /* fg_color = ANSITTY_IFSTRONG | ANSITTY_CL_CYAN */
#define AC_FG_WHITE           _AC_SGR("97")  /* fg_color = ANSITTY_IFSTRONG | ANSITTY_CL_WHITE */
#define AC_FG_LIGHT_GRAY      AC_FG_SILVER
#define AC_FG_DARK_GRAY       AC_FG_GREY
#define AC_FG_MAGENTA         AC_FG_PURPLE
#define AC_FG_CYAN            AC_FG_TEAL
#define AC_FG_LIGHT_GREEN     AC_FG_LIME
#define AC_FG_BRIGHT_GREEN    AC_FG_LIME
#define AC_FG_DARK_BLUE       AC_FG_NAVY


/* Background colors */
#define AC_BGDEF              _AC_SGR("49")  /* bg_color = def_fg_color */
#define AC_BG_BLACK           _AC_SGR("40")  /* bg_color = ANSITTY_CL_BLACK */
#define AC_BG_MAROON          _AC_SGR("41")  /* bg_color = ANSITTY_CL_RED */
#define AC_BG_GREEN           _AC_SGR("42")  /* bg_color = ANSITTY_CL_GREEN */
#define AC_BG_OLIVE           _AC_SGR("43")  /* bg_color = ANSITTY_CL_YELLOW */
#define AC_BG_NAVY            _AC_SGR("44")  /* bg_color = ANSITTY_CL_BLUE */
#define AC_BG_PURPLE          _AC_SGR("45")  /* bg_color = ANSITTY_CL_MAGENTA */
#define AC_BG_TEAL            _AC_SGR("46")  /* bg_color = ANSITTY_CL_CYAN */
#define AC_BG_SILVER          _AC_SGR("47")  /* bg_color = ANSITTY_CL_WHITE */
#define AC_BG_GREY            _AC_SGR("100") /* bg_color = ANSITTY_IFSTRONG | ANSITTY_CL_BLACK */
#define AC_BG_RED             _AC_SGR("101") /* bg_color = ANSITTY_IFSTRONG | ANSITTY_CL_RED */
#define AC_BG_LIME            _AC_SGR("102") /* bg_color = ANSITTY_IFSTRONG | ANSITTY_CL_GREEN */
#define AC_BG_YELLOW          _AC_SGR("103") /* bg_color = ANSITTY_IFSTRONG | ANSITTY_CL_YELLOW */
#define AC_BG_BLUE            _AC_SGR("104") /* bg_color = ANSITTY_IFSTRONG | ANSITTY_CL_BLUE */
#define AC_BG_FUCHSIA         _AC_SGR("105") /* bg_color = ANSITTY_IFSTRONG | ANSITTY_CL_MAGENTA */
#define AC_BG_AQUA            _AC_SGR("106") /* bg_color = ANSITTY_IFSTRONG | ANSITTY_CL_CYAN */
#define AC_BG_WHITE           _AC_SGR("107") /* bg_color = ANSITTY_IFSTRONG | ANSITTY_CL_WHITE */
#define AC_BG_LIGHT_GRAY      AC_BG_SILVER
#define AC_BG_DARK_GRAY       AC_BG_GREY
#define AC_BG_MAGENTA         AC_BG_PURPLE
#define AC_BG_CYAN            AC_BG_TEAL
#define AC_BG_LIGHT_GREEN     AC_BG_LIME
#define AC_BG_BRIGHT_GREEN    AC_BG_LIME
#define AC_BG_DARK_BLUE       AC_BG_NAVY


/* Set foreground color to one of `ANSITTY_CL_*' */
#define AC_FG(color) _AC_SGR(_AC_FG(color))
#define   _AC_FG(color) _AC_FG_##color
#define   _AC_FG_0x0 "30"
#define   _AC_FG_0x1 "31"
#define   _AC_FG_0x2 "32"
#define   _AC_FG_0x3 "33"
#define   _AC_FG_0x4 "34"
#define   _AC_FG_0x5 "35"
#define   _AC_FG_0x6 "36"
#define   _AC_FG_0x7 "37"
#define   _AC_FG_0x8 "90"
#define   _AC_FG_0x9 "91"
#define   _AC_FG_0xa "92"
#define   _AC_FG_0xb "93"
#define   _AC_FG_0xc "94"
#define   _AC_FG_0xd "95"
#define   _AC_FG_0xe "96"
#define   _AC_FG_0xf "97"

/* Set backround color to one of `ANSITTY_CL_*' */
#define AC_BG(color) _AC_SGR(_AC_BG(color))
#define   _AC_BG(color) _AC_BG_##color
#define   _AC_BG_0x0 "40"
#define   _AC_BG_0x1 "41"
#define   _AC_BG_0x2 "42"
#define   _AC_BG_0x3 "43"
#define   _AC_BG_0x4 "44"
#define   _AC_BG_0x5 "45"
#define   _AC_BG_0x6 "46"
#define   _AC_BG_0x7 "47"
#define   _AC_BG_0x8 "100"
#define   _AC_BG_0x9 "101"
#define   _AC_BG_0xa "102"
#define   _AC_BG_0xb "103"
#define   _AC_BG_0xc "104"
#define   _AC_BG_0xd "105"
#define   _AC_BG_0xe "106"
#define   _AC_BG_0xf "107"

/* Set foreground and background colors to one of `ANSITTY_CL_*' */
#define AC_COLOR(fg, bg) _AC_SGR(_AC_FG(fg) ";" _AC_BG(bg))

/* Reset foreground and background colors (same as `AC_FGDEF AC_BGDEF') */
#define AC_DEFCOLOR _AC_SGR("39;49")

/* Helper macros for displaying some given text in some custom
 * color,  before  reverting  the  default  color  afterwards. */
#define AC_WITHCOLOR(fg, bg, text) AC_COLOR(fg, bg) text AC_DEFCOLOR
#define AC_WITHFG(color, text)     AC_FG(color) text AC_FGDEF
#define AC_WITHBG(color, text)     AC_BG(color) text AC_BGDEF

#define AC_BLACK(text)        AC_WITHFG(ANSITTY_CL_BLACK, text)
#define AC_MAROON(text)       AC_WITHFG(ANSITTY_CL_MAROON, text)
#define AC_GREEN(text)        AC_WITHFG(ANSITTY_CL_GREEN, text)
#define AC_OLIVE(text)        AC_WITHFG(ANSITTY_CL_OLIVE, text)
#define AC_NAVY(text)         AC_WITHFG(ANSITTY_CL_NAVY, text)
#define AC_PURPLE(text)       AC_WITHFG(ANSITTY_CL_PURPLE, text)
#define AC_TEAL(text)         AC_WITHFG(ANSITTY_CL_TEAL, text)
#define AC_SILVER(text)       AC_WITHFG(ANSITTY_CL_SILVER, text)
#define AC_GREY(text)         AC_WITHFG(ANSITTY_CL_GREY, text)
#define AC_RED(text)          AC_WITHFG(ANSITTY_CL_RED, text)
#define AC_LIME(text)         AC_WITHFG(ANSITTY_CL_LIME, text)
#define AC_YELLOW(text)       AC_WITHFG(ANSITTY_CL_YELLOW, text)
#define AC_BLUE(text)         AC_WITHFG(ANSITTY_CL_BLUE, text)
#define AC_FUCHSIA(text)      AC_WITHFG(ANSITTY_CL_FUCHSIA, text)
#define AC_AQUA(text)         AC_WITHFG(ANSITTY_CL_AQUA, text)
#define AC_WHITE(text)        AC_WITHFG(ANSITTY_CL_WHITE, text)
#define AC_LIGHT_GRAY(text)   AC_WITHFG(ANSITTY_CL_LIGHT_GRAY, text)
#define AC_DARK_GRAY(text)    AC_WITHFG(ANSITTY_CL_DARK_GRAY, text)
#define AC_MAGENTA(text)      AC_WITHFG(ANSITTY_CL_MAGENTA, text)
#define AC_CYAN(text)         AC_WITHFG(ANSITTY_CL_CYAN, text)
#define AC_LIGHT_GREEN(text)  AC_WITHFG(ANSITTY_CL_LIGHT_GREEN, text)
#define AC_BRIGHT_GREEN(text) AC_WITHFG(ANSITTY_CL_BRIGHT_GREEN, text)
#define AC_DARK_BLUE(text)    AC_WITHFG(ANSITTY_CL_DARK_BLUE, text)

#endif /* !_LIBANSITTY_CTL_H */
