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
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_INPUT_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_INPUT_H 1

#include <kernel/compiler.h>
#include <debugger/config.h>

#ifdef CONFIG_HAVE_DEBUGGER
#include <kernel/types.h>
#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__

/* Wait for the user to press a key and return its keycode.
 * @return: * : One of `KEY_*' (from <kos/keyboard.h>) */
FUNDEF u16 NOTHROW(KCALL dbg_getkey)(void);
FUNDEF NOBLOCK u16 NOTHROW(KCALL dbg_trygetkey)(void); /* @return: 0: No keys available. */

/* Unget a key to be re-returned by `dbg_(try)getkey'
 * When ungetting multiple keys, the key last unget'ed will be returned last. */
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_ungetkey)(u16 key);

/* Wait for the user to press a key and return the pressed character.
 * NOTE: Modifier keys aren't returned by this function. */
FUNDEF /*utf-8*/ char KCALL dbg_getc(void);
FUNDEF /*utf-32*/ char32_t KCALL dbg_getuni(void);
FUNDEF NOBLOCK /*utf-8*/ char KCALL dbg_trygetc(void);
FUNDEF NOBLOCK /*utf-32*/ char32_t KCALL dbg_trygetuni(void);

/* Unget a character to be re-returned by `dbg_(try)get(c|uni)'
 * When ungetting multiple characters, the character last unget'ed will be returned last. */
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_ungetc)(/*utf-8*/ char ch);
FUNDEF NOBLOCK bool NOTHROW(KCALL dbg_ungetuni)(/*utf-32*/ char32_t ch);

/* Check if there are pending unicode characters. */
FUNDEF NOBLOCK WUNUSED ATTR_PURE bool NOTHROW(KCALL dbg_hasuni)(void);
/* Purge pending unicode characters. */
FUNDEF NOBLOCK void NOTHROW(KCALL dbg_purgeuni)(void);

/* Check if a given modifier key is being held down. */
FUNDEF NOBLOCK WUNUSED ATTR_PURE bool NOTHROW(KCALL dbg_isholding_ctrl)(void);
FUNDEF NOBLOCK WUNUSED ATTR_PURE bool NOTHROW(KCALL dbg_isholding_shift)(void);
FUNDEF NOBLOCK WUNUSED ATTR_PURE bool NOTHROW(KCALL dbg_isholding_alt)(void);
FUNDEF NOBLOCK WUNUSED ATTR_PURE bool NOTHROW(KCALL dbg_isholding_altgr)(void);


/* Try to auto-complete whatever was written at `line+num_written',
 * returning the number of additional bytes written by the Autocomplete
 * @param: line:        The input line of text that should be completed.
 * @param: bufsize:    [> num_written] The available buffer size in bytes, starting at `line' (must not be exceeded)
 * @param: num_written: The amount of bytes already filled in by the user.
 * @return: * :         The number of bytes appended by auto-completion. */
typedef NONNULL((1)) size_t (KCALL *dbg_autocomplete_t)(char *__restrict line,
                                                        size_t bufsize, size_t num_written);

/* Default auto completion function for the debug command line. */
FUNDEF NONNULL((1)) size_t
NOTHROW(KCALL dbg_autocomplete_command)(char *__restrict line,
                                        size_t bufsize, size_t num_written);

/* Read a single line of user-input from the debug terminal, and fill `buf'
 * NOTE: This function also performs tab-completion, as well as keep an input
 *       history backlog.
 * @param: autocomplete: The autocomplete function that should be used
 *                       for TAB (or `NULL' if this should be disabled)
 * @return: * : The number of bytes read and written to `buf' */
FUNDEF size_t KCALL dbg_readline(/*utf-8*/ char *__restrict buf, size_t bufsize,
                                 dbg_autocomplete_t autocomplete);
#define DBG_MAXLINE 256 /* Default max length of a line (aka. intended size for `dbg_readline:buf') */


#endif /* __CC__ */

DECL_END
#endif /* CONFIG_HAVE_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_INPUT_H */
