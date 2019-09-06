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
#ifndef GUARD_KERNEL_INCLUDE_KERNEL_DEBUGGER_H
#define GUARD_KERNEL_INCLUDE_KERNEL_DEBUGGER_H 1

#include <kernel/compiler.h>

#include <kernel/arch/debugger.h>
#include <kernel/types.h>
#include <stdbool.h>

#ifndef CONFIG_NO_DEBUGGER

DECL_BEGIN


#ifdef __CC__

#define ATTR_DBGTEXT    ATTR_COLDTEXT
#define ATTR_DBGRODATA  ATTR_COLDRODATA
#define ATTR_DBGDATA    ATTR_COLDDATA
#define ATTR_DBGBSS     ATTR_COLDBSS
#define DBGSTR(s)       XBLOCK({ PRIVATE ATTR_DBGRODATA char const _dbg_str[] = s; XRETURN _dbg_str; })

/* Enter the interactive kernel debugger.
 * HINT: This function preserves _all_ registers upon entry,
 *       as well as the state of most hardware components.
 *       It is intended to be callable from pretty much any
 *       context, where it is meant to display an interactive
 *       commandline in which the user can enter commands in
 *       order to make sense of what may have gone wrong.
 * NOTE: This function is also called during kernel panic. */
FUNDEF void KCALL dbg(void);
struct fcpustate;
struct ucpustate;
struct lcpustate;
struct kcpustate;
struct icpustate;
struct scpustate;

/* Enter the debugger using the given state by invoking `main'
 * This function will change the system state such that the debug sub-system becomes
 * available, allowing the caller to use this function to implement handlers for assertion
 * failures, unhandled exceptions, or plain old kernel panics.
 * @param: state_source: One of `DBG_ENTER_STATE_*' */
FUNDEF NONNULL((1)) void FCALL dbg_enter_here(void (KCALL *main)(void *arg), void *arg);
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter_fcpustate(struct fcpustate *__restrict state, void (KCALL *main)(void *arg), void *arg);
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter_ucpustate(struct ucpustate *__restrict state, void (KCALL *main)(void *arg), void *arg);
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter_lcpustate(struct lcpustate *__restrict state, void (KCALL *main)(void *arg), void *arg);
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter_kcpustate(struct kcpustate *__restrict state, void (KCALL *main)(void *arg), void *arg);
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter_icpustate(struct icpustate *__restrict state, void (KCALL *main)(void *arg), void *arg);
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter_scpustate(struct scpustate *__restrict state, void (KCALL *main)(void *arg), void *arg);
#endif /* __CC__ */
#define DBG_ENTER_STATE_CURRENT   0 /* Use the CPU state of the caller to `dbg_enter', allowing any changes
                                     * made to that state by `main' to be propagated upon return. */
#define DBG_ENTER_STATE_FSTATE    1 /* Use `state', interpreted as `struct fcpustate *state'. */
#define DBG_ENTER_STATE_USTATE    2 /* Use `state', interpreted as `struct ucpustate *state'. */
#define DBG_ENTER_STATE_LSTATE    3 /* Use `state', interpreted as `struct lcpustate *state'. */
#define DBG_ENTER_STATE_KSTATE    4 /* Use `state', interpreted as `struct kcpustate *state'. */

#ifdef __CC__
#ifdef __cplusplus
extern "C++" {
struct fcpustate;
struct ucpustate;
struct lcpustate;
struct kcpustate;
struct icpustate;
struct scpustate;
/* Helper overloads to automatically select the state encoding ID. */
FUNDEF NONNULL((1)) void FCALL dbg_enter(void (KCALL *main)(void *arg), void *arg) ASMNAME("dbg_enter_here");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct fcpustate *__restrict state, void (KCALL *main)(void *arg), void *arg) ASMNAME("dbg_enter_fcpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct ucpustate *__restrict state, void (KCALL *main)(void *arg), void *arg) ASMNAME("dbg_enter_ucpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct lcpustate *__restrict state, void (KCALL *main)(void *arg), void *arg) ASMNAME("dbg_enter_lcpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct kcpustate *__restrict state, void (KCALL *main)(void *arg), void *arg) ASMNAME("dbg_enter_kcpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct icpustate *__restrict state, void (KCALL *main)(void *arg), void *arg) ASMNAME("dbg_enter_icpustate");
FUNDEF ATTR_NORETURN NONNULL((1, 2)) void FCALL dbg_enter(struct scpustate *__restrict state, void (KCALL *main)(void *arg), void *arg) ASMNAME("dbg_enter_scpustate");
}
#endif

struct task;

/* The default debugger main entry function. */
FUNDEF void KCALL dbg_main(uintptr_t show_welcome);
/* Invoke debugger exit callbacks and load `dbg_exitstate'. Then, resume execution */
FUNDEF ATTR_NORETURN void KCALL dbg_exit(void);

/* Non-zero if the debugger is currently active. */
DATDEF unsigned int dbg_active;
DATDEF struct fcpustate dbg_exitstate; /* The CPU state to which the debugger will return. */
DATDEF struct fcpustate dbg_viewstate; /* The CPU state currently being viewed by the debugger (for walking the stack...). */

/* [1..1] The original thread that entered debugger mode */
DATDEF struct task *const debug_original_thread;

/* Impersonate the given `thread' for the purpose of debugging.
 * For this purpose, change the TLS segment to `thread', and update `dbg_viewstate',
 * though only `dbg_viewstate' to represent the register state of `thread'.
 * You may switch back to the original thread by using:
 *     `dbg_impersonate_thread(debug_original_thread)'
 * HINT: This is done as part of the `undo' command */
FUNDEF void KCALL dbg_impersonate_thread(struct task *__restrict thread);


/* Wait for the user to press a key and return its keycode.
 * @return: * : One of `KEY_*' (from <kos/keyboard.h>) */
FUNDEF unsigned int KCALL dbg_getkey(void);
FUNDEF NOBLOCK unsigned int KCALL dbg_trygetkey(void); /* @return: 0: No keys available. */

/* Unget a key to be re-returned by `dbg_(try)getkey'
 * When ungetting multiple keys, the key last unget'ed will be returned last. */
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_ungetkey)(unsigned int key);

/* Wait for the user to press a key and return the pressed character.
 * NOTE: Modifier keys aren't returned by this function. */
FUNDEF /*utf-8*/char KCALL dbg_getc(void);
FUNDEF /*utf-32*/u32 KCALL dbg_getuni(void);
FUNDEF NOBLOCK /*utf-8*/char KCALL dbg_trygetc(void);
FUNDEF NOBLOCK /*utf-32*/u32 KCALL dbg_trygetuni(void);

/* Unget a character to be re-returned by `dbg_(try)get(c|uni)'
 * When ungetting multiple characters, the character last unget'ed will be returned last. */
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_ungetc)(/*utf-8*/char ch);
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_ungetuni)(/*utf-32*/u32 ch);

/* Check if there are pending unicode characters. */
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_hasuni)(void);
/* Purge pending unicode characters. */
FUNDEF NOBLOCK void NOTHROW(KCALL dbg_purgeuni)(void);

FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_isholding_ctrl)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_isholding_shift)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_isholding_alt)(void);
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_isholding_altgr)(void);


/* Try to auto-complete whatever was written at `line+num_written',
 * returning the number of additional bytes written by the Autocomplete
 * @param: line:        The input line of text that should be completed.
 * @param: bufsize:    [> num_written] The available buffer size in bytes, starting at `line' (must not be exceeded)
 * @param: num_written: The amount of bytes already filled in by the user.
 * @return: * :         The number of bytes appended by auto-completion. */
typedef NONNULL((1)) size_t (KCALL *dbg_autocomplete_t)(char *__restrict line,
                                                        size_t bufsize, size_t num_written);

/* Default auto completion function for the debug command line. */
FUNDEF NONNULL((1)) size_t KCALL dbg_autocomplete_command(char *__restrict line,
                                                          size_t bufsize, size_t num_written);

/* Read a single line of user-input from the debug terminal, and fill `buf'
 * NOTE: This function also performs tab-completion, as well as keep an input
 *       history backlog.
 * @param: autocomplete: The autocomplete function that should be used
 *                       for TAB (or `NULL' if this should be disabled)
 * @return: * : The number of bytes read and written to `buf' */
FUNDEF size_t KCALL dbg_readline(/*utf-8*/char *__restrict buf, size_t bufsize,
                                 dbg_autocomplete_t autocomplete);
#define DBG_MAXLINE 256 /* Default max length of a line (aka. intended size for `dbg_readline:buf') */

/* I/O within the debugger. */
FUNDEF void NOTHROW(KCALL dbg_bell)(void);
FUNDEF void NOTHROW(KCALL dbg_putc)(/*utf-8*/char ch);
FUNDEF void NOTHROW(KCALL dbg_putuni)(/*utf-32*/u32 ch);
FUNDEF void NOTHROW(KCALL dbg_fillscreen)(/*utf-32*/u32 ch); /* Fill the entire screen with `ch' */
FUNDEF NONNULL((1)) void KCALL dbg_print(/*utf-8*/char const *__restrict str);
FUNDEF NONNULL((1)) void VCALL dbg_printf(/*utf-8*/char const *__restrict format, ...);
FUNDEF NONNULL((1)) void KCALL dbg_vprintf(/*utf-8*/char const *__restrict format, __builtin_va_list args);
FUNDEF NONNULL((2)) ssize_t KCALL dbg_printer(void *ignored, /*utf-8*/char const *__restrict data, size_t datalen);

/* Display a rectangle (frame) or box (filled) on-screen. */
FUNDEF void NOTHROW(KCALL dbg_fillbox)(int x, int y, unsigned int size_x, unsigned int size_y, /*utf-32*/u32 ch);
FUNDEF void NOTHROW(KCALL dbg_fillrect)(int x, int y, unsigned int size_x, unsigned int size_y, /*utf-32*/u32 ch);
FUNDEF void NOTHROW(KCALL dbg_fillrect2)(int x, int y, unsigned int size_x, unsigned int size_y, /*utf-32*/u32 tl, /*utf-32*/u32 t, /*utf-32*/u32 tr, /*utf-32*/u32 l, /*utf-32*/u32 r, /*utf-32*/u32 bl, /*utf-32*/u32 b, /*utf-32*/u32 br);
FUNDEF void NOTHROW(KCALL dbg_hline)(int x, int y, unsigned int size_x, /*utf-32*/u32 ch);
FUNDEF void NOTHROW(KCALL dbg_vline)(int x, int y, unsigned int size_y, /*utf-32*/u32 ch);

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
FUNDEF void NOTHROW(KCALL dbg_pputuni)(int x, int y, /*utf-32*/u32 ch);
FUNDEF void KCALL dbg_pprint(int x, int y, /*utf-8*/char const *__restrict str);
FUNDEF void VCALL dbg_pprintf(int x, int y, /*utf-8*/char const *__restrict format, ...);
FUNDEF void KCALL dbg_vpprintf(int x, int y, /*utf-8*/char const *__restrict format, __builtin_va_list args);
FUNDEF ssize_t KCALL dbg_pprinter(/*dbg_pprinter_arg_t*/void *arg, /*utf-8*/char const *__restrict data, size_t datalen);
typedef struct {
	int p_printx;  /* X-coord of the next character */
	int p_printy;  /* Y-coord of the next character */
	u8  p_utf8[8]; /* Pending UTF-8 characters */
} dbg_pprinter_arg_t;
#define DBG_PPRINTER_ARG_INIT(x, y) { x, y, { 0, 0, 0, 0, 0, 0, 0, 0  } }

/* Display a selections menu with a set of `options' (which is a NULL-terminated vector strings)
 * Options are on top of each other, and can be navigated using the arrow keys.
 * @return: * : The index of the selected option, or one of `DBG_MENU_SELECTION_*' */
FUNDEF WUNUSED NONNULL((1, 2)) unsigned int
NOTHROW(KCALL dbg_menuex)(char const *__restrict title,
                          char const *const *__restrict options,
                          unsigned int default_option,
                          void (KCALL *print_message)(void *arg),
                          void *arg);
FUNDEF WUNUSED NONNULL((1, 2, 4)) unsigned int
NOTHROW(VCALL dbg_menuf)(char const *__restrict title,
                         char const *const *__restrict options,
                         unsigned int default_option,
                         char const *__restrict message_format,
                         ...);
FUNDEF WUNUSED NONNULL((1, 2, 4)) unsigned int
NOTHROW(KCALL dbg_vmenuf)(char const *__restrict title,
                          char const *const *__restrict options,
                          unsigned int default_option,
                          char const *__restrict message_format,
                          __builtin_va_list args);
#define DBG_MENU_SELECTION_CANCEL  ((unsigned int)-1) /* The user pressed ESC */

/* Print a messagebox centered on-screen. */
FUNDEF void NOTHROW(KCALL dbg_messagebox)(char const *__restrict title,
                                          char const *__restrict text);

/* Open an interactive hex editor at `addr'
 * @param: is_readonly: When true, enable read-only mode by default
 * @return: * : The final selected address when the editor was closed. */
FUNDEF void *NOTHROW(FCALL dbg_hexedit)(void *addr, bool is_readonly DFL(true));

/* Open an interactive assembly viewer at `addr'
 * @return: * : The final selected address when the viewer was closed. */
FUNDEF void *NOTHROW(FCALL dbg_asmview)(void *addr);

/* Process input for an edit field at the given position, allowing
 * the user to type in input text, with that text then being written
 * to the given `buf'.
 * Note that if `buf' is non-empty (buf[0] != '\0') upon entry,
 * editing will resume with the current contents of `buf'
 * @return: * : One of `DBG_EDITFIELD_RETURN_*' */
FUNDEF unsigned int
NOTHROW(FCALL dbg_editfield)(int x, int y, unsigned int field_width,
                             char *buf, size_t buflen);
#define DBG_EDITFIELD_RETURN_ENTER     0 /* Enter (confirm) */
#define DBG_EDITFIELD_RETURN_TAB       1 /* Tab (go to next field?) */
#define DBG_EDITFIELD_RETURN_SHIFT_TAB 2 /* Shift+Tab (go to next field?) */
#define DBG_EDITFIELD_RETURN_ESC       3
#define DBG_EDITFIELD_RETURN_F(n)     (16+((n)-1)) /* Fn key was pressed */

/* Same as `dbg_editfield()', but only draw the edit field. */
FUNDEF void
NOTHROW(FCALL dbg_draweditfield)(int x, int y, unsigned int field_width,
                                 char *buf, size_t buflen);


/* Evaluate an address expression
 * @param: flags:  Set of `DBG_EVALADDR_FLAG_*'
 * @return: true:  Evaluation failed. (when `DBG_EVALADDR_FLAG_NO_ERROR' wasn't set,
 *                                     an error was already displayed to the user)
 * @return: false: Evaluation failed. */
FUNDEF bool NOTHROW(FCALL dbg_evaladdr)(char const *__restrict expr,
                                        uintptr_t *__restrict presult,
                                        unsigned int flags DFL(0));
#define dbg_evalexpr(expr, presult) dbg_evaladdr(expr, presult, DBG_EVALADDR_FLAG_NO_HEX)
#define DBG_EVALADDR_FLAG_NO_ERROR  0x0001 /* Don't show an error message describing what's wrong with the syntax. */
#define DBG_EVALADDR_FLAG_NO_HEX    0x0002 /* When not set, `512' is `0x512', else it is decimal. Regardless of this,
                                            * `5C2' is always hex, and `+512' or `(512)' are always decimal.
                                            * This flag only affects top-level integral constants. */


/* Try to get/set the value of a given register from `dbg_viewstate', given its name.
 * Note that registers with values larger than pointer-size are usually split up into
 * two or more different registers.
 * @return: true:  Success.
 * @return: false: Invalid register name. */
FUNDEF bool NOTHROW(FCALL dbg_getreg)(char const *__restrict name, size_t namelen, uintptr_t *__restrict presult);
FUNDEF bool NOTHROW(FCALL dbg_setreg)(char const *__restrict name, size_t namelen, uintptr_t value);

/* Apply changes made to the viewed register state
 * to the current thread's return location. */
FUNDEF void NOTHROW(FCALL dbg_applyreg)(void);

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
                                    * of the current */


/* Get/Set debug TTY screen data
 * NOTE: Reading Out-of-bound cells are read as the same value as a space-character
 *       cell when written using `dbg_putc(' ')' as the current cursor position.
 * NOTE: Writing Out-of-bound cells is a no-op.
 * NOTE: These functions will read/write the SCROLL-TOP screen data, and
 *      `dbg_setscreendata()' will apply `dbg_scroll(DBG_SCROLL_CMD_SET,0)'
 *       before actually copying cells.
 * @param: buf: A buffer capable of holding `size_x * size_y * dbg_screen_cellsize' bytes of data. */
FUNDEF NONNULL((5)) void (KCALL dbg_getscreendata)(int x, int y, unsigned int size_x, unsigned int size_y, void *__restrict buf);
FUNDEF NONNULL((5)) void (KCALL dbg_setscreendata)(int x, int y, unsigned int size_x, unsigned int size_y, void const *__restrict buf);


/* Set if the current cursor position should be visible.
 * @return: true:  The cursor is (now) visible.
 * @return: false: The cursor is (now) hidden. */
FUNDEF bool NOTHROW(KCALL dbg_setcur_visible)(unsigned int cmd);
#define DBG_SETCUR_VISIBLE_HIDE 0 /* Hide the cursor. */
#define DBG_SETCUR_VISIBLE_SHOW 1 /* Show the cursor. */
#define DBG_SETCUR_VISIBLE_TEST 2 /* Check if the cursor is visible. */

/* Get/Set the current on-screen cursor position.
 * NOTE: Out-of-bounds coords are clamped to their valid ranges. */
FUNDEF u32 NOTHROW(KCALL dbg_setcur)(int x, int y);
FUNDEF u32 NOTHROW(KCALL dbg_getcur)(void);
#define DBG_GETCUR_X(val)  ((unsigned int)((val) & 0xffff))
#define DBG_GETCUR_Y(val)  ((unsigned int)((val) >> 16))
LOCAL unsigned int NOTHROW(KCALL dbg_getcur_x)(void) { return DBG_GETCUR_X(dbg_getcur()); }
LOCAL unsigned int NOTHROW(KCALL dbg_getcur_y)(void) { return DBG_GETCUR_Y(dbg_getcur()); }


/* TTY color codes. */
#define DBG_COLOR_BLACK   0x0 /* RGB(0x00, 0x00, 0x00) */
#define DBG_COLOR_NAVY    0x1 /* RGB(0x00, 0x00, 0xa8) */
#define DBG_COLOR_GREEN   0x2 /* RGB(0x00, 0xa8, 0x00) */
#define DBG_COLOR_TEAL    0x3 /* RGB(0x00, 0xa8, 0xa8) */
#define DBG_COLOR_MAROON  0x4 /* RGB(0xa8, 0x00, 0x00) */
#define DBG_COLOR_PURPLE  0x5 /* RGB(0xa8, 0x00, 0xa8) */
#define DBG_COLOR_OLIVE   0x6 /* RGB(0xa8, 0x57, 0x00) */
#define DBG_COLOR_SILVER  0x7 /* RGB(0xa8, 0xa8, 0xa8) */
#define DBG_COLOR_GREY    0x8 /* RGB(0x57, 0x57, 0x57) */
#define DBG_COLOR_BLUE    0x9 /* RGB(0x57, 0x57, 0xff) */
#define DBG_COLOR_LIME    0xa /* RGB(0x57, 0xff, 0x57) */
#define DBG_COLOR_AQUA    0xb /* RGB(0x57, 0xff, 0xff) */
#define DBG_COLOR_RED     0xc /* RGB(0xff, 0x57, 0x57) */
#define DBG_COLOR_FUCHSIA 0xd /* RGB(0xff, 0x57, 0xff) */
#define DBG_COLOR_YELLOW  0xe /* RGB(0xff, 0xff, 0x57) */
#define DBG_COLOR_WHITE   0xf /* RGB(0xff, 0xff, 0xff) */
#define DBG_COLOR_LIGHT_GRAY    DBG_COLOR_SILVER
#define DBG_COLOR_DARK_GRAY     DBG_COLOR_GREY



#define _DBG_PRIVATE_COLORFMT_FG_0x0 "30"  /* DBG_COLOR_BLACK  : RGB(0x00,0x00,0x00) */
#define _DBG_PRIVATE_COLORFMT_FG_0x1 "31"  /* DBG_COLOR_NAVY   : RGB(0x00,0x00,0xa8) */
#define _DBG_PRIVATE_COLORFMT_FG_0x2 "32"  /* DBG_COLOR_GREEN  : RGB(0x00,0xa8,0x00) */
#define _DBG_PRIVATE_COLORFMT_FG_0x3 "33"  /* DBG_COLOR_TEAL   : RGB(0x00,0xa8,0xa8) */
#define _DBG_PRIVATE_COLORFMT_FG_0x4 "34"  /* DBG_COLOR_MAROON : RGB(0xa8,0x00,0x00) */
#define _DBG_PRIVATE_COLORFMT_FG_0x5 "35"  /* DBG_COLOR_PURPLE : RGB(0xa8,0x00,0xa8) */
#define _DBG_PRIVATE_COLORFMT_FG_0x6 "36"  /* DBG_COLOR_OLIVE  : RGB(0xa8,0x57,0x00) */
#define _DBG_PRIVATE_COLORFMT_FG_0x7 "37"  /* DBG_COLOR_SILVER : RGB(0xa8,0xa8,0xa8) */
#define _DBG_PRIVATE_COLORFMT_FG_0x8 "90"  /* DBG_COLOR_GREY   : RGB(0x57,0x57,0x57) */
#define _DBG_PRIVATE_COLORFMT_FG_0x9 "91"  /* DBG_COLOR_BLUE   : RGB(0x57,0x57,0xff) */
#define _DBG_PRIVATE_COLORFMT_FG_0xa "92"  /* DBG_COLOR_LIME   : RGB(0x57,0xff,0x57) */
#define _DBG_PRIVATE_COLORFMT_FG_0xb "93"  /* DBG_COLOR_AQUA   : RGB(0x57,0xff,0xff) */
#define _DBG_PRIVATE_COLORFMT_FG_0xc "94"  /* DBG_COLOR_RED    : RGB(0xff,0x57,0x57) */
#define _DBG_PRIVATE_COLORFMT_FG_0xd "95"  /* DBG_COLOR_FUCHSIA: RGB(0xff,0x57,0xff) */
#define _DBG_PRIVATE_COLORFMT_FG_0xe "96"  /* DBG_COLOR_YELLOW : RGB(0xff,0xff,0x57) */
#define _DBG_PRIVATE_COLORFMT_FG_0xf "97"  /* DBG_COLOR_WHITE  : RGB(0xff,0xff,0xff) */
#define _DBG_PRIVATE_COLORFMT_BG_0x0 "40"  /* DBG_COLOR_BLACK  : RGB(0x00,0x00,0x00) */
#define _DBG_PRIVATE_COLORFMT_BG_0x1 "41"  /* DBG_COLOR_NAVY   : RGB(0x00,0x00,0xa8) */
#define _DBG_PRIVATE_COLORFMT_BG_0x2 "42"  /* DBG_COLOR_GREEN  : RGB(0x00,0xa8,0x00) */
#define _DBG_PRIVATE_COLORFMT_BG_0x3 "43"  /* DBG_COLOR_TEAL   : RGB(0x00,0xa8,0xa8) */
#define _DBG_PRIVATE_COLORFMT_BG_0x4 "44"  /* DBG_COLOR_MAROON : RGB(0xa8,0x00,0x00) */
#define _DBG_PRIVATE_COLORFMT_BG_0x5 "45"  /* DBG_COLOR_PURPLE : RGB(0xa8,0x00,0xa8) */
#define _DBG_PRIVATE_COLORFMT_BG_0x6 "46"  /* DBG_COLOR_OLIVE  : RGB(0xa8,0x57,0x00) */
#define _DBG_PRIVATE_COLORFMT_BG_0x7 "47"  /* DBG_COLOR_SILVER : RGB(0xa8,0xa8,0xa8) */
#define _DBG_PRIVATE_COLORFMT_BG_0x8 "100" /* DBG_COLOR_GREY   : RGB(0x57,0x57,0x57) */
#define _DBG_PRIVATE_COLORFMT_BG_0x9 "101" /* DBG_COLOR_BLUE   : RGB(0x57,0x57,0xff) */
#define _DBG_PRIVATE_COLORFMT_BG_0xa "102" /* DBG_COLOR_LIME   : RGB(0x57,0xff,0x57) */
#define _DBG_PRIVATE_COLORFMT_BG_0xb "103" /* DBG_COLOR_AQUA   : RGB(0x57,0xff,0xff) */
#define _DBG_PRIVATE_COLORFMT_BG_0xc "104" /* DBG_COLOR_RED    : RGB(0xff,0x57,0x57) */
#define _DBG_PRIVATE_COLORFMT_BG_0xd "105" /* DBG_COLOR_FUCHSIA: RGB(0xff,0x57,0xff) */
#define _DBG_PRIVATE_COLORFMT_BG_0xe "106" /* DBG_COLOR_YELLOW : RGB(0xff,0xff,0x57) */
#define _DBG_PRIVATE_COLORFMT_BG_0xf "107" /* DBG_COLOR_WHITE  : RGB(0xff,0xff,0xff) */


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



/* Print addr2line optimized for the debugger.
 * Example (of an inlined function):
 * >> c010783a+4   [my_inline_function+8] [bar.c:9]
 * >> c0107828+38  [my_function+26] [bar.c:42]
 * This is similar to `addr2line_printf()', however doesn't include the full source path,
 * and doesn't follow the file(line,col) format, but instead opts for much shorter lines
 * which can then (usually) be displayed in one continuous line, rather than having to be
 * split up into multiple lines.
 * Additionally, this function also highlights output using differing colors. */
FUNDEF void NOTHROW(VCALL dbg_addr2line_printf)(uintptr_t start_pc, uintptr_t end_pc,
                                                char const *message_format, ...);
FUNDEF void NOTHROW(KCALL dbg_addr2line_vprintf)(uintptr_t start_pc, uintptr_t end_pc,
                                                 char const *message_format, __builtin_va_list args);


#define DEBUG_CALL VCALL

/* The prototype for the callback of a debugger service function. */
typedef uintptr_t (DEBUG_CALL *debug_func_t)(size_t argc, char *argv[]);
struct debug_function {
	debug_func_t df_main; /* [1..1][const] The function's callback. */
	char const  *df_name; /* [1..1][const] The function's name. */
	char const  *df_help; /* [0..1][const] An optional help string for the function. */
};

/* Search for a debug function matching the given name.
 * @return: NULL: No function exists that matches `name' */
FUNDEF WUNUSED NONNULL((1)) struct debug_function const *KCALL
dbg_getfunc(char const *__restrict name);
/* Search for a debug function matching the given name most closely. */
FUNDEF ATTR_RETNONNULL WUNUSED NONNULL((1)) struct debug_function const *KCALL
dbg_getfunc_fuzzy(char const *__restrict name);
/* Search for a debug function who's name starts with `name'. */
FUNDEF WUNUSED NONNULL((1)) struct debug_function const *KCALL
dbg_getfunc_start(char const *__restrict name);


/* Special return values for debug functions. */
#define DBG_FUNCTION_INVALID_ARGUMENTS ((uintptr_t)-1)

#define _DBG_PRIVATE_FUNCTION_NAME3(x, y) x##y
#define _DBG_PRIVATE_FUNCTION_NAME2(x, y) _DBG_PRIVATE_FUNCTION_NAME3(x, y)
#define _DBG_PRIVATE_FUNCTION_NAME(x) _DBG_PRIVATE_FUNCTION_NAME2(x, __LINE__)

#define REGISTER_DEBUG_FUNCTION_EX(name, help, main)                                                                      \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_function_str") char const _DBG_PRIVATE_FUNCTION_NAME(_debug_name_)[] = name; \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_function_str") char const _DBG_PRIVATE_FUNCTION_NAME(_debug_help_)[] = help; \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_functions") ATTR_USED                                                        \
	struct debug_function const _DBG_PRIVATE_FUNCTION_NAME(_debug_def) =                                                  \
		{ &main, _DBG_PRIVATE_FUNCTION_NAME(_debug_name_), _DBG_PRIVATE_FUNCTION_NAME(_debug_help_) }
#define DEFINE_DEBUG_FUNCTION(name, help, argc, argv)                                                                     \
	PRIVATE uintptr_t DEBUG_CALL _DBG_PRIVATE_FUNCTION_NAME(_debug_main_)(size_t argc, char *argv[]);                     \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_function_str") char const _DBG_PRIVATE_FUNCTION_NAME(_debug_name_)[] = name; \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_function_str") char const _DBG_PRIVATE_FUNCTION_NAME(_debug_help_)[] = help; \
	PRIVATE ATTR_SECTION(".rodata.cold.debug_functions") ATTR_USED                                                        \
	struct debug_function const _DBG_PRIVATE_FUNCTION_NAME(_debug_def) =                                                  \
		{	&_DBG_PRIVATE_FUNCTION_NAME(_debug_main_),                                                                    \
			_DBG_PRIVATE_FUNCTION_NAME(_debug_name_),                                                                     \
			_DBG_PRIVATE_FUNCTION_NAME(_debug_help_) };                                                                   \
	PRIVATE ATTR_DBGTEXT uintptr_t DEBUG_CALL _DBG_PRIVATE_FUNCTION_NAME(_debug_main_)(size_t argc, char *argv[])
#endif /* __CC__ */

/* >> void KCALL func(void);
 * Define a debug initializer/reset/finalizer function
 * INIT:  Called whenever the debugger is entered (not called upon recursive re-entry)
 * FINI:  Called whenever the debugger is exited
 * RESET: Called whenever the debugger is entered (after INIT, including on recursive re-entry) */
#define DEFINE_DBG_INIT(func)  DEFINE_CALLBACK(".rodata.cold.callback.dbg_init", func)
#define DEFINE_DBG_RESET(func) DEFINE_CALLBACK(".rodata.cold.callback.dbg_reset", func)
#define DEFINE_DBG_FINI(func)  DEFINE_CALLBACK(".rodata.cold.callback.dbg_fini", func)

DECL_END

#ifdef __CC__
#include <libc/string.h>
#define _DBG_PRIVATE_BZERO_NAME3(prefix, y) prefix##y
#define _DBG_PRIVATE_BZERO_NAME2(prefix, y) _DBG_PRIVATE_BZERO_NAME3(prefix, y)
#define _DBG_PRIVATE_BZERO_NAME(prefix) _DBG_PRIVATE_BZERO_NAME2(prefix, __LINE__)

/* Define the callbacks necessary to do `memset(p,0,size)' during a debugger
 * reset, as well as safely backup/restore the original contents of the
 * specified memory range upon initialization/finalization. */
#define DEFINE_DBG_BZERO(p, size)                                                    \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[size];  \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)(void) {  \
		__libc_memcpy(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), p, size);        \
	}                                                                                \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)(void) { \
		__libc_memset(p, 0, size);                                                   \
	}                                                                                \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini)(void) {  \
		__libc_memcpy(p, _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), size);        \
	}                                                                                \
	DEFINE_DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init));                     \
	DEFINE_DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset));                   \
	DEFINE_DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini))
#define DEFINE_DBG_BZERO_IF(cond, p, size)                                           \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[size];  \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)(void) {  \
		if (cond)                                                                    \
			__libc_memcpy(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), p, size);    \
	}                                                                                \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)(void) { \
		if (cond)                                                                    \
			__libc_memset(p, 0, size);                                               \
	}                                                                                \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini)(void) {  \
		if (cond)                                                                    \
			__libc_memcpy(p, _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup), size);    \
	}                                                                                \
	DEFINE_DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init));                     \
	DEFINE_DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset));                   \
	DEFINE_DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini))
#define DEFINE_DBG_BZERO_VECTOR(vector_base, element_count, element_size, element_stride)                       \
	PRIVATE ATTR_COLDBSS byte_t _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup)[(element_count) * (element_size)]; \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_init)(void) {                             \
		size_t i;                                                                                               \
		byte_t *dst       = _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup);                                       \
		byte_t const *src = (byte_t const *)(vector_base);                                                      \
		for (i = 0; i < (element_count); ++i) {                                                                 \
			__libc_memcpy(dst, src, element_size);                                                              \
			dst += (element_size);                                                                              \
			src += (element_stride);                                                                            \
		}                                                                                                       \
	}                                                                                                           \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset)(void) {                            \
		size_t i;                                                                                               \
		byte_t *dst = (byte_t *)(vector_base);                                                                  \
		for (i = 0; i < (element_count); ++i) {                                                                 \
			__libc_memset(dst, 0, element_size);                                                                \
			dst += (element_stride);                                                                            \
		}                                                                                                       \
	}                                                                                                           \
	PRIVATE ATTR_USED void KCALL _DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini)(void) {                             \
		size_t i;                                                                                               \
		byte_t *dst       = (byte_t *)(vector_base);                                                            \
		byte_t const *src = _DBG_PRIVATE_BZERO_NAME(_debug_bzero_backup);                                       \
		for (i = 0; i < (element_count); ++i) {                                                                 \
			__libc_memcpy(dst, src, element_size);                                                              \
			dst += (element_stride);                                                                            \
			src += (element_size);                                                                              \
		}                                                                                                       \
	}                                                                                                           \
	DEFINE_DBG_INIT(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_init));                                                \
	DEFINE_DBG_RESET(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_reset));                                              \
	DEFINE_DBG_FINI(_DBG_PRIVATE_BZERO_NAME(_debug_bzero_fini))
#define DEFINE_DBG_BZERO_OBJECT(obj) \
	DEFINE_DBG_BZERO(&(obj), sizeof(obj))
#endif /* __CC__ */

#else /* !CONFIG_NO_DEBUGGER */
#define DEFINE_DEBUG_FUNCTION(name, main, help)                                           /* nothing */
#define DEFINE_DBG_INIT(func)                                                             /* nothing */
#define DEFINE_DBG_RESET(func)                                                            /* nothing */
#define DEFINE_DBG_FINI(func)                                                             /* nothing */
#define DEFINE_DBG_BZERO(p, size)                                                         /* nothing */
#define DEFINE_DBG_BZERO_IF(cond, p, size)                                                /* nothing */
#define DEFINE_DBG_BZERO_VECTOR(vector_base, element_count, element_size, element_stride) /* nothing */
#define DEFINE_DBG_BZERO_OBJECT(obj)                                                      /* nothing */
#endif /* CONFIG_NO_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_KERNEL_DEBUGGER_H */
