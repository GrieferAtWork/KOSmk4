/* Copyright (c) 2019-2023 Griefer@Work                                       *
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
 *    Portions Copyright (c) 2019-2023 Griefer@Work                           *
 * 2. Altered source versions must be plainly marked as such, and must not be *
 *    misrepresented as being the original software.                          *
 * 3. This notice may not be removed or altered from any source distribution. *
 */
#ifndef GUARD_KERNEL_INCLUDE_DEBUGGER_INPUT_H
#define GUARD_KERNEL_INCLUDE_DEBUGGER_INPUT_H 1

#include <kernel/compiler.h>

#include <debugger/config.h>

#ifdef CONFIG_HAVE_KERNEL_DEBUGGER
#include <kernel/types.h>

#include <stdbool.h>

DECL_BEGIN

#ifdef __CC__

/* Wait for the user to press a key and return its keycode.
 * @return: * : One of `KEY_*' (from <kos/keyboard.h>) */
FUNDEF u16 NOTHROW(FCALL dbg_getkey)(void);
FUNDEF NOBLOCK u16 NOTHROW(FCALL dbg_trygetkey)(void); /* @return: 0: No keys available. */

/* Unget a key to be re-returned by `dbg_(try)getkey'
 * When ungetting multiple keys, the key last unget'ed will be returned last. */
FUNDEF NOBLOCK bool NOTHROW(FCALL dbg_ungetkey)(u16 key);

/* Wait for the user to press a key and return the pressed character.
 * NOTE:   Modifier   keys   aren't   returned   by   this  function. */
FUNDEF /*utf-8*/ char NOTHROW(FCALL dbg_getc)(void);
FUNDEF /*utf-32*/ char32_t NOTHROW(FCALL dbg_getuni)(void);
FUNDEF NOBLOCK /*utf-8*/ char NOTHROW(FCALL dbg_trygetc)(void); /* @return: 0: No characters available. */
FUNDEF NOBLOCK /*utf-32*/ char32_t NOTHROW(FCALL dbg_trygetuni)(void); /* @return: 0: No characters available. */

/* Unget a character to be re-returned by `dbg_(try)get(c|uni)'
 * When ungetting multiple characters, the character last unget'ed will be returned last. */
FUNDEF NOBLOCK bool NOTHROW(FCALL dbg_ungetc)(/*utf-8*/ char ch);
FUNDEF NOBLOCK bool NOTHROW(FCALL dbg_ungetuni)(/*utf-32*/ char32_t ch);

/* Check if there are pending unicode characters. (s.a. `dbg_getuni()') */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_hasuni)(void);

/* Check if there are pending utf-8 characters. (s.a. `dbg_getc()') */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_haschar)(void);

/* Purge pending unicode characters. */
FUNDEF NOBLOCK void NOTHROW(FCALL dbg_purgeuni)(void);

/* Check if a given modifier key is being held down. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_isholding_ctrl)(void);
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_isholding_shift)(void);
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_isholding_alt)(void);
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_isholding_altgr)(void);



#if 0 /* TODO */
/* Accepted debugger IRQ levels. */
#define DBG_IRQLEVEL_NONE    0 /* Code is never considered to be interrupted. */
#define DBG_IRQLEVEL_CTRL_C  1 /* An interrupt is present as soon as a \3-byte is pending for `dbg_getc()' */
#define DBG_IRQLEVEL_KEYDOWN 2 /* An interrupt is present as soon as a key-down event is pending,
                                * or there  is unread  data  for `dbg_getc()'  or  `dbg_getuni()' */
#define DBG_IRQLEVEL_INPUT   3 /* An interrupt is present once any kind of input is pending. */

/* The debugger IRQ level, which  can be used to  select
 * which condition is checked for by `dbg_interrupted()'
 * Must be one of `DBG_IRQLEVEL_*' */
DATDEF unsigned int dbg_irqlevel;

/* Set to  true if  the caller  is considered  to have  been
 * interrupted, as per the current setting of `dbg_irqlevel' */
DATDEF bool const volatile dbg_interrupted;

/* Try  to clear `dbg_interrupted',  but keep it turned
 * on in case the selected  IRQ event is still  raised.
 * Alternatively, if the interrupt is no longer raised,
 * then `dbg_interrupted' is set to `false' */
DATDEF void NOTHROW(FCALL dbg_update_interrupted)(void);
#endif

/* Codes for what kind of input to await. */
#define DBG_AWAIT_GETC   0 /* Await `dbg_getc()' */
#define DBG_AWAIT_GETUNI 1 /* Await `dbg_getuni()' */
#define DBG_AWAIT_GETKEY 2 /* Await `dbg_getkey()' */

/* Begin/end expecting further user-input in the near future.
 * While  user-input is being awaited, `dbg_awaituser()' will
 * return `true' when `dbg_getc()' would not block.
 * @param: what: One of `DBG_AWAIT_*' */
FUNDEF NOBLOCK void NOTHROW(FCALL dbg_awaituser_begin)(unsigned int what);
FUNDEF NOBLOCK void NOTHROW(FCALL dbg_awaituser_end)(__BOOL force DFL(0));

/* Check if there is pending user-input left to-be processed,
 * and that the  debugger is  currently awaiting  user-input.
 * This function should  be called  from within  long-running
 * functions, and a `true' return value should be interpreted
 * as a request to stop the function and return to the caller
 * with some sort of consistent state as soon as possible. */
FUNDEF NOBLOCK ATTR_PURE WUNUSED bool NOTHROW(FCALL dbg_awaituser)(void);


#endif /* __CC__ */

DECL_END
#endif /* CONFIG_HAVE_KERNEL_DEBUGGER */

#endif /* !GUARD_KERNEL_INCLUDE_DEBUGGER_INPUT_H */
